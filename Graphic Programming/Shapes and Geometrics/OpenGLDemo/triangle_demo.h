#ifndef _TRIANGLE_DEMO_H
#define _TRIANGLE_DEMO_H

#include "demo_base.h"
#include <math.h>

class TriangleDemo : public DemoBase
{
private:
	float m_rotation;
	float m_speed;
public:
	void init()
	{
		m_rotation = 0.0f;
		m_speed = 0.0f;
	}

	void deinit()
	{
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

	void drawTriangle()
	{
		glBegin(GL_TRIANGLES);	
		// Drawing Using Triangles
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f( 1.0f, 1.0f, 0.0f);				
		glVertex3f( 1.0f,-1.0f, 0.0f);					
		glVertex3f( 2.0f,-1.0f, 0.0f);	
		glEnd();	
	}

	void drawRectangle()
	{
		glBegin(GL_TRIANGLES);
		//rectangle
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f( 1.0f, 1.0f, 0.0f);
		glVertex3f( 1.0f,-1.0f, 0.0f);
		glVertex3f( 2.0f,-1.0f, 0.0f);

		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(2.0f, 1.0f, 0.0f);
		glVertex3f(2.0f, -1.0f, 0.0f);
		glEnd();
	}
	void drawSquare()
	{
		glBegin(GL_TRIANGLES);
		//square
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);
		glEnd();
	}
	void drawCube()
	{
		glBegin(GL_TRIANGLES);
		//cube
		//front
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		//back
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		//left
		glColor3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		//right
		glColor3f(-0.5f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
	}

	void drawPyramid()
	{
		glBegin(GL_TRIANGLES);
		//pyramid
		//front
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		//right
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		//left
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		//back
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glEnd();
	}

	void drawCylinder()
	{
		int sides = 20;
		float radius = 1.0f;
		float height = 1.0f;	
		glColor3f(1.0f, 0.0f, 1.0f);
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i *(M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle
			glVertex3f(0.0f, height, 0.0f);
			glVertex3f(radius*cos(theta), height, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta), height, radius*sin(nextTheta));

			glVertex3f(0.0f, -height, 0.0f);
			glVertex3f(radius*cos(theta), -height, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta), -height, radius*sin(nextTheta));

			//Side Cylinder
			glVertex3f(radius*cos(theta), height, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta), height, radius*sin(nextTheta));
			glVertex3f(radius*cos(theta), -height, radius*sin(theta));

			glVertex3f(radius*cos(theta), -height, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta), -height, radius*sin(nextTheta));
			glVertex3f(radius*cos(nextTheta), height, radius*sin(nextTheta));

		}
		glEnd();
	}

	void drawSphere()
	{
		float x, y, z; // Storage for coordinates and angles        
		float radius = 1.0f;
		int sides = 20;

		for (float i = 0.0f; i < M_PI; i += M_PI / sides)
		{
			glBegin(GL_TRIANGLES);
			for (float j = 0.0f; j < 2.01*M_PI; j += M_PI / sides)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(radius * cos(j)*sin(i), radius * sin(j)*sin(i), radius * cos(i));
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides), radius * sin(j)*sin(i + M_PI / sides), radius * cos(i + M_PI / sides));

				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(radius * cos(j)*sin(i), radius * cos(i), radius * sin(j)*sin(i));
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides), radius * cos(i + M_PI / sides), radius * sin(j)*sin(i + M_PI / sides));
			}
			glEnd();
		}
	}

	void drawBothRectangle()
	{
		glBegin(GL_TRIANGLES);
		//front
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		//back
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-2.0f, 2.0f, -0.5f);
		glVertex3f(-2.0f, -2.0f, -0.5f);
		glVertex3f(2.0f, -2.0f, -0.5f);

		glVertex3f(-2.0f, 2.0f, -0.5f);
		glVertex3f(2.0f, 2.0f, -0.5f);
		glVertex3f(2.0f, -2.0f, -0.5f);

		
	}

	void draw(const Matrix& viewMatrix)
	{
		drawAxis(viewMatrix);

		//glLoadMatrixf((GLfloat*)viewMatrix.mVal);

		//enable wireframe mode
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		//drawAxis(viewMatrix);
		//auto rotation
		/*m_rotation += 5.0f;
		Matrix rotate1 = Matrix::makeRotateMatrix(m_rotation, Vector(0.0f, 1.0f, 0.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(5.0f, 0.0f, 0.0f);
		Matrix modelMatrix = rotate1 * translate1;*/

		//move up and down
		/*m_speed += 0.05f;
		Matrix modelMatrix = Matrix::makeTranslationMatrix(0.0f, cosf(m_speed)*2.0f, 0.0f);*/


		//move around origin point, move up and down
		m_speed += 0.05f;
		m_rotation += 1.0f;
		Matrix rotate1 = Matrix::makeRotateMatrix(m_rotation, Vector(0.0f, 1.0f, 0.0f));
		//Matrix move1 =  Matrix::makeTranslationMatrix(0.0f, cosf(m_speed)*1.5f, 0.0f); 
		Matrix translate1 = Matrix::makeTranslationMatrix(5.0f, 0.0f, 0.0f);
		Matrix modelMatrix = rotate1 * translate1;
		Matrix viewSpaceMatrix2 = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix2.mVal);
		drawPyramid(); 

		//move around origin point, move up and down, not perfect orbit
		/*m_rotation += 0.05f;
		Matrix move1 = Matrix::makeTranslationMatrix(cosf(m_rotation)*3.0f, 0.0f, sinf(m_rotation)*10.0f);
		Matrix modelMatrix = move1;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);*/

		//drawTriangle();
		//drawRectangle();
		//drawSquare();
		//drawCube();
		//drawPyramid();
		//drawCylinder();*/


		//1st 0bject- move around origin point, move up and down, not perfect orbit,
		//2nd object - rotate itself at origin
		/*m_rotation += 0.05f;
		Matrix move1 = Matrix::makeTranslationMatrix(cosf(m_rotation)*5.0f, 0.0f, sinf(m_rotation)*5.0f);
		Matrix modelMatrix = move1;
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
		drawPyramid();*/

		/*m_speed += 1.0f;
		Matrix rotate2 = Matrix::makeRotateMatrix(m_speed, Vector(0.0f, 1.0f, 0.0f));
		Matrix modelMatrix2 = rotate2;
		Matrix viewSpaceMatrix2 = viewMatrix * modelMatrix2;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix2.mVal);
		drawPyramid();*/

		//m_speed += 0.05f;
		//m_rotation += 2.0f;
		//for (int i = 1; i <20; i++)
		//{		
		//	Matrix translate1 = Matrix::makeTranslationMatrix(cosf(m_speed-i)*2.0f, 0.0f+i, sinf(m_speed-i)*2.0f);
		//	Matrix modelMatrix = translate1;
		//	Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		//	glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
		//	drawCube();	
		//}	

		/*for (int i = 1; i < 4; i++)
		{
			Matrix translate1 = Matrix::makeTranslationMatrix(sinf(m_speed-i)*2.0f, 0.0f, cosf(m_speed-i)*2.0f);
			Matrix rotate1 = Matrix::makeRotateMatrix(m_rotation, Vector(0.0f, 1.0f, 0.0f));
			Matrix modelMatrix = translate1* rotate1;
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawCube();
		}*/


		//drawTriangle();
		//drawSphere();
		//drawBothRectangle();
	}
};

#endif
