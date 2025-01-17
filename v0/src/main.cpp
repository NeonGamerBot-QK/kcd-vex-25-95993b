#include "main.h"
#include "auton/auton.hpp"
#include "config.hpp"
#include "buttons/handleIntake.hpp"
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
std::cout << "\x1B[2J\x1B[H";
	 std::cout << R"(

.dP"Y8    db       db    88  88 88 88     
`Ybo."   dPYb     dPYb   88  88 88 88     
o.`Y8b  dP__Yb   dP__Yb  888888 88 88  .o 
8bodP' dP""""Yb dP""""Yb 88  88 88 88ood8 
       
)" << '\n';
std::cout << "\033[1;33mMade by saahil (saahild.com) and ran in Pros\033[00m";
	//pros::lcd::register_btn1_cb(on_center_button);
pros::adi::Pneumatics  sensor('A', DIGITAL_SENSOR_PORT);
sensor.set_value(false);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	// d
}

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
	// TODO: auton
	runAuton();
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
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({RIGHT_FRONT_PORT, RIGHT_BACK_PORT  });    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({ LEFT_FRONT_PORT, LEFT_BACK_PORT });  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	pros::adi::Pneumatics  sensor('A', DIGITAL_SENSOR_PORT);
	pros::Motor intake2(8);
	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs
		
		// print the dir and turn
		// Arcade control scheme
		if(pros::lcd::read_buttons() & LCD_BTN_LEFT) {
		setAutonMode(1);
		} else if(pros::lcd::read_buttons() & LCD_BTN_CENTER) {
		setAutonMode(3);
		} else if(pros::lcd::read_buttons() & LCD_BTN_RIGHT) {
		setAutonMode(2);
		} 
		int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		left_mg.move(dir - -turn);                      // Sets left motor voltage
		right_mg.move(dir + -turn);                     // Sets right motor voltage
		std::cout << dir - -turn << '\n';
		std::cout << dir + -turn << '\n';
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			handleIntake();
		} 
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			reverseIntake();
		} 
		if(!master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			brakeIntake();
		}
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
			intake2.move(127);
		} else {
			intake2.brake();
		}
		// stay as a toggle
		// no
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			sensor.toggle();
		}
		pros::delay(19);                               // Run for 19 ms then update
	}
}
