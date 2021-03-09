#include "ETank.h"


#include "SoundManager.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Game.h"
#include "Util.h"

ETank::ETank()
{
	TextureManager::Instance()->load("../Assets/textures/Tank2.png", "etank");

	auto size = TextureManager::Instance()->getTextureSize("etank");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);

	getRigidBody()->isColliding = false;

	setType(ETANK);
	setMaxSpeed(1.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
	setAccelerationRate(1.0f);
	setTurnRate(5.0f);
	setStopRadius(150.0f);
}

ETank::~ETank()
= default;

void ETank::draw()
{
	TextureManager::Instance()->draw("etank", 
		getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);
}

void ETank::update()
{
		//if (moveRight == true) {
		//	getTransform()->position.y += speed;
		//	if (getTransform()->position.y == 550) {
		//		moveRight = false;
		//	}
		//}
		//else if (moveRight == false) {
		//	getTransform()->position.y -= speed;
		//	if (getTransform()->position.y == 50) {
		//		moveRight = true;
		//	}
		//}

		m_Move();

}

void ETank::clean()
{
}

void ETank::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

void ETank::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

glm::vec2 ETank::getOrientation() const
{
	return m_orientation;
}

float ETank::getTurnRate() const
{
	return m_turnRate;
}

void ETank::setTurnRate(const float rate)
{
	m_turnRate = rate;
}

float ETank::getAccelerationRate() const
{
	return m_accelerationRate;
}

void ETank::setAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void ETank::setOrientation(const glm::vec2 orientation)
{
	m_orientation = orientation;
}

void ETank::setRotation(const float angle)
{
	m_rotationAngle = angle;

	const auto offset = -90.0f;
	const auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}

float ETank::getRotation() const
{
	return m_rotationAngle;
}

void ETank::setStopRadius(float stopR)
{
	m_stopRadius = stopR;
}


void ETank::m_Move()
{
		auto deltaTime = TheGame::Instance()->getDeltaTime();
		if (move == true)
		{
			setTurnRate(5.0f);
			setMaxSpeed(1.0f);
			// direction with magnitude
			m_targetDirection = m_destination - getTransform()->position;

			// normalized direction
			m_targetDirection = Util::normalize(m_targetDirection);

			auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

			auto turn_sensitivity = 5.0f;

			if (abs(target_rotation) > turn_sensitivity)
			{
				if (target_rotation > 0.0f)
				{
					setRotation(getRotation() + getTurnRate());
				}
				else if (target_rotation < 0.0f)
				{
					setRotation(getRotation() - getTurnRate());
				}
			}

			//getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

			//// using the formula pf = pi + vi*t + 0.5ai*t^2
			//getRigidBody()->velocity += getOrientation() * (deltaTime)+
			//	0.5f * getRigidBody()->acceleration * (deltaTime);

			getRigidBody()->velocity = m_targetDirection;

			getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

			getTransform()->position += getRigidBody()->velocity;
		}
}
