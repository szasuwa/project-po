#include "TextBox.h"


TextBox::TextBox(Map* map) : TextBox(sf::Vector2f(), TEXT_BOX_SIZE, TEXT_BOX_COLOR, map)
{
}

TextBox::TextBox(const sf::Vector2f& position, Map* map) : TextBox(position, TEXT_BOX_SIZE, TEXT_BOX_COLOR, map)
{
}

TextBox::TextBox(const sf::Vector2f& position, const sf::Color& color, Map* map) : TextBox(position, TEXT_BOX_SIZE, color, map)
{
}

TextBox::TextBox(const sf::Vector2f& position, const int& size, Map* map) : TextBox(position, size, TEXT_BOX_COLOR, map)
{
}

TextBox::TextBox(const sf::Vector2f& position, const int& size, const sf::Color& color, Map* map) : GameObject(map)
{
	fDrawable = new TextObject(size);
	fTransformable = (TextObject*)fDrawable;
	fTransformable->setPosition(position);
	((TextObject*)fDrawable)->setFillColor(color);
}

TextBox::TextBox(const TextBox& obj) : GameObject(obj)
{
	fDrawable = new TextObject();
	fTransformable = (TextObject*)fDrawable;
	fTransformable->setPosition(obj.fTransformable->getPosition());
	((TextObject*)fDrawable)->setFillColor(((TextObject*)obj.fDrawable)->getFillColor());
	((TextObject*)fDrawable)->setCharacterSize(((TextObject*)obj.fDrawable)->getCharacterSize());
	((TextObject*)fDrawable)->setString(((TextObject*)obj.fDrawable)->getString());
	((TextObject*)fDrawable)->setFont(*((TextObject*)obj.fDrawable)->getFont());
}

void TextBox::onUpdate(GameEngineInterface& f)
{
}

void TextBox::onFocus(GameEngineInterface& f)
{
}

sf::FloatRect TextBox::getGlobalBounds() const
{
	return ((TextObject*)fDrawable)->getGlobalBounds();
}

void TextBox::resize(const sf::Vector2f & p, bool gridSnap, bool vLock, bool hLock)
{
}

void TextBox::setColor(const sf::Color & c) {
	((TextObject*)fDrawable)->setFillColor(sf::Color(c));
}

GameObjectClassType TextBox::getClassType() const
{
	return GameObjectClassType::TEXT_BOX;
}

void TextBox::serializeObject(std::ostream & ss) const {
	ss << (int)(getClassType()) << SERIALIZABLE_FIELD_DELIMITER;
	GameObject::serializeObject(ss);
	ss << ((TextObject*)fDrawable)->getCharacterSize() << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((TextObject*)fDrawable)->getFillColor().toInteger() << SERIALIZABLE_FIELD_DELIMITER;
	std::string temp = ((TextObject*)fDrawable)->getString();
	ss << base64_encode((const unsigned char*)temp.c_str(), temp.size()) << SERIALIZABLE_FIELD_DELIMITER;
}

void TextBox::deserializeObject(std::istream & ss) {
	GameObject::deserializeObject(ss);

	int s;
	sf::Uint32 c;
	std::string t;
	if (!(ss >> s >> c >> t))
		return;

	((TextObject*)fDrawable)->setCharacterSize(s);
	((TextObject*)fDrawable)->setFillColor(sf::Color(c));
	((TextObject*)fDrawable)->setString(base64_decode(t));
}

bool TextBox::checkSerializableValidity(const std::string& s)
{
	return true;
	return std::regex_match(s, std::regex(
		REGEX_WHITESPACE
		+ F_REGEX_GAME_OBJECT_PATTERN
		+ REGEX_INT_PATTERN + "{2}"
		+ REGEX_INT_PATTERN + "{2}"
		+ REGEX_WHITESPACE
	));
}