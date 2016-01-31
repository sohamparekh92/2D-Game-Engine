#include "scoreboard.h"

Scoreboard::Scoreboard(): score(0), health(25), win(false), lose(false), lock(false) { }

Scoreboard& Scoreboard::getInstance()
{
 static Scoreboard instance;
 return instance;
}

void Scoreboard::scoreUp(int n)
{
 if(!win && !lose )
 {
  score += n;
 }
}

void Scoreboard::won()
{
 if(!lock)
 {
  win = true;
  lock = true;
 }
}

void Scoreboard::reset()
{
 health = 25;
 win = false;
 lose = false;
 lock = false;
}

void Scoreboard::decreaseHealth(int n)
{
 if(!win && !lose )
 {
  if(health>=n)
  health -= n;
  else
  health = 0;
 }
}

void Scoreboard::scoreDown()
{
 if(score>0)
 --score;
}

void Scoreboard::increaseHealth()
{
 if(health<25)
 ++health;
}

void Scoreboard::scoreDown(int n)
{
 if(score>=n)
 score -= n;
}
