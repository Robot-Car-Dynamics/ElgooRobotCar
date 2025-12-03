# ELEGOO Robot Car 2D Position and Orientation Tracking

This repo contains code for the Elegoo Smart Robot Car Kit V4.0 to allow for 2D position and orientation tracking using a Kalman filter.
It also supports a system of movement commands through an API available on the ESP32's network.
The API allows users to direct the car to a series of 2D Cartesian coordinates, with the starting position as 0,0.
Note that the starting orientation of the car is defined to be the Y axis and a 90 degree offset from that is the X axis, contrary to general robotics conventions.
Starting heading is defined to be 0.

This project is a modification of the original Elegoo software shipped with the car to add these capabilities.
The original source can be found at: https://www.elegoo.com/blogs/arduino-projects/elegoo-smart-robot-car-kit-v4-0-tutorial

The project supports only the version of the car containing the Arduino Uno, MPU 6050 intertial measurement unit, TB6612 motors, and ESP32-S3, though other hardware configurations of the Smart Robot Car V4.0 do exist.

## Installation
These instructions assume that you already have an assembled Elegoo Smart Robot Car Kit V4.0 with the hardware described above.

1. Download this project as a .zip file using the code dropdown menu or other means.
2. Unpack the files to some desireable location.
3. Download and set up the Arduino IDE for your operating system from https://www.arduino.cc/en/software/.
4. Open the project in the Arduino IDE. This can be done by opening the ElegooRobotCar.ino file. Other files in the project will be opened as well.
5. Select Arduino Uno from the dropdown menu at the top left or connect the car's Uno to your PC by USB to select it automatically.
6. Click the upload button to compile and upload the project into the car. 
The project is now installed and the car will run the project's code once turned on.

## Usage
Once the car is on, it will listen for move or turn commands sent by HTTP over its API. 

## System Architecture

## Software Configuration 

## Purposes of Files

## Kalman Filter

## Movement Handling

## API

## Known Limitations
