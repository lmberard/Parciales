//SEGUNDO PARCIALITO 04/07/2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CADENA 200
#define MAX_NUMEROS 20
#define MAX_STR 200

/*
1.  Una persona se representa según un *nombre* que es una cadena de no más de
    `MAX_CADENA` elementos, un *DNI* que es un entero sin signo, un *año de
    nacimiento* que es un entero corto sin signo y un *padre* y una *madre* que
    son dos referencias a personas.

    a.  Declarar una estructura `struct persona` que modele a la persona
    descripta.

    b.  Definir el tipo `persona_t` en base a la estructura anterior.

    c.  Escribir una función
    `bool tiene_padres_mayores(const persona_t *p, short edad);`
    que indique si alguno de los padres era mayor de `edad` años al momento de
    nacer la persona `p`. Si no hubiera referencia se asumirá que no era mayor
    a dicha edad.

*/
typedef struct persona{
    char nombre[MAX_CADENA];
    unsigned int dni;
    unsigned int year_nacimiento;
    struct persona *madre;
    struct persona *padre;
}persona_t;

bool tiene_padres_mayores(const persona_t *p, short edad){
    unsigned int year_actual = 2021;

    return p->madre == NULL ||p->padre == NULL || (year_actual - p->madre->year_nacimiento)<= 18 || (year_actual - p->padre->year_nacimiento)<= 18;
}

/*
2.
    a.  Implementar una función
            char **clonar_arreglo_cadenas(char *ss[]);

    que reciba un arreglo de cadenas de caracteres `ss` el cual contiene
    cadenas en sus primeras posiciones y el centinela `NULL` en su última
    posición y que devuelva una copia en memoria nueva de dicho arreglo.

    b.  Implementar una función
            void destruir_arreglo_cadenas(char *ss[]);

    que reciba un arreglo dinámico de cadenas dinámicas como el del ítem
    anterior y libere la memoria asociada a él.
*/

 void destruir_arreglo_cadenas(char *ss[]){
    for (size_t i = 0; ss[i]!= NULL; i++)
         free(ss[i]);
    free(ss);     
 }

 char **clonar_arreglo_cadenas(char *ss[]){
    //verifico si lo que me pasan apunta a algo
    if(ss == NULL) return NULL;
    
    //calculo cuantas cadenas tiene
    size_t cantidad_cadenas = 0;
    for (size_t i = 0; ss[i] != NULL; i++){}
    cantidad_cadenas = i+1; //le sumo uno para que en la copia tb finalice con null

    
    //pido para el arreglo de cadenas y verifico
    char **copia_arreglo = malloc(cantidad_cadenas*sizeof(char*));
    if(copia_arreglo == NULL)
        return NULL;
    
    //pido para cada cadena y voy copiando 
    for (i = 0; i < cantidad_cadenas; i++)
    {   
        //memoria para cada cadena y verifico
        copia_arreglo[i] = malloc(strlen(ss[i])); //*sizeof(char) pero es 1 asiq al pepe
        if (copia_arreglo[i] == NULL){
            destruir_arreglo_cadenas(copia_arreglo);  //me borra hasta que encuentra el NULL asiq ta bien    
            return NULL;
        }
        //se creo bien la memoria asique copio lo que habia
        strcpy(copia_arreglo[i], ss[i]);
    }
    copia_arreglo[cantidad_cadenas] = NULL; //para que finalice en null como el orishinal
    return copia_arreglo;
 }

/*
3.  Escribir una función `bool leer_flotantes(float **pv, size_t *n);` que lea
    valores flotantes de `stdin` y los almacene en un vector dinámico de
    flotantes. Los parámetros `pv` y `n` son sólamente de salida y la función
    debe retornar a través de ellos el vector dinámico y su longitud. A su vez
    debe retornar por el nombre `true` si todo está bien o `false` en caso de
    error.
*/

bool leer_flotantes(float **pv, size_t *n){
    //armo vector y nauxiliar para guardar la data 
	float *vector_aux = NULL;
	size_t n_aux = 0;
	char aux[MAX_CADENA]; //para guardar lo de stdin
    
	while(fgets(aux,MAX_CADENA,stdin) != NULL){
		//cada vez que entra al while tengo que reallocar pero puede que falle asique lo voy guardando en un vector extra
		float *vector_auxaux = realloc(vector_aux,(n_aux + 1)*sizeof(float)); 
		if(vector_auxaux == NULL){
			free(vector_aux);
			return false; 
		}
    //como no fallo, lo guardo en el aux normal y aumento la posicion 
		vector_aux = vector_auxaux;
        n_aux++;
		vector_aux[n_aux] = atof(aux);
	}
    
	*pv = vector_aux;
	*n = n_aux;
	return true;
}


int main(void){
    return 0;
}