#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buzzer = 13;
const int blueLEDPin = 10;
const int yellowLEDPin = 9;
const int redLEDPin = 8;
const int greenLEDPin = 7;

const int greenTone = 440;
const int redTone = 494;
const int blueTone = 523;
const int yellowTone = 587;

const int blueButton = A0;
const int redButton = A1;
const int greenButton = A2;
const int yellowButton = A3;

String order = "";
int score = 0;
bool won = true;
bool gameOver = false;

void setup() {
  randomSeed(analogRead(4));

  pinMode(blueLEDPin,OUTPUT);
  pinMode(yellowLEDPin,OUTPUT);
  pinMode(redLEDPin,OUTPUT);
  pinMode(greenLEDPin,OUTPUT);
  pinMode(buzzer,OUTPUT);
  
  pinMode(blueButton, INPUT_PULLUP);
  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(yellowButton, INPUT_PULLUP);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print(" Starting in... ");
  
  play_green();
  play_red();
  play_blue();
  play_yellow();

  for (int i = 3; i>=0;i--){
    lcd.setCursor(0, 1);
     lcd.print("       0" +String(i)+"       ");
     delay(1000);
  }

}
// 1 = blue 2 = red 3 = green 4 = yellow
void loop() {
  if(!gameOver){
    order = order + String(random(1,5));
    won = true;
    
    lcd.setCursor(0, 0);
    lcd.print("     SCORE:     ");
    lcd.setCursor(0, 1);
    lcd.print("       " + String(score)+ "       ");

    for (int i = 0; i < order.length(); i++){
      if (order[i] == '1'){
          play_blue();
      }      
      else if (order[i] == '2'){
          play_red();
      }
      else if (order[i] == '3'){
          play_green();
      }
      else{
          play_yellow();
      }
      delay(600);
    }

    for (int i = 0; i < order.length(); i++){
      while (true){
        if (digitalRead(blueButton) != HIGH){
          play_blue();
          if (order[i] != '1'){
            won = false;
          }
          break;
        }
        if (digitalRead(redButton) != HIGH){
          play_red();
          if (order[i] != '2'){
            won = false;
          }
          break;
        }
        if (digitalRead(greenButton) != HIGH){
          play_green();
          if (order[i] != '3'){
            won = false;
          }
          break;  
        }
        if (digitalRead(yellowButton) != HIGH){
          play_yellow();
          if (order[i] != '4'){
            won = false;
          }
          break; 
        }
      }
      if (!won){
        break;
      }
    }
    
  if (!won){
    lcd.setCursor(0, 0);
    lcd.print("    GAME OVER   ");
    lcd.setCursor(0, 1);
    lcd.print("    SCORE: " + String(score)+ "   ");
    tone(buzzer, 659);
    delay(1000);
    noTone(buzzer);
    gameOver = true;
  }
  delay(1000);
  score++;
  }
}

void play_blue(){
  digitalWrite(blueLEDPin, HIGH);
  tone(buzzer, blueTone);
  delay(500);
  digitalWrite(blueLEDPin, LOW);
  noTone(buzzer);
}

void play_green(){
  digitalWrite(greenLEDPin, HIGH);
  tone(buzzer, greenTone);
  delay(500);
  digitalWrite(greenLEDPin, LOW);
  noTone(buzzer);
}

void play_red(){
  digitalWrite(redLEDPin, HIGH);
  tone(buzzer, redTone);
  delay(500);
  digitalWrite(redLEDPin, LOW);
  noTone(buzzer);
}

void play_yellow(){
  digitalWrite(yellowLEDPin, HIGH);
  tone(buzzer, yellowTone);
  delay(500);
  digitalWrite(yellowLEDPin, LOW);
  noTone(buzzer);
}
