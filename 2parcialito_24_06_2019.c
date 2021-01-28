//SEGUNDO PARCIALITO 24/06/2019

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

1.  Implementar la función `char *join(char *strs[], size_t n, char delim);`
    que reciba en `strs` un arreglo de `n` cadenas de caracteres y devuelva una
    cadena que contenga la concatenación de todas ellas usando el carácter
    `delim` como delimitador.

    Por ejemplo, si se llama a `join({"hola", "que", "tal"}, 3, ' ')` debe
    devolverse `"hola que tal"`.
*/
   //había que devolver una cadena, de largo indefinido => memoria dinámica. Podía saberse la cantidad de memoria contándola primero => se resuelve más fácil sin realloc().
   //Sobre el uso de strcat(), strcat() sirve para interactuar con cadenas, delim no es una cadena, es un caracter suelto. Y me importa NADA que &delim sea de tipo char* SIGUE sin ser una cadena.

char *join(char *strs[], size_t cant_cadenas, char delim){
    // Calculo la memoria que necesito (long del vector final):
   size_t longitud = 0;
   for(size_t i = 0; i < cant_cadenas; i++)
      longitud += strlen(strs[i]); // Sumo los largos de las cadenas.
   longitud += cant_cadenas; // Sumo los largos de los delimitadores + el '\0'.

   // Pido la memoria:
   char *cadena_entera = malloc(longitud * sizeof(char));

   // Armo la cadena y copio la primer palabnra:
   strcpy(cadena_entera, strs[0]);
   // Acá tengo que tener algo para poder meter delim al final, esto sirve:
   size_t pos = strlen(cadena_entera);

   for(size_t i = 1; i < cant_cadenas; i++) {

      cadena_entera[pos++] = delim; // Si voy a usar strcat() después necesito poner el '\0'
      strcpy(cadena_entera + pos, strs[i]); // Acá puedo hacer strcat(s, strs[i]), ¿lo malo?, convierto en cuadrático un problema lineal.
      pos += strlen(strs[i]);
   
   }

   return cadena_entera;

}

/*2.

    a.  Implementar una función `char **leer_lineas(size_t *n);` que lea líneas
        de `stdin` hasta que se termine la entrada estándar y que devuelva un
        arreglo de cadenas que contenga cada una de esas líneas. Debe
        devolverse la cantidad de líneas leídas a través de `n`.

    b.  Implementar la función `void liberar_lineas(char **lineas, size_t n);`
        que reciba un arreglo dinámico de cadenas `lineas` de longitud `n` y
        libere la memoria asociada.
*/
void liberar_lineas(char **lineas, size_t n){
    for(size_t i = 0; i < n; i++)
       free(lineas[i]);
    free(lineas);
}

char **leer_lineas(size_t *n){
    *n = 0;

   char aux[MAX_STR];
   size_t i = 0;
   char **ss = NULL;

   while(fgets(aux, MAX_STR, stdin) != NULL) {
      
      //hago un auxiliar por las dudas si me lo realoquea mal
      char **auxaux = realloc(ss, (i + 1) * sizeof(char *));
      if(auxaux == NULL) {
          liberar_lineas(ss, i);
          return NULL;
      }
      ss = auxaux;

      ss[i] = malloc((strlen(aux) + 1) * sizeof(char));
      if(ss[i] == NULL) {
          liberar_lineas(ss, i);
          return NULL;
      }

      strcpy(ss[i], aux);
      i++;
   }

   *n = i; //devuelve el valor de la cantidad de lineas leidas en esa variable n
   return ss; //devuelve arreglo de cadenas
}



/*3.  Se quiere modelar el contacto en una agenda telefónica.

    Un número de teléfono consta de una *referencia* que indica qué representa
    ese número y que es un texto de no más de `MAX_CADENA` elementos y de un
    entero largo sin signo que representa al *número*.

    Un contacto en una agenda tiene el *nombre* del contacto, una cadena de no
    más de `MAX_CADENA` elementos y de un vector de *n* (nunca más de
    `MAX_NUMEROS`) *números* telefónicos.

    a.  Declarar las estructuras `struct numero` y `struct contacto` que
        representen un número telefónico y un contacto respectivamete.

    b.  Definir los tipos `numero_t` y `contacto_t` en base a las estructuras
        anteriores.

    c.  Escribir una función

            bool numero_en_contacto(const contacto_t *c, unsigned long numero);

        que retorne si `numero` es uno de los números del contacto `c`.
*/

/*3) El ejercicio era de composición de estructuras, una estructura tenía un vector de las otras.
   Lectocomprensión, el enunciado decía claramente que había N números almacenados, y le ponía una cota a la cantidad máxima que podía haber... 
   hubo muchísima gente que no almacenó la cantidad de números almacenados en ningún lado. 
   El enunciado NO DICE que tenga que haber MAX_NUMEROS, dice que hay N y que como mucho van a ser MAX_NUMEROS.
   Sobre la evaluación del 1.c lo importante era ver cómo accedían al puntero a la estructura y al vector de estructuras, no por nada era el ejercicio de estructuras :).
*/

//a)
typedef struct numero {
   char referencia[MAX_CADENA];
   unsigned long numero;
}numero_t;

typedef struct contacto {
   char nombre[MAX_CADENA];
   numero_t numeros[MAX_NUMEROS];
   size_t cantidad_numeros;
}contacto_t;


//c)
bool numero_en_contacto(const contacto_t *c, unsigned long numero) {
   for(size_t i = 0; i < c->cantidad_numeros; i++)
      if(c->numeros[i].numero == numero)
         return true;
   return false;
}

int main(void){
   return 0;
}