#include "main.h"
pros::Motor intake(INTAKE_PORT);
pros::Motor intake2(INTAKE_PORT);
void handleIntake() {
    intake = 127;
    intake2 = 127;
}
