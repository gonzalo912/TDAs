#include "vector.h" 
#include <stdbool.h>
#include <stdlib.h>


// Funciones del alumno.

// ...
size_t vector_largo(vector_t* vector) {
	return vector->tam;
}

void vector_destruir(vector_t* vector) {
	free(vector->datos);
	free(vector);
}

bool vector_obtener(vector_t* vector, size_t pos, int* valor) { 
	if(pos > vector->tam-1 || vector->tam == 0)
		return false;
	*valor = vector->datos[pos];
	return true;
}

bool vector_guardar(vector_t* vector, size_t pos, int valor) { 
	if(pos > vector->tam-1 || vector->tam == 0)
		return false;
	vector->datos[pos] = valor;
	return true;
}


// Funciones implementadas por la catedra.


/* en el .h declara una varialble struct llamada vector_t. Define vector de tipo vector_t y le asigna el tamaño de la estructura vector_t.
Luego, accede a la estructura llamada vector de la forma vector->datos (accedo al miembro datos de vector) y le asigna el tamaño especificado por tam
Por ultimo le asigna a la variable tam de vector, el valor de tam especificado en la funcion vector_crear.

*/

vector_t* vector_crear(size_t tam) {
    vector_t* vector = malloc(sizeof(vector_t));

    if (vector == NULL) {
        return NULL;
    }
    vector->datos = malloc(tam * sizeof(int));
    if (tam > 0 && vector->datos == NULL) {
        free(vector);
        return NULL;
    }
    vector->tam = tam;
    return vector;
}

bool vector_redimensionar(vector_t* vector, size_t tam_nuevo) {
    int* datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(int));

    // Cuando tam_nuevo es 0, es correcto si se devuelve NULL.
    // En toda otra situación significa que falló el realloc.
    if (tam_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }

    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}
