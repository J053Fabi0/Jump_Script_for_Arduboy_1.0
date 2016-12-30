#include <Arduboy2.h>

Arduboy2 arduboy;

const int XTAM = 128; //El tamaño de la pantalla
const int YTAM = 64;
const int RADIO = 7;
const float GRAV = 0.2;

float x = XTAM/2 - RADIO/2;
float y = YTAM/2 - RADIO/2;
float dx = 0; //Velocidad (lo que se le suma a x por frame)
float dy = 2;

void setup() {
  // put your setup code here, to run once:
  arduboy.boot();
  arduboy.blank();
  arduboy.flashlight();
  arduboy.audio.begin();
}

void loop() {
  arduboy.clear();

  arduboy.drawFastHLine(0, 63, 128, WHITE);
  
  arduboy.drawCircle (x, y, RADIO, WHITE);
  x += dx;
  y += dy;
  if(x > XTAM - RADIO -2 || x < RADIO -2){
    dx = -dx;
  }
  if(y > YTAM - RADIO -2 || y < RADIO -2){
    dy = -dy;
    dy -= GRAV;
  }

  dy += GRAV;

  delay(35);
  
  arduboy.display();
}
