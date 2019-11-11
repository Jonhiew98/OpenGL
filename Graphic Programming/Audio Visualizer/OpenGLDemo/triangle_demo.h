#ifndef _TRIANGLE_DEMO_H
#define _TRIANGLE_DEMO_H

#include "Math.h"

#include "demo_base.h"
#include "bitmap.h"
#include <fmod.hpp>
#include <fmod_errors.h>

#define TEXTURE_COUNT 4
#define SPECTRUM_SIZE 128

#define RECT_VERTICE_W 50
#define RECT_VERTICE_H 50

//every quad has 6 vertices
const int RECT_VERTEX_COUNT = (RECT_VERTICE_W - 1)*(RECT_VERTICE_H - 1) * 6;

//every vertex has 3 components(x,y,z)
const int RECT_VERTEX_ARRAY_SIZE = RECT_VERTEX_COUNT * 3;
//every textCoor had 2 components(x,y)
const int RECT_TEX_ARRAY_SIZE = RECT_VERTEX_COUNT * 2;


void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << "EMOD error! :" << FMOD_ErrorString(result) << std::endl;
	}
}

class TriangleDemo : public DemoBase
{
private:
	//texture
	float m_rotation;
	float m_speed;
	float m_speed2;
	GLuint mTextureID[TEXTURE_COUNT];

	//sound
	FMOD::System* m_fmodSystem;
	FMOD::Sound* m_music;
	FMOD::Channel *m_musicChannel;
	float m_spectrumLeft[SPECTRUM_SIZE];
	float m_spectrumRight[SPECTRUM_SIZE];

	//wave
	float mWaveRadianOffset;
	GLfloat mRectVertices[RECT_VERTEX_ARRAY_SIZE];
	GLfloat mRectTexCoor[RECT_TEX_ARRAY_SIZE];
	
	//random
	//GLfloat mRectVertices[18];

public:
	void initFmod()
	{
		FMOD_RESULT		result;
		unsigned int	version;

		result = FMOD::System_Create(&m_fmodSystem);
		ERRCHECK(result);

		result = m_fmodSystem->getVersion(&version);
		ERRCHECK(result);

		if (version < FMOD_VERSION)
		{
			std::cout << "FMOD Error! You are using old version of FMOD" << std::endl;
		}

		//initialize fmod system
		result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
		ERRCHECK(result);

		//load and set up music
		result = m_fmodSystem->createStream("../media/Alan Walker & Alex Skrindo - Sky.mp3", FMOD_SOFTWARE, 0, &m_music);
		ERRCHECK(result);

		//play the loaded mp3 music
		result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
		ERRCHECK(result);
	}

	void init()
	{
		initFmod();
		m_rotation = 0.0f;
		m_speed = 0.0f;

		glGenTextures(TEXTURE_COUNT, mTextureID);
		loadTexture("../media/rocks.bmp", mTextureID[0]);
		loadTexture("../media/glass.bmp", mTextureID[1]);
		loadTexture("../media/water.bmp", mTextureID[2]);
	}

	void deinit()
	{
	}

	void updateFmod()
	{
		m_fmodSystem->update();

		//Get spectrum for left and right stereo channels
		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

		//testing first frequency range
		std::cout << "left : " << m_spectrumLeft[0] << ", right:" << m_spectrumRight[0] << std::endl;
	}

	void drawAxis(const Matrix& viewMatrix)
	{
	// ============draw axis.
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);
		glBegin(GL_LINES);
			glColor3f(1.0f, 0.3f, 0.3f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

			glColor3f(0.3f, 1.0f, 0.3f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);

			glColor3f(0.3f, 0.3f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
		glEnd();
		// ============================
	}

	void genPlane(float offsetRadian)
	{
		const float width = 5.0f;
		const float height = 5.0f;
		const float halfWidth = width * 0.5f;
		const float halfHeight = height * 0.5f;

		const float waveAmpMul = 0.1f;
		const float xToRadianMul = 5.0f;

		const float texMul = 1.0f;

		int currentVert = -1;
		//int currentIndex = -1;
		for (int h = 0; h < RECT_VERTICE_H - 1; h++)
		{
			for (int w = 0; w < RECT_VERTICE_W - 1; w++)
			{
				//========= 6 vertices to form one sub-rectangle

				//1st vertex
				int vertex1 = ++currentVert;
				/*mRectTexCoor[vertex1 * 2] = 0.0f;
				mRectTexCoor[vertex1 * 2+1] = 0.0f;*/
				/*mRectTexCoor[vertex1 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex1 * 2 +1] = (float)(h) / (float)RECT_VERTICE_H * texMul;*/
				mRectVertices[vertex1 * 3] = -halfWidth + (float)(w) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex1 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex1 * 3] * xToRadianMul);
				mRectVertices[vertex1 * 3 + 2] = -halfHeight + (float)(h) / (float)RECT_VERTICE_H * height;


				//2nd vertex
				int vertex2 = ++currentVert;
				/*mRectTexCoor[vertex2 * 2] = 1.0f;
				mRectTexCoor[vertex2 * 2 + 1] = 0.0f;*/
				/*mRectTexCoor[vertex2 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex2 * 2 + 1] = (float)(h) / (float)RECT_VERTICE_H * texMul;*/
				mRectVertices[vertex2 * 3] = -halfWidth + (float)(w) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex2 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex2 * 3] * xToRadianMul);
				mRectVertices[vertex2 * 3 + 2] = -halfHeight + (float)(h + 1) / (float)RECT_VERTICE_H * height;

				//3rd vertex
				int vertex3 = ++currentVert;
				/*mRectTexCoor[vertex3 * 2] = 1.0f;
				mRectTexCoor[vertex3 * 2 + 1] = 1.0f;*/
				/*mRectTexCoor[vertex3 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex3 * 2 + 1] = (float)(h + 1) / (float)RECT_VERTICE_H * texMul;*/
				mRectVertices[vertex3 * 3] = -halfWidth + (float)(w + 1) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex3 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex3 * 3] * xToRadianMul);
				mRectVertices[vertex3 * 3 + 2] = -halfHeight + (float)(h + 1) / (float)RECT_VERTICE_H * height;


				//4th vertex
				int vertex4 = ++currentVert;
				/*mRectTexCoor[vertex4 * 2] = 1.0f;
				mRectTexCoor[vertex4 * 2 + 1] = 1.0f;*/
		/*		mRectTexCoor[vertex4 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex4 * 2 + 1] = (float)(h + 1) / (float)RECT_VERTICE_H * texMul;*/
				mRectVertices[vertex4 * 3] = mRectVertices[vertex3 * 3];
				mRectVertices[vertex4 * 3 + 1] = mRectVertices[vertex3 * 3 + 1];
				mRectVertices[vertex4 * 3 + 2] = mRectVertices[vertex3 * 3 + 2];

				//5th vertex
				int vertex5 = ++currentVert;
				/*mRectTexCoor[vertex5 * 2] = 0.0f;
				mRectTexCoor[vertex5 * 2 + 1] = 1.0f;*/
				/*mRectTexCoor[vertex5 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex5 * 2 + 1] = (float)(h + 1) / (float)RECT_VERTICE_H * texMul;*/
				mRectVertices[vertex5 * 3] = -halfWidth + (float)(w + 1) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex5 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex5 * 3] * xToRadianMul);
				mRectVertices[vertex5 * 3 + 2] = -halfHeight + (float)(h) / (float)RECT_VERTICE_H * height;

				//6th vertex
				int vertex6 = ++currentVert;
				/*mRectTexCoor[vertex6 * 2] = 0.0f;
				mRectTexCoor[vertex6 * 2 + 1] = 0.0f;*/
				/*mRectTexCoor[vertex6 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex6 * 2 + 1] = (float)(h) / (float)RECT_VERTICE_H * texMul;*/
				mRectVertices[vertex6 * 3] = mRectVertices[vertex1 * 3];
				mRectVertices[vertex6 * 3 + 1] = mRectVertices[vertex1 * 3 + 1];
				mRectVertices[vertex6 * 3 + 2] = mRectVertices[vertex1 * 3 + 2];
			}
		}
	}

	void drawWave()
	{
		mWaveRadianOffset += 0.01f;
		if (mWaveRadianOffset > 2.0f * M_PI)
			mWaveRadianOffset -= 2.0f * M_PI;
		genPlane(mWaveRadianOffset);

		glColor3f(1.0f, 1.0f, 1.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, mRectVertices);
		glTexCoordPointer(2, GL_FLOAT, 0, mRectTexCoor);
		glDrawArrays(GL_TRIANGLES, 0, RECT_VERTEX_COUNT);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	static float Remap(float from, float fromMin, float fromMax, float toMin, float toMax)
	{
		float fromAbs = from - fromMin;
		float fromMaxAbs = fromMax - fromMin;

		float normal = fromAbs / fromMax;

		float toMaxAbs = toMax - toMin;
		float toAbs = normal * toMax;
		float to = toAbs + toMin;

		return to;
	}

	void loadTexture(const char* path, GLuint textureID)
	{
		CBitmap bitmap(path);

		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//! Bilinear Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(),
		bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());		
	}

	void frontCube(float spectrumY,float mag)
	{
		//create vertices data
		GLfloat vertices[] =
		{
			//front
			-0.5f,-0.5f - spectrumY * mag,0.5f,
			0.5f,-0.5f - spectrumY * mag,0.5f,
			0.5f,0 + spectrumY * mag,0.5f,
			0.5f,0 + spectrumY * mag,0.5f,
			-0.5f,0 + spectrumY * mag,0.5f,
			-0.5f,-0.5f - spectrumY * mag,0.5f,

			//back side
			-0.5f, 0 + spectrumY * mag, -0.5f,
			-0.5f, -0.5f - spectrumY * mag, -0.5f,
			0.5f, -0.5f - spectrumY * mag, -0.5f,
			0.5f, 0 + spectrumY * mag, -0.5f,
			0.5f, -0.5f - spectrumY * mag, -0.5f,
			-0.5f, 0 + spectrumY * mag, -0.5f,

			//left
			-0.5f, 0 + spectrumY * mag, -0.5f,
			-0.5f, -0.5f - spectrumY * mag, -0.5f,
			-0.5f, -0.5f - spectrumY * mag, 0.5f,
			-0.5f, 0 + spectrumY * mag, 0.5f,
			-0.5f, -0.5f - spectrumY * mag, 0.5f,
			-0.5f, 0 + spectrumY * mag, -0.5f,

			//right 
			0.5f, 0 + spectrumY * mag, 0.5f,
			0.5f, -0.5f - spectrumY * mag, 0.5f,
			0.5f, -0.5f - spectrumY * mag, -0.5f,
			0.5f, 0 + spectrumY * mag, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, 0 + spectrumY * mag, 0.5f,

			//top 
			-0.5f, 0 + spectrumY * mag, -0.5f,
			-0.5f, 0 + spectrumY * mag, 0.5f,
			0.5f, 0 + spectrumY * mag, 0.5f,
			0.5f, 0 + spectrumY * mag, -0.5f,
			-0.5f, 0 + spectrumY * mag, -0.5f,
			0.5f, 0 + spectrumY * mag, 0.5f,

			//bottom 
			0.5f, -0.5f - spectrumY * mag, 0.5f,
			-0.5f, -0.5f - spectrumY * mag, -0.5f,
			-0.5f, -0.5f - spectrumY * mag, 0.5f,
			0.5f, -0.5f - spectrumY * mag, 0.5f,
			0.5f, -0.5f - spectrumY * mag, -0.5f,
			-0.5f, -0.5f - spectrumY * mag, -0.5f,
		};

		// create tex coordinate data
		static GLfloat texCoords[] =
		{
			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,
		};

		static GLubyte colors[] =
		{
			//top
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,

			//bottom
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,

			//left
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,

			//right
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,

			//top
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,

			//bottom
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,
			226, 88, 34,
			226, 120, 34,
		};
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	
	void middleCylinder(void)
	{
		static GLfloat cylinVertices[36*20];
		int sides = 20;
		float radius = 1.0f;
		float height = 1.0f;
		float spectrum;
		int vertexNum = 36;
		for (int i = 0; i < sides; i++)
		{			
			if (i < sides / 2)
			{
				spectrum = m_spectrumLeft[i] * 6;
			}
			else if (i >= sides / 2)
			{
				spectrum = m_spectrumRight[i] * 6;
			}
			if (spectrum > 0.3)
			{
				spectrum = 0.3;
			}

			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle		
			cylinVertices[(vertexNum * i)] = { 0.0f }; cylinVertices[(vertexNum * i + 1)] = { height }; cylinVertices[(vertexNum * i + 2)] = { 0.0f };
			cylinVertices[(vertexNum * i + 3)] = { radius*cos(theta) }; cylinVertices[(vertexNum * i + 4)] = { height - spectrum }; cylinVertices[(vertexNum * i + 5)] = { radius*sin(theta) };
			cylinVertices[(vertexNum * i + 6)] = { radius*cos(nextTheta) }; cylinVertices[(vertexNum * i + 7)] = { height - spectrum }; cylinVertices[(vertexNum * i + 8)] = { radius*sin(nextTheta)};

			cylinVertices[(vertexNum * i + 9)] = { 0.0f }; cylinVertices[(vertexNum * i + 10)] = { -height + spectrum }; cylinVertices[(vertexNum * i + 11)] = { 0.0f };
			cylinVertices[(vertexNum * i + 12)] = { radius*cos(theta) }; cylinVertices[(vertexNum * i + 13)] = { -height + spectrum }; cylinVertices[(vertexNum * i + 14)] = { radius*sin(theta)};
			cylinVertices[(vertexNum * i + 15)] = { radius*cos(nextTheta) }; cylinVertices[(vertexNum * i + 16)] = { -height + spectrum }; cylinVertices[(vertexNum * i + 17)] = { radius*sin(nextTheta)};

			//side cylinder		
			cylinVertices[(vertexNum * i + 18)] = { radius*cos(theta) }; cylinVertices[(vertexNum * i + 19)] = { height - spectrum }; cylinVertices[(vertexNum * i + 20)] = { radius*sin(theta)};
			cylinVertices[(vertexNum * i + 21)] = { radius*cos(nextTheta) }; cylinVertices[(vertexNum * i + 22)] = { height - spectrum }; cylinVertices[(vertexNum * i + 23)] = { radius*sin(nextTheta) };
			cylinVertices[(vertexNum * i + 24)] = { radius*cos(theta) }; cylinVertices[(vertexNum * i + 25)] = { -height + spectrum }; cylinVertices[(vertexNum * i + 26)] = { radius*sin(theta)};

			cylinVertices[(vertexNum * i + 27)] = { radius*cos(theta) }; cylinVertices[(vertexNum * i + 28)] = { -height + spectrum }; cylinVertices[(vertexNum * i + 29)] = { radius*sin(theta)};
			cylinVertices[(vertexNum * i + 30)] = { radius*cos(nextTheta) }; cylinVertices[(vertexNum * i + 31)] = { -height + spectrum }; cylinVertices[(vertexNum * i + 32)] = { radius*sin(nextTheta)};
			cylinVertices[(vertexNum * i + 33)] = { radius*cos(nextTheta) }; cylinVertices[(vertexNum * i + 34)] = { height - spectrum }; cylinVertices[(vertexNum * i + 35)] = { radius*sin(nextTheta)};
		}

		glColor3f(0.9f, 0.7f, 0.2f);
		
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, cylinVertices);
		//glColorPointer(3, GL_UNSIGNED_BYTE, 0, cylinderColor);

		glDrawArrays(GL_TRIANGLES, 0, 36*20/3);

		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void surroundPyramid(float offSetx, float offSetz,float spectrumY,float mag)
	{
		GLfloat vertices[] =
		{
			//Topfront
			0.0f + offSetx, 1.0f + spectrumY * mag, 1.5f + offSetz,
			0.0f + offSetx, 0.5f, 1.7f + offSetz,
			0.2f + offSetx, 0.5f, 1.7f + offSetz,
			0.0f + offSetx, 1.0f + spectrumY * mag, 1.5f + offSetz,
			0.0f + offSetx, 0.5f, 1.7f + offSetz,
			-0.2f + offSetx, 0.5f, 1.7f + offSetz,

			//Topright
			0.0f + offSetx, 1.0f + spectrumY * mag, 1.5f + offSetz,
			0.2f + offSetx, 0.5f, 1.5f + offSetz,
			0.2f + offSetx, 0.5f, 1.7f + offSetz,
			0.0f + offSetx, 1.0f + spectrumY * mag, 1.5f + offSetz,
			0.2f + offSetx, 0.5f, 1.7f + offSetz,
			0.2f + offSetx, 0.5f, 1.3f + offSetz,

			//Topleft
			0.0f + offSetx, 1.0f + spectrumY * mag, 1.5f + offSetz,
			-0.2f + offSetx, 0.5f, 1.5f + offSetz,
			-0.2f + offSetx, 0.5f, 1.7f + offSetz,
			0.0f + offSetx, 1.0f + spectrumY * mag, 1.5f + offSetz,
			-0.2f + offSetx, 0.5f, 1.7f + offSetz,
			-0.2f + offSetx, 0.5f, 1.3f + offSetz,

			//Topback
			0.0f + offSetx, 1.0f + spectrumY * mag, 1.5f + offSetz,
			0.0f + offSetx, 0.5f,  1.3f + offSetz,
			0.2f + offSetx, 0.5f,  1.3f + offSetz,
			0.0f + offSetx, 1.0f + spectrumY * mag, 1.5f + offSetz,
			0.0f + offSetx, 0.5f, 1.3f + offSetz,
			-0.2f + offSetx, 0.5f,  1.3f + offSetz,

			//bottomfront
			0.0f + offSetx, 0.0f - spectrumY * mag, 1.5f + offSetz,
			0.0f + offSetx, 0.5f, 1.7f + offSetz,
			0.2f + offSetx, 0.5f, 1.7f + offSetz,
			0.0f + offSetx, 0.0f - spectrumY * mag, 1.5f + offSetz,
			0.0f + offSetx, 0.5f, 1.7f + offSetz,
			-0.2f + offSetx, 0.5f, 1.7f + offSetz,

			//bottomright
			0.0f + offSetx, 0.0f - spectrumY * mag, 1.5f + offSetz,
			0.2f + offSetx, 0.5f, 1.5f + offSetz,
			0.2f + offSetx, 0.5f, 1.7f + offSetz,
			0.0f + offSetx, 0.0f - spectrumY * mag, 1.5f + offSetz,
			0.2f + offSetx, 0.5f, 1.7f + offSetz,
			0.2f + offSetx, 0.5f, 1.3f + offSetz,

			//bottomleft
			0.0f + offSetx, 0.0f - m_spectrumRight[0] * mag, 1.5f + offSetz,
			-0.2f + offSetx, 0.5f, 1.5f + offSetz,
			-0.2f + offSetx, 0.5f, 1.7f + offSetz,
			0.0f + offSetx, 0.0f - m_spectrumRight[0] * mag, 1.5f + offSetz,
			-0.2f + offSetx, 0.5f, 1.7f + offSetz,
			-0.2f + offSetx, 0.5f, 1.3f + offSetz,

			//bottomback
			0.0f + offSetx, 0.0f - m_spectrumRight[0] * mag, 1.5f + offSetz,
			0.0f + offSetx, 0.5f,  1.3f + offSetz,
			0.2f + offSetx, 0.5f,  1.3f + offSetz,
			0.0f + offSetx, 0.0f - m_spectrumRight[0] * mag, 1.5f + offSetz,
			0.0f + offSetx, 0.5f, 1.3f + offSetz,
			-0.2f + offSetx, 0.5f,  1.3f + offSetz,
		};

		// create tex coordinate data
		static GLfloat texCoords[] =
		{
			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,
		};

		static GLubyte colors[] =
		{
			//TopFront
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,

			//Topright
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,

			//Topleft
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,

			//BottomFront
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,

			//BottomRight
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,

			//BottomLeft
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,

			//BottomBack
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,

			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,
			226, 88, 34,
			226, 184, 34,
		};
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

		glDrawArrays(GL_TRIANGLES, 0, 48);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void surroundRotateDiamond(const Matrix& viewMatrix)
	{
		m_speed += 0.005f;
		for (int i = 0; i < 6; i++)
		{
			Matrix translate1 = Matrix::makeTranslationMatrix(cosf(m_speed + 0.1f - i)*5.0f, 0.0f, -1.5f+ sinf(m_speed + 0.1f - i)*5.0f);
			Matrix rotate1 = Matrix::makeRotateMatrix(m_rotation, Vector(0.0f, 1.0f, 0.0f));
			Matrix modelMatrix = translate1 * rotate1;
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			surroundPyramid(0, 0, m_spectrumLeft[i],1.0);
		}
	}

	void surroundRotateDiamond2(const Matrix& viewMatrix)
	{
		m_speed += 0.005f;
		m_rotation += 0.005f;
		for (int i = 0; i < 46; i++)
		{
			Matrix translate1 = Matrix::makeTranslationMatrix(sinf(m_speed - i)*10.0f, 0.0f, -1.5f + cosf(m_speed - i)*10.0f);
			Matrix rotate1 = Matrix::makeRotateMatrix(m_rotation, Vector(0.0f, 1.0f, 0.0f));
			Matrix modelMatrix = translate1 * rotate1;
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			surroundPyramid(0, 0, m_spectrumLeft[0], 0.5);
		}
	}

	void surroundSquare(const Matrix& viewMatrix)
	{
		m_speed2 += 1.0f;
		for (int i = 0; i < 12; i++)
		{
			Matrix translates2 = Matrix::makeTranslationMatrix(Vector(0,0,3));
			Matrix rotate2 = Matrix::makeRotateMatrix(i * 30, Vector(0.0f, 1.0f, 0.0f));
			Matrix rotates2 = Matrix::makeRotateMatrix(1.5f - m_speed2, Vector(0.0f, 1.0f, 0.0f));
			Matrix modelMatrix2 = rotate2 * rotates2 * translates2;
			Matrix viewSpaceMatrix2 = viewMatrix * modelMatrix2;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix2.mVal);
			frontCube(m_spectrumRight[i], 3);
		}
	}

	void surroundSquare2(const Matrix& viewMatrix)
	{
		m_speed2 += 1.0f;
		for (int i = 0; i < 20; i++)
		{
			Matrix translates2 = Matrix::makeTranslationMatrix(Vector(0, 0, 7));
			Matrix rotate2 = Matrix::makeRotateMatrix(i * 18, Vector(0.0f, 1.0f, 0.0f));
			Matrix rotates2 = Matrix::makeRotateMatrix(m_speed2, Vector(0.0f, 1.0f, 0.0f));
			Matrix modelMatrix2 = rotate2 * rotates2 * translates2;
			Matrix viewSpaceMatrix2 = viewMatrix * modelMatrix2;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix2.mVal);
			frontCube(m_spectrumRight[0], 1);
		}
	}

	void all(const Matrix& viewMatrix)
	{		
		middleCylinder();
		surroundSquare(viewMatrix);
		surroundSquare2(viewMatrix);
		surroundRotateDiamond(viewMatrix);		
		surroundRotateDiamond2(viewMatrix);	
	}

	void draw(const Matrix& viewMatrix)
	{
		drawAxis(viewMatrix);
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);

		//enable wireframe mode
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthMask(true);
			
		updateFmod();
		all(viewMatrix);
	}
};

#endif


