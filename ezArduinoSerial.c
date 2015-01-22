#include "ezArduinoSerial.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#define DEFAULT_TIME_OUT 200
struct ezArduinoSerial{
  int fd;
};
int readFromArduino(int fd, char *buffer,int size)
{
 int timeout=DEFAULT_TIME_OUT;
  int n=0;
  int caractereRead=0;
  while(timeout>0 &&  n==0 ){
    n=read(fd,buffer,size*sizeof(char));
    if(n>0)
      caractereRead+=n;
    else if (n==0){
      usleep(1000);
      timeout--;
    }
    else
      perror("Read error !");
     
    
  }
  return caractereRead;
}
int readFromEzArduino(EzArduinoSerial this,char *buffer,int size)
{
  int timeout=DEFAULT_TIME_OUT;
  int n=0;
  int caractereRead=0;
  while(timeout>0 &&  n==0 ){
    n=read(this->fd,buffer,size*sizeof(char));
    if(n>0)
      caractereRead+=n;
    else if (n==0){
      usleep(1000);
      timeout--;
    }
    else
      perror("Read error !");
     
    
  }

}
void writeToEzArduino(EzArduinoSerial this,char *msg)
{
  write(this->fd,msg,strlen(msg)*sizeof(char));
  

}
void linkWithArduino(char *path,int bitrate)
{
  struct termios t;
  int fd=open(path,O_RDONLY| O_NONBLOCK);
  tcgetattr(fd,&t);
  cfsetispeed(&t,bitrate);
  cfsetospeed(&t,bitrate);
  tcsetattr(fd,TCSANOW,&t);
  
  int fd2=open(path,O_WRONLY| O_NONBLOCK| O_TRUNC | O_CREAT,0666);
  tcgetattr(fd2,&t);
  cfsetispeed(&t,bitrate);
  cfsetospeed(&t,bitrate);
  tcsetattr(fd2,TCSANOW,&t);
  
  if(fork()==0)
    {
      int n;
	char buffer[100];
	char bufferReception[100];
	int nbReception=0;
	while((n=read(0,buffer,sizeof(char)*100))>0)
	  {
	    write(fd2,&buffer,sizeof(char)*n);
	    while((nbReception=readFromArduino(fd,bufferReception,sizeof(char)*100))>0)
	      write(1,bufferReception,sizeof(char)*nbReception);
	  }
	exit(0);
    }

  

}
EzArduinoSerial createEzArduinoSerial(char *path,int bitrate)
{
  struct termios t;
  EzArduinoSerial this=malloc(sizeof(struct ezArduinoSerial));
  this->fd=open(path,O_RDWR| O_NONBLOCK);
  tcgetattr(this->fd,&t);
  cfsetispeed(&t,bitrate);
  cfsetospeed(&t,bitrate);
  tcsetattr(this->fd,TCSANOW,&t);

  return this;

}

