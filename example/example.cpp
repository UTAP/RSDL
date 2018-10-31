#include "../src/rsdl.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

struct Person {
  string name;
  bool flipped;
  Point pos;
  Point size;
  Person(string _name, bool _flipped, Point _pos, Point _size = Point(225, 400))
      : name(_name), flipped(_flipped), pos(_pos), size(_size) {
    pos -= size / 2;
  }
};

bool process_event(const Event &event, vector<Person> &persons) {
  static const string persons_names[] = {"Ghune", "Spartiate", "Athenian"};
  switch (event.get_type()) {
  case QUIT:
    return false;
  case LCLICK:
    persons.push_back(Person(persons_names[rand() % 3], rand() % 2,
                             event.get_mouse_position()));
    break;
  case KEY_PRESS:
    if (event.get_pressed_key() == 'q')
      return false;
  default:;
  }
  return true;
}

void render(Window &win, const vector<Person> &persons) {
  win.clear();
  win.draw_img("example/assets/back.png");
  for (vector<Person>::const_iterator person = persons.begin();
       person != persons.end(); person++)
    win.draw_img("example/assets/" + person->name + ".png", person->pos,
                 person->size, 0, person->flipped);
  win.draw_img("example/assets/cursor.png",
               get_current_mouse_position() - Point(15, 15), Point(30, 30));
  win.update_screen();
  delay(50);
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  Window win = Window();
  vector<Person> persons;

  while (process_event(win.poll_for_event(), persons)) {
    render(win, persons);
  }

  return 0;
}
