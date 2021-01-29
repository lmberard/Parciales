//3ER PARCIALITO  07/04/2019
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CADENA 200
#define MAX_NUMEROS 20
#define MAX_STR 200
#define MAX 30
#define CANT_ELEM 1

/*
1.  Se quiere modelar el TDA polinomio, el cual representa a un polinomio de
grado $n$ dado por la ecuación $a_0 + a_1\,x + a_2\,x^2 + \ldots + a_n\,x^n$.
Se pide:

    a.  Declarar la estructura que encapsula el TDA. Explicar qué representa
    cada miembro y documentar el invariante de representación.

    b.  Implementar la primitiva `size_t polinomio_grado(const polinomio_t *p)`
    que devuelva el grado del polinomio.

    c.  Implementar la primitiva
    `polinomio_t *polinomio_derivar(const polinomio_t *p);` que dado un
    polinomio $p(x)$ retorne el polinomio $p(x)^\prime$, su derivada. Puede
    asumir que se encuentra implementada la función
    `static polinomio_t *_polinomio_crear(size_t n);` que crea un polinomio de
    grado $n$.

*/

//a)Declarar la estructura que encapsula el TDA. explicar que representa cada uno de los miembros
typedef struct {
	float *coeficientes; //vector con todos los ao, a1, a2, ..., an
	size_t n; //n es la cant de coeficientes (el grado)
}polinomio_t;

size_t polinomio_grado(const polinomio_t *p){
    return p->n;
}

//extra
polinomio_t *polinomio_crear(size_t n){//revisar
    
    polinomio_t *polinomio = malloc(sizeof(polinomio_t));
    if(polinomio == NULL)
        return NULL;
    
    polinomio->coeficientes = malloc(n*sizeof(float));
    if(polinomio->coeficientes == NULL)
        return NULL;
    
    return polinomio;
}

polinomio_t *polinomio_derivar(const polinomio_t *p){
	
	polinomio_t *p_derivado;

	p_derivado = polinomio_crear(p->n);
	//tengo que verificar que me cree bien el polinomio
	if(p_derivado == NULL){
        printf("Falla al crear memoria para el polinomio derivado");
		return NULL;
	}

	if(p->n == 1){
		p_derivado->coeficientes = NULL;
		return p_derivado;
	}

	if(p->n > 1){
		for (int i = 0; i < (p->n); i++){
		p_derivado->coeficientes[i] = (p->coeficientes[i])*(i);
		}
	}
	
	return p_derivado;
}

//extra
double polinomio_evaluar(const polinomio_t *p, double x){
	
	float aux = 0;
	
	for (size_t i = 0; i < p->n; i++){
		aux = aux + p->coeficientes[i] *pow(x,i);
	
	}
	return aux;
}

//////////////////////////-------------PUNTO DOS-------------------/////////////////////////////////////
/*2.  Se tiene una estructura que representa a una persona como
    `typedef struct {char nombre[MAX]; unsigned int dni; float altura;} persona_t;`
    se pide:

    a.  Escribir una función `bool leer_persona(FILE *f, persona_t *p);` que
    lea una persona del archivo **binario** `f` y la guarde en la estructura
    `p`. La función debe devoler `false` de no poder realizar la operación.

    b.  Escribir una función
    `void escribir_persona(FILE *f, const persona_t *p);` que dado un archivo
    de **texto** `f` escriba en él a la persona `p` en formato CSV
    "`nombre;dni;altura`".

    c.  Escribir una función
    `bool leer_personas(const char *r, persona_t v[], size_t max, size_t *n);`
    que reciba una ruta a un archivo **binario** `r` y un vector `v` de `max`
    elementos y cargue en él todas las estructuras contenidas en el archivo
    hasta el máximo. La función debe retornar por `n` la cantidad de
    estructuras leidas y `false` en caso de falla.
*/
//a)escribir una funcion que lea una persona del archivo binario f y a guarde en la estructura p


typedef struct {
	char nombre[MAX];
	unsigned int dni;
	float altura;
}persona_t;


bool leer_persona(FILE *f, persona_t *p){
	
	//siempre tengo que abrir primero el archivo, rb porque estoy con binario y quiero leerlo nada mas
	if(!(f = fopen("archivo.bin", "rb")))
		return false;

	//fread me devuelve un size_t de la cant de elementos que leyo
	if(fread(p, sizeof(persona_t), CANT_ELEM, f) == sizeof(persona_t)*CANT_ELEM){
		fclose(f);
		return true;
	}
	fclose(f);
	return false;
}

void escribir_persona(FILE *f, const persona_t *p){

	f = fopen("archivo.txt", "w");
	if(f == NULL){
		fprintf(stderr, "Error al abrir el archivo\n");
	}
	//lo escribo con fprintf porque me lo pide en un formato especifico
	fprintf(f, "%s;%u;%f", p->nombre, p->dni, p->altura);

	if(fclose(f) == EOF)
		fprintf(stderr, "No se pudo cerrar el archivo\n");
}


//////////////////-----------PUNTO 3----------------/////////////////////

/*3.  Escribir un programa que se ejecute "`$ ./convertir entrada`" donde
    `entrada` es el nombre de un archivo **binario** de personas que imprima
    por `stdout` cada una de las personas del archivo en formato CSV. Si el
    programa se ejecutara "`$ ./convertir --help`" se debe imprimir una pequeña
    ayuda y terminar.

    Se deben utilizar las funciones desarrolladas en el punto 2.
	*/


int main(int argc, char *argv[]){
	FILE *f;
	persona_t *persona = NULL;

	if(argc == 1)
		fprintf(stderr, "Falta ingresar el nombre del archivo\n");

	char ayuda[] = "--help";

	if(strcmp(argv[1],ayuda) == 0){
		fprintf(stdout, 
			"Compilar el programa seguido del nombre del archivo binario\n./convertir nombre_archivo\n El archivo debe contener las estructuras de las personas para luego poder imprimirlas en formato CSV por stdout");
		return 0;
	}
	
	f = fopen(argv[1], "rb");
	if(f == NULL){
        fprintf(stderr, "No se pude abrir el archivo. Intentar de nuevo\n");
        return 0;
    }

	while(feof(f) != 0){
		if(fread(persona, sizeof(persona_t), CANT_ELEM, f) != sizeof(persona_t)*CANT_ELEM)
			fprintf(stderr, "No se leyo bien el archivo\n"); //return EXIT_FAILURE
		
		fprintf(stdout,"%s;%u;%f\n",persona->nombre, persona->dni, persona->altura);
	}

	return 0;
}

