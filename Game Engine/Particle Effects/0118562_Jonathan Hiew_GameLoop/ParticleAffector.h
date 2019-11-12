#pragma once
#ifndef _PARTICLE_AFFECTOR_

#include <vector>
#include <iostream>
#include <list>
#include "ParticleObject.h"
using namespace std;

enum particleAffect
{
	COLOR,
	ROTATION,
	SCALE,
	GRAVITY,
};

class ParticleAffector
{
private:
	//Color
	Color m_startColor;
	Color m_endColor;

	//rotate
	float m_rotation;

	//scale
	float m_scale;

	//gravity
	Vector m_gravity;

	particleAffect m_pa;

public:
	ParticleAffector();
	ParticleAffector(particleAffect pa);

	void affectorUpdate(ParticleObject* pa, float deltaTime);
	float Lerp(float current, float start, float end);
};

#endif