#include "xor.h"

/**
 * Crea una lista dinámica con la clave del código
 * 
 * @param **inicioG La lista dinámica en la que se almacenará la información como puntero tipo void
 * @param args Información de la ejecución
 * 
 * @returns int (Simepre 1)
 */
int loadKeyFromString(void **inicioG, ARGUMENTOS args)
{
    CLAVE **inicio = (CLAVE **) inicioG;
    CLAVE *newK;

    FRASE *new;
    FRASE *temp;

    int i = 0;
    int l = strlen(args.key_c);

    newK = (CLAVE *) malloc(sizeof(CLAVE));

    newK->clave = NULL;
    newK->sig = newK;

    // para todos los caracteres de la palabra clave
    for(i = 0; i < l; i++)
    {
        // crea un nuevo elemento con el caracter que se esté evaluando
        new = (FRASE *) malloc(sizeof(FRASE));
        new->a = args.key_c[i];
        new->bin = NULL;
        new->sig = NULL;

        // obtiene el valor en binario del caracter
        createBinary(&new->bin, new->a);

        // lo inserta en la lista
        if(newK->clave != NULL)
        {
            temp->sig = new;
            temp = temp->sig;
        }
        else
        {
            newK->clave = new;
            temp = newK->clave;
        }
    }

    // hace que la lista sea circular
    temp->sig = newK->clave;

    *inicio = newK;

    return 1;
}

/**
 * Carga las claves de decodificación desde un archivo de texto
 * 
 * @param **inicioG La lista dinámica de las claves, como puntero tipo void
 * @param args Información de ejecución
 * 
 * @returns int (1 en caso de carga exitosa, 0 en caso de error)
 */
int loadKeyFromFile(void **inicioG, ARGUMENTOS args)
{
    CLAVE **inicio = (CLAVE **) inicioG;
    CLAVE *newK;
    CLAVE *tempK;

    FRASE *newF;
    FRASE *tempF;

    FILE *fp;

    char a = 0;

    newK = NULL;
    tempK = NULL;
    newF = NULL;
    tempF = NULL;

    fp = fopen(args.key_c, "rb");

    // si no s epudo abrir el archivo
    if(fp == NULL)
    {
        printf("Key file not found...\n");

        return 0;
    }

    // crea un primer elemento para la lista
    tempK = (CLAVE *) malloc(sizeof(CLAVE));
    tempK->clave = NULL;
    tempK->sig = NULL;

    *inicio = tempK;

    // para cada caracter
    while(fread(&a, sizeof(char), 1, fp))
    {
        // si hay un salto de linea y se desea ignorar los saltos de linea
        if(a == '\n' && args.key_i)
        {
            // si la frase actual no tiene caracteres
            if(tempK->clave == NULL)
            {
                // colocar un caracter nulo y cerrar la lista circular
                tempK->clave = (FRASE *) malloc(sizeof(FRASE));
                tempK->clave->a = 0;
                tempK->clave->bin = NULL;
                tempK->clave->sig = tempK->clave;

                createBinary(&tempK->clave->bin, tempK->clave->a);
            }
            // si la frase tiene caracteres
            else
            {
                // cerrar la lista circular
                tempF->sig = tempK->clave;
            }

            // crear nuevo elemento key
            newK = (CLAVE *) malloc(sizeof(CLAVE));
            newK->clave = NULL;
            newK->sig = NULL;

            // agregarlo a la lista
            tempK->sig = newK;
            tempK = tempK->sig;
        }
        else
        {
            // crear elementos frase y meterlos a la lista
            newF = (FRASE *) malloc(sizeof(FRASE));
            newF->a = a;
            newF->bin = NULL;
            newF->sig = NULL;

            createBinary(&newF->bin, newF->a);

            if(tempK->clave != NULL)
            {
                tempF->sig = newF;
                tempF = tempF->sig;
            }
            else
            {
                tempK->clave = newF;
                tempF = tempK->clave;
            }
        }
    }

    // cerrar la última lista circular de frase
    // si la ultima frase no tiene caracteres
    if(tempK->clave == NULL)
    {
        // colocar un caracter nulo y cerrar la lista circular
        tempK->clave = (FRASE *) malloc(sizeof(FRASE));
        tempK->clave->a = 0;
        tempK->clave->bin = NULL;
        tempK->clave->sig = tempK->clave;

        createBinary(&tempK->clave->bin, tempK->clave->a);
    }
    // si la frase tiene caracteres
    else
    {
        // cerrar la lista circular
        tempF->sig = tempK->clave;
    }

    // cerrar la lista circular
    tempK->sig = *inicio;

    fclose(fp);

    return 1;
}

/**
 * Libera la memoria de la lista dinámica de la clave, que consta de una lista circular y
 * cada elemento de la clave contiene otra lista circular que contiene una lista dinámica simple
 * 
 * @param **inicio La lista dinámica de la clave
 * 
 * @returns void
 */
void freeKey(CLAVE **inicio)
{
    CLAVE *plHol;
    CLAVE *temp;
    
    FRASE *plHolf;
    FRASE *tempf;

    plHol = *inicio;

    // si la lista de claves tiene elementos
    if(plHol != NULL)
    {
        // va a dar una vuelta completa a cada elemento
        do
        {
            // guarda la posición actual y se recorre una posición
            temp = plHol;
            plHol = temp->sig;

            // liberaciónd e la segunda lista circular
            plHolf = temp->clave;

            // si la segunda lista circular tiene elementos
            if(plHolf != NULL)
            {
                // da una vuelta a cada elemento de esa lista circular
                do
                {
                    // guarda ese elemento y se recorre al siguiente elementp
                    tempf = plHolf;
                    plHolf = tempf->sig;

                    // libera el valor binario de la lista y libera la estructura
                    freeBinary(&tempf->bin);
                    free(tempf);
                } while(plHolf != temp->clave);
            }

            // libera la estructura
            free(temp);
        } while(plHol != *inicio); 
    }

    return;
}