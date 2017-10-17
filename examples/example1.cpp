#include "../src/rsdl.hpp"

#include <fstream>

using namespace std;

class A{
public:
  int x;
  A(int _x){
    x = _x;
  }
};

class B{
public:
  A* a;
  void setA(A* _a){
    a = _a;
  }
};
int main(){
    window win(800, 600);
    ofstream file;
    int x = 0,y = 0;
    int tx = 0, ty = 0;
    int sgn = 1;
    while(true){
        Event e = win.pollForEvent();
        if(e.type() == LCLICK)
        {
          cout<<e.mouseX()<<endl;
        }
        tx++;
        x = tx;
        y = ty;
        win.draw_bg("./geo.jpg", 0, 0);
        win.draw_png("./drone.png", x, y, 100, 100);
        win.update_screen();
        Delay(50);
    }
}
