#include "MovementManager.h"
int movingBalls = 0;
void MovementManager::ballMove(Ball *ball, sf::CircleShape *ballShape) {
    ball->ax = (-ball->vx); //setting an acceloration value (friction on the table)
    ball->ay = (-ball->vy);

    ball->vx += (ball->ax * dt); //applying the friction to the velocity
    ball->vy += (ball->ay * dt);

    ball->x += (ball->vx * dt); //moviving the ball with the velocity
    ball->y += (ball->vy * dt);

    ballShape->setPosition(ball->x, ball->y);
}

void MovementManager::collisionCheck(Ball *ball, Ball *balls[]) {
    for (int otherBall = 0; otherBall < ballNumbers; otherBall++) {
        if (ball->num != otherBall) {
            float distanceX = (ball->x - balls[otherBall]->x) * (ball->x - balls[otherBall]->x);
            float distancey = (ball->y - balls[otherBall]->y) * (ball->y - balls[otherBall]->y);

            if ((distanceX + distancey) <= 1600.f) { //1600.f being radius^2
                if((ball->vx == 0 && ball->vy == 0) || balls[otherBall]->vx == 0 && balls[otherBall]->vy == 0) {
                    movingBalls++;
                }
                Physics::ballCollision(ball, balls[otherBall]);
            }
        }
    }
}

void MovementManager::moveTick(Ball *balls[], sf::CircleShape *ballShapes[], int velocityX, int velocityY) {
    if(movingBalls == 0) {//fires whiteBall
        balls[0]->vx = (balls[0]->x - velocityX);
        balls[0]->vy = (balls[0]->y - velocityY);
        movingBalls++;
    }
    dt = dtClock.restart().asSeconds();
    for (int i = 0; i < ballNumbers; i++) {
        if (balls[i]->vx != 0 && balls[i]->vy != 0) {
            Physics::boxColision(balls[i]);
            ballMove(balls[i], ballShapes[i]);
            collisionCheck(balls[i], balls);
            if (fabs(balls[i]->vx * balls[i]->vx + balls[i]->vy * balls[i]->vy) < 1.f) { //if the balls velociy gets to a certain point, stop it
                ballShapes[i]->setPosition(balls[i]->x, balls[i]->y);
                balls[i]->vx = 0;
                balls[i]->vy = 0;
                movingBalls--;
            }
            if (movingBalls == 0) {
                return;
            }
        }
    }
}