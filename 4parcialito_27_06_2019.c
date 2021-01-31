//4TO PARCIALITO 27/06/2019
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


/*
1.  Teniendo representado el TDA lista **de enteros** como
    `typedef struct {struct nodo *prim;} lista_t;` y el nodo
    `struct nodo {struct nodo *sig; int dato;};` implementar una función

        void unir_listas_ordenadas(lista_t *d, lista_t *o);

    que reciba dos listas ordenadas `d` y `o` y que junte ambas listas en `d`.
    La lista resultante debe quedar ordenada y la lista `o` debe quedar vacía.

    (**Nota:** Sólo se puede recorrer las listas una única vez.)
*/
//1

struct nodo {
    struct nodo *sig; 
    int dato;
};

typedef struct {
    struct nodo *prim;
} lista_t;


void unir_listas_ordenadas(lista_t *d, lista_t *o){
	if(d->prim == NULL){
		d->prim = o-> prim;
		o->prim = NULL;
	}

	if(d->prim ==NULL)
		return;

	if(d->prim->dato > o->prim->dato){
		struct nodo *aux = d->prim;
		d->prim = o-> prim;
		o->prim = o-> prim->sig;
		d->prim->sig = aux;
	}

	struct nodo *ant = d->prim;
	struct nodo *act = ant->sig;

	while(act!= NULL && o->prim != NULL){
		if(act-> dato > o->prim->dato){
			ant->sig = o->prim;
			o->prim = o->prim->sig;
			ant->sig = act;
		}
		else act = act->sig;
	}

	if(o->prim != NULL){
		ant->sig = o->prim;
		o->prim = NULL;
	}
}
/*
2.  Se quiere implementar un TDA que sea capaz de almacenar 50 valores
    booleanos indexados por un entero entre 0 y 49.

    Se propone implementar el TDA sobre la declaración
    `typedef uint64_t booleanos_t;` y utilizar los bits de este entero para
    guardar los estados de los diferentes booleanos.

    a.  Implementar la primitiva
    `void booleanos_guardar(booleanos_t *b, int indice, bool valor);` que
    almacena el `valor` en la posición `indice`.

    b.  Implementar la primitiva
    `bool booleanos_obtener(const booleanos_t *b, int indice);` que devuelve el
    valor almacenado en la posición `indice`.
*/
//2
#define MASK 0x1
typedef uint64_t booleanos_t;
void booleanos_guardar(booleanos_t *b, int indice, bool valor){
	*b &= ~(MASK <<indice);
	*b |= ((MASK | valor) <<indice);
}

bool booleanos_obtener(const booleanos_t *b, int indice){
	return *b & (MASK << indice);
}

/*3.  Implementar una función recursiva que responda al siguiente prototipo

        bool es_palindromo(const char *s);

    que reciba una cadena de caracteres `s` y que indique si la misma es
    palíndroma o no. Una cadena es palíndroma si se lee igual desde ambos
    lados, como por ejemplo `"neuquen"`.
*/
//3

//REVISAR ESTO PROQUE EN REALIDAD QUIERO COMPARAR CHARS Y ACA NO ESTOY HACIENDO ESO
bool son_iguales(const char *s, size_t l, size_t r){
	if(l >= r)
		return true;
	if(!son_iguales(s, l+1, r-1))
		return false;
}

bool es_palindromo(const char *s){
	size_t tam = strlen(s);
	return son_iguales(s, 0, tam-1);
}




int main(void){
    return 0;
}