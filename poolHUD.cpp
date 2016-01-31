#include<iostream>
#include "ioManager.h"
#include "drawable.h"
#include "aaline.h"
#include "poolHUD.h"


poolHUD::poolHUD(): poolHUD_WIDTH(175), 
poolHUD_HEIGHT(100), 
currentTime(Clock::getInstance().getSeconds()) 
{}

void poolHUD::drawHUD( int x, int y, SDL_Surface * screen, bool toggleHUD,unsigned bulletList,unsigned freeList) {
  if(!toggleHUD) return;
  Draw_AALine(screen, x, y+poolHUD_HEIGHT/2, 
                     x+poolHUD_WIDTH,y+poolHUD_HEIGHT/2, 
                    poolHUD_HEIGHT, 0xff, 0x2, 0x2, 0xff/5);
 IOManager::getInstance().printMessageValueAt("Bullet List: ",bulletList, 810, 60);
 IOManager::getInstance().printMessageValueAt("Free List: ", freeList, 810, 80);
 IOManager::getInstance().printMessageAt("Press F2 to toggle", 810, 110);
}




