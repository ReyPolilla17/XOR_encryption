#include "xor.h"

/**
 * Carga un mensaje o clave de un archivo de texto o una cadena segun se necesite
 * 
 * @param **inicio Un puntero que contenga el inicio de la lista dinámica
 * @param args Los argumentos de ejecución del programa
 * @param x El tipo de estructura a cargar (0 Claves, 1 Mensajes)
 * @param y La forma de cargar el mensaje (0 Cadenas, 1 archivos)
 * 
 * @returns int (Si la carga fue exitosa)
 */
int load(void **inicio, ARGUMENTOS args, int x, int y)
{
    // crea un arreglo con las funciones
    int (*loadFunctions[2][2])(void **inicio, ARGUMENTOS args) = {
        { loadKeyFromString, loadKeyFromFile },
        { loadMessageFromString, loadMessageFromFile }
    };

    // ejecuta la función decidida
    return (loadFunctions[x][y])(inicio, args);    
}

/**
 * Imprime un mensaje con las especificaciones de uso del programa
 * 
 * @returns void
 */
void helpMessage(void)
{
    printf("Every element with a * is mandatory.\n");
    printf("Extras are placed as part of the tag and must be placed on the end of it, ex: --in-F-n.\n\n");
    printf("--In *\n");
    printf("The encrypted or to-enrypt message, a string must be inputed after this tag.\n");
    printf("The string can be the message itself or a path to a file with the message,\n");
    printf("in this case you must use one of the variations instead.\n");
    printf("The extra is optional and it is used to ignore the \\n character from the message;\n");
    printf("this will result in an encoded message except for the page breaks, and reseting the key every new line.\n");
    printf("The extra can only be used if the message is stored in a file.\n");
    printf("    Alias: -i\n\n");
    printf("    Variations:\n");
    printf("        --In-F\n");
    printf("        -if\n\n");
    printf("    Extras:\n");
    printf("        -n\n\n");
    
    printf("--Key *\n");
    printf("The decryption key, a string must be inputed after this tag.\n");
    printf("The string can be the key itself or a path to a file with the key,\n");
    printf("in this case you must use one of the variations instead.\n");
    printf("The extra is optional and it is used to ignore the \\n character from the key;\n");
    printf("this will result in an encoded message that every new line uses a different key thus,\n");
    printf("evey \\n in the original message will be ignored.\n");
    printf("The extra can only be used if both the message and the kay are stored in files.\n");
    printf("In case there are more lines in the keys file than in the messages file, the excess keys will be ignored.\n");
    printf("In case there are less lines in the keys file than in the messages file, the keys will cycle to decrypt the missing messages.\n");
    printf("    Alias: -k\n\n");
    printf("    Variations:\n");
    printf("        --Key-F\n");
    printf("        -kf\n\n");
    printf("    Extras:\n");
    printf("        -n\n\n");
    
    printf("--Out\n");
    printf("The output file, a string must be inputed after this tag unless the extra is used.\n");
    printf("The extra is optional and it is used to give the output file the name res_ followed by the original file name.\n");
    printf("For this reason, it's mandatory to give a file as the encrypted or to-enrypt message when using the extra.\n");
    printf("    Alias: -o\n\n");
    printf("    Extras:\n");
    printf("        -d\n\n");

    return;
}

/**
 * Determina si una cadena comienza con la cadena especificada
 * 
 * @param start[] La forma en la que la cadena debe comenzar
 * @param string[] La cadena a verificar
 * 
 * @returns int (1 si la cadena comienza de la forma especificada, 0 si la cadena no comienza de la forma especificada)
 */
int startsWith(char start[], char string[])
{
    int i = 0;

    // obtiene la longitud de las cadenas
    int l1 = strlen(start);
    int l2 = strlen(string);

    // si la cadena a comprobar es menor a la forma de iniciar
    if(l2 < l1)
    {
        return 0;
    }

    // compara cada caracter en la forma de iniciar
    for(i = 0; i < l1; i++)
    {
        // si algun caracter es diferente
        if(start[i] != string[i])
        {
            return 0;
        }
    }

    return 1;
}

/**
 * Determina si una cadena termina con la cadena especificada
 * 
 * @param end[] La forma en la que la cadena debe terminar
 * @param string[] La cadena a verificar
 * 
 * @returns int (1 si la cadena termina de la forma especificada, 0 si la cadena no termina de la forma especificada)
 */
int endsWith(char end[], char string[])
{
    int i = 0;

    // obtiene la longitud de las cadenas
    int l1 = strlen(end);
    int l2 = strlen(string);

    // si la cadena a comprobar es menor a la forma de iniciar
    if(l2 < l1)
    {
        return 0;
    }

    // compara cada caracter en la forma de terminar
    for(i = 0; i < l1; i++)
    {
        // si algun caracter no coincide
        if(end[l1 - i] != string[l2 - i])
        {
            return 0;
        }
    }

    return 1;
}