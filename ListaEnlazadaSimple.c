#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM_LISTA 5
#define MIN 1111
#define MAX 9999

/**
 * Estructura de datos.
 */
typedef struct datos
{
    int valor;
} Datos;

/**
 * Estrucutra de cada nodo
 */
typedef struct nodo
{
    Datos *datos;           //Estructura de los datos.
    struct nodo *siguiente; //Enlace siguiente nodo ingresado.
} Nodo;

//Prototipo de funciones
Nodo *Crear_Nodo(Datos *);
void Apilar_Nodo(Nodo **, Nodo *);
void Desapilar_Nodo(Nodo **);
void Imprimir_Pila(Nodo *);
int Contar_Nodos(Nodo *);
void Borrar_Pila(Nodo **);
void Insertar_Nodo(Nodo **, Nodo *, int);
void Borrar_Nodo(Nodo **, int pos);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    Nodo *pila = NULL, *nuevo = (Nodo *)malloc(sizeof(Nodo));
    Datos *datos;

    for (size_t i = 0; i < TAM_LISTA; i++)
    {
        datos = (Datos *)malloc(sizeof(Datos));
        datos->valor = (int)(rand() % MAX) + MIN; //aleatorios 111->999

        nuevo = Crear_Nodo(datos);
        Apilar_Nodo(&pila, nuevo); //Agregando a la pila
    }
    printf("Pila de %d nodos cargada aleatoriamente con datos enteros entre %d y %d.\n", TAM_LISTA, MIN, MAX);
    Imprimir_Pila(pila);

    //Apilado de un nuevo nodo.
    printf("Apilado de nuevo nodo.\n");
    printf("\nNodo generado.\n");

    datos = (Datos *)malloc(sizeof(Datos)); //Nueva escructura de datos
    datos->valor = 9999999;                 //Guardado de un dato cualquiera.

    printf("  [%d] ->%x\n", nuevo->datos->valor, nuevo->siguiente);

    nuevo = Crear_Nodo(datos); //Se crea el nodo
    Apilar_Nodo(&pila, nuevo); //Se apila
    Imprimir_Pila(pila);

    //Borrar último nodo ingresado.
    printf("Desapilado. Se borra el %cltimo nodo ingresado.\n", 163);
    Desapilar_Nodo(&pila);
    Imprimir_Pila(pila);

    //Borrado de un nodo específico
    printf("Borrado de un nodo dada su posici%cn(2 en este caso).\n", 162);
    Borrar_Nodo(&pila, 2);
    Imprimir_Pila(pila);

    return 0;
}

/**
* Inserta un nodo en cualquier lugar de la pila.
* @param Nodo** pila
* @param Nodo* nodo a insertar
* @param posición donde insertar. Como la cola se recorre desde el último
* ingresado hacía el primero, Ej.-> Cola [3][2][1][0] -> ciclo: 3, 2, 1, 0. 
* Si queremos la posición 1, entonces recorremos hasta 1, serán 3 ciclos.
* Para obtener este número, 3, debemos hacer: Cantidad de elementos total - posición ingresada.
* Ej.-> 4 - 1 = 3;
*/
void Insertar_Nodo(Nodo **pila, Nodo *nodo, int pos)
{
    Nodo *pilaAux = NULL;

    pos = Contar_Nodos(*pila) - pos; //Devuelve la posición en la pila.

    for (size_t i = 0; i < pos; i++) //Recorrido hasta a posición determinada
    {
        //Copia nodo a nodo hacia una pila auxiliar en forma invertida
        Apilar_Nodo(&pilaAux, Crear_Nodo((*pila)->datos));
        *pila = (*pila)->siguiente;
    }

    Apilar_Nodo(&pilaAux, nodo); //Apila el nuevo nodo.

    //Devuelve los nodos de la pila auxiliar a la original
    while (pilaAux != NULL)
    {
        Apilar_Nodo(pila, Crear_Nodo(pilaAux->datos));
        pilaAux = pilaAux->siguiente;
    }
}

/**
 * @param Nodo** pila sobre la que borrar.
 * @param int pos, posición del nodo a borrar.
 */
void Borrar_Nodo(Nodo **pila, int pos)
{
    Nodo *pilaAux = NULL;

    pos = Contar_Nodos(*pila) - pos; //Devuelve la posición en la pila.

    for (size_t i = 0; i < pos - 1; i++)
    {
        Apilar_Nodo(&pilaAux, Crear_Nodo((*pila)->datos));
        *pila = (*pila)->siguiente;
    }

    Desapilar_Nodo(pila); //Quita el nodo del tope

    //Devuelve los nodos de la pila auxiliar a la original
    while (pilaAux != NULL)
    {
        Apilar_Nodo(pila, Crear_Nodo(pilaAux->datos));
        pilaAux = pilaAux->siguiente;
    }
}

/**
* Imprime los nodos de la pila 
* desde el tope hasta la base.
* Número de nodo.
* Dirección del nodo actual y el siguiente.
* @param Nodo* pila a imprimir
*/
void Imprimir_Pila(Nodo *pila)
{
    int i = Contar_Nodos(pila) - 1;

    if (pila != NULL)
    {
        printf("\n---------------------------------\n");
        while (pila != NULL)
        {
            printf("Nodo: %d\n", i--);
            // Imprime el contenido de los datos.
            // En este caso, sólo un valor entero.
            printf("(%10d) ", pila->datos->valor);
            printf("-> %x  ", pila); //
            printf("-> %x\n", pila->siguiente);

            pila = pila->siguiente;
        }
        printf("------------------------------------\n\n");
    }
    else
    {
        printf("Lista sin contenido.\n");
    }
}

/**
* Crea un nodo
* @param valor del nodo
* @return nodo
*/
Nodo *Crear_Nodo(Datos *datos)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->datos = datos;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

/**
* Apila un nodo.
* Agrega el nodo al tope de la lista.
* @param Nodo** pila a la que agregar
* @param Nodo* nodo a agrega/
*/
void Apilar_Nodo(Nodo **pila, Nodo *nodo)
{
    if (*pila == NULL)
    { //Si la pila está vacía, se le agrega el nuevo nodo.
        *pila = nodo;
    }
    else
    { //Si no lo está, se enlaza el nuevo nodo al existente.
        nodo->siguiente = *pila;
        *pila = nodo; //Y se agrega a la pila
    }
}

/**
* Quita el último nodo agregado.
* @param Nodo** pila de donde quitar el nodo.
*/
void Desapilar_Nodo(Nodo **pila)
{
    if (*pila != NULL)
    {
        Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
        nodo = (*pila)->siguiente;
        free(*pila);
        *pila = nodo;
    }
}

/**
* Cuenta la cantidad de nodos de una pila.
* @param Nodo* pila a contar nodos contenidos.
* @return cantidad de nodos.
*/
int Contar_Nodos(Nodo *pila)
{
    int contador = 0;
    while (pila != NULL)
    {
        contador++;
        pila = pila->siguiente;
    }
    return contador;
}

/**
* Elimina una pila, nodo por nodo
* @param Nodo** pila a eliminar
*/
void Borrar_Pila(Nodo **pila)
{
    Nodo *actual;

    while (*pila != NULL)
    {
        actual = (*pila)->siguiente;
        free(pila);
        *pila = actual;
    }
}
