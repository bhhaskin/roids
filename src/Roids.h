#pragma once
#include <string>
#include <stack>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class Roids {
public:
  Roids();
  ~Roids();
  void play();

private:
  ALLEGRO_DISPLAY* display;
  ALLEGRO_EVENT_QUEUE* main_queue;
  ALLEGRO_EVENT_QUEUE* input_queue;
  ALLEGRO_FONT* font12;
  ALLEGRO_FONT* font18;
  ALLEGRO_TIMER* timer;
  double targetFPS;
  int screenWidth;
  int screenHeight;
  const char* fontName;
  bool showFPS;

};
