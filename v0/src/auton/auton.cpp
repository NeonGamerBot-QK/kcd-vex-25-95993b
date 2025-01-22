#include "main.h"

#include "buttons/handleIntake.hpp"
#include "../config.hpp"
// dev mode so im changing the value; please use 0 in prod
int amode = 1;
	pros::MotorGroup left_mg({RIGHT_FRONT_PORT, RIGHT_BACK_PORT  });    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({ LEFT_FRONT_PORT, LEFT_BACK_PORT });  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	pros::adi::Pneumatics  sensor('A', DIGITAL_SENSOR_PORT);
	pros::Motor intake2(8);
	void resetAuton() {
	intake2.brake();
	left_mg.brake();
	right_mg.brake();
	brakeIntake();
}


void runAuton() {
	switch(amode) {
		case 1:
	// Red side
	left_mg.move(127);
	right_mg.move(127);
	std::cout << "#debug move" << std::endl;
	pros::delay(950);
	// brake
	left_mg.brake();
	right_mg.brake();
	std::cout << "#debug brake" << std::endl;
	pros::delay(20);
	// turn to the direction to grab the goal.
	// echo to terminal asw
	std::cout << "#debug turn right" << std::endl;
	left_mg.move(-127);
	right_mg.move(127);
	pros::delay(230);
		// brake
	left_mg.brake();
	right_mg.brake();
	pros::delay(20);
	std::cout << "#debug open air" << std::endl;
	sensor.set_value(true);
// TODO: test the rest
	// move back 
	right_mg.move(-100);
	left_mg.move(-100);
	pros::delay(50);
		left_mg.brake();
	right_mg.brake();
	sensor.set_value(false);
// now lets take in the nearby thingy
	intake2.move(127);
	handleIntake();
	right_mg.move(127);
	left_mg.move(127);
	pros::delay(500);
	resetAuton();
		break;
	case 2:
	// TODO: Blue side
		left_mg.move(100);
	right_mg.move(100);
	// brake
	left_mg.brake();
	right_mg.brake();
	// turn to the direction to grab the goal.
	left_mg.move(-100);
	right_mg.move(-100);
	pros::delay(1000);
		// brake
	left_mg.brake();
	right_mg.brake();
	sensor.set_value(true);
	// move back 
	right_mg.move(-127);
	left_mg.move(-127);
	pros::delay(200);
		left_mg.brake();
	right_mg.brake();
	sensor.set_value(false);
// now lets take in the nearby thingy
	right_mg.move(127);
	left_mg.move(127);
	intake2.move(127);
	handleIntake();
	pros::delay(1000);
	break;
case 3:
	// TODO: Auton
	left_mg.move(100);
	right_mg.move(100);
	pros::delay(1000);
	break;
	} 

	resetAuton();
}


void setAutonMode(int mode) {
	amode = mode;
};