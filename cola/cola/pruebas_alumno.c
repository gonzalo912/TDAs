#include "cola.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "testing.h"
#include "pila.h"

void destruir_wrapper(void*);

void pruebas_cola_recien_creada(void);
void pruebas_cola_simples(void);
void pruebas_cola_volumen(void);
void pruebas_cola_TDA(void);

void pruebas_cola_alumno(void){
	pruebas_cola_recien_creada();
	pruebas_cola_simples();
	pruebas_cola_volumen();
	pruebas_cola_TDA();
}


void pruebas_cola_recien_creada(void){
	cola_t *cola = cola_crear();
	//cola_destruir(cola, NULL);
	printf("\t\t\t~~~~PRUEBAS COLA RECIEN CREADA~~~\n");
	print_test("Prueba cola vacia", cola_esta_vacia(cola) == true);
	print_test("Prueba ver primero", cola_ver_primero(cola) == NULL);
	print_test("Prueba desencolar", cola_desencolar(cola) == NULL);
	cola_destruir(cola, NULL);
}

void pruebas_cola_simples(void){
	cola_t *cola = cola_crear();
	char vector_pruebas[4] = {'h', 'o', 'l', 'a'};
	int entero_pruebas = 40000;
	printf("\t\t\t~~~~PRUEBAS COLA SIMPLES~~~\n");
	print_test("Prueba encolar entero", cola_encolar(cola, &entero_pruebas) == true);
	print_test("Prueba encolar arreglo", cola_encolar(cola, &vector_pruebas) == true);
	print_test("Prueba encolar NULL", cola_encolar(cola, NULL) == true);
	print_test("Prueba ver primero", cola_ver_primero(cola) == &entero_pruebas);
	print_test("Prueba desencolar entero", cola_desencolar(cola) == &entero_pruebas);
	print_test("Prueba desencolar arreglo", cola_desencolar(cola) == &vector_pruebas);
	print_test("Prueba desencolar NULL", cola_desencolar(cola) == NULL);
	print_test("Prueba desencolar cola vacia", cola_desencolar(cola) == NULL);
	print_test("Prueba cola vacia", cola_esta_vacia(cola) == true);
	print_test("Prueba ver primero", cola_ver_primero(cola) == NULL);
	cola_destruir(cola, NULL);
}

void pruebas_cola_volumen(void){
	cola_t *cola = cola_crear();
	unsigned int volumen[10000];
	unsigned int v;
	printf("\t~~~~PRUEBAS DE VOLUMEN (APILAR Y DESAPILAR 10000 ELEMENTOS)~~~\n");
	for(v = 0;v < 10000; v++){
		volumen[v] = v;
		cola_encolar(cola, &volumen[v]);

	}
	for(v = 10000; v > 0; v--){
		cola_desencolar(cola);
	}
	print_test("Prueba ver primero cola vacia", cola_ver_primero(cola) == NULL);
	print_test("Prueba desencolar cola vacia", cola_desencolar(cola) == NULL);
	print_test("Prueba cola vacia", cola_esta_vacia(cola));
	cola_destruir(cola, NULL);
}

void pruebas_cola_TDA(void){
	pila_t *pila = pila_crear();
	cola_t *cola = cola_crear();
	printf("\t\t\t~~~~PRUEBAS ENCOLAR TDA PILA~~~\n");
	print_test("Prueba pila esta vacia", pila_esta_vacia(pila) == true);
	print_test("Prueba encolar pila", cola_encolar(cola, pila));
	print_test("Prueba ver primero", cola_ver_primero(cola) == pila);
	cola_destruir(cola, destruir_wrapper);
}

void destruir_wrapper(void* dato){
	pila_destruir(dato);
}