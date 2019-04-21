#include "DynamicObject.h"
#include "../../Maps/Map.h"
const std::string DynamicObject::F_REGEX_DYNAMIC_OBJECT_PATTERN = REGEX_BOOL_PATTERN + "{1}" + REGEX_FLOAT_PATTERN + "{3}" + REGEX_BOOL_PATTERN + "{4}";


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
	fIsStatic = obj.fIsStatic;
	fMass = obj.fMass;
	fForceVector = obj.fForceVector;
	fCollider = obj.fCollider;
	fVerticalInWindowLock = obj.fVerticalInWindowLock;
	fHorizontalInWindowLock = obj.fHorizontalInWindowLock;
}

void DynamicObject::applyWorldForces()
{
	if (fMap == nullptr)
		return;

	if (!fCollider.getBottom()) {
		fForceVector.y += (*fMap).fGravityRate * Frame::getInstance().getFrameTime();
		fForceVector.y = std::min(fForceVector.y, (*fMap).fMaxGravityForce);
	}
	else {
		fForceVector.y = std::min(fForceVector.y, (*fMap).fGravityRate * Frame::getInstance().getFrameTime());
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

sf::Vector2f DynamicObject::checkCollisions(const sf::Vector2f& p, const Collision & c) {
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
		if (p.x < 0 && c != Collision::Left)
		{
			d = sf::FloatRect(b.left, b.top, p.x, b.height);
			
			if (d.intersects(o))
			{
				if (obj->getInterfaceType() == GameObjectInterfaceType::DYNAMIC_OBJECT)
				{
					((DynamicObject*)obj)->onCollision(out, this, Collision::Right);
					o = obj->getGlobalBounds();
				}

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

		if (p.x > 0 && c != Collision::Right)
		{
			d = sf::FloatRect(b.left + b.width, b.top, p.x, b.height);

			if (d.intersects(o))
			{
				if (obj->getInterfaceType() == GameObjectInterfaceType::DYNAMIC_OBJECT)
				{
					((DynamicObject*)obj)->onCollision(out, this, Collision::Left);
					o = obj->getGlobalBounds();
				}

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

		if (p.y < 0 && c != Collision::Top)
		{
			d = sf::FloatRect(b.left, b.top, b.width, p.y);

			if (d.intersects(o))
			{
				if (obj->getInterfaceType() == GameObjectInterfaceType::DYNAMIC_OBJECT)
				{
					((DynamicObject*)obj)->onCollision(out, this, Collision::Bottom);
					o = obj->getGlobalBounds();
				}

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

		if (p.y > 0 && c != Collision::Bottom)
		{
			d = sf::FloatRect(b.left, b.top + b.height, b.width, p.y);

			if (d.intersects(o))
			{
				if (obj->getInterfaceType() == GameObjectInterfaceType::DYNAMIC_OBJECT)
				{
					((DynamicObject*)obj)->onCollision(out, this, Collision::Top);
					o = obj->getGlobalBounds();
				}

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

#include "../../../../Logger.h"
sf::Vector2f DynamicObject::onCollision(const sf::Vector2f& p, DynamicObject * o, const Collision& c)
{
	
	if (c == Collision::Top)
	{
		sf::Vector2f tP;
		tP = fMovement;
		o->move(tP, Collision::Bottom);
	}

	if (c == Collision::Left || c == Collision::Right)
	{
		if (p.x > 0)
			move(sf::Vector2f(std::min(p.x, p.x / fMass), 0), c);
		else
			move(sf::Vector2f(std::max(p.x, p.x / fMass), 0), c);
	}
		

	if (c == Collision::Bottom)
	{
		if (p.y > 0)
			move(sf::Vector2f(0, std::min(p.y, p.y)), c);
		else
			move(sf::Vector2f(0, std::max(p.y, p.y)), c);
	}

	return p;
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
	fMovement.x = fMovement.y = 0;
	applyWorldForces();

	//Set position
	move(fForceVector * Frame::getInstance().getFrameTime());
}

void DynamicObject::move(const sf::Vector2f& p)
{
	if (fTransformable == nullptr)
		return;

	if (fIsStatic)
		return;

	sf::Vector2f nP = p;
	nP = checkCollisions(nP);
	nP = lockInFrame(nP);
	fTransformable->move(nP);
	fMovement += nP;
}

void DynamicObject::move(const sf::Vector2f& p, const Collision & c)
{
	if (fTransformable == nullptr)
		return;

	if (fIsStatic)
		return;

	sf::Vector2f nP = p;
	nP = checkCollisions(nP, c);
	nP = lockInFrame(nP);
	fTransformable->move(nP);
	fMovement += nP;
}

GameObjectInterfaceType DynamicObject::getInterfaceType() const
{
	return GameObjectInterfaceType::DYNAMIC_OBJECT;
}

void DynamicObject::serializeObject(std::ostream & ss) const {
	GameObject::serializeObject(ss);
	ss << fIsStatic << SERIALIZABLE_FIELD_DELIMITER;
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

	bool s;
	float m, x, y;
	bool l, r, t, b;

	if (!(ss >> s >> m >> x >> y >> l >> r >> t >> b))
		return;

	fIsStatic = s;
	fMass = m;
	fForceVector.x = x;
	fForceVector.y = y;

	if(l)
		fCollider.triggerLeft();

	if (r)
		fCollider.triggerRight();

	if (t)
		fCollider.triggerTop();

	if (b)
		fCollider.triggerBottom();

}