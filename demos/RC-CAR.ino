#include <Servo.h>

#include <Bridge.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
#include <BridgeSSLClient.h>
#include <BridgeUdp.h>
#include <Console.h>
#include <FileIO.h>
#include <HttpClient.h>
#include <Mailbox.h>
#include <Process.h>
#include <YunClient.h>
#include <YunServer.h>
// Left wheels
int motorLeft = 6;
int leftForward = 7;
int leftBackward = 8;

// Right wheels
int motorRight = 11;
int rightForward = 12;
int rightBackward = 13;

// Timer

Servo neck;
int pos = 90;


void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Serial.begin(9600);
  neck.attach(9);
  pinMode(motorLeft, OUTPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(motorRight, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  
  neck.write(pos);
  Serial.println('x'); 
}

void loop() {
  
  HttpClient client;
  client.get("https://api-project-133104497638.appspot.com/test");
  if (client.available()){
    char c = client.read();

    
    
    Serial.print(c);

    if (c == 'w'){
      forward(155);
      }
    if (c == 'a'){
      turnLeft();
      }
    if (c == 's'){
      backward(155);
      }
    if (c == 'd'){
      turnRight();
      }
    if (c == 'f'){
      brake();
      }
    if (c == 'q'){
      if (pos >0){
        pos = pos - 15;
        neck.write(pos);
        }
      }
    if (c == 'e'){
      if (pos < 180){
        pos = pos + 15;
        neck.write(pos);
        }
      }
    }
    Serial.flush();
    delay(500);
    
}

void forward(int motorSpeed){
  digitalWrite(leftForward, HIGH);
  digitalWrite(rightForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightBackward, LOW);
  analogWrite(motorLeft, motorSpeed);
  analogWrite(motorRight, motorSpeed);
  }

//S
void backward(int motorSpeed){
  digitalWrite(leftForward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightBackward, HIGH);
  analogWrite(motorLeft, motorSpeed);
  analogWrite(motorRight, motorSpeed);  
  }

//F
void brake(){
  digitalWrite(leftForward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightBackward, LOW);
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
  }

//A
void turnLeft(){
  digitalWrite(leftForward, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightBackward, LOW);
  analogWrite(motorLeft, 155);
  analogWrite(motorRight, 155);
  }

//D
void turnRight(){
  digitalWrite(leftForward, HIGH);
  digitalWrite(rightForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightBackward, HIGH);
  analogWrite(motorLeft, 155);
  analogWrite(motorRight, 155);
  }
