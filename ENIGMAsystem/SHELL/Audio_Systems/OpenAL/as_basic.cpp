#include <stdio.h>
#include <stddef.h>
#include "alure/include/AL/alure.h"


namespace enigma
{
  struct sound
  {
    ALuint src, buf; // The source-id and buffer-id of the sound data
    int loaded;   // Degree to which this sound has been loaded successfully
    bool idle;    // True if this sound is not being used, false if playing or paused.
    bool playing; // True if this sound is playing; not paused or idle.
    sound(): src(0), buf(0), loaded(0), idle(1), playing(0) {}
  };
  
  sound *sounds;
  size_t numSounds;
  extern int sound_idmax;
  
  static void eos_callback(void *soundID, ALuint src)
  {
    puts ("The sound has stopped. The universe is at peace.");
    sounds[(ptrdiff_t)soundID].playing = false;
    sounds[(ptrdiff_t)soundID].idle = true;
  }

  int audiosystem_initialize()
  {
    numSounds = sound_idmax > 0 ? sound_idmax : 1;
    sounds = new sound[numSounds];
    
    if(!alureInitDevice(NULL, NULL)) {
      fprintf(stderr, "Failed to open OpenAL device: %s\n", alureGetErrorString());
      return 1;
    }
    
    for (size_t i = 0; i < numSounds; i++)
    {
      alGenSources(1, &sounds[i].src);
      if(alGetError() != AL_NO_ERROR) {
        fprintf(stderr, "Failed to create OpenAL source!\n");
        return 1;
      }
      sounds[i].loaded = 1;
    }
    
    return 0;
  }
  
  int sound_add_from_buffer(int id, void* buffer, size_t bufsize)
  {
    if (sounds[id].loaded != 1)
      return 1;
    
    ALuint& buf = sounds[id].buf;
    buf = alureCreateBufferFromMemory((ALubyte*)buffer, bufsize);
    
    if(!buf) {
      fprintf(stderr, "Could not load sound %d: %s\n", id, alureGetErrorString());
      return 1;
    }
    
    alSourcei(sounds[id].src, AL_BUFFER, buf);
    sounds[id].loaded = 2;
    return 0;
  }
  
  void audiosystem_update(void) { alureUpdate(); }
  
  void audiosystem_cleanup()
  {
    for (size_t i = 0; i < numSounds; i++) 
    {
      switch (sounds[i].loaded)
      {
        case 2:
          alDeleteBuffers(1, &sounds[i].buf);
        case 1:
          alDeleteSources(1, &sounds[i].src);
      }
    }
    
    alureShutdownDevice();
  }
};

bool sound_play(int sound) // Returns nonzero if an error occurred
{
  enigma::sound &snd = enigma::sounds[sound];
  return snd.idle = !(snd.playing = (alurePlaySource(snd.src, enigma::eos_callback, (void*)sound) != AL_FALSE));
}

const char* sound_get_audio_error() {
  return alureGetErrorString();
}

int amain()
{
  /*puts("Initializing sound.");
  if (enigma::audiosystem_initialize())
    return 1;
  
  puts("Loading sound.");
  FILE *afile = fopen("FancyPants.ogg","rb");
  if (!afile) return 1;
  fseek(afile,0,SEEK_END);
  const ALsizei flen = ftell(afile);
  char fdata[flen];
  fseek(afile,0,SEEK_SET);
  fread(fdata,1,flen,afile);
  puts("Decoding sound.");
  if (enigma::sound_add_from_buffer(0,fdata,flen))
    return 1;
  puts("Playing Sound.");
  sound_play(0);
  puts("Done.");*/
  return 0;
}