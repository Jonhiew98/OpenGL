#pragma once
#ifndef _PARTICLE_SYSTEM_

#include <iostream>
#include <list>
#include "ParticleObject.h"
#include "ParticleAffector.h"

using namespace std;

enum emitShape
{
	circle,
	square,
	point,
	none
};

class ParticleSystem
{
private:
	list<ParticleObject*> m_particleList;
	Sprite* m_sprites;
	float emissionRate;
	float currentTime = 0;

	float emissionCount;

	float particleLimit;
	float particleCount;

	Vector m_position;
	list<ParticleAffector*> m_affectorList;
	
	emitShape m_emitShape;

public:
	ParticleSystem(Sprite* sprite);

	void SetPos(Vector pos);
	Vector getPos();

	void setEmitShape(emitShape shape);
	emitShape getEmitShape();
	void setParticlePos(ParticleObject * obj);

	void update(float deltaTime);
	void update2(float deltaTime);
	void update3(float deltaTime);
	void Spawn();
	void draw(void);
};

#endif