#include <iostream>
#include "ioManager.h"
//This is a singleton class dedicated to keep a track of the progress made in the game
//somewhat similar to clock class
class Scoreboard
{
 public:
 static Scoreboard& getInstance();
 void scoreUp() { ++score; }
 void scoreUp(int);
 void scoreDown();
 void scoreDown(int);
 void decreaseHealth(int);
 void increaseHealth();
 void resetHealth() { health = 25; }
 void reset();
 void won();
 void lost() { lose = true; }
 bool hasWon() { return win; }
 bool hasLost() { return lose; }
 int getHealth() { return health; }
 int getScore() { return score; }

 private:
 int score;
 int health;
 bool win;
 bool lose;
 bool lock;
 Scoreboard();
 Scoreboard(const Scoreboard&);
 Scoreboard& operator=(const Scoreboard&);
};
