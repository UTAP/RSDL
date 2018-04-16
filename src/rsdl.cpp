#include <iostream>
#include <sstream>
#include "rsdl.hpp"

using namespace std;

void Delay(int milis)
{
  SDL_Delay(milis);
}

Event::Event(){
  
}

Event::Event(SDL_Event _sdlEvent)
{
	sdlEvent = _sdlEvent;
}

EventType Event::type()
{
	SDL_Event e = sdlEvent;
  try{
    if (e.type == SDL_QUIT)
  		return QUIT;
  	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
  		return LCLICK;
  	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT)
  		return RCLICK;
  	if (e.type == SDL_KEYDOWN )
  		return KEY_PRESS;
  	if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
  		return LRELEASE;
  	if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT)
  		return RRELEASE;
    if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT)
  		return RRELEASE;
    if (e.type == SDL_MOUSEMOTION)
      return MMOTION;
  }catch(...){
    return NA;
  }
	return NA;
}

int Event::mouseX()
{
  if(type() == KEY_PRESS || type() == QUIT || type() == NA)
    return -1;
  if(type() == MMOTION)
    return sdlEvent.motion.x;
  else
	  return sdlEvent.button.x;
}

int Event::mouseY()
{
  if(type() == KEY_PRESS || type() == QUIT || type() == NA)
    return -1;
  if(type() == MMOTION)
    return sdlEvent.motion.y;
  else
	  return sdlEvent.button.y;
}

int Event::relativeMouseX()
{
  if(type() != MMOTION)
    return 0;
  else
	 return sdlEvent.motion.xrel;
}

int Event::relativeMouseY()
{
  if(type() != MMOTION)
    return 0;
  else
	  return sdlEvent.motion.yrel;
}

char Event::pressedKey()
{
  if(type() != KEY_PRESS)
    return -1;
	return sdlEvent.key.keysym.sym;
}

void Window::init(){
    if (SDL_Init(0) < 0)
		throw "SDL Init Fail";
	int flags = (SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	if (SDL_WasInit(flags) != 0)
		throw string("SDL_WasInit Failed ") + SDL_GetError();
	if (SDL_InitSubSystem(flags) < 0)
        throw string("SDL_InitSubSystem Failed ") + SDL_GetError();
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw "IMG_Init Fail";
	if (TTF_Init() == -1)
		throw "TTF_Init Fail";
}

Window::Window(int width, int heigth, std::string title):width(width),heigth(heigth){
    init();
    SDL_CreateWindowAndRenderer(width,heigth,0,&win,&renderer);
	if (win == NULL || renderer == NULL)
		throw string("Window could not be created! SDL_Error: ") + SDL_GetError();
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetWindowTitle(win, title.c_str());
    update_screen();
}

Window::~Window(){
	SDL_DestroyWindow(win);
    if (TTF_WasInit())
        TTF_Quit();
    SDL_Quit();
}

Window& Window::operator=(const Window& window){
  width = window.width;
  heigth = window.heigth;
  return *this;
}

void Window::show_text(string input, int x, int y, RGB color, string font_addr, int size){
    SDL_Color textColor = { color.red, color.green, color.blue,};
    stringstream ss;
    ss << size;
    TTF_Font* font = fonts_cache[font_addr+":"+ss.str()];
    if(font == NULL){
        font = TTF_OpenFont(font_addr.c_str(), size);
        fonts_cache[font_addr+":"+ss.str()] = font;
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, input.c_str(), textColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
    SDL_DestroyTexture(text);
}

void Window::set_color(RGB color){
	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 255);
}

void Window::clear(){
  SDL_SetRenderDrawColor(renderer,0,0,0,0);
  SDL_RenderClear(renderer);
}

void Window::draw_bmp(string filename, int x, int y, int width, int heigth){
	SDL_Texture* res = texture_cache[filename];
	if (res == NULL){
		SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
        res = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
		texture_cache[filename]=res;
	}
	SDL_Rect r = {x, y, width, heigth};
    SDL_RenderCopy(renderer, res, NULL, &r);
}

void Window::draw_png(string filename, int x, int y, int width, int heigth){
	SDL_Texture* res = texture_cache[filename];
	if (res == NULL){
		res = IMG_LoadTexture(renderer, filename.c_str());
		texture_cache[filename]=res;
	}
    SDL_Rect r = {x, y, width, heigth};
    SDL_RenderCopy(renderer, res, NULL, &r);
}

void Window::draw_png(string filename, int x, int y, int width, int heigth,int angle){
	SDL_Texture* res = texture_cache[filename];
	if (res == NULL){
		res = IMG_LoadTexture(renderer, filename.c_str());
		texture_cache[filename]=res;
	}
    SDL_Rect r = {x, y, width, heigth};
    SDL_RenderCopyEx( renderer, res, NULL, &r, angle, NULL, SDL_FLIP_NONE );
}

void Window::draw_bg(string filename, int x, int y){
	SDL_Texture* res = texture_cache[filename];
	if (res == NULL){
		res = IMG_LoadTexture(renderer, filename.c_str());
		texture_cache[filename]=res;
	}
    SDL_Rect src = {0, 0, width, heigth};
    SDL_Rect dst = {x, y, width, heigth};
    SDL_RenderCopy(renderer, res, &dst, &src);
}

void Window::update_screen(){
	SDL_RenderPresent(renderer);
}

void Window::fill_rect(int x, int y, int width, int heigth, RGB color){
    set_color(color);
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = width;
    r.h = heigth;
    SDL_RenderFillRect( renderer, &r );
}

void Window::draw_line(int x1, int y1, int x2, int y2, RGB color){
    set_color(color);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Window::draw_point(int x, int y, RGB color){
    set_color(color);
    SDL_RenderDrawPoint(renderer, x, y);
}

void Window::draw_rect(int x, int y, int width, int heigth, RGB color){
    for (size_t i = 0; i < 4; i++) {
      draw_line(x+i,y+i,x+width-i,y+i,color);
      draw_line(x+i,y+i,x+i,y+heigth-i,color);
      draw_line(x+i,y+heigth-i,x+width-i,y+heigth-i,color);
      draw_line(x+width-i,y+i,x+width-i,y+heigth-i,color);
    }
}

Event Window::pollForEvent(){
  SDL_Event event;
  while(SDL_PollEvent(&event) != 0){
    Event e(event);
    if(e.type() != 0)
      return e;
  }
  return event;
}
