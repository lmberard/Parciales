//SEGUNDO PARCIALITO 13/05/2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CADENA 200

/*
1.  Se quiere almacenar los datos de alumnos. Un alumno tiene un "nombre" que es un texto de no más de `MAX_CADENA` elementos, un "padrón",
 que es un entero sin signo y un "promedio general", que es un número real.

    a.  Declarar una estructura `struct alumno` que modele al alumno descripto.
    b.  Definir el tipo `alumno_t` en base a la estructura anterior.
    c.  Escribir una función `bool alumno_son_iguales(const alumno_t *a, const alumno_t *b);` que dados dos alumos `a` y `b`
     diga si son iguales. Un alumno es igual a otro si coinciden todos sus campos.
*/
typedef struct {
    char nombre[MAX_CADENA];
    int padron;
    float promedio;
}alumno_t;


bool alumno_son_iguales(const alumno_t *a,const alumno_t *b){
	return a->promedio == b->promedio && a->padron == b->padron && strcmp(a->nombre,b->nombre) == 0;
}

/*
2.  Teniendo definida una estructura `vector_t` la cual contiene un `float *v` y un `size_t n` y 
que modela a un vector dinámico `v` de `n` elementos se pide:

    a.  Escribir una función `vector_t *vector_crear(const float vals[], size_t n);` que genere un `vector_t` de longitud `n`
     inicializado con los valores del vector `vals`.

    b.  Escribir una función `void vector_destruir(vector_t *v);` que libere la memoria asociada a un `vector_t` dinámico.
*/
typedef struct {
    float *v;
    size_t n;
}vector_t;

//2
void vector_destruir(vector_t *v){
	free(v->v);
	free(v);
}

vector_t *vector_crear(const float vals[], size_t nv){
	//pido mem para la estructur y verifico
    vector_t *v = malloc(sizeof(vector_t));
	if(v == NULL) return NULL;
	
    //pido mem para el vector y verifico
    v->v = malloc(nv*sizeof(float));
	if(v->v == NULL)
    {
		free(v);
		return NULL;
	}

    //inicializo el vector con los valores
	for( size_t i = 0 ; i < nv ; i++) //memcpy(v->v,vals,sizeof(float)*nv); reemplaza las dos l�neas
		v->v[i] = vals[i]; // *((*v).v+i)= *(vals+i) //memcpy(v->v,vals,sizeof(float)*nv);

	v->n = nv;

	return v;
}
/*
3.  Escribir una función `bool leer_enteros(int **pv, size_t *n);` que lea valores enteros de `stdin` y los almacene en un
 vector dinámico de enteros. Los parámetros `pv` y `n` son sólamente de salida y la función debe retornar a través de ellos 
 el vector dinámico y su longitud. A su vez debe retornar por el nombre `true` si todo está bien o `false` en caso de error.
*/

bool leer_enteros(int **pv, size_t *pn){ // ejercicio de reallocs
	//usa la estrategia 1 / 0  / n
	*pv = NULL;
	*pn = 0;
	char aux[MAX_CADENA];
	while(fgets(aux,MAX_CADENA,stdin) != NULL){ //el NULL seria el End of file que es al insertar ctrl D
        // llegue aca, tengo una cadena y la tengo que guardar
		int *v = realloc(*pv,(*pn+1)*sizeof(int)); // idea de la semejanza malloc realloc con el NULL ..
		
		if(v == NULL){
			free(*pv);
			return false; // se podria mejorar
		}
		*pv = v;
		(*pv)[(*pn)++] = atoi(aux);
	}
	return true;
}


int main(void){

    //1
    alumno_t pepito, pepito2;
    strcpy(pepito.nombre, "Juan");
    strcpy(pepito2.nombre, "Juan");
    pepito.padron = 101213;
    pepito2.padron = 101213;
    pepito.promedio = 7;
    pepito2.promedio = 7;

    printf("Los alumnos %sson iguales\n", alumno_son_iguales(&pepito, &pepito2) ? "" : "no ");

    //2
    float valores[] = {1,2,4};
    size_t tam = 3;
    vector_t *vector = vector_crear(valores, tam);
    
    vector_destruir(vector);

    //3
    size_t n;
    int *v;
    if(!leer_enteros(&v,&n)){
        printf("No se guardaron bien los datos en un vector dinamico\n");
    }
    printf("Se guardaron los datos en el vector dinamico\n");
    free(v);
    

    return 0;

}

//otra opcion
/*
bool leer_enteros2(int **pv, size_t *pn){ 
	
	size_t *v = NULL;
	size_t n = 0;
	
	char aux[MAX_CADENA];
	while(fgets(aux,MAX_CADENA,stdin) != NULL){
		// llegue aca, tengo una cadena y la tengo que guardar
		int *_v = realloc(v,(n+1)*sizeof(int)); // idea de la semejanza malloc realloc con el NULL ..
		if(_v == NULL){
			free(v);
			return false; // se podria mejorar
		}
		v = _v;
		v[n++] = atoi(aux);
	}
	*pv = v;
	*pn = n;
	return true;
}*/

/*
aux, idea func realloc
void *realloc(void *p,size_t n){
	void *n=malloc(n);
	if(n==NULL)
		return NULL;
	memcpy(n,p,...);
	free(p);
	return n;
}
*/

