# Hackabrick
This code allows the use of left and right mouse clicks through an arduino micro designed for the use of jelly buttons for those with limited dexterity. The code also allows the user to scroll up and down through the same buttons by holding the buttons in a certain sequence.

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
  
  The left button is programmed for pin 2
  The right button is programmed for pin 3
