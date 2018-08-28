# Ideas
* Functions for common tasks with autonomous.
* Use 3 Jumpers for switching autonomous.
  * Have one pin determine autonomous version. (Far tile or close tile relative to flags)
  * Have the other pin determine team color. (In means Red, out means Blue)
  * Have the last jumper determine if we are going to attempt parking.
    * Reasoning: Allied Robot may also attempt parking in their autonomous, making ours toggleable would prevent damages during autonomous period.
  * Allows us to have 8 different autonomi plans 'saved'.
  * Autonomous variations (Tile, Team, Parking):
   * 0,0,0 = Flag Ops Autonomous, Red Team, Parking
   * 0,0,1 = Flag Ops Autonomous, Red Team, No parking
   * 0,1,0 = Flag Ops Autonomous, Blue Team, Parking
   * 0,1,1 = Flag Ops Autonomous, Blue Team, No Parking
   * 1,0,0 = Flipside Ops Autonomous, Red Team, Parking
   * 1,0,1 = Flipside Ops Autonomous, Red Team, No Parking
   * 1,1,0 = Flipside Ops Autonomous, Blue Team, Parking
   * 1,1,1 = Flipside Ops Autonomous, Blue Team, No Parking
* Use Motor Encoders to use for more accurate autonomi code.
* Run the manipulator (claw thingy) and drive train (wheels) on two seperate batteries, keeping dedicated power for each.

* A function that makes the bot rotate vigorously left and right in an attempt to make dislodging it from the platform more difficult
  * possible end function of autonomi if on platform
  * probably a button that you can press after reaching the top platform
  
## Possible Autonomi Ideas:
#### 1. Flag Ops:
* Conditions
 * Start from Tile 1, 4 (Red Tile closest to Flagpost)
 * Steps:
   1. Turn left facing the flags.
   2. Move forward to flag
   3. Hit Flag, making it Red.
   4. Move back to tile 1, 5 (One tile down from Flagpost)
   5. Turn right facing Cap.
   6. Flip Cap. (If Parking Jumper is not active, end here)
   7. Turn right facing starting tiles.
   8. Move to tile 1, 3 (Tile with a straight path to parking platform)
   9. Turn left facing parking platform.
   10. Move to parking platform.
   11. End.

#### 2. Flipside Ops:
* Conditions:
  * Start from Tile 1, 2 (Red tile furthest from Flagpost)
* Steps:
  1. Turn right facing the south wall of field.
  2. Move to tile 1, 1 (Southwest corner tile)
  3. Turn left facing blue cap.
  4. Move to tile 3, 1 (Tile with blue cap)
  5. Flip Cap. (If Parking Jumper is not active, end here)
  6. Back up to point of straight path with parking platform.
  7. Turn left facing parking platform.
  8. Move to parking platform.
  9. End.
