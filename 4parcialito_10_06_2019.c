//4TO PARCIALITO 10/06/2019
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

/*
1.  Teniendo el TDA Conjunto de enteros el cual se representa sobre
    `typedef struct {int *e; size_t n;} conjunto_t;` en donde `e` es un vector
    **ordenado** de longitud `n` con los elementos contenidos en el conjunto
    se pide:

    a.  Implementar la primitiva

            conjunto_t *conjunto_interseccion(const conjunto_t *a, const conjunto_t *b);

        que compute la intersección entre dos conjuntos. (Asumir que se tiene
        la primitiva `conjunto_t *conjunto_crear();` y la función auxiliar
        `static bool _agregar_al_final(conjunto_t *c, int elem);` que agrega un
        elemento al final sin chequear si esa es su ubicación correcta. **Para
        simplificar:** No hace falta chequear fallas de memoria.)

        **Aclaración:** La función debe resolver el problema eficientemente sin
        llamar a funciones de ordenamiento ni implementar ningún método de
        ordenamiento.

    b.  Si implementáramos la primitiva

            bool conjunto_agregar(conjunto_t *c, int e);

        con una llamada a `_agregar_al_final(c, elem)`, ¿con qué método nos
        convendría ordenar el arreglo después?, justificar brevemente.
*/

typedef struct{
    int *e; //vector ORDENADO 
    size_t n; //longitud del vector e
}conjunto_t;

void conjunto_destruir(conjunto_t *c){

    if(c != NULL){
        if(c->e != NULL)
            free(c->e);
        free(c)
    }
}

conjunto_t *conjunto_crear(size_t n){

    //mem para la estructura
    conjunto_t *c = malloc(sizeof(conjunto_t));
    if(c == NULL){
        printf("Rip la estructura");
        return NULL;
    }

    //mem para el vector
    c->e = malloc(n*sizeof(int));
    if(c->e == NULL){
        printf("rip la memoria para el vector ordenado");
        conjunto_destruir(c);
        return NULL;
    }

    //guardo valor
    c->n = n;

    return c;
}

static bool _agregar_al_final(conjunto_t *c, int elem){

    //agrego un lugar (n+1), lo hago con aux por si falla para no poder lo que tengo en e
    c->n +=1;
    int *aux = realloc(c->e,(c->n)*sizeof(int));
    if(aux == NULL){
        printf("rip el realloqueo bro");
        return false;
    }

    //como no falló, apunto lo de e al aux y guardo el elem al final
    c->e = aux;
    c->e[c->n] = elem;    
    return true;
}

//crear un conjunto con un vector que solo tenga los valores q estan en ambos vectores
conjunto_t *conjunto_interseccion(const conjunto_t *a, const conjunto_t *b) {
   
   //empiezo con un vector c->e vacio
   conjunto_t *c = conjunto_crear(0);

   size_t i = 0, j = 0, cant_repetidos = 0; 
   while(i < a->n && j < b->n) {

      if(a->e[i] < b->e[j]) 
        i++;

      else if(a->e[i] > b->e[i]) 
        j++;

      else { //si son iguales:
         _agregar_al_final(c, a->e[i]);
         i++;
         j++;
         cant_repetidos++;
      }
   }
   c->n = cant_repetidos;
   return c;
}

//1) b. Hay que usar inserción, el arreglo está todo ordenado salvo el último elemento, va a ordenar en T(n). 
//Es de hecho el algoritmo de "insertar_ordenado" que hicimos en clase hace un par de meses y que charlamos cuando dimos ordenamiento.

/*2.  Teniendo una lista **de enteros** en la cual la lista se representa
    `typedef struct {struct nodo *prim;} lista_t;` y el nodo se representa como
    `struct nodo {struct nodo *sig; int dato;};` implementar la primitiva

        void lista_enteros_borrar(lista_t *l, int e);

    que borre todas las ocurrencias del dato `e` en la lista.
    */
//2 )Este hay varias maneras de resolverlo, puede hacerse sin necesidad de casos borde (con dobles punteros). Lo más sencillo sería así:
typedef struct nodo{
    struct nodo *sig;
    int dato;
}nodo_t;


typedef struct{
    nodo_t *prim;
}lista_t;


void lista_enteros_borrar(lista_t *l, int e) {

   // Borro al principio:
   while(l->prim && l->prim->dato == e) {

      nodo_t *aux = l->prim->sig;
      free(l->prim);
      l->prim = aux;

   }

   // Borro del resto:
   nodo_t *ant = l->prim;
   while(ant->sig) {

      nodo_t *actual = ant->sig;
      if(actual->dato == e) {
         ant->sig = actual->sig;
         free(actual);
      }
      else
          ant = actual;

   }
}

///////////////////////////////////////////////////////
//otras maneras de resolverlo:                                                              
                                                                               
void lista_borrar_doble_punteros(lista_t *l, int e) {                          
    nodo_t **pn;                                                          
                                                                               
    // Nos manejamos con el puntero que apunta al nodo sobre el que trabajo.    
    pn = &l->prim;                                                              
                                                                               
    while(*pn != NULL) {                                                        
        if((*pn)->dato == e) {                                                  
            nodo_t *aux = *pn;                                            
            *pn = aux->sig;                                                    
            free(aux);                                                          
        }                                                                      
        else                                                                    
            pn = &(*pn)->sig;                                                  
    }                                                                          
}                                                                              
                                                                               

static nodo_t *borrar_recursivo(nodo_t *n, int e) {                  
    // Caso base: La lista está vacía:                                          
    if(n == NULL)                                                              
        return NULL;                                                            
                                                                               
    // General: Trabajo sobre el primer nodo, recursividad para el resto.      
                                                                               
    // Borramos los elementos del resto de la lista:                            
    nodo_t *resto_lista = borrar_recursivo(n->sig, e);                    
                                                                               
    // Si mi nodo vale e lo tengo que borrar:                                  
    if(n->dato == e) {                                                          
        free(n);                                                                
        return resto_lista;                                                    
    }                                                                          
                                                                               
    // Si no, queda:                                                            
    n->sig = resto_lista;                                                      
    return n;                                                                  
}                                                                              
                                                                               
void lista_borrar_recursiva(lista_t *l, int e) {                                
    // Función wrapper para la recursiva real
    // La función recursiva me devuelve la lista con los elementos borrados.
    l->prim = borrar_recursivo(l->prim, e);                                    
}               

/*3.  Se representa a un color RGB de 24 bits como un entero sin signo `0xAABBCC`
    donde el byte `0xAA` representa el rojo, `0xBB` el verde y `0xCC` el azul.
    Se pide:

    a.  Implementar la función `unsigned char get_rojo(unsigned int color);` que
        devueva el valor de la componente roja.

    b.  Implementar la función `void set_verde(unsigned int *color, unsigned char verde);` que
        cargue la componente de `verde` en el `color` recibido.*/

//3) Este podían resolverlo, así como lo estoy poniendo acá o declarando máscaras para los colores y haciendo máscara + corrimiento. 
//Siendo que se trataba de agarrar bytes enteros no está mal usar un 0xFF como máscara de byte y hacer al revés.

#define SHIFT_ROJO 16
#define SHIFT_VERDE 8

unsigned char get_rojo(unsigned int color) {
    return color >> SHIFT_ROJO;
}

void set_verde(unsigned int *color, unsigned char verde) {
    *color &= ~(0xFF << SHIFT_VERDE); // Clean
    *color |= verde << SHIFT_VERDE; // Set
}


