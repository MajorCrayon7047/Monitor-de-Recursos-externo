#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
byte customChar[] = {B01100,B10010,B10010,B01100,B00000,B00000,B00000,B00000};

String CPU;
String RAM;
String RamGb;
String DISK;
String TEMP;

const unsigned int MAX_LENGTH = 14;
static char message[MAX_LENGTH];
static unsigned int message_pos = 0;

unsigned long delai;
unsigned long ultima = 0;

void readSerialData(){
  while(Serial.available() > 0){
    char inByte = Serial.read();
    if (inByte !="\n" && (message_pos < MAX_LENGTH - 1)){
      message[message_pos] = inByte;
      message_pos++;
    }
    else{
      message[message_pos] = "\0";
      Serial.println(message);

      CPU = String(message[0]) + String(message[1]) + String(message[2]);
      RAM = String(message[3]) + String(message[4]) + String(message[5]);
      RamGb = String(message[6]) + String(message[7]) + String(message[8]) + String(message[9]);
      TEMP = String(message[10]) + String(message[11]) + String(message[12]);
        
      message_pos = 0;
    }
  }
}


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.createChar(0, customChar);
  lcd.backlight();
  //Serial.setTimeout(10);
}

void loop() {
  readSerialData();
  
  delai = millis();
  if(delai >= ultima){
    ultima = delai + 3000;
    lcd.setCursor(0,0);
    lcd.print("CPU:    %    c");
    lcd.setCursor(14,0);
    lcd.write(0);
    lcd.setCursor(5,0);
    lcd.print(CPU.toInt());
    lcd.setCursor(10,0);
    lcd.print(TEMP.toInt());

    lcd.setCursor(0,1);
    lcd.print("RAM:    %     Gb");
    lcd.setCursor(5,1);
    lcd.print(RAM.toInt());
    lcd.setCursor(10,1);
    lcd.print(RamGb.toFloat());
    lcd.setCursor(14,1);
    lcd.print("Gb");
    /*
    Serial.print("CPU:  ");
    Serial.print(CPU);
    Serial.println("%");
    Serial.print("RAM:  ");
    Serial.print(RAM);
    Serial.println("%");
    Serial.print("Ram in GB:  ");
    Serial.print(RamGb);
    Serial.println("Gb");
    Serial.print("CPU temp:  ");
    Serial.print(TEMP);
    Serial.println("°C");
    */
  }
}
