#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>

Servo myservo;
int pos=0; // position of servo motor
LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);
const byte rows=4;
const byte cols=3;
 
char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows]={0,1,2,3};
byte colPins[cols]={4,5,6};
Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="1234";
int currentposition=0;
 
int red = 13;
int green = 12; 

void setup()
{ 
  displayscreen();
  //Serial.begin(9600);
  myservo.attach(8); //Servo motor connection
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  lcd.begin(16,2);
}
 
void loop()
  {
  if( currentposition==0)
  {
      displayscreen();
  }
  int l ;
  char code=keypad.getKey();
  if(code!=NO_KEY)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PASSWORD:");
    lcd.setCursor(7,1);
    lcd.print(" ");
    lcd.setCursor(7,1);
    for(l=0;l<=currentposition;++l)
    {
    lcd.print("*");
    //keypress();
    }
    if (code==password[currentposition])
    {
      ++currentposition;
      if(currentposition==4)
        {
        unlockdoor();
        displayscreen();
        currentposition=0;
        }   
    }
    else
    {
    incorrect();
    currentposition=0;
    }
  }
}
//------------------ Function 1- OPEN THE DOOR--------------//
void unlockdoor()
  {
  delay(900);
  
  lcd.setCursor(0,0);
  lcd.println(" ");
  lcd.setCursor(1,0);
  lcd.print("Access Done");
  lcd.setCursor(4,1);
  lcd.println("WELCOME!");
  lcd.setCursor(15,1);
  lcd.println(" ");
  lcd.setCursor(16,1);
  lcd.println(" ");
  lcd.setCursor(14,1);
  lcd.println(" ");
  lcd.setCursor(13,1);
  lcd.println(" ");

  for(pos = 180; pos>=0; pos-=5) // open the door
    {
    myservo.write(pos); 
    delay(5); 
    }

  digitalWrite(green,HIGH);
  delay(1000);
  digitalWrite(green,LOW);
  delay(1000);
  
  for(pos = 0; pos <= 180; pos +=5) // close the door
    { // in steps of 1 degree
    myservo.write(pos); 
    delay(15); 
    }
  digitalWrite(red,HIGH);
  delay(1000);
  digitalWrite(red,LOW);
  delay(500);
  currentposition=0;
  lcd.clear();
  displayscreen();
}
//--------------------Function 2- Wrong code--------------//
void incorrect()
  {
  delay(500);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("CODE");
  lcd.setCursor(6,0);
  lcd.print("INCORRECT Password");
  lcd.setCursor(15,1);
  lcd.println(" ");
  lcd.setCursor(4,1);
  lcd.println("TRY AGAIN !");
  
  lcd.setCursor(13,1);
  lcd.println(" ");
  Serial.println("CODE INCORRECT ");
  digitalWrite(red,HIGH);
  delay(1000);
  digitalWrite(red,LOW);
  delay(3000);
  lcd.clear();
  displayscreen();
}
//------------Function 3 - DISPLAY FUNCTION--------------------//
void displayscreen()
{
  lcd.setCursor(0,0);
  lcd.println("*ENTER THE CODE ");
  lcd.setCursor(1 ,1);
  lcd.println("TO OPEN DOOR.");
}