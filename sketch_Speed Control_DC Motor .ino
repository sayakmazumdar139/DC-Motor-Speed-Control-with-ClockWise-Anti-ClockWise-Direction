#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define PRESET  A0  
#define Motor_Forward A1 
#define Motor_Stop A2 
#define Motor_Back A3 

#define Motor_ENB 11 
#define Motor_IN4 10 
#define Motor_IN3 9  

int Read_Value =0;
int Speed;
int Speed_LCD;
int Value = 0;

void setup(){
Serial.begin(9600);// initialize serial communication at 9600 bits per second:

pinMode(PRESET, INPUT);

pinMode(Motor_Forward, INPUT_PULLUP);
pinMode(Motor_Stop, INPUT_PULLUP);
pinMode(Motor_Back, INPUT_PULLUP);

pinMode(Motor_ENB, OUTPUT);
pinMode(Motor_IN4, OUTPUT);
pinMode(Motor_IN3, OUTPUT);

lcd.begin(16,2);  
lcd.setCursor(0,0);
lcd.print(" Speed Control ");
lcd.setCursor(0,1);
lcd.print("  DC Motor  ");
delay(2000); // Waiting for a while
lcd.clear();
}

void loop(){ 
Read_Value = analogRead(PRESET);
Speed = map(Read_Value, 0, 670, 0, 250);  
Speed_LCD = map(Read_Value, 0, 670, 0, 100); 

analogWrite(Motor_ENB, Speed);

lcd.setCursor(0,0);
lcd.print("Speed: ");
lcd.print(Speed_LCD); 
lcd.print("%  ");

if(digitalRead (Motor_Forward) == 0){Value = 1;}
if(digitalRead (Motor_Stop) == 0){Value = 0;}
if(digitalRead (Motor_Back) == 0){Value = 2;}


lcd.setCursor(0,1);

if(Value==0){ lcd.print("      Stop      ");
digitalWrite(Motor_IN4, LOW);  
digitalWrite(Motor_IN3, LOW);
}

if(Value==1){ lcd.print("    Anticlockwise   ");
digitalWrite(Motor_IN4, HIGH);  
digitalWrite(Motor_IN3, LOW);
}

if(Value==2){ lcd.print("     Clockwise      ");
digitalWrite(Motor_IN4, LOW);  
digitalWrite(Motor_IN3, HIGH);
}

delay(50); 
}

