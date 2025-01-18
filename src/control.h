#ifndef CONTROL_H
#define CONTROL_H

#include "libs.h"

struct key_callback{
  int keycode;
  void (*callback)(int argc, char** argv);
};

void key_callback_execute_press(GLFWwindow* window, key_callback* key, int argc, char** argv);
void key_callback_execute_release(GLFWwindow* window, key_callback* key, int argc, char** argv);

void key_callbacks_execute_press(GLFWwindow* window, key_callback* keys, int elements, int argc, char** argv);
void key_callbacks_execute_release(GLFWwindow* window, key_callback* keys, int elements, int argc, char** argv);

#endif
