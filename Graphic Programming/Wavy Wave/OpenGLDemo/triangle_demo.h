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
		result = m_fmodSystem->createStream("../media/Testing.mp3", FMOD_SOFTWARE, 0, &m_music);
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

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 20; i++)
		{
			glColor3f(1.0f, 0.3f, 0.3f);
			glVertex3f(-0.5f +i *0.6f , m_spectrumLeft[i] *2, 0.5f);
			glVertex3f(-0.5f +i * 0.6f, 0.0f *2, 0.5f );
			glVertex3f(0.0f + i * 0.6f, 0.0f *2, 0.5f );

			glVertex3f(0.0f + i * 0.6f, m_spectrumLeft[i] *2, 0.5f );
			glVertex3f(-0.5f + i *0.6f, m_spectrumLeft[i] *2, 0.5f );
			glVertex3f(0.0f + i * 0.6f, 0.0f *2, 0.5f );
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		for (int j = 0; j < 20; j++)
		{
			glColor3f(1.0f, 0.3f + m_spectrumLeft[j], 0.3f);
			glVertex3f(-0.5f + j * 0.6f, -m_spectrumLeft[j] * 2, 0.5f);
			glVertex3f(-0.5f + j * 0.6f, 0.0f * 2, 0.5f);
			glVertex3f(0.0f + j * 0.6f, 0.0f * 2, 0.5f);

			glVertex3f(0.0f + j * 0.6f, -m_spectrumLeft[j] * 2, 0.5f);
			glVertex3f(-0.5f + j * 0.6f, -m_spectrumLeft[j] * 2, 0.5f);
			glVertex3f(0.0f + j * 0.6f, 0.0f * 2, 0.5f);
		}
		glEnd();
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
				mRectTexCoor[vertex1 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex1 * 2 +1] = (float)(h) / (float)RECT_VERTICE_H * texMul;
				mRectVertices[vertex1 * 3] = -halfWidth + (float)(w) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex1 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex1 * 3] * xToRadianMul);
				mRectVertices[vertex1 * 3 + 2] = -halfHeight + (float)(h) / (float)RECT_VERTICE_H * height;


				//2nd vertex
				int vertex2 = ++currentVert;
				/*mRectTexCoor[vertex2 * 2] = 1.0f;
				mRectTexCoor[vertex2 * 2 + 1] = 0.0f;*/
				mRectTexCoor[vertex2 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex2 * 2 + 1] = (float)(h) / (float)RECT_VERTICE_H * texMul;
				mRectVertices[vertex2 * 3] = -halfWidth + (float)(w) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex2 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex2 * 3] * xToRadianMul);
				mRectVertices[vertex2 * 3 + 2] = -halfHeight + (float)(h + 1) / (float)RECT_VERTICE_H * height;

				//3rd vertex
				int vertex3 = ++currentVert;
				/*mRectTexCoor[vertex3 * 2] = 1.0f;
				mRectTexCoor[vertex3 * 2 + 1] = 1.0f;*/
				mRectTexCoor[vertex3 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex3 * 2 + 1] = (float)(h + 1) / (float)RECT_VERTICE_H * texMul;
				mRectVertices[vertex3 * 3] = -halfWidth + (float)(w + 1) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex3 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex3 * 3] * xToRadianMul);
				mRectVertices[vertex3 * 3 + 2] = -halfHeight + (float)(h + 1) / (float)RECT_VERTICE_H * height;


				//4th vertex
				int vertex4 = ++currentVert;
				/*mRectTexCoor[vertex4 * 2] = 1.0f;
				mRectTexCoor[vertex4 * 2 + 1] = 1.0f;*/
				mRectTexCoor[vertex4 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex4 * 2 + 1] = (float)(h + 1) / (float)RECT_VERTICE_H * texMul;
				mRectVertices[vertex4 * 3] = mRectVertices[vertex3 * 3];
				mRectVertices[vertex4 * 3 + 1] = mRectVertices[vertex3 * 3 + 1];
				mRectVertices[vertex4 * 3 + 2] = mRectVertices[vertex3 * 3 + 2];

				//5th vertex
				int vertex5 = ++currentVert;
				/*mRectTexCoor[vertex5 * 2] = 0.0f;
				mRectTexCoor[vertex5 * 2 + 1] = 1.0f;*/
				mRectTexCoor[vertex5 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex5 * 2 + 1] = (float)(h + 1) / (float)RECT_VERTICE_H * texMul;
				mRectVertices[vertex5 * 3] = -halfWidth + (float)(w + 1) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex5 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex5 * 3] * xToRadianMul);
				mRectVertices[vertex5 * 3 + 2] = -halfHeight + (float)(h) / (float)RECT_VERTICE_H * height;

				//6th vertex
				int vertex6 = ++currentVert;
				/*mRectTexCoor[vertex6 * 2] = 0.0f;
				mRectTexCoor[vertex6 * 2 + 1] = 0.0f;*/
				mRectTexCoor[vertex6 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
				mRectTexCoor[vertex6 * 2 + 1] = (float)(h) / (float)RECT_VERTICE_H * texMul;
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
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTextureID[2]);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, mRectVertices);
		glTexCoordPointer(2, GL_FLOAT, 0, mRectTexCoor);
		glDrawArrays(GL_TRIANGLES, 0, RECT_VERTEX_COUNT);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}


	void drawTriangle(void)
	{
		glBegin(GL_TRIANGLES);								// Drawing Using Triangles
					
			glColor3f(1.0f, 0.0f, 1.0f);

			glVertex3f( -0.5f, 0.5f, 0.0f);				
			glVertex3f( -0.5f,-0.5f, 0.0f);					
			glVertex3f( 0.5f,-0.5f, 0.0f);

			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(0.5f, 0.5f, 0.0f);
			glVertex3f(0.5f, -0.5f, 0.0f);
			glVertex3f(-0.5f, 0.5f, 0.0f);
						
		glEnd();	
	}

	void drawCube(void)
	{
		glBegin(GL_TRIANGLES);								// Drawing Using Triangles

		//! The front face
		glColor3f(0.0f, 1.0f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		//! The back face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		//! The left face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		//! The right face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		//! The top face
		glColor3f(0.5f, 0.0f, 0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		//! The bottom face
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glEnd();
	}

	void drawPyramid(void)
	{
		glBegin(GL_TRIANGLES);								// Drawing Using Triangles

		//! Front face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);		

		//! Back face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		//! Left face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		//! Right Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		//! Bottom left
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		//! Bottom Right
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glEnd();
	}

	void drawCylinder(void)
	{
		glBegin(GL_TRIANGLES);								// Drawing Using Triangles		
		
		//! Top circle
		for (int i = 0; i < 360; i++)
		{
			//! Top circle
			//glColor3f(1.0f, 0.0f, 0.0f);

			glVertex3f(0.0f, 2.0f, 0.0f);
			glVertex3f(0.0f + cos((180 + i) * M_PI / 180), 2.0f, 0.0f + sin((180 + i) * M_PI / 180));
			glVertex3f(0.0f + sin((i) * M_PI / 180), 2.0f, 0.0f + cos((180 + i) * M_PI / 180));

			//! Bottom Circle
			//glColor3f(0.0f, 1.0f, 0.0f);

			glVertex3f(0.0f, -2.0f, 0.0f);
			glVertex3f(0.0f + sin((270 + i) * M_PI / 180), -2.0f, 0.0f + sin((180 + i) * M_PI / 180));
			glVertex3f(0.0f + sin((i)* M_PI / 180), -2.0f, 0.0f + sin((270 + i) * M_PI / 180));

			//! Sides
			//glColor3f(0.0f, 0.0f, 1.0f);

			glVertex3f(sin((90 + i) * M_PI / 180), 2.0f,sin(i * M_PI / 180));
			glVertex3f(sin((90 + i) * M_PI / 180), -2.0f,sin(i * M_PI / 180));
			glVertex3f(sin(i * M_PI / 180), -2.0f,sin((90 + i) * M_PI / 180));

			glVertex3f(sin((90 + i) * M_PI / 180), 2.0f,sin(i * M_PI / 180));
			glVertex3f(sin(i * M_PI / 180), 2.0f,sin((90 + i) * M_PI / 180));
			glVertex3f(sin(i * M_PI / 180), -2.0f,sin((90 + i) * M_PI / 180));
		}

		glEnd();
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

	void drawSphere(void)
	{
#define X .525731112119133606 
#define Z .850650808352039932

		static GLfloat vdata[12][3] = {
			{ -X, 0.0, Z },{ X, 0.0, Z },{ -X, 0.0, -Z },{ X, 0.0, -Z },
		{ 0.0, Z, X },{ 0.0, Z, -X },{ 0.0, -Z, X },{ 0.0, -Z, -X },
		{ Z, X, 0.0 },{ -Z, X, 0.0 },{ Z, -X, 0.0 },{ -Z, -X, 0.0 }
		};
		static GLuint tindices[20][3] = {
			{ 0,4,1 },{ 0,9,4 },{ 9,5,4 },{ 4,5,8 },{ 4,8,1 },
		{ 8,10,1 },{ 8,3,10 },{ 5,3,8 },{ 5,2,3 },{ 2,7,3 },
		{ 7,10,3 },{ 7,6,10 },{ 7,11,6 },{ 11,0,6 },{ 0,1,6 },
		{ 6,1,10 },{ 9,0,11 },{ 9,11,2 },{ 9,2,5 },{ 7,2,11 } };
		int i;

		glBegin(GL_TRIANGLES);
		for (i = 0; i < 20; i++) {
			/* color information here */
			glVertex3fv(&vdata[tindices[i][0]][0]);
			glVertex3fv(&vdata[tindices[i][1]][0]);
			glVertex3fv(&vdata[tindices[i][2]][0]);
		}
		glEnd();
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

	void vertexCoor(void)
	{
		//create vertices data
		static GLfloat vertices[] =
		{
			-1.0f,-1.0f,1.0f,
			1.0f,-1.0f,1.0f,
			1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,
			-1.0f,1.0f,1.0f,
			-1.0f,-1.0f,1.0f
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
			255,255,255,
			255,255,255,
			255,255,255,
			255,255,255,
			255,255,255,
			255,255,255,
		};

		//glEnable(GL_BLEND);
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, mTextureID[0]);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices + 20);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void DrawBigRectanle(void)
	{
		glBegin(GL_TRIANGLES);

		//! The front face
		glTexCoord2d(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

		glTexCoord2d(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2d(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

		glEnd();
	}

	void DrawFrontBigRectangle(void)
	{
		glBegin(GL_TRIANGLES);

		//! The front face
		glTexCoord2d(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

		glTexCoord2d(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2d(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

		glEnd();
	}

	void DrawSmallBackground(void)
	{
		glBegin(GL_TRIANGLES);

		/*glTexCoord2d(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2d(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);

		glTexCoord2d(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2d(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);*/

		static float uShift = 0.0f;
		uShift += 0.01f;
		if (uShift > 1.0f)
		{
			uShift -= 1.0f;
		}
		//! The front face
		glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);

		glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

		glEnd();

		//! The back face
		glBegin(GL_TRIANGLES);
		glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);

		glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, mTextureID[3]);

		glBegin(GL_TRIANGLES);

		//! The left face
		glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

		glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

		//! The right face
		glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);

		glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, mTextureID[2]);

		glBegin(GL_TRIANGLES);

		//! The top face
		glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);

		glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, mTextureID[3]);

		glBegin(GL_TRIANGLES);

		//! The bottom face
		glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);

		glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);

		glEnd();
	}


	void draw(const Matrix& viewMatrix)
	{
		drawAxis(viewMatrix);


		glLoadMatrixf((GLfloat*)viewMatrix.mVal);

		//glLoadMatrixf((GLfloat*)viewMatrix.mVal);

		//enable wireframe mode
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		glColor3f(1.0f, 1.0f, 1.0f);
		
		glDisable(GL_BLEND);
		//DrawBigRectanle();
		//DrawFrontBigRectangle();

		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//DrawSmallBackground();
		glDepthMask(true);
		
		//vertexCoor();
		//updateFmod();
		drawWave();
	}
};

#endif
