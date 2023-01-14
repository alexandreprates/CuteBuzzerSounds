#ifndef CuteBuzzerSounds_h
#define CuteBuzzerSounds_h
#include <avr/power.h>
#include "Sounds.h"

class CuteBuzzerSoundsClass
{
  public:

    void init(int buzzerPin);
    void playTone (float noteFrequency, long noteDuration, int silentDuration, bool isMicro = false);
    void toneWithVolume(float noteFrequency, long noteDuration, int volume);
    void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
    void playSound(int soundName);

  private:
    int buzzerPin;
};

extern CuteBuzzerSoundsClass cute;

#endif
