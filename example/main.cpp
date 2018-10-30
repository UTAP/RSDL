#include "textInput.hpp"
#include <iostream>

using namespace std;

#define window_height 640
#define WINDOW_height 480

int main() {
  TextInputWindow textInputWindow;
  textInputWindow.display();
  cout << textInputWindow.getText() << endl;
}
