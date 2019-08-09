#include "GameManager.h"
#include <String>
#include <iostream>
sf::Vector2f initialPositions[] = { //array of the balls positions
    sf::Vector2f(391.95f, 391.95f),  sf::Vector2f(701.5f,400.5f), sf::Vector2f(861.5f,360.5f),  sf::Vector2f(741.5f,420.5f), //0, 1, 2, 3
    sf::Vector2f(821.5f,420.5f),  sf::Vector2f(861.5f,440.5f), sf::Vector2f(781.5f,360.5f),  sf::Vector2f(861.5f,320.5f), //4, 5, 6, 7
    sf::Vector2f(781.5f,400.5f),  sf::Vector2f(821.5f,460.5f), sf::Vector2f(861.5f,400.5f),  sf::Vector2f(741.5f,380.5f), //8, 9, 10, 11
    sf::Vector2f(861.5f,480.5f),  sf::Vector2f(821.5f,340.5f), sf::Vector2f(781.5f,440.5f),  sf::Vector2f(821.5f,380.5f), //12, 13, 14, 15
};
int playerGoing = 0;
Player *players[2];
void GameManager::tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers) {
    dLine[0] = sf::Vertex(sf::Vector2f(400.5f, 210.f), sf::Color::Black);
    dLine[1] = sf::Vertex(sf::Vector2f(400.5f, 211.f+tableHeight), sf::Color::Black);
    innerTable.setPosition(210.f, 210.f);
    innerTable.setFillColor(sf::Color::Green);
    innerTable.setOutlineThickness(59.f);
    innerTable.setOutlineColor(sf::Color::Yellow);
    for(int i = 0; i < 6; i++){
        cushions[i].setPosition(cushionPositions[i]);
        cushions[i].setFillColor(sf::Color::Blue);
        cushions[i].setOutlineThickness(0.f);
        cushions[i].setOutlineColor(sf::Color::Blue);
    }
    for (int i = 0; i < ballNumbers; i++) {
        balls[i] = new Ball(i, 8.55f, initialPositions[i].x, initialPositions[i].y);
        ballShapes[i] = new sf::CircleShape(balls[i]->radius);
        ballShapes[i]->setPosition(balls[i]->x, balls[i]->y);
        if (balls[i]->num < 8) {
            ballShapes[i]->setFillColor(sf::Color::Blue);
        } else if (balls[i]->num > 8) {
            ballShapes[i]->setFillColor(sf::Color::Red);
        }
        if (balls[i]->num == 0) {
            ballShapes[i]->setFillColor(sf::Color::White);
        } if (balls[i]->num == 8) {
            ballShapes[i]->setFillColor(sf::Color::Black);
        }
    }
    
    players[0] = new Player(0);
    players[1] = new Player(1);
    poolCue.setPosition(sf::Vector2f(balls[0]->x + balls[0]->radius - 10, balls[0]->y - balls[0]->radius - 10));
    poolCue.setFillColor(sf::Color::Black);
}
void GameManager::lose() {
    std::cout << "loser\n";
}
void GameManager::win() {
    std::cout << "winner\n";
}
void GameManager::ballSunk(Ball *ball) {
    if(ball->num == 0) {
        if(players[playerGoing]->playersBallsLeft == 0) {
            lose();
        }
        ball->isSunk = true;
    } else if(ball->num == 8) {
        ball->isSunk = true;
        if(players[playerGoing]->playersBallsLeft == 0) {
            win();
        } else {
            lose();
        }
    } else {
        if(players[playerGoing]->ballSuit == 0) {
            if(ball->num > 8) {
                players[playerGoing]->ballSuit = 9;
                if(playerGoing == 0) {
                    players[1]->ballSuit = 1;
                } else {
                    players[0]->ballSuit = 1;
                }
            }
            else {
                players[playerGoing]->ballSuit = 1;
                if(playerGoing == 0) {
                    players[1]->ballSuit = 9;
                } else {
                    players[0]->ballSuit = 9;
                }
            }
        }
        if(ball->num < 8) {
            if(players[playerGoing]->ballSuit == 1) {
                if(!ballSunk) players[playerGoing]->ballSunk = true;
                players[playerGoing]->playersBallsLeft--;
            } else {
                if(playerGoing == 0) {
                    players[1]->playersBallsLeft--;
                } else {
                    players[0]->playersBallsLeft--;
                }
            }
        } else if(ball->num > 8) {
            if(players[playerGoing]->ballSuit == 9) {
                if(!ballSunk) players[playerGoing]->ballSunk = true;
                players[playerGoing]->playersBallsLeft--;
            } else {
                if(playerGoing == 0) {
                    players[1]->playersBallsLeft--;
                } else {
                    players[0]->playersBallsLeft--;
                }
            }
        }
        ball->isSunk = true;
        std::cout << "Ball sunk: " << ball->num << "\n";
        ballsLeft--;
    }
}

void GameManager::swapPlayer() {
    std::cout << "Player: " << players[playerGoing]->playerNum << "\n";
    if(players[playerGoing]->ballSuit == 1) {
        std::cout << "Suit: " << "blue" << "\n";
    } else if (players[playerGoing]->ballSuit == 9) {
        std::cout << "Suit: " << "red" << "\n";
    } else {
        std::cout << "Suit: " << "none" << "\n";
    }
    std::cout << "Balls left: " << players[playerGoing]->playersBallsLeft << "\n";
    std::cout << "total left: " << ballsLeft << "\n";
    if(playerGoing == 0){
        playerGoing = 1;
        poolCue.setFillColor(sf::Color::Magenta);
    } else {
        playerGoing = 0;
        poolCue.setFillColor(sf::Color::Black);
    }
}