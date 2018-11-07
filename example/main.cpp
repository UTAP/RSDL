#include "textInput.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

#define window_height 640
#define WINDOW_height 480

int main() {
  try {
    TextInputWindow textInputWindow;
    textInputWindow.display();
    cout << textInputWindow.getText() << endl;
  } catch (string exception) {
    cerr << "EXCEPTION: " << exception << endl;
    exit(1);
  }

  return 0;
}
