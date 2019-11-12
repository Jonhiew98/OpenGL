#include "pch.h"
#include <iostream>
#include "ParticleAffector.h"

ParticleAffector::ParticleAffector()
{

}

ParticleAffector::ParticleAffector(particleAffect pa)
{
	m_pa = pa;
}

float ParticleAffector::Lerp(float current, float start, float end)
{
	return (1 - current)*start + current * end;
}

void ParticleAffector::affectorUpdate(ParticleObject* obj, float deltaTime)
{
	if (m_pa == particleAffect::COLOR)
	{
		//red
		m_startColor = Color(1, 0, 0);
		//yellow
		m_endColor = Color(1, 1, 0);
		float current = obj->getLife() / obj->getMaxLife();
		Color temp = obj->getColor();
		temp.r = Lerp(current, m_startColor.r, m_endColor.r);
		temp.g = Lerp(current, m_startColor.g, m_endColor.g);
		temp.b = Lerp(current, m_startColor.b, m_endColor.b);

		obj->SetColor(temp);
	}

	else if (m_pa == particleAffect::ROTATION)
	{
		m_rotation = obj->GetRotation();
		m_rotation += deltaTime * 20.0f;
		obj->SetRotation(m_rotation);

	}
	else if (m_pa == particleAffect::SCALE)
	{
		m_scale = obj->GetScale();
		m_scale += deltaTime/ 10.0f;
		obj->SetScale(m_scale);
	}
	else if (m_pa == particleAffect::GRAVITY)
	{
		m_gravity = obj->getVelocity();
		m_gravity.mVal[1] -= deltaTime * 100.0f;
		obj->SetVelocity(m_gravity);
	}
}



