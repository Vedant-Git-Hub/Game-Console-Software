default:
	echo "Use make gc to build and download the hex file to Atmega328p"

speaker.o: drivers/speaker.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/speaker.o drivers/speaker.c

pwm.o: drivers/pwm.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/pwm.o drivers/pwm.c

keypad.o: drivers/keypad.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/keypad.o drivers/keypad.c

7seg.o: drivers/7seg.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/7seg.o drivers/7seg.c

srdriver.o: drivers/srdriver.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/srdriver.o drivers/srdriver.c

glcd.o: drivers/glcd.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/glcd.o drivers/glcd.c

spi.o: drivers/spi.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/spi.o drivers/spi.c
#	avr-gcc -c -mmcu=atmega328p spi.c -o spi.o

app.o: Src/app.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/app.o Src/app.c

main.o: Src/main.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/main.o Src/main.c
#	avr-gcc -c -mmcu=atmeg328p  main.c -o main.o

gc: speaker.o pwm.o keypad.o 7seg.o srdriver.o glcd.o spi.o app.o main.o 
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p build/spi.o build/glcd.o build/srdriver.o build/7seg.o build/keypad.o build/pwm.o build/speaker.o build/main.o build/app.o -o build/gameConsole.elf
	avr-size -C -x build/gameConsole.elf
	avr-objcopy -O ihex -R .eeprom build/gameConsole.elf build/gameConsole.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:build/gameConsole.hex

clean:
	rm build/*.elf build/*.hex build/*.o
