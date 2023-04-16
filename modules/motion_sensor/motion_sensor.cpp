//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "motion_sensor.h"
#include "pc_serial_com.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

InterruptIn pirOutputSignal(PG_0);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool pirState;
static bool motionSensorActivated;

//=====[Declarations (prototypes) of private functions]========================

static void motionDetected();
static void motionCeased();

//=====[Implementations of public functions]===================================

void motionSensorInit()
{
   pirOutputSignal.rise(&motionDetected);
   pirOutputSignal.fall(&motionCeased);
   pirState = OFF;
   motionSensorActivated = true;
}

bool motionSensorRead()
{
    return pirState;
}

void motionSensorActivate()
{
   motionSensorActivated = true;
   pirOutputSignal.rise(&motionDetected);
   pirOutputSignal.fall(&motionCeased);
   pcSerialComStringWrite("The motion sensor has been activated\r\n");
}

void motionSensorDeactivate()
{
   motionSensorActivated = false;
   pirOutputSignal.rise(NULL);
   pirOutputSignal.fall(NULL);
   pcSerialComStringWrite("The motion sensor has been deactivated\r\n");
}


//=====[Implementations of private functions]==================================

static void motionDetected()
{
   pirState = ON;
}


static void motionCeased()
{
   pirState = OFF;
}