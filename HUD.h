#include<iostream>
#include "drawable.h"
#include "ioManager.h"
#include "aaline.h"
#include "clock.h"
class HUD
{
public:
HUD();
~HUD() {}
void setTime() { currentTime = Clock::getInstance().getSeconds(); }
unsigned int getTime() { return currentTime; }
void drawHUD( int x, int y, SDL_Surface * screen, bool);
private:
const int HUD_WIDTH; 
const int HUD_HEIGHT;
mutable unsigned int currentTime;
HUD(const HUD&);
HUD& operator=(const HUD&);
};


