// LIBRARIES
#include <LiquidCrystal.h>
#include <Wire.h>

// MACROS
#define buzzer 10
#define led 9

// GLOBAL VARIABLES
byte SlaveReceived;
String message="";
int value;
int totalScore=0;

// Initiating lcd
LiquidCrystal lcd(12,11,2,3,4,5);

// FUNCTIONS
// getName()
// printName()
// ledGlow()
// Buzzer()
// onTrue()
// onFalse()

// SERVICE HANDLERS
// sendEvent
// receiveEvent 

// prints the greeting message on lcd, and asks for user name
// waits until it get the username
void getName(){
	lcd.clear();
  	lcd.print("Hello");
  	lcd.setCursor(0,1);
  	lcd.print("Enter your name");
  	while(!Serial.available()){};
  	if (Serial.available()>0){
    		message = Serial.readString();
  	}
}

// prints the greeting and name on lcd
// after 3 seconds it clears the screen
void printName(String msg){
	lcd.clear();
  	lcd.print("hello");
    	lcd.setCursor(0,1);
    	lcd.print(message);
    	delay(100);
    	lcd.clear();
}

// glow the led
void ledGlow(){
  	analogWrite(led,255);
  	delay(200);
  	analogWrite(led,0);
  	delay(50);
}

// initiate buzzer
void Buzzer(){
	tone(buzzer,300);
	delay(25);
	noTone(buzzer);
	delay(25);
}


void sendEvent(){
  	Wire.write(int(1));
}
void receiveEvent (int howMany){
  	Serial.println("worked");
  	while(Wire.available()){
    		value = Wire.read();
  	}                  
}

// increase the score, print CORRECT on lcd with new Score
void onTrue(){
  	totalScore++;
  	lcd.clear();
  	lcd.print("CORRECT");
  	lcd.setCursor(0,1);
  	lcd.print("total Score ");
  	lcd.print(totalScore);
}

// print WRONG on lcd with old highest score of user
void onFalse(){
  	lcd.clear();
  	lcd.print("WRONG");
  	lcd.setCursor(0,1);
  	lcd.print("total Score ");
  	lcd.print(totalScore);
}

// 
void setup(){
  	Serial.begin(9600);
  	lcd.begin(16,2);
  	pinMode(buzzer,OUTPUT);
  	getName();
  	printName(message);
  	lcd.clear();
  	lcd.print("lets start");
  	Wire.begin(9);
  	Wire.onRequest(sendEvent);   
}
void loop(){
	delay(100);
	Wire.onReceive(receiveEvent);
    	Serial.println(value);
    	if (value==3){
      		onFalse();
      		Buzzer();
      		totalScore = 0;
    	}else if (value==2){
      		onTrue();
      		ledGlow();
    	}else{
      		Serial.println(value);
    	}
    value=0;
  } 
