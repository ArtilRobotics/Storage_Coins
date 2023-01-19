#include "Adafruit_Keypad.h"


const byte ROWS = 4; // rows
const byte COLS = 4; // columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'D','C','B','A'},
  {'#','9','6','3'},
  {'0','8','5','2'},
  {'*','7','4','1'}
};
byte rowPins[ROWS] = {46, 47, 48, 49}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {50, 51, 52, 53}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

////////////////
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10  // Number of snowflakes in the animation example

/////////////////////////////////////
int uncent_g = 0;
int diezcent_g = 0;
int cincocent_g = 0;
int vnt_cincocent_g = 0;
int cnta_g = 0;
int undolar_g = 0;

int uncent = 0;
int diezcent = 0;
int cincocent = 0;
int vnt_cincocent = 0;
int cnta = 0;
int undolar = 0;

int beforeReaduncent = 1;
int beforeReaddiezcent = 1;
int beforeReadcincocent = 1;
int beforeReadvnt_cincocent = 1;
int beforeReadcnta = 1;
int beforeReadundolar = 1;

int PIN1C=2;
int PIN10C=3;
int PIN5C=4;
int PIN25C=5;
int PIN50C=6;
int PIN100C=7;

float val_1=0.3;

int CAJM=8;
int CAJ1=9;
int CAJ2=10;
int CAJ3=11;

///////////////////////////////

double tma=0.1;

int tmas=tma*1000;

unsigned long lastTime, sampleTime = tmas;

double tma2=0.25;

int tmas2=tma2*1000;

unsigned long lastTime2, sampleTime2 = tmas2;

 char message;
 char message_or;

bool stringComplete = false;

float sum;
float sum_a;
float sum_g;

bool countStatus=false;

void setup() {

  Serial.begin(9600); 
  unitScreen();
  initKeyboard();
  initContador();
  ResetCount();
  
}
void loop() {
  // put your main code here, to run repeatedly:


  //   if (millis() - lastTime2 >= sampleTime2)
  // {  // Se actualiza cada sampleTime (milisegundos)
  
  //      lastTime2 = millis(); // Almacenar el tiempo actual.

   if (digitalRead(PIN1C) == 0 && beforeReaduncent == 1) {
    Serial.print("10 centavos - Suma:");
    Serial.println(sum);
    uncent += 1;
    uncent_g += 1;
    beforeReaduncent = 0;
    countStatus=true;
  } else if (digitalRead(PIN1C) == 1) {
    beforeReaduncent = 1;
  }


  //50원
  if (digitalRead(PIN10C) == 0 && beforeReaddiezcent == 1) {
    Serial.print("10 centavos - Suma:");
    Serial.println(sum);
    diezcent += 1;
    diezcent_g += 1;
    beforeReaddiezcent = 0;
    countStatus=true;
  } else if (digitalRead(PIN10C) == 1) {
    beforeReaddiezcent = 1;
  }
  //100원
  if (digitalRead(PIN5C) == 0 && beforeReadcincocent == 1) {
    Serial.print("5 centavos - Suma:");
    Serial.println(sum);
    cincocent += 1;
    cincocent_g += 1;
    beforeReadcincocent = 0;
    countStatus=true;
  } else if (digitalRead(PIN5C) == 1) {
    beforeReadcincocent = 1;
  }
  //500원
  if (digitalRead(PIN25C) == 0 && beforeReadvnt_cincocent == 1) {
    Serial.print("25 centavos - Suma:");
    Serial.println(sum);
    vnt_cincocent += 1;
    vnt_cincocent_g += 1;
    beforeReadvnt_cincocent = 0;
    countStatus=true;
  } else if (digitalRead(PIN25C) == 1) {
    beforeReadvnt_cincocent = 1;
  }

  if (digitalRead(PIN50C) == 0 && beforeReadcnta == 1) {
    Serial.print("50 centavos - Suma:");
    Serial.println(sum);
    cnta += 1;
    cnta_g += 1;
    beforeReadcnta = 0;
    countStatus=true;
  } else if (digitalRead(PIN50C) == 1) {
    beforeReadcnta = 1;
  }

    if (digitalRead(PIN100C) == 0 && beforeReadundolar == 1) {
    Serial.print("100 centavos - Suma:");
    Serial.println(sum);
    undolar += 1;
    undolar_g += 1;
    beforeReadundolar = 0;
    countStatus=true;
  } else if (digitalRead(PIN100C) == 1) {
    beforeReadundolar = 1;
  }
  
 // }

  if(countStatus){


    sum =  uncent*0.01
        + diezcent *0.1
        + cincocent *0.05
        + vnt_cincocent *0.25
        + cnta *0.50
        + undolar *1;

  sum_g =  uncent*0.01 
        + diezcent_g *0.1
        + cincocent_g *0.05
        + vnt_cincocent_g *0.25
        + cnta_g *0.50
        + undolar_g *1;
  

    Serial.println(sum);
    sum_a=sum;
    ScreenPrincipal(message,sum);
    countStatus=false;

}

  //////////////////////////////////////
  customKeypad.tick();

   if (millis() - lastTime2 >= sampleTime2)
  {  // Se actualiza cada sampleTime (milisegundos)
  
       lastTime2 = millis(); // Almacenar el tiempo actual.
  while(customKeypad.available() && stringComplete==false){
    keypadEvent e = customKeypad.read();
    // Serial.print((char)e.bit.KEY);
    // if(e.bit.EVENT == KEY_JUST_PRESSED) Serial.println(" pressed");
    // else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
    if(e.bit.EVENT == KEY_JUST_PRESSED) {
     message = e.bit.KEY;
     Serial.println((char)e.bit.KEY);      
    }
    else if(e.bit.EVENT == KEY_JUST_RELEASED) ;
    stringComplete = true;
  }
  }
  
  
    if (millis() - lastTime >= sampleTime)
  {  // Se actualiza cada sampleTime (milisegundos)
  
       lastTime = millis(); // Almacenar el tiempo actual.
       if( stringComplete){
      ScreenPrincipal(message,sum);
       stringComplete = false;
       message_or=message;
      
      }
      
  }

    switch (message_or)
        {
        case '0':
           message_or="";
           delay(0.1);
          ResetCount();
          ScreenPrincipal(message,sum);
         
           
         break;

        case 'A':
               message_or="";
          

              if(sum>=val_1){
              sum=sum-val_1;
              Serial.println("Activado Producto 30 Centavos");
              openCajon(CAJM);
              ResetCount();
              ScreenPrincipal(message,sum);
              }
              else{
                Serial.println("Dinero Insuficiente");
                Message_FaltaDinero();

              }
              
              
        break;
            
          case 'B':
              message_or="";
              delay(100);

          break;

          case '*':
              //while(""){}

              message_or="";
              delay(100);

          break;
        }

}
void unitScreen() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
  ScreenPrincipal("",0);
  delay(2000);
}

void initKeyboard(){
    customKeypad.begin();
}

// char Keyboard(){
//    char messege;
//    while(customKeypad.available()){
//     keypadEvent e = customKeypad.read();
//     // Serial.print((char)e.bit.KEY);
//     // if(e.bit.EVENT == KEY_JUST_PRESSED) Serial.println(" pressed");
//     // else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
//     if(e.bit.EVENT == KEY_JUST_PRESSED) Serial.print((char)e.bit.KEY);
//     else if(e.bit.EVENT == KEY_JUST_RELEASED) ;
//      messege = e.bit.KEY;
//   }
//     delay(10);
//     return messege;
// }


void ScreenPrincipal(char messege, float sum) {
  display.clearDisplay();

  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);  // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);  // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  //display.print(F("0x"));
  display.print(F("$ "));
  display.print(sum);
  display.print(F("-"));
  display.println(messege);

  display.display();
}


  void initContador(){

  pinMode(PIN1C, INPUT);
  pinMode(PIN10C, INPUT);
  pinMode(PIN5C, INPUT);
  pinMode(PIN25C, INPUT);
  pinMode(PIN50C, INPUT);
  pinMode(PIN100C, INPUT);
  }

  void ResetCount(){
              sum = 0;
              uncent = 0;
              diezcent = 0;
              cincocent = 0;
              vnt_cincocent = 0;
              cnta = 0;
              undolar = 0;

  }

  void openCajon(int RELE){
    
   digitalWrite(RELE,HIGH);
   delay(5000);
  digitalWrite(RELE,LOW);    

  }

  void Message_FaltaDinero(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("  FALTA\n  DINERO"));
  display.display();      // Show initial text
  delay(1000);
  display.clearDisplay();
  ScreenPrincipal(message,sum);

}

  