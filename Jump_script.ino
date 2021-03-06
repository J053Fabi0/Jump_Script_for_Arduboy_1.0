#include <Arduboy2.h>

Arduboy2 arduboy;

const int XTAM = 128; //El tamaño de la pantalla
const int YTAM = 64;
const int RADIO = 7;
const float GRAV = 0.1;

float x = XTAM/2 - RADIO/2;
float y = YTAM/2 - RADIO/2;
float dx = 0; //Velocidad (lo que se le suma a x por frame)
float dy = 0;

bool onGround = false;
bool onTop = false;

void setup() {
  arduboy.boot();
  arduboy.blank();
  arduboy.flashlight();
  arduboy.audio.begin();
  arduboy.setFrameRate(30);
}

void startJump(){
  if(onGround){
    dy = -3.14; //El primer impulso, el mejor es 3.14 para que no toque el techo
    onGround = false;
    y = YTAM - RADIO -2;
  }
}

void endJump(){
  if(dy < -0.1){
    dy -= -0.1;
  }
}

void update(){
  dy += GRAV;
  x += dx;
  y += dy;
  onTop = false;

  if(y > YTAM - RADIO -2){
    onGround = true;
    dy = 0.0;
    y = YTAM - RADIO -2;
  }
  if(y < RADIO){
    y = RADIO;
    onTop = true;
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
  
  arduboy.drawCircle(x, y, RADIO, WHITE);

  if(dy > 0){
    arduboy.setCursor(0, 0);
    arduboy.print("Falling");
  }else if(dy < 0 && !onGround){
    arduboy.setCursor(0, 0);
    arduboy.print("Jumping");
  }
    
  arduboy.display();
}
