/*
 * @Author: ELEGOO
 * @Date: 2019-10-22 11:59:09
 * @LastEditTime: 2020-12-18 14:14:35
 * @LastEditors: Changhua
 * @Description: Smart Robot Car V4.0
 * @FilePath: 
 */
#include <avr/wdt.h>
#include "ApplicationFunctionSet_xxx0.h"
#include"scalarPosition.h"
#include"scalarPosition.h"

bool onGround;
void setup()
{
  // put your setup code here, to run once:
  Application_FunctionSet.ApplicationFunctionSet_Init(); // here i start the pos tracking moduel
  wdt_enable(WDTO_2S);
}
  int directionRecord = 0;

  // added by Alan
  PositionTracking kalmanFilter = PositionTracking(); // leaving all default values
  // values later used by Kalman filter
  float heading = 0, accel = 0, voltage = 0, dummy = 0; // dummy passed as a garbage value where needed
  int dt = 0;
  unsigned long clockTime = millis();

void loop()
{
  wdt_reset();
  Application_FunctionSet.ApplicationFunctionSet_SensorDataUpdate();
  Application_FunctionSet.ApplicationFunctionSet_KeyCommand();
  // Temporarily disable non-essential features to save memory
  Application_FunctionSet.ApplicationFunctionSet_RGB();
  // Application_FunctionSet.ApplicationFunctionSet_Follow();
  // Application_FunctionSet.ApplicationFunctionSet_Obstacle();
  // Application_FunctionSet.ApplicationFunctionSet_Tracking();
  // Application_FunctionSet.ApplicationFunctionSet_Rocker();
  // Application_FunctionSet.ApplicationFunctionSet_Standby();
  // Application_FunctionSet.ApplicationFunctionSet_IRrecv();
  // Application_FunctionSet.ApplicationFunctionSet_SerialPortDataAnalysis();
//by lucas - Keep position tracking functionality
 onGround = Application_FunctionSet.ApplicationFunctionSet_SmartRobotCarLeaveTheGround();

    Application_FunctionSet.ApplicationFunctionSet_PositionTracking();
    if (onGround) {

      // by Alan
      // find heading, acceleration, dt, and voltage
      Application_FunctionSet.AppMPU6050getdata.MPU6050_dveGetEulerAngles(&heading); // set heading
      accelgyro.getMotion6(&accel, &dummy, &dummy, &dummy, &dummy, &dummy) // set accel, reading x axis only
      voltage = Application_FunctionSet.AppVoltage.DeviceDriverSet_Voltage_getAnalogue(); // set voltage
      unsigned long currTime = millis();
      dt = currTime - clockTime;
      clockTime = currTime;

      kalmanFilter.updatePosition(heading, accel, dt, voltage);
      // end of Alan's block
      
      Application_FunctionSet.ApplicationFunctionSet_SmartRobotCarLinearMotionControl(Forward, directionRecord, 50, 12, 150);
      directionRecord = 1;
      Application_FunctionSet.ReportPosition();
    }
    else {
      Application_FunctionSet.ApplicationFunctionSet_SmartRobotCarLinearMotionControl(stop_it, 0, 0, 1, 150); // Stop the car if it's not on the ground
      directionRecord = 0;
      return;
    }
  // Temporarily disable command processing to save memory
  // Application_FunctionSet.CMD_ServoControl_xxx0();
  // Application_FunctionSet.CMD_MotorControl_xxx0();
  // Application_FunctionSet.CMD_CarControlTimeLimit_xxx0();
  // Application_FunctionSet.CMD_CarControlNoTimeLimit_xxx0();
  // Application_FunctionSet.CMD_MotorControlSpeed_xxx0();
  // Application_FunctionSet.CMD_LightingControlTimeLimit_xxx0();
  // Application_FunctionSet.CMD_LightingControlNoTimeLimit_xxx0();
  // Application_FunctionSet.CMD_ClearAllFunctions_xxx0();
}
