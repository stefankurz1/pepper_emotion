//////////////////////////
// libKeepon.h          //
// Keepon(R) Pro API    //
// (c)2010 BeatBots LLC //
// support@beatbots.net //
//////////////////////////


//////////////
// Includes //
//////////////
#ifdef _WIN32 // Windows
	#include <windows.h>
	#include <stdio.h>
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
#define KEEPON 17 // This is the address for a single standard Keepon Pro.


///////////////
// DOF names //
///////////////
// The second argument (int dof) to all bbMov*, bbSet*, and bbGet* commands is
// the index of the DOF.

// Pitch (TILT):
// The robot can lean forward 45 degrees and backward -45 degrees. The TILT
// axis is located 28mm above the center of the base of the robot's body.
#define TILT 0

// Yaw (PAN):
// The robot can turn left -180 degrees and right 180 degrees. The PAN axis is
// located at the center of the base of the robot's body.
#define PAN 1

// Compression (PON):
// The robot can linearly compress approximately 15mm (0 is fully extended, 100
// is fully compressed). The PON axis is located between the TILT/SIDE axes and
// the top of the robot's head (which is 120mm above the base).
#define PON 2

// Roll (SIDE):
// The robot can lean left -25 degrees and right 25 degrees. The SIDE axis is
// located 28mm above the center of the base of the robot's body.
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
//   Positions are to be given in degrees (except for PON, which uses 0 to 100).

// Move to a given position (in deg) at velocity and acceleration previously set
// using bbSetVel and bbSetAcc.
// Example: bbMovPos(KEEPON,PAN,90);
//          will turn the robot right 90 degrees.
void bbMovPos (int robot, int dof, double pos);

// Move to a given position (in deg) at given velocity (>0, in rad/s) and
// acceleration previously set using bbSetAcc.
void bbMovVel (int robot, int dof, double pos, double vel);

// Move to a given position (in deg) at given acceleration (>0.0, in rad/s/s)
// and velocity previously set using bbSetVel.
void bbMovAcc (int robot, int dof, double pos, double acc);


//////////////////////
// Setting commands //
//////////////////////

// Set position (in deg). This results in a ballistic movement without smooth
// acceleration or deceleration. It is recommended for PON only.
// Example: bbSetPos(KEEPON,PON,100); sleep(.1); bbSetPos(KEEPON,PON,0);
//          will make the robot bounce down and up quickly.
void bbSetPos (int robot, int dof, double pos);

// Set maximum velocity (>0, in rad/s), or v in the above diagram. This setting
// will be used in subsequent calls to bbMovPos and bbMovAcc.
void bbSetVel (int robot, int dof, double vel);

// Set acceleration (>0, in rad/s/s), or slope a in the above diagram. This
// setting will be used in subsequent calls to bbMovPos and bbMovVel.
void bbSetAcc (int robot, int dof, double acc);


///////////////////////
// Querying commands //
///////////////////////

// Return current position (in deg).
double bbGetPos (int robot, int dof);

// Return current velocity (in rad/s).
double bbGetVel (int robot, int dof);

// Return acceleration (in rad/s/s) as previously set using bbSetAcc.
double bbGetAcc (int robot, int dof);


///////////////////
// Misc commands //
///////////////////

// Do not use for normal operation -- may cause damage!
void	bbCmd (int robot, int dof, int jnst, int index, int *word);
