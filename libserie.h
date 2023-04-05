#ifndef _LIBSERIE_H_
#define _LIBSERIE_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

/* Definitions de MACRO */
#define ERROR -1
#define LBUF 256

int UART_Open(char* port);
void UART_Close(int fd);

#define NBSPEED 8
int UART_Init(int fd, int speed,short flowCtrl,short dbits,short stopb, short delai, short nbcmin, char parity);

int UART_Recv(int fd, char *buf,int len);

void UART_Send(char *msg, int fd);



void UART_SetSpeed(int speed, struct termios *options);


#endif