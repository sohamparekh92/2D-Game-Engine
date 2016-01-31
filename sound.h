#include <vector>
#include <SDL.h>
#include <SDL/SDL_mixer.h>


class SDLSound {
public:
  SDLSound();
  ~SDLSound();

  void startMusic();
  void stopMusic();      

private:
  int volume;
  Mix_Music *music;
  int audioRate;
  int audioChannels;
  int audioBuffers;
  std::vector<int> channels;
  SDLSound(const SDLSound&);
  SDLSound& operator=(const SDLSound&);
};

