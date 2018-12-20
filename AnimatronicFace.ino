

/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  PWM test - this will drive 16 PWMs in a 'wave'

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <Servo.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);
                                     
int x, y,ym; 
int sensorValue = 0; 
int mode = 0; 
int total=0;
int num = 0; 
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
const int bPin = 3;
const int gPin = 5;
const int rPin = 6;
const int CLOCKS_PER_SEC = 1000; 
int sec; 
int flag = 0; 
int n = 0; 
int totalSecret;
int secSecret;

#define trigPin 12
#define echoPin 11

class Mp3Notify
{
public:
  static void OnError(uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }

  static void OnPlayFinished(uint16_t globalTrack)
  {
    Serial.println();
    Serial.print("Play finished for #");
    Serial.println(globalTrack);   
  }

  static void OnCardOnline(uint16_t code)
  {
    Serial.println();
    Serial.print("Card online ");
    Serial.println(code);     
  }

  static void OnCardInserted(uint16_t code)
  {
    Serial.println();
    Serial.print("Card inserted ");
    Serial.println(code); 
  }

  static void OnCardRemoved(uint16_t code)
  {
    Serial.println();
    Serial.print("Card removed ");
    Serial.println(code);  
  }
};

SoftwareSerial secondarySerial(10, 9); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);


void(*resetFunc)(void) =0;
void setup() {
  randomSeed(analogRead(A2)); //seeds random number for random sequence upon start
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
 pwm.begin();
 Serial.begin(9600);
 pwm.setPWMFreq(60);  // This is the maximum PWM frequency
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (x, INPUT) ;                     
  pinMode (y, INPUT) ;
  pinMode (ym, INPUT) ;
  delay(500);

   mp3.begin();
   mp3.setVolume(30);
   mp3.playMp3FolderTrack(18);
}

void loop() {
if(mode > 3) 
  resetFunc();

Serial.println(mode); 

if(digitalRead(2)==HIGH) 
  mode++; 

switch (mode) {
    case 1:
  mp3.stop();
  Serial.println("1");
  analogWrite(rPin, 0);
  analogWrite(gPin, 0);
  analogWrite(bPin, 100);
  joyStick();
      break;
    case 2:
        Serial.println("2");
  analogWrite(rPin, 100);
  analogWrite(gPin, 0);
  analogWrite(bPin, 0);
        distance();
      break;
     case 3:
  Serial.println("3");
  analogWrite(rPin, 100);
  analogWrite(gPin, 0);
  analogWrite(bPin, 100);
      joyStickOnly2();  
      //do something when var equals 2
      break;  
      default:
  Serial.println(mode);
  analogWrite(rPin, 0);
  analogWrite(gPin, 0);
  analogWrite(bPin, 0);
  pwm.setPWM(4, 0,130);
  pwm.setPWM(5, 0,455);
  pwm.setPWM(6, 0,420);
  pwm.setPWM(7, 0,420);
  pwm.setPWM(8, 0,420);
      break;
  }
  delay(180);
}

void joyStick() {
  delay(800);
  mp3.playMp3FolderTrack(random(1,16));
  delay(200);
  
  while(digitalRead(2) == LOW) {
    delay(150);
    joyStickOnly1(); 
  }
}

void distance() {
   pwm.setPWM(5, 0,500);
   pwm.setPWM(6, 0,500);
   pwm.setPWM(7, 0,500);
   pwm.setPWM(8, 0,500);
  sec = millis(); 
  total = 0;
  delay(200);
  while(flag != 1) {
   if(digitalRead(2) == HIGH) {
   mp3.stop();
   mode++; 
    delay(500);
    return; 
    }
      long duration, distance;
      digitalWrite(trigPin, LOW);  // Added this line
      delayMicroseconds(2); // Added this line
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); // Added this line
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration/2) / 29.1; 
      Serial.println(distance); 
      pwm.setPWM(4, 0,300); 
      if(distance == 70) {
      Serial.println("YES");
      mp3.playMp3FolderTrack(5);

      delay(100);
        pwm.setPWM(5, 0,420);
        pwm.setPWM(6, 0,500);
        pwm.setPWM(7, 0,420);
        pwm.setPWM(8, 0,500);
     
        pwm.setPWM(4, 0,300);
        delay(1500);  
        pwm.setPWM(4, 0,130);
        delay(250); 
        pwm.setPWM(4, 0,300);
        delay(1300); 
        pwm.setPWM(4, 0,130);
        delay(100); 
        pwm.setPWM(4, 0,300);
        delay(1250); 
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);
        delay(1250); 
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);
        delay(1700); 
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);
        delay(1250); 
        pwm.setPWM(6, 0,420);
        pwm.setPWM(8, 0,420);
        delay(100);  
        pwm.setPWM(6, 0,500);
        pwm.setPWM(8, 0,500);
        delay(10);
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);
        delay(1250); 
        pwm.setPWM(4, 0,130);
        delay(150);
        pwm.setPWM(4, 0,300);
        delay(1300);
        pwm.setPWM(4, 0,130);
        delay(150);
        pwm.setPWM(4, 0,300);
        delay(3500);
        Serial.println("flag=1");
        flag = 1;   
        delay(50);
      }
     
   }
   
   flag = 0; 
        pwm.setPWM(5, 0,500);
        pwm.setPWM(6, 0,500);
        pwm.setPWM(7, 0,500);
        pwm.setPWM(8, 0,500);
   delay(500);
   for(int i=0; i<2;i++) {
        pwm.setPWM(5, 0,420);
        pwm.setPWM(6, 0,420);
        pwm.setPWM(7, 0,420);
        pwm.setPWM(8, 0,420);
        delay(200);  
        pwm.setPWM(5, 0,500);
        pwm.setPWM(6, 0,500);
        pwm.setPWM(7, 0,500);
        pwm.setPWM(8, 0,500);
        delay(300);
        pwm.setPWM(5, 0,420);
        pwm.setPWM(6, 0,420);
        pwm.setPWM(7, 0,420);
        pwm.setPWM(8, 0,420);
        delay(100);  
        pwm.setPWM(5, 0,500);
        pwm.setPWM(6, 0,500);
        pwm.setPWM(7, 0,500);
        pwm.setPWM(8, 0,500);
        delay(50);
   }
   
   while(flag != 1) {
      if(digitalRead(2) == HIGH) {
   mode++; 
    delay(500);
    return; 
    }
      long duration, distance;
      digitalWrite(trigPin, LOW);  // Added this line
      delayMicroseconds(2); // Added this line
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); // Added this line
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration/2) / 29.1; 
      Serial.println(distance); 
      pwm.setPWM(4, 0,300); 
          if(distance == 100) {
      Serial.println("YES");
      mp3.playMp3FolderTrack(7);

        delay(500);
        pwm.setPWM(5, 0,500);
        pwm.setPWM(6, 0,420);
        pwm.setPWM(7, 0,500);
        pwm.setPWM(8, 0,420);

     for(int i=0;i<2;i++) {  
        pwm.setPWM(4, 0,130);
        delay(100); 
        pwm.setPWM(4, 0,300);
        delay(300); 
     }
delay(1000);

        pwm.setPWM(4, 0,130);
        delay(100); 
        pwm.setPWM(4, 0,300);
        delay(300); 
        pwm.setPWM(4, 0,130);
        delay(100); 
        pwm.setPWM(4, 0,300);
        delay(600);
        pwm.setPWM(4, 0,130);
        delay(100); 
        pwm.setPWM(4, 0,300);
        Serial.println("here");
        delay(1300); 
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);
        delay(2800); 
        pwm.setPWM(4, 0,130);
        delay(80); 
        pwm.setPWM(4, 0,300);
        delay(200); 

        pwm.setPWM(4, 0,130);
        delay(80); 
        pwm.setPWM(4, 0,300);
        delay(200); 
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);
        delay(1700); 
      Serial.println("CP  1");

        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);
        delay(3750);

        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);

        delay(1700);
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);

        delay(1500);
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);


        delay(2750);
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);

        delay(300);
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);

        delay(200);
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);

        delay(200);
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);


        delay(200);
        pwm.setPWM(4, 0,130);
        delay(150); 
        pwm.setPWM(4, 0,300);
        flag = 1;   
      }
   }
   pwm.setPWM(4, 0,130);
     delay(250);
     mp3.playMp3FolderTrack(8);
     delay(1000);
     pwm.setPWM(4, 0,300);
     mp3.stop();

   
        while(1) {
          delay(150);
          if(digitalRead(2) == HIGH) {
            mp3.stop();
            mode++; 
            delay(500);
            return; 
          }
        }
}

void easterEgg() {
  mp3.playMp3FolderTrack(17);
  delay(500);
}

void joyStickOnly1() {      
  y = map(analogRead(A1), 0, 1023, 380, 300); 
  x = map(analogRead(A0), 0, 1023, 240,330);

  ym = map(analogRead(A3), 0, 1023,500, 130);


  if(digitalRead(4) ==HIGH) { 
      pwm.setPWM(5, 0,455);
      pwm.setPWM(6, 0,420);
      pwm.setPWM(7, 0,420);
      pwm.setPWM(8, 0,420);
  }else {
    pwm.setPWM(5, 0,500);
    pwm.setPWM(6, 0,500);
    pwm.setPWM(7, 0,500);
    pwm.setPWM(8, 0,500);
  }
  pwm.setPWM(0, 0,x);
  pwm.setPWM(1, 0,x + 20);
  pwm.setPWM(2, 0,y);
  pwm.setPWM(3, 0,y + 15);
  pwm.setPWM(4, 0,ym);


    if(digitalRead(2) == HIGH) {
    mp3.stop();
    mode++; 
    return; 
  }
  delay(2);
}

void joyStickOnly2() {           

  y = map(analogRead(A1), 0, 1023, 380,300); 
  x = map(analogRead(A0), 0, 1023, 240, 330);

  ym = map(analogRead(A3), 0, 1023, 500,130);


  if(digitalRead(4) ==HIGH) { 
      pwm.setPWM(5, 0,470);
      pwm.setPWM(6, 0,420);
      pwm.setPWM(7, 0,420);
      pwm.setPWM(8, 0,420);
  }else {
    pwm.setPWM(5, 0,500);
    pwm.setPWM(6, 0,500);
    pwm.setPWM(7, 0,500);
    pwm.setPWM(8, 0,500);
  }
  pwm.setPWM(0, 0,x);
  pwm.setPWM(1, 0,x);
  pwm.setPWM(2, 0,y);
  pwm.setPWM(3, 0,y);
  pwm.setPWM(4, 0,ym);
  delay(2);
  totalSecret = 0;  
  secSecret = millis(); 
  while(digitalRead(4) == HIGH){
    Serial.println(totalSecret);
      pwm.setPWM(5, 0,470);
      pwm.setPWM(6, 0,420);
      pwm.setPWM(7, 0,420);
      pwm.setPWM(8, 0,420); 
        totalSecret = (double)(millis() - secSecret) / CLOCKS_PER_SEC;
        if(totalSecret > 8)
            easterEgg();
          }
    if(digitalRead(2) == HIGH) {
    mp3.stop();
    mode++; 
    return; 
  }
        
}
