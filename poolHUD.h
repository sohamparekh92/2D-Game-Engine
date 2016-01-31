#include<iostream>
#include "drawable.h"
#include "ioManager.h"
#include "aaline.h"
#include "clock.h"
class poolHUD
{
public:
poolHUD();
~poolHUD() {}
void setTime() { currentTime = Clock::getInstance().getSeconds(); }
unsigned int getTime() { return currentTime; }
void drawHUD( int x, int y, SDL_Surface * screen, bool, unsigned, unsigned);
private:
const int poolHUD_WIDTH; 
const int poolHUD_HEIGHT;
mutable unsigned int currentTime;
poolHUD(const poolHUD&);
poolHUD& operator=(const poolHUD&);
};


