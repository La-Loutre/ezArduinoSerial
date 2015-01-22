#include <stdio.h>
#include <stdlib.h>
#include "ezArduinoSerial.h"

int main(int argc,char **argv)
{
  /*  EzArduinoSerial ez=createEzArduinoSerial("/dev/ttyACM0",9600);
  writeToEzArduino(ez,"test d'un message plutot long a lire");
  char buffer[50];
  int i;
  for(i=0;i<10;i++){
    int nb=readFromEzArduino(ez,buffer,50*sizeof(char));
    write(1,buffer,nb*sizeof(char));
    }*/
  linkWithArduino("/dev/ttyACM0",9600);
  while(1);
}
