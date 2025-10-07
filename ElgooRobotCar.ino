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
bool onGround;
void setup()
{
  // put your setup code here, to run once:
  Application_FunctionSet.ApplicationFunctionSet_Init();
  wdt_enable(WDTO_2S);
}

void loop()
{
  //put your main code here, to run repeatedly :
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
      Application_FunctionSet.ApplicationFunctionSet_SmartRobotCarLinearMotionControl(Forward, 1, 50, 1, 150);
      Application_FunctionSet.ReportPosition();
    }
    else {
      Application_FunctionSet.ApplicationFunctionSet_SmartRobotCarLinearMotionControl(stop_it, 0, 0, 1, 150); // Stop the car if it's not on the ground
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
