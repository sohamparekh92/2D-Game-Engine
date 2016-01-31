#include<iostream>
#include "ioManager.h"
#include "drawable.h"
#include "aaline.h"
#include "HUD.h"


HUD::HUD(): HUD_WIDTH(250), 
HUD_HEIGHT(240), 
currentTime(Clock::getInstance().getSeconds()) 
{}

void HUD::drawHUD( int x, int y, SDL_Surface * screen, bool toggleHUD) {
  if(!toggleHUD) return;
  Draw_AALine(screen, x, y+HUD_HEIGHT/2, 
                     x+HUD_WIDTH,y+HUD_HEIGHT/2, 
                    HUD_HEIGHT, 0xff, 0x2, 0x2, 0xff/5);
 IOManager::getInstance().printMessageValueAt("TIME: ", Clock::getInstance().getSeconds(), 60, 50);
 IOManager::getInstance().printMessageValueAt("FPS: ", Clock::getInstance().getAvgFps(), 60, 70);
 IOManager::getInstance().printMessageAt("use A S D W to move", 60, 100);
 IOManager::getInstance().printMessageAt("LEFT DOWN", 60, 120);
 IOManager::getInstance().printMessageAt("RIGHT UP", 60, 140);
 IOManager::getInstance().printMessageAt("Press SPACE to shoot", 60, 170);
 IOManager::getInstance().printMessageAt("Press 'ESC' to Quit", 60, 200);
 IOManager::getInstance().printMessageAt("Press 'G' for God mode", 60, 220);
 IOManager::getInstance().printMessageAt("Press 'R' to Reset", 60, 240);
}




