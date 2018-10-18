#ifndef WRITER_H_
#define WRITER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <signal.h>

#define CTRL_C_START 0x02
#define CTRL_C_END   0x03
#define T1           0x00   //Tamanho do ficheiro
#define T2           0x01   //Nome do ficheiro   
#define L1           0x04   //4 - Tamanho de um long int 



void data_writer(int argc, char * argv[]);

//       Data Link Layer Functions

int llopenW(int porta, int status); //TODO Tirar argumentos
// argumentos
// –porta: COM1, COM2, ...
// –flag: TRANSMITTER / RECEIVER
// retorno
// –identificador da ligação de dados
// –valor negativo em caso de erro


int llwrite(int fd, char * buffer, int length);
// argumentos
// – fd: identificador da ligação de dados
// – buffer: array de caracteres a transmitir
// – length: comprimento do array de caracteres
// retorno
// – número de caracteres escritos
// – valor negativo em caso de erro


//Global variables

unsigned char SET[5];
unsigned char UA[5];
int fd;


//      Application Layer Functions

unsigned char * readFile(unsigned char * fileName, long int * fileSize);

unsigned char * makeControlPackage_I(long int fileSize, unsigned char * fileName, int fileName_size, int * finalSize, unsigned char start_or_end);


#endif