#include "main.h"

#include "buttons/handleIntake.hpp"
#include "../config.hpp"
int amode = 0;
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
	case 2:
	// TODO: Blue side
	left_mg.move(100);
	right_mg.move(100);
	// sensor.set_value(true);
	intake2.move(127);
	handleIntake();
	pros::delay(1000);
		break;

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