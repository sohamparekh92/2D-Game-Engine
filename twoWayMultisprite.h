#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include <vector>
#include "drawable.h"

class TwoWayMultiSprite : public Drawable {
public:
  TwoWayMultiSprite(const std::string&);
  virtual ~TwoWayMultiSprite(){}

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

protected:
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;
  
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;
  bool right;

  void advanceFrame(Uint32 ticks);
  int getSuperRandom();
  TwoWayMultiSprite(const TwoWayMultiSprite&);
  TwoWayMultiSprite& operator=(const TwoWayMultiSprite&);
};
#endif
