#ifndef CONTROL_H
#define CONTROL_H

#include "libs.h"

// this is a header that will provide utilities for the creation
// and maintaining of the control of a window!!
// I.E. Keypresses and Mouse input galore!!

namespace nswincon{
  int getKeyStatus(GLFWwindow* handle, int key);

  void getCursorPosition(GLFWwindow* handle, double* x, double* y);
  void setCursorMode(GLFWwindow* handle, bool state);
}

#endif
