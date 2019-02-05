#include <Wire.h>

int p1XPin = A0;
int p1YPin = A1;

int p2XPin = A2;
int p2YPin = A3;

char d1;
char d2;

void setup() {
  
  pinMode(p1XPin, INPUT);
  pinMode(p1YPin, INPUT);

  Wire.begin();
  
}

void loop() {

  readDirection1();
  readDirection2();
  
  Wire.beginTransmission(9);
  sendPlayerDirection();
  Wire.endTransmission();

}

void sendPlayerDirection() {

  Wire.write(d1);
  Wire.write(d2);

  d1 = 'n';
  d2 = 'n';
}

void readDirection1() {

  int x = analogRead(p1XPin);
  int y = analogRead(p1YPin);

  if(x == 1023) {

    d1 = 'R';
    
  } else if(x == 0) {

    d1 = 'L';
    
  } else if(y == 1023) {

    d1 = 'U';
    
  } else if(y == 0) {

    d1 = 'D';
    
  }
}

 void readDirection2() {

  int x = analogRead(p2XPin);
  int y = analogRead(p2YPin);

  if(x == 1023) {

    d2 = 'r';
    
  } else if(x == 0) {

    d2 = 'l';
    
  } else if(y == 1023) {

    d2 = 'u';
    
  } else if(y == 0) {

    d2 = 'd';
    
  } 
}


