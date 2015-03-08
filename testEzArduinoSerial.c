#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ezArduinoSerial.h"

int main(int argc,char **argv)
{
   int input,output;
   //int childPid=linkWithArduino("/dev/ttyACM0",9600,&input,&output);
   /*   char buffer[MAX_ARDUINO_BUFFER];
  int readFromKeyboard;
   int readFromArduino;
   while((readFromKeyboard=read(0,buffer,sizeof(char)*MAX_ARDUINO_BUFFER))>0){
     write(input,buffer,sizeof(char)*readFromKeyboard);
     if((readFromArduino=read(output,buffer,sizeof(char)*MAX_ARDUINO_BUFFER))>0)
	 write(1,buffer,sizeof(char)*readFromArduino);
    
	 }*/
   //   printf("test\n");
   //   if((readFromArduino=read(output,buffer,sizeof(char)*MAX_ARDUINO_BUFFER))>0){
   //	 write(1,buffer,sizeof(char)*readFromArduino);
   //    }
   //   delinkArduino(childPid);
   char *txt="azertyuiop";
   write(1,&txt,strlen(txt));
   char buffer[1000];
   read(0,&buffer,sizeof(char)*1000);
   fprintf(stderr,"%s",buffer);
   return EXIT_SUCCESS;
}
