#include "textInput.hpp"
#include <cstdlib>

TextInputWindow::TextInputWindow(int _width, int _height)
    : width(_width), height(_height),
      img_background("example/assets/background.jpg"),
      inputString((_width - text_input_width) / 2,
                  (_height - text_input_height) / 2, 30) {
  win = new Window(Point(width, height), "RSDL Tutorial");
  enterPressed = false;
}

void TextInputWindow::display() {
  while (!enterPressed) {
    getAndProcessInput();
    draw();
    delay(TICK_DURATION);
  }
}

string TextInputWindow::getText() { return inputString.getString(); }

void TextInputWindow::draw() {
  win->clear();
  win->draw_img(img_background);
  win->fill_rect(
      Point((width - text_input_width) / 2, (height - text_input_height) / 2),
      Point(text_input_width, text_input_height), BLACK);
  inputString.drawString(win);
  win->update_screen();
}

void TextInputWindow::getAndProcessInput() {
  lastEvent = win->poll_for_event();
  processLastEvent();
}

void TextInputWindow::processLastEvent() {
  if (lastEvent.type() == QUIT)
    exit(0);
  if (lastEvent.type() == KEY_PRESS) {
    if (lastEvent.pressedKey() == BACK_SPACE)
      inputString.eraseLastChar();
    else if (lastEvent.pressedKey() == RETURN)
      enterPressed = true;
    else
      inputString.addChar(lastEvent.pressedKey());
  }
}
