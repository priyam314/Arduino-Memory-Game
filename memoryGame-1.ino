// LIBRARIES
#include <Wire.h>
#include <Keypad.h>

// GLOBAL VARIABLES
char RANDOM[10]={'0','1','2','3','4','5','6','7','8','9'};
char DIGIT[100];
int temp;
int indexDigit=0;

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 3; //number of columns on the keypad
//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3'}, 
{'4', '5', '6'}, 
{'7', '8', '9'},
{'*', '0', '#'}
};
//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {7,6,A3,8}; //Rows 0 to 3
byte colPins[numCols]= {A2,A1,A0}; //Columns 0 to 2

// MACROS 
#define segA 12
#define segB 13
#define segC 3
#define segD 4
#define segE 5
#define segF 11
#define segG 10
#define row1 7
#define row2 6
#define row3 A3
#define row4 8
#define col1 A2
#define col2 A1
#define col3 A0

//FUNCTIONS
// set()
// glowSegment()
// generateRandomInt()

// set seven segment display value
void set(int a,int b,int c,int d,int e,int f,int g){
  digitalWrite(segA,a);
  digitalWrite(segB,b);
  digitalWrite(segC,c);
  digitalWrite(segD,d);
  digitalWrite(segE,e);
  digitalWrite(segF,f);
  digitalWrite(segG,g);
}

void print(String msg,int val){
  Serial.print(msg);
  Serial.println(val); 
}
void printM(String msg){
	Serial.println(msg);
}

// Enables the seven segment display
void glowSegment(int count){
  switch(count){
  	case 0:
    	set(1,1,1,1,1,1,0);
    	break;
    case 1:
    	set(0,1,1,0,0,0,0);
    	break;
    case 2:
    	set(1,1,0,1,1,0,1);
    	break;
    case 3:
    	set(1,1,1,1,0,0,1);
    	break;
    case 4:
    	set(0,1,1,0,0,1,1);
    	break;
    case 5:
    	set(1,0,1,1,0,1,1);
    	break;
    case 6:
    	set(1,0,1,1,1,1,1);
    	break;
    case 7:
    	set(1,1,1,0,0,0,0);
    	break;
    case 8:
    	set(1,1,1,1,1,1,1);
    	break;
    case 9:
    	set(1,1,1,1,0,1,1);
    	break;
  }
}

// generates the random number between -1,10
// sets it to DIGIT[indexDigit] then glowSegment()
// increments the indexDigit;
int generateRandomInt(){
  printM("\n");
  printM("generateRandom init");
  long value = random(10);
  print("random value : ",int(value));
  DIGIT[indexDigit] = RANDOM[value];
  print("DIGIT[indexDigit] : ",DIGIT[indexDigit]);
  glowSegment(value);
  print("segment glow with : ",int(value));
  print("indexDigit : ",indexDigit);
  indexDigit++;
  printM("generateRandome ends");
}

// INSTANCE
//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

int finally(){
  printM("\n");
  printM("finally init");
  int i=0;
  while(i<indexDigit){
    print("i : ",i);
    char key = myKeypad.getKey();
    while(!key){	key = myKeypad.getKey();	}
    print("keyPad : ",key);
    if (DIGIT[i]!=key){	
      print("finally returned ",-1);
      return -1;	
    }
    i++;
    print("i updated to : ",i);
  }
  print("finally returned ",1);
  printM("finally end ");
  return 1;
}


void setup(){
  Serial.begin(9600);
  pinMode(segB, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(row4, INPUT);
  pinMode(row1, INPUT);
  pinMode(row2, INPUT);
  pinMode(segE, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(col3, INPUT);
  pinMode(col2, INPUT);
  pinMode(col1, INPUT);
  pinMode(row3, INPUT);
  Wire.begin(9);
}
void wireTransmit(int k){
  Wire.beginTransmission(9);
  Wire.write(int(k));
  Wire.endTransmission();
}
void sendEvent(int howmany){
  Wire.write(howmany);
}
void receiveEvent(int howmany){
  while(1<Wire.available()){
    temp = Wire.read();
  }
}
void loop(){
  print("",0);
  print("void loop init : ",indexDigit);
  Wire.requestFrom(9,2);
  print("requested from slave ", 1000);
  while(Wire.available()>1){
    temp = Wire.read();/* read data received from slave */
  }
  print("from slave to master : ",temp);
  if (temp==1){
    print("ENTERED, temp was : ",temp);
  	while(indexDigit<100){
      Wire.beginTransmission(9);
      generateRandomInt();
      if(finally()==-1){
        print("finally was -1, transmitted : ",3);
        Wire.write(int(3));
        indexDigit=0;
      }else{
        print("finally was 2, transmitted : ",2);
        Wire.write(int(2));
      }
    Wire.endTransmission();
    }
  }
} 