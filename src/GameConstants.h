#pragma once
#include <string>
#include <SFML/Config.hpp>
const std::string GAME_VERSION = "0.4"; 

const std::string REGEX_WHITESPACE = "\\s*";
const std::string REGEX_FLOAT_PATTERN = "(-?\\d+(\\.\\d+)?\\s+)";
const std::string REGEX_INT_PATTERN = "(-?\\d+\\s+)";
const std::string REGEX_BOOL_PATTERN = "((0|1)\\s+)";

const char SERIALIZABLE_OBJECT_DELIMITER = '\n';
const char SERIALIZABLE_FIELD_DELIMITER = ' ';

const sf::Vector2f PLAYER_SIZE(10, 10);
const sf::Color PLAYER_COLOR(0x4c33ffff);

const sf::Vector2f PLATFORM_SIZE(20, 5);
const sf::Color PLATFORM_COLOR(0x7d7d7dff);

const float POINT_RADIUS = 5;
const  sf::Color POINT_COLOR(0xffc90eff);

const float PORTAL_RADIUS = 5;
const int PORTAL_POINT_COUNT = 4;
const sf::Color PORTAL_COLOR(0x990033ff);

const sf::Vector2f BOX_SIZE(10, 10);
const sf::Color BOX_COLOR(0x79ecccc);

const sf::Color GRID_COLOR(0xc8c8c864);

const sf::Color PORTAL_LINK_LINE_COLOR_1(0xc8c8c8ff);
const sf::Color PORTAL_LINK_LINE_COLOR_2(0xc8c8c8ff);
const sf::Color PORTAL_LINK_POINT_COLOR_1(0xc8c8c8ff);
const sf::Color PORTAL_LINK_POINT_COLOR_2(0xc8c8c8ff);
const sf::Color PORTAL_LINK_POINT_COLOR_3(0xc8c8c8ff);
const sf::Color PORTAL_LINK_POINT_COLOR_4(0xc8c8c8ff);

const sf::Color TEXT_DEFAULT_COLOR(0xffffffff);
const sf::Color TEXT_ACTIVE_COLOR(0xc8c8c8ff);