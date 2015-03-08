CFLAGS=-g
all:testEzArduinoSerial autoLinkWith
	cp ezArduinoSerial.h ../../include
	ar -cr ../../lib/libezArduinoSerial.a ezArduinoSerial.o
autoLinkWith: autoLinkWith.o ezArduinoSerial.o

testEzArduinoSerial : testEzArduinoSerial.o ezArduinoSerial.o

ezArduinoSerial.o: ezArduinoSerial.c ezArduinoSerial.h 

testEzArduinoSerial.o : testEzArduinoSerial.c ezArduinoSerial.h

autoLinkWith.o: autoLinkWith.c ezArduinoSerial.h