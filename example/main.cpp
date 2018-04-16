#include <iostream>
#include "textInput.hpp"

using namespace std;

int main()
{
  TextInputWindow textInputWindow;
  textInputWindow.display();
  cout<<textInputWindow.getText()<<endl;
}
