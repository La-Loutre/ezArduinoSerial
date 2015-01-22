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
  /*TODO
    Mettre en place 2 pipe pour que l'on puisse ecrire depuis ce processus dans un pipe que linkWith arduino renverra au arduino et un autre pipe dans lequel on pourra lire et qui contiendra les réponse du arduino ( récupéré depuis le arduino et mises dans le pipe depuis le processus linkWithArduino ) .
   */
  while(1);
}
