
#ifndef CLOCK_H
#define CLOCK_H
#include <SDL.h>
#include <string>
#include <deque>
#include "vector2f.h"

class Manager;

class Clock {
public:
  static Clock& getInstance();  // This class is a Singleton
  unsigned int getTicksSinceInit() const { return startTicks; }//sumOfTicks; }
  unsigned int getSeconds() const { return sumOfTicks/1000; }

  void toggleSloMo();
  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }

  int getAvgFps() const;
  int getTicksFps() const;
  void reset(); 
  void start();
  void pause();
  void unpause();
  void draw() const;  // For debugging

private:
  unsigned int ticks;
  unsigned int startTicks;
  unsigned int totalTicks;
  static  unsigned int delayTime; //Changes dynamically to achieve the desired framerate
  unsigned int capRate;
  unsigned int frames;
  bool started;
  bool paused;
  bool sloMo;
  bool cap;

  unsigned int sumOfTicks;
  Vector2f pos;


  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
  friend class Manager;
  void update();  // Increments time/ticks
  unsigned int getTicksSinceLastFrame() const;
};

#endif

