#include "libserie.h"

int UART_Open(char* port)
{
int fd;
    if ((fd = open(port, O_RDWR|O_NOCTTY|O_NDELAY)) == -1){
       perror("open");
       return ERROR;
    }
    if (fcntl(fd, F_SETFL, 0) < 0) {
       perror("fcntl");
       return ERROR;
    }
    if(!isatty(fd)) {
       fprintf(stderr,"%s n'est pas un terminal !!\n",port);
       return ERROR;
    }
    return fd;
}

void UART_Close(int fd)
{
    close(fd);
}

void UART_SetSpeed(int speed, struct termios *options){
     int i;
     int speed_arr[]={B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1800};
     int valeur[]={115200, 57600, 38400, 19200, 9600, 4800, 2400, 1800};
    /* Mise en place des vitesse en entree et en sortie */
    for (i=0; i<NBSPEED; i++) {
        if (speed == valeur[i]) {
            cfsetispeed(options, speed_arr[i]);
            cfsetospeed(options, speed_arr[i]);
            break;
        }
    }

}


int UART_Init(int fd, int speed,short flowCtrl,short dbits,short stopb,
    short delai, short nbcmin, char parity)
{

//int speed_arr[]={B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1800};
//int valeur[]={115200, 57600, 38400, 19200, 9600, 4800, 2400, 1800};

struct termios options;
     int i;
    if ( tcgetattr(fd,&options) != 0) {
        perror("tcgetattr");
        return ERROR;
    }

    cfmakeraw(&options); // Set raw input mode and output mode
    options.c_cc[VTIME] = 0; // Set timeout between characters to 0
    options.c_cc[VMIN] = 1; // Wait for at least 1 character before returning
    options.c_cflag |= CLOCAL; // Ignore modem control lines
    options.c_cflag |= CREAD; // Enable receiver

    // Set input and output baud rate to 115200
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    // Disable hardware flow control
    options.c_cflag &= ~CRTSCTS;

    // Set data bits to 8
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // Disable parity
    options.c_cflag &= ~PARENB;

    // Set stop bits to 1
    options.c_cflag &= ~CSTOPB;

    // Disable software flow control
    options.c_iflag &= ~(IXON | IXOFF | IXANY);

    // Disable canonical mode and echo
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // Disable output processing
    options.c_oflag &= ~OPOST;


    /* Activation de la configuration */
    if (tcsetattr(fd,TCSANOW,&options) != 0) {
         perror("tcsetattr");
         return ERROR;
    }
    return 0;
}
int UART_Recv(int fd, char *buf,int len)
{
     return (read(fd,buf,len));
}

void UART_Send(char *msg, int fd) {
  int len = strlen(msg);
  int bytes_written = write(fd, msg, len);
  if (bytes_written != len) {
    printf("Erreur lors de l'envoi des données\n");
  }
}

