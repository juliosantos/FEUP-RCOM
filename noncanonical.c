/*Non-Canonical Input Processing*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define BAUDRATE B38400
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE;

int main(int argc, char** argv)
{
    int fd,c, res;
    struct termios oldtio,newtio;
    char buf[255],guardar[255];

    if ( (argc < 2) || 
  	     ((strcmp("/dev/ttyS0", argv[1])!=0) && 
  	      (strcmp("/dev/ttyS1", argv[1])!=0) )) {
      printf("Usage:\tnserial SerialPort\n\tex: nserial /dev/ttyS1\n");
      exit(1);
    }


  /*
    Open serial port device for reading and writing and not as controlling tty
    because we don't want to get killed if linenoise sends CTRL-C.
  */
  
    
    fd = open(argv[1], O_RDWR | O_NOCTTY );
    if (fd <0) {perror(argv[1]); exit(-1); }

    if ( tcgetattr(fd,&oldtio) == -1) { /* save current port settings */
      perror("tcgetattr");
      exit(-1);
    }

    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio.c_lflag = 0;

    newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
    newtio.c_cc[VMIN]     = 1;   /* blocking read until 5 chars received */



  /* 
    VTIME e VMIN devem ser alterados de forma a proteger com um temporizador a 
<<<<<<< HEAD
    leitura do(s) pr�ximo(s) caracter(es)
=======
    leitura do(s) próximo(s) caracter(es)
  */



    tcflush(fd, TCIOFLUSH);

    if ( tcsetattr(fd,TCSANOW,&newtio) == -1) {
      perror("tcsetattr");
      exit(-1);
    }

    printf("New termios structure set\n");
    strcpy(guardar,"");

    while (STOP==FALSE) {       /* loop for input */
      res = read(fd,buf,1);   /* returns after 5 chars have been input */
	if(res>0){

      buf[res]=0;               /* so we can printf... */
      printf(":%s:%d\n", buf, res);

	strcat(guardar,buf);
      if (buf[res-1]=='\0') STOP=TRUE;}
    }
	printf("%s\n",guardar);
    	sleep(2);
	guardar[strlen(guardar)]='\0';
	res= write(fd,guardar,255);
	printf("enviado %d\n",res);
	


  /* 
    O ciclo WHILE deve ser alterado de modo a respeitar o indicado no guião 
  */

    sleep(2);

    tcsetattr(fd,TCSANOW,&oldtio);
    close(fd);
    return 0;
}
    /* set input mode (non-canonical, no echo,...) */
    newtio.c_lflag = 0;

    newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
    newtio.c_cc[VMIN]     = 1;   /* blocking read until 5 chars received */



  /* 
    VTIME e VMIN devem ser alterados de forma a proteger com um temporizador a 
    leitura do(s) próximo(s) caracter(es)
>>>>>>> 85cb985bb20c75aacc2f0cd99771751d95d56ff8
  */



    tcflush(fd, TCIOFLUSH);

    if ( tcsetattr(fd,TCSANOW,&newtio) == -1) {
      perror("tcsetattr");
      exit(-1);
    }

    printf("New termios structure set\n");
    strcpy(guardar,"");

    while (STOP==FALSE) {       /* loop for input */
      res = read(fd,buf,255);   /* returns after 5 chars have been input */
      buf[res]=0;               /* so we can printf... */
      printf(":%s:%d\n", buf, res);
	strcat(guardar,buf);
      if (buf[res-1]=='\0') STOP=TRUE;
    }
printf("%s\n",guardar);
    sleep(2);
	guardar[strlen(guardar)]='\0';
	res= write(fd,guardar,255);
	printf("enviado %d\n",res);
	


  /* 
<<<<<<< HEAD
    O ciclo WHILE deve ser alterado de modo a respeitar o indicado no gui�o 
=======
    O ciclo WHILE deve ser alterado de modo a respeitar o indicado no guião 
>>>>>>> 85cb985bb20c75aacc2f0cd99771751d95d56ff8
  */

    sleep(2);

    tcsetattr(fd,TCSANOW,&oldtio);
    close(fd);
    return 0;
}
