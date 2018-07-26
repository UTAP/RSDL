#include "myString.hpp"

MyString::MyString(int _x, int _y, int _fontSize)
    : x(_x), y(_y), fontSize(_fontSize) {}

string MyString::textToDisplay() { return "  Your name: " + inputString; }

void MyString::eraseLastChar() {
  if (inputString.size() > 0)
    inputString.erase(inputString.size() - 1);
}

void MyString::addChar(char c) {
  if (inputString.size() < MAX_STRING_LENGTH)
    inputString += c;
}

void MyString::drawString(Window *win) {
  win->show_text(textToDisplay(), x, y, WHITE, FONT_FREESANS, fontSize);
}

string MyString::getString() { return inputString; }
