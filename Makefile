CC=avr-gcc
FREQ=-DF_CPU=16000000UL
MCU=-mmcu=atmega328p
OBJECTS=build/spi.o build/glcd.o build/srdriver.o build/7seg.o build/keypad.o build/pwm.o build/speaker.o build/main.o build/common.o build/app.o build/startupscreen.o build/menumanager.o
ELFS=build/gameConsole.elf
HEX=build/gameConsole.hex

PROGRAMER=arduino
UC=ATMEGA328P
DEVICE=/dev/ttyACM0
BAUD=115200


default:
	echo "Use make gc to build and download the hex file to Atmega328p"

speaker.o: drivers/speaker.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/speaker.o drivers/speaker.c

pwm.o: drivers/pwm.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/pwm.o drivers/pwm.c

keypad.o: drivers/keypad.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/keypad.o drivers/keypad.c

7seg.o: drivers/7seg.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/7seg.o drivers/7seg.c

srdriver.o: drivers/srdriver.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/srdriver.o drivers/srdriver.c

glcd.o: drivers/glcd.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/glcd.o drivers/glcd.c

spi.o: drivers/spi.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/spi.o drivers/spi.c
	
menumanager.o: Src/Apps/menumanager.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/menumanager.o Src/Apps/menumanager.c

startupscreen.o: Src/Apps/startupscreen.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/startupscreen.o Src/Apps/startupscreen.c

app.o: Src/app.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/app.o Src/app.c

common.o: Src/common.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/common.o Src/common.c

main.o: Src/main.c
	$(CC) -Os $(FREQ) $(MCU) -c -o build/main.o Src/main.c

gc: speaker.o pwm.o keypad.o 7seg.o srdriver.o glcd.o spi.o menumanager.o startupscreen.o app.o common.o main.o 
	$(CC) -Os $(FREQ) $(MCU) $(OBJECTS) -o $(ELFS)
	avr-size -C -x $(ELFS)
	avr-objcopy -O ihex -R .eeprom $(ELFS) $(HEX)
	sudo avrdude -F -V -c $(PROGRAMER) -p $(UC) -P $(DEVICE) -b $(BAUD) -U flash:w:$(HEX)

clean:
	rm $(OBJECTS) $(ELFS) $(HEX)
