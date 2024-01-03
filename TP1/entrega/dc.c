#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "pila.h"
#include "strutil.h"

#define TAM_BUFFER 1
#define BASE_NUMERICA 10

#define NUM	0
#define	RAIZ 1 	
#define	DIVISION 2
#define	RESTA 3
#define PRODUCTO 4
#define LOG 5
#define POT 6
#define SUMA 7
#define TERNARIO 8
#define ERROR 9

typedef struct token{
	unsigned char type;
	long int val;
}tok;

static tok parse(const char *token);

bool evaluar(pila_t *pila, long int*result);

bool operar(unsigned char operacion, long int* resultado, long int num1,
 long int num2, long int num3);

bool es_negativo(const char* token);


int main(void){
	size_t buffer = TAM_BUFFER;
	char *linea = malloc(sizeof(char) * buffer);
	size_t tam = 0;
	char **strv;
	long int resultado = 0;
	pila_t *pila = pila_crear();
	while((tam = getline(&linea, &buffer, stdin)) != EOF){
		if(linea[strlen(linea)-1] < 39)
			linea[strlen(linea)-1] = '\0';
 		strv = split(linea, ' ');
		for(size_t i = 0; strv[i]; i++)
			pila_apilar(pila, strv[i]);
		if(evaluar(pila, &resultado) && pila_esta_vacia(pila))
			printf("%ld\n", resultado);
		else
			printf("ERROR\n");
		free_strv(strv);
	}
	pila_destruir(pila);
	free(linea);
}


bool evaluar(pila_t *pila, long int *result){
	if(pila_esta_vacia(pila))
		return false;
	tok token = parse((char*) pila_desapilar(pila));
	if(token.type == ERROR)
		return false;
	long int primer_operando = 0, segundo_operando = 0, 
		tercer_operando = 0;
	bool ok = true;
	if(token.type == NUM){
		*result = token.val;
		return true;
	}
	if(token.type > NUM){
		ok &= evaluar(pila, result);
		primer_operando = *result;
	}
	if(token.type > RAIZ){
		ok &= evaluar(pila, result);
		segundo_operando = *result;
	}
	if(token.type == TERNARIO){
		ok &= evaluar(pila, result);
		tercer_operando = *result;
	}
	if(ok)
		ok&=operar(token.type, result, primer_operando, segundo_operando, 
			tercer_operando);
	return ok;
}

tok parse(const char *token){
	tok t = {.val = -1};
	if(isdigit(token[0])||es_negativo(token)){
		t.type = NUM;
		t.val = strtol(token, NULL, BASE_NUMERICA);
	} else if(!strcmp(token, "+")){
		t.type = SUMA;
	} else if(!strcmp(token, "-")){
		t.type = RESTA;
	} else if(!strcmp(token, "*")){
		t.type = PRODUCTO;
	} else if(!strcmp(token, "/")){
		t.type = DIVISION;
	} else if(!strcmp(token, "sqrt")){
		t.type = RAIZ;
	} else if(!strcmp(token, "?")){
		t.type = TERNARIO;
	} else if(!strcmp(token, "^")){ 
		t.type = POT;
	} else if(!strcmp(token, "log")){
		t.type = LOG;
	} else {
		t.type = ERROR;
	}
	return t;
}

bool operar(unsigned char operacion, long int* resultado, long int num1,
 long int num2, long int num3){
	if(operacion == SUMA){
		*resultado = /*(long int)*/num1 + num2;
	} else if(operacion == RESTA){
		*resultado = /*(long int)*/num2 - num1;
	} else if(operacion == PRODUCTO){
		*resultado = /*(long int)*/num1 * num2;
	} else if(operacion == DIVISION){
		if(num1 == 0)
			return false;
		*resultado = /*(long int)*/(num2/num1);
	} else if(operacion == RAIZ){
		if(num1 < 0)
			return false;
		*resultado = /*(long int)*/sqrt(num1);
	} else if(operacion == TERNARIO){
		*resultado = num3? num2:num1;
	} else if(operacion == POT){
		if(num1 < 0)
			return false;
		*resultado = pow(num2, num1);
	} else if(operacion == LOG){
		if(num1 < 2)
			return false;
		double x = log(num1);
		double y = log(num2);
		*resultado = (y/x);
	}
	return true;
}

bool es_negativo(const char* token){
	return token[0]=='-'&&isdigit(token[1]);
}

