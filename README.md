# Computer Vision-Guided Robotic Recycling System

This project automates waste segregation using computer vision and a 3D-printed robotic arm. It leverages ESP32-CAM and Arduino Mega 2560 for real-time detection and sorting of recyclables such as plastic bottles, aluminum, paper, and tetrapaks. Currently, the system is specifically designed to detect and sort only plastic bottles. However, it has a modular design that allows for future expansion to include additional materials. By training the model with new image datasets for other waste types and updating the sorting mechanism, the system can be adapted to improve recycling efficiency across various recyclable materials.

# Table of Contents

## Table of Contents

- [Key Features](#key-features)
- [Hardware Used](#hardware-used)
- [Software](#software)
- [How It Works](#how-it-works)
- [Performance](#performance)
- [Changes to Be Made](#changes-to-be-made)
  - [1. Object Detection Code](#1-object-detection-code)
    - [Modify Waste Categories](#modify-waste-categories)
    - [Adjust Conveyor Belt Speed](#adjust-conveyor-belt-speed)
    - [Customize Servo Motor Movement](#customize-servo-motor-movement)
    - [Change Object Detection Model](#change-object-detection-model)
    - [Adjust Ultrasonic Sensor Sensitivity](#adjust-ultrasonic-sensor-sensitivity)
    - [Modify Suction Pump Activation](#modify-suction-pump-activation)
  - [2. Robotics Code](#2-robotics-code)
    - [Adjust Distance Thresholds](#adjust-distance-thresholds)
    - [Change Motor Speed](#change-motor-speed)
    - [Modify Suction Timing](#modify-suction-timing)
    - [Change Motor Direction Logic](#change-motor-direction-logic)
    - [Modify Ultrasonic Sensor Range](#modify-ultrasonic-sensor-range)
    - [Adjust Motor Control Pins](#adjust-motor-control-pins)
    - [Modify Serial Output](#modify-serial-output)
- [Future Improvements](#future-improvements)
- [License](#license)

## Key Features
- **Object Detection**: Uses a **MobileNetV2 FOMO model** trained via **Edge Impulse**, achieving **94% accuracy** and an **F1 score of 96.3%** for real-time waste classification.
- **Robotic Arm**: A 3D-printed arm equipped with ultrasonic sensors and a vacuum pump to pick and place waste into bins.
- **Modular Design**: Scalable system that can be adapted for various waste materials in recycling facilities.
- **Edge AI**: Machine learning models run directly on the ESP32-CAM for low-latency, on-device processing.

## Hardware Used
- ESP32-CAM
- Arduino Mega 2560
- Turnigy TGY50090M servo motor
- HC-SR04 Ultrasonic Sensor
- Mini Air Vacuum Pump WPV40
- 17HS4401 Stepper Motor

## Software
- **Edge Impulse**: For model training and deployment.
- **Arduino IDE**: For programming the microcontrollers.
- **Autodesk Fusion 360** and **Ultimaker Cura**: For 3D modeling and printing.

## How It Works
1. The **ESP32-CAM** captures images of waste items on a conveyor belt.
2. A **MobileNetV2 FOMO model** detects and classifies the items.
3. A **robotic arm** picks up the waste and places it in the appropriate bin using suction.
4. The system operates in real-time, handling different waste types efficiently.

## Performance
- **Accuracy**: 94% testing accuracy in waste classification.
- **Efficiency**: Capable of sorting waste in real-time, with minimal misidentifications.

## Changes to Be Made

This section provides suggestions on how users can modify the system to fit their hardware and requirements. The modifications are divided into two parts: one for the **Object Detection Code** and one for the **Robotics Code**.

### 1. Object Detection Code

Below are possible code changes for the object detection section of the project:

#### Modify Waste Categories
- **Change**: Train the model to detect additional waste types.
- **How**: Collect new images, label them using **Edge Impulse**, and update the model with the new dataset.
- **Code**: Update the `ei_camera_capture()` and `run_classifier()` functions to reflect new class labels and retrained models.

#### Adjust Conveyor Belt Speed
- **Change**: Alter the conveyor speed for different processing rates.
- **How**: Update the motor control code to match your conveyor belt setup.
- **Code**:
  ```cpp
  motor.setSpeed(new_speed_value);
  ```
  
### Customize Servo Motor Movement
- *Change*: Adjust the servo motor angles based on your setup.
- *How*: Modify the arm's rotational limits for more precise or extended movement.
- *Code*: Update the `moveServo(float theta)` function to adjust the rotation angles:
   ```cpp
   for(pos = 0; pos <= desired_angle; pos += step){
       servo.write(pos);
       delay(delay_time);
   }
   ```
### Change Object Detection Model
- *Change*: Switch to a different model, like YOLO or Faster R-CNN, for more advanced detection.
- *How*: Retrain and deploy a new model with Edge Impulse or another platform, then integrate it into the code.
- *Code*: Replace the classifier model in the `run_classifier()` function to load the new model’s weights and structure.

### Adjust Ultrasonic Sensor Sensitivity
- *Change*: Tweak the sensitivity of the ultrasonic sensor for more accurate object detection distances.
- *How*: Modify the trigger and echo timings in the ultrasonic sensor code.
- *Code*: Adjust the sensor's threshold in the `checkUltrasonicSensor()` function:
   ```cpp
   if (distance < desired_distance) {
       // Trigger object handling process
   }
   ```

### Modify Suction Pump Activation
- *Change*: Adjust when and how the suction mechanism is triggered.
- *How*: Change the conditions under which the pump engages based on the object’s size or type.
- *Code*: Modify the `initiateSuction()` function to include new conditions:
   ```cpp
   if (object_type == "bottle" && distance < desired_threshold) {
       activateSuction();
   }
   ```

### 2. Robotics Code
Here are possible changes for the robotics and motor control part of the project:

### Adjust Distance Thresholds
- *Change*: Modify the maximum distance `(MAX_DIST)` and contact distance `(CONTACT_DIST)` based on your needs.
- *How*: Update the values to adjust when the motor starts or the suction begins.
- *Code*:
   ```cpp
   #define MAX_DIST 15.00  // Adjust this based on your setup
   #define CONTACT_DIST 5.0  // Adjust to the contact distance of your objects
   ```

### Change Motor Speed
- *Change*: Modify the motor speed by adjusting the value passed to `analogWrite()` in functions like `moveMotor()`, `reverseMotor()`, and `motorReset()`.
- *How*: Update the PWM value (0-255) to increase or decrease the motor's speed.
- *Code*:
   ```cpp
   analogWrite(enA, 128);  // Increase this value for faster motor speed
   ```

### Modify Suction Timing
- *Change*: Adjust the timing of the suction process for different object sizes or conveyor speeds.
- *How*: Modify the delay values in the `initiateSuction()` function to change the duration of the suction and motor reset timings.
- *Code*:
   ```cpp
   delay(3000);  // Decrease or increase this delay based on suction needs
   ```

### Change Motor Direction Logic
- *Change*: Adjust the motor direction by switching the pins in the `reverseMotor()` or `motorReset()` functions.
- *How*: Swap the pin values to change the motor's direction.
- *Code*:
   ```cpp
   digitalWrite(in1, HIGH);  // Change the logic here to alter motor direction
   digitalWrite(in2, LOW);   // Reverse these to change direction
   ```

### Modify Ultrasonic Sensor Range
- *Change*: Fine-tune the sensor range by adjusting how the sensor readings trigger different actions.
- *How*: Modify the logic in the `triggerSensor()` function to change how sensor data is processed.
- *Code*:
   ```cpp
   if (dist < 2.0 || dist > 15.0) {  // Adjust these values based on sensor range and application
       // Do something
   }
   ```

### Adjust Motor Control Pins
- *Change*: Use different GPIO pins for motor control or relay depending on your hardware configuration.
- *How*: Update the `enA`, `in1`, `in2`, and `relayPin` definitions to the appropriate pins on your setup.
- *Code*:
   ```cpp
   const int enA = 5;  // Change pin number based on your setup
   const int in1 = 6;  // Update this for motor direction control
   const int in2 = 7;  // Update this for motor direction control
   ```

### Modify Serial Output
- *Change*: Adjust or remove the `Serial.print()` statements to customize the output or remove debug information.
- *How*: Add, remove, or change the content of the `Serial.println()` calls for debugging or status reporting.
- *Code*:
   ```cpp
   Serial.println("Custom message here");  // Update this to fit your needs
   ```

Feel free to make these changes to tailor the system to your specific hardware setup and use case!
  
## Future Improvements
- Advanced sorting for mixed materials.
- Enhanced sensors (e.g., X-ray or spectroscopy).
- Adaptive learning systems for better performance over time.
- Industry collaboration for larger-scale deployments.

## License
This project is open-source and free to use. Feel free to modify and distribute it as needed.
