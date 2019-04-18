#pragma once
#include <string>
#include <SFML/Config.hpp>
const std::string GAME_VERSION = "0.3"; 

const std::string REGEX_WHITESPACE = "\\s*";
const std::string REGEX_FLOAT_PATTERN = "(-?\\d+(\\.\\d+)?\\s+)";
const std::string REGEX_INT_PATTERN = "(-?\\d+\\s+)";
const std::string REGEX_BOOL_PATTERN = "((0|1)\\s+)";

const char SERIALIZABLE_OBJECT_DELIMITER = '\n';
const char SERIALIZABLE_FIELD_DELIMITER = ' ';

const sf::Vector2f PLAYER_SIZE(10, 10);
const sf::Color PLAYER_COLOR(1278476287);

const sf::Vector2f PLATFORM_SIZE(20, 5);
const sf::Color PLATFORM_COLOR(2105376255);

const float POINT_RADIUS = 5;
const  sf::Color POINT_COLOR(4291366655);

const sf::Vector2f PORTAL_SIZE(10, 10);
const sf::Color PORTAL_COLOR(2566927359);

const sf::Color GRID_COLOR(3368601700);

const sf::Color PORTAL_LINK_LINE_COLOR_1(3368601855);
const sf::Color PORTAL_LINK_LINE_COLOR_2(3368601855);
const sf::Color PORTAL_LINK_POINT_COLOR_1(3368601855);
const sf::Color PORTAL_LINK_POINT_COLOR_2(3368601855);
const sf::Color PORTAL_LINK_POINT_COLOR_3(3368601855);
const sf::Color PORTAL_LINK_POINT_COLOR_4(3368601855);