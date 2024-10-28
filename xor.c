/**
 * @file cifrdo_xor.c
 * 
 * @brief (quizá en un futuro lo divida en más archivos, depende de que tan complejo se ponga)
 * Este archivo contiene un programa capaz de codificar y decodificar mensajes usando el cifrado XOR
 * 
 * Dicho cifrado requiere de un mensaje y de una clave, en cada caracter del mensaje, usará cada caracter de la clave,
 * si la clave es más corta que el mensaje, repetirá la clave para cubrir todo el mensaje.
 * En cada caracter, obtendrá el valor binario del caracter del mensaye y de la clave y para cada valor de ambos numeros,
 * realizará una operación XOR, lo que resultará en otro número, ese numero será el caracter codificado, realizará
 * este procedimiento con todos los caracteres del mensaje.
 * 
 * Este programa cuenta con la posibilidad de decodificar mensajes desde un archivo de texto o desde la terminal,
 * haciendo lo mismo con la clave, se puede configurar para guardar el mensaje resultante en un archivo de texto,
 * igualmente se puede especificar si se desea ignorar o no los saltos de linea, tanto para el mensaje como para la clave,
 * ignorar los saltos de linea de la clave resultará en que cada linea del mensaje se decodificará con cada línea de la
 * clave, ignorar los saltos de línea para el archivo hará que cada linea uneva se interprete como un mensaje nuevo,
 * haciendo que la clave se vuelva a iniciar con cada línea nueva.
 * 
 * El programa fue desarrollado con ciertas limitaciones por cuestión de tiempo, por lo que ahora mismo se está trabajando
 * en modificar la mayoría de sus funcionalidades.
 * 
 * @author Polilla
 * 
 * @date 26/10/2024
 */

#include "xor.h"

int main(int argc, char *argv[])
{
    ARGUMENTOS args;
    
    CLAVE *clave;
    
    FRASE *mensaje;
    FRASE *res;

    int ar = getArgs(argc, argv, &args); // organiza los argumentos de entrada

    clave = NULL;
    mensaje = NULL;
    res = NULL;

    // en caos de que algun argumento no sea valido
    if(ar < 0)
    {
        printf("\nUse -h for an explanation on how to run the program.\n");

        return -1;
    }
    // en caso de solicitar ayuda
    else if(ar > 0)
    {
        helpMessage();

        return 0;
    }

    // intenta cargar las claves
    if(!load((void **)&clave, args, 0, args.key_f))
    {
        return -2;
    }

    // intenta cargar el mensaje
    if(!load((void **)&mensaje, args, 1, args.source_f))
    {
        freeKey(&clave);

        return -2;
    }

    // decodifica el mensaje y lo imprime
    decodeMessage(mensaje, clave, &res, args.source_i);
    printMessage(res);

    // si se eligió guardar
    if(args.out_d || args.out_c != NULL)
    {
        saveMessage(res, args);
    }

    // libera la memoria
    freeKey(&clave);
    freeMessage(&mensaje);
    freeMessage(&res);

    return 0;
}