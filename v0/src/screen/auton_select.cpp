// #include "../autonomous/auton.hpp"
// #include "../config/config.hpp"
#include "main.h"
#include "auton/auton.hpp"
#include <iostream>
#include <unistd.h>
// #include "screen.hpp"

// create the menu
lv_obj_t *autonMenu = lv_ddlist_create(lv_scr_act(), NULL);
lv_style_t style_list;

// reset position button
lv_obj_t *resetPositionButton = lv_btn_create(lv_scr_act(), NULL);
lv_obj_t *resetPositionLabel = lv_label_create(resetPositionButton, NULL);

// startAuton button 
// lv_obj_t *startAutonButton = lv_btn_create(lv_scr_act(), NULL);
// lv_obj_t *StartAutonLabel = lv_label_create(startAutonButton, NULL);
// reset turret button
// lv_obj_t *resetTurretButton = lv_btn_create(lv_scr_act(), NULL);
// lv_obj_t *resetTurretLabel = lv_label_create(resetTurretButton, NULL);

// button callback
static lv_res_t resetPositionCallback(lv_obj_t *btn) {
  // reset the position
 resetAuton();

  // return
  return LV_RES_OK;
}
static lv_res_t startAuton(lv_obj_t *btn) {
  // reset the position
//  resetAuton();
// autonomous();
// sleep(3);
pros::delay(3000);
autonomous();
  // return
  return LV_RES_OK;
}

// turret callback
// static lv_res_t resetTurretCallback(lv_obj_t *btn) {
//   // reset the position
//   turret_rot->reset();

//   // return
//   return LV_RES_OK;
// }
// task
void DautonSelectTask() {
  while (true) {
    // get the selected option
    int selected = lv_ddlist_get_selected(autonMenu);

    // set the auton - corresponds to the enum's value

    // auton::setAutonMode((auton::AutonMode)selected);
    setAutonMode(selected);
    /// wait
    pros::delay(20);
  }
}
// initailize the menu
void DinitializeAutonSelect() {
  // set the options
  lv_ddlist_set_options(autonMenu, "Red Side\nBlue side\nSkills\nNone");
  // set the button text
  lv_label_set_text(resetPositionLabel, "Reset Position");
  // lv_label_set_text(StartAutonLabel, "Start Auton.");
  // lv_label_set_text(resetTurretLabel, "Reset Turret");

  // set the position
  lv_obj_set_pos(autonMenu, 200, 150);
  lv_obj_set_pos(resetPositionButton, 320, 120);
  // lv_obj_set_pos(startAutonButton, 220, 120);
  // lv_obj_set_pos(resetTurretButton, 204, 210);

  // set the size
  lv_obj_set_size(autonMenu, 200, 50);
  lv_btn_set_fit(resetPositionButton, true, true);
  // lv_btn_set_fit(resetTurretButton, true, true);

  // reduce the padding to 3 px
  lv_style_copy(&style_list, &lv_style_plain);
  style_list.body.padding.hor = 3;
  style_list.body.padding.ver = 3;
  style_list.body.padding.inner = 3;
  lv_ddlist_set_style(autonMenu, LV_DDLIST_STYLE_BG, &style_list);
  // lv_btn_set_style(resetPositionButton, LV_BTN_STYLE_REL, &style_list);
  // lv_btn_set_style(resetTurretButton, LV_BTN_STYLE_REL, &style_list);

  // on click
  lv_btn_set_action(resetPositionButton, LV_BTN_ACTION_CLICK,
                    resetPositionCallback);

  //  lv_btn_set_action(startAutonButton, LV_BTN_ACTION_CLICK,
                    // startAuton);
                    
//   lv_btn_set_action(resetTurretButton, LV_BTN_ACTION_CLICK,
                    // resetTurretCallback);

  // create the task
  pros::Task autonMenuTask(DautonSelectTask);
}

