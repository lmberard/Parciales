//TERCER PARCIALITO 30/05/2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CADENA 200
#define MAX_NUMEROS 20
#define MAX_STR 200

/*1.  Se quiere modelar un TDA que represente a un vector en $\mathbb R^n$. Se
    pide:

    a.  Declarar la estructura `vector_t` que representa el TDA. Explicar qué
    modela cada uno de los miembros y sus valores posibles (*invariante*).

    b.  Implementar la primitiva `size_t vector_dimension(const vector_t *v);`
    que retorne la dimensión $n$ del vector.

    c.  Implementar la primitiva `double vector_norma(const vector_t *v);` que
    devuelve la norma del vector, $|\!|v|\!|$.

    d.  Implementar la primitiva
    `bool vector_sumar(vector_t *a, const vector_t *b);` que sume `b` en `a`,
    si es que son sumables. La función devuelve `true` si la operación pudo
    ser realizada.*/

typedef struct{
    float *vector; //vector de cada componente
    size_t n; //cantidad de componentes del vector (dimension) 
}vector_t;

size_t vector_dimension(const vector_t *v){
    return v->n;
}

double vector_norma(const vector_t *v){
    double suma_cuad = 0;

    for(size_t i = 0; v->n - 1; i++)
        suma_cuad += v->vector[i]*v->vector[i];

    return sqrt(suma_cuad);
}

bool vector_sumar(vector_t *a, const vector_t *b){
    if(a->n == b->n){
        for(size_t i = 0; a->n -1; i++)
            a->vector[i] += b->vector[i];
        return true;
    }
    else return false;
}

/*
2.  Se tiene un archivo **binario** que contiene un `size_t` $n$ seguido de $n$
    flotantes, según el siguiente esquema:

                                    +----+----+----+----+----+-   -+----+
                                    | n  | a1 | a2 | a3 | a4 | ... | an |
                                    +----+----+----+----+----+-   -+----+

    a.  Escribir una función
    `bool escribir_arreglo(const char *r, const float *a, size_t n);` que reciba
    una ruta `r` y un arreglo `a` de `n` elementos y los escriba en un archivo
    **binario** según el formato anterior.

    b.  Escribir una función
    `float *leer_arreglo(const char *r, size_t *n);` que reciba una ruta `r` a
    un archivo binario y devuelva por nombre el arreglo contenido en él, y en
    `n` la cantidad de elementos leídos.
*/

bool escribir_arreglo(const char *r, const float *a, size_t n){
    
    FILE *f = fopen(r,"wb");
    if(f == NULL){
        printf("No se pudo abrir el archivo %s", r);
        return false;
    }

    if(fwrite(&n, sizeof(size_t), 1,f) != 1)
        return false;
    if(fwrite(a,sizeof(float),n,f) !=n*sizeof(float))
        return false;

    fclose(f);
    return true;
}

float *leer_arreglo(const char *r, size_t *n){
    
    FILE *f;
	if((f = fopen(r, "rb")) == NULL){
        printf("No se pudo abrir el archivo '%s'\n", r);
        return NULL;
    }
    
    if(fread(n, sizeof(size_t), 1, f) != 1){
        printf("No se pudo leer el archivo '%s'\n", r);
        return NULL;
    }
        
    //pido memoria para el arreglo
    float *arreglo = malloc(*n*sizeof(float));
    if(arreglo == NULL) {
        fclose(f);
        return NULL;
    }

    if(fread(arreglo, sizeof(float), *n, f) != *n*sizeof(float)) {
        printf("No se pudo leer el arreglo de flotantes\n");
        return NULL;
    }
       
    fclose(f);

    return arreglo;
}

/*
3.  Dado el formato (y las funciones) del ejercicio 2 escribir un programa que
    se ejecute

        $ ./escalar entrada salida valor

    que cargue en memoria el arreglo contenido en el archivo **binario**
    `entrada`, multiplique cada uno de sus elementos por el escalar `valor` y
    lo guarde en el archivo **binario** `salida`.*/

int main(int argc, char* argv[]){

    if(argc != 4){
        printf("Mal ingresado. Compilar con: <archivo> <entrada> <salida> <valor>.\n            Se tiene que ejecutar el programa seguido del nombre del archivo binario de entrada, el archivo binario de salida y un escalar.\nEl escalar va a multiplicar cada uno de los elementos de la entrada para luego ser guardados en el archivo de salida\n");
        return EXIT_FAILURE;
    }

    int valor = atoi(argv[3]);

    size_t n = 0;
    float *arreglo = leer_arreglo(argv[1],&n);

    for (size_t i = 0; i < n ; i++)
        arreglo[i] *= valor;

    printf("%s se escribio correctamente el archivo\n", escribir_arreglo(argv[2], arreglo, n) ? "": "no");
    
    return 0;
}