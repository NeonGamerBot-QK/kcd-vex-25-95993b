#include "../../include/buttons/handleIntake.hpp"
#include "../config.hpp"
#include "../../include/main.h"

pros::Motor intake(INTAKE_PORT);

void handleIntake() {
    intake.move(120) ;
}
void brakeIntake() {
    intake.brake();
}
void reverseIntake() {
    intake.move(-120);
}