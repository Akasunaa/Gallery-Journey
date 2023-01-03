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




##### Projet étudiant - Jeu Vidéo développé en C++ par Alexandre LAFERRERE et Prométhée TONEATTI

Vous êtes parti en exploration avec Otto Lidenbrock et son neveu Axel, au centre de la terre. Vous les accompagnez en tant qu'explorateur eminant et archéologue de renond. Seulement, après quelques heures de fouille, un eboulement à lieu. Vous êtes séparé lors de cet éboulement, et coincé au centre de la terre. Vous n’avez qu’avec vous une pioche, quelques fils, et votre immense savoir en archéologie et votre débrouillardise. Parviendrez-vous à remonter à la surface ? 

Commandes : 
- Flèches/ZQSD : se déplacer
- E : interagir
- I : inventaire
- Q : quitter les menus
- Clic gauche souris : creuser

<h1 align="center">
<img src="https://user-images.githubusercontent.com/74360060/176509289-71914b9f-eef0-4aa4-b8c0-a502d9bee451.png" alt="drawing" width="600"/>
<img src="https://user-images.githubusercontent.com/74360060/176509968-bd8dc911-5669-4169-a0f9-cd43c81411e7.png" alt="drawing" width="600"/>
<img src="https://user-images.githubusercontent.com/74360060/176510202-fd2ac8a6-65fa-41dc-b39a-02475e1b6449.png" width="600"/>
</h1>
