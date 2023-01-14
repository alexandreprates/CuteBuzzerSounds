#include "Arduino.h"
#include "CuteBuzzerSounds.h"

void CuteBuzzerSoundsClass::init(int aBuzzerPin) {
  buzzerPin = aBuzzerPin;
}

void CuteBuzzerSoundsClass::playTone(float noteFrequency, long noteDuration, int silentDuration, bool isMicro) {
  int  x;
  long delayAmount = (long)(1000000 / noteFrequency);
  long loopTime = (long)((noteDuration * 1000) / (delayAmount * 2));
  
  pinMode(buzzerPin, OUTPUT);
  for (x = 0; x < loopTime; x++) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(delayAmount);
  }
  pinMode(buzzerPin, INPUT);

  if (silentDuration == 0) {
    silentDuration = 1;
  }

  if (isMicro == false) {
    delay(silentDuration);
  } else {
    delayMicroseconds(silentDuration);
  }
}

void CuteBuzzerSoundsClass::toneWithVolume(float noteFrequency, long noteDuration, int volume) {
  int numberOfDelays = 7; //unknown magic number since it may not matter, test later
  int i = 0;
  int delayTime = 0;

  while (i < numberOfDelays) {
    i++;
    int tempNoteDuration = noteDuration / numberOfDelays - delayTime;
    CuteBuzzerSoundsClass::playTone(noteFrequency + 3 * sin(i * .2) / 5, tempNoteDuration, delayTime, true);
  }
}

void CuteBuzzerSoundsClass::bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration) {
  if (silentDuration == 0) {
    silentDuration = 1;
  }

  if (initFrequency < finalFrequency)
  {
    for (int i = initFrequency; i < finalFrequency; i = i * prop) {
      playTone(i, noteDuration, silentDuration);
    }

  } else {

    for (int i = initFrequency; i > finalFrequency; i = i / prop) {
      playTone(i, noteDuration, silentDuration);
    }
  }
}


void CuteBuzzerSoundsClass::playSound(int soundName) {
  switch (soundName) {

    case S_CONNECTION:
      playTone(NOTE_E5, 50, 30);
      playTone(NOTE_E6, 55, 25);
      playTone(NOTE_A6, 60, 10);
      break;

    case S_DISCONNECTION:
      playTone(NOTE_E5, 50, 30);
      playTone(NOTE_A6, 55, 25);
      playTone(NOTE_E6, 50, 60);
      break;

    case S_BUTTON_PUSHED:
      bendTones (NOTE_E6, NOTE_G6, 1.03, 20, 2);
      delay(30);
      bendTones (NOTE_E6, NOTE_D7, 1.04, 10, 2);
      break;

    case S_MODE1:
      bendTones (NOTE_E6, NOTE_A6, 1.02, 30, 10);
      break;

    case S_MODE2:
      bendTones (NOTE_G6, NOTE_D7, 1.03, 30, 10);
      break;

    case S_MODE3:
      playTone(NOTE_E6, 50, 100);
      playTone(NOTE_G6, 50, 80);
      playTone(NOTE_D7, 300, 0);
      break;

    case S_SURPRISE:
      bendTones(800, 2150, 1.02, 10, 1);
      bendTones(2149, 800, 1.03, 7, 1);
      break;

    case S_JUMP:
      bendTones(880, 2000, 1.04, 8, 3);
      delay(200);
      break;

    case S_OHOOH:
      bendTones(880, 2000, 1.04, 8, 3);
      delay(200);

      for (int i = 880; i < 2000; i = i * 1.04) {
        playTone(NOTE_B5, 5, 10);
      }
      break;

    case S_OHOOH2:
      bendTones(1880, 3000, 1.03, 8, 3);
      delay(200);

      for (int i = 1880; i < 3000; i = i * 1.03) {
        playTone(NOTE_C6, 10, 10);
      }
      break;

    case S_CUDDLY:
      bendTones(700, 900, 1.03, 16, 4);
      bendTones(899, 650, 1.01, 18, 7);
      break;

    case S_SLEEPING:
      bendTones(100, 500, 1.04, 10, 10);
      delay(500);
      bendTones(400, 100, 1.04, 10, 1);
      break;

    case S_HAPPY:
      bendTones(1500, 2500, 1.05, 20, 8);
      bendTones(2499, 1500, 1.05, 25, 8);
      break;

    case S_SUPER_HAPPY:
      bendTones(2000, 6000, 1.05, 8, 3);
      delay(50);
      bendTones(5999, 2000, 1.05, 13, 2);
      break;

    case S_HAPPY_SHORT:
      bendTones(1500, 2000, 1.05, 15, 8);
      delay(100);
      bendTones(1900, 2500, 1.05, 10, 8);
      break;

    case S_SAD:
      bendTones(880, 669, 1.02, 20, 200);
      break;

    case S_CONFUSED:
      bendTones(1000, 1700, 1.03, 8, 2);
      bendTones(1699, 500, 1.04, 8, 3);
      bendTones(1000, 1700, 1.05, 9, 10);
      break;

    case S_FART1:
      bendTones(1600, 3000, 1.02, 2, 15);
      break;

    case S_FART2:
      bendTones(2000, 6000, 1.02, 2, 20);
      break;

    case S_FART3:
      bendTones(1600, 4000, 1.02, 2, 20);
      bendTones(4000, 3000, 1.02, 2, 20);
      break;
  }
}

CuteBuzzerSoundsClass cute;
