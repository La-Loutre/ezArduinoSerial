#ifndef EZ_ARDUINO_SERIAL_H
#define EZ_ARDUINO_SERIAL_H
typedef struct ezArduinoSerial *EzArduinoSerial;
EzArduinoSerial createEzArduinoSerial(char*,int);
int readFromEzArduino(EzArduinoSerial,char*,int);
int readFromArduino(int,char*,int);
#endif
