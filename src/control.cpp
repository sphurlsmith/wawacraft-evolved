#include "libs.h"
#include "control.h"

void key_callback_execute_press(GLFWwindow* window, key_callback* key, int argc, char** argv)
{
  if(glfwGetKey(window, (key->keycode))==GLFW_PRESS){
    (*(key->callback))(argc, argv);
  }
}

void key_callback_execute_release(GLFWwindow* window, key_callback* key, int argc, char** argv)
{
  if(glfwGetKey(window, (key->keycode))==GLFW_RELEASE){
    (*(key->callback))(argc, argv);
  }
}

void key_callbacks_execute_press(GLFWwindow* window, key_callback* keys, int elements, int argc, char** argv)
{
  for(int x=0; x<elements; x++){
    key_callback_execute_press(window,(keys+x), argc, argv);
  }
}

void key_callbacks_execute_release(GLFWwindow* window, key_callback* keys, int elements, int argc, char** argv)
{
  for(int x=0; x<elements; x++){
    key_callback_execute_release(window, (keys+x), argc, argv);
  }
}
