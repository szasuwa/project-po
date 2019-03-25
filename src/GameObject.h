#pragma once
#include"Serializable.h"
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject : public Serializable
{
private:
	static int fNextGameObjectId;
	
protected:
	static std::vector<GameObject*> fGameObjectList;

	sf::Drawable *fDrawable;
	const int fId;
public:
	GameObject();
	~GameObject();

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);

	virtual void update() = 0;
	virtual sf::FloatRect getGlobalBounds() = 0;
	sf::Drawable *getDrawable();
	virtual sf::Transformable *getTransformable() = 0;
	int getId();

	//Statics
	static void broadcastOriginChange(sf::Vector2f &o);
	static void broadcastUpdate();
	static void broadcastDraw(sf::RenderWindow &w);
	static void destroyAll();
};

