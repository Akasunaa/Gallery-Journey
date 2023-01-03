# GALLERY JOURNEY

### Code Arduino pour la carte 

```c
#include "Keypad.h"
#include <LiquidCrystal.h> 

//led
#define BLUE_LED 7  // The pin the LED is connected to
#define RED_LED 6  // The pin the LED is connected to
#define LCD_Backlight 10

//for message
const int MAX_SIZE_BUFF = 256;
char buffer[MAX_SIZE_BUFF];

//keypad
const byte ROWS = 4; // number of rows
const byte COLS = 4; // number of columns
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = {8, 9, A0, A1}; // row pinouts of the keypad R1 = D8, R2 = D7, R3 = D6, R4 = D5
byte colPins[COLS] = {A2, A3, A4, A5};    // column pinouts of the keypad C1 = D4, C2 = D3, C3 = D2
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//screen
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int Contrast = 60;

void setup() {
  //message
  Serial.begin(9600);

  //led
  pinMode(BLUE_LED, OUTPUT); 
  pinMode(RED_LED, OUTPUT); 

  //screen
  lcd.begin(16, 2);
  lcd.print("GALLERY JOURNEY");

}

void loop() {

  if (Serial.available() > 0) {
    String message = Serial.readString();
    message.trim();
    lcd.clear();
    if(message=="red"){
        redled();
    }
    else if(message=="blue"){
      blueled();
    }
    else{
      lcd.print(message);
    }
  }  
  //read input
  char key = keypad.getKey(); 
  if (key != NO_KEY){
    Serial.println((char)key);
  }
  //write screen
  //lcd.print(" Hello, World!!");
}
void blueled(){
  digitalWrite(BLUE_LED , HIGH);
  delay(1000);
  digitalWrite(BLUE_LED , LOW);
}

void redled(){
  digitalWrite(RED_LED , HIGH);
  delay(1000);
  digitalWrite(RED_LED , LOW);
}
```

### Branchements
<h1 align="center">
<img src="https://user-images.githubusercontent.com/74360060/210371972-6a0bce55-b743-4395-8fab-80dcb0e436ee.jpg" alt="drawing" width="200" rotate="90"/>
</h1>

### Démo 
<h1 align="center">
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/FP7NBC67TgI/0.jpg)](https://www.youtube.com/watch?v=FP7NBC67TgI)
</h1>


