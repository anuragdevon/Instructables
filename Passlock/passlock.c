#include <Keypad.h>

#include<LiquidCrystal.h>

#include<EEPROM.h>

#include <Servo.h>  

Servo servo_test; 

int angle = 0;    

LiquidCrystal LCD(9,8,7,6,5,4);

char password[4];

char initial_password[4],new_password[4];

int i = 0;

int ledW = 12;

int ledR = 11;


char key_pressed=0;

const byte rows = 4; 

const byte columns = 4; 

char hexaKeys[rows][columns] = {

{'1','2','3','A'},

{'4','5','6','B'},

{'7','8','9','C'},

{'*','0','#','D'}

};

byte row_pins[rows] = {A0,A1,A2,A3};

byte column_pins[columns] = {A4,A5,3,2};   

Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);



void setup()

{
    
  servo_test.attach(9); 

  pinMode(ledR, OUTPUT);

  pinMode(ledW, OUTPUT);

  LCD.begin(16,2);

  LCD.print("WELCOME");

  LCD.setCursor(0,1);

  LCD.print("PASSLOCK!!");

  delay(2000);

  LCD.clear();

  LCD.print("Enter Password");

  delay(500);

  LCD.print("."); delay(500);

  LCD.print("."); delay(500);

  LCD.print("."); delay(500);

  LCD.setCursor(0,1);

  initialpassword();

  digitalWrite(ledR, HIGH);

  digitalWrite(ledW, HIGH);

  delay(500);


  digitalWrite(ledR, LOW);

  digitalWrite(ledW, LOW);

  delay(500);


  digitalWrite(ledR, HIGH);

  digitalWrite(ledW, HIGH);

  delay(500);


  digitalWrite(ledR, LOW);

  digitalWrite(ledW, LOW);

  delay(500);


}




void loop()

{

    for(angle = 0; angle < 180; angle += 1)     
    {                                  
        servo_test.write(angle);                 
        delay(15);                       
    } 

  

  key_pressed = keypad_key.getKey();

  if(key_pressed=='#')

    change();

  if (key_pressed)

  {

    password[i++]=key_pressed;

    LCD.print(key_pressed);

      }

  if(i==4)

  {

    delay(200);

    for(int j=0;j<4;j++)

      initial_password[j]=EEPROM.read(j);

    if(!(strncmp(password, initial_password,4)))

    {

        LCD.clear();

        LCD.print("Pass Accepted");

        digitalWrite(ledR, HIGH);
        
        delay(500);

        digitalWrite(ledR, LOW);

        delay(500);        

        digitalWrite(ledR, LOW);

        delay(500);

        digitalWrite(ledR, LOW);

        delay(500);

        for(angle = 180; angle>=1; angle-=5)    
        {                                
            servo_test.write(angle);              
            delay(5);                       
        } 

        delay(2000);

        LCD.setCursor(0,1);

        LCD.print("Pres # to change");

        delay(2000);

        LCD.clear();

        LCD.print("Enter Password:");

        LCD.setCursor(0,1);

        i=0;

    }

    else

    {

        for(angle = 0; angle < 180; angle += 1)     
        {                                  
            servo_test.write(angle);                 
            delay(15);                       
        }


        LCD.clear();

        LCD.print("Wrong Password");

        digitalWrite(ledW, HIGH);
        
        delay(500);

        digitalWrite(ledW, LOW);

        delay(500);        

        digitalWrite(ledW, LOW);

        delay(500);

        digitalWrite(ledW, LOW);

        delay(500);

        LCD.setCursor(0,1);
 
        LCD.print("Pres # to Change");

        delay(2000);

        LCD.clear();

        LCD.print("Enter Password");

        LCD.setCursor(0,1);

        i=0;

    }

  }

}

void change()

{

  int j=0;

  LCD.clear();

  LCD.print("Current Password");

  LCD.setCursor(0,1);

  while(j<4)

  {

    char key=keypad_key.getKey();

    if(key)

    {

      new_password[j++]=key;

      LCD.print(key);

       

    }

    key=0;

  }

  delay(500);




  if((strncmp(new_password, initial_password, 4)))

  {

    LCD.clear();

    LCD.print("Wrong Password");

    LCD.setCursor(0,1);

    LCD.print("Try Again");

    delay(1000);

  }

  else

  {

    j=0;

    LCD.clear();

    LCD.print("New Password:");

    LCD.setCursor(0,1);

    while(j<4)

    {

      char key=keypad_key.getKey();

      if(key)

      {

        initial_password[j]=key;

        LCD.print(key);

        EEPROM.write(j,key);

        j++;

     

      }

    }

    LCD.print("Pass Changed");

    delay(1000);

  }

  LCD.clear();

  LCD.print("Enter Password");

  LCD.setCursor(0,1);

  key_pressed=0;

}




void initialpassword(){

  for(int j=0;j<4;j++)

    EEPROM.write(j, j+49);

  for(int j=0;j<4;j++)

    initial_password[j]=EEPROM.read(j);

}