#include "Pokitto.h"
#include "mouse.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PB = Pokitto::Buttons;


DigitalIn button0 = DigitalIn(EXT0); // Button

InterruptIn ballLeft(EXT3); // Left
InterruptIn ballRight(EXT4); // Right
InterruptIn ballUp(EXT5); // Up
InterruptIn ballDown(EXT8); // Down

DigitalOut ledGreen = DigitalOut(EXT6); // Green LED
DigitalOut ledWhite = DigitalOut(EXT7); // White LED
DigitalOut ledBlue = DigitalOut(EXT9); // Blue LED
DigitalOut ledRed = DigitalOut(EXT10); // Red LED

int px,py = 0;
int speed = 3;

void moveRight(){
    px+=speed;
}
void moveLeft(){
    px-=speed;
}
void moveUp(){
    py-=speed;
}
void moveDown(){
    py+=speed;
}

int main() {
    PC::begin();
    PD::persistence = false;
    PD::invisiblecolor = 0;

    button0.mode(PullUp); // Button Low active
    ballLeft.mode(PullUp); // Left
    ballRight.mode(PullUp); // Right
    ballUp.mode(PullUp); // Up
    ballDown.mode(PullUp); // Down

    ledGreen.write(LOW); // Green
    ledWhite.write(LOW); // White
    ledBlue.write(LOW); // Blue
    ledRed.write(LOW); // Red


    while( PC::isRunning() ){
        PD::update();
        
        ballUp.rise(&moveUp);
        ballUp.fall(&moveUp);
        ballDown.rise(&moveDown);
        ballDown.fall(&moveDown);
        ballLeft.rise(&moveLeft);
        ballLeft.fall(&moveLeft);
        ballRight.rise(&moveRight);
        ballRight.fall(&moveRight);

        if(PB::upBtn()){ledRed.write(HIGH);}else{ledRed.write(LOW);}
        if(PB::downBtn()){ledGreen.write(HIGH);}else{ledGreen.write(LOW);}
        if(PB::leftBtn()){ledBlue.write(HIGH);}else{ledBlue.write(LOW);}
        if(button0.read()){ledWhite.write(LOW);}else{ledWhite.write(HIGH);}


        PD::printf("X: %d, Y: %d\n", px,py);
        PD::drawBitmap(px,py,mouse);
    }
}