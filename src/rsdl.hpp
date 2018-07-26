#ifndef __RSDL_H__
#define __RSDL_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
void Delay(int milis);
class RGB {
public:
  RGB(int r, int g, int b) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
      throw "Invalid RGB color!";
    red = r;
    green = g;
    blue = b;
  }
  Uint8 red;
  Uint8 green;
  Uint8 blue;
};

const RGB WHITE(255, 255, 255);
const RGB YELLOW(255, 255, 0);
const RGB MAGENTA(255, 0, 255);
const RGB RED(255, 0, 0);
const RGB CYAN(0, 255, 255);
const RGB GREEN(0, 255, 0);
const RGB BLUE(0, 0, 255);
const RGB BLACK(0, 0, 0);

enum EventType {
  NA,
  LCLICK,
  RCLICK,
  LRELEASE,
  RRELEASE,
  MMOTION,
  KEY_PRESS,
  QUIT
};

class Event {
public:
  Event();
  Event(SDL_Event _sdlEvent);
  EventType type();
  int mouseX();
  int mouseY();
  int relativeMouseX();
  int relativeMouseY();
  char pressedKey();

private:
  SDL_Event sdlEvent;
};

class Window {
public:
  Window(int width = 800, int heigth = 400, std::string title = "RSDL");
  ~Window();
  Window &operator=(const Window &);
  void draw_bmp(std::string filename, int x, int y, int width, int heigth);
  void draw_png(std::string filename, int x, int y, int width, int heigth);
  void draw_png(std::string filename, int x, int y, int width, int heigth,
                int angle);
  void show_text(std::string input, int x = 0, int y = 0, RGB color = WHITE,
                 std::string font_addr = "FreeSans.ttf", int size = 24);
  void draw_bg(std::string filename, int x = 0, int y = 0);
  void update_screen();
  void fill_rect(int x, int y, int width, int heigth, RGB color = WHITE);
  void draw_line(int x1, int y1, int x2, int y2, RGB color = WHITE);
  void draw_point(int x, int y, RGB color = WHITE);
  void draw_rect(int x, int y, int width, int heigth, RGB color = WHITE);
  void clear();
  Event pollForEvent();

private:
  int width;
  int heigth;
  SDL_Window *win;
  SDL_Renderer *renderer;
  std::map<std::string, SDL_Texture *> texture_cache;
  std::map<std::string, TTF_Font *> fonts_cache;
  void set_color(RGB color);
  void dump_err() { std::cerr << SDL_GetError() << '\n'; }
  void init();
};

#endif
