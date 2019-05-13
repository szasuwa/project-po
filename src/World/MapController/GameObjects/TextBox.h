#pragma once
#include <regex>

#include "Interfaces/GameObject.h"
#include "../../TextObject.h"
#include "../../../Libs/base64.h"


class TextBox : public GameObject {
public:
	TextBox(Map* map = nullptr);
	TextBox(const sf::Vector2f& position, Map* map = nullptr);
	TextBox(const sf::Vector2f& position, const sf::Color& color, Map* map = nullptr);
	TextBox(const sf::Vector2f& position, const int& size, Map* map = nullptr);
	TextBox(const sf::Vector2f& position, const int& size, const sf::Color& color, Map* map = nullptr);
	TextBox(const TextBox& obj);

	void onUpdate(GameEngineInterface& f);
	void onFocus(GameEngineInterface& f);
	sf::FloatRect getGlobalBounds() const;
	void resize(const sf::Vector2f & p, bool gridSnap = false, bool vLock = false, bool hLock = false);
	void setColor(const sf::Color & c);

	/*
		<<Data format>>
		Properties separated using SERIALIZABLE_FIELD_DELIMITER.

		<<Data order>>
		class type
		id
		position.x
		position.y
		has hollider
		has trigger
		radius
		color
	*/
	virtual GameObjectClassType getClassType() const;
	virtual void serializeObject(std::ostream & ss) const;
	virtual void deserializeObject(std::istream & ss);
	static bool checkSerializableValidity(const std::string& s);
};