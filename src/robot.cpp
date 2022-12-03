//constructors for everything electrical

#include "api.h"
#include "auton.h"
#include "main.h"
#include "robot.h"
#include "pros/motors.h"

#define INDEXER_PORT 1
#define OPTICAL_PORT 4
#define IMU_PORT 6
#define LF_PORT 1
#define LM_PORT 9
#define LB_PORT 8
#define RF_PORT 10
#define RM_PORT 11
#define RB_PORT 12
#define GPS_PORT 16
#define CATA_PORT 17
#define INTAKE_PORT 18


pros::Motor LF (LF_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor LM (LM_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor LB (LB_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor RF (RF_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor RM (RM_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor RB (RB_PORT, pros::E_MOTOR_GEARSET_06, false);

//intake
pros::Motor INTAKE (INTAKE_PORT, pros::E_MOTOR_GEARSET_18, true);

//flywheel
pros::Motor CATA (CATA_PORT, pros::E_MOTOR_GEARSET_06);

//angler
// pros::ADIDigitalOut angler ('B', true);

//cata limit switch
pros::ADIDigitalIn catalim ('H');

//expansion
pros::ADIDigitalOut expand ({{3, 8}});

//auton selector
pros::ADIDigitalIn selec ({{3, 7}});

//imu
pros::Imu imu (IMU_PORT);

//controller
pros::Controller con (pros::E_CONTROLLER_MASTER);

//optical
pros::Optical optical(OPTICAL_PORT);