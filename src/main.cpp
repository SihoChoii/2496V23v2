// basically run all of the code here (PID, auton, etc.)

#include "main.h"
#include "api.h"
#include "auton.h"
#include "okapi/api/util/abstractRate.hpp"
#include "pid.h"
#include "pros/misc.h"
#include "robot.h"

using namespace pros;
using namespace std;


// void resetEncoders() { //we can't add this to main.h because main.h doesn't
// refer to robot.h (where LF, LB, etc. are located) 	LF.tare_position(); //or
// set_zero_position(0) or set_zero_position(LF.get_position()); (sets current
// encoder position to 0) 	LB.tare_position(); 	RF.tare_position();
// 	RB.tare_position();
// }

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "I was pressed!");
  } else {
    pros::lcd::clear_line(2);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::lcd::initialize();
  pros::lcd::set_text(1, "Hello PROS User!");

  pros::lcd::register_btn1_cb(on_center_button);
  optical.set_led_pwm(100);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

int atn;
string autstr;

void competition_initialize() {
    while(true){
      if(selec.get_value() == true){
        atn ++;
        delay(350);
      }
    
      if (atn == 1){
        autstr = "Red Non-Roller";
        con.print(0, 0, "Aut 1: %s", autstr);
      }
      else if(atn == 2){
        autstr = "Blue Non-Roller";
        con.print(0, 0, "Aut 2: %s", autstr);
      }
      else if(atn == 3){
        autstr = "Red Roller";
        con.print(0, 0, "Aut 3: %s", autstr);
      }
      else if(atn == 4){
        autstr = "Blue Roller";
        con.print(0, 0, "Aut 4: %s", autstr);
      }
      else if(atn == 5){
        autstr = "AWP";
        con.print(0, 0, "Aut 5: %s", autstr);
      }
      else if(atn == 6){
        autstr = "Skills";
        con.print(0, 0, "Aut 6: %s", autstr);
      }
      con.clear();
      // con.print(0, 0, "Aut: %s", autstr);
    }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void arcadeDrive()
{
		// Arcade Drive
		int power = con.get_analog(ANALOG_LEFT_Y); //power is defined as forward or backward
		int RX = con.get_analog(ANALOG_RIGHT_X); //turn is defined as left (positive) or right (negative)
		int turn = int(abs(RX) * RX / 75);
		int left = power + turn;
		int right = power - turn;

    LF.move(left);
    LM.move(left);
    LB.move(left);
    RF.move(right);
    RM.move(right);
    RB.move(right);
}

double motorLeftAvg()
{
  return ((LF.get_position() + LM.get_position() + LB.get_position()) / 3);
}
double motorRightAvg()
{
  return ((RF.get_position() + RM.get_position() + RB.get_position()) / 3);
}
double motorAvg()
{
  return ((motorLeftAvg() + motorRightAvg()) / 2);
}

int cycle = 0;
int wait = 900;
int wait2 = 250;

bool anglerToggle = false;
bool expandToggle = false;
bool deployExpansion = false;

bool rollerOn = false;

void opcontrol() {
  int time = 0;
  bool drive = false;
  int forwardAmount = 1000; // Motor Encoder Position
  int turnAmount = 90; // Degrees
  bool displayPage = 1; // Bool for 2 page

	while (true) {
    
    // Controller Display
    if (con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) displayPage = !displayPage;
    if (displayPage)
    {
      if (time % 100 == 0) con.clear();
      else if (time % 50 == 0) {
        cycle++;
        if (cycle % 3 == 0) con.print(0, 0, "MotorAvg %d", motorAvg());
        if ((cycle+1) % 3 == 0) con.print(1, 0, "Target+: %d", forwardAmount);
        if ((cycle+2) % 3 == 0) con.print(2, 0, "Error: %d", (forwardAmount-motorAvg()));
      }
    } else if (!displayPage)
    {
      if (time % 100 == 0) con.clear();
      else if (time % 50 == 0) {
        cycle++;
        if (cycle % 3 == 0) con.print(0, 0, "IMU %f", imu.get_heading());
        if ((cycle+1) % 3 == 0) con.print(1, 0, "Target+: %f", turnAmount);
        if ((cycle+2) % 3 == 0) con.print(2, 0, "Error: %f", (turnAmount-imu.get_heading()));
      }
    }

    // Drive
    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)) drive = !drive;
    if (drive) arcadeDrive();

    // Encoder Tare
		if (con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) resetEncoders();

    // Forward Test
    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_UP))
    {
      driveStraight(forwardAmount);
      displayPage = true;
    }
    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN))
    {
      driveStraight(-forwardAmount);
      displayPage = true;
    }
    
    // Turn Test
    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT))
    {
      driveTurn(turnAmount);
      displayPage = false;
    }
    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN))
    {
      driveTurn(-turnAmount);
      displayPage = false;
    }

		time += 10;
		pros::delay(10);
	}
}