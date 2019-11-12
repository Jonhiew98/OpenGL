#include "pch.h"
#include <iostream>
#include "ParticleObject.h"

using namespace std;

ParticleObject ::ParticleObject()
{

}

ParticleObject::ParticleObject(Sprite* sprite, float lifeSpan)
{
	SetSprite(sprite);
	m_maxLife = lifeSpan;
	m_life = m_maxLife;
	

	m_speed = 100.0f;
}

void ParticleObject::SetAcceleration(float Accel)
{
	m_acceleration = Accel;
}

float ParticleObject::getAcceleration()
{
	return m_acceleration;
}

void ParticleObject::SetVelocity(Vector vel)
{
	for (int i = 0; i < 3; i++)
	{
		m_velocity.mVal[i] = vel.mVal[i];
	}	
}

Vector ParticleObject::getVelocity()
{
	return m_velocity;
}

void ParticleObject::SetLife(float life)
{
	m_life = life;
}

float ParticleObject::getLife()
{
	return m_life;
}

void ParticleObject::SetMaxLife(float maxLife)
{
	m_maxLife = maxLife;
}
float ParticleObject::getMaxLife()
{
	return m_maxLife;
}

void ParticleObject::update(float deltaTime)
{
	//acceleration
	m_acceleration *= m_speed;

	if (m_life >= 0)
	{
		//temporary solution
		Vector temp = GetPos() + (m_velocity*deltaTime);
		SetPos(temp);
		m_life -= deltaTime;
	}	
}

////temporary solution
//Vector temp = GetPos();
//temp.mVal[1] += m_speed * deltaTime;
//SetPos(temp);
//m_life -= deltaTime;