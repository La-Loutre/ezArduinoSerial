all:testEzArduinoSerial autoLinkWith

autoLinkWith: autoLinkWith.o ezArduinoSerial.o

testEzArduinoSerial : testEzArduinoSerial.o ezArduinoSerial.o

ezArduinoSerial.o: ezArduinoSerial.c ezArduinoSerial.h 

testEzArduinoSerial.o : testEzArduinoSerial.c ezArduinoSerial.h

autoLinkWith.o: autoLinkWith.c ezArduinoSerial.h