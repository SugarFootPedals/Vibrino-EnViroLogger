VIBRINO EnViroLogger =

An Arduino-compatible circuit board with many extras added for convenience.

I originally built this to be used in Paranormal Investigations, to
LOG Environmental Changes that occur during Paranormal Events.
Of course, it can be used for other purposes too !

The microprocessor is the ATmega328A - same as the original Uno, Nano and ProMini.

I was able to succesfully burn the Uno bootloader to the Atmega328A. ISP Pins on board !

Because the memory on the ATmega328 is very limited, I used the 
SSD1306Ascii.h library for the OLED DISPLAY, otherwise there would
not have been enough memory to run this Sketch!

There is access to all pins, except pin10, which is dedicated to the micro SD Card .
FTDI Pins are in-line with the 0.1 inch connectors.

Up to +10 volts MAX can be used to power, but works
fine with a +3.7 volt LiPo Battery too.

Power Supply has a +5 volt Regulator AND a +3.3 volt Regulator !

Added two extra i2C connectors for an i2C Display (OLED) and an i2C Sensor (BME280).

Real-Time Clock IC (RTC) and uSD Card for Datalogging. CR1220 Backup Battery Holder.

I have included an Arduino Sketch (.ino) that works! 
It reads a (generic) BME280 Barometric Sensor, displays the Temperature/Barometric Pressure/Humidity/Date(timestamp) on an OLED Display (mounted on bottom of the board), then LOGS this information onto a microSD Card with Timestamp in CSV format (comma seperated values). 
An added plus is that it starts a new Data File after powering up without erasing the previous File!

There are two LEDs on the board marked as PWR (RED) and 
SCK (BLUE).

All surface-mount components (Capacitors, Resistors and LEDs) are 1206 size.

CR1220 Battery Holder = Digikey #BK-890-ND
RTC 32.768 Khz Crystal = Digikey #535-9034-ND
16MHz Resonator = Digikey #490-17948-6-ND
5 volt Regulator = Digikey #MCP1802T-5002I/OTCT-ND
3.3 volt Regulator = Digikey #AP2120N-3.3TRG1DICT-ND
Reset Switch = Digikey #CKN10688CT-ND
Power Switch = Digikey #563-1091-1-ND
uSD Connector = Digikey #WM14405CT-ND
Microprocessor = Digikey #ATmega328P-AU-ND
RTC IC DS1307 = Digikey #DS1307ZN+T&RCT-ND

