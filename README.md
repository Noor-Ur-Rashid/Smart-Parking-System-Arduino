# Smart Parking System Using Arduino

## Overview

The Smart Parking System is an Arduino-based embedded system designed to automate vehicle entry and parking slot monitoring. The system utilizes RFID technology for vehicle authentication, ultrasonic sensors for parking slot detection, and a servo motor for automated gate control. Real-time parking information is displayed through an LCD module and LED indicators, providing a user-friendly parking management solution.

This project was developed to address common parking management issues such as traffic congestion, inefficient space utilization, and delays in vehicle access control.

---

## Features

* RFID-based vehicle authentication
* Automatic gate control using servo motor
* Real-time parking slot monitoring
* LCD display for parking status updates
* LED indicators for slot availability
* Buzzer notification system
* Unauthorized RFID card detection and access denial
* Support for 2 parking slots

---

## Hardware Components

| Component                 | Quantity |
| ------------------------- | -------- |
| Arduino Uno               | 1        |
| RFID RC522 Module         | 1        |
| Ultrasonic HC-SR04 Sensor | 2        |
| Servo SG90 Motor          | 1        |
| 16x2 LCD Display          | 1        |
| Red LED                   | 1        |
| Green LED                 | 1        |
| Buzzer                    | 1        |

---

## System Workflow

1. Vehicle approaches the entrance gate.
2. RFID card is scanned using the RC522 reader.
3. The system verifies whether the card is authorized.
4. If authorized, available parking slots are checked using ultrasonic sensors.
5. The servo motor opens the gate if a parking slot is available.
6. Parking status is displayed on the LCD screen.
7. LED indicators provide visual feedback.
8. Unauthorized RFID cards are denied access and appropriate alerts are triggered.

---

## Circuit Design

The system was implemented using an Arduino Uno as the main controller. RFID technology was used for authentication while ultrasonic sensors continuously monitored parking slot occupancy. A servo motor controlled gate movement and an LCD display provided user feedback.

Circuit diagrams and Wokwi simulation files are included in this repository.

---

## Results

The system successfully:

* Automated vehicle authentication and access control.
* Detected parking slot occupancy in real time.
* Controlled gate operations automatically.
* Prevented unauthorized vehicle entry.
* Improved parking management efficiency.

---

## Screenshots

### Physical Prototype

(Add image here)

### Circuit Setup

(Add image here)

### RFID Authentication

(Add image here)

### LCD Display Output

(Add image here)

### Wokwi Simulation

(Add image here)

---

## Source Code

The Arduino source code used for the project is included in this repository.

---

## Future Improvements

* Mobile application integration
* Cloud-based parking monitoring
* License plate recognition
* Online parking reservation system
* IoT-based remote monitoring

---

## Technologies Used

* Arduino IDE
* Embedded C/C++
* RFID Technology
* Ultrasonic Sensing
* Embedded Systems Design

---

## Author

Noor Ur Rashid

Bachelor of Computer Engineering
Asia Pacific University of Technology & Innovation (APU)

GitHub: https://github.com/Noor-Ur-Rashid

LinkedIn: https://www.linkedin.com/in/noor-ur-rashid-148b352a3/
