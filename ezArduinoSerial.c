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
#include <errno.h>
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
    else{
      perror("Read error !");
      return -1;
    }
    
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
static void addToBuffer(char *b1,char *b2,int size)
{
  int i;
  for(i=0;i<size;i++)
    b1[i]=b2[i];

}
void delinkArduino(int childPid)
{
  /**
     xxx
   */

  kill(childPid,9);
  waitpid(childPid,NULL);
}
/**
   Create an interface between an arduino and the 
   'main' process ( process calling this function ).
   At the end :
   -input will contain the file descriptor (O_WRONLY|O_TRUNC) associated with 
   arduino .
   -output will contain the file descriptor (O_RDONLY|O_APPEND) associated with 
   arduino .
   -return the pid of the interface.(dont forget to kill him before leaving !!)
   
   Current limitation :
   -output can BLOCK because it's a pipe . Therefore if the arduino is not sending information , read will BLOCK indefinitly . You can change this by using fcntl(output,O_NONBLOCK) .
   -MAX_ARDUINO_BUFFER should be used to read from input and to write to output.
   However you can redefine MAX_ARDUINO_BUFFER size before including ezArduino.h
   
 */

int linkWithArduino(char *path,int bitrate,int *input,int *output)
{

  struct termios t;
  int fd=open(path,O_RDONLY|O_NONBLOCK);
  tcgetattr(fd,&t);
  cfsetispeed(&t,bitrate);
  cfsetospeed(&t,bitrate);
  tcsetattr(fd,TCSANOW,&t);
  
  int fd2=open(path,O_WRONLY| O_TRUNC | O_NONBLOCK| O_CREAT,0666);
  tcgetattr(fd2,&t);
  cfsetispeed(&t,bitrate);
  cfsetospeed(&t,bitrate);
 
  tcsetattr(fd2,TCSANOW,&t);


  /**
    Pipe creation 
    used to abstract arduino as a file.
   */
  int writeToInterface[2];
  int readFromInterface[2];
  pipe(writeToInterface);
  pipe(readFromInterface);
  
  int pidfils;
  if((pidfils=fork())==0)
    {
      /**
	'main' process's pipes closed 
       */
      close(writeToInterface[1]);
      close(readFromInterface[0]);
      
      int n;
	char buffer[100];
	char bigbufferReception[1000];
	char bufferReception[100];
	int nbReception=0;
	int bigNbReception=0;
	
	while((n=read(writeToInterface[0],buffer,sizeof(char)*100))>0)
	  {
	    write(fd2,buffer,sizeof(char)*n);
	    while((nbReception=readFromArduino(fd,bufferReception,sizeof(char)*100))>0){
	      addToBuffer(bigbufferReception+bigNbReception,bufferReception,nbReception);
	      bigNbReception+=nbReception;

	    }
	    write(readFromInterface[1],bigbufferReception,sizeof(char)*bigNbReception);
	    if(DEBUG_EZ_ARDUINO==1){
	      	    write(2,bigbufferReception,sizeof(char)*bigNbReception);

	    }
	    bigNbReception=0;

	  }
	perror(strerror(errno));
	exit(1);
	
	//Pipe closed implicitly there

    }
  /*
    'interface' process's pipes closed
   */
  close(writeToInterface[0]);
  close(readFromInterface[1]);
  *input=writeToInterface[1];
  *output=readFromInterface[0];
  return pidfils;

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

