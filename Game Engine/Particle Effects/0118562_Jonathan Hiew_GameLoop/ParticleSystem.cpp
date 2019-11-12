#include "pch.h"
#include <iostream>
#include "ParticleSystem.h"

using namespace std;

ParticleSystem::ParticleSystem(Sprite* sprite)
{
	m_sprites = sprite;

	//spawnRate
	emissionRate = 0.05f;
	currentTime = 0;

	//Set Effects
	ParticleAffector* pa = new ParticleAffector(particleAffect::GRAVITY);
	ParticleAffector* pa2 = new ParticleAffector(particleAffect::COLOR);
	ParticleAffector* pa3 = new ParticleAffector(particleAffect::ROTATION);
	ParticleAffector* pa4 = new ParticleAffector(particleAffect::SCALE);

	m_affectorList.push_back(pa);
	m_affectorList.push_back(pa2);
	m_affectorList.push_back(pa3);
	m_affectorList.push_back(pa4);
}

void ParticleSystem::SetPos(Vector pos)
{
	m_position = pos;
}

Vector ParticleSystem::getPos()
{
	return m_position;
}

void ParticleSystem::setEmitShape(emitShape shape)
{
	m_emitShape = shape;
}

emitShape ParticleSystem::getEmitShape()
{
	return m_emitShape;
}

void ParticleSystem::Spawn()
{
	//sprites & object life span
	ParticleObject* newParticle = new ParticleObject(m_sprites,5.0f); 

	// set particles object
	newParticle->SetRotation(50.0f);
	newParticle->SetScale(0.2f);

	// set particle velocity
	float speed = 50.0f;
	float x = (float(rand()) / float(RAND_MAX)) * 2.0f * speed - 1.0f * speed;
	float y = (float(rand()) / float(RAND_MAX)) * 2.0f * speed - 1.0f * speed;
	newParticle->SetVelocity(Vector(x, y, 0.0));

	//set emitter
	setEmitShape(emitShape::point);
	setParticlePos(newParticle);

	//spawn particle
	m_particleList.push_back(newParticle);
}

void ParticleSystem::setParticlePos(ParticleObject * obj)
{
	if (m_emitShape == emitShape::circle)
	{
		float radiusLimit = 50.0f;
		float limit = m_position.mVal[0];
		float angle = float(rand() / float(RAND_MAX / 360.0f));
		float radius = -radiusLimit * 2 + float(rand() / float(RAND_MAX / (radiusLimit * 4)));
		Vector temp = m_position;
		temp.mVal[0] = m_position.mVal[0] + radius * sin(angle);
		temp.mVal[1] = m_position.mVal[1] - radius * cos(angle);
		obj->SetPos(temp);		
	}
	else if (m_emitShape == emitShape::point)
	{
		obj->SetPos(m_position);
	}

	else if (m_emitShape == emitShape::square)
	{
		float limit = m_position.mVal[0];
		float x = rand()% int(m_position.mVal[0]) + limit - 250;
		float y = rand()% int(m_position.mVal[1]) + limit - 350;
		Vector temp = Vector(x, y, 0);
		obj->SetPos(temp);
	}
}

void ParticleSystem::update(float deltaTime)
{
	currentTime += deltaTime;
	if (currentTime >= emissionRate)
	{
		Spawn();
		currentTime = 0;
	}

	if (m_particleList.size() >= 1)
	{
		list<ParticleObject*>::iterator iter = m_particleList.begin();
		while (iter != m_particleList.end())
		{
			ParticleObject* po = *iter;
			
			if (po->getLife() <= 0)
			{
				iter = m_particleList.erase(iter);
			}
			else
			{
				list<ParticleAffector*>::iterator affectiter = m_affectorList.begin();
				while (affectiter != m_affectorList.end())
				{
					ParticleAffector* pa = *affectiter;
					pa->affectorUpdate(po,deltaTime);
					affectiter++;
				}
				po->update(deltaTime);
				++iter;
			}
		}
	}
}

void ParticleSystem::update2(float deltaTime)
{
	ParticleAffector* pa = new ParticleAffector(particleAffect::COLOR);
	m_affectorList.push_back(pa);

	currentTime += deltaTime;
	if (currentTime >= emissionRate)
	{
		Spawn();
		currentTime = 0;
	}

	if (m_particleList.size() >= 1)
	{
		list<ParticleObject*>::iterator iter = m_particleList.begin();
		while (iter != m_particleList.end())
		{
			ParticleObject* po = *iter;

			if (po->getLife() <= 0)
			{
				iter = m_particleList.erase(iter);
			}
			else
			{
				list<ParticleAffector*>::iterator affectiter = m_affectorList.begin();
				while (affectiter != m_affectorList.end())
				{
					ParticleAffector* pa = *affectiter;
					pa->affectorUpdate(po, deltaTime);
					affectiter++;
				}
				po->update(deltaTime);
				++iter;
			}
		}
	}
}


void ParticleSystem::update3(float deltaTime)
{
	ParticleAffector * pa = new ParticleAffector(particleAffect::SCALE);
	m_affectorList.push_back(pa);

	currentTime += deltaTime;
	if (currentTime >= emissionRate)
	{
		Spawn();
		currentTime = 0;
	}

	if (m_particleList.size() >= 1)
	{
		list<ParticleObject*>::iterator iter = m_particleList.begin();
		while (iter != m_particleList.end())
		{
			ParticleObject* po = *iter;

			if (po->getLife() <= 0)
			{
				iter = m_particleList.erase(iter);
			}
			else
			{
				list<ParticleAffector*>::iterator affectiter = m_affectorList.begin();
				while (affectiter != m_affectorList.end())
				{
					ParticleAffector* pa = *affectiter;
					pa->affectorUpdate(po, deltaTime);
					affectiter++;
				}
				po->update(deltaTime);
				++iter;
			}
		}
	}
}




void ParticleSystem::draw()
{
	if (m_particleList.size() >= 1)
	{
		list<ParticleObject*>::iterator iter = m_particleList.begin();
		while (iter != m_particleList.end())
		{
			(**iter).draw();
			++iter;
		}
	}
}

