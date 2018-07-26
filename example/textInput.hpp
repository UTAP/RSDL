#include "../src/rsdl.hpp"
#include "myString.hpp"
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGTH 480
#define WINDOW_TITLE "RSDL Tutorial"

#define BACK_SPACE 8
#define RETURN 13
#define TICK_DURATION 10

#define IMG_SQUARE "example/assets/square.png"
#define IMG_BACKGROUND "example/assets/background.jpeg"

#define TEXT_INPUT_X 100
#define TEXT_INPUT_Y 100
#define TEXT_INPUT_WIDTH 400
#define TEXT_INPUT_HEIGHT 50

class TextInputWindow {
private:
  Window *win;
  Event lastEvent;
  MyString inputString;
  bool enterPressed;
  void draw();
  void getAndProcessInput();
  void processLastEvent();

public:
  TextInputWindow();
  void display();
  string getText();
};
