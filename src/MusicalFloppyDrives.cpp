
#include "MusicalFloppyDrives.h"

// Floppy drive numbers, used to calculate step and direction pins
#define FIRST_DRIVE  1
#define SECOND_DRIVE 2

// Pins to connect the floppy drives
#define FIRST_DRIVE_STEP_CONTROL_PIN  2
#define FIRST_DRIVE_DIRECTION_PIN     3
#define SECOND_DRIVE_STEP_CONTROL_PIN 4
#define SECOND_DRIVE_DIRECTION_PIN    5

#define FLOPPY_SAFETY_DELAY_SHORT 5
#define FLOPPY_SAFETY_DELAY_LONG 500

// Musical note indexes for musicalNotePeriods array
#define C_1 24
#define D_1 26
#define E_1 28
#define F_1 29
#define G_1 31
#define A_1 33
#define B_1 34
#define C_2 36
#define D_2 38
#define E_2 40
#define F_2 41
#define G_2 43
#define A_2 45
#define B_2 47
#define C_3 48
#define D_3 50
#define E_3 52
#define F_3 53
#define G_3 55
#define A_3 57
#define B_3 58

// Sharp and flat note modifiers, and silence
#define SEMITONE 1
#define SILENCE  0

// Microseconds in a timer-tick for setting timer resolution
#define TIMER_RESOLUTION 40

// Pulse only every-other tick, on rising signal
#define DOUBLE_TIMER_RESOLUTION (TIMER_RESOLUTION * 2)

// An array of maximum track positions for each floppy drive.  3.5" Floppies have
// 80 tracks.These should be doubled, because each tick is half a position.
// Index zero of this array controls the "resetAllDrivesSimultaneously" function, and
// should be the same as the largest value in this array
#define FLOPPY_POSITION_LIMIT 158

// Note periods in two-tick units
const unsigned int musicalNotePeriods[128] = {
    0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION,
    0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION,
    30578/DOUBLE_TIMER_RESOLUTION, 28861/DOUBLE_TIMER_RESOLUTION, 27242/DOUBLE_TIMER_RESOLUTION, 25713/DOUBLE_TIMER_RESOLUTION, 24270/DOUBLE_TIMER_RESOLUTION, 22909/DOUBLE_TIMER_RESOLUTION, 21622/DOUBLE_TIMER_RESOLUTION, 20409/DOUBLE_TIMER_RESOLUTION, 19263/DOUBLE_TIMER_RESOLUTION, 18182/DOUBLE_TIMER_RESOLUTION, 17161/DOUBLE_TIMER_RESOLUTION, 16198/DOUBLE_TIMER_RESOLUTION, //C_1 - B_1
    15289/DOUBLE_TIMER_RESOLUTION, 14436/DOUBLE_TIMER_RESOLUTION, 13621/DOUBLE_TIMER_RESOLUTION, 12856/DOUBLE_TIMER_RESOLUTION, 12135/DOUBLE_TIMER_RESOLUTION, 11454/DOUBLE_TIMER_RESOLUTION, 10811/DOUBLE_TIMER_RESOLUTION, 10205/DOUBLE_TIMER_RESOLUTION, 9632/DOUBLE_TIMER_RESOLUTION, 9091/DOUBLE_TIMER_RESOLUTION, 8581/DOUBLE_TIMER_RESOLUTION, 8099/DOUBLE_TIMER_RESOLUTION, //C_2 - B_2
    7645/DOUBLE_TIMER_RESOLUTION, 7218/DOUBLE_TIMER_RESOLUTION, 6811/DOUBLE_TIMER_RESOLUTION, 6428/DOUBLE_TIMER_RESOLUTION, 6068/DOUBLE_TIMER_RESOLUTION, 5727/DOUBLE_TIMER_RESOLUTION, 5406/DOUBLE_TIMER_RESOLUTION, 5103/DOUBLE_TIMER_RESOLUTION, 4816/DOUBLE_TIMER_RESOLUTION, 4546/DOUBLE_TIMER_RESOLUTION, 4291/DOUBLE_TIMER_RESOLUTION, 4050/DOUBLE_TIMER_RESOLUTION, //C_3 - B_3
    3823/DOUBLE_TIMER_RESOLUTION, 3609/DOUBLE_TIMER_RESOLUTION, 3406/DOUBLE_TIMER_RESOLUTION, 3214/DOUBLE_TIMER_RESOLUTION, 3034/DOUBLE_TIMER_RESOLUTION, 2864/DOUBLE_TIMER_RESOLUTION, 2703/DOUBLE_TIMER_RESOLUTION, 2552/DOUBLE_TIMER_RESOLUTION, 2408/DOUBLE_TIMER_RESOLUTION, 2273/DOUBLE_TIMER_RESOLUTION, 2146/DOUBLE_TIMER_RESOLUTION, 2025/DOUBLE_TIMER_RESOLUTION, //C4 - B4
    1911/DOUBLE_TIMER_RESOLUTION, 1804/DOUBLE_TIMER_RESOLUTION, 1703/DOUBLE_TIMER_RESOLUTION, 1607/DOUBLE_TIMER_RESOLUTION, 1517/DOUBLE_TIMER_RESOLUTION, 1432/DOUBLE_TIMER_RESOLUTION, 1351/DOUBLE_TIMER_RESOLUTION, 1276/DOUBLE_TIMER_RESOLUTION, 1204/DOUBLE_TIMER_RESOLUTION, 1136/DOUBLE_TIMER_RESOLUTION, 1073/DOUBLE_TIMER_RESOLUTION, 1012/DOUBLE_TIMER_RESOLUTION, //C5 - B5
    956/DOUBLE_TIMER_RESOLUTION, 902/DOUBLE_TIMER_RESOLUTION, 851/DOUBLE_TIMER_RESOLUTION, 804/DOUBLE_TIMER_RESOLUTION, 758/DOUBLE_TIMER_RESOLUTION, 716/DOUBLE_TIMER_RESOLUTION, 676/DOUBLE_TIMER_RESOLUTION, 638/DOUBLE_TIMER_RESOLUTION, 602/DOUBLE_TIMER_RESOLUTION, 568/DOUBLE_TIMER_RESOLUTION, 536/DOUBLE_TIMER_RESOLUTION, 506/DOUBLE_TIMER_RESOLUTION, //C6 - B6
    478/DOUBLE_TIMER_RESOLUTION, 451/DOUBLE_TIMER_RESOLUTION, 426/DOUBLE_TIMER_RESOLUTION, 402/DOUBLE_TIMER_RESOLUTION, 379/DOUBLE_TIMER_RESOLUTION, 358/DOUBLE_TIMER_RESOLUTION, 338/DOUBLE_TIMER_RESOLUTION, 319/DOUBLE_TIMER_RESOLUTION, 301/DOUBLE_TIMER_RESOLUTION, 284/DOUBLE_TIMER_RESOLUTION, 268/DOUBLE_TIMER_RESOLUTION, 253/DOUBLE_TIMER_RESOLUTION, //C7 - B7
    0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION,
    0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0/DOUBLE_TIMER_RESOLUTION, 0};

// Star Wars Imperial March song segments
const unsigned int imperialMarchSegment1[] = {musicalNotePeriods[G_2], musicalNotePeriods[G_2], musicalNotePeriods[G_2], musicalNotePeriods[G_2], SILENCE,
                                              musicalNotePeriods[G_2], musicalNotePeriods[G_2], musicalNotePeriods[G_2], musicalNotePeriods[G_2], SILENCE,
                                              musicalNotePeriods[G_2], musicalNotePeriods[G_2], musicalNotePeriods[G_2], musicalNotePeriods[G_2], SILENCE, SILENCE};
const unsigned int imperialMarchSegment2[] = {musicalNotePeriods[E_2-SEMITONE], musicalNotePeriods[E_2-SEMITONE], musicalNotePeriods[E_2-SEMITONE], SILENCE,
                                              musicalNotePeriods[B_2-SEMITONE], SILENCE, SILENCE};
const unsigned int imperialMarchSegment3[] = {musicalNotePeriods[G_2], musicalNotePeriods[G_2], musicalNotePeriods[G_2], musicalNotePeriods[G_2], SILENCE, SILENCE};
const unsigned int imperialMarchSegment4[] = {musicalNotePeriods[G_2], musicalNotePeriods[G_2], musicalNotePeriods[G_2], musicalNotePeriods[G_2],
                                              musicalNotePeriods[G_2], musicalNotePeriods[G_2], SILENCE, SILENCE};
const unsigned int imperialMarchSegment5[] = {musicalNotePeriods[D_3], musicalNotePeriods[D_3], musicalNotePeriods[D_3], musicalNotePeriods[D_3], SILENCE,
                                              musicalNotePeriods[D_3], musicalNotePeriods[D_3], musicalNotePeriods[D_3], musicalNotePeriods[D_3], SILENCE,
                                              musicalNotePeriods[D_3], musicalNotePeriods[D_3], musicalNotePeriods[D_3], musicalNotePeriods[D_3], SILENCE, SILENCE};
const unsigned int imperialMarchSegment6[] = {musicalNotePeriods[E_3-SEMITONE], musicalNotePeriods[E_3-SEMITONE], musicalNotePeriods[E_3-SEMITONE], SILENCE,
                                              musicalNotePeriods[B_2-SEMITONE], SILENCE, SILENCE};
const unsigned int imperialMarchSegment7[] = {musicalNotePeriods[F_2+SEMITONE], musicalNotePeriods[F_2+SEMITONE], musicalNotePeriods[F_2+SEMITONE], musicalNotePeriods[F_2+SEMITONE], SILENCE, SILENCE};
const unsigned int imperialMarchSegment8[] = {musicalNotePeriods[G_3], musicalNotePeriods[G_3], musicalNotePeriods[G_3], musicalNotePeriods[G_3], SILENCE, SILENCE};
const unsigned int imperialMarchSegment9[] = {musicalNotePeriods[G_2], musicalNotePeriods[G_2], SILENCE, musicalNotePeriods[G_2], SILENCE, SILENCE};
const unsigned int imperialMarchSegment10[] = {musicalNotePeriods[F_3+SEMITONE], musicalNotePeriods[F_3+SEMITONE], SILENCE, musicalNotePeriods[F_3], SILENCE, SILENCE};
const unsigned int imperialMarchSegment11[] = {musicalNotePeriods[E_3], musicalNotePeriods[E_3-SEMITONE], musicalNotePeriods[E_3], SILENCE};
const unsigned int imperialMarchSegment12[] = {musicalNotePeriods[G_2+SEMITONE], SILENCE, 
                                              musicalNotePeriods[C_3+SEMITONE], musicalNotePeriods[C_3+SEMITONE], musicalNotePeriods[C_3+SEMITONE], musicalNotePeriods[C_3+SEMITONE], SILENCE,
                                              musicalNotePeriods[C_3], musicalNotePeriods[C_3], SILENCE, SILENCE};
const unsigned int imperialMarchSegment13[] = {musicalNotePeriods[B_2], SILENCE, musicalNotePeriods[B_2-SEMITONE], musicalNotePeriods[A_2], musicalNotePeriods[B_2-SEMITONE], SILENCE};
const unsigned int imperialMarchSegment14[] = {musicalNotePeriods[E_2-SEMITONE], SILENCE,
                                              musicalNotePeriods[F_2+SEMITONE], musicalNotePeriods[F_2+SEMITONE], musicalNotePeriods[F_2+SEMITONE], musicalNotePeriods[F_2+SEMITONE], SILENCE,
                                              musicalNotePeriods[E_2-SEMITONE], musicalNotePeriods[E_2-SEMITONE], musicalNotePeriods[E_2-SEMITONE], SILENCE, musicalNotePeriods[F_2+SEMITONE], SILENCE, SILENCE};
const unsigned int imperialMarchSegment15[] = {musicalNotePeriods[B_2-SEMITONE], musicalNotePeriods[B_2-SEMITONE], musicalNotePeriods[B_2-SEMITONE], musicalNotePeriods[B_2-SEMITONE], SILENCE,
                                              musicalNotePeriods[G_2], musicalNotePeriods[G_2], musicalNotePeriods[G_2], SILENCE, musicalNotePeriods[B_2-SEMITONE], SILENCE, SILENCE};
const unsigned int imperialMarchSegment16[] = {musicalNotePeriods[D_3], musicalNotePeriods[D_3], musicalNotePeriods[D_3], musicalNotePeriods[D_3],
                                              musicalNotePeriods[D_3], musicalNotePeriods[D_3], SILENCE, SILENCE};
const unsigned int imperialMarchSegment17[] = {musicalNotePeriods[E_2-SEMITONE], SILENCE,
                                              musicalNotePeriods[F_2+SEMITONE], musicalNotePeriods[F_2+SEMITONE], musicalNotePeriods[F_2+SEMITONE], musicalNotePeriods[F_2+SEMITONE], SILENCE, SILENCE};
const unsigned int imperialMarchSegment18[] = {musicalNotePeriods[E_2-SEMITONE], musicalNotePeriods[E_2-SEMITONE], musicalNotePeriods[E_2-SEMITONE], SILENCE,
                                              musicalNotePeriods[B_2-SEMITONE], SILENCE, SILENCE};
const unsigned int imperialMarchBaseG1[] = {musicalNotePeriods[G_1]};
const unsigned int imperialMarchBaseG2[] = {musicalNotePeriods[G_2]};
const unsigned int imperialMarchBaseE2[] = {musicalNotePeriods[E_2]};  
const unsigned int imperialMarchBaseE2flat[] = {musicalNotePeriods[E_2-SEMITONE]};
const unsigned int imperialMarchBaseD2[] = {musicalNotePeriods[D_2]};
const unsigned int imperialMarchBaseF2sharp[] = {musicalNotePeriods[F_2+SEMITONE]};
const unsigned int imperialMarchBaseC2sharp[] = {musicalNotePeriods[C_2+SEMITONE]};
const unsigned int imperialMarchBaseB2flat[] = {musicalNotePeriods[B_2-SEMITONE]};
const unsigned int imperialMarchSilenceShort[] = {SILENCE};
const unsigned int imperialMarchSilenceLong[] = {SILENCE, SILENCE, SILENCE, SILENCE};

// Maximum track positions for each floppy drive
const unsigned int MusicalFloppyDrives::FLOPPY_MAX_POSITION[] = {FLOPPY_POSITION_LIMIT, FLOPPY_POSITION_LIMIT, FLOPPY_POSITION_LIMIT,
                                                                FLOPPY_POSITION_LIMIT, FLOPPY_POSITION_LIMIT, FLOPPY_POSITION_LIMIT, 
                                                                FLOPPY_POSITION_LIMIT, FLOPPY_POSITION_LIMIT, FLOPPY_POSITION_LIMIT, 
                                                                FLOPPY_POSITION_LIMIT};

//Array to track the current position of each floppy head
unsigned int MusicalFloppyDrives::currentFloppyHeadPosition[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Array to keep track of state of each pin.  Even indexes: control pins; odd indexes: direction pins (low: forward; high: reverse)
int MusicalFloppyDrives::currentFloppyPinState[] = {0, 0, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

// Current period assigned to each drive
unsigned int MusicalFloppyDrives::currentFloppyPeriod[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Current tick count for each drive
unsigned int MusicalFloppyDrives::currentFloppyTickCount[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void MusicalFloppyDrives::setup() {
  // Pin setup
  pinMode(FIRST_DRIVE_STEP_CONTROL_PIN, OUTPUT);
  pinMode(FIRST_DRIVE_DIRECTION_PIN, OUTPUT);
  pinMode(SECOND_DRIVE_STEP_CONTROL_PIN, OUTPUT);
  pinMode(SECOND_DRIVE_DIRECTION_PIN, OUTPUT);

  // Start from idle position
  resetAllDrivesSimultaneously();
  delay(FLOPPY_SAFETY_DELAY_LONG);

  // Generate interrupts and execute the associated function
  Timer1.initialize(TIMER_RESOLUTION);
  Timer1.attachInterrupt(tick);
}

void MusicalFloppyDrives::playImperialMarchSong() {
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG2, sizeof(imperialMarchBaseG2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment1, sizeof(imperialMarchSegment1));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseE2flat, sizeof(imperialMarchBaseE2flat)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment2, sizeof(imperialMarchSegment2));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG2, sizeof(imperialMarchBaseG2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment3, sizeof(imperialMarchSegment3));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseE2flat, sizeof(imperialMarchBaseE2flat)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment2, sizeof(imperialMarchSegment2));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG2, sizeof(imperialMarchBaseG2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment4, sizeof(imperialMarchSegment4));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceLong, sizeof(imperialMarchSilenceLong));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseD2, sizeof(imperialMarchBaseD2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment5, sizeof(imperialMarchSegment5));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseE2flat, sizeof(imperialMarchBaseE2flat)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment6, sizeof(imperialMarchSegment6));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseF2sharp, sizeof(imperialMarchBaseF2sharp)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment7, sizeof(imperialMarchSegment7));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseE2flat, sizeof(imperialMarchBaseE2flat)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment6, sizeof(imperialMarchSegment6));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG2, sizeof(imperialMarchBaseG2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment4, sizeof(imperialMarchSegment4));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceLong, sizeof(imperialMarchSilenceLong));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG2, sizeof(imperialMarchBaseG2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment8, sizeof(imperialMarchSegment8));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG1, sizeof(imperialMarchBaseG1)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment9, sizeof(imperialMarchSegment9));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG2, sizeof(imperialMarchBaseG2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment8, sizeof(imperialMarchSegment8));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG1, sizeof(imperialMarchBaseG1)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment10, sizeof(imperialMarchSegment10));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseC2sharp, sizeof(imperialMarchBaseC2sharp)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment11, sizeof(imperialMarchSegment11));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceLong, sizeof(imperialMarchSilenceLong));
    playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchBaseC2sharp, sizeof(imperialMarchBaseC2sharp));
    playMusicalNote(SECOND_DRIVE, imperialMarchSegment12, sizeof(imperialMarchSegment12)); playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchBaseE2flat, sizeof(imperialMarchBaseE2flat));
    playMusicalNote(SECOND_DRIVE, imperialMarchSegment13, sizeof(imperialMarchSegment13)); playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchSilenceLong, sizeof(imperialMarchSilenceLong)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseE2flat, sizeof(imperialMarchBaseE2flat)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment14, sizeof(imperialMarchSegment14));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseB2flat, sizeof(imperialMarchBaseB2flat)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment15, sizeof(imperialMarchSegment15));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseD2, sizeof(imperialMarchBaseD2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment16, sizeof(imperialMarchSegment16));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceLong, sizeof(imperialMarchSilenceLong));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG2, sizeof(imperialMarchBaseG2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment8, sizeof(imperialMarchSegment8));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG1, sizeof(imperialMarchBaseG1)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment9, sizeof(imperialMarchSegment9));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG2, sizeof(imperialMarchBaseG2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment8, sizeof(imperialMarchSegment8));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG1, sizeof(imperialMarchBaseG1)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment10, sizeof(imperialMarchSegment10));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseC2sharp, sizeof(imperialMarchBaseC2sharp)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment11, sizeof(imperialMarchSegment11));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceLong, sizeof(imperialMarchSilenceLong));
    playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchBaseC2sharp, sizeof(imperialMarchBaseC2sharp));
    playMusicalNote(SECOND_DRIVE, imperialMarchSegment12, sizeof(imperialMarchSegment12)); playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchBaseE2flat, sizeof(imperialMarchBaseE2flat));
    playMusicalNote(SECOND_DRIVE, imperialMarchSegment13, sizeof(imperialMarchSegment13)); playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchSilenceLong, sizeof(imperialMarchSilenceLong)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseE2flat, sizeof(imperialMarchBaseE2flat)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment17, sizeof(imperialMarchSegment17));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseE2flat, sizeof(imperialMarchBaseE2flat)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment18, sizeof(imperialMarchSegment18));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG2, sizeof(imperialMarchBaseG2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment3, sizeof(imperialMarchSegment3));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseE2flat, sizeof(imperialMarchBaseE2flat)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment18, sizeof(imperialMarchSegment18));
    playMusicalNote(FIRST_DRIVE, imperialMarchBaseG2, sizeof(imperialMarchBaseG2)); playMusicalNote(SECOND_DRIVE, imperialMarchSegment4, sizeof(imperialMarchSegment4));
    playMusicalNote(SECOND_DRIVE, imperialMarchSilenceShort, sizeof(imperialMarchSilenceShort)); playMusicalNote(FIRST_DRIVE, imperialMarchSilenceLong, sizeof(imperialMarchSilenceLong));
    delay(FLOPPY_SAFETY_DELAY_LONG);
    resetAllDrivesSimultaneously();
}

void MusicalFloppyDrives::playMusicalNote(byte driveNum, unsigned int const chargeNotes[], byte numElements)
{
  byte iterator = 0;
  unsigned long lastRun = 0;
  while(iterator < numElements) {
    if (millis() - 100 > lastRun) {
      lastRun = millis();
      currentFloppyPeriod[driveNum] = chargeNotes[iterator++];
    }
  }
}

void MusicalFloppyDrives::resetAllDrivesSimultaneously()
{
  // Stop all drives and set to reverse
  for (byte d = FIRST_DRIVE; d <= SECOND_DRIVE; d++)
  {
    byte stepPin = d * 2;
    currentFloppyPeriod[d] = 0;
    digitalWrite(stepPin + 1, HIGH);
  }

  // Reset all drives together
  for (unsigned int s=0; s < FLOPPY_MAX_POSITION[0]; s += 2)
  {
    for (byte d = FIRST_DRIVE; d <= SECOND_DRIVE; d++)
    {
      byte stepPin = d * 2;
      digitalWrite(stepPin, HIGH);
      digitalWrite(stepPin, LOW);
    }
    delay(FLOPPY_SAFETY_DELAY_SHORT);
  }

  // Return tracking to ready state
  for (byte d=FIRST_DRIVE;d<=SECOND_DRIVE;d++)
  {
    byte stepPin = d * 2;
    currentFloppyHeadPosition[d] = 0;
    currentFloppyPinState[stepPin] = LOW;
    digitalWrite(stepPin + 1, LOW);
    currentFloppyPinState[stepPin + 1] = LOW;
  }
}

void MusicalFloppyDrives::toggleFloppyPin(byte driveNum, byte pin, byte direction_pin) {
  // Switch directions if end has been reached
  if (currentFloppyHeadPosition[driveNum] >= FLOPPY_MAX_POSITION[driveNum])
  {
    currentFloppyPinState[direction_pin] = HIGH;
    digitalWrite(direction_pin, HIGH);
  }
  else if (currentFloppyHeadPosition[driveNum] <= 0)
  {
    currentFloppyPinState[direction_pin] = LOW;
    digitalWrite(direction_pin, LOW);
  }
  // Update currentFloppyHeadPosition
  if (currentFloppyPinState[direction_pin] == HIGH)
    currentFloppyHeadPosition[driveNum]--;
  else
    currentFloppyHeadPosition[driveNum]++;
  // Pulse the control pin
  digitalWrite(pin, currentFloppyPinState[pin]);
  currentFloppyPinState[pin] = ~currentFloppyPinState[pin];
}

// Function executed at Timer One interruption
void MusicalFloppyDrives::tick()
{
  if (currentFloppyPeriod[1] > 0)
  {
    currentFloppyTickCount[1]++;
    if (currentFloppyTickCount[1] >= currentFloppyPeriod[1])
    {
      toggleFloppyPin(1, 2, 3);
      currentFloppyTickCount[1] = 0;
    }
  }
  if (currentFloppyPeriod[2] > 0)
  {
    currentFloppyTickCount[2]++;
    if (currentFloppyTickCount[2] >= currentFloppyPeriod[2])
    {
      toggleFloppyPin(2, 4, 5);
      currentFloppyTickCount[2] = 0;
    }
  }
  if (currentFloppyPeriod[3] > 0)
  {
    currentFloppyTickCount[3]++;
    if (currentFloppyTickCount[3] >= currentFloppyPeriod[3])
    {
      toggleFloppyPin(3, 6, 7);
      currentFloppyTickCount[3] = 0;
    }
  }
  if (currentFloppyPeriod[4] > 0)
  {
    currentFloppyTickCount[4]++;
    if (currentFloppyTickCount[4] >= currentFloppyPeriod[4])
    {
      toggleFloppyPin(4, 8, 9);
      currentFloppyTickCount[4] = 0;
    }
  }
  if (currentFloppyPeriod[5] > 0)
  {
    currentFloppyTickCount[5]++;
    if (currentFloppyTickCount[5] >= currentFloppyPeriod[5])
    {
      toggleFloppyPin(5, 10, 11);
      currentFloppyTickCount[5] = 0;
    }
  }
  if (currentFloppyPeriod[6] > 0)
  {
    currentFloppyTickCount[6]++;
    if (currentFloppyTickCount[6] >= currentFloppyPeriod[6])
    {
      toggleFloppyPin(6, 12, 13);
      currentFloppyTickCount[6] = 0;
    }
  }
  if (currentFloppyPeriod[7] > 0)
  {
    currentFloppyTickCount[7]++;
    if (currentFloppyTickCount[7] >= currentFloppyPeriod[7])
    {
      toggleFloppyPin(7, 14, 15);
      currentFloppyTickCount[7] = 0;
    }
  }
  if (currentFloppyPeriod[8] > 0)
  {
    currentFloppyTickCount[8]++;
    if (currentFloppyTickCount[8] >= currentFloppyPeriod[8])
    {
      toggleFloppyPin(8, 16, 17);
      currentFloppyTickCount[8] = 0;
    }
  }
  if (currentFloppyPeriod[9] > 0)
  {
    currentFloppyTickCount[9]++;
    if (currentFloppyTickCount[9] >= currentFloppyPeriod[9])
    {
      toggleFloppyPin(9, 18, 19);
      currentFloppyTickCount[9] = 0;
    }
  }
}