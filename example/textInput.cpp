#include "textInput.hpp"
#include <cstdlib>

TextInputWindow::TextInputWindow() : inputString(100, 100, 30) {
  win = new Window(WINDOW_WIDTH, WINDOW_HEIGTH, "Text Input");
  enterPressed = false;
}

void TextInputWindow::display() {
  while (!enterPressed) {
    getAndProcessInput();
    draw();
    Delay(TICK_DURATION);
  }
}

string TextInputWindow::getText() { return inputString.getString(); }

void TextInputWindow::draw() {
  win->clear();
  win->draw_bg(IMG_BACKGROUND, 0, 0);
  win->fill_rect(TEXT_INPUT_X, TEXT_INPUT_Y, TEXT_INPUT_WIDTH,
                 TEXT_INPUT_HEIGHT, RED);
  inputString.drawString(win);
  win->update_screen();
}

void TextInputWindow::getAndProcessInput() {
  lastEvent = win->pollForEvent();
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
