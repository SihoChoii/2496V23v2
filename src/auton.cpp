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

  //INDEX (subject to change)
    //AUTON 1: RED NON-ROLLER
    //AUTON 2: BLUE NON-ROLLER
    //AUTON 3: RED ROLLER
    //AUTON 4: BLUE ROLLER
    //AUTON 5: FULL AWP
    //AUTON 6: SKILLS

  //11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
  
  //RED NON-ROLLER
  if (atn == 1) {

  }

  //22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222

  //BLUE NON-ROLLER
  if (atn == 2) {

  }

  //33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333

  //RED ROLLER
  if (atn == 3) {

  }

  //44444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444

  //BLUE ROLLER
  if (atn == 4) {

  }

  //55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555

  //FULL AWP
  if (atn == 5) {

  }

  //66666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666
  if (atn == 6) {
    
  }
}