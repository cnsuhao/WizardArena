#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include "../gameobjects/panel.hpp"
#include "../gameobjects/text.hpp"
#include "../includes.hpp"
#include "../scene.hpp"

class MessageBox : public Scene {
 public:
  /** MessageBox constructor that takes in a message and a time in milliseconds
      @param message Message string to be displayed
      @param time Time to display message in milliseconds
   */
  MessageBox(string message, uint time);
  ~MessageBox();
  void Update();

 private:
  uint endTime;
};

#endif  // MESSAGEBOX_H
