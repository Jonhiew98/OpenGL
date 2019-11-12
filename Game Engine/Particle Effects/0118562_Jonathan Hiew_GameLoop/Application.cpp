#include "pch.h"
#include <iostream>
#include "Application.h"

using namespace std;

void Application::Start()
{
	cout << "Application is started" << endl;
	//sprite
	m_dummySprite = new Sprite("../Media/Particles2.bmp");

	//gameObject
	m_dummyObject = new GameObject(m_dummySprite);
	/*m_dummyObject->SetPos(Vector(540, 360, 0));
	m_dummyObject->SetRotation(50.0f);
	m_dummyObject->SetScale(2.0f);*/

	//particleObject
	m_particleSystem = new ParticleSystem(m_dummySprite);
	m_particleSystem->SetPos(Vector(540, 360, 0));
}

void Application::Update(float deltaTime)
{	
	//cout << "Update" << endl;
	m_particleSystem->update(deltaTime);
}

void Application::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	////Sprite
	//m_dummySprite->Draw(540, 360, 50.0f, 2.0f, Color(1.0f, 0.0f, 0.0f));

	////GameObject
	//m_dummyObject->draw();

	//////Blend effect
	////Additive
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	////ADDITIVE_ALPHA
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	m_particleSystem->draw();
}