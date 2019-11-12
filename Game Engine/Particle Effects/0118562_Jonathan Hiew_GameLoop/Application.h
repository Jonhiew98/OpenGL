#pragma once
#ifndef _APPLICATION_

#include "pch.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <windows.h>
#include "Sprite.h"
#include "GameObject.h"
#include "vector.h"
#include "ParticleSystem.h"

class Application
{
private:
	Sprite* m_dummySprite;
	GameObject* m_dummyObject;
	ParticleSystem* m_particleSystem;
	ParticleSystem* m_particleSystem2;
	ParticleSystem* m_particleSystem3;

public:
	void Start();
	void Update(float deltaTime);
	void Draw();
};

#endif


//float currentTime = 0;
//float lastTime = glfwGetTime();
//float frameCount = 0;
//float fps = 0;

////limit fps
//float targetFps = 1;
//float minDeltaTime = 1.0 / targetFps;

