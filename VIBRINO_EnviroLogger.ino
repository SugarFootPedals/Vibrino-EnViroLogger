// Nov. 12, 2019 VIBRATO, LLC.
// VIBRINO arduino-compatible custom circuit board, with the ATmega328 and
// extra features; RTC DS1307, uSD Card Connector for Datalogging, i2C Connector (used here
// for the BME280 module), OLED i2C Connector, ISP Connector for burning the Uno Bootloader,
// easy access to all other pins (except Pin10, used for SD Card ChipSelect).
//
// Started off with code from Engineers Portal for SD Card Logging of BME280 Sensor on GitHub: 
// https://github.com/engineersportal/arduino_sd_saver
// then incorporated code from the Arduino library examples.
//
// If anything us unique, I added a "String" to the OLED display code to keep everything in line.
//
// Starts Logging to SD Card (Sensor Readings and TimeStamp) after boot on Power Up. Oled displays Sensor Readings and Date.
// Starts a new File on each Power Up, without erasing the older files.
// Writes to SD Card approx. every Second, which can be increased through the "delay()"
// Code is Open Source.

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "RTClib.h"
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"


#define SSD1306_I2C_ADDRESS 0x3C
#define RST_PIN -1
#define Adafruit_BME280_ADDRESS 0x76

SSD1306AsciiWire oled;

RTC_DS1307 rtc;

File main_folder; // initialize folder for saving
File dataFile; // initialize sd file
const int chipSelect = 10; // CS pin on sd card module
int prev_file_indx = 0; // used for file naming
String fileName = "000";

Adafruit_BME280 bme; // start BME sensor


void setup() {

  Wire.begin();
//  Wire.setClock(400000L);

#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, SSD1306_I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, SSD1306_I2C_ADDRESS);
#endif // RST_PIN >= 0

  // verfy RTC is running

  Serial.begin(9600);

   rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // verify BME280 is working

  bool status;
  status = bme.begin();
  if (!status) {
    while (1);
  }

  // verify SD card is working

  if (!SD.begin(chipSelect)) {
    return;
  }
  main_folder = SD.open("/");
  fileName = sd_saver(main_folder);


}

void loop() {

  DateTime time = rtc.now();

  //OLED DISPLAY

  oled.setFont(Callibri15);
  oled.clear();
  oled.println(String("TempC:     ") +bme.readTemperature());
  oled.println(String("mBar:      ") +bme.readPressure()/ 100);
  oled.println(String("Hum:         ") +bme.readHumidity());
  oled.println(String("Date:      ")+time.timestamp(DateTime::TIMESTAMP_DATE));
  delay(500);

  // SD save section in CSV format

  String data_array = "";
  
  data_array += String(String("TIMESTAMP:  ")+time.timestamp(DateTime::TIMESTAMP_FULL)); //RTC Time Stamp
  data_array += ",  ";

  data_array += String(bme.readTemperature()); // save temp in degrees Celsius
  data_array += "C";
  data_array += ",";
  data_array += String(bme.readHumidity()); // save humidity
  data_array += "%";
  data_array += ",";
  data_array += String(bme.readPressure() / 100); // save pressure in Pa, divided by 100 for Absolute Pressure(LSS)
  data_array += "mB";

  // SD Card writing and saving
  dataFile = SD.open("DATA" + fileName + ".csv", FILE_WRITE);
  // if the file is valid, write to it:
  if (dataFile) {
    dataFile.println(data_array);
    dataFile.close();
  }
  delay(500);
}


String sd_saver(File dir) {
  while (true) {
    // iterate all files to ensure no overwrites
    File entry = dir.openNextFile();
    if (!entry) {
      break;
    }
    // naming routine
    String entry_name = entry.name();
    if ((entry_name.substring(4, 7)).toInt() >= prev_file_indx) {
      prev_file_indx = (entry_name.substring(4, 7)).toInt() + 1;
      if (prev_file_indx >= 100) {
        fileName = String(prev_file_indx);
      } else if (prev_file_indx >= 10) {
        fileName = "0" + String(prev_file_indx);
      } else {
        fileName = "00" + String(prev_file_indx);
      }
    }
    entry.close();
  }
  return fileName;
}
