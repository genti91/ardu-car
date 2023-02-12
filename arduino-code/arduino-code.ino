#include "configuration.h"
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 35
#define TRIG_PIN2 A2 
#define ECHO_PIN2 A3

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar2(TRIG_PIN2, ECHO_PIN2, MAX_DISTANCE); 

Servo myservo;

/*motor control*/
void go_Advance(void)  //Forward
{
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
}
void go_Left(void)  //Turn left
{
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void go_Right(void)  //Turn right
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
}
void go_Back(void)  //Reverse
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void stop_Stop()    //Stop
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,LOW);
}

/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(speedPinL,speed_L); 
  analogWrite(speedPinR,speed_R);   
}

//Pins initialize
void init_GPIO()
{
  pinMode(dir1PinL, OUTPUT); 
  pinMode(dir2PinL, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
 
  pinMode(dir1PinR, OUTPUT);
  pinMode(dir2PinR, OUTPUT); 
  pinMode(speedPinR, OUTPUT); 
  stop_Stop();
}

String rx="";
String command="";
unsigned long prevTime = millis();
unsigned long prevTime2 = millis();
int thisNote = 0;
bool playing = false;
bool song = false;
int interval = 0;

void setup() {
  Serial.begin(9600);
  init_GPIO();
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  delay(50);
}

void loop() {
  
  unsigned long currentTime = millis();
  int distance = sonar.ping_cm();
  int distance2 = sonar2.ping_cm();

  if(distance == 0){
    distance = 50;
  }
  if(distance2 == 0){
    distance2 = 50;
  }
  if((distance < 25 || distance2 < 25) && command == "up"){
    stop_Stop();
  }


  if (Serial.available() > 0) {
    rx = Serial.readStringUntil("\n");
    Serial.println(rx);

    if(rx == "Up" && command == ""){
      Serial.println("Moving Forward");
      go_Advance();
      set_Motorspeed(255,255);
      prevTime = currentTime;
      command = "up";
    }
    if(rx.startsWith("-w") && command == ""){
      Serial.println("moving -w");
      int spaceIndex = rx.indexOf(' ');
      String numberString = rx.substring(spaceIndex + 1);
      Serial.println(numberString.toInt());
      interval = numberString.toInt();
      go_Advance();
      set_Motorspeed(255,255);
      prevTime = currentTime;
      command = "up";
    }
    if(rx == "Down" && command == ""){
      Serial.println("Moving Back");
      go_Back();
      set_Motorspeed(255,255);
      prevTime = currentTime;
      command = "down";
    }
    if(rx.startsWith("-s") && command == ""){
      Serial.println("moving -s");
      int spaceIndex = rx.indexOf(' ');
      String numberString = rx.substring(spaceIndex + 1);
      Serial.println(numberString.toInt());
      interval = numberString.toInt();
      go_Back();
      set_Motorspeed(255,255);
      prevTime = currentTime;
      command = "down";
    }
    if(rx == "Left" && command == ""){
      Serial.println("Moving Left");
      go_Left();
      set_Motorspeed(255,255);
      prevTime = currentTime;
      command = "left";
    }
    if(rx.startsWith("-a") && command == ""){
      Serial.println("moving -a");
      int spaceIndex = rx.indexOf(' ');
      String numberString = rx.substring(spaceIndex + 1);
      Serial.println(numberString.toInt());
      interval = numberString.toInt();
      go_Left();
      set_Motorspeed(255,255);
      prevTime = currentTime;
      command = "left";
    }
    if(rx == "Right" && command == ""){
      Serial.println("Moving Right");
      go_Right();
      set_Motorspeed(255,255);
      prevTime = currentTime;
      command = "right";
    }
    if(rx.startsWith("-d") && command == ""){
      Serial.println("moving -d");
      int spaceIndex = rx.indexOf(' ');
      String numberString = rx.substring(spaceIndex + 1);
      Serial.println(numberString.toInt());
      interval = numberString.toInt();
      go_Right();
      set_Motorspeed(255,255);
      prevTime = currentTime;
      command = "right";
    }
    if(rx == "on"){
      Serial.println("Led On");
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
    }
    if(rx == "off"){
      Serial.println("Led Off");
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    }
    if(rx == "open"){
      Serial.println("Gripper Opened");
      myservo.attach(9);
      myservo.write(180);
      delay(300);
      myservo.detach();
    }
    if(rx == "close"){
      Serial.println("Gripper Closed");
      myservo.attach(9);
      myservo.write(0);
      delay(500);
      myservo.detach();
    }
    if(rx == "song"){
      song = true;
      thisNote = 0;
      prevTime2 = currentTime;
    }
    if(rx == "song_stop"){
      song = false;
    }
  }
  if(command == "up" || command == "down"){
    int delay = 1500;
    if (interval > 0) {
      delay = interval;
    }
    if(millis() - prevTime > delay){
      stop_Stop();
      Serial.println("Stop");
      command = "";
      interval = 0;
    }
  }
  if(command == "left" || command == "right"){
    int delay = 1100;
    if (interval > 0) {
      delay = interval;
    }
    if(currentTime - prevTime > delay){
      stop_Stop();
      Serial.println("Stop");
      command = "";
      interval = 0;
    }
  }

  if(song == true){
    /*if(currentTime - prevTime2 > noteDuration){
      noTone(buzzer);
      thisNote = thisNote + 2;
      playing = false;
      prevTime2 = currentTime;
      //Serial.println(thisNote);
      if(thisNote > (sizeof(melody)/2)){
        song = false;
      }
    }
    if(thisNote < notes * 2 && playing == false){
      playing = true;
      divider = melody[thisNote + 1];
      //divider = pgm_read_word_near(melody+thisNote + 1);
      if (divider > 0) {
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;
      }
      tone(buzzer, melody[thisNote], noteDuration*0.9);
      //tone(buzzer, pgm_read_word_near(melody+thisNote), noteDuration * 0.9);
    }*/
  }
}