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

The user GUI, which sends these commands, can be found under the Pathing-Front-End repo in this project.

Commands can also be sent via curl with commands such as
```
curl -X POST http://192.168.4.1/api/path \
  -H "Content-Type: application/json" \
  -d '{"cmd":"move","d": .01,"dir":1}'
  
curl -X POST http://192.168.4.1/api/path \
  -H "Content-Type: application/json" \
  -d '{"cmd":"turn","a":90}'
  
curl http://192.168.4.1/api/pose 
```

In a move command, "d" is the distance in meters, and "dir" is 1 for forward and 0 for backwards.

In a turn command, "a" is the desired direction to face.

The car will execute commands until no more remain in queue, with a maximum number of stored commands at 5. 
Turn commands and move commands both take up a single space in the queue.

There are also built in test functions: 
- Application_FunctionSet.testBasicRoute() runs a basic 5 command route.
- Application_FunctionSet.testMoves() moves the car straight for 3 meters.
- Application_FunctionSet.testTurns() turns the car right 179 degrees and then back left to face a 1 degree heading.

These can be inserted to the setup() function in the ino file to insert their relevant commands into the queue.

## System Architecture
 Include the diagram here

## Software Configuration
A few parts of the software can be reconfigured to account for differing hardware.

STANDARDSPEED in ApplicationFunctionSet_xx0.cpp can be altered to either increase or decrease the speed of the car.

### PID system
This project features a Proportional-Integral-Derivative controller system to keep the car moving in a straight line.

A STANDARDKP value is defined in ApplicationFunctionSet_xx0.cpp which controls how aggressively the controller attempts to correct course when drifting.

By default, this value is set to 12, but setting a higher value makes the system quicker to correct.

### Kalman Filter
The kalman filter works by comparing integrated acceleration to a dead reckoning model. Each method has an associated noise value.

These are accelNoise, a variable, and RECKONINGNOISE, a compiler defined value. In either case, a value closer to 0 places more trust in that method of prediction, and a higher value places less trust.

The dead reckoning method also relies on a linear approximation of the speed value given by the internal speed value passed to the filter. This is generally STANDARDSPEED in ApplicationFunctionSet_xx0.cpp.

This function can be altered in PositionTracking::internalSpeedToMPS as desired to match a given car, if the actual speed differs.

## Purposes of Files

## Kalman Filter

## Movement Handling

## API

## Known Limitations
