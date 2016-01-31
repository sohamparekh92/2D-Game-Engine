#ifndef ENEMY__H
#define ENEMY__H
#include <string>
#include <vector>
#include "drawable.h"
#include "enemyBullets.h"
#include "explodingSprite.h"
#include "collisionStrategy.h"
#include "player.h"

class Enemy : public Drawable {
public:
  Enemy(const std::string&, EnemyBullets* bulls, Player* p);
  virtual ~Enemy();

  virtual void pressed(int);
  virtual void explode();

  bool collidedWith(const Drawable* d) const {
    return strategy->execute(enemy, *d);
  }


  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

protected:
  Sprite enemy;
  Player* player;
  Vector2f originalVelocity;
  const std::vector<Frame *> frames;
  ExplodingSprite* explosion;
  CollisionStrategy* strategy;
  int worldWidth;
  int worldHeight;
  EnemyBullets* bullets;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastShoot;
  float timeSinceLastShift;
  float timeSinceLastFrame;
  float ticksSinceLastExplostion;
  int frameWidth;
  int frameHeight;
  bool right;
  bool shift;
  bool up;
  bool exploded;
  bool doNotShoot;
  int pressedKey;
  int randomFactor;
  int speed;

  void shoot();
  void advanceFrame(Uint32 ticks);
  int getSuperRandom();
  Enemy(const Enemy&);
  Enemy& operator=(const Enemy&);
};
#endif
