#include <RGBmatrixPanel.h>
#include <Wire.h>

#define CLK 8
#define OE 9
#define LAT 10
#define A A0
#define B A1
#define C A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

//Player1
int p1X;
int p1Y;
char d1 = 'n';
bool p1Collided = false;
bool hasP1Moved = false;

//Player 2
int p2X;
int p2Y;
int d2 = 'n';
bool p2Collided = false;
bool hasP2Moved = false;

//GameGrid
char gameGrid[16][32];

void setup() {

  initializePlayer1();
  initializePlayer2();
  
  matrix.begin();
  Serial.begin(9600);
  Wire.begin(9);

  Wire.onReceive(storeReceivedDirections);

}

void loop() {

  while(!p1Collided && !p2Collided) {
    
    showPlayer1();
    showPlayer2();

    if(hasP1Moved && hasP2Moved) {
     
      movePlayer1();
      movePlayer2();
      p1Collided = didP1Collide();
      p2Collided = didP2Collide();
      
    }
    
     delay(200);
     
    recordPlayersPositions();
  }

  if(p1Collided || p2Collided) {

    showGameOverMessage();
  }

  delay(3000);

  if(p1Collided) {

    showBlueWin();
    
  } else if(p2Collided) {

    showRedWin();
  }

  delay(3000);
}

void recordPlayersPositions() {

  gameGrid[p1Y][p1X] = 't';
  gameGrid[p2Y][p2X] = 't';
  
}

void showPlayer1() {

  matrix.drawPixel(p1X, p1Y, matrix.Color333(7, 0, 0));
}

void showPlayer2() {

  matrix.drawPixel(p2X, p2Y, matrix.Color333(0, 0, 7));
  
}

void initializePlayer1() {

  randomSeed(analogRead(3));

  p1X = random(0, 31);
  p1Y = random(0, 15);
}

void initializePlayer2() {

  p2X = random(0, 31);
  p2Y = random(0, 15);
}

void storeReceivedDirections(char directions) {

  char p1D = Wire.read();
  char p2D = Wire.read();

  if(p1D != 'n') {

    d1 = p1D;
    hasP1Moved = true;
  
  } else if (p2D != 'n') {

    d2 = p2D;
    hasP2Moved = true;
  }
}

void movePlayer1() {
   
  if(d1 == 'U') {

    p1Y++;
  
  } else if(d1 == 'D') {

    p1Y--;
  
  } else if(d1 == 'R') {

    p1X++;
    
  } else if(d1 == 'L') {

    p1X--;
    
  } 
}

void movePlayer2() {
   
  if(d2 == 'u') {

    p2Y++;
  
  } else if(d2 == 'd') {

    p2Y--;
  
  } else if(d2 == 'r') {

    p2X++;
    
  } else if(d2 == 'l') {

    p2X--;
    
  }
}
  bool didP1Collide() {

     return (gameGrid[p1Y][p1X] == 't') || p1X > 31 || p1X < 0 || p1Y < 0 || p1Y > 15;
  }

  bool didP2Collide() {

    return (gameGrid[p2Y][p2X] == 't') || p2X > 31 || p2X < 0 || p2Y < 0 || p2Y > 15;
  }
  
  void showGameOverMessage() {

    matrix.fillScreen(0);

    matrix.setCursor(4, 0);
    matrix.setTextColor(matrix.Color333(7,0,7));
    
    matrix.print('T');
    matrix.print('R');
    matrix.print('O');
    matrix.print('N');

    matrix.setCursor(4, 9);
    
    matrix.print('O');
    matrix.print('V');
    matrix.print('E');
    matrix.print('R');
  }

void  showRedWin() {

    matrix.fillScreen(0);

    matrix.setCursor(8, 5);
    matrix.setTextColor(matrix.Color333(7,0,0));
    
    matrix.print('W');
    matrix.print('I');
    matrix.print('N');
    
 }

 void  showBlueWin() {

    matrix.fillScreen(0);

    matrix.setCursor(8, 5);
    matrix.setTextColor(matrix.Color333(0,0,7));
    
    matrix.print('W');
    matrix.print('I');
    matrix.print('N');
    
 }


