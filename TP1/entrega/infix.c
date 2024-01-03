#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "pila.h"
#include "cola.h"
#include "strutil.h"


#define BASE_NUMERICA 10

#define NUM	0 	
#define	SUMA 1
#define	RESTA 2
#define PRODUCTO 3
#define DIVISION 4
#define POT 5
#define PARENTESIS_IZQUIERDO 6
#define PARENTESIS_DERECHO 7
#define ERROR 9

#define IZQ_DER	1
#define DER_IZQ 2

typedef struct token{
	char* character;
	unsigned char asoc;
	unsigned char type;
	long int val;
}tok;

void separar_en_terminos(const char* linea);

char* infix(const char* eq, const size_t tam_buffer);

tok parse(const char* token);

char* cola_a_string(cola_t *cola, size_t tam);

int main(void){
	char *eq = NULL;
	char* new_eq = NULL;
	size_t buffer = 1;
	char *linea = malloc(sizeof(char));
	char **strv = NULL;
	while(getline(&linea, &buffer, stdin) != -1 && linea[0] != '\0'){
		if(linea[strlen(linea)-1] < 32)
			linea[strlen(linea)-1] = '\0';
 		strv = split(linea, ' ');
 		eq = join(strv, '\0');
 		new_eq = infix(eq, buffer);
 		if(new_eq)
 			printf("%s\n", new_eq);
 		else
 			printf("ERROR\n");
		free_strv(strv);
		free(eq);
		free(new_eq);
	}
	free(linea);
}

char* infix(const char* eq, const size_t tam_buffer){
	pila_t* pila = pila_crear();
	cola_t* cola = cola_crear();
	tok* tope_pila = NULL;
	char* resultante = NULL;
	if(!eq || !cola || !pila)
		return NULL;
	tok *token = calloc(tam_buffer, sizeof(tok));
	size_t i = 0, j = 0;
	bool ok = true, error = false;
	while(ok&&!error){
		token[j] = parse(eq+i);
		if(token[j].type == ERROR && eq[i] < 32 && eq[i] != '\0')
			error = true;
		if(token[j].type == NUM){
			cola_encolar(cola, &token[j]);
		} else if(token[j].type > NUM && token[j].type < PARENTESIS_IZQUIERDO){
			if(!pila_esta_vacia(pila)){
				while((tope_pila = (tok*)pila_ver_tope(pila)) &&
				 	(tope_pila->type > NUM && tope_pila->type < PARENTESIS_IZQUIERDO) &&
					((token[j].asoc == IZQ_DER && token[j].type <= tope_pila->type)||
					(token[j].asoc == DER_IZQ && token[j].type < tope_pila->type))){
					cola_encolar(cola, pila_desapilar(pila));
				}
			}
			pila_apilar(pila, &token[j]);
		} else if(token[j].type == PARENTESIS_IZQUIERDO){
			pila_apilar(pila, &token[j]);
		} else if(token[j].type == PARENTESIS_DERECHO){
			while((tope_pila = (tok*)pila_ver_tope(pila)) &&
				tope_pila->type != PARENTESIS_IZQUIERDO){
				cola_encolar(cola, pila_desapilar(pila));
			}
			pila_desapilar(pila);
		}
		if(eq[i] == '\0'){
			ok = false;
			while(!pila_esta_vacia(pila)){
				tope_pila = (tok*)pila_ver_tope(pila);
				if(tope_pila->type == PARENTESIS_DERECHO ||
					tope_pila->type == PARENTESIS_IZQUIERDO)
					error = true;
				cola_encolar(cola, pila_desapilar(pila));
			}
		}
		if(token[j].type == NUM)
			i+=(token[j].val==0)? 1:log10((token[j].val))+1;
		else
			i++;
		j++;
	}
	if(!error)
		resultante = cola_a_string(cola, tam_buffer);
	else
		resultante = NULL;
	free(token);
	pila_destruir(pila);
	return resultante;
}

tok parse(const char *token){
	tok t = {.val = -1, .asoc = 0, .character = "?"};
	if(isdigit(token[0])){
		t.type = NUM;
		t.val = strtol(token, NULL, BASE_NUMERICA);
	} else if(token[0] == '+'){
		t.character = "+";
		t.type = RESTA;
		t.asoc = IZQ_DER;
	} else if(token[0] == '-'){
		t.character = "-";
		t.type = RESTA;
		t.asoc = IZQ_DER;
	} else if(token[0] == '*'){
		t.character = "*";
		t.type = DIVISION;
		t.asoc = IZQ_DER;
	} else if(token[0] == '/'){
		t.character = "/";
		t.type = DIVISION;
		t.asoc = IZQ_DER;
	} else if(token[0] == '^'){ 
		t.character = "^";
		t.type = POT;
		t.asoc = DER_IZQ;
	} else if(token[0] == '('){
		t.type = PARENTESIS_IZQUIERDO;
	} else if(token[0] == ')'){
		t.type = PARENTESIS_DERECHO;
	} else {
		t.type = ERROR;
	}
	return t;
}

char* cola_a_string(cola_t *cola, size_t tam){
	char* str = calloc(tam+1, sizeof(char));
	tok aux = {.val = 0, .type = 0, .asoc = 0, .character = '\0'};
	while(!cola_esta_vacia(cola)){
		aux = *(tok*)cola_desencolar(cola);
		if(aux.type == NUM)
			sprintf(str+strlen(str), "%ld ", aux.val);		
		if(aux.type > NUM && aux.type < PARENTESIS_IZQUIERDO)
			sprintf(str+strlen(str), "%s ", aux.character);	
	}
	cola_destruir(cola, NULL);
	return str;
}