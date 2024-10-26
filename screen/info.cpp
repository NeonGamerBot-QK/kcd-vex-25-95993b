// #include "../tasks/tasks.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
// #include "screen.hpp"

// text label
lv_obj_t *informationTextLabel = lv_label_create(lv_scr_act(), NULL);


// task
void DinformationTask() {
  while (true) {
    // get the match mode
    auto status = pros::competition::get_status();

    // to string
    std::string compStatus =
        (status == COMPETITION_DISABLED     ? "Disabled"
         : status == COMPETITION_AUTONOMOUS ? "Autonomous"
         : status == COMPETITION_CONNECTED  ? "Driver Control"
                                            : "Unknown");

    // get the battery level
    auto battery = pros::battery::get_capacity();
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    auto controllerBattery = master.get_battery_capacity();
    auto isControllerConnected = (master.is_connected() == 0 ? "Disconnected" : master.is_connected() == 1 ? "Connected (wired)" : master.is_connected() == 2 ? "Connected (wireless)" : "Unk");
    pros::Motor left_mtr(1);
    auto motorPos = left_mtr.get_voltage();
    // auto controllerStatus = pros::E_CONTROLLER_MASTER
    // turret target angle
    // auto target = tasks::turretTargetAngle;

    // target speed
    // auto speed = tasks::flywheelTargetSpeed;

    // build a big string
    std::string text = "Match Mode: " + compStatus + "\n" +
                       "Brain Battery: " + std::to_string((int)battery) + "%\n" +
                       "Controller Battery: " + std::to_string((int) controllerBattery) + "%\n"+ 
                       "ConStat: " + isControllerConnected + "\n" +
                    //    "MotorPos: "+ ((char)motorPos) + "\n" + 
                       "Coded by Saahil (saahild.com)";
                    //    "Turret Target: " + std::to_string(target) + "\n" +
                    //    "Flywheel Target: " + std::to_string(speed) + "\n";

    // put the information in the text area
    lv_label_set_text(informationTextLabel, text.c_str());

    // wait
    pros::delay(100);
  }
}

void DinitializeInformation() {
  // goes to the right of the field
  lv_obj_set_pos(informationTextLabel, 200, 0);
  // DinformationTask();

  pros::Task infoTask(DinformationTask);

  // create the task
//   Task informationTask(display::informationTask);
}
