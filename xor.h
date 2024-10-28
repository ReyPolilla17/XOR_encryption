#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct def_argumentos
{
    int source_f;               // Si la entrada es un archivo
    int source_i;               // Si la entrada ignora los \n
    char *source_c;             // La cadena relacionada con la entrada (archivo o mensaje)
    int key_f;                  // Si la clave es un archivo
    int key_i;                  // Si la clave ignora los \n
    char *key_c;                // La cadena relacionada con la clave (archivo o mensaje)
    int out_d;                  // Si el mensaje decodificado se guardará como "res_entrada"
    char *out_c;                // El nombre del archivo en el que se guarde el mensaje decodificado
} ARGUMENTOS;

typedef struct def_binario
{
    int val;                    // 1 o 0 de la posición que el elemento representa del numero
    struct def_binario *sig;    // El siguiente valor del binario
} BINARIO;

typedef struct def_frase
{
    char a;                     // La letra de la frase
    BINARIO *bin;               // El valor binario de la letra
    struct def_frase *sig;      // La siguiente letra de la frase
} FRASE;

typedef struct def_clave
{
    FRASE *clave;               // La clave
    struct def_clave *sig;      // La siguiente clave
} CLAVE;

// Trabaja con los argumentos
int getArgs(int argc, char *argv[], ARGUMENTOS *args);

// Operaciones con los valores binarios
void createBinary(BINARIO **inicio, int val);
void addToBinary(BINARIO **inicio, int val);
void XORBinaries(BINARIO *bin1, BINARIO *bin2, BINARIO **res);
char binToChar(BINARIO *inicio);
void freeBinary(BINARIO **inicio);

// Acciones para decodificar
void decodeMessage(FRASE *message, CLAVE *key, FRASE **res, int ignore);
void printMessage(FRASE *inicio);
void saveMessage(FRASE *inicio, ARGUMENTOS args);

// Trabaja con la clave
int loadKeyFromString(void **inicioG, ARGUMENTOS args);
int loadKeyFromFile(void **inicioG, ARGUMENTOS args);
void freeKey(CLAVE **inicio);

// Funciones varias
int load(void **inicio, ARGUMENTOS args, int x, int y);
void helpMessage(void);
int startsWith(char start[], char string[]);
int endsWith(char end[], char string[]);

// Trabaja con el mensaje
int loadMessageFromString(void **inicioG, ARGUMENTOS args);
int loadMessageFromFile(void **inicioG, ARGUMENTOS args);
void freeMessage(FRASE **inicio);