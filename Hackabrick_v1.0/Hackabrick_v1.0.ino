/*
    This is the first version of the Hackabrick software. This version allows 
    left and right mouse clicks along with a mouse scroll and an escape key, all
    from two inputs. (see more details below)
    Copyright (C) 2017  Daniel Van't Sant

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


  #######################################Instructions#######################################

  When the left button is held and the right button held after, the Hackabrick will simulate
  mouse scrolls until the right button is released, if another press of the right button
  occurs while the left button is still held down, the Hackabrick will simulate a mouse
  scroll in the other direction.

  If the right button is held and the left button is pressed the escape key
  will be pressed.

  This program was actually designed to make Sim City easier to play. With some modifications
  this program can be changed to suit your application.

  | Condition                                                     |  Action              |
  |---------------------------------------------------------------|----------------------|
  | Press Left Button Independantly                               | Left Mouse Click     |
  | Press Right Button Independantly                              | Right Mouse Click    |
  | Hold Left Button then Hold Right Button                       | Scroll Down          |
  | Hold Left Button then Press, Release then Hold Right Button   | Scroll Up            |
  | Hold Right Button then press Left Button                      | Escape Key Pressed   |
  -> On Board Light will turn on if any button is pressed for diagnostic reasons.

  ##########################################################################################
*/

//==Pin configuration:===
const int left = 2 ;
const int right = 3 ;
//=======================

//==Include Keyboard and Mouse Libraries==
#include <Mouse.h>
#include <Keyboard.h>
//========================================

//=======Keyboard && Mouse Modifiers==========
char upkey = KEY_UP_ARROW ;
char downkey = KEY_DOWN_ARROW ;
char leftkey = KEY_LEFT_ARROW ;
char rightkey = KEY_RIGHT_ARROW ;
char enterkey = KEY_RETURN ;
char ctrlkey = KEY_LEFT_CTRL ;
char shiftkey = KEY_LEFT_SHIFT ;
char esckey = KEY_ESC ;
char leftclick = MOUSE_LEFT ;
char rightclick = MOUSE_RIGHT ;
char middleclick = MOUSE_MIDDLE ;
char tabkey = KEY_TAB ;
char f11key = KEY_F11 ;
char f3key = KEY_F3;
char f2key = KEY_F2;
char f1key = KEY_F1;
char delkey = KEY_DELETE ;
char altkey = KEY_LEFT_ALT ;
char homekey = KEY_HOME ;
char endkey = KEY_END ;
char backspacekey = KEY_BACKSPACE ;
//============================================

//=======Program Variables========
byte val_left;
byte previous_val_left;
byte left_first;
byte left_first_both_pressed ;
byte previous_left_first_both_pressed;
byte left_direction = 0;

byte val_right;
byte previous_val_right;
byte right_first;
byte right_first_both_pressed ;
byte previous_right_first_both_pressed;
byte right_direction = 0;
//================================

//========For Scroll=========
//Adjust scroll_time to produce a faster scroll speed.(Time is in milliseconds)
int scroll_time = 300;
byte toggle_scroll;
byte do_scroll = 0;
byte previous_toggle_scroll;
//===========================

void setup() {
  //Pullup - switching to ground.
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  //Start the mouse and keyboard functions:
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  //============================Control Scroll Speed=====================================
  /*This part of the program controls do_scroll to equal one for one iteration during the
    period of scroll_time. This is required so that only one scroll of the mouse wheel
    occurs during the scroll_time period.*/
  toggle_scroll = clockSignal(scroll_time);
  do_scroll = possitiveTrigger(toggle_scroll, previous_toggle_scroll);
  //=====================================================================================

  //Delay introduced to stop glitching.
  delay(5);

  //==============Read Pin Status================
  val_left = !digitalRead(left);
  val_right = !digitalRead(right);
  //=============================================

  //==============On-Board Light Control==============================================
  //Turn the light on if either buttons pressed. (For Debugging)
  if (val_left == 1 || val_right == 1) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
  //==================================================================================

  //==============Decide which button was pressed first while both buttons are held====
  //If the left button was pressed first then set left_first to 1.
  if (val_left == 1 && val_right == 1 && previous_val_right == 0 ) {
    left_first = 1;
  }

  //If the right button was pressed first then set right_first to 1.
  if (val_left == 1 && val_right == 1 && previous_val_left == 0) {
    right_first = 1;
  }

  //reset both variables when both buttons are released
  if (val_left == 0 && val_right == 0) {
    left_first = 0;
    right_first = 0;
  }
  //===================================================================================

  //==============Change Direction while Left Held========================================
  //Whilst holding the left button toggle left_direction on and off with a press and
  //release of the right button.
  if (val_left == 1 && val_right == 1 && left_first == 1) {
    left_first_both_pressed = 1;
  }
  else {
    left_first_both_pressed = 0;
  }
  left_direction = toggle(left_first_both_pressed, previous_left_first_both_pressed,
                          left_direction);
  //======================================================================================

  //==============Change Direction while Right Held=========================================
  //Whilst holding the right button down toggle right_direction on and off with a press and
  //release of the left button.
  if (val_left == 1 && val_right == 1 && right_first == 1) {
    right_first_both_pressed = 1;
  }
  else {
    right_first_both_pressed = 0;
  }
  right_direction = toggle(right_first_both_pressed, previous_right_first_both_pressed,
                           right_direction);
  //========================================================================================

  //==============Execute Mouse Scroll=======================================================
  if (val_left == 1 && val_right == 1 && left_first == 1 && left_direction == 1
      && do_scroll == 1) {
    Mouse.move(0, 0, 1);
  }

  if (val_left == 1 && val_right == 1 && left_first == 1 && left_direction == 0
      && do_scroll == 1) {
    Mouse.move(0, 0, -1);
  }
  //=========================================================================================

  //===================Escape Key Press======================================================
  //Another key press can be introduced here quite simply by using a similar
  //program structure to the one above.
  if (val_left == 1 && val_right == 1 && right_first == 1) {
    Keyboard.press(esckey);
  } else {
    Keyboard.release(esckey);
  }
  //=========================================================================================

  //==============Standard Mouse Clicks=================================================
  if (val_left == 1 && val_right == 0 && left_first == 0 && right_first == 0) {
    Mouse.press(leftclick);
  } else {
    Mouse.release(leftclick);
  }

  if (val_right == 1 && val_left == 0 && left_first == 0 && right_first == 0) {
    Mouse.press(rightclick);
  } else {
    Mouse.release(rightclick);
  }
  //=====================================================================================

  //==============Release Keyboard Presses and Mouse Functions===========================
  if (left_first == 0 && right_first == 0 && val_left == 0 && val_right == 0) {
    Mouse.release(leftclick);
    Mouse.release(rightclick);
    Mouse.release(middleclick);
    Keyboard.releaseAll();
    Mouse.move(0, 0, 0); //Resets mouse scroll if on?
    do_scroll = 0;
  }
  //=====================================================================================

  //==============Save Previous Values===================
  previous_toggle_scroll = toggle_scroll;
  previous_val_left = val_left;
  previous_val_right = val_right;
  previous_left_first_both_pressed = left_first_both_pressed;
  previous_right_first_both_pressed = right_first_both_pressed;
  //=====================================================
}

byte clockSignal(int period) {
  // Continuously toggles on and off with a time period.
  byte output;
  if (millis() % period > 0.5 * period) {
    output = 1;
  }
  else {
    output = 0;
  }
  return output;
}

byte possitiveTrigger(byte actualInput, byte previousInput) {
  byte pulse;
  if (actualInput == 1 && previousInput == 0) {
    pulse = 1;
  }
  else {
    pulse = 0;
  }
  return pulse;
}

byte toggle(byte actualInput, byte previousInput, byte previousBoolean) {
  byte newBoolean;
  if (actualInput == 1 && previousInput == 0) {
    newBoolean = previousBoolean + 1;
  } else {
    newBoolean = previousBoolean;
  }
  newBoolean = newBoolean % 2;
  return newBoolean;
}











