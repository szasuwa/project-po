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
	fDrawable = new sf::Text();
	fTransformable = (sf::Text*)fDrawable;
	fTransformable->setPosition(position);
	((sf::Text*)fDrawable)->setFillColor(color);
	((sf::Text*)fDrawable)->setCharacterSize(size);

	static bool isFontLoaded;
	static sf::Font font;

	if (!isFontLoaded)
		isFontLoaded = font.loadFromFile("res/bboron.ttf");

	((sf::Text*)fDrawable)->setFont(font);
}

TextBox::TextBox(const TextBox& obj) : GameObject(obj)
{
	fDrawable = new sf::Text();
	fTransformable = (sf::Text*)fDrawable;
	fTransformable->setPosition(obj.fTransformable->getPosition());
	((sf::Text*)fDrawable)->setFillColor(((sf::Text*)obj.fDrawable)->getFillColor());
	((sf::Text*)fDrawable)->setCharacterSize(((sf::Text*)obj.fDrawable)->getCharacterSize());
	((sf::Text*)fDrawable)->setString(((sf::Text*)obj.fDrawable)->getString());
	((sf::Text*)fDrawable)->setFont(*((sf::Text*)obj.fDrawable)->getFont());
}

void TextBox::onUpdate(GameEngineInterface& f)
{
}

void TextBox::onFocus(GameEngineInterface& f)
{
}

sf::FloatRect TextBox::getGlobalBounds() const
{
	return ((sf::Text*)fDrawable)->getGlobalBounds();
}

void TextBox::resize(const sf::Vector2f & p, bool gridSnap, bool vLock, bool hLock)
{
}

void TextBox::setColor(const sf::Color & c) {
	((sf::Text*)fDrawable)->setFillColor(sf::Color(c));
}

GameObjectClassType TextBox::getClassType() const
{
	return GameObjectClassType::TEXT_BOX;
}

void TextBox::serializeObject(std::ostream & ss) const {
	ss << (int)(getClassType()) << SERIALIZABLE_FIELD_DELIMITER;
	GameObject::serializeObject(ss);
	ss << ((sf::Text*)fDrawable)->getCharacterSize() << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::Text*)fDrawable)->getFillColor().toInteger() << SERIALIZABLE_FIELD_DELIMITER;
	std::string temp = ((sf::Text*)fDrawable)->getString();
	ss << base64_encode((const unsigned char*)temp.c_str(), temp.size()) << SERIALIZABLE_FIELD_DELIMITER;
}

void TextBox::deserializeObject(std::istream & ss) {
	GameObject::deserializeObject(ss);

	int s;
	sf::Uint32 c;
	std::string t;
	if (!(ss >> s >> c >> t))
		return;

	((sf::Text*)fDrawable)->setCharacterSize(s);
	((sf::Text*)fDrawable)->setFillColor(sf::Color(c));
	((sf::Text*)fDrawable)->setString(base64_decode(t));
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