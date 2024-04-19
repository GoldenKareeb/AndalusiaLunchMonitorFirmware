#include <LiquidCrystal.h>

#include <SPI.h>

#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>

//pin def
#define LCD_PIN_RS	9
#define LCD_PIN_E	8
#define LCD_PIN_D4	4
#define LCD_PIN_D5	5
#define LCD_PIN_D6	6
#define LCD_PIN_D7	7
#define RFID_PIN_SDA 53
#define RFID_PIN_RST 10

//object init
MFRC522 mfrc522(RFID_PIN_SDA, RFID_PIN_RST);
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_E, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Establish connection with the computer at 9600 b/ps.
  while(!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  //LCD setup
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if (!mfrc522.PICC_IsNewCardPresent()) {
    lcd.setCursor(0, 0);
    lcd.print("I love ROBOTS");
		return;
	}

	// Select one of the cards
	if (!mfrc522.PICC_ReadCardSerial()) {
    lcd.setCursor(0, 0);
    lcd.print("I LOVE ROBOTS MORE");
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
