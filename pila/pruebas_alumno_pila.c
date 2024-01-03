#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
void pruebas_pila_vacia(void);
void pruebas_pila_algunos_elementos(void);
void pruebas_pila_volumen(void);

void pruebas_pila_alumno() {
	pruebas_pila_vacia();
	pruebas_pila_algunos_elementos();
	pruebas_pila_volumen();


}

void pruebas_pila_vacia(void){
	pila_t *prueba = pila_crear();
    
	//PRUEBA DESAPILAR Y VER TOPE EN LISTA RECIEN CREADA
	printf("\t\t~~~ PRUEBAS PILA RECIEN CREADA ~~~\n\n");
	print_test("Prueba pila vacia", pila_esta_vacia(prueba));
	print_test("Prueba desapilar pila recien creada", pila_desapilar(prueba) == NULL);
	print_test("Prueba ver tope pila recien creada", pila_ver_tope(prueba) == NULL);
	pila_destruir(prueba);
}

void pruebas_pila_algunos_elementos(void){
	pila_t *prueba = pila_crear();
	int entero = 5;
	char caracter = 'b';
	printf("\n\t\t~~~ PRUEBAS APILAR DESAPILAR SIMPLES ~~~\n\n");
	print_test("Prueba apilar numero 5", pila_apilar(prueba, &entero));
	print_test("Ver tope", pila_ver_tope(prueba) == &entero);
	entero = 8;
	print_test("Prueba apilar numero 8", pila_apilar(prueba, &entero));
	print_test("Ver tope", pila_ver_tope(prueba) == &entero);
	entero = 10;
	print_test("Prueba apilar numero 10", pila_apilar(prueba, &entero));
	print_test("Ver tope", pila_ver_tope(prueba) == &entero);
	print_test("Prueba desapilar", pila_desapilar(prueba) == &entero);
	print_test("Ver tope", pila_ver_tope(prueba) == &entero);
	print_test("Prueba desapilar", pila_desapilar(prueba) == &entero);
	print_test("Prueba apilar char", pila_apilar(prueba, &caracter));
	print_test("Ver tope", pila_ver_tope(prueba) == &caracter);
	caracter = 'd';
	print_test("Prueba apilar char", pila_apilar(prueba, &caracter));
	print_test("Ver tope", pila_ver_tope(prueba) == &caracter);
	print_test("Prueba apilar NULL", pila_apilar(prueba, NULL));
	print_test("Ver tope", pila_ver_tope(prueba) == NULL);
	print_test("Prueba desapilar", pila_desapilar(prueba) == NULL);
	print_test("Prueba desapilar", pila_desapilar(prueba) == &caracter);
	print_test("Prueba desapilar", pila_desapilar(prueba) == &caracter);
	print_test("Prueba desapilar", pila_desapilar(prueba) == &entero);
	// VERIFICO QUE ESTA VACIA Y QUE VER TOPE Y DESAPILAR SON INVALIDAS
	print_test("Prueba pila vacia", pila_esta_vacia(prueba));
	print_test("Prueba desapilar pila vacia", pila_desapilar(prueba) == NULL);
	print_test("Prueba ver tope pila vacia", pila_ver_tope(prueba) == NULL);
	pila_destruir(prueba);
}

void pruebas_pila_volumen(void){
	pila_t *prueba = pila_crear();
	int v;
	int *volumen = &v;
	bool error_check = true;
	printf("\n\t\t~~~ PRUEBAS DE VOLUMEN (APILAR Y DESAPILAR 10000 ELEMENTOS)~~~\n\n");
	for(v = 0;v < 10000; v++){
		pila_apilar(prueba, &volumen[v]);
		error_check &= (pila_ver_tope(prueba)==&volumen[v]);
	}
	print_test("Se apilaron 10000 elementos", error_check);
	error_check = true;
	for(v = 9999; v >= 0; v--){
		error_check &= (pila_ver_tope(prueba)==&volumen[v]);
		pila_desapilar(prueba);
	}
	print_test("Se desapilaron 10000 elementos", error_check);
	print_test("Prueba ver tope pila vacia", pila_ver_tope(prueba) == NULL);
	print_test("Prueba desapilar pila vacia", pila_desapilar(prueba) == NULL);
	print_test("Prueba pila vacia", pila_esta_vacia(prueba));
	pila_destruir(prueba);
}
