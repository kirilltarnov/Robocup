#include "motors.h"
#include "Arduino.h"
#include "weight_collection.h"
#include "sensors.h"
bool pickup_calibration_complete = false;
bool can_trigger = true;
int timer = 0;
bool thing = true;
int pickup_state = 0;
int Navigation_State = 0;
int turn_angle = 0;
int limit_switch;
/* Check whether the speed value to be written is within the maximum
 *  and minimum speed caps. Act accordingly.
 *
 */
void check_speed_limits(/*parameters*/) {
  //Serial.println("Check the motor speed limit \n");
}


/* In this section, the motor speeds should be updated/written.
 *It is also a good idea to check whether value to write is valid.
 *It is also a good idea to do so atomically!
 */
//Pick-up motor values (looking at the motor front on):
//1500-1950 = anticlockwise
//1050-1500 = clockwise

void DC_motors() {

   if(io.digitalRead(15) == 1){
    can_trigger = false;
  }

  switch (Navigation_State) {
    case No_move:
        if (can_trigger == false) {
          Navigation_State = Moveforward;
        }
      break;
    case Moveforward:
      if (Left_sensor > 550 || Right_sensor > 550 ) {
        Navigation_State = MoveBackward;
        Encoder_Left = 0; //reset encoder values 
        Encoder_Right = 0;

        turn_angle = random(3000,9000); // determine turn angle
      }
      break;
    case MoveBackward:
      if ((Encoder_Left < -500 && Encoder_Right < -500)) {
        if (turn_angle > 6000){
          Navigation_State = 4;
        } else {
          Navigation_State = 3;
        }
        Encoder_Left = 0;
        Encoder_Right = 0;
      }
      break;
    case TurnRight:
      if (Encoder_Left > turn_angle && Encoder_Right < -turn_angle) {
        Navigation_State = Moveforward;
      }
      break;
    case TurnLeft:
      if(Encoder_Left < -(12000 - turn_angle) && Encoder_Right > (12000 - turn_angle)) {
        Navigation_State = 1;
      }
    break;
  }
      
  switch(pickup_state) {
    case 0:
      pickup_motor.writeMicroseconds(joystick_map_x);
      if (can_trigger == false) {
        pickup_state = 1;
      }
      break;
    case 1:
      if(limit_switch2 == 0) {
        pickup_motor.writeMicroseconds(1050);
      } else {
        pickup_motor.writeMicroseconds(1500);
        pickup_state = 2;
      }
      break;
    case 2:
      if (low_right_sensor > 350) {
        pickup_motor.writeMicroseconds(1950);
        pickup_state = 3;
      }
      break;
    case 3:
      if (limit_switch == HIGH) {
        pickup_state = 1;
        can_trigger = true;
    }
    
  }

//  if(Navigation_State == 1){
//    right_motor.writeMicroseconds(1950);
//    left_motor.writeMicroseconds(1950);
//  }else if (Navigation_State == 2) {
//    right_motor.writeMicroseconds(1050);
//    left_motor.writeMicroseconds(1050);
////    right_motor.writeMicroseconds(1500);
////    left_motor.writeMicroseconds(1500);
//  } else if (Navigation_State == 3) {
//    right_motor.writeMicroseconds(1050);
//    left_motor.writeMicroseconds(1950);
//  } else if (Navigation_State == 4) {
//    right_motor.writeMicroseconds(1950);
//    left_motor.writeMicroseconds(1050);
//  }


}
