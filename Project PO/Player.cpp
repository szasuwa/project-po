#include "Player.h"

Player::Player(const sf::Vector2u windowSize) : F_WINDOW_SIZE(windowSize)
{
	fDrawable = new sf::RectangleShape(sf::Vector2f(10, 10));
}

Player::~Player()
{
}

void Player::update() 
{

}
