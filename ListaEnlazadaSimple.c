#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int valor;
    struct nodo *siguiente;
} Nodo;

Nodo *Crear_Nodo(int);
void Apilar_Nodo(Nodo **, Nodo *);
void Desapilar_Nodo(Nodo **);
void Imprimir_Pila(Nodo *);
int Contar_Nodos(Nodo *);
void Borrar_Pila(Nodo **);

int main(int argc, char const *argv[])
{
    Nodo *pila = NULL, *nuevo;
    for (size_t i = 0; i < 4; i++)
    {
        nuevo = Crear_Nodo(i);
        Apilar_Nodo(&pila, nuevo);
    }

    Imprimir_Pila(pila);

    return 0;
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
    Nodo *auxPila = (Nodo *)malloc(sizeof(Nodo)); //Creación de un nodo con memoria dinámica
    auxPila = pila;
    int i = 0;

    while (pila != NULL)
    {
        printf("Nodo: %d\n",  pila->valor);
        printf("Direcciones:\n");
        printf("Actual: -> %x\t", pila);
        printf("Siguiente: -> %x\n", pila->siguiente);
        pila = pila->siguiente;
    }
}

/**
 * Crea un nodo
 * @param valor del nodo
 * @return nodo
 */
Nodo *Crear_Nodo(int valor)
{
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->valor = valor;
    nodo->siguiente = NULL;

    return nodo;
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
        *pila = nodo; //Y se agrega la pila
    }
}

/**
 * Quita el último nodo agregado.
 * @param Nodo** pila de donde quitar el nodo.
 */
void Desapilar_Nodo(Nodo **pila)
{
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo = (*pila)->siguiente;
    free(*pila);
    *pila = nodo;
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