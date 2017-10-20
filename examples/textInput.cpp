#include "../src/rsdl.hpp"
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BACK_SPACE 8
#define RETURN 13

using namespace std;

string getCursor(int& age)
{
  age++;
  if(age > 50)
    age = 0;
  return age > 25 ? "|" : "";
}

struct Square{
  int x,y;
  int v_x,v_y;
  int width,height;
};

bool collision_with_horizontal_border(Square square)
{
  return square.y<= 0 || square.y > WINDOW_HEIGHT-square.height;
}

bool collision_with_vertical_border(Square square)
{
  return square.x <= 0 || square.x > WINDOW_WIDTH-square.width;
}


void move_square(Square& square){
  square.x += square.v_x;
  square.y += square.v_y;
  if(collision_with_horizontal_border(square))
    square.v_y = -square.v_y;
  if(collision_with_vertical_border(square))
    square.v_x = -square.v_x;
}

void draw_in_window(window& win, string inputStringWithCursor, Square square)
{
  win.draw_bg("examples/assets/background.jpg",0,0);
  win.draw_png("examples/assets/square.png", square.x, square.y, square.width, square.height,45);
  win.fill_rect(100, 100, 400 - 1, 50 - 1, RED);
  win.show_text(inputStringWithCursor, 100, 100, WHITE, "examples/assets/FreeSans.ttf",30);
  win.update_screen();
  win.clear();
}

void erase_last_char(string& inputString)
{
  if(inputString.size() > 0)
      inputString.erase(inputString.size()-1);
}

void add_char(string& inputString, char c)
{
  if(inputString.size() < 10)
    inputString+= c;
}

string get_input(window& win){
	string inputString = "";
	const int tickDuration = 10;
	int age = 0;
  Square square;
  square.x = 50;
  square.y = 60;
  square.v_x = 1;
  square.v_y = -1;
  square.width = 40;
  square.height = 40;
	while(true) {
    Event event = win.pollForEvent();
		if(event.type() == KEY_PRESS)
		{
			if(event.pressedKey() == BACK_SPACE)
        erase_last_char(inputString);
			else if(event.pressedKey() == RETURN)
					break;
			else
        add_char(inputString, event.pressedKey());
		}
    move_square(square);
    draw_in_window(win, "  Your name: "+inputString+getCursor(age), square);
		Delay(tickDuration);
	}
	return inputString;
}


int main() {
  window win(WINDOW_WIDTH, WINDOW_HEIGHT,"RSDL");
	cout<<get_input(win)<<endl;
}
