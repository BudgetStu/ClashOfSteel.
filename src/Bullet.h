﻿#pragma once
#ifndef _BULLET_
#define _BULLET_

#include "DisplayObject.h"
#include "TextureManager.h"
#include "PlayerTank.h"


class Bullet :public PlayerTank
{
public:
	Bullet(float rotation, glm::vec2 position, bool enable, std::string texture, std::string key);

	~Bullet();

	void draw() override;
	void update() override;
	void handeEvents();
	void clean() override;
	void reset();

	glm::vec2 getOrientation() const;
	void setOrientation(glm::vec2 orientation);
	float getRotation() const;
	void setRotation(float angle);
	bool bulletShot = false;
	float getAccelerationRate() const;
	void setAccelerationRate(float rate);

	void Shoot();
	void move();
private:
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed = 10;
	float m_accelerationRate;
	std::string m_Texture, m_key;
};
#endif


