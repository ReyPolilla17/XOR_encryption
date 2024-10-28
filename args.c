#include "xor.h"

/**
 * Obtiene los argumentos usados en la ejecución del programa, que pueden estar en cualquier orden,
 * siguiendo las reglas de cada argumento
 * 
 * @param argc La cantidad de argumentos utilizados al ejecutar el programa
 * @param *argv[] Los argumentos utilizados al ejecutar el programa
 * @param *args Los detalles de los argumentos utilizados al iniciar el programa
 * 
 * @returns int (menor a 0 en caso de errores de ejecución, 0 en caso de ejecución válida, 1 en caso de solicitar ayuda)
 */
int getArgs(int argc, char *argv[], ARGUMENTOS *args)
{
    int e = 0;
    int i = 0;

    // inicializa la info en args
    args->source_c = NULL;
    args->source_f = 0;
    args->source_i = 0;
    args->key_c = NULL;
    args->key_f = 0;
    args->key_i = 0;
    args->out_c = NULL;
    args->out_d = 0;

    // para cada argumento
    for(i = 1; i < argc; i++)
    {
        // mensaje codificado o a codificar
        if(startsWith("--In", argv[i]) || startsWith("-i", argv[i]))
        {
            // si ya se habia establecido un mensaje antes
            if(args->source_c != NULL)
            {
                printf("--In string/file already used once...\n");

                e--;
            }
            // si hay una cadena después
            else if((i + 1) < argc)
            {
                // guarda esa cadena
                args->source_c = argv[i + 1];

                // si se desea que la entrada sea  un archivo
                if(startsWith("--In-F", argv[i]) || startsWith("-if", argv[i]))
                {
                    args->source_f = 1;
                }

                // si se desea ignorar los saltos de linea
                if(endsWith("-n", argv[i]))
                {
                    // si se desea cargar el mensaje de un archivo
                    if(args->source_f)
                    {
                        // en caso de que ya se haya establecido dicha afirmación
                        if(args->source_i == 1)
                        {
                            printf("Warning: Redundant ignoring of --In \\n mentioned.\n");
                        }

                        args->source_i = 1;
                    }
                    // de lo contrario
                    else
                    {
                        printf("-n extra only can be used if the message is stored in a file...\n");

                        e--;
                    }
                }

                // se saltará el siguiente argumento
                i++;
            }
            // si es el ultimo argumento utilizado
            else
            {
                printf("--In must be followed by a string...\n");

                e--;
            }
        }
        // clave
        else if(startsWith("--Key", argv[i]) || startsWith("-k", argv[i]))
        {
            // si ya se habia establecido una clave
            if(args->key_c != NULL)
            {
                printf("--Key string/file already used once...\n");

                e--;
            }

            // si hay un argumento después
            else if((i + 1) < argc)
            {
                // guarda el siguiente argumento
                args->key_c = argv[i + 1];

                // si la llave se obtiene de un archivo
                if(startsWith("--Key-f", argv[i]) || startsWith("-kf", argv[i]))
                {
                    args->key_f = 1;
                }

                // si se desea usar una clave diferente para cada línea del archivo
                if(endsWith("-n", argv[i]))
                {
                    // si tanto las claves como los mensajes se cargarán de archivos
                    if(args->key_f && args->source_f)
                    {
                        // si ya se habia habilitado la acción con anterioridad
                        if(args->key_i)
                        {
                            printf("Warning: Redundant ignoring of --Key \\n mentioned.\n");
                        }

                        args->key_i = 1;
                        args->source_i = 1;
                    }
                    // de lo contrario
                    else
                    {
                        printf("-n extra only can be used if both the message and the key are stored in files...\n");

                        e--;
                    }
                }

                i++;
            }
            // si es el ultimo argumento utilizado
            else
            {
                printf("--Key must be followed by a string...\n");

                e--;
            }
        }
        // archivo con el mensaje decodificado
        else if(startsWith("--Out", argv[i]) || startsWith("-o", argv[i]))
        {
            // si ya se habia establecido un archivo
            if(args->out_c != NULL || args->out_d)
            {
                printf("--Out already used once...\n");

                e--;
            }
            // si se desea que el archivo se llame res_ fuente
            else if(!strcmp(argv[i], "--Out-d") || !strcmp(argv[i], "-od"))
            {
                args->out_d = 1;
            }
            // si  se desea establecer otro nombre
            else if((i + 1) < argc)
            {
                // guarda el nombre
                args->out_c = argv[i + 1];

                i++;
            }
            // si se desea establecer otro nombre, pero es el último argumento
            else
            {
                args->out_d = 1;
                
                printf("Warning: --Out should be followed by the output file name, assuming intended use of --Out-d...\n");
            }
        }
        // mensaje de ayuda
        else if(!strcmp(argv[i], "-h"))
        {
            return 1;
        }
        // acción desconocida
        else
        {
            printf("Unknown argument used: %s\n", argv[i]);

            e--;
        }
    }

    // si falta algún elemento obligatorio
    if(args->source_c == NULL)
    {
        printf("Mandatory --In missing...\n");

        e--;
    }

    if(args->key_c == NULL)
    {
        printf("Mandatory --Key missing...\n");

        e--;
    }

    // si se estableció el nombre por defecto, pero el mensaje no está en un archivo
    if(args->out_d && !args->source_f)
    {
        printf("Can't use --Out-d if --In-f is not being used...\n");

        e--;
    }

    return e;
}