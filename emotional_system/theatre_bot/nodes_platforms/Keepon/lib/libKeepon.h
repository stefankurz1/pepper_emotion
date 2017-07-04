///////////////////////////////
// libKeepon.h               //
// Keepon(R) Pro API         //
// (c)2010-2012 BeatBots LLC //
// support@beatbots.net      //
///////////////////////////////

//For now, this declaration is necessary for Windows.
#define HARDWARE 3

//////////////
// Includes //
//////////////
#ifdef _WIN32 // Windows
	#include <windows.h>
	#include <stdio.h>
	#include <stdlib.h>
#else // Linux/Mac
	#include <stdlib.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <sys/uio.h>
	#include <termios.h>
#endif


/////////////////////
// Robot addresses //
/////////////////////
// The first argument (int robot) to all commands (except bbInitComm) is the
// address of the robot. 

#if HARDWARE==3
	// This is the address for a single standard Keepon Pro (hardware version 3).
	#define KEEPON 17
	#define MAXROBOTS 1
#elif HARDWARE==4
	// For a chain of up to 30 Keepon Pro robots in the "Garden" configuration (hardware version 4):
	// This is the address used by returning packets -- do not use. 
	#define RETURN 0
	// These are the addresses used for Keepon Garden. Each robot needs address-specific firmware.
	#define K1 1
	#define K2 2
	#define K3 3
	#define K4 4
	#define K5 5
	#define K6 6
	#define K7 7
	#define K8 8
	#define K9 9
	#define K10 10
	#define MAXROBOTS 32
#endif


///////////////
// DOF names //
///////////////
// The second argument (int dof) to all bbMov*, bbSet*, and bbGet* commands is
// the index of the DOF.

// Pitch (TILT):
// The robot can lean forward/backward +/- 45deg (v3) or 46deg (v4). 
// The TILT axis is located 28mm above the center of the base of the robot's body.
#define TILT 0

// Yaw (PAN):
// The robot can turn right/left +/- 180deg (v3) or 174degrees (v4).
// The PAN axis is located at the center of the base of the robot's body.
#define PAN 1

// Compression (PON):
// The robot can linearly compress approximately 10mm (0 is fully extended, 10 is fully compressed).
// The PON axis is located between the TILT/SIDE axes and the top of the robot's head (which is 120mm above the base).
#define PON 2

// Roll (SIDE):
// The robot can lean right/left +/- 25deg (v3) or 23deg (v4).
// The SIDE axis is located 28mm above the center of the base of the robot's body.
#define SIDE 3


/////////////////////////////
// Initialization commands //
/////////////////////////////

// Before running any commands, it is necessary to initialize communication.
// This function connects to a robot on the specified serial device. In case of
// an error, it prints the error and exits.
// Example: bbInitComm("/dev/tty.KeySerial1");
void bbInitComm (char *device);

// Next, it is necessary to calibrate the motors. This function runs each DOF to
// its physical limits and determines the controllable range.
// Example: bbInitMotors(KEEPON);
void bbInitMotors (int robot);


///////////////////////
// Movement commands //
///////////////////////
// The bbMov* commands drive the DOFs with a trapezoidal velocity profile:
//
//   v |
//   e |            v
//   l |      ______________
//   o |     /              \
//   c |  a /                \ -a
//   i |   /                  \
//   t |  /                    \
//   y | /                      \
//     +----------------------------
//      start      time        end
//       pos                   pos
//
//   v = maximum velocity (set with bbSetVel)
//   a = acceleration (slope set with bbSetAcc)
//   Positions are to be given in degrees (except for PON, which uses 0-10mm).
//   In the functions below, "deg" should be replaced with "mm" in the case of PON.

// Move to a given position (in deg) at velocity and acceleration previously set
// using bbSetVel and bbSetAcc.
// Example: bbMovPos(KEEPON,PAN,90);
//          will turn the robot right 90 degrees.
void bbMovPos (int robot, int dof, double pos);

// Move to a given position (in deg) at given velocity (>0, in deg/s) and
// acceleration previously set using bbSetAcc.
void bbMovVel (int robot, int dof, double pos, double vel);

// Move to a given position (in deg) at given acceleration (>0, in deg/s/s)
// and velocity previously set using bbSetVel.
void bbMovAcc (int robot, int dof, double pos, double acc);


//////////////////////
// Setting commands //
//////////////////////

// Set position (in deg). This results in a ballistic movement without smooth
// acceleration or deceleration. It is recommended for PON only.
// Example: bbSetPos(KEEPON,PON,10); sleep(.1); bbSetPos(KEEPON,PON,0);
//          will make the robot bounce down and up quickly.
void bbSetPos (int robot, int dof, double pos);

// Set maximum velocity (>0, in deg/s), or v in the above diagram. This setting
// will be used in subsequent calls to bbMovPos and bbMovAcc.
// Defaults are: TILT 50, PAN 150, PON 25, SIDE 50.
void bbSetVel (int robot, int dof, double vel);

// Set acceleration (>0, in deg/s/s), or slope a in the above diagram. This
// setting will be used in subsequent calls to bbMovPos and bbMovVel, and will
// only be readable by bbGetAcc after a bbMovPos or bbMovVel command.
// Defaults are: TILT 1500, PAN 3000, PON 4300, SIDE 2000.
void bbSetAcc (int robot, int dof, double acc);


///////////////////////
// Querying commands //
///////////////////////

// Return current position (in deg).
double bbGetPos (int robot, int dof);

// Return current velocity (in deg/s).
double bbGetVel (int robot, int dof);

// Return acceleration (in deg/s/s) as previously set using bbSetAcc.
double bbGetAcc (int robot, int dof);


////////////////////////////
// Miscellaneous commands //
////////////////////////////

#if HARDWARE==4
// For Keepon Pro "Garden" confirguration only:
// Play a sound that has been loaded onto the microcontroller's EEPROM along
// with firmware. Sound is unsigned 8-bit PCM data at 8 kHz (8 kB/s). Robots in
// the "Garden" configuration can store approximately 900 kB of sound, or 2 min.
// (int sound) is an index between 1 and the number of stored sounds, or 0 to stop.
// (int volume) should be between 0 (silent) and 128 (normal). A value up to 255
// may be provided, but this doubles the audio signal values and may result in
// clipping and distortion.
void bbPlay (int robot, int sound, int volume);
#endif
