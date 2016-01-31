#include <string>
#include <iostream>
#include <ctime>
#include "sound.h"
using std::string;

SDLSound::~SDLSound() {

  Mix_HaltMusic();
  Mix_FreeMusic(music);
  Mix_CloseAudio();
}

SDLSound::SDLSound() : 
  volume(SDL_MIX_MAXVOLUME/4), 
  music(NULL),
  audioRate(22050), 
  audioChannels(2), 
  audioBuffers(4096),
  channels() 
{
  if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, 
                   audioBuffers)){
    throw string("Unable to open audio!");
  }
  music = Mix_LoadMUS("sound/musicBack.mp3");

  if (!music) throw string("Couldn't load musicBack.mp3")+Mix_GetError();

  startMusic();

}

void SDLSound::startMusic() {
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(music, -1);
}

void SDLSound::stopMusic() {
  Mix_HaltMusic();
  Mix_FreeMusic(music);
}

