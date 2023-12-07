#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 53
#define RST_PIN 5
#define LED_G 6 //define green LED pin
#define LED_R 4 //define red LED
#define BUZZER 2 //buzzer pin
#define Peyas "71 1E A3 C3" // define main card with uid
#define Swapnil "43 EA 0D 32" // define card1 with uid
#define Rimi "6B D3 99 1B" // difine tag with uid

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name


 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();

}


void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
  if (content.substring(1)== Peyas)
   {
    Serial.println ("Name: Ismot Sadik Peyas");
   }
   
   else if (content.substring(1) == Swapnil)
   {
   Serial.println ("Name: Swapnil kar");
   }
   else if (content.substring(1) == Rimi )
   {
   Serial.println ("Name: Rimi");
   }
   else
   {
   Serial.println("Name:______________");
    }

   
  
  Serial.println();
  Serial.print("Message : ");

  if (content.substring(1) == Peyas || content.substring(1) == Swapnil || content.substring(1) == Rimi ) //change here the UID of the card/cards  to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
    myServo.write(180);
    delay(5000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
  }
 
 else   {
    Serial.println(" Access denied");
    Serial.println();
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
  }
}
