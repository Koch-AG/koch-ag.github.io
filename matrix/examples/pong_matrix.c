#include "SPI.h"
#include <Wire.h>
#include "NeoSWSerial.h"
#include "Matrix_RKAG.h"


//#define PLAYER1
#define PLAYER2


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
float timescale = 15;
byte pot_pos_0 = 0;
byte pot_pos_1 = 0;
byte pot_pos_0_last = 0;
byte pot_pos_1_last = 0;
byte score_player1 = 0;
byte score_player2 = 0;
byte score_player1_new = 0;
byte score_player2_new = 0;
int time_delay = 0;
byte flag = 0;
byte game_start = 0;
byte score_trans = 0;
byte pot_pos_1_new = 0;


NeoSWSerial mySerial(8, 9);

void setup() 
{
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  mySerial.begin(38400);
  Serial.begin(9600);
  matrix.init();

  delay(100);

  matrix.read_io();

 #ifdef PLAYER2
  pot_pos_1 = matrix.potentiometer_0/128+1;
  mySerial.write(pot_pos_1);
  if(mySerial.available()>0)
  {
    score_trans = mySerial.read();
    if(((score_trans & 0b11110000) >> 4) < 11) score_player1 = (score_trans & 0b11110000) >> 4;
    if((score_trans & 0b00001111) < 11) score_player2 = score_trans & 0b00001111;
    game_start = 1;
  }
#endif

#ifdef PLAYER1
  pot_pos_0 = matrix.potentiometer_0/128+1;

  if(mySerial.available()> 0 && mySerial.read() > 0)
  {
    pot_pos_1 = mySerial.read();
  }
  score_trans = (score_player1 << 4) | (score_player2 & 0b11110000);
  mySerial.write(score_trans);
#endif
}


void loop() 
{
  
#ifdef PLAYER1
  if(!game_start && !score_player1 && !score_player2)
  {
  	matrix.write(231, 165, 231, 128, 151, 212, 181, 151);
  }
#endif

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

  pot_pos_0_last = pot_pos_0;

  matrix.read_io();

#ifdef PLAYER2
  pot_pos_1 = matrix.potentiometer_0/128+1;
  mySerial.write(pot_pos_1);

  if(mySerial.available()>0)
  {
    score_trans = mySerial.read();
    delay(5);
    score_player1_new = (score_trans & 0b11110000) >> 4;
    score_player2_new = score_trans & 0b00001111;
    Serial.print("score_player1-->");
    Serial.println(score_player1_new);
    Serial.print("score_player2-->");
    Serial.println(score_player2_new);
    if((score_player1_new > score_player1 || score_player1_new == 0) && (score_player1_new < 11) && (score_player1_new < (score_player1 + 2)))  score_player1 = score_player1_new;
    if((score_player2_new > score_player2 || score_player2_new == 0) && (score_player2_new < 11) && (score_player2_new < (score_player2 + 2)))  score_player2 = score_player2_new;
  }

    switch(score_player1)
    {
    	case 0: matrix1[0][1] = 1;
    			matrix1[0][2] = 1;
    			matrix1[0][3] = 1;
    			matrix1[0][4] = 1;
    			matrix1[0][5] = 1;
    			matrix1[1][1] = 1;
    			matrix1[1][5] = 1;
    			matrix1[2][1] = 1;
    			matrix1[2][2] = 1;
    			matrix1[2][3] = 1;
    			matrix1[2][4] = 1;
    			matrix1[2][5] = 1;
    			break;
    	case 1: matrix1[2][1] = 1;
    			matrix1[2][2] = 1;
    			matrix1[2][3] = 1;
    			matrix1[2][4] = 1;
    			matrix1[2][5] = 1;
    			break;
    	case 2: matrix1[0][1] = 1;
    			matrix1[1][1] = 1;
    			matrix1[2][1] = 1;
    			matrix1[2][2] = 1;
    			matrix1[2][3] = 1;
    			matrix1[1][3] = 1;
    			matrix1[0][3] = 1;
    			matrix1[0][4] = 1;
    			matrix1[0][5] = 1;
    			matrix1[1][5] = 1;
    			matrix1[2][5] = 1;
    			break;
    	case 3: matrix1[0][1] = 1;
    			matrix1[1][1] = 1;
    			matrix1[2][1] = 1;
    			matrix1[2][2] = 1;
    			matrix1[2][3] = 1;
    			matrix1[1][3] = 1;
    			matrix1[0][3] = 1;
    			matrix1[2][4] = 1;
    			matrix1[0][5] = 1;
    			matrix1[1][5] = 1;
    			matrix1[2][5] = 1;
    			break;
    	case 4: matrix1[0][1] = 1;
    			matrix1[0][2] = 1;
    			matrix1[0][3] = 1;
    			matrix1[1][3] = 1;
    			matrix1[2][1] = 1;
    			matrix1[2][2] = 1;
    			matrix1[2][3] = 1;
    			matrix1[2][4] = 1;
    			matrix1[2][5] = 1;
    			break;
    	case 5: matrix1[0][1] = 1;
    			matrix1[1][1] = 1;
    			matrix1[2][1] = 1;
    			matrix1[0][2] = 1;
    			matrix1[2][3] = 1;
    			matrix1[1][3] = 1;
    			matrix1[0][3] = 1;
    			matrix1[2][4] = 1;
    			matrix1[0][5] = 1;
    			matrix1[1][5] = 1;
    			matrix1[2][5] = 1;
    			break;
    	case 6: matrix1[0][1] = 1;
    			matrix1[1][1] = 1;
    			matrix1[2][1] = 1;
    			matrix1[0][2] = 1;
    			matrix1[2][3] = 1;
    			matrix1[1][3] = 1;
    			matrix1[0][3] = 1;
    			matrix1[0][4] = 1;
    			matrix1[2][4] = 1;
    			matrix1[0][5] = 1;
    			matrix1[1][5] = 1;
    			matrix1[2][5] = 1;
    			break;
    	case 7:	matrix1[0][1] = 1;
    			matrix1[1][1] = 1;
    			matrix1[2][1] = 1;
    			matrix1[2][2] = 1;
    			matrix1[2][3] = 1;
    			matrix1[2][4] = 1;
    			matrix1[2][5] = 1;
    			break;
    	case 8: matrix1[0][1] = 1;
    			matrix1[1][1] = 1;
    			matrix1[2][1] = 1;
    			matrix1[0][2] = 1;
    			matrix1[2][2] = 1;
    			matrix1[2][3] = 1;
    			matrix1[1][3] = 1;
    			matrix1[0][3] = 1;
    			matrix1[0][4] = 1;
    			matrix1[2][4] = 1;
    			matrix1[0][5] = 1;
    			matrix1[1][5] = 1;
    			matrix1[2][5] = 1;
    			break;
		case 9: matrix1[0][1] = 1;
    			matrix1[1][1] = 1;
    			matrix1[2][1] = 1;
    			matrix1[0][2] = 1;
    			matrix1[2][2] = 1;
    			matrix1[2][3] = 1;
    			matrix1[1][3] = 1;
    			matrix1[0][3] = 1;
    			matrix1[2][4] = 1;
    			matrix1[0][5] = 1;
    			matrix1[1][5] = 1;
    			matrix1[2][5] = 1;
    			break;
    }
    switch(score_player2)
    {
    	case 0: matrix1[5][1] = 1;
    			matrix1[5][2] = 1;
    			matrix1[5][3] = 1;
    			matrix1[5][4] = 1;
    			matrix1[5][5] = 1;
    			matrix1[6][1] = 1;
    			matrix1[6][5] = 1;
    			matrix1[7][1] = 1;
    			matrix1[7][2] = 1;
    			matrix1[7][3] = 1;
    			matrix1[7][4] = 1;
    			matrix1[7][5] = 1;
    			break;
    	case 1: matrix1[7][1] = 1;
    			matrix1[7][2] = 1;
    			matrix1[7][3] = 1;
    			matrix1[7][4] = 1;
    			matrix1[7][5] = 1;
    			break;
    	case 2: matrix1[5][1] = 1;
    			matrix1[6][1] = 1;
    			matrix1[7][1] = 1;
    			matrix1[7][2] = 1;
    			matrix1[7][3] = 1;
    			matrix1[6][3] = 1;
    			matrix1[5][3] = 1;
    			matrix1[5][4] = 1;
    			matrix1[5][5] = 1;
    			matrix1[6][5] = 1;
    			matrix1[7][5] = 1;
    			break;
    	case 3: matrix1[5][1] = 1;
    			matrix1[6][1] = 1;
    			matrix1[7][1] = 1;
    			matrix1[7][2] = 1;
    			matrix1[7][3] = 1;
    			matrix1[6][3] = 1;
    			matrix1[5][3] = 1;
    			matrix1[7][4] = 1;
    			matrix1[5][5] = 1;
    			matrix1[6][5] = 1;
    			matrix1[7][5] = 1;
    			break;
    	case 4: matrix1[5][1] = 1;
    			matrix1[5][2] = 1;
    			matrix1[5][3] = 1;
    			matrix1[6][3] = 1;
    			matrix1[7][1] = 1;
    			matrix1[7][2] = 1;
    			matrix1[7][3] = 1;
    			matrix1[7][4] = 1;
    			matrix1[7][5] = 1;
    			break;
    	case 5: matrix1[5][1] = 1;
    			matrix1[6][1] = 1;
    			matrix1[7][1] = 1;
    			matrix1[5][2] = 1;
    			matrix1[7][3] = 1;
    			matrix1[6][3] = 1;
    			matrix1[5][3] = 1;
    			matrix1[7][4] = 1;
    			matrix1[5][5] = 1;
    			matrix1[6][5] = 1;
    			matrix1[7][5] = 1;
    			break;
    	case 6: matrix1[5][1] = 1;
    			matrix1[6][1] = 1;
    			matrix1[7][1] = 1;
    			matrix1[5][2] = 1;
    			matrix1[7][3] = 1;
    			matrix1[6][3] = 1;
    			matrix1[5][3] = 1;
    			matrix1[5][4] = 1;
    			matrix1[7][4] = 1;
    			matrix1[5][5] = 1;
    			matrix1[6][5] = 1;
    			matrix1[7][5] = 1;
    			break;
    	case 7:	matrix1[5][1] = 1;
    			matrix1[6][1] = 1;
    			matrix1[7][1] = 1;
    			matrix1[7][2] = 1;
    			matrix1[7][3] = 1;
    			matrix1[7][4] = 1;
    			matrix1[7][5] = 1;
    			break;
    	case 8: matrix1[5][1] = 1;
    			matrix1[6][1] = 1;
    			matrix1[7][1] = 1;
    			matrix1[5][2] = 1;
    			matrix1[7][2] = 1;
    			matrix1[7][3] = 1;
    			matrix1[6][3] = 1;
    			matrix1[5][3] = 1;
    			matrix1[5][4] = 1;
    			matrix1[7][4] = 1;
    			matrix1[5][5] = 1;
    			matrix1[6][5] = 1;
    			matrix1[7][5] = 1;
    			break;
		case 9: matrix1[5][1] = 1;
    			matrix1[6][1] = 1;
    			matrix1[7][1] = 1;
    			matrix1[5][2] = 1;
    			matrix1[7][2] = 1;
    			matrix1[7][3] = 1;
    			matrix1[6][3] = 1;
    			matrix1[5][3] = 1;
    			matrix1[7][4] = 1;
    			matrix1[5][5] = 1;
    			matrix1[6][5] = 1;
    			matrix1[7][5] = 1;
    			break;
  }
#endif

#ifdef PLAYER1
  score_trans = (score_player1 << 4) | score_player2;
  mySerial.write(score_trans);

  delay(5);

  pot_pos_0 = matrix.potentiometer_0/128+1;
  if(mySerial.available()>0)
  {
    pot_pos_1_new = mySerial.read();
    if(pot_pos_1_new > 0)
    {
    	pot_pos_1 = pot_pos_1_new;
    }
  }

   

  switch(pot_pos_0)
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
  switch(pot_pos_1)
  {
    case 1: matrix1[7][0] = 1;
            matrix1[7][1] = 1;
            break;
    case 2: matrix1[7][0] = 1;
            matrix1[7][1] = 1;
            matrix1[7][2] = 1;
            break;
    case 3: matrix1[7][1] = 1;
            matrix1[7][2] = 1;
            matrix1[7][3] = 1;
            break;
    case 4: matrix1[7][2] = 1;
            matrix1[7][3] = 1;
            matrix1[7][4] = 1;
            break;
    case 5: matrix1[7][3] = 1;
            matrix1[7][4] = 1;
            matrix1[7][5] = 1;
            break;            
    case 6: matrix1[7][4] = 1;
            matrix1[7][5] = 1;
            matrix1[7][6] = 1;
            break;
    case 7: matrix1[7][5] = 1;
            matrix1[7][6] = 1;
            matrix1[7][7] = 1;
            break;
    case 8: matrix1[7][6] = 1;
            matrix1[7][7] = 1;
            break;
  }
	if(x_pos < 1 || x_pos > 6)
	  {
	  	time_delay++;
	  	if((x_pos < 1) && (flag == 0))
	  	{
	  		score_player2++;
	  		flag = 1;
	  	}
	  	if(x_pos > 6 && (flag == 0))
	  	{
	  		score_player1++;
	  		flag = 1;
	  	}
	  	if(time_delay > 50)
	  	{
		    x_move = !x_move;
		    y_move = 1;
		    x_pos = 3;
		    y_pos = 2;
		    timescale = 15;
		    time_delay = 1;
		    flag = 0;
		}
	  }
	  if(x_pos == 3 && y_pos == 2 && time_delay)
	  {
	  	time_delay++;
		if(time_delay > 50)
		{
			time_delay = 0;
		}
	  }
	  	

 if((counter > timescale) && ( x_pos > 0 || x_pos < 7) && !time_delay && game_start)
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
  
    if(matrix1[x_pos_next][y_pos_next] == 1) x_move = !(x_move);
    else{moved = 1; x_pos = x_pos_next; y_pos = y_pos_next;}
    
  }while(moved != 1); 
 }
  matrix1[x_pos][y_pos] = 1;
  moved = 0;
  counter++;
#endif

      for(int x = 0; x < 8; x++)
      {
        for(int y = 0; y < 8; y++)
        {
          if(matrix1[x][y] == 1)
          {
            x_pos_pad = 0x01 << (7 - x);
  
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

#ifdef PLAYER1
  if((score_player1 > 9 && score_player1 < 11) || (score_player2 > 9 && score_player2 < 11))
  {
  	game_start = 0;
  	if(score_player1 > 9)
  	{
  		matrix.write(60, 255, 189, 126, 60, 24, 60, 126);
  	}
  	else
  	{
  		matrix.write(0, 0, 0, 0, 0, 0, 00, 0);
  	}
  	time_delay++;
  	if(time_delay > 100)
  	{
	    x_move = !x_move;
	    y_move = !y_move;
	    x_pos = 3;
	    y_pos = 2;
	    timescale = 15;
	    time_delay = 0;
	    flag = 0;
	    score_player1 = 0;
	    score_player2 = 0;
	    game_start = 1;
	}
  }
#endif

#ifdef PLAYER2
  if((score_player1 > 9 && score_player1 < 11) || (score_player2 > 9 && score_player2 < 11))
  {
  	game_start = 0;
  	if(score_player2 > 9)
  	{
  		matrix.write(60, 255, 189, 126, 60, 24, 60, 126);
 	}
 	else
 	{
 		matrix.write(0, 0, 0, 0, 0, 0, 0, 0);
 	}
  	time_delay++;
  	if(time_delay > 100)
  	{
	    x_move = !x_move;
	    y_move = !y_move;
	    x_pos = 3;
	    y_pos = 2;
	    timescale = 15;
	    time_delay = 0;
	    flag = 0;
	    score_player1 = 0;
	    score_player2 = 0;
	    game_start = 1;
	}
  }
#endif

  if(game_start)
  {
  	matrix.write(matrix2[0], matrix2[1], matrix2[2], matrix2[3], matrix2[4], matrix2[5], matrix2[6], matrix2[7]);
  }
  	game_start = 1;
  
  delay(5); 
}