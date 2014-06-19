/*  Program: Ping Pong Scoreboard
    Programmer:Kyle Butler
    Date Created: 6/18/14
    Date Modified:
    Description: This program is designed to keep score of a ping
    pong match (volleyball as well i spose!). When a player has 
    scored a point, they hit their corresponding push button, which
    increments their score. When a player reaches a score of 21
    or higher, and has beaten their opponent by at least 2 points,
    "WINNER!" will be displayed next to their name. At the end of 
    the game (or at any point during), the reset button can be hit
    and the players scores will be reset to zero.
    
    ~*~Note~*~
    In my original code I didnt use any functions. Although the
    functionality was all there, I decided to break the program
    up a little bit. If it had been a larger program, having the 
    functions, instead of the code all in the main, would have been
    very helpful for any needed troubleshooting.
      As well, the kyle and alex variables can clearly be changed to
    player1, player2 or whatver your heart so desires!
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int kyle_score=0;// player one incremented varible for score
int alex_score=0;
int reset;// var read from reset button
int kyle=10;// pin for player 1 is read on d10
int alex=9;// pin for player 2 is read on d9
boolean flag=true;// prevents unwanted incrementing

void setup() 
{ 
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
  lcd.setCursor(0,0);
  lcd.print("Kyle:0");// print p1's name
  lcd.setCursor(0,1);
  lcd.print("Alex:0");// print p2's name
  pinMode(8, INPUT);// declare I/O
  pinMode(9, INPUT);
  pinMode(10, INPUT);
}

void loop()
{
  alex=digitalRead(9);
  kyle=digitalRead(10);
  reset=digitalRead(8);
  
  // increment p1 variable
  if((kyle==LOW)&&(flag==true))  
  {
    kyle_plus();
  } 

  if((alex==LOW)&&(flag==true))//
  {
    alex_plus();
  }
  
  //resets the scores
  if((reset==LOW)&&(flag==true))
  {
    new_game();// call game reset function
  }
  
  // allow for another button hit
  if((kyle==HIGH)&&(alex==HIGH)&&(reset==HIGH))
  {
    flag=true;  // reset flag when button has been released
  }
  
  // check for a winner
  if((kyle_score>=21)&&((kyle_score-alex_score)>=2))
  {
    kyle_win();// call function to display the winner
  }
  
  if((alex_score>=21)&&((alex_score-kyle_score)>=2))
  {
    alex_win();
  }
}

void kyle_plus()
{
   kyle_score++;// increment p1's score
   lcd.setCursor(5,0);
   lcd.print(kyle_score);// print p1's score
   flag=false;// prevent further incrementing until button is released 
}

void alex_plus()
{
   alex_score++;
   lcd.setCursor(5,1);
   lcd.print(alex_score);
   flag=false; 
}

void new_game()
{
    alex_score=0;// reset the scores
    kyle_score=0;
    lcd.setCursor(5,0);
    lcd.print(kyle_score);// print the score of "0"
    lcd.setCursor(5,1);
    lcd.print(alex_score);
    lcd.setCursor(6,0);
    lcd.print("          ");// clears latent # if scores were in the 10's 
    lcd.setCursor(6,1);
    lcd.print("          ");
}

void kyle_win()
{
    lcd.setCursor(8,0);
    lcd.print("WINNER!");// prints winner next to p1's name
}

void alex_win()
{
    lcd.setCursor(8,1);
    lcd.print("WINNER!");
}



