#ifndef CUBE_H
#define CUBE_H

enum CubeMovement {
    L,
    L_PRIME,
    R,
    R_PRIME,
    U,
    U_PRIME,
    D,
    D_PRIME,
    F,
    F_PRIME,
    B,
    B_PRIME
};

enum HandPosition { RIGHT, LEFT, MIDDLE };

class Cube {
  public:
    Cube();
    void setup(int leftHandPin, int rightHandPin, int leftGripperPin,
               int rightGripperPin);
    void idle();
    void moveCube(CubeMovement move);
    void moveLeftHand(HandPosition pos);
    void moveRightHand(HandPosition pos);
    void moveLeftGripper(bool open);
    void moveRightGripper(bool open);

  private:
    int leftHandPin;
    int rightHandPin;
    int leftGripperPin;
    int rightGripperPin;

    HandPosition currentLeftHandPosition;
    HandPosition currentRightHandPosition;
    bool leftGripperOpened;
    bool rightGripperOpened;
};

#endif