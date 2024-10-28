#include "xor.h"

/**
 * Decodifica un mensaje utilizando una clave y lo guarda en una lista dinámica
 * 
 * @param *message El mensaje a decodificar
 * @param *key La clave de decodificación
 * @param **res La lista dinámica en la que se guarda el mensaje decodificado
 * @param ignore Si se debe ignorar el caracter de salto de linea o no
 * 
 * @returns void
 */
void decodeMessage(FRASE *message, CLAVE *key, FRASE **res, int ignore)
{
    CLAVE *tempK;
    FRASE *temp;

    FRASE *tempM;
    FRASE *temp2;
    FRASE *new;

    tempK = key;
    temp = key->clave;

    tempM = message;
    temp2 = *res;

    // para cada elemento del mensaje
    while(tempM != NULL)
    {
        // crea un elemento para el caracrer decodificado
        new = (FRASE *) malloc(sizeof(FRASE));
        new->sig = NULL;
        new->bin = NULL;

        // si se deben ignorar los saltos de linea
        if(tempM->a == '\n' && ignore)
        {
            // si es un enter, guarda ese valor como un enter
            new->a = tempM->a;
            createBinary(&new->bin, new->a);

            // reinicia la clave
            tempK = tempK->sig;
            temp = tempK->clave;
        }
        // de lo contrario
        else
        {
            // obtiene el resultado de la operación XOR entre los 2 binarios
            XORBinaries(tempM->bin, temp->bin, &new->bin);

            // convierte el resultado anterior en un caracter
            new->a = binToChar(new->bin);
            
            // recorre la clave al siguiente caracter
            temp = temp->sig;
        }
        
        // inserta el valor en la lista del resultado
        if(temp2 != NULL)
        {
            temp2->sig = new;
            temp2 = temp2->sig;
        }
        else
        {
            temp2 = new;

            *res = temp2;
        }
        
        // se recorre al siguiente caracter del mensaje
        tempM = tempM->sig;
    }

    return;
}

/**
 * Imprime el contenido de una lista dinámica
 * 
 * @param *inicio El inicio de la lista
 * 
 * @returns void
 */
void printMessage(FRASE *inicio)
{
    FRASE *temp;

    temp = inicio;

    while(temp != NULL)
    {
        printf("%c", temp->a);
        
        temp = temp->sig;
    }

    printf("\n");

    return;
}

/**
 * Guarda el mensaje resultante en un archivo de texto
 *
 * @param *inicio La lista que contiene el mensaje decodificado
 * @param args Infomración para guardar el archivo
 * 
 * @returns void
 */
void saveMessage(FRASE *inicio, ARGUMENTOS args)
{
    FRASE *temp;

    FILE *fp;

    char *file;
    char *h;

    int i = 0;
    int l = strlen(args.source_c);

    // si el nombre del archivo va a ser [runta]/res_[nombre original]
    if(args.out_d)
    {
        // copia el nombre y tuta originales del archivo
        file = (char *) malloc(sizeof(char) * (l + strlen("res_") + 1));
        strcpy(file, args.source_c);

        // se recorre hasta encontrar la ultima diagonal o llegar al inicio
        for(i = l; i >= 0 && !((i - 1) >= 0 && (file[i - 1] == '/' || file[i - 1] == '\\')); i--);

        // acondicionamiento
        if(i == -1)
        {
            i++;
        }

        // vacía la copia hasta ese lugar y guarda lo qeu debería ir a partir de ese punto
        file[i] = 0;
        h = &args.source_c[i];

        // coloca el prefijo y lo que debería seguir
        strcat(file, "res_");
        strcat(file, h);
    }
    // si ya hay un nombre establecido
    else
    {
        file = args.out_c;
    }

    fp = fopen(file, "wt");
    
    temp = inicio;

    // escribe cada caracter en el archivo de texto e imprime en pantalla dicho caracter
    while(temp != NULL)
    {
        fprintf(fp, "%c", temp->a);
        temp = temp->sig;
    }

    fclose(fp);
    
    // en caso de que se haya alocado memoria
    if(args.out_d)
    {
        free(file);
    }

    return;
}