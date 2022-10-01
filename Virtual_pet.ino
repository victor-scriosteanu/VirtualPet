/*********************

Example code for the Adafruit RGB Character LCD Shield and Library

This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <EEPROM.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define TEAL 0x6

#define WHITE 0x7
int count;
int second;
long second1;
long second2;
int time;
int min;
int sec;
int s;
int m;
int t;
int happiness;
int stage;
int fullness;
int v;
int v1;
int v2;
boolean v3=false;
boolean v4=false;
void(* resetFunc) (void) = 0; 
void setup() {
  // Debugging output
  Serial.begin(9600);
  count = 0;
  second=0;
  second1 =0;
  second2=0;
  s= 0;
  m=0;
  t=0;
  happiness = 2;
  stage = 0;
  fullness =3;
  v=1;
  v1=1;
  v2=1;
  count = EEPROM.read(10);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.setBacklight(TEAL);
  
}
void displayBlink(int blinks, int duration)
{
  while(blinks--)
  {
    lcd.noDisplay();
    delay(duration);
    lcd.display();
    delay(duration); 
  }
}
void loop() {
  
  while(v3==false){
    if(count!=0){
      second=millis()/1000;
      lcd.setCursor(0,0);
      lcd.print("<- New Game     ");
      lcd.setCursor(0,1);
      lcd.print("-> Continue Game");
      
      uint8_t buttons = lcd.readButtons();
      if (buttons) {
        if (buttons & BUTTON_LEFT) {
          v3=true;
          lcd.clear();
        }
        if (buttons & BUTTON_RIGHT) {
          s = EEPROM.read(1);
          m = EEPROM.read(2);
          t = EEPROM.read(3);
          happiness = EEPROM.read(4);
          stage = EEPROM.read(5);
          fullness = EEPROM.read(6);
          v = EEPROM.read(7);
          v1 = EEPROM.read(8);
          v2 = EEPROM.read(9);
          displayBlink(3, 100);
          v3=true;
          lcd.clear();
          sec=0;
          min=0;
          time=0;
        }
        
      }
      
    }
    else{
      v3=true;
    }
  }
  
  unsigned long lastRun = millis();
  sec = millis()/1000+s-second-second1/1000; 
  min = millis()/1000+m-second-second1/1000;
  time = millis()/1000+t-second-second1/1000;
  
  
  uint8_t buttons = lcd.readButtons();
   if (buttons) {
    if (buttons & BUTTON_SELECT) {
      v4=false;
      second2 =  second1;
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("<-Restart ->Save");
      lcd.setCursor(0,0);
      lcd.print("^Del Down-Resume");
      while(v4==false){
        uint8_t buttons = lcd.readButtons();
        if(buttons & BUTTON_DOWN){
          v4=true;
        }
        if(buttons & BUTTON_LEFT){
          displayBlink(3, 100);
          resetFunc(); //call reset
        }
        if(buttons & BUTTON_RIGHT){
          EEPROM.write(1, sec);
          EEPROM.write(2, min);
          EEPROM.write(3, time);
          EEPROM.write(4, happiness);
          EEPROM.write(5, stage);
          EEPROM.write(6, fullness);
          EEPROM.write(7, v);
          EEPROM.write(8, v1);
          EEPROM.write(9, v2);
          EEPROM.write(10,time);
          displayBlink(3, 100);
        }
        if(buttons & BUTTON_UP){
          EEPROM.write(1, 0);
          EEPROM.write(2, 0);
          EEPROM.write(3, 0);
          EEPROM.write(4, 2);
          EEPROM.write(5, 0);
          EEPROM.write(6, 3);
          EEPROM.write(7, 1);
          EEPROM.write(8, 1);
          EEPROM.write(9, 1);
          EEPROM.write(10, 0);
          displayBlink(3, 100);
        }
        second1=millis()- lastRun+second2;
      }
      lcd.clear();
      displayBlink(2, 100);
    }
    if (buttons & BUTTON_UP) {
      if(stage>=1){
        if(fullness==3){
          happiness=0;
        }
        if(fullness<=3){
          fullness++;
          displayBlink(2, 100);
        }
      }
    }
    
    if (buttons & BUTTON_LEFT) {
      if(time>=35 & happiness >=1 & fullness >=3 & stage==1){
        stage=2;
        displayBlink(2, 100);
      }
    }
    if (buttons & BUTTON_RIGHT) {
      if(fullness>=2 & happiness<2){
        happiness++;
        displayBlink(2, 100);
      }
    }
    if (buttons & BUTTON_DOWN) {
      EEPROM.write(1, sec);
      EEPROM.write(2, min);
      EEPROM.write(3, time);
      EEPROM.write(4, happiness);
      EEPROM.write(5, stage);
      EEPROM.write(6, fullness);
      EEPROM.write(7, v);
      EEPROM.write(8, v1);
      EEPROM.write(9, v2);
      EEPROM.write(10,time);
      displayBlink(3, 100);
    }
  }
  if(stage>2){
    stage=2;
  }
  if(stage<0){
    stage=0;
  }
  if(happiness>2){
    happiness=2;
  }
  if(happiness<0){
    happiness=0;
  }
  if(fullness>4){
    fullness=4;
  }
  if(fullness<0){
    fullness=0;
  }
  if(fullness==0){
    lcd.setCursor(7,0);
    lcd.print("^Ravenous");
  }
  if(fullness==1){
    lcd.setCursor(7,0);
    lcd.print("^Hungry  ");
  }
  if(fullness==2){
    lcd.setCursor(7,0);
    lcd.print("^Peckish ");
  }
  if(fullness==3){
    lcd.setCursor(7,0);
    lcd.print("^Full    ");
  }
  if(fullness==4){
    lcd.setCursor(7,0);
    lcd.print("^Overfull");
  }
  if(stage==0){
    lcd.setCursor(0,1);
    lcd.print("<-Egg");
  }
  if(stage==1){
    lcd.setCursor(0,1);
    lcd.print("<-Young");
  }
  if(stage==2){
    lcd.setCursor(0,1);
    lcd.print("<-Adult");
  }
  if(happiness==0){
    lcd.setCursor(7,1);
    lcd.print("->Unhappy");
  }
  if(happiness==1){
    lcd.setCursor(7,1);
    lcd.print("->Content");
  }
  if(happiness==2){
    lcd.setCursor(7,1);
    lcd.print("->Happy  ");
  }
  if((time-5)%7==0 && v==(time-5)/7 && (time-5)!=0){
    v++;
    happiness--;
  }
  if(sec%5==0 && v1==sec/5 && sec!=0){
    v1=1;
    stage=1;
  }
  if((time-5)%11==0 && v2==(time-5)/11 && (time-5)!=0){
    v2++;
    fullness--;
  }
  if(fullness==0){
    happiness=0;
  }
  while(sec>=60){
    sec = sec -60; 
  }
  if(sec%60==0){
    lcd.setCursor(3,0);
    lcd.print(" ");
  }
  while(min>=600){
    min = min -600;
  }
  lcd.setCursor(0, 0);
  lcd.print(min/60);
  lcd.setCursor(1,0);
  lcd.print(":");
  lcd.setCursor(2,0);
  lcd.print(sec);
  lcd.setCursor(2,0);
  lcd.print(sec);
  if(time==599){
    lcd.setCursor(0, 0);
    lcd.print("   Game Over    ");
    lcd.setCursor(0, 1);
    lcd.print("  Well played!  ");
    delay(5000);
    resetFunc();
  }
  
}
