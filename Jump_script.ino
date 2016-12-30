#include <Arduboy2.h>

Arduboy2 arduboy;

const int XTAM = 128; //El tamaño de la pantalla
const int YTAM = 64;
const int RADIO = 7;
const float GRAV = 0.2;

float x = XTAM/2 - RADIO/2;
float y = YTAM/2 - RADIO/2;
float dx = 0; //Velocidad (lo que se le suma a x por frame)
float dy = 0;

bool onGround = false;

void setup() {
  arduboy.boot();
  arduboy.blank();
  arduboy.flashlight();
  arduboy.audio.begin();
  arduboy.setFrameRate(30);
}

void startJump(){
  if(onGround){
    dy = -3;
    onGround = false;
    y = YTAM - RADIO -2;
  }
}

void endJump(){
  if(dy < -0.2){
    dy = -0.2;
  }
}

void update(){
  dy += GRAV;
  x += dx;
  y += dy;

  if(y > YTAM - RADIO -2){
    onGround = true;
    dy = 0.0;
    y = YTAM - RADIO -2;
  }
}

void loop() {
  if (!arduboy.nextFrame())
    return;
  
  arduboy.clear();

  arduboy.drawFastHLine(0, 63, 128, WHITE);

  update();

  if(arduboy.pressed(UP_BUTTON)){
    startJump();
  }
  if(!arduboy.pressed(UP_BUTTON)){
    endJump();
  }

  arduboy.setCursor(0, 0);
  arduboy.print(dy);
  arduboy.setCursor(0, 9);
  arduboy.print(y);
  arduboy.setCursor(0, 18);
  arduboy.print(onGround);

  arduboy.drawCircle(x, y, RADIO, WHITE);
  
  //delay(35);
  
  arduboy.display();
}
