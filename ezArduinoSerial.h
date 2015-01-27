#ifndef EZ_ARDUINO_SERIAL_H
#define EZ_ARDUINO_SERIAL_H
#ifndef MAX_ARDUINO_BUFFER
#define MAX_ARDUINO_BUFFER 1000
#endif
#ifndef DEBUG_EZ_ARDUINO
#define DEBUG_EZ_ARDUINO 1
#endif
typedef struct ezArduinoSerial *EzArduinoSerial;
EzArduinoSerial createEzArduinoSerial(char*,int);
int readFromEzArduino(EzArduinoSerial,char*,int);
int readFromArduino(int,char*,int);
int linkWithArduino(char*,int,int *input,int *output); 
#endif
