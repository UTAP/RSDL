#ifndef __RSDL_H__
#define __RSDL_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

struct Point {
  Point(int x, int y);
  int x;
  int y;
  Point operator+(const Point) const;
  Point operator-(const Point) const;
  Point operator*(const int)const;
  Point operator/(const int) const;
  Point &operator+=(const Point);
  Point &operator-=(const Point);
  Point &operator*=(const int);
  Point &operator/=(const int);
  operator SDL_Point();
};
Point operator*(const int, const Point);
std::ostream& operator<<(std::ostream& stream, const Point);

struct RGB {
  RGB(int r, int g, int b);
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
  EventType get_type() const;
  Point get_mouse_position() const;
  Point get_relative_mouse_position() const;
  char get_pressed_key() const;

protected:
  SDL_Event sdlEvent;
};

class Window {
public:
  Window(Point size = Point(640, 480), std::string title = "RSDL");
  ~Window();
  Window &operator=(const Window &);
  void draw_img(std::string filename, Point src = Point(0, 0),
                Point size = Point(0, 0), double angle = 0,
                bool flip_horizontal = false, bool flip_vertical = false);
  void show_text(std::string input, Point src, RGB color = WHITE,
                 std::string font_addr = "FreeSans.ttf", int size = 24);
  void update_screen();
  void draw_line(Point src, Point dst, RGB color = WHITE);
  void draw_point(Point, RGB color = WHITE);
  void draw_rect(Point src, Point size, RGB color = WHITE,
                 unsigned int line_width = 4);
  void fill_rect(Point src, Point size, RGB color = WHITE);
  void clear();
  Event poll_for_event();
  void dump_err();

protected:
  Point size;
  SDL_Window *win;
  SDL_Renderer *renderer;
  std::map<std::string, SDL_Texture *> texture_cache;
  std::map<std::string, TTF_Font *> fonts_cache;
  void set_color(RGB color);
  void init();
};

void delay(int milis);
Point get_current_mouse_position();

#endif
