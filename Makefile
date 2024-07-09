default:
	echo "Use make gc to build and download the hex file to Atmega328p"

glcd.o: glcd.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/glcd.o glcd.c

spi.o: spi.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/spi.o spi.c
#	avr-gcc -c -mmcu=atmega328p spi.c -o spi.o

main.o: main.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/main.o main.c
#	avr-gcc -c -mmcu=atmeg328p  main.c -o main.o

gc: glcd.o spi.o main.o 
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p build/main.o build/spi.o build/glcd.o -o build/gameConsole.elf
	avr-size -C -x build/gameConsole.elf
	avr-objcopy -O ihex -R .eeprom build/gameConsole.elf build/gameConsole.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:build/gameConsole.hex

clean:
	rm build/*.elf build/*.hex build/*.o
