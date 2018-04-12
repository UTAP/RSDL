#include "../src/rsdl.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define DELAY_DURATION 5000
#define BACKGROUND_FILE "examples/assets/background.jpeg"

int main()
{
  Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Welcome");
  window.draw_bg(BACKGROUND_FILE);
  window.update_screen();
  Delay(DELAY_DURATION);
}
