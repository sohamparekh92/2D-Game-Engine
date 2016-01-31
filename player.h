#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include "drawable.h"
#include "bullets.h"
#include "explodingSprite.h"
#include "collisionStrategy.h"

class Player : public Drawable {
public:
  Player(const std::string&, Bullets* bulls);
  virtual ~Player();

  virtual void pressed(int);
  virtual void shoot();
  virtual void explode();

  bool collidedWith(const Drawable* d) const {
    return strategy->execute(player, *d);
  }
  bool getRight() { return right; }
  
  void toggleGod() { god = !god; }
  bool getGod() { return god; }
 
  virtual Vector2f getOriginalVelocity() { return originalVelocity; }
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

protected:
  Sprite player;
  Vector2f originalVelocity;
  const std::vector<Frame *> frames;
  ExplodingSprite* explosion;
  CollisionStrategy * strategy;
  int worldWidth;
  int worldHeight;
  Bullets* bullets;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  float ticksSinceLastExplostion;
  int frameWidth;
  int frameHeight;
  int health;
  bool right;
  bool exploded;
  bool doNotShoot;
  bool god;
  int pressedKey;
  int speed;

  void decHealth();
  void advanceFrame(Uint32 ticks);
  int getSuperRandom();
  Player(const Player&);
  Player& operator=(const Player&);
};
#endif
