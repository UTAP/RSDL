#include "../src/rsdl.hpp"
#include <cstdlib>
#include <vector>
#include <cmath>
#include <thread>
#include <string>

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 1000
#define BACK_SPACE 8
#define RETURN 13

using namespace std;

string getCursor(int& age)
{
  age++;
  if(age > 100)
    age = 0;
  return age > 50 ? "|" : "";
}

string getInput(window& win){
	string inputString = "";
	const int tickDuration = 10;
	int age = 0;
	while(true) {
    win.clear();
		win.show_text("You: "+inputString+getCursor(age), 100, 300, WHITE, "examples/assets/FreeSans.ttf",100);
		Event e = win.pollForEvent();
		if(e.type() == KEY_PRESS)
		{
			if(e.pressedKey() == BACK_SPACE)
				inputString.erase(inputString.size()-1);
			else if(e.pressedKey() == RETURN)
					break;
			else
					inputString+= e.pressedKey();
		}
		win.update_screen();
		Delay(tickDuration);
	}
	return inputString;
}


int main() {
	window win(WINDOW_WIDTH, WINDOW_HEIGHT);
	cout<<getInput(win)<<endl;
}
