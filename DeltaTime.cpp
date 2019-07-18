#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int windowWidth = 1182, windowHeight = 601;
int tableWidth = 762, tableHeight = 381;
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
sf::RectangleShape innerTable(sf::Vector2f(tableWidth, tableHeight));
sf::CircleShape ball(10.f);

sf::Clock dtClock;
float dt;


int main() {
    innerTable.setFillColor(sf::Color::Green);
    innerTable.setPosition(sf::Vector2f(windowWidth / 2 - tableWidth / 2, windowHeight / 2 - tableHeight / 2));
    ball.setPosition(sf::Vector2f(windowWidth / 2 - ball.getRadius() / 2, windowHeight / 2 - ball.getRadius() / 2));
    bool direction = true;
    while(window.isOpen()) {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.draw(innerTable);

        dt = dtClock.restart().asSeconds();
        if(direction == true) {
            float newX = ball.getPosition().x + (100*dt);
            float newY = ball.getPosition().y;
            ball.setPosition(sf::Vector2f(newX, newY));
            if (ball.getPosition().x + (ball.getRadius() * 2) >= innerTable.getPosition().x + tableWidth){
                direction = false;
            }
        } else if(direction == false) {
            float newX = ball.getPosition().x - (100*dt);
            float newY = ball.getPosition().y;
            ball.setPosition(sf::Vector2f(newX, newY));
            if (ball.getPosition().x  <= innerTable.getPosition().x){
                direction = true;
            }
        }

        window.draw(ball);
        window.display();
    }
}