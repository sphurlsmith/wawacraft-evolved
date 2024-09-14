#include "libs.h"
#include "control.h"

int nswincon::getKeyStatus(GLFWwindow* handle, int key){
  return glfwGetKey(handle, key);
}

void getCursorPosition(GLFWwindow* handle, double& x, double& y){
  glfwGetCursorPos(handle, x, y);
}

void setCursorMode(GLFWwindow* handle, bool state){
  if(state){glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);}
  else{glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);}
}
