#ifndef PHYSICS_H
#define PHYSICS_H
#include "Ball.h"
#include "MovementManager.h"
#include "GameManager.h"
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

extern int windowWidth, windowHeight;
extern int tableWidth, tableHeight;
extern sf::Clock dtClock;
extern float dt;
extern sf::Vertex socketEdges[24][2];
extern Ball* cornerObjects[12];

class Physics{
    public:
        static void boxColision(Ball *ball);
        static void ballCollision(Ball *ballA, Ball *ballB);
        static void cushionCollision(Ball *ballA, Ball *ballB);
        static bool overLapDetection(Ball *whiteBall, Ball *ball);
};
#endif