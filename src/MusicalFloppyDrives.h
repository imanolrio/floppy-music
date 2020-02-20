
#ifndef _MUSICALFLOPPYDRIVES_H_
#define _MUSICALFLOPPYDRIVES_H_

#include <Arduino.h>
#include <TimerOne.h>

class MusicalFloppyDrives {
public:
  static void setup();
  static void playImperialMarchSong();
  
protected:
  static const unsigned int FLOPPY_MAX_POSITION[];
  static unsigned int currentFloppyHeadPosition[];
  static int currentFloppyPinState[];
  static unsigned int currentFloppyPeriod[];
  static unsigned int currentFloppyTickCount[];

  static void playMusicalNote(byte driveNum, unsigned int const chargeNotes[], byte numElements);
  static void resetAllDrivesSimultaneously();
  static void toggleFloppyPin(byte driveNum, byte pin, byte direction_pin);
  static void tick();
};

#endif // _MUSICALFLOPPYDRIVES_H_
