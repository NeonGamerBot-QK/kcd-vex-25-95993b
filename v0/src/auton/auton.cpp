#include "main.h"
#include "buttons/handleIntake.hpp"
#include "../config.hpp"
	pros::MotorGroup left_mg({RIGHT_FRONT_PORT, RIGHT_BACK_PORT  });    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({ LEFT_FRONT_PORT, LEFT_BACK_PORT });  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	pros::adi::Pneumatics  sensor('A', DIGITAL_SENSOR_PORT);
	pros::Motor intake2(8);
void runAuton() {
	// handleIntake();
	intake2.move(127);
	left_mg.move(120);
	right_mg.move(120);
	pros::delay(600);
	left_mg.move(0);
	right_mg.move(0);
	intake2.brake();
	pros::delay(200);
	// brakeIntake();
	left_mg.move(-127);
	right_mg.move(-127);
	pros::delay(350);
	left_mg.move(0);
	right_mg.move(0);
	pros::delay(10);
	// sensor.toggle();
	left_mg.move(120);
	right_mg.move(120);
	pros::delay(220);
	left_mg.move(0);
	right_mg.move(0);
	// sensor.toggle();
}
void resetAuton();

void setAutonMode(int mode);