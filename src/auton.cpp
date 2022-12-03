#include "api.h"
#include "auton.h"
#include "main.h"
#include "robot.h"
#include "pid.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

  //INDEX
    //AUTON 1: RED NON-ROLLER
    //AUTON 2: BLUE NON-ROLLER
    //AUTON 3: RED ROLLER
    //AUTON 4: BLUE ROLLER
    //AUTON 5: FULL AWP
    //AUTON 6: SKILLS

// //11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
}