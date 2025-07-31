#include "Matrix_RKAG.h"

#include "SPI.h"
#include "Wire.h"


byte matrix1[8][8];
byte matrix2[8];
int x_move = 1;
int y_move = 1;
int x_pos = 2;
int y_pos = 2;
int x_pos_next = 0;
int y_pos_next = 0;
int counter = 0;
int x_pos_pad = 0;
int moved = 0;
float timescale = 2;
int blinken = 0;

void setup() {
  Serial.begin(9600);
  matrix.init();
 
}


void loop() {
  Serial.println("section:1");
  for(int i = 0; i < 8; i++)
  {
    matrix2[i] = 0;
  }
  for(int x = 0; x < 8; x++)
  {
    for(int y = 0; y < 8; y++)
    {
      matrix1[x][y] = 0;
    }
  }
  matrix.read_io();
  Serial.println(matrix.potentiometer_0/128+1);

  Serial.println("section:2");
    
  switch(matrix.potentiometer_0/128+1)
  {
    case 1: matrix1[0][0] = 1;
            matrix1[0][1] = 1;
            break;
    case 2: matrix1[0][0] = 1;
            matrix1[0][1] = 1;
            matrix1[0][2] = 1;
            break;
    case 3: matrix1[0][1] = 1;
            matrix1[0][2] = 1;
            matrix1[0][3] = 1;
            break;
    case 4: matrix1[0][2] = 1;
            matrix1[0][3] = 1;
            matrix1[0][4] = 1;
            break;
    case 5: matrix1[0][3] = 1;
            matrix1[0][4] = 1;
            matrix1[0][5] = 1;
            break;            
    case 6: matrix1[0][4] = 1;
            matrix1[0][5] = 1;
            matrix1[0][6] = 1;
            break;
    case 7: matrix1[0][5] = 1;
            matrix1[0][6] = 1;
            matrix1[0][7] = 1;
            break;
    case 8: matrix1[0][6] = 1;
            matrix1[0][7] = 1;
            break;
 }

 if(counter > timescale && x_pos - 1 != -1)
 {
  counter = 0;
  timescale -= 0.1;
  do{
    if(x_move == 1 && x_pos + 1 == 8) x_move = 0;
    if(x_move == 0 && x_pos - 1 == -1) x_move = 1;
    if(y_move == 1 && y_pos + 1 == 8) y_move = 0;
    if(y_move == 0 && y_pos - 1 == -1) y_move = 1;
    
    if(x_move == 1) x_pos_next = x_pos + 1;
    if(x_move == 0) x_pos_next = x_pos - 1;
    if(y_move == 1) y_pos_next = y_pos + 1;
    if(y_move == 0) y_pos_next = y_pos - 1;
  
    if(matrix1[x_pos_next][y_pos_next] == 1) x_move = 1;
    else{moved = 1; x_pos = x_pos_next; y_pos = y_pos_next;}
    
  }while(moved != 1); 
 }
  matrix1[x_pos][y_pos] = 1;
  moved = 0;
  counter++;
 
 if(x_pos - 1 == -1)
 {
  if(blinken % 2 == 0)
  {
   matrix1[x_pos][y_pos] = 1;
  }
  if(blinken % 2 == 1)
  {
   matrix1[x_pos][y_pos] = 0;
  }
  if(blinken > 10)
  {
    x_move = 1;
    y_move = 1;
    x_pos = 2;
    y_pos = 2;
    timescale = 5;
    blinken = 0;
  }
  blinken++;
 }
 

  Serial.println(matrix1[2][2]);

  Serial.println("section:3");

 
    for(int x = 0; x < 8; x++)
    {
      for(int y = 0; y < 8; y++)
      {
        if(matrix1[x][y] == 1)
        {
                    Serial.println(x);
          // x_pos_pad = 2^x;
          // x_pos_pad = pow(2, (7 - x));
          x_pos_pad = 0x01 << (7 - x);

          Serial.print("x-->");
          Serial.println(7 - x);
          Serial.print("y-->");
          Serial.println(y);
          Serial.print("x_pos_pad-->");
          Serial.println(x_pos_pad);
          
          switch(y)
          {    
            case 0: matrix2[0] += x_pos_pad;  break;
            case 1: matrix2[1] += x_pos_pad;  break;
            case 2: matrix2[2] += x_pos_pad;  break;
            case 3: matrix2[3] += x_pos_pad;  break;
            case 4: matrix2[4] += x_pos_pad;  break;
            case 5: matrix2[5] += x_pos_pad;  break;
            case 6: matrix2[6] += x_pos_pad;  break;
            case 7: matrix2[7] += x_pos_pad;  break;
          }
        }
      }
    }
  Serial.println("section:4");
  
  Serial.println(matrix2[0]);
  matrix.write(matrix2[0], matrix2[1], matrix2[2], matrix2[3], matrix2[4], matrix2[5], matrix2[6], matrix2[7]);
}
