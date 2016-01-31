#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

unsigned int Clock::delayTime = 0;

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  ticks(0),
  startTicks(0), 
  totalTicks(0),
  capRate(Gamedata::getInstance().getXmlInt("frameCap")),
  frames(0),
  started(false), 
  paused(false), 
  sloMo(false),
  cap(Gamedata::getInstance().getXmlBool("framesAreCapped")),
 
  sumOfTicks(SDL_GetTicks()),
  pos( Gamedata::getInstance().getXmlInt("clock/locX"),
       Gamedata::getInstance().getXmlInt("clock/locY"))
  {
  start();
}

void Clock::draw() const { 
  IOManager::getInstance().
    printMessageValueAt("Seconds: ", getSeconds(), pos[0], pos[1]);
  IOManager::getInstance().
    printMessageValueAt("fps: ", getTicksFps(), pos[0], pos[1]+20);
  IOManager::getInstance().
    printMessageValueAt("delay: ", delayTime, pos[0], pos[1]+40);
}

void Clock::update() { 
  frames++;
  totalTicks = SDL_GetTicks() - startTicks;
  ticks = totalTicks - sumOfTicks;
  sumOfTicks += ticks;
  if(cap)
  {
   if((unsigned)getAvgFps()>capRate)
   delayTime++;
   if(delayTime>0 && (unsigned)getAvgFps()<capRate)
   delayTime--;
   SDL_Delay(delayTime);  
  }
}

unsigned int Clock::getTicksSinceLastFrame() const {
  return ticks;
}

void Clock::toggleSloMo() {
  sloMo = ! sloMo;
}

int Clock::getTicksFps() const { 
  if ( ticks > 0 ) 
  return 1000/ticks;
  return 0;
}

int Clock::getAvgFps() const { 
  if ( getSeconds() > 0 ) 
  return frames/getSeconds();
  return 0;
}

void Clock::reset()
{
 startTicks += totalTicks;
 sumOfTicks =0;
 frames=0;
 ticks=0;
}

void Clock::start() { 
  started = true; 
  paused = false; 
}

void Clock::pause() { 
  paused = true;
}

void Clock::unpause() { 
  paused = false;
}

