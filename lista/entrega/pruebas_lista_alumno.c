#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "testing.h"
#include "pila.h"

#define CANTIDAD_ELEMENTOS 20
#define DIVISOR 2

void destruir_wrapper(void*);

/*FUNCIONES DE PRUEBA PARA LA LISTA*/

void pruebas_lista_recien_creada(void);
void pruebas_lista_simples(void);
void pruebas_lista_volumen(void);
void pruebas_lista_TDA(void);

/*FUNCIONES DE PRUEBA PARA EL ITERADOR EXTERNO*/

void pruebas_iter_recien_creado(void);
void pruebas_iter_simples(void);
void pruebas_iter_doble(void);

/*FUNCIONES DE PRUEBA PARA EL ITERADOR INTERNO*/

bool imprimir_lista(void* dato, void* extra);
void pruebas_iter_interno(void);


void pruebas_lista_alumno(void){
	pruebas_lista_recien_creada();
	pruebas_lista_simples();
	pruebas_lista_volumen();
	pruebas_lista_TDA();
	pruebas_iter_recien_creado();
	pruebas_iter_simples();
	pruebas_iter_doble();
	pruebas_iter_interno();
}


void pruebas_lista_recien_creada(void){
	lista_t *lista = lista_crear();
	//lista_destruir(lista, NULL);
	printf("\t\t\t~~~~PRUEBAS LISTA RECIEN CREADA~~~\n");
	print_test("Prueba lista vacia", lista_esta_vacia(lista) == true);
	print_test("Prueba ver primero", lista_ver_primero(lista) == NULL);
	print_test("Prueba borrar primero", lista_borrar_primero(lista) == NULL);
	print_test("Prueba ver primero", lista_ver_primero(lista) == NULL);
	print_test("Prueba ver ultimo", lista_ver_ultimo(lista) == NULL);
	print_test("Prueba largo", lista_largo(lista) == 0);
	lista_destruir(lista, NULL);
}

void pruebas_lista_simples(void){
	lista_t *lista = lista_crear();
	char vector_pruebas[4] = {'h', 'o', 'l', 'a'};
	int entero_pruebas = 40000;
	printf("\t\t\t~~~~PRUEBAS LISTA SIMPLES~~~\n");
	print_test("Prueba enlistar entero", lista_insertar_ultimo(lista, &entero_pruebas) == true);
	print_test("Prueba enlistar arreglo", lista_insertar_ultimo(lista, &vector_pruebas) == true);
	print_test("Prueba enlistar NULL", lista_insertar_primero(lista, NULL) == true);
	print_test("Prueba ver primero", lista_ver_primero(lista) == NULL);
	print_test("Prueba desenlistar entero", lista_borrar_primero(lista) == NULL);
	print_test("Prueba desenlistar arreglo", lista_borrar_primero(lista) == &entero_pruebas);
	print_test("Prueba desenlistar NULL", lista_borrar_primero(lista) == &vector_pruebas);
	print_test("Prueba desenlistar lista vacia", lista_borrar_primero(lista) == NULL);
	print_test("Prueba lista vacia", lista_esta_vacia(lista) == true);
	print_test("Prueba ver primero", lista_ver_primero(lista) == NULL);
	lista_destruir(lista, NULL);
}

void pruebas_lista_volumen(void){
	lista_t *lista = lista_crear();
	unsigned int volumen[10000];
	unsigned int v;
	bool flag = true;
	printf("\t~~~~PRUEBAS DE VOLUMEN (APILAR Y DESAPILAR 10000 ELEMENTOS)~~~\n");
	for(v = 0;v < 10000; v++){
		volumen[v] = v;
		flag&=lista_insertar_primero(lista, &volumen[v]);
	}
	print_test("Agregar 10000 elementos al comienzo de la lista", flag);
	flag = true;
	for(v = 10000; v > 0; v--){
		lista_borrar_primero(lista);
	}
	print_test("Quitar 10000 elementos de la lista", flag);
	flag = true;
	for(v = 0;v < 10000; v++){
		volumen[v] = v;
		flag&=lista_insertar_ultimo(lista, &volumen[v]);
	}
	print_test("Agregar 10000 elementos al final de la lista", flag);
	flag = true;
	for(v = 10000; v > 0; v--){
		lista_borrar_primero(lista);
	}
	print_test("Quitar 10000 elementos de la lista", flag);
	print_test("Prueba ver primero lista vacia", lista_ver_primero(lista) == NULL);
	print_test("Prueba quitar elemento de lista vacia", lista_borrar_primero(lista) == NULL);
	print_test("Prueba lista vacia", lista_esta_vacia(lista));
	lista_destruir(lista, NULL);
}

void pruebas_lista_TDA(void){
	pila_t *otra_pila = pila_crear();
	pila_t *pila = pila_crear();
	lista_t *lista = lista_crear();
	printf("\t\t~~~~PRUEBAS AGREGAR TDA PILA A LA LISTA~~~\n");
	print_test("Prueba pila esta vacia", pila_esta_vacia(pila) == true);
	print_test("Prueba agregar pila al principio", lista_insertar_primero(lista, pila));
	print_test("Prueba agregar otra pila al final", lista_insertar_ultimo(lista, otra_pila));
	print_test("Prueba ver primero", lista_ver_primero(lista) == pila);
	print_test("Prueba ver ultimo", lista_ver_ultimo(lista) == otra_pila);
	print_test("Eliminar pila de la lista", lista_borrar_primero(lista) == pila);
	print_test("Eliminar la otra pila de la lista", lista_borrar_primero(lista) == otra_pila);
	pila_destruir(pila);
	pila_destruir(otra_pila);
	lista_destruir(lista, destruir_wrapper);
}

void pruebas_iter_recien_creado(void){
	lista_t *lista = lista_crear();
	lista_iter_t* iter = lista_iter_crear(lista);
	printf("\t\t\t~~~~PRUEBAS ITERADOR RECIEN CREADO~~~\n");
	print_test("Prueba iterador ver actual", lista_iter_ver_actual(iter) == NULL);
	print_test("Prueba borrar elemento con iterador", lista_iter_borrar(iter) == NULL);
	print_test("Prueba iterador al final", lista_iter_al_final(iter) == true);
	print_test("Prueba avanzar", lista_iter_avanzar(iter) == false);
	lista_iter_destruir(iter);
	lista_destruir(lista, NULL);
}

void pruebas_iter_simples(void){
	char char_prueba = 'a';
	char char_final = 'b';
	int entero_pruebas = 40000;
	char vector_pruebas[4] = {'h', 'o', 'l', 'a'};
	size_t index = 1334;
	unsigned char test = 2;
	lista_t *lista = lista_crear();
	lista_iter_t* iter = lista_iter_crear(lista);
	printf("\t\t\t~~~~PRUEBAS ITERADOR SIMPLES~~~\n");
	print_test("Insertar dato al principio", lista_iter_insertar(iter, &index));
	print_test("Insertar dato al principio", lista_iter_insertar(iter, &vector_pruebas));
	print_test("Insertar dato al principio", lista_iter_insertar(iter, &entero_pruebas));
	print_test("Insertar dato al principio", lista_iter_insertar(iter, &test));
	print_test("Prueba ver largo", lista_largo(lista) == 4);
	print_test("Prueba ver actual", lista_iter_ver_actual(iter) == &test);
	print_test("Prueba ver primero", lista_ver_primero(lista) == &test);
	print_test("Prueba ver ultimo", lista_ver_ultimo(lista) == &index);
	print_test("Prueba borrar", lista_iter_borrar(iter));
	print_test("Prueba borrar", lista_iter_borrar(iter));
	print_test("Prueba borrar", lista_iter_borrar(iter));
	print_test("Prueba borrar", lista_iter_borrar(iter));
	print_test("Prueba ver largo", lista_largo(lista) == 0);
	print_test("Prueba ver actual", lista_iter_ver_actual(iter) == NULL);
	print_test("Prueba ver primero", lista_ver_primero(lista) == NULL);
	print_test("Prueba ver ultimo", lista_ver_ultimo(lista) == NULL);
	print_test("Insertar dato al principio", lista_iter_insertar(iter, &index));
	print_test("Insertar dato al principio", lista_iter_insertar(iter, &vector_pruebas));
	print_test("Insertar dato al principio", lista_iter_insertar(iter, &entero_pruebas));
	print_test("Insertar dato al principio", lista_iter_insertar(iter, &test));
	print_test("Prueba ver actual", lista_iter_ver_actual(iter) == &test);
	print_test("Prueba ver primero", lista_ver_primero(lista) == &test);
	print_test("Prueba ver ultimo", lista_ver_ultimo(lista) == &index);
	print_test("Avanzar", lista_iter_avanzar(iter));
	print_test("Avanzar", lista_iter_avanzar(iter));
	print_test("Prueba ver actual", lista_iter_ver_actual(iter) == &vector_pruebas);
	print_test("Ver ultimo", lista_ver_ultimo(lista) == &index);
	print_test("Ver primero", lista_ver_primero(lista) == &test);
	print_test("Prueba insertar en el medio de la lista", lista_iter_insertar(iter, &char_prueba));
	print_test("Ver ultimo", lista_ver_ultimo(lista) == &index);
	print_test("Ver primero", lista_ver_primero(lista) == &test);
	print_test("Prueba ver actual", lista_iter_ver_actual(iter) == &char_prueba);
	print_test("Avanzar", lista_iter_avanzar(iter));
	print_test("Avanzar", lista_iter_avanzar(iter));
	print_test("Avanzar", lista_iter_avanzar(iter));
	print_test("Prueba avanzar invalida", lista_iter_avanzar(iter) == false);
	print_test("Prueba insertar al final", lista_iter_insertar(iter, &char_final));
	print_test("Prueba ver actual", lista_iter_ver_actual(iter) == &char_final);
	print_test("Prueba borrar", lista_iter_borrar(iter));
	lista_iter_destruir(iter);
	lista_destruir(lista, NULL);
}

void pruebas_iter_doble(void){
	lista_t* lista = lista_crear();
	lista_iter_t *iter1 = lista_iter_crear(lista);
	char letras[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
	int numeros[4] = {4, 1000, -400, 20000}; 
	printf("\t\t\t~~~~PRUEBAS CON DOS ITERADORES SIMULTANEAMENTE~~~\n");
	print_test("Prueba insertar letra a (iterador 1)", lista_iter_insertar(iter1, &letras[1]));
	print_test("Prueba insertar letra b (iterador 1)", lista_iter_insertar(iter1, &letras[2]));
	print_test("Prueba insertar letra c (iterador 1)", lista_iter_insertar(iter1, &letras[3]));
	print_test("Prueba insertar letra d (iterador 1)", lista_iter_insertar(iter1, &letras[4]));
	print_test("Ver ultimo", lista_ver_ultimo(lista) == &letras[1]);
	print_test("Insertar con iterador 1", lista_iter_insertar(iter1, &numeros[0]));
	print_test("Ver ultimo", lista_ver_ultimo(lista) == &letras[1]);
	print_test("Avanzar iterador 1", lista_iter_avanzar(iter1));
	print_test("Avanzar iterador 1", lista_iter_avanzar(iter1));
	print_test("Avanzar iterador 1", lista_iter_avanzar(iter1));
	print_test("Ver actual iterador 1", lista_iter_ver_actual(iter1) == &letras[2]);
	print_test("Avanzar iterador 1", lista_iter_avanzar(iter1));
	print_test("Avanzo y deberia estar al final", lista_iter_avanzar(iter1));
	print_test("Esta al final", lista_iter_al_final(iter1));
	print_test("No puedo avanzar", lista_iter_avanzar(iter1) == false);
	print_test("Inserto al final con iterador 1", lista_iter_insertar(iter1, &numeros[2]));
	print_test("Ver ultimo", lista_ver_ultimo(lista) == &numeros[2]);
	print_test("Avanzo iterador 1 y esta al final", lista_iter_avanzar(iter1)&&lista_iter_al_final(iter1));
	lista_iter_t *iter2 = lista_iter_crear(lista);
	print_test("Ver ultimo", lista_ver_ultimo(lista) == &numeros[2]);
	print_test("Ver primero", lista_ver_primero(lista) == &numeros[0]);
	print_test("Creacion de segundo iterador", true);
	print_test("Avanzar iterador 2", lista_iter_avanzar(iter2));
	print_test("Ver actual iterador 2", lista_iter_ver_actual(iter2) == &letras[4]);
	print_test("Prueba insertar letra e (iterador 2)", lista_iter_insertar(iter2, &letras[5]));
	print_test("Prueba ver actual iterador 2", lista_iter_ver_actual(iter2) == &letras[5]);
	lista_destruir(lista, NULL);
	lista_iter_destruir(iter1);
	lista_iter_destruir(iter2);
}

void pruebas_iter_interno(void){
	lista_t *lista = lista_crear();
	size_t contador = 0;
	size_t vector[CANTIDAD_ELEMENTOS];
	printf("\t\t\t~~~~PRUEBAS ITERADOR INTERNO~~~\n");
	for(size_t i = 0; i < CANTIDAD_ELEMENTOS; i++){
		vector[i] = i;
		lista_insertar_ultimo(lista, &vector[i]);
	}
	lista_iterar(lista, imprimir_lista, &contador);
	lista_destruir(lista, NULL);
	print_test("Sin errores", true);

}

bool imprimir_lista(void* dato, void* extra){
	if(*(unsigned int*)extra > CANTIDAD_ELEMENTOS/DIVISOR)
		return false;
	print_test("Dato impreso", dato);
	*(unsigned int*)extra = *(unsigned int*)extra + 1;
	return true;

}

void destruir_wrapper(void* dato){
	pila_destruir(dato);
}