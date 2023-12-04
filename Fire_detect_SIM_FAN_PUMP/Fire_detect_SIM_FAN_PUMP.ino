#include <Servo.h>
#include <SoftwareSerial.h>
Servo myservo;  // create servo object to control a servo
SoftwareSerial mySerial(6, 7);
int buzGas = 0;
int buzFlame1 =0;
int buzFlame2 =0;

void call(){
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();
  
  mySerial.println("ATD+ +8801867417227;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(20000); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  updateSerial();
}
void setup() {
  pinMode(2,INPUT);   //flame
  pinMode(3,INPUT);   //flame
  pinMode(4,INPUT);   //Gas

  pinMode(8,OUTPUT);  //servo
  pinMode(9,OUTPUT);  //fan relay
  pinMode(10,OUTPUT);  //pump
  pinMode(11,OUTPUT);  //buzzer

  Serial.begin(9600);
  myservo.attach(8);
  
}

void loop() 
{   
  int f1=digitalRead(2);
  int f2=digitalRead(3);
  int g=digitalRead(4);

  if (f1 ==0 || f2 ==0 || g==0)
  {
    digitalWrite(11,HIGH);
  }
  else
  {
    digitalWrite(11,LOW);
  }

  if(g==1)
  { // gas not detected
    digitalWrite(9,HIGH);
    // digitalWrite(11,LOW);
    // buzGas = 0;
    delay(20);
  }
  else 
  {  
    // CH4 Gas Detected
    digitalWrite(9,LOW);
    // digitalWrite(11,HIGH);
    // buzGas ==1;
    // call();
    Serial.println(" CH4 Gas Detected");
    delay(500);
  }
  // Serial.print(f1);
  // Serial.println(f2);

   if( f2==0) //f1==1 &&
  {
    myservo.write(90); //angle set to 1
    // digitalWrite(11,HIGH); //buzzer
    // buzFlame1 = 1;
    digitalWrite(10,LOW); // pump
    Serial.println("Flame Detected on Sensor 2");
    delay(500);
    // call();
    

  }
  else if(f1==0 ) //&& f2==1
  {
    myservo.write(5);
    // digitalWrite(11,HIGH);//buzzer
    //  buzFlame1 = 1;
    digitalWrite(10,LOW); //pump
    Serial.println("Flame Detected on Sensor 1");
    delay(500);
    // call();
  }
    else
  {
    myservo.write(45);
    // digitalWrite(11,LOW);
    digitalWrite(10,HIGH);
    //  buzFlame1 = 0;
    
  }

    if(f1==0 || f2==0)
    {
        digitalWrite(10,LOW);
        //  buzFlame1 = 0;
    }
    else
    {
        digitalWrite(10,HIGH);
    }

}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
