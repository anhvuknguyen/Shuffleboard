#ifndef __Puck_h
#define __Puck_h

#include <stdio.h>
#include <stdint.h>
#include <string>
#include "images/images.h"
#include "../inc/ST7735.h"

using namespace std;

class Puck{
    public:
    uint8_t id;

    float oldX;
    float oldY;
    float x;
    float y;

    float speed;
    float vX;
    float vY;
    bool isMoving;


    string color;
    const unsigned short *image; 
    const unsigned short *erase;
    uint8_t w;
    uint8_t h;

    Puck(float startX, float startY, string c, uint8_t puckid);
    void set_Velocity(float velX, float velY);
    int8_t check_Collisions(uint8_t puckId);
    void process_Collision(uint8_t firstId, uint8_t secondId, float speed);
    void process_Movement();
};

#endif