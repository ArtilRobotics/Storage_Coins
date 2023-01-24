#include "Adafruit_Keypad.h"


const byte ROWS = 4;  // rows
const byte COLS = 4;  // columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  { 'D', 'C', 'B', 'A' },
  { '#', '9', '6', '3' },
  { '0', '8', '5', '2' },
  { '*', '7', '4', '1' }
};
byte rowPins[ROWS] = { 42, 43, 44, 45 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 48, 49, 50, 51 };  //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

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

int PIN1C = 8;
int PIN10C = 9;
int PIN5C = 10;
int PIN25C = 13;
//int PIN50C = 12;
int PIN100C = 11;

float val_1 = 0.3;
float val_2 = 0.5;
float val_3 = 0.75;
float val_4 = 1;

int CAJM = 6;
int CAJ1 = 2;
int CAJ2 = 3;
int CAJ3 = 4;
int CAJ4 = 5;

///////////////////////////////

double tma = 0.1;

int tmas = tma * 1000;

unsigned long lastTime, sampleTime = tmas;

double tma2 = 0.25;

int tmas2 = tma2 * 1000;

unsigned long lastTime2, sampleTime2 = tmas2;

char message;
char message_or;

bool stringComplete = false;

float sum;
float sum_nc;
float sum_g;

bool countStatus = false;

///////


char TECLA;                      // almacena la tecla presionada
char CLAVE[5];                   // almacena en un array 4 digitos ingresados
char CLAVE_MAESTRA[5] = "0000";  // almacena en un array la contraseña inicial
byte INDICE = 0;                 // indice del array
//////

void setup() {

  Serial.begin(9600);
  unitScreen();
  initKeyboard();
  initContador();
  ResetCount();
  initCajon();
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
    sum_nc = sum_nc + 0.01;
    countStatus = true;
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
    sum_nc = sum_nc + 0.1;
    countStatus = true;
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
    sum_nc = sum_nc + 0.05;
    countStatus = true;
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
    sum_nc = sum_nc + 0.25;
    countStatus = true;
  } else if (digitalRead(PIN25C) == 1) {
    beforeReadvnt_cincocent = 1;
  }

  // if (digitalRead(PIN50C) == 0 && beforeReadcnta == 1) {
  //   Serial.print("50 centavos - Suma:");
  //   Serial.println(sum);
  //   cnta += 1;
  //   cnta_g += 1;
  //   beforeReadcnta = 0;
  //   sum_nc = sum_nc + 0.5;
  //   countStatus = true;
  // } else if (digitalRead(PIN50C) == 1) {
  //   beforeReadcnta = 1;
  // }

  if (digitalRead(PIN100C) == 0 && beforeReadundolar == 1) {
    Serial.print("100 centavos - Suma:");
    Serial.println(sum);
    undolar += 1;
    undolar_g += 1;
    beforeReadundolar = 0;
    sum_nc = sum_nc + 1;
    countStatus = true;
  } else if (digitalRead(PIN100C) == 1) {
    beforeReadundolar = 1;
  }

  // }

  if (countStatus) {


    sum = uncent * 0.01
          + diezcent * 0.1
          + cincocent * 0.05
          + vnt_cincocent * 0.25
          + cnta * 0.50
          + undolar * 1;

    sum_g = uncent * 0.01
            + diezcent_g * 0.1
            + cincocent_g * 0.05
            + vnt_cincocent_g * 0.25
            + cnta_g * 0.50
            + undolar_g * 1;


    Serial.println(sum);
    //sum_a=sum;
    ScreenPrincipal(message, sum_nc);
    countStatus = false;
  }

  //////////////////////////////////////
  customKeypad.tick();

  if (millis() - lastTime2 >= sampleTime2) {  // Se actualiza cada sampleTime (milisegundos)

    lastTime2 = millis();  // Almacenar el tiempo actual.
    while (customKeypad.available() && stringComplete == false) {
      keypadEvent e = customKeypad.read();
      // Serial.print((char)e.bit.KEY);
      // if(e.bit.EVENT == KEY_JUST_PRESSED) Serial.println(" pressed");
      // else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
      if (e.bit.EVENT == KEY_JUST_PRESSED) {
        message = e.bit.KEY;
        Serial.println((char)e.bit.KEY);
        stringComplete = true;
      } else if (e.bit.EVENT == KEY_JUST_RELEASED)
        ;
    }
  }


  if (millis() - lastTime >= sampleTime) {  // Se actualiza cada sampleTime (milisegundos)

    lastTime = millis();  // Almacenar el tiempo actual.
    if (stringComplete) {
      // ScreenPrincipal(message, sum);
      ScreenPrincipal(message, sum_nc);
      stringComplete = false;
      message_or = message;
    }
  }

  switch (message_or) {
    case '#':
      message_or = "";
      delay(0.1);
      sum_nc=0;
      ResetCount();
      //ScreenPrincipal(message, sum);
      ScreenPrincipal(message, sum_nc);


      break;

    case 'A':
      message_or = "";


      if (sum_nc >= val_1) {
        sum_nc = sum_nc - val_1;
        ScreenPrincipal(message, sum_nc);
        Serial.println("Activado Producto 30 Centavos");
        openCajon(CAJ1);
        ResetCount();
        // ScreenPrincipal(message, sum);
      } else {
        Serial.println("Dinero Insuficiente");
        Message_FaltaDinero();
      }


      break;

    case 'B':
      message_or = "";


      if (sum_nc >= val_2) {
        sum_nc = sum_nc - val_2;
        ScreenPrincipal(message, sum_nc);
        Serial.println("Activado Producto 50 Centavos");
        openCajon(CAJ2);
        ResetCount();
      } else {
        Serial.println("Dinero Insuficiente");
        Message_FaltaDinero();
      }

      break;

    case 'C':
      message_or = "";


      if (sum_nc >= val_3) {
        sum_nc = sum_nc - val_3;
        ScreenPrincipal(message, sum_nc);
        Serial.println("Activado Producto 75 centavos");
        openCajon(CAJ3);
        ResetCount();
      } else {
        Serial.println("Dinero Insuficiente");
        Message_FaltaDinero();
      }

      break;

    case 'D':
      message_or = "";


      if (sum_nc >= val_4) {
        sum_nc = sum_nc - val_4;
        ScreenPrincipal(message, sum_nc);
        Serial.println("Activado Producto 1 dolar");
        openCajon(CAJ4);
        ResetCount();
      } else {
        Serial.println("Dinero Insuficiente");
        Message_FaltaDinero();
      }

      break;

    case '*':

      ClaveInput();

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
  ScreenPrincipal("", 0);
  delay(2000);
}

void initKeyboard() {
  customKeypad.begin();
}


void ScreenPrincipal(char messege, float sum) {
  display.clearDisplay();

  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
  display.println(F("Cajones Inteligentes"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);  // Draw 'inverse' text
  display.println(3.14);

  display.setTextSize(2);  // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  //display.print(F("0x"));
  display.print(F("$ "));
  display.print(sum);
  display.print(F("-"));
  display.println(messege);

  display.display();
}


void ScreenKey(String messege) {
  display.clearDisplay();

  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
  display.println(F("INGRESE LA CLAVE"));

  display.setTextSize(2);  // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  //display.print(F("0x"));
  display.println(messege);

  display.display();
}

void ScreenKeyStatus(String messege1, float sum) {
  display.clearDisplay();

  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
  display.println(F("Dinero Total:"));

  display.setTextSize(2);  // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);


  display.print(messege1);
  display.println(sum);
  display.display();
}


void initContador() {

  pinMode(PIN1C, INPUT);
  pinMode(PIN10C, INPUT);
  pinMode(PIN5C, INPUT);
  pinMode(PIN25C, INPUT);
  //pinMode(PIN50C, INPUT);
  pinMode(PIN100C, INPUT);
}

void ResetCount() {
  sum = 0;
  uncent = 0;
  diezcent = 0;
  cincocent = 0;
  vnt_cincocent = 0;
  cnta = 0;
  undolar = 0;
}

void ResetCountGlobal() {
  sum_g = 0;
  uncent_g = 0;
  diezcent_g = 0;
  cincocent_g = 0;
  vnt_cincocent_g = 0;
  cnta_g = 0;
  undolar_g = 0;
}

void openCajon(int RELE) {

  digitalWrite(RELE, LOW);
  delay(5000);
  digitalWrite(RELE, HIGH);
}

void initCajon() {

  pinMode(CAJM, OUTPUT);
  digitalWrite(CAJM, HIGH);
  pinMode(CAJ1, OUTPUT);
  digitalWrite(CAJ1, HIGH);
  pinMode(CAJ2, OUTPUT);
  digitalWrite(CAJ2, HIGH);
  pinMode(CAJ3, OUTPUT);
  digitalWrite(CAJ3, HIGH);
  pinMode(CAJ4, OUTPUT);
  digitalWrite(CAJ4, HIGH);
}

void Message_FaltaDinero() {
  display.clearDisplay();

  display.setTextSize(2);  // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("  FALTA\n  DINERO"));
  display.display();  // Show initial text
  delay(1000);
  display.clearDisplay();
  ScreenPrincipal(message, sum_nc);
}

void ClaveInput() {

  ScreenKey(CLAVE);

  while (customKeypad.available() && stringComplete == false) {
    keypadEvent e = customKeypad.read();
    // Serial.print((char)e.bit.KEY);
    // if(e.bit.EVENT == KEY_JUST_PRESSED) Serial.println(" pressed");
    // else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      TECLA = e.bit.KEY;  // obtiene tecla presionada y asigna a variable
      delay(10);
      if (TECLA)  // comprueba que se haya presionado una tecla
      {
        CLAVE[INDICE] = TECLA;  // almacena en array la tecla presionada
        INDICE++;               // incrementa indice en uno
        Serial.println(TECLA);  // envia al LCD la tecla presionada
        Serial.println(CLAVE);
      }

      if (INDICE == 4)  // si ya se almacenaron los 4 digitos
      {
        if (!strcmp(CLAVE, CLAVE_MAESTRA)) {

          Serial.println("Abrir Caja Maestra");
          ScreenKey("Abrir");
          openCajon(CAJM);
          /////
          ScreenKeyStatus("$ ", sum_g);
          delay(1000);

          ScreenKeyStatus("1 c: ", uncent_g);
          delay(1000);

          ScreenKeyStatus("10 c: ", diezcent_g);
          delay(1000);

          ScreenKeyStatus("5 c: ", cincocent_g);
          delay(1000);

          ScreenKeyStatus("25 c: ", vnt_cincocent_g);
          delay(1000);

          ScreenKeyStatus("50 c: ", cnta_g);
          delay(1000);

          ScreenKeyStatus("1 $: ", undolar_g);
          delay(1000);
          ResetCountGlobal();

        }  // compara clave ingresada con clave maestra
           //abierto();

        else {

          Serial.println("ERROR");
          ScreenKey("Error");
          delay(5000);
        }
        //error();
        INDICE = 0;
        message_or = "";

        memset(CLAVE, 0, sizeof(CLAVE));

        ScreenPrincipal(message, sum);
      }
    } else if (e.bit.EVENT == KEY_JUST_RELEASED)
      ;
  }
}
