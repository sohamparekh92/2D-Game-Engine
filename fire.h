#ifndef FIRE__H
#define FIRE__H
#include <string>
#include "drawable.h"
#include "explodingSprite.h"

class Fire : public Drawable {
public:
  Fire(const std::string&, double);
  Fire(const Fire& s);
  virtual ~Fire(); 
  Fire& operator=(const Fire&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void explode();
  virtual void draw() const;
  virtual void update(Uint32 ticks);

private:
  const Frame * frame;
  double scaleFactor;
  SDL_Surface* scaledSurface;
  float  ticksSinceLastExplostion;
  bool exploded;
  bool lock;
  ExplodingSprite* explosion;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int getDistance(const Fire*) const;
  int getSuperRandom();
static int displacementFactor;
};
#endif
