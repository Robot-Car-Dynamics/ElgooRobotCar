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
  Application_FunctionSet.ApplicationFunctionSet_Init(); 
  Application_FunctionSet.testBasicRoute(); // moves 100 cm forward
  
  uint8_t starttime = millis(); // initialize clock

}
uint8_t now;
PositionTracking kalmanFilter = PositionTracking();
  
void loop()
{

  wdt_reset();
  Application_FunctionSet.ApplicationFunctionSet_SensorDataUpdate();
  Application_FunctionSet.ApplicationFunctionSet_SerialPortDataAnalysis(kalmanFilter);

  onGround = Application_FunctionSet.ApplicationFunctionSet_SmartRobotCarLeaveTheGround();
  if (Application_FunctionSet.numPathActions() > 0 ) {
    static unsigned long lastActionTime = 0;
    unsigned long currentTime = millis();
    if (currentTime - lastActionTime >= 1000) { // Check if 1 second has passed
        Application_FunctionSet.handleAction(kalmanFilter);
        lastActionTime = currentTime; // Update the last action time
    }
    // will not return until action in front of queue is complete
    // above call handles updating filter
  } else {

  }

}
