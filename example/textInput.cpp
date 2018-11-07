#include "textInput.hpp"
#include <cstdlib>

TextInputWindow::TextInputWindow(int _width, int _height)
    : width(_width), height(_height), img_background("example/assets/ut.png"),
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
  RGB input_back_color(30, 30, 30);
  win->fill_circle(Point((width - text_input_width) / 2, height / 2),
                   text_input_height / 2, input_back_color);
  win->fill_circle(Point((width + text_input_width) / 2, height / 2),
                   text_input_height / 2, input_back_color);
  win->fill_rect(
      Point((width - text_input_width) / 2, (height - text_input_height) / 2),
      Point(text_input_width, text_input_height), input_back_color);
  inputString.drawString(win);
  win->update_screen();
}

void TextInputWindow::getAndProcessInput() {
  lastEvent = win->poll_for_event();
  processLastEvent();
}

void TextInputWindow::processLastEvent() {
  if (lastEvent.get_type() == QUIT)
    exit(0);
  if (lastEvent.get_type() == KEY_PRESS) {
    if (lastEvent.get_pressed_key() == BACK_SPACE)
      inputString.eraseLastChar();
    else if (lastEvent.get_pressed_key() == RETURN)
      enterPressed = true;
    else
      inputString.addChar(lastEvent.get_pressed_key());
  }
}
