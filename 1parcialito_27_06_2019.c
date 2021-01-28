//PRIMER PARCIALITO 27/06/2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STR 256
#define N 3
#define M 2

int contar_mayusculas(const char cadena[]);
bool es_nonegativa(float matriz[N][M]);
void imprimir_matriz(float matriz[N][M]);

int main(void){

    /* 1.
        a.  Escribir una función

        int contar_mayusculas(const char cadena[]);

        que reciba una cadena de caracteres `cadena` y que cuente la cantidad de
        mayúsculas que contiene. (**Nota:** puede utilizarse la función booleana
        `int isupper(int c);` de la biblioteca `<ctype.h>` que indica si el
        carácter `c` es o no mayúscula.)

        b.  Con un pequeño código de ejemplo mostrar cómo utilizar a la función
        para mostrar cuántas mayúsculas tiene la cadena
        `"Algoritmos y Programación I"`.

    */
    char cadena[] = "Algoritmos y Programación I";
    int cantidad = contar_mayusculas(cadena);
    printf("Cantidad de mayusculas en %s  es %d\n", cadena, cantidad);

     /* 2.  Una matriz es no-negativa si todos sus elementos son mayores o iguales a
        cero.

        a.  Escribir una función `es_nonegativa` que reciba una matriz de flotantes
        de tamaño `N`$\times$`M` y que retorne si es no-negativa o no.

        b.  Teniendo `#define N 3` y `#define M 2` escribir un pequeño ejemplo de
        código que declare y defina una matriz, llame a la función del punto
        anterior e imprima un mensaje para el usuario según el resultado.
    */

    float matriz[N][M] = {{1,2},{3,4},{5,6}};

    printf("La matriz es %s negativa\n", es_nonegativa(matriz) ? "" : "no");

    /*  3.  Escribir un programa que le pida al usuario que ingrese dos números y que
    le indique cuál de los dos es mayor.*/
    char aux[MAX_STR];
    printf("Ingrese un numero: ");
	fgets(aux, MAX_STR, stdin);
    float n = atof(aux);
    printf("Ingrese otro numero: ");
    fgets(aux, MAX_STR, stdin);
	float n2 = atof(aux);

	if(n < 0 || n2 < 0) {
		fprintf(stderr, "Numero invalido\n");
		return 1;
	}

	if(n > n2){
        printf("%f es mayor que %f\n", n, n2);
    }else if(n == n2){
        printf("%f es igual que %f\n", n, n2);
    }else 
        printf("%f es menor que %f\n", n, n2);

    return 0;
}


int contar_mayusculas(const char cadena[]){
    int resultado = 0;
    for (size_t i = 0; cadena[i]; i++)
    {
        if(isupper(cadena[i]) != 0)
        {
            resultado ++;
        }
    }
    return resultado;
}

bool es_nonegativa(float matriz[N][M]){
    for(size_t i = 0; i < N ; i++)
    {
        for(size_t j = 0; j < M; i++)
        {
            if(matriz[i][j] < 0)
            {
                return false;
            }
        }
    }
    return true;
}

void imprimir_matriz(float matriz[N][M]){
    for(size_t i = 0; i < N ;i++)
    {
        for(size_t j = 0; j < M; i++)
        {
            printf("%f\t", matriz[i][j]);
        }
        printf("\n");
    }
}

