#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

/*
  Ejercicio 3. El problema del papá tacaño.

  Entrada sugerida:
    n
    t1 t2 ... tn

  Donde cada token ti es:
    - un entero positivo (costo conocido), o
    - una letra MAYÚSCULA (costo desconocido, p. ej. X, Y, Z)

  Restricciones:
    1) n >= 3
    2) Los costos conocidos son enteros positivos
    3) Hay al menos 1 costo desconocido y al menos 1 costo conocido
    4) Todo desconocido es mayor que cualquier conocido
    5) Si la mayoría son desconocidos, elegir uno al azar
*/

/* Representación de cada destino */
typedef struct {
    int es_conocido;   // 1 si el costo es conocido, 0 si es desconocido
    int costo;         // válido solo si es_conocido == 1
    char etiqueta;     // válido solo si es_conocido == 0 (p. ej., 'X', 'Y')
} Destino;

/* Imprime el arreglo de destinos tal como se interpretó */
void imprimir_destinos(const Destino *destinos, int n) {
    printf("Destinos interpretados: [ ");
    for (int i = 0; i < n; i++) {
        if (destinos[i].es_conocido) {
            printf("%d", destinos[i].costo);
        } else {
            printf("%c", destinos[i].etiqueta);
        }
        if (i < n - 1) printf(", ");
    }
    printf(" ]\n");
}

/* Utilidad: parsea un token; retorna 1 si es válido, 0 si no. */
int parsear_token(const char *tok, Destino *d) {
    // Si empieza con dígito, lo tratamos como costo conocido
    if (isdigit((unsigned char)tok[0])) {
        // Validar que sea entero positivo
        for (int i = 0; tok[i]; i++) {
            if (!isdigit((unsigned char)tok[i])) return 0;
        }
        long val = strtol(tok, NULL, 10);
        if (val <= 0) return 0;
        d->es_conocido = 1;
        d->costo = (int)val;
        d->etiqueta = '\0';
        return 1;
    }
    // Si es una letra MAYÚSCULA (una sola), lo tratamos como desconocido
    if (strlen(tok) == 1 && tok[0] >= 'A' && tok[0] <= 'Z') {
        d->es_conocido = 0;
        d->costo = 0;
        d->etiqueta = tok[0];
        return 1;
    }
    return 0;
}

/*
 * FUNCIÓN A IMPLEMENTAR
 *
 * Objetivo general:
 *   Seleccionar el índice del destino cuya "propuesta de costo" sea la
 *   más cercana a la "media" considerada en el total (ver reglas).
 *
 * Reglas a incorporar en tu solución:
 *   (1) Siempre hay >= 3 destinos.
 *   (2) Costos conocidos: enteros positivos.
 *   (3) Hay al menos un conocido y al menos un desconocido.
 *   (4) Todo desconocido es MAYOR que cualquier conocido.
 *   (5) Si la mayoría son desconocidos, elegir uno al azar.
 *
 * Comentarios-guía (NO OBLIGATORIOS, solo orientación):
 *   - Paso 1: contar cuántos conocidos y desconocidos hay.
 *   - Paso 2 (Regla 5): si desconocidos > conocidos, elige uno al azar
 *            entre los desconocidos y retorna su índice.
 *   - Paso 3: define tu estrategia para la "media". Por ejemplo:
 *       * usar la media de los costos conocidos,
 *       * y tratar los desconocidos como "mayores que todo conocido"
 *         (puedes usar una cota, p. ej., maxConocido + 1, o un valor simbólico).
 *     Justifica en tu reporte/README cómo aproximas la media bajo la Regla 4.
 *   - Paso 4: encuentra el índice cuyo "costo (o valor representativo)"
 *             esté más cercano a la media. En caso de empate, define
 *             una política simple, p. ej., el de menor índice.
 */
int elegir_destino(Destino *destinos, int n) {
    // Escribe aquí tu función

    // Sugerencias de variables que podrías usar:
    // int conocidos = 0, desconocidos = 0;
    // int indice_elegido = -1;
    // int max_conocido = ...; // para apoyar la Regla 4 si asignas un valor simbólico
    // double media = 0.0;

    // 1) Contar conocidos vs desconocidos

    int conocidos = 0, desconocidos = 0; //Contadores de conocidos y desconocidos
    
    for(int i = 0; i<n; i++){ //Contamos los conocidos y los desconocidos
        if(destinos[i].es_conocido == 1){
            conocidos++;
        }
        else desconocidos++;
    }

    // 2) Si desconocidos > conocidos:
    //      - Elegir aleatoriamente entre índices con es_conocido == 0
    //      - return indice_aleatorio;

    //Regla 5. Cuando hay más desconocidos que conocidos, se elige un desconocido al azar
    if(desconocidos > conocidos){
        int random = rand() % desconocidos; //Número aleatorio entre 0 y desconocidos-1 
        for(int i = 0; i<n; i++){ //Recorremos el arreglo buscando el desconocido en la posición random
            if(destinos[i].es_conocido == 0){ //Si el elemento encontrado es desconocido, usamos ese índice. De lo contrario, buscamos el siguiente elemento, hasta encontrar un desconocido
                if(random == 0){
                    return i;
                }
                random--;
            }
        }
    }


    // 3) Calcular "media" según tu diseño
    //      - p. ej., media de costos conocidos
    //      - asignar valor representativo a desconocidos respetando Regla 4

    int suma = 0; //Suma de los costos conocidos (inicializada en 0)
    int max_conocido = 0; //Máximo costo conocido (inicializado en 0)
    for(int i = 0; i<n; i++){ //Recorremos el arreglo para calcular la suma de los costos conocidos y el máximo costo conocido
        if(destinos[i].es_conocido == 1){ //Si se cumple, el elemento es conocido
            suma += destinos[i].costo; //Como es conocido, sumamos su costo a la suma total
            if(destinos[i].costo > max_conocido){ //Si el costo del elemento es mayor que el máximo conocido, actualizamos el máximo conocido
                max_conocido = destinos[i].costo;
            }
        }
    }
    double media = (double)suma / conocidos; //Obtenemos el promedio de los costos conocidos
    //Asignamos a los desconocidos un valor representativo mayor que cualquier conocido
    double valor_representativo = max_conocido + 1; //max_conocido + 1 es un valor mayor que cualquier conocido

    for(int i = 0; i<n; i++){ //Recorremos el arreglo para asignar el valor representativo a los desconocidos
        if(destinos[i].es_conocido == 0){ //Si el elemento es desconocido, le asignamos el valor representativo
            destinos[i].costo = valor_representativo; //Asignamos el valor representativo al costo del destino desconocido
        }
    }
    /*Nota:
        -- Para poder asignar el valor representativo a los desconocidos, tuvimos que quitar el const del arreglo de destinos en los parámetros, de lo contrario, no podría modificarse.
    */



    // 4) Hallar el índice con distancia mínima a la media
    //      - manejar empates de forma determinista (p. ej., menor índice)

    int indice_elegido = -1; // índice del destino elegido (inicializado en -1)
    double min_distancia = 1e9; // un valor grande inicial (para que cualquier valor sea menor que este)
    
    for(int i = 0; i<n; i++){ //Recorremos el arreglo para encontrar el índice con la distancia mínima a la media
        double distancia = abs(destinos[i].costo - media); //Calculamos la distancia entre el costo del destino y la media. El valor absoluto es para evitar distancias negativas, en caso de que el valor sea menor a la media
        if(distancia < min_distancia){ //Si la distancia es menor que la distancia mínima, actualizamos la distancia mínima y el índice elegido
            min_distancia = distancia;
            indice_elegido = i; // actualizar índice elegido
        }
        //En caso de que haya dos números con la misma distancia, se elige el de menor índice. Esto por la condición (distancia < min_distancia), ya que si la distancia es igual, no se actualiza el índice elegido
    }
    return indice_elegido; //Retornamos el índice elegido
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 3) {
        fprintf(stderr, "Error: n inválido (debe ser >= 3).\n");
        return 1;
    }

    Destino *destinos = (Destino *)malloc(n * sizeof(Destino));
    if (!destinos) {
        fprintf(stderr, "Error: memoria insuficiente.\n");
        return 1;
    }

    // Semilla para la Regla 5 (elección aleatoria cuando la mayoría es desconocida)
    srand((unsigned int)time(NULL));

    // Leer n tokens
    for (int i = 0; i < n; i++) {
        char tok[64];
        if (scanf("%63s", tok) != 1) {
            fprintf(stderr, "Error: no se pudo leer el token %d.\n", i + 1);
            free(destinos);
            return 1;
        }
        if (!parsear_token(tok, &destinos[i])) {
            fprintf(stderr, "Error: token inválido en la posición %d: '%s'.\n", i + 1, tok);
            free(destinos);
            return 1;
        }
    }

    // Verificación mínima de las restricciones 3 y 4
    int hay_conocido = 0, hay_desconocido = 0;
    for (int i = 0; i < n; i++) {
        if (destinos[i].es_conocido) hay_conocido = 1; else hay_desconocido = 1;
    }
    if (!hay_conocido || !hay_desconocido) {
        fprintf(stderr, "Error: debe haber al menos un costo conocido y al menos uno desconocido.\n");
        free(destinos);
        return 1;
    }

    // (Opcional) Mostrar cómo se interpretó la entrada
    imprimir_destinos(destinos, n);

    // Llamar a la función a implementar
    int indice = elegir_destino(destinos, n);
    if (indice < 0 || indice >= n) {
        fprintf(stderr, "Advertencia: índice no válido devuelto por elegir_destino.\n");
        free(destinos);
        return 1;
    }

    // Salida: imprime el destino elegido tal cual fue ingresado
    printf("Destino elegido (índice %d): ", indice);
    if (destinos[indice].es_conocido) {
        printf("%d\n", destinos[indice].costo);
    } else {
        printf("%c\n", destinos[indice].etiqueta);
    }

    free(destinos);
    return 0;
}

/*
Ejemplos de uso (solo referencia; la elección final depende de tu implementación):

Ejemplo 1:
Entrada
6
241 42 362 X 79 Y

Salida (posible)
Destinos interpretados: [ 241, 42, 362, X, 79, Y ]
Destino elegido (índice k): <valor o etiqueta>

Ejemplo 2:
Entrada
5
A 10 20 B 30

Salida (posible)
Destinos interpretados: [ A, 10, 20, B, 30 ]
Destino elegido (índice k): <valor o etiqueta>
*/
