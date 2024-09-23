# Computer Vision-Guided Robotic Recycling System

This project automates waste segregation using computer vision and a 3D-printed robotic arm. It leverages ESP32-CAM and Arduino Mega 2560 for real-time detection and sorting of recyclables such as plastic bottles, aluminum, paper, and tetrapaks. Currently, the system is specifically designed to detect and sort only plastic bottles. However, it has a modular design that allows for future expansion to include additional materials. By training the model with new image datasets for other waste types and updating the sorting mechanism, the system can be adapted to improve recycling efficiency across various recyclable materials.

# Table of Contents

1. [Key Features](#key-features)
   - [Object Detection](#object-detection)
   - [Robotic Arm](#robotic-arm)
   - [Modular Design](#modular-design)
   - [Edge AI](#edge-ai)
2. [Hardware Used](#hardware-used)
3. [Software](#software)
4. [How It Works](#how-it-works)
5. [Performance](#performance)
   - [Accuracy](#accuracy)
   - [Efficiency](#efficiency)
6. [Changes to Be Made](#changes-to-be-made)
   - [Modify Waste Categories](#modify-waste-categories)
   - [Adjust Conveyor Belt Speed](#adjust-conveyor-belt-speed)
   - [Customize Servo Motor Movement](#customize-servo-motor-movement)
   - [Change Object Detection Model](#change-object-detection-model)
   - [Adjust Ultrasonic Sensor Sensitivity](#adjust-ultrasonic-sensor-sensitivity)
   - [Modify Suction Pump Activation](#modify-suction-pump-activation)
7. [Future Improvements](#future-improvements)

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

Below are possible code changes users can make to customize the system:

### 1. Modify Waste Categories
- **Change**: Train the model to detect additional waste types.
- **How**: Collect new images, label them using **Edge Impulse**, and update the model with the new dataset.
- **Code**: Update the `ei_camera_capture()` and `run_classifier()` functions to reflect new class labels and retrained models.

### 2. Adjust Conveyor Belt Speed
- **Change**: Alter the conveyor speed for different processing rates.
- **How**: Update the motor control code to match your conveyor belt setup.
- **Code**: Modify the speed parameter in the motor control section:
  ```cpp
  motor.setSpeed(new_speed_value);
  ```

### 3. Customize Servo Motor Movement
- **Change**: Adjust the servo motor angles based on your setup.
- **How**: Modify the arm's rotational limits for more precise or extended movement.
- **Code**: Update the `moveServo(float theta)` function to adjust the rotation angles:
  ```cpp
  for(pos = 0; pos <= desired_angle; pos += step){
      servo.write(pos);
      delay(delay_time);
  }
  ```

### 4. Change Object Detection Model
- **Change**: Switch to a different model, like YOLO or Faster R-CNN, for more advanced detection.
- **How**: Retrain and deploy a new model with Edge Impulse or another platform, then integrate it into the code.
- **Code**: Replace the classifier model in the `run_classifier()` function to load the new model’s weights and structure.
  
### 5. Adjust Ultrasonic Sensor Sensitivity
- **Change**: Tweak the sensitivity of the ultrasonic sensor for more accurate object detection distances.
- **How**: Modify the trigger and echo timings in the ultrasonic sensor code.
- **Code**: Adjust the sensor's threshold in the `checkUltrasonicSensor()` function:
  ```cpp
  if (distance < desired_distance) {
      // Trigger object handling process
  }
  ```

### 6. Modify Suction Pump Activation
- **Change**: Adjust when and how the suction mechanism is triggered.
- **How**: Change the conditions under which the pump engages based on the object’s size or type.
- **Code**: Modify the `initiateSuction()` function to include new conditions:
  ```cpp
  if (object_type == "bottle" && distance < desired_threshold) {
      activateSuction();
  }
  ```
  
## Future Improvements
- Advanced sorting for mixed materials.
- Enhanced sensors (e.g., X-ray or spectroscopy).
- Adaptive learning systems for better performance over time.
- Industry collaboration for larger-scale deployments.

## License
This project is open-source and free to use. Feel free to modify and distribute it as needed.
