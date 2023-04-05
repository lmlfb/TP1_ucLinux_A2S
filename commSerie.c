/* litSerie0.c : programme de lecture d'une interface serie */
#include "libserie.h"


int main(int N, char *P[])
{

   printf("hello !");
   
   int fd, speed, n;
char rcv_buf[LBUF];
char tobesend[100];

    if (N != 3) {
       fprintf(stderr,"Utilisation: %s /dev/ttyXX vitesse_en_baud\n",P[0]);
       return 1;
    }
    if ((fd = UART_Open(P[1])) == ERROR) return 2;
    speed = atoi(P[2]);
    if (UART_Init(fd,speed, 0,8,1,0,1,'N') == ERROR) return 3;
    /* boucle de lecture */
while (1) {
    n = UART_Recv(fd, rcv_buf,LBUF);
    if (n > 0) {
        rcv_buf[n] = '\0';
        printf("%s",rcv_buf);
    } else {
        fprintf(stderr,"Erreur lecture !!\n");
        break;
    }

    printf(" :  ");
    fgets(tobesend, sizeof(tobesend), stdin);
    UART_Send(tobesend, fd);
}

    UART_Close(fd);
    return 0;
}

