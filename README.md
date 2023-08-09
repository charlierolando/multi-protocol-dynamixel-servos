# multi-protocol-dynamixel-servos

**Using many types of [Dynamixel Servos](https://github.com/ROBOTIS-GIT/emanual/blob/master/docs/en/dxl/dxl.md) with [OpenCM 9.04](https://github.com/ROBOTIS-GIT/emanual/blob/master/docs/en/parts/controller/opencm904.md) or [OpenCR 1.0](https://github.com/ROBOTIS-GIT/emanual/blob/master/docs/en/parts/controller/opencr10.md)**

>This tools has been checked with Dynamixel X Series, AX Series and MX Series

![Result](https://github.com/charlierolando/multi-protocol-dynamixel-servos/blob/main/images/images1.gif)

klik [this](https://github.com/charlierolando/multi-protocol-dynamixel-servos/blob/main/images/images1.gif) when the image doesn't appear

## [How to use:](#how-to-use)

**• Change CMD Port:**

```cpp title="editt.cpp"
#define CMD_PORT     Serial // Set CMD Port
```

**• Change Baudrate configuration:**

```cpp title="editt.cpp"
#define BAUDRATE     1000000  // Set 1Mbps baudrate
```

**• Change Servo configuration:**

```cpp title="editt.cpp"
#define USING_PROTOCOL_1 true
#define NUMBER_OF_PROTOCOL_1_SERVO 2
const uint8_t p_1_id[NUMBER_OF_PROTOCOL_1_SERVO] = {1, 2}; // {servo_ID_1, servo_ID_2, ...};

#define USING_PROTOCOL_2 true
#define NUMBER_OF_PROTOCOL_2_SERVO 3
const uint8_t p_2_id[NUMBER_OF_PROTOCOL_2_SERVO] = {3, 4, 5}; // {servo_ID_5, servo_ID_6, ...};
```

**a. Set this to *true or *false, when using/not using Protocol 1.0 and/or Protocol 2.0:**

```cpp title="editt.cpp"
#define USING_PROTOCOL_1 *true

#define USING_PROTOCOL_2 *true
```

**b. Set *number of servo:**

```cpp title="editt.cpp"
#define NUMBER_OF_PROTOCOL_1_SERVO *2

#define NUMBER_OF_PROTOCOL_2_SERVO *2
```

**c. Set ID *{servo_ID_1, servo_ID_2, servo_ID_3, ...}:**

```cpp title="editt.cpp"
const uint8_t p_1_id[NUMBER_OF_PROTOCOL_1_SERVO] = *{1, 2}; // {servo_ID_1, servo_ID_2, ...};

const uint8_t p_2_id[NUMBER_OF_PROTOCOL_2_SERVO] = *{3, 4, 5}; // {servo_ID_3, servo_ID_4, ...};
```

**• Servo Ping (must be included):**

```cpp title="editt.cpp"
  // setup device and baudrate
  setup_dxl_wb();
```

**• Add Goal Position syncWrite Handler (if you want use synWrite):**

```cpp title="editt.cpp"
  // setup syncwrite
  add_goalpos_syncWrite();
```

**• Enable/disable torque to all servo *(true/false):**

```cpp title="editt.cpp"
  enable_torque("p_1", *true);

  enable_torque("p_2", *true);
```

**• Enable/disable LED to all servo *(true/false):**

```cpp title="editt.cpp"
  enable_led("p_1", true);

  enable_led("p_2", true);
```

**• Write *position value to servo (snycWrite):**

>You must fill in the value for each servo in the index array that corresponds to the servo ID array index

```cpp title="editt.cpp"
  p_1_syncwrite_variable[0] = *0; // set the goal position to p_1_id[0]
  p_1_syncwrite_variable[1] = *0; // set the goal position to p_1_id[1]

  p_2_syncwrite_variable[0] = *0; // set the goal position to p_2_id[0]
  p_2_syncwrite_variable[1] = *0; // set the goal position to p_2_id[1]
  p_2_syncwrite_variable[2] = *0; // set the goal position to p_2_id[2]

  do_syncWrite(); // write the goal position for p1 and p2
```

**• Write *position value to servo (not use snycWrite):**

>You must fill in the value for each servo in the index array that corresponds to the servo ID array index

```cpp title="editt.cpp"
  p_1.goalPosition(p_1_id[0], (int32_t)*0); // write the goal position to p_1_id[0]
  p_1.goalPosition(p_1_id[1], (int32_t)*0); // white the goal position to p_1_id[1]
  
  p_2.goalPosition(p_2_id[0], (int32_t)*0); // white the goal position to p_2_id[0]
  p_2.goalPosition(p_2_id[1], (int32_t)*0); // white the goal position to p_2_id[1]
  p_2.goalPosition(p_2_id[2], (int32_t)*0); // white the goal position to p_2_id[2]
```