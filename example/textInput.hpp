#include "../src/rsdl.hpp"
#include "myString.hpp"
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

#define BACK_SPACE 8
#define RETURN 13
#define TICK_DURATION 10

class TextInputWindow {
private:
  rsdl::Window *win;
  rsdl::Event lastEvent;
  MyString inputString;
  int width;
  int height;
  static const int text_input_width = 400;
  static const int text_input_height = 50;
  const string img_background;
  bool enterPressed;
  void draw();
  void getAndProcessInput();
  void processLastEvent();

public:
  TextInputWindow(int width = 640, int height = 480);
  void display();
  string getText();
};
