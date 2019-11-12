#pragma once

#ifndef _PARTICLE_OBJECT_

#include <vector>
#include <iostream>
#include <list>
#include <ctime>

class ParticleObject : public GameObject
{
private:
	Vector m_velocity;
	float m_acceleration;
	float m_life;
	float m_maxLife;

	float m_speed;

public:
	ParticleObject();
	ParticleObject(Sprite* sprite,float lifeSpan);

	void SetAcceleration(float Accel);
	float getAcceleration();

	void SetVelocity(Vector vel);
	Vector getVelocity();

	void SetLife(float life);
	float getLife();

	void SetMaxLife(float maxLife);
	float getMaxLife();

	void update(float deltaTime);
};

#endif
