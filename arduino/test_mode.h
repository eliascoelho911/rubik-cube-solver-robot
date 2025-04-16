#ifndef TEST_MODE_H
#define TEST_MODE_H

#include "robot.h"
#include "serial.h"

class TestMode {
  public:
    TestMode(Robot &robot);
    void run();

  private:
    Robot &_robot;
    void showMenu();
    void handleCubeMovement();
    void handleGripperMovement();
    void handleHandMovement();
};

#endif