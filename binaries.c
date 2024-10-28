#include "xor.h"

/**
 * Convierte a binario un numero en base 10 (usado para obtener el binario de un caracter)
 * 
 * @param **inicio El inicio de la lista dinámica del numero binario
 * @param val El valor a convertir a binario
 * 
 * @returns void
 */
void createBinary(BINARIO **inicio, int val)
{
    int a = val;

    // convierte el numero a binario
    while(a)
    {
        // agrega el módulo del numero entre 2 al final de la lista, resultando en el valor binario invertido,
        // esto es más útil y eficiente para el resto de pasos
        addToBinary(inicio, a % 2);
        
        // divide el numero entre 2
        a /= 2;
    }

    return;
}

/**
 * Agrega un valor binario al final de la lista dinámica con el valor binario invertido
 * 
 * @param **inicio El inicio de la lista
 * @param val El valor que tendrá esa posición del número
 * 
 * @returns void
 */
void addToBinary(BINARIO **inicio, int val)
{
    BINARIO *new;
    BINARIO *temp;

    temp = *inicio;

    // crea un nuevo elemento con los valores especificados
    new = (BINARIO *) malloc(sizeof(BINARIO));
    new->sig = NULL;
    new->val = val;

    // agrega el elemento a la lista
    if(temp != NULL)
    {
        while(temp->sig != NULL)
        {
            temp = temp->sig;
        }

        temp->sig = new;
    }
    else
    {
        *inicio = new;
    }

    return;
}

/**
 * Realiza la operación XOR entre 2 numeros binarios, lo que genera otro numero binario
 * - XOR regresa un 0 si más de una condición es verdadera o si ninguna lo es y un 1 si solo una condición es verdadera
 * 
 * @param *bin1 El primer numero binario a operar
 * @param *bin2 El segundo numero binario a operar
 * @param **res El numero resultante de la operación
 * 
 * @returns void
 */
void XORBinaries(BINARIO *bin1, BINARIO *bin2, BINARIO **res)
{
    BINARIO *temp1;
    BINARIO *temp2;

    BINARIO *new;

    int v1 = 0;
    int v2 = 0;

    temp1 = bin1;
    temp2 = bin2;

    new = NULL;

    // mientras alguno de los 2 elementos siga teniendo valores
    while(temp1 != NULL || temp2 != NULL)
    {
        // valores por defecto
        v1 = 0;
        v2 = 0;

        // si alguno de los numeros sigue teniendo valores
        // cambia el valor por defecto y se recorre una posición
        if(temp1 != NULL)
        {
            v1 = temp1->val;
            temp1 = temp1->sig;
        }

        if(temp2 != NULL)
        {
            v2 = temp2->val;
            temp2 = temp2->sig;
        }

        // agrega el resultado de la operacion XOR al binario resultante
        addToBinary(&new, v1 ^ v2);
    }

    // guarda el binario resultante en res
    *res = new;

    return;
}

/**
 * Conbierte un valor binario en un caracter
 * 
 * @param *inicio El valor binario a convertir
 * 
 * @returns char - El caracter correspondiente
 */
char binToChar(BINARIO *inicio)
{
    BINARIO *temp;

    int p = 0;
    int res = 0;

    temp = inicio;

    // convierte el numero binario en un numero entero
    while(temp != NULL)
    {
        res += temp->val * pow(2, p);
        p++;

        temp = temp->sig;
    }

    // regresa el numero resultante como caracter
    return res;
}

/**
 * Libera la memoria dinámica de un numero binario
 * 
 * @param **inicio El inicio de la lista
 * 
 * @returns void
 */
void freeBinary(BINARIO **inicio)
{
    BINARIO *temp;

    // libera cada elemento de la lista
    while(*inicio != NULL)
    {
        temp = *inicio;
        *inicio = temp->sig;
        free(temp);
    }

    return;
}