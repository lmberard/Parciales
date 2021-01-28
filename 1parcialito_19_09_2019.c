//PRIMER PARCIALITO 19/09/2019
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAX_STR 256
#define N 3
#define M 2

void left_trim(char cadena[]);
float sumar_positivos(float matriz[N][M]);

int main(void){
    /*1.
    a.  Escribir una función

            void left_trim(char cadena[]);

    que elimine todos los caracteres de espacio que haya al comienzo de la
    `cadena`. Por ejemplo, si se le pasara la cadena `"   hola mundo "` después
    de ejecutar la función la misma deberá ser `"hola mundo "`.

    b.  Con un pequeño código de ejemplo mostrar cómo utilizar a la función
    con las cadenas del ejemplo anterior.
*/
    char cadena[] = "   hola mundo ";
    printf("Cadena original:%s\n", cadena);
    left_trim(cadena);
    printf("Cadena left_trim:%s\n", cadena);

/*2.
    a.  Escribir una función `sumar_positivos` que reciba una matriz de
    flotantes de tamaño `N`$\times$`M` y que retorne la suma de los elementos
    de la matriz que sean positivos.

    b.  Teniendo `#define N 3` y `#define M 2` escribir un pequeño ejemplo de
    código que declare y defina una matriz, llame a la función del punto
    anterior e imprima un mensaje para el usuario con el resultado.
*/
    float matriz[N][M] = {{-1,-2},{-3,4},{-5,6}};
    float suma = sumar_positivos(matriz);
    printf("La suma de los positivos de la matriz es: %f\n", suma);


/*3.  Escribir un programa que cuente la cantidad de caracteres blancos
    ingresados por `stdin`. Al detectar que no hay más datos a ser leídos se
    deberá imprimir la cantidad. (**Nota:** para determinar si un carácter es
    blanco puede utilizarse la función `int isspace(int);` de la biblioteca
    `<ctype.h>`.)*/
    printf("Ingresar palabras y caracteres blancos:\n");
    
    char aux[MAX_STR];
    fgets(aux, MAX_STR, stdin);
    int cant = 0;
    
    for (size_t i = 0; aux[i]; i++)
    {
        if (isspace(aux[i]) != 0)
        {
            cant ++;
        }
    }
    cant--; //para no tener en cuenta el enter del final (porque es un caracter blanco ingresado)
    printf("La cantidad de espacios blancos es %d\n", cant);
    

    return 0;
}

void left_trim(char cadena[]){
    size_t i, j;
    for (i = 0; cadena[i]; i++)
    {
        if(cadena[i] != ' '){break;}
    }
    printf("i es igual a %zd\n", i);
    for (j = 0; cadena[i]; j++)
    {
        cadena[j] = cadena[i];
        i++; 
        if(cadena[i] == '\0')
        {
            printf("fin");
            cadena[j] = '\0';
            break;
        }   
    }
    printf("la nueva i es igual a %zd\n", i);
    /*memcpy(cadena,aux,strlen(aux));*/
}

float sumar_positivos(float matriz[N][M]){
    float suma = 0;
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            if (matriz[i][j] >= 0)
            {
                suma += matriz[i][j];
            }
        }
    }
    return suma;
}


