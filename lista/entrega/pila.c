#include "pila.h"
#include <stdlib.h>
#include <stdio.h>


#define MIN_CAP	10
#define VACIO 0
#define IND_REDIM 2
#define IND_REDUC 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

bool pila_redimensionar(pila_t *pila, size_t nueva_capacidad);

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...


pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));
	if (pila == NULL)
		return NULL;
	pila->datos = malloc(sizeof(void*) * MIN_CAP);
	if(pila->datos == NULL){
		free(pila);
		return NULL;
	}
	pila->cantidad = VACIO;
	pila->capacidad = MIN_CAP;
	return pila;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);		
}

bool pila_esta_vacia(const pila_t *pila){
	return !pila->cantidad;
}

bool pila_apilar(pila_t *pila, void* valor){
	if(pila == NULL)
		return false;
	if(pila->cantidad == pila->capacidad){
		if(!pila_redimensionar(pila, IND_REDIM * pila->capacidad))
			return false;
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
}

void* pila_ver_tope(const pila_t *pila){
	if(pila->cantidad == VACIO)
		return NULL;
	return pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t *pila){
	if(pila_esta_vacia(pila))
		return NULL;
	pila->cantidad--;
	if(pila->cantidad <= pila->capacidad/IND_REDUC && pila->capacidad > MIN_CAP)
		pila_redimensionar(pila, pila->capacidad/IND_REDIM);
	return pila->datos[pila->cantidad];
}


/* FUNCIONES AUXILIARES PARA IMPLEMENTACIÓN */

bool pila_redimensionar(pila_t *pila, size_t nueva_capacidad){
	void** nuevos_datos = realloc(pila->datos, nueva_capacidad * sizeof(void*));
	if(nuevos_datos == NULL)
		return false;
	pila->datos = nuevos_datos;
	pila->capacidad = nueva_capacidad;
	return true;
}



