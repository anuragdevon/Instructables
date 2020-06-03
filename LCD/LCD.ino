#include <LiquidCrystal.h>

const int ledPin = 8;
const int button = 7;
int ButtonState = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{
  
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  pinMode(button, INPUT);
  lcd.display();
  lcd.print("Starting");delay(500);
  lcd.print("."); delay(500);
  lcd.print("."); delay(500);
  lcd.print("."); delay(500);
  lcd.clear();
  lcd.noDisplay();
  
}

void loop() 
{
  lcd.display();
  ButtonState = digitalRead(button);
  
  if (ButtonState == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    lcd.clear();
    lcd.print("LED IS ON");
    delay(500);
  }
  else
  {
    digitalWrite(ledPin, LOW);
    lcd.clear();
    lcd.print("LED IS OFF");
    delay(500);
  }    
    
}
