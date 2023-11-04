#define MOTOR1A 9
#define MOTOR1B 8
void setup(){
  pinMode(MOTOR1A, OUTPUT);
  pinMode(MOTOR1B, OUTPUT);
}
void loop(){
 Forward();  
}
void Forward(){
  analogWrite(MOTOR1A , 110);
  digitalWrite(MOTOR1B, LOW);
}