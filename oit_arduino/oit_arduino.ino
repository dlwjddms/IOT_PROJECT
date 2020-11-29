#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//buzzer number
const int BUZ = 10;
//set pin number
const int dp = 9;
const int APIN1 = 2;
const int APIN2 = 3;
const int APIN3 = 4;
const int APIN4 = 5;
const int APIN5 = 6;
const int APIN6 = 7;
const int APIN7 = 8;

LiquidCrystal_I2C lcd(0x3F, 16,3);
void setup(){

  //init segment
  pinMode(APIN1, OUTPUT);
  pinMode(APIN2, OUTPUT);
  pinMode(APIN3, OUTPUT);
  pinMode(APIN4, OUTPUT);
  pinMode(APIN5, OUTPUT);
  pinMode(APIN6, OUTPUT);
  pinMode(APIN7, OUTPUT);
  
lcd.init();
lcd.setCursor(2,0);
lcd.backlight();
lcd.print("20181149 LJE");
  Serial.begin(9600);
}
void do_lcd(){
    Serial.flush();  
  
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("20181149 LJE");
    lcd.setCursor(0,1);
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
    Serial.flush();
}
void do_seg(){

     Serial.flush();
     int seg = Serial.parseInt();
     switch(seg){
         case 0:
             digitalWrite(APIN1,HIGH);
             digitalWrite(APIN2,HIGH);
             digitalWrite(APIN3, HIGH); 
             digitalWrite(APIN4, HIGH);
             digitalWrite(APIN5, HIGH);
             digitalWrite(APIN6, HIGH);
             digitalWrite(APIN7, LOW);
             break;
          case 1:
             digitalWrite(APIN1,LOW);
             digitalWrite(APIN2,HIGH);
             digitalWrite(APIN3, HIGH); 
             digitalWrite(APIN4, LOW);
             digitalWrite(APIN5, LOW);
             digitalWrite(APIN6, LOW);
             digitalWrite(APIN7, LOW);
             break;
          case 2:
             digitalWrite(APIN1,HIGH);
             digitalWrite(APIN2,HIGH);
             digitalWrite(APIN3, LOW); 
             digitalWrite(APIN4, HIGH);
             digitalWrite(APIN5, HIGH);
             digitalWrite(APIN6, LOW);
             digitalWrite(APIN7, HIGH);
             break;
          case 3:             
             digitalWrite(APIN1,HIGH);
             digitalWrite(APIN2,HIGH);
             digitalWrite(APIN3, HIGH); 
             digitalWrite(APIN4, HIGH);
             digitalWrite(APIN5, LOW);
             digitalWrite(APIN6, LOW);
             digitalWrite(APIN7, HIGH);
             break;
          case 4:
             digitalWrite(APIN1,LOW);
             digitalWrite(APIN2,HIGH);
             digitalWrite(APIN3, HIGH); 
             digitalWrite(APIN4, LOW);
             digitalWrite(APIN5, LOW);
             digitalWrite(APIN6, HIGH);
             digitalWrite(APIN7, HIGH);
             break;
          case 5:
             digitalWrite(APIN1,HIGH);
             digitalWrite(APIN2,LOW);
             digitalWrite(APIN3, HIGH); 
             digitalWrite(APIN4, HIGH);
             digitalWrite(APIN5, LOW);
             digitalWrite(APIN6, HIGH);
             digitalWrite(APIN7, HIGH);
             break;
          case 6:
             digitalWrite(APIN1,HIGH);
             digitalWrite(APIN2,LOW);
             digitalWrite(APIN3, HIGH); 
             digitalWrite(APIN4, HIGH);
             digitalWrite(APIN5, HIGH);
             digitalWrite(APIN6, HIGH);
             digitalWrite(APIN7, HIGH);
             break;
          case 7:
             digitalWrite(APIN1,HIGH);
             digitalWrite(APIN2,HIGH);
             digitalWrite(APIN3, HIGH); 
             digitalWrite(APIN4, LOW);
             digitalWrite(APIN5, LOW);
             digitalWrite(APIN6, LOW);
             digitalWrite(APIN7, LOW);
             break;
          case 8:
             digitalWrite(APIN1,HIGH);
             digitalWrite(APIN2,HIGH);
             digitalWrite(APIN3, HIGH); 
             digitalWrite(APIN4, HIGH);
             digitalWrite(APIN5, HIGH);
             digitalWrite(APIN6, HIGH);
             digitalWrite(APIN7, HIGH);
             break;
          case 9:
             digitalWrite(APIN1,HIGH);
             digitalWrite(APIN2,HIGH);
             digitalWrite(APIN3, HIGH); 
             digitalWrite(APIN4, HIGH);
             digitalWrite(APIN5, LOW);
             digitalWrite(APIN6, HIGH);
             digitalWrite(APIN7, HIGH);
             break;
          default:break;
     }
     Serial.flush();
}

void do_buz(){
  Serial.flush();
  const int C = 261;
  const int D = 293;
  const int F = 349;
  const int G  = 392;
  int song [4]= { C,D,F,G};
  int fast[4]= {500, 500, 500, 1000};
  for(int i=0 ; i< sizeof(song)/sizeof(int); i++){
  tone(BUZ, song[i]);
    delay(fast[i]);
    noTone(BUZ);
    }
}
void loop(){
   if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    char idx = Serial.read();
    if(idx=='1'){

       do_buz();
    }
    else if(idx=='2'){
    // clear the screen
        do_lcd();    
    
    }
    else if(idx=='3'){

       do_seg();    
     
    }
  }
  


}
