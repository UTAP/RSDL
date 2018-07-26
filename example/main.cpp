#include "textInput.hpp"
#include <iostream>

using namespace std;

int main() {
  TextInputWindow textInputWindow;
  textInputWindow.display();
  cout << textInputWindow.getText() << endl;
}
