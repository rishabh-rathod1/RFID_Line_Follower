#include <SPI.h>
#include <MFRC522.h>

#define LINESENSOR1 2
#define LINESENSOR2 8
#define BUZZER A0
#define MOTOR1A 5
#define MOTOR1B 4
#define MOTOR2A 6
#define MOTOR2B 7
#define RFID_SDA 10
#define RFID_SCK 13
#define RFID_MOSI 11
#define RFID_MISO 12
#define RFID_RST 9

#define STOP_TIME 3000
#define BEEP_LENGTH 200
#define MINIMUM_TIME_BETWEEN_CARDS 2000

MFRC522 mfrc522(10, 9);
long int last_card_read;

#define COMMANDS_LENGTH 4
char* Type[4]={"Stop", "Beep&stop", "Beep&ignore", "Stop"};
int Value[4]={3000, 1000, 0, 5000};
char* CardID[4]={"62 DE 2B 51", "59 7A 06 18", "ED B9 E0 2B", "83 87 3B 2E"};




void setup() {
 SPI.begin();  
 mfrc522.PCD_Init();    
  pinMode(LINESENSOR1, INPUT);
  pinMode(LINESENSOR2, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(MOTOR1A, OUTPUT);
  pinMode(MOTOR1B, OUTPUT);
  pinMode(MOTOR2A, OUTPUT);
  pinMode(MOTOR2B, OUTPUT);

}

void loop() {
  if(digitalRead(LINESENSOR1) == LOW && digitalRead(LINESENSOR2) == LOW ){
  Forward();
}
else if(digitalRead(LINESENSOR1) == LOW && digitalRead(LINESENSOR2) == HIGH ){
Left();
delay(20);
}
else if(digitalRead(LINESENSOR1) == HIGH && digitalRead(LINESENSOR2) == LOW ){
Right();
delay(20);
}
else if (digitalRead(LINESENSOR1)==HIGH && digitalRead(LINESENSOR2)==HIGH){
  Stop();
  delay(20);
}


if(millis() - last_card_read >= MINIMUM_TIME_BETWEEN_CARDS){

if ( ! mfrc522.PICC_IsNewCardPresent()){
    return;
  }

if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }


String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  content = content.substring(1);


for(int a = 0; a < COMMANDS_LENGTH; a++){
    last_card_read = millis();

if(content == CardID[a]){
      if(Type[a] == "Stop"){
        tone(BUZZER, 2000);
        Stop();
        delay(Value[a]);
        noTone(BUZZER);
      }else if(Type[a] == "Beep&stop"){
        tone(BUZZER, 2500);
        Stop();
        delay(Value[a]);
        noTone(BUZZER);
      }else if(Type[a] == "Beep&ignore"){
        Stop();
        tone(BUZZER, 950);
        delay(500);
        noTone(BUZZER);
      }else if(Type[a] == "Ignore"){
        
      }
  }
  }
}
}






void Forward(){
  digitalWrite(MOTOR1A, HIGH);
  digitalWrite(MOTOR1B,LOW);
  digitalWrite(MOTOR2A, HIGH);
  digitalWrite(MOTOR2B,LOW);

}

void Left(){
  analogWrite(MOTOR1A, 255);
  digitalWrite(MOTOR1B,LOW);
  analogWrite(MOTOR2A, 80);
  digitalWrite(MOTOR2B,LOW);
}

void Right(){
  analogWrite(MOTOR1A, 80);
  digitalWrite(MOTOR1B,LOW);
  analogWrite(MOTOR2A, 255);
  digitalWrite(MOTOR2B,LOW);
}

void Stop(){
  digitalWrite(MOTOR1A, LOW);
  digitalWrite(MOTOR1B, LOW);
  
  digitalWrite(MOTOR2A,LOW);
  digitalWrite(MOTOR2B, LOW);
}
