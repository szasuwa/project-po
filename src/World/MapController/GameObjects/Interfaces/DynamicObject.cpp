#include "DynamicObject.h"
#include "../../Maps/Map.h"
const std::string DynamicObject::F_REGEX_DYNAMIC_OBJECT_PATTERN = REGEX_FLOAT_PATTERN + "{3}" + REGEX_BOOL_PATTERN + "{4}";


DynamicObject::DynamicObject(Map * map) : DynamicObject(sf::Vector2f(0,0), map)
{
}

DynamicObject::DynamicObject(const sf::Vector2f & position, Map * map) : DynamicObject(position, false, false, map)
{
}

DynamicObject::DynamicObject(bool vLock, bool hLock, Map * map) : DynamicObject(sf::Vector2f(0,0), vLock, hLock, map)
{
}

DynamicObject::DynamicObject(const sf::Vector2f & position, bool vLock, bool hLock, Map * map) : GameObject(map), 
	fForceVector(0, 0), fVerticalInWindowLock(vLock), fHorizontalInWindowLock(hLock), fMass(1)
{
}

DynamicObject::DynamicObject(const DynamicObject &obj) : GameObject(obj)
{
	fForceVector = obj.fForceVector;
	fCollider = obj.fCollider;
	fVerticalInWindowLock = obj.fVerticalInWindowLock;
	fHorizontalInWindowLock = obj.fHorizontalInWindowLock;
}


DynamicObject::~DynamicObject()
{
}

void DynamicObject::applyWorldForces()
{
	if (fMap == nullptr)
		return;

	if (!fCollider.getBottom()) {
		fForceVector.y += (*fMap).fGravityRate;
		fForceVector.y = std::min(fForceVector.y, (*fMap).fMaxGravityForce);
	}

	if (fCollider.getTop() && fForceVector.y < 0)
		fForceVector.y = 0;

	if (fForceVector.x > 0)
	{
		fForceVector.x = std::max(fForceVector.x - (*fMap).fDecelerationRate, 0.0f);
	}
	else if (fForceVector.x < 0)
	{
		fForceVector.x = std::min(fForceVector.x + (*fMap).fDecelerationRate, 0.0f);
	}
}

sf::Vector2f DynamicObject::lockInFrame(const sf::Vector2f & p)
{
	if (fMap == nullptr)
		return sf::Vector2f();

	if(!fHorizontalInWindowLock && !fVerticalInWindowLock)
		return p;

	sf::Vector2f out = p;

	MapBoundaries mb = fMap->getBoundaries();
	sf::FloatRect b = getGlobalBounds();

	if (fHorizontalInWindowLock) 
	{
		if (mb.hasLeft && p.x < 0 && b.left + p.x < mb.left)
		{
			fCollider.triggerLeft();
			out.x = std::min(mb.left - b.left, 0.f);
		}

		if (mb.hasRight && p.x > 0 && b.left + b.width + p.x > mb.right)
		{
			fCollider.triggerRight();
			out.x = std::max(mb.right - b.left - b.width, 0.f);
		}
	}
	
	if (fVerticalInWindowLock) 
	{
		if (mb.hasTop && p.y < 0 && b.top + p.y < mb.top)
		{
			fCollider.triggerTop();
			out.y = std::min(mb.top - b.top, 0.f);
		}

		if (mb.hasBottom && p.y > 0 && b.top + b.height + p.y > mb.bottom)
		{
			fCollider.triggerBottom();
			out.y = std::max(mb.bottom - b.top - b.height, 0.f);
		}
	}
	return out;
}

sf::Vector2f DynamicObject::checkCollisions(const sf::Vector2f& p) {
	if (fMap == nullptr)
		return sf::Vector2f(0,0);

	sf::Vector2f out = p;
	fCollider.resetCollider();

	sf::FloatRect b = getGlobalBounds();

	for (GameObject* obj : fMap->getGameObjects()) 
	{
		if (obj == nullptr || obj == this || (!obj->hasCollider() && !obj->hasTrigger()))
			continue;
		
		sf::FloatRect o = obj->getGlobalBounds();
		sf::FloatRect d;
		bool collision = false, trigger = false;

		//Check left
		if (!fCollider.getLeft() && p.x < 0)
		{
			d = sf::FloatRect(b.left, b.top, p.x, b.height);
			
			if (d.intersects(o))
			{
				if (obj->hasTrigger())
				{
					trigger = true;
					out = onTrigger(out, obj, Collision::Left, d, o);
				}

				if (obj->hasCollider())
				{
					collision = true;
					out = onCollision(out, obj, Collision::Left, d, o);
				}
			}
		}

		if (!fCollider.getRight() && p.x > 0)
		{
			d = sf::FloatRect(b.left + b.width, b.top, p.x, b.height);

			if (d.intersects(o))
			{
				if (obj->hasTrigger())
				{
					trigger = true;
					out = onTrigger(out, obj, Collision::Right, d, o);
				}

				if (obj->hasCollider())
				{
					collision = true;
					out = onCollision(out, obj, Collision::Right, d, o);
				}
			}
		}

		if (!fCollider.getTop() && p.y < 0)
		{
			d = sf::FloatRect(b.left, b.top, b.width, p.y);

			if (d.intersects(o))
			{
				if (obj->hasTrigger())
				{
					trigger = true;
					out = onTrigger(out, obj, Collision::Top, d, o);
				}

				if (obj->hasCollider())
				{
					collision = true;
					out = onCollision(out, obj, Collision::Top, d, o);

				}
			}

		}

		if (!fCollider.getBottom() && p.y > 0)
		{
			d = sf::FloatRect(b.left, b.top + b.height, b.width, p.y);

			if (d.intersects(o))
			{
				if (obj->hasTrigger())
				{
					trigger = true;
					out = onTrigger(out, obj, Collision::Bottom, d, o);
				}

				if (obj->hasCollider())
				{
					collision = true;
					out = onCollision(out, obj, Collision::Bottom, d, o);
				}
			}
		}

		if (trigger && !obj->onTrigger(this))
			continue;

		if (collision && !obj->onCollision(this))
			continue;
	}

	
	return out;
}

sf::Vector2f DynamicObject::onCollision(const sf::Vector2f & p, GameObject * obj, const Collision & c, const sf::FloatRect & z, const sf::FloatRect & o)
{
	sf::Vector2f out = p;

	switch (c)
	{
		case Collision::Left:
			fCollider.triggerLeft();
			out.x = std::min(o.left + o.width - z.left, 0.f);
			break;

		case Collision::Right:
			fCollider.triggerRight();
			out.x = std::max(o.left - z.left, 0.f);
			break;

		case Collision::Top:
			fCollider.triggerTop();
			out.y = std::min(o.top + o.height - z.top, 0.f);
			break;

		case Collision::Bottom:
			fCollider.triggerBottom();
			out.y = std::max(o.top - z.top, 0.f);
			break;

		default:
			break;
	}

	return out;
}

void DynamicObject::onUpdate() 
{
	applyWorldForces();

	//Set position
	move(fForceVector * Frame::getInstance().getFrameTime());
}

void DynamicObject::serializeObject(std::ostream & ss) const {
	GameObject::serializeObject(ss);
	ss << fMass << SERIALIZABLE_FIELD_DELIMITER;
	ss << fForceVector.x << SERIALIZABLE_FIELD_DELIMITER;
	ss << fForceVector.y << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getLeft() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getRight() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getTop() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getBottom() << SERIALIZABLE_FIELD_DELIMITER;
}

void DynamicObject::deserializeObject(std::istream & ss) {
	GameObject::deserializeObject(ss);
	ss >> fMass;
	ss >> fForceVector.x;
	ss >> fForceVector.y;

	float l, r, t, b;
	ss >> l;
	ss >> r;
	ss >> t;
	ss >> b;

	if(l)
		fCollider.triggerLeft();

	if (r)
		fCollider.triggerRight();

	if (t)
		fCollider.triggerTop();

	if (b)
		fCollider.triggerBottom();

}

void DynamicObject::move(const sf::Vector2f& p)
{
	if (fTransformable == nullptr)
		return;

	sf::Vector2f nP = p;
	nP = checkCollisions(nP);
	nP = lockInFrame(nP);
	fTransformable->move(nP);
}