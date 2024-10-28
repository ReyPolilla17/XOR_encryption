#include "xor.h"

/**
 * Carga el mensaje a decodificar en una lista dinámica desde una cadena
 * 
 * @param **inicioG La lista dinámica en la que se guardará el mensaje como puntero a void
 * @param args Información de la ejecución
 * 
 * @returns int (Simepre 1)
 */
int loadMessageFromString(void **inicioG, ARGUMENTOS args)
{
    FRASE **inicio = (FRASE **) inicioG;

    FRASE *new;
    FRASE *temp;

    int i = 0;
    int l = strlen(args.source_c);

    // para todos los caracteres de la frase
    for(i = 0; i < l; i++)
    {
        // crea un nuevo elemento de la lista
        new = (FRASE *) malloc(sizeof(FRASE));
        new->a = args.source_c[i];
        new->bin = NULL;
        new->sig = NULL;

        // obtiene el valor binario del caracter
        createBinary(&new->bin, new->a);

        // lo inserta en la lista
        if(*inicio != NULL)
        {
            temp->sig = new;
            temp = temp->sig;
        }
        else
        {
            *inicio = new;
            temp = *inicio;
        }
    }

    return 1;
}

/**
 * Carga el mensaje a decodificar en una lista dinámica desde un archivo de texto
 * 
 * @param **inicioG La lista dinámica en la que se guardará el mensaje como puntero a void
 * @param args Información de la ejecución
 * 
 * @returns int (1 en caso de carga exitosa, 0 en caso de error)
 */
int loadMessageFromFile(void **inicioG, ARGUMENTOS args)
{
    FRASE **inicio = (FRASE **) inicioG;

    FRASE *new;
    FRASE *temp;

    FILE *fp;

    char a = 0;

    temp = NULL;

    fp = fopen(args.source_c, "rb");

    // si no encuentra el archivo
    if(fp == NULL)
    {
        printf("Mesage file not found...\n");
        return 0;
    }

    // para cada caracter del archivo
    while(fread(&a, sizeof(char), 1, fp))
    {
        // crea un nuevo elemento de la lista
        new = (FRASE *) malloc(sizeof(FRASE));
        new->a = a;
        new->bin = NULL;
        new->sig = NULL;

        // obtiene el valor binario del caracter
        createBinary(&new->bin, new->a);

        // lo inserta en la lista
        if(*inicio != NULL)
        {
            temp->sig = new;
            temp = temp->sig;
        }
        else
        {
            *inicio = new;
            temp = *inicio;
        }
    }

    fclose(fp);

    return 1;
}

/**
 * Libera la memoria dinámica de un mensaje
 * 
 * @param **inicio El inicio del mensaje
 * 
 * @returns void
 */
void freeMessage(FRASE **inicio)
{
    FRASE *temp;

    // libera cada elemento
    while(*inicio != NULL)
    {
        temp = *inicio;
        *inicio = temp->sig;

        // libera la memoria del caracter en binario
        freeBinary(&temp->bin);
        free(temp);
    }

    return;
}