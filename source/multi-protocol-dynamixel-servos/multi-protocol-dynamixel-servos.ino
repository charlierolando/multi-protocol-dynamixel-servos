#include <DynamixelWorkbench.h>
// p1 or P1 -> Protocol 1.0
// p2 or P2 -> Protocol 2.0

#define CMD_PORT     Serial // Set CMD Port
#define BAUDRATE     1000000  // Set 1Mbps baudrate

#if defined(__OPENCM904__)
#define DEVICE_NAME "1" //Dynamixel on Serial1 <-OpenCM 9.04
#elif defined(__OPENCR__)
#define DEVICE_NAME ""
#endif

#define USING_PROTOCOL_1 true
#define NUMBER_OF_PROTOCOL_1_SERVO 2
const uint8_t p_1_id[NUMBER_OF_PROTOCOL_1_SERVO] = {1, 2}; // {servo_ID_1, servo_ID_2, ...};

#define USING_PROTOCOL_2 true
#define NUMBER_OF_PROTOCOL_2_SERVO 3
const uint8_t p_2_id[NUMBER_OF_PROTOCOL_2_SERVO] = {3, 4, 5}; // {servo_ID_3, servo_ID_4, ...};

#if USING_PROTOCOL_1
DynamixelWorkbench p_1;
int32_t p_1_syncwrite_variable[NUMBER_OF_PROTOCOL_1_SERVO];

#endif

#if USING_PROTOCOL_2
DynamixelWorkbench p_2;
int32_t p_2_syncwrite_variable[NUMBER_OF_PROTOCOL_2_SERVO];

#endif

const uint8_t handler_index = 0;

void setup()
{
  CMD_PORT.begin(BAUDRATE);

  CMD_PORT.println("setup");

#if defined(__OPENCM904__)

#else
  pinMode(BDPIN_BUZZER, OUTPUT); // Set BDPIN_BUZZER - pin 31 as an output
  // beep sound
  tone(BDPIN_BUZZER, 1500); // Send 1.5KHz sound signal...

  digitalWrite(BDPIN_DXL_PWR_EN, HIGH); // set Dxl Power Pin to High // TTL power is on

#endif

  // setup device and baudrate
  setup_dxl_wb();
  // setup syncwrite
  add_goalpos_syncWrite();

  // enable torque all p1 servos
  enable_torque("p_1", true);
  // enable torque all p2 servos
  enable_torque("p_2", true);

  // turn on all p1 led servos
  enable_led("p_1", true);
  // turn on all p2 led servos
  enable_led("p_2", true);

  delay(1000);
  // turn off all p1 and/or p2 led servos
  turn_off_led_all_servo();

  // beep sound
  beep();

  CMD_PORT.println("setup done");

}

void loop()
{
  p_1_syncwrite_variable[0] = 0; // set the goal position to p_1_id[0]
  p_1_syncwrite_variable[1] = 0; // set the goal position to p_1_id[1]
  
  p_2_syncwrite_variable[0] = 0; // set the goal position to p_2_id[0]
  p_2_syncwrite_variable[1] = 0; // set the goal position to p_2_id[1]
  p_2_syncwrite_variable[2] = 0; // set the goal position to p_2_id[2]
  
  do_syncWrite(); // write the goal position for p1 and p2

  delay(1000);

  p_1_syncwrite_variable[0] = 4095; // set the goal position to p_1_id[0] // comment this if not use syncWrite
  p_1_syncwrite_variable[1] = 1023; // set the goal position to p_1_id[1] // comment this if not use syncWrite
  // p_1.goalPosition(p_1_id[0], (int32_t)4095); // write the goal position to p_1_id[0] // uncomment this if not use syncWrite
  // p_1.goalPosition(p_1_id[1], (int32_t)1023); // write the goal position to p_1_id[1] // uncomment this if not use syncWrite
  
  p_2_syncwrite_variable[0] = 4095; // set the goal position to p_2_id[0] // comment this if not use syncWrite
  p_2_syncwrite_variable[1] = 4095; // set the goal position to p_2_id[1] // comment this if not use syncWrite
  p_2_syncwrite_variable[2] = 1023; // set the goal position to p_2_id[2] // comment this if not use syncWrite
  // p_2.goalPosition(p_2_id[0], (int32_t)4095); // write the goal position to p_2_id[0] // uncomment this if not use syncWrite
  // p_2.goalPosition(p_2_id[1], (int32_t)4095); // write the goal position to p_2_id[1] // uncomment this if not use syncWrite
  // p_2.goalPosition(p_2_id[2], (int32_t)1023); // write the goal position to p_2_id[2] // uncomment this if not use syncWrite
  
  do_syncWrite(); // write the goal position for p1 and p2 // comment this if not use syncWrite
  delay(1000);

  // while (1);
}
