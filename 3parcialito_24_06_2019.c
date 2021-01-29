//TERCER PARCIALITO 24/06/2019
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CADENA 200
#define MAX_NUMEROS 20
#define MAX_STR 200

/*1)
1.  Se quiere modelar un TDA que represente una recta en $\mathbb R^2$ (como
    las implementadas en los EJ2 y EJ3). Se pide:

    a.  Declarar la estructura `recta_t` que representa al TDA. Explicar qué
    modela cada uno de los miembros y sus valores posibles.

    b.  Implementar la primitiva `bool recta_x_en_rango(const recta_t *r, float x);`
    que indique si la coordenada `x` está entre los extremos de la recta.

    c.  Implementar la primitiva `bool recta_agregar_punto(recta_t *r, float x, float y);`
    que agrega un punto a la recta.

*/
//Representa una recta de n coordenadas coords. 
//La recta tiene que tener al menos 2 puntos. 
//coords es un arreglo dinámico de vectores de 2 elementos 
//tiene memoria pedida para las n coordenadas. 
//Las coordenadas se encuentran ordenadas por x creciente." <- IMPORTANTE
typedef struct {
   float **coords; 
   size_t n; 
} recta_t;

bool recta_x_en_rango(const recta_t *r, float x) {
   return x >= r->coords[0][0] && x <= r->coords[r->n - 1][0];
}

bool recta_agregar_punto(recta_t *r, float x, float y) {
    
    float *coord = malloc(2 * sizeof(float));
    if(coord == NULL)
        return false;

    coord[0] = x;
    coord[1] = y;

    float **aux = realloc(r->coords, (r->n + 1) * sizeof(float*));
    if(aux == NULL) {
        free(coord);
        return false;
    }

    size_t pos;
    for(pos = 0; pos < r->n; pos++) {
        if(x < r->coords[pos][0])
            break;
    }

    // Insertamos en pos, notar que pos está entre 0 y n (inclusivo).
        size_t i = 0;
    for( i = r->n; i > pos; i--)
        r->coords[i] = r->coords[i - 1];

    r->coords[i] = coord;

    r->n++;

    return true;
}

/*
2.  Se tiene un archivo **binario** que contiene un `size_t` $n$ seguido de $n$
    pares de coordenadas flotantes, según el siguiente esquema:

                                    +----+----+----+----+----+-   -+----+----+
                                    | n  | x1 | y1 | x2 | y2 | ... | xn | yn |
                                    +----+----+----+----+----+-   -+----+----+

    Teniendo definido `typedef float coord_t[2];` se pide:

    a.  Escribir una función
    `bool escribir_coordenadas(const char *r, coord_t *cs, size_t n);` que
    reciba una ruta `r` y un arreglo `cs` de `n` pares de coordenadas y los
    escriba en un archivo **binario** según el formato anterior.

    b.  Escribir una función
    `coord_t *leer_coordenadas(const char *r, size_t *n);` que reciba una ruta
    `r` a un archivo **binario** y devuelva por nombre el arreglo de
    coordenadas contenido en él, y en `n` la cantidad de elementos leídos.
*/
typedef float coord_t[2];

bool escribir_coordenadas(const char *r, coord_t *cs, size_t n) {
   FILE *f = fopen(r, "wb");
   if(f == NULL)
      return false;

   if(fwrite(&n, sizeof(size_t), 1, f) != 1)
        return false;
   if(fwrite(cs, sizeof(coord_t), n, f) != sizeof(coord_t)*n)
        return false;

   fclose(f);

   return true;
}

coord_t *leer_coordenadas(const char *r, size_t *n) {
   FILE *f = fopen(r, "rb");
   if(f == NULL)
       return NULL;

   fread(n, sizeof(float), sizeof(float), f);

   coord_t *v = malloc(*n * sizeof(coord_t));
   if(v == NULL) {
      fclose(f);
      return NULL;
   }

   fread(v, sizeof(coord_t), *n, f);

   fclose(f);

   return v;
}

/*
3.  Dado el formato (y las funciones) del ejercicio 2 escribir un programa que
    se ejecute

        $ ./rotar entrada salida radianes

    que cargue en memoria el arreglo de coordenadas contenido en el archivo
    **binario** `entrada`, rote cada uno de sus elementos por el ángulo
    `radianes` y lo guarde en el archivo **binario** `salida`.

    (Recordar las funciones de transformación
    $x^\prime = x\cos\theta - y\sin\theta$, $y^\prime = x\sin\theta + y\cos\theta$.)
*/

int main(int argc, char *argv[]) {
   if(argc != 4) {
      fprintf(stderr, "Uso: %s <entrada> <salida> <radianes>\n", argv[0]);
      return EXIT_FAILURE;
   }

   size_t n;
   coord_t *v = leer_coordenadas(argv[1], &n);

   if(v == NULL) {
      fprintf(stderr, "No pudo abrirse \"%s\"\n", argv[1]);
      return EXIT_FAILURE;
   }

   //float angulo = atof(argv[3]);
   //<INSERTE AQUÍ EL CÓDIGO DEL EJ2> ;)

   bool escribio = escribir_coordenadas(argv[2], v, n);

   free(v);

   if(! escribio) {
      fprintf(stderr, "No pudo escribirse \"%s\"\n", argv[2]);
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}