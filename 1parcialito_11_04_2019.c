#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_STR 256
#define N 3

/* PRIMER PARCIALITO - 11/04/2019
1.
    a.  Escribir una función
            void reemplazar_caracter(char destino[], const char origen[], char viejo, char nuevo);

    que almacene en `destino` el resultado de intercambiar todas las apariciones del carácter `viejo` por el carácter `nuevo` en la cadena `origen`.

    b.  Con un pequeño código de ejemplo mostrar cómo utilizar a la función para cambiar las `'o'` por `'e'` en la cadena `"Los alumnos"`.

2.  Una matriz cuadrada es triangular superior si todos los elementos debajo de su diagonal principal son iguales a cero.

    a.  Escribir una función `es_triangular_superior` que reciba una matriz de flotantes de tamaño `N`$\times$`N` y que retorne si es triangular superior o no.
    b.  Teniendo `#define N 3` escribir un pequeño ejemplo de código que declare y defina una matriz, llame a la función del punto anterior e imprima un mensaje para el usuario según el resultado.


3.  Escribir un programa que le pida un número al usuario y que, de ser posible, le muestre su raíz cuadrada. (**Nota:** para calcular una raíz cuadrada puede utilizarse la función `double sqrt(double x);` de la biblioteca `<math.h>`.)
*/

void reemplazar_caracter(char *destino, const char *origen, char viejo, char nuevo);
bool es_triangular_superior(float matriz[N][N]);


int main(void) {
	//1
	char destino[MAX_STR];
	reemplazar_caracter(destino, "Los alumnos", 'o', 'e');
	printf("%s\n", destino);

	
	// 2.b
	float matriz[][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	bool es_triangular = es_triangular_superior(matriz);
	printf("La matriz %ses triangular superior\n", es_triangular ? "" : "no ");


	// 3
	char aux[MAX_STR];
	printf("Ingrese un numero positivo: ");
	fgets(aux, MAX_STR, stdin);

	float n = atof(aux);

	if(n < 0) {
		fprintf(stderr, "Numero invalido\n");
		return 1;
	}
	double raiz = sqrt(n);
	printf("La raiz de %f es %f\n", n, raiz);


	return 0;
}


// 1.a
/*
void reemplazar_caracter(char *destino, const char *origen, char viejo, char nuevo) {
	size_t i;
	for(i = 0; origen[i]; i++) {
		if(origen[i] == viejo)
			destino[i] = nuevo;
		else
			destino[i] = origen[i];
	}
	destino[i] = '\0';
}
*/

// 1.a
void reemplazar_caracter(char *destino, const char *origen, char viejo, char nuevo) {
	for(size_t i = 0; (destino[i] = origen[i]); i++)
		if(destino[i] == viejo)
			destino[i] = nuevo;
}


///////////////////////////////////////////////
// 2.a
bool es_triangular_superior(float matriz[][N]) {
	for(size_t i = 0; i < N; i++)
		for(size_t j = 0; j < N; j++)
			if(i > j && matriz[i][j] != 0)
				return false;

	return true;
}

// 2.a
/*
bool es_triangular_superior(float matriz[][N]) {
	for(size_t i = 1; i < N; i++)
		for(size_t j = 0; j < i; j++)
			if(matriz[i][j])
				return false;
	return true;
}
*/