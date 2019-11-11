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

	void upperrightshoulder()
	{
		glBegin(GL_TRIANGLES);
		// top
		glColor3f(0.5f, 0.35f, 0.05f);
		glVertex3f(2.5f, 1.5f, -0.7f);
		glVertex3f(2.5f, 1.5f, 0.7f);
		glVertex3f(0.75f, 1.5f, 0.7f);

		glVertex3f(2.5f, 1.5f, -0.7f);
		glVertex3f(0.5f, 1.5f, -0.7f);
		glVertex3f(0.75f, 1.5f, 0.7f);

		//front
		glColor3f(0.5f, 0.35f, 0.05f);
		glVertex3f(2.5f, 1.5f, 0.7f);
		glVertex3f(0.5f, 1.5f, 0.7f);
		glVertex3f(0.75f, 0.0f, 0.7f);

		//back
		glColor3f(0.5f, 0.35f, 0.05f);
		glVertex3f(2.5f, 1.5f, -0.7f);
		glVertex3f(0.5f, 1.5f, -0.7f);
		glVertex3f(0.75f, 0.0f, -0.7f);

		//left
		glColor3f(0.5f, 0.35f, 0.05f);
		glVertex3f(2.5f, 1.5f, -0.7f);
		glVertex3f(0.75f, 0.0f, -0.7f);
		glVertex3f(0.75f, 0.0f, 0.7f);

		glVertex3f(2.5f, 1.5f, -0.7f);
		glVertex3f(0.75f, 1.5f, 0.7f);
		glVertex3f(0.75f, 0.0f, 0.7f);

		glEnd();
	}

	void upperleftshoulder()
	{
		glBegin(GL_TRIANGLES);
		// top
		glColor3f(0.5f, 0.35f, 0.05f);
		glVertex3f(-2.5f, 1.5f, -0.7f);
		glVertex3f(-2.5f, 1.5f, 0.7f);
		glVertex3f(-0.75f, 1.5f, 0.7f);

		glVertex3f(-2.5f, 1.5f, -0.7f);
		glVertex3f(-0.75f, 1.5f, -0.7f);
		glVertex3f(-0.75f, 1.5f, 0.7f);

		//front
		glColor3f(0.5f, 0.35f, 0.05f);
		glVertex3f(-2.5f, 1.5f, 0.7f);
		glVertex3f(-0.5f, 1.5f, 0.7f);
		glVertex3f(-0.75f, 0.0f, 0.7f);

		//back
		glColor3f(0.5f, 0.35f, 0.05f);
		glVertex3f(-2.5f, 1.5f, -0.7f);
		glVertex3f(-0.5f, 1.5f, -0.7f);
		glVertex3f(-0.75f, 0.0f, -0.7f);

		//right
		glColor3f(0.5f, 0.35f, 0.05f);
		glVertex3f(-2.5f, 1.5f, -0.7f);
		glVertex3f(-0.75f, 0.0f, -0.7f);
		glVertex3f(-0.75f, 0.0f, 0.7f);

		glVertex3f(-2.5f, 1.5f, -0.7f);
		glVertex3f(-0.75f, 1.5f, 0.7f);
		glVertex3f(-0.75f, 0.0f, 0.7f);
		glEnd();
	}

	void upperlefthand()
	{
		int sides = 20;
		float radius = 0.3f;
		float height = 1.0f;
		glColor3f(0.5f, 0.35f, 0.05f);
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle
			glVertex3f(-1.0f, height, 0.0f);
			glVertex3f(radius*cos(theta) - 1.0f, height, radius*sin(theta) );
			glVertex3f(radius*cos(nextTheta) - 1.0f, height, radius*sin(nextTheta) );

			glVertex3f(-1.5f, -height, 0.0f);
			glVertex3f(radius*cos(theta) - 1.5f, -height, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta) - 1.5f, -height, radius*sin(nextTheta) );

			//Side Cylinder
			glVertex3f(radius*cos(theta) - 1.0f, height, radius*sin(theta) );
			glVertex3f(radius*cos(nextTheta) - 1.0f, height, radius*sin(nextTheta) );
			glVertex3f(radius*cos(theta) - 1.5f, -height, radius*sin(theta));

			glVertex3f(radius*cos(theta) - 1.5f, -height, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta) - 1.5f, -height, radius*sin(nextTheta));
			glVertex3f(radius*cos(nextTheta) - 1.0f, height, radius*sin(nextTheta));

		}
		glEnd();
	}

	void upperrighthand()
	{
		int sides = 20;
		float radius = 0.3f;
		float height = 0.8f;
		glColor3f(0.5f, 0.35f, 0.05f);
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle
			glVertex3f(1.0f, height , 0.0f);
			glVertex3f(radius*cos(theta)+ 1.0f, height , radius*sin(theta));
			glVertex3f(radius*cos(nextTheta)+ 1.0f, height , radius*sin(nextTheta));

			glVertex3f(1.5f, -height, 1.5f);
			glVertex3f(radius*cos(theta) + 1.5f, -height , radius*sin(theta)+ 1.5f);
			glVertex3f(radius*cos(nextTheta) + 1.5f, -height , radius*sin(nextTheta)+ 1.5f);

			//Side Cylinder
			glVertex3f(radius*cos(theta)+ 1.0f, height , radius*sin(theta));
			glVertex3f(radius*cos(nextTheta)+1.0f, height , radius*sin(nextTheta));
			glVertex3f(radius*cos(theta) + 1.5f, -height , radius*sin(theta)+1.5f);

			glVertex3f(radius*cos(theta) + 1.5f, -height , radius*sin(theta)+ 1.5f);
			glVertex3f(radius*cos(nextTheta) + 1.5f, -height , radius*sin(nextTheta)+ 1.5f);
			glVertex3f(radius*cos(nextTheta)+ 1.0f, height , radius*sin(nextTheta));

		}
		glEnd();
	}

	void lowerrighthand()
	{
		int sides = 20;
		float radius = 0.3f;
		float length = 1.0f;
		glColor3f(0.5f, 0.35f, 0.05f);
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle
			glVertex3f(1.5f, -0.3f, length + 2.3f);
			glVertex3f(radius*cos(theta) + 1.5f, radius*sin(theta) - 0.3f, length +2.3f);
			glVertex3f(radius*cos(nextTheta) + 1.5f, radius*sin(nextTheta) - 0.3f,length + 2.3f);

			glVertex3f(1.5f, -0.6f, -length +2.3f);
			glVertex3f(radius*cos(theta) + 1.5f, radius*sin(theta) - 0.6f, -length + 2.3f);
			glVertex3f(radius*cos(nextTheta) + 1.5f, radius*sin(nextTheta) - 0.6f, -length + 2.3f);

			//Side Cylinder
			glVertex3f(radius*cos(theta) + 1.5f, radius*sin(theta) - 0.3f, length + 2.3f);
			glVertex3f(radius*cos(nextTheta) + 1.5f, radius*sin(nextTheta) - 0.3f, length + 2.3f);
			glVertex3f(radius*cos(theta) + 1.5f, radius*sin(theta) - 0.6f, -length + 2.3f);

			glVertex3f(radius*cos(theta) + 1.5f, radius*sin(theta) - 0.6f, -length + 2.3f);
			glVertex3f(radius*cos(nextTheta) + 1.5f, radius*sin(nextTheta) - 0.6f, -length + 2.3f);
			glVertex3f(radius*cos(nextTheta) + 1.5f, radius*sin(nextTheta) - 0.3f, length + 2.3f);

		}
		glEnd();
	}

	void lowerlefthand()
	{
		int sides = 20;
		float radius = 0.3f;
		float length = 1.0f;
		glColor3f(0.5f, 0.35f, 0.05f);
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle
			glVertex3f(-1.5f, -1.0f, length + 0.75f);
			glVertex3f(radius*cos(theta) - 1.5f, radius*sin(theta) - 1.0f, length + 0.75f);
			glVertex3f(radius*cos(nextTheta) - 1.5f, radius*sin(nextTheta) - 1.0f, length + 0.75f);

			glVertex3f(-1.5f, -1.0f, -length + 1.0f);
			glVertex3f(radius*cos(theta) - 1.5f, radius*sin(theta) - 1.0f, -length +0.75f);
			glVertex3f(radius*cos(nextTheta) - 1.5f, radius*sin(nextTheta) - 1.0f, -length  +0.75f);

			//Side Cylinder
			glVertex3f(radius*cos(theta) - 1.5f, radius*sin(theta) - 1.0f, length + 0.75f);
			glVertex3f(radius*cos(nextTheta) - 1.5f, radius*sin(nextTheta) - 1.0f, length + 0.75f);
			glVertex3f(radius*cos(theta) - 1.5f, radius*sin(theta) - 1.0f, -length + 0.75f);

			glVertex3f(radius*cos(theta) - 1.5f, radius*sin(theta) - 1.0f, -length + 0.75f);
			glVertex3f(radius*cos(nextTheta) - 1.5f, radius*sin(nextTheta) - 1.0f, -length + 0.75f);
			glVertex3f(radius*cos(nextTheta) - 1.5f, radius*sin(nextTheta) - 1.0f, length + 0.75f);

		}
		glEnd();
	}

	void lefthand()
	{
		glBegin(GL_TRIANGLES);
		//front
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.95f, -0.65f, 1.75f);
		glVertex3f(-1.95f, -1.35f, 1.75f);
		glVertex3f(-1.15f, -1.35f, 1.75f);

		glVertex3f(-1.95f, -0.65f, 1.75f);
		glVertex3f(-1.15f, -0.65f, 1.75f);
		glVertex3f(-1.15f, -1.35f, 1.75f);

		//back
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.95f, -0.65f, 1.25f);
		glVertex3f(-1.95f, -1.35f, 1.25f);
		glVertex3f(-1.15f, -1.35f, 1.25f);

		glVertex3f(-1.95f, -0.64f, 1.25f);
		glVertex3f(-1.15f, -0.64f, 1.25f);
		glVertex3f(-1.15f, -1.35f, 1.25f);

		//left
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.95f, -0.65f, 1.25f);
		glVertex3f(-1.95f, -1.35f, 1.25f);
		glVertex3f(-1.95f, -1.35f, 1.75f);

		glVertex3f(-1.95f, -0.65f, 1.25f);
		glVertex3f(-1.95f, -0.65f, 1.75f);
		glVertex3f(-1.95f, -1.35f, 1.75f);

		//right
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.15f, -0.65f, 1.25f);
		glVertex3f(-1.15f, -1.35f, 1.25f);
		glVertex3f(-1.15f, -1.35f, 1.75f);

		glVertex3f(-1.15f, -0.65f, 1.25f);
		glVertex3f(-1.15f, -0.65f, 1.75f);
		glVertex3f(-1.15f, -1.35f, 1.75f);

		//top
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.95f, -0.65f, 1.25f);
		glVertex3f(-1.95f, -0.65f, 1.75f);
		glVertex3f(-1.15f, -0.65f, 1.75f);

		glVertex3f(-1.15f, -0.65f, 1.75f);
		glVertex3f(-1.15f, -0.65f, 1.25f);
		glVertex3f(-1.95f, -0.65f, 1.25f);

		//bottom
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.95f, -1.35f, 1.25f);
		glVertex3f(-1.95f, -1.35f, 1.75f);
		glVertex3f(-1.15f, -1.35f, 1.75f);

		glVertex3f(-1.15f, -1.35f, 1.75f);
		glVertex3f(-1.15f, -1.35f, 1.25f);
		glVertex3f(-1.95f, -1.35f, 1.25f);
		glEnd();
	}

	void righthand()
	{
		glBegin(GL_TRIANGLES);
		//front
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.85f, 0.0f, 3.45f);
		glVertex3f(1.85f, -0.5f, 3.45f);
		glVertex3f(1.05f, -0.5f, 3.45f);

		glVertex3f(1.85f, 0.0f, 3.45f);
		glVertex3f(1.05f, 0.2f, 3.45f);
		glVertex3f(1.05f, -0.5f, 3.45f);

		//back
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.85f, 0.2f, 3.05f);
		glVertex3f(1.85f, -0.7f, 3.05f);
		glVertex3f(1.05f, -0.7f, 3.05f);

		glVertex3f(1.85f, 0.2f, 3.05f);
		glVertex3f(1.05f, 0.2f, 3.05f);
		glVertex3f(1.05f, -0.7f, 3.05f);

		//left
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.85f, 0.2f, 3.05f);
		glVertex3f(1.85f, -0.7f, 3.05f);
		glVertex3f(1.85f, -0.5f, 3.45f);

		glVertex3f(1.85f, 0.2f, 3.05f);
		glVertex3f(1.85f, 0.0f, 3.45f);
		glVertex3f(1.85f, -0.7f, 3.45f);

		//right
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.05f, 0.2f, 3.05f);
		glVertex3f(1.05f, -0.7f, 3.05f);
		glVertex3f(1.05f, -0.7f, 3.45f);

		glVertex3f(1.05f, 0.2f, 3.05f);
		glVertex3f(1.05f, 0.2f, 3.45f);
		glVertex3f(1.05f, -0.7f, 3.45f);

		//top
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.85f, 0.2f, 3.05f);
		glVertex3f(1.85f, 0.2f, 3.45f);
		glVertex3f(1.05f, 0.2f, 3.45f);

		glVertex3f(1.05f, 0.2f, 3.45f);
		glVertex3f(1.05f, 0.2f, 3.05f);
		glVertex3f(1.85f, 0.2f, 3.05f);

		//bottom
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.85f, -0.7f, 3.05f);
		glVertex3f(1.85f, -0.7f, 3.45f);
		glVertex3f(1.05f, -0.7f, 3.45f);

		glVertex3f(1.05f, -0.7f, 3.45f);
		glVertex3f(1.05f, -0.7f, 3.05f);
		glVertex3f(1.85f, -0.7f, 3.05f);
		glEnd();
	}

	void waist()
	{
		int sides = 20;
		float radius = 0.5f;
		float height = 0.1f;
		glColor3f(0.5f, 0.5f, 0.5f);
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle
			glVertex3f(0.0f, height - 0.6f, 0.0f);
			glVertex3f(radius*cos(theta), height - 0.6f, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta), height - 0.6f, radius*sin(nextTheta));

			glVertex3f(0.0f, -height - 0.6f, 0.0f);
			glVertex3f(radius*cos(theta), -height - 0.6f, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta), -height - 0.6f, radius*sin(nextTheta));

			//Side Cylinder
			glVertex3f(radius*cos(theta), height - 0.6f, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta), height - 0.6f, radius*sin(nextTheta));
			glVertex3f(radius*cos(theta), -height - 0.6f, radius*sin(theta));

			glVertex3f(radius*cos(theta), -height - 0.6f, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta), -height - 0.6f, radius*sin(nextTheta));
			glVertex3f(radius*cos(nextTheta), height - 0.6f, radius*sin(nextTheta));

		}
		glEnd();
		
	}

	void lowerwaist()
	{
		int sides = 20;
		float radius = 0.5f;
		float radius2 = 1.5f;
		float height = 0.5f;
		glColor3f(0.87f, 0.58f, 0.98f);
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle
			glVertex3f(0.0f, height - 1.2f, 0.0f);
			glVertex3f(radius*cos(theta), height - 1.2f, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta), height - 1.2f, radius*sin(nextTheta));

			glVertex3f(0.0f, -height - 1.4f, 0.0f);
			glVertex3f(radius2*cos(theta), -height - 1.4f, radius2*sin(theta));
			glVertex3f(radius2*cos(nextTheta), -height - 1.4f, radius2*sin(nextTheta));

			//Side Cylinder
			glVertex3f(radius*cos(theta), height - 1.2f, radius*sin(theta));
			glVertex3f(radius*cos(nextTheta), height - 1.2f, radius*sin(nextTheta));
			glVertex3f(radius2*cos(theta), -height - 1.4f, radius2*sin(theta));

			glVertex3f(radius2*cos(theta), -height - 1.4f, radius2*sin(theta));
			glVertex3f(radius2*cos(nextTheta), -height - 1.4f, radius2*sin(nextTheta));
			glVertex3f(radius*cos(nextTheta), height - 1.2f, radius*sin(nextTheta));

		}
		glEnd();
	}

	void head()
	{
		float x, y, z; // Storage for coordinates and angles        
		float radius = 0.9f;
		int sides = 20;
		//roundhead
		for (float i = 0.0f; i < M_PI; i += M_PI / sides)
		{
			glBegin(GL_TRIANGLES);
			glColor3f(0.5f, 0.35f, 0.05f);
			for (float j = 0.0f; j < 2.01*M_PI; j += M_PI / sides)
			{				
				glVertex3f(0.0f, 2.0f, 0.3f);
				glVertex3f(radius * cos(j)*sin(i), radius * sin(j)*sin(i)+2.0f, radius * cos(i)+0.3f);
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides), radius * sin(j)*sin(i + M_PI / sides) + 2.0f, radius * cos(i + M_PI / sides) + 0.3f);

				glVertex3f(0.0f, 2.0f, 0.3f);
				glVertex3f(radius * cos(j)*sin(i), radius * cos(i) + 2.0f, radius * sin(j)*sin(i) + 0.3f);
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides), radius * cos(i + M_PI / sides) + 2.0f, radius * sin(j)*sin(i + M_PI / sides) + 0.3f);
			}			
		}

		//topfront
		glColor3f(0.5f, 0.35f, 0.05f);
		glVertex3f(-0.15f, 2.0f, 1.2f);
		glVertex3f(-0.15f, 3.5f, 0.7f);
		glVertex3f(0.15f, 3.5f, 0.7f);

		glVertex3f(-0.15f, 2.0f, 1.2f);
		glVertex3f(0.15f, 2.0f, 1.2f);
		glVertex3f(0.15f, 3.5f, 0.7f);

		//topleft
		glVertex3f(-0.55f, 2.0f, 0.9f);
		glVertex3f(-0.55f, 3.2f, 0.5f);
		glVertex3f(-0.25f, 3.3f, 0.7f);

		glVertex3f(-0.55f, 2.0f, 0.9f);
		glVertex3f(-0.25f, 2.0f, 1.2f);
		glVertex3f(-0.25f, 3.3f, 0.7f);

		//topleftleft
		glVertex3f(-0.95f, 2.0f, 0.0f);
		glVertex3f(-0.95f, 2.9f, 0.1f);
		glVertex3f(-0.65f, 3.0f, 0.4f);

		glVertex3f(-0.95f, 2.0f, 0.0f);
		glVertex3f(-0.65f, 2.0f, 0.7f);
		glVertex3f(-0.65f, 3.0f, 0.4f);

		//topright
		glVertex3f(0.25f, 2.0f, 1.2f);
		glVertex3f(0.25f, 3.3f, 0.7f);
		glVertex3f(0.55f, 3.2f, 0.5f);

		glVertex3f(0.25f, 2.0f, 1.2f);
		glVertex3f(0.55f, 2.0f, 0.7f);
		glVertex3f(0.55f, 3.2f, 0.5f);

		//toprightright
		glVertex3f(0.65f, 2.0f, 0.7f);
		glVertex3f(0.65f, 3.0f, 0.5f);
		glVertex3f(0.95f, 2.9f, 0.25f);

		glVertex3f(0.65f, 2.0f, 0.7f);
		glVertex3f(0.95f, 2.0f, 0.25f);
		glVertex3f(0.95f, 2.9f, 0.25f);

		//lefteyes
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-0.65f, 1.8f, 0.95f);
		glVertex3f(-0.65f, 2.2f, 0.95f);
		glVertex3f(-0.25f, 2.1f, 1.2f);

		glVertex3f(-0.65f, 1.8f, 0.95f);
		glVertex3f(-0.25f, 1.7f, 1.2f);
		glVertex3f(-0.25f, 2.1f, 1.2f);

		//righteyes
		glVertex3f(0.6f, 1.8f, 1.0f);
		glVertex3f(0.6f, 2.2f, 1.0f);
		glVertex3f(0.2f, 2.1f, 1.2f);

		glVertex3f(0.6f, 1.8f, 1.0f);
		glVertex3f(0.2f, 1.7f, 1.2f);
		glVertex3f(0.2f, 2.1f, 1.2f);
		
		glEnd();
	}

	void lefteyeball()
	{
		//lefteyeball
		int sides = 20;
		float radius = 0.1f;
		float length = 1.0f;
		glColor3f(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle
			glVertex3f(-0.35f, 1.85f, length + 0.2f);
			glVertex3f(radius*cos(theta) - 0.35f, radius + 0.2f*sin(theta) + 1.8f, length + 0.2f);
			glVertex3f(radius*cos(nextTheta) - 0.35f, radius + 0.2f*sin(nextTheta) + 1.8f, length + 0.2f);
		}
		glEnd();
	}

	void righteyeball()
	{
		//righteyeball
		int sides = 20;
		float radius = 0.1f;
		float length = 1.0f;		
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.3f, 1.8f, length + 0.2f);
			glVertex3f(radius*cos(theta) + 0.3f, radius + 0.2f*sin(theta) + 1.8f, length + 0.2f);
			glVertex3f(radius*cos(nextTheta) + 0.3f, radius + 0.2f*sin(nextTheta) + 1.8f, length + 0.2f);
		}
		glEnd();
	}

	void rightiris()
	{
		int sides = 20;
		float radius = 0.05f;
		float length = 1.0f;
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.3f, 1.9f, length + 0.25f);
			glVertex3f(radius*cos(theta) + 0.3f, radius + 0.1f*sin(theta) + 1.9f, length + 0.25f);
			glVertex3f(radius*cos(nextTheta) + 0.3f, radius + 0.1f*sin(nextTheta) + 1.9f, length + 0.25f);
		}
		glEnd();
	}

	void leftiris()
	{
		int sides = 20;
		float radius = 0.05f;
		float length = 1.0f;
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.35f, 1.9f, length + 0.25f);
			glVertex3f(radius*cos(theta) - 0.35f, radius + 0.1f*sin(theta) + 1.9f, length + 0.25f);
			glVertex3f(radius*cos(nextTheta) - 0.35f, radius + 0.1f*sin(nextTheta) + 1.9f, length + 0.25f);
		}
		glEnd();
	}

	void mouth()
	{
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.4f, 1.45f, 1.1f);
		glVertex3f(-0.4f, 1.5f, 1.1f);
		glVertex3f(0.4f, 1.5f, 1.1f);

		glVertex3f(-0.4f, 1.45f, 1.1f);
		glVertex3f(0.4f, 1.45f, 1.1f);
		glVertex3f(0.4f, 1.5f, 1.1f);

		glEnd();
	}

	void upperbody()
	{
		glBegin(GL_TRIANGLES);
		//cube
		//front
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.75f, 1.5f, 0.5f);
		glVertex3f(-0.75f, 0.0f, 0.5f);
		glVertex3f(0.75f, 0.0f, 0.5f);

		glVertex3f(-0.75f, 1.5f, 0.5f);
		glVertex3f(0.75f, 1.5f, 0.5f);
		glVertex3f(0.75f, 0.0f, 0.5f);

		//back
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.75f, 1.5f, -0.5f);
		glVertex3f(-0.75f, 0.0f, -0.5f);
		glVertex3f(0.75f, 0.0f, -0.5f);

		glVertex3f(-0.75f, 1.5f, -0.5f);
		glVertex3f(0.75f, 1.5f, -0.5f);
		glVertex3f(0.75f, 0.0f, -0.5f);

		//left
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.75f, 1.5f, -0.5f);
		glVertex3f(-0.75f, 0.0f, -0.5f);
		glVertex3f(-0.75f, 0.0f, 0.5f);

		glVertex3f(-0.75f, 1.5f, -0.5f);
		glVertex3f(-0.75f, 1.5f, 0.5f);
		glVertex3f(-0.75f, 0.0f, 0.5f);

		//lowerleft
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.75f, 0.0f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glVertex3f(-0.75f, 0.0f, -0.5f);
		glVertex3f(-0.75f, 0.0f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		//right
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.75f, 1.5f, -0.5f);
		glVertex3f(0.75f, 0.5f, -0.5f);
		glVertex3f(0.75f, 0.5f, 0.5f);

		glVertex3f(0.75f, 1.5f, -0.5f);
		glVertex3f(0.75f, 1.5f, 0.5f);
		glVertex3f(0.75f, 0.5f, 0.5f);

		//lowerright
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.75f, 0.0f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glVertex3f(0.75f, 0.0f, -0.5f);
		glVertex3f(0.75f, 0.0f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		//lowerfront
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.75f, 0.0f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glVertex3f(-0.75f, 0.0f, 0.5f);
		glVertex3f(0.75f, 0.0f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		//lowerback
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.75f, 0.0f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glVertex3f(-0.75f, 0.0f, -0.5f);
		glVertex3f(0.75f, 0.0f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glEnd();
		
	}

	void leftleg()
	{
		int sides = 20;
		float radius = 0.3f;
		float height = 2.0f;
		glColor3f(0.5f, 0.35f, 0.05f);
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle
			glVertex3f(-0.3f, height - 3.0f, -0.2f);
			glVertex3f(radius*cos(theta)-0.3f, height-3.0f, radius*sin(theta) - 0.2f);
			glVertex3f(radius*cos(nextTheta) - 0.3f, height - 3.0f, radius*sin(nextTheta) - 0.2f);

			glVertex3f(-0.5f, -height - 3.0f, -0.5f);
			glVertex3f(radius*cos(theta) - 0.5f, -height-3.0f, radius*sin(theta) - 0.5f);
			glVertex3f(radius*cos(nextTheta) - 0.5f, -height - 3.0f, radius*sin(nextTheta) - 0.5f);

			//Side Cylinder
			glVertex3f(radius*cos(theta) - 0.3f, height - 3.0f, radius*sin(theta) - 0.2f);
			glVertex3f(radius*cos(nextTheta) - 0.3f, height - 3.0f, radius*sin(nextTheta) - 0.2f);
			glVertex3f(radius*cos(theta) - 0.5f, -height - 3.0f, radius*sin(theta) - 0.5f);

			glVertex3f(radius*cos(theta) - 0.5f, -height - 3.0f, radius*sin(theta) - 0.5f);
			glVertex3f(radius*cos(nextTheta) - 0.5f, -height -3.0f, radius*sin(nextTheta) - 0.5f);
			glVertex3f(radius*cos(nextTheta) - 0.3f, height - 3.0f, radius*sin(nextTheta) - 0.2f);

		}
		glEnd();
	}

	void leftshoes()
	{
		glBegin(GL_TRIANGLES);
		//cube
		//backfront
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.15f, -4.5f, -0.15f);
		glVertex3f(-0.15f, -5.0f, -0.2f);
		glVertex3f(-0.85f, -5.0f, -0.2f);

		glVertex3f(-0.15f, -4.5f, -0.15f);
		glVertex3f(-0.85f, -4.5f, -0.15f);
		glVertex3f(-0.85f, -5.0f, -0.2f);

		//backback
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.15f, -4.5f, -0.8f);
		glVertex3f(-0.15f, -5.0f, -0.8f);
		glVertex3f(-0.85f, -5.0f, -0.8f);

		glVertex3f(-0.15f, -4.5f, -0.8f);
		glVertex3f(-0.85f, -4.5f, -0.8f);
		glVertex3f(-0.85f, -5.0f, -0.8f);

		//backleft
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.15f, -4.5f, -0.8f);
		glVertex3f(-0.15f, -5.0f, -0.8f);
		glVertex3f(-0.15f, -5.0f, -0.2f);

		glVertex3f(-0.15f, -4.5f, -0.8f);
		glVertex3f(-0.15f, -4.5f, -0.15f);
		glVertex3f(-0.15f, -5.0f, -0.2f);

		//backright
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.85f, -4.5f, -0.8f);
		glVertex3f(-0.85f, -5.0f, -0.8f);
		glVertex3f(-0.85f, -5.0f, -0.2f);

		glVertex3f(-0.85f, -4.5f, -0.8f);
		glVertex3f(-0.85f, -4.5f, -0.15f);
		glVertex3f(-0.85f, -5.0f, -0.2f);

		//frontleft
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.15f, -4.5f, -0.15f);
		glVertex3f(-0.15f, -5.0f, -0.2f);
		glVertex3f(-0.15f, -5.0f, 0.6f);

		glVertex3f(-0.15f, -4.5f, -0.15f);
		glVertex3f(-0.15f, -4.5f, 0.6f);
		glVertex3f(-0.15f, -5.0f, 0.6f);

		//frontright
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.85f, -4.5f, -0.15f);
		glVertex3f(-0.85f, -5.0f, -0.2f);
		glVertex3f(-0.85f, -5.0f, 0.6f);

		glVertex3f(-0.85f, -4.5f, -0.15f);
		glVertex3f(-0.85f, -4.5f, 0.6f);
		glVertex3f(-0.85f, -5.0f, 0.6f);

		//frontfront
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.15f, -4.65f, 0.8f);
		glVertex3f(-0.15f, -5.0f, 0.8f);
		glVertex3f(-0.85f, -5.0f, 0.8f);

		glVertex3f(-0.15f, -4.65f, 0.8f);
		glVertex3f(-0.85f, -4.65f, 0.8f);
		glVertex3f(-0.85f, -5.0f, 0.8f);

		//fronthalftop
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.15f, -4.5f, 0.6f);
		glVertex3f(-0.15f, -4.65f, 0.8f);
		glVertex3f(-0.85f, -4.65f, 0.8f);

		glVertex3f(-0.15f, -4.5f, 0.6f);
		glVertex3f(-0.85f, -4.5f, 0.6f);
		glVertex3f(-0.85f, -4.65f, 0.8f);

		//fronttop
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.15f, -4.5f, 0.6f);
		glVertex3f(-0.15f, -4.5f, -0.15f);
		glVertex3f(-0.85f, -4.5f, -0.15f);

		glVertex3f(-0.15f, -4.5f, 0.6f);
		glVertex3f(-0.85f, -4.5f, -0.15f);
		glVertex3f(-0.85f, -4.5f, 0.6f);

		//fronthalfright
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.85f, -4.65f, 0.8f);
		glVertex3f(-0.85f, -5.0f, 0.6f);
		glVertex3f(-0.85f, -5.0f, 0.8f);

		glVertex3f(-0.85f, -4.65f, 0.8f);
		glVertex3f(-0.85f, -4.5f, 0.6f);
		glVertex3f(-0.85f, -5.0f, 0.6f);

		//fronthalleft
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.15f, -4.65f, 0.8f);
		glVertex3f(-0.15f, -5.0f, 0.6f);
		glVertex3f(-0.15f, -5.0f, 0.8f);

		glVertex3f(-0.15f, -4.65f, 0.8f);
		glVertex3f(-0.15f, -4.5f, 0.6f);
		glVertex3f(-0.15f, -5.0f, 0.6f);

		//frontquatertop
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.15f, -4.35f, -0.1f);
		glVertex3f(-0.15f, -4.5f, 0.3f);
		glVertex3f(-0.85f, -4.5f, 0.3f);

		glVertex3f(-0.15f, -4.35f, -0.1f);
		glVertex3f(-0.85f, -4.35f, -0.1f);
		glVertex3f(-0.85f, -4.5f, 0.3f);

		//frontquateraback
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.15f, -4.35f, -0.1f);
		glVertex3f(-0.15f, -4.5f, -0.1f);
		glVertex3f(-0.85f, -4.5f, -0.1f);

		glVertex3f(-0.15f, -4.35f, -0.1f);
		glVertex3f(-0.85f, -4.35f, -0.1f);
		glVertex3f(-0.85f, -4.5f, -0.1f);

		//frontquaterleft
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.15f, -4.35f, -0.1f);
		glVertex3f(-0.15f, -4.5f, -0.1f);
		glVertex3f(-0.15f, -4.5f, 0.3f);

		//frontquaterright
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(-0.85f, -4.35f, -0.1f);
		glVertex3f(-0.85f, -4.5f, -0.1f);
		glVertex3f(-0.85f, -4.5f, 0.3f);

		glEnd();
	
	}

	void rightleg()
	{
		int sides = 20;
		float radius = 0.3f;
		float height = 2.0f;
		glColor3f(0.5f, 0.35f, 0.05f);
		for (int i = 0; i < sides; i++)
		{
			glBegin(GL_TRIANGLES);
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			//Top and Bottom circle
			glVertex3f(0.3f, height - 3.0f, 0.2f);
			glVertex3f(radius*cos(theta) + 0.3f, height - 3.0f, radius*sin(theta) + 0.2f);
			glVertex3f(radius*cos(nextTheta) + 0.3f, height - 3.0f, radius*sin(nextTheta) + 0.2f);

			glVertex3f(0.5f, -height- 3.0f, 0.5f);
			glVertex3f(radius*cos(theta) + 0.5f, -height - 3.0f, radius*sin(theta) + 0.5f);
			glVertex3f(radius*cos(nextTheta) + 0.5f, -height - 3.0f, radius*sin(nextTheta) + 0.5f);

			//Side Cylinder
			glVertex3f(radius*cos(theta) + 0.3f, height - 3.0f, radius*sin(theta) + 0.2f);
			glVertex3f(radius*cos(nextTheta) + 0.3f, height - 3.0f, radius*sin(nextTheta) + 0.2f);
			glVertex3f(radius*cos(theta) + 0.5f, -height - 3.0f, radius*sin(theta) + 0.5f);

			glVertex3f(radius*cos(theta) + 0.5f, -height - 3.0f, radius*sin(theta) + 0.5f);
			glVertex3f(radius*cos(nextTheta) + 0.5f, -height - 3.0f, radius*sin(nextTheta) + 0.5f);
			glVertex3f(radius*cos(nextTheta) + 0.3f, height - 3.0f, radius*sin(nextTheta) + 0.2f);

		}
		glEnd();
	}

	void rightshoes()
	{
		glBegin(GL_TRIANGLES);
		//cube
		//backfront
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.15f, -4.5f, 0.8f);
		glVertex3f(0.15f, -5.0f, 0.8f);
		glVertex3f(0.85f, -5.0f, 0.8f);

		glVertex3f(0.15f, -4.5f, 0.8f);
		glVertex3f(0.85f, -4.5f, 0.8f);
		glVertex3f(0.85f, -5.0f, 0.8f);

		//backback
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.15f, -4.5f, 0.15f);
		glVertex3f(0.15f, -5.0f, 0.2f);
		glVertex3f(0.85f, -5.0f, 0.2f);

		glVertex3f(0.15f, -4.5f, 0.15f);
		glVertex3f(0.85f, -4.5f, 0.15f);
		glVertex3f(0.85f, -5.0f, 0.2f);

		//backleft
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.15f, -4.5f, 0.15f);
		glVertex3f(0.15f, -5.0f, 0.2f);
		glVertex3f(0.15f, -5.0f, 0.8f);

		glVertex3f(0.15f, -4.5f, 0.15f);
		glVertex3f(0.15f, -4.5f, 0.8f);
		glVertex3f(0.15f, -5.0f, 0.8f);

		//backright
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.85f, -4.5f, 0.15f);
		glVertex3f(0.85f, -5.0f, 0.2f);
		glVertex3f(0.85f, -5.0f, 0.8f);

		glVertex3f(0.85f, -4.5f, 0.15f);
		glVertex3f(0.85f, -4.5f, 0.8f);
		glVertex3f(0.85f, -5.0f, 0.8f);

		//frontfront
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.15f, -4.65f, 1.8f);
		glVertex3f(0.15f, -5.0f, 1.8f);
		glVertex3f(0.85f, -5.0f, 1.8f);

		glVertex3f(0.15f, -4.65f, 1.8f);
		glVertex3f(0.85f, -4.65f, 1.8f);
		glVertex3f(0.85f, -5.0f, 1.8f);

		//frontleft
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.15f, -4.5f, 0.8f);
		glVertex3f(0.15f, -5.0f, 0.8f);
		glVertex3f(0.15f, -5.0f, 1.6f);

		glVertex3f(0.15f, -4.5f, 0.8f);
		glVertex3f(0.15f, -4.5f, 1.6f);
		glVertex3f(0.15f, -5.0f, 1.6f);

		//frontright
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.85f, -4.5f, 0.8f);
		glVertex3f(0.85f, -5.0f, 0.8f);
		glVertex3f(0.85f, -5.0f, 1.6f);

		glVertex3f(0.85f, -4.5f, 0.8f);
		glVertex3f(0.85f, -4.5f, 1.6f);
		glVertex3f(0.85f, -5.0f, 1.6f);
		
		//fronthalftop
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.15f, -4.5f, 1.6f);
		glVertex3f(0.15f, -4.65f, 1.8f);
		glVertex3f(0.85f, -4.65f, 1.8f);

		glVertex3f(0.15f, -4.5f, 1.6f);
		glVertex3f(0.85f, -4.5f, 1.6f);
		glVertex3f(0.85f, -4.65f, 1.8f);

		//fronthalfleft
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.15f, -4.65f, 1.8f);
		glVertex3f(0.15f, -5.0f, 1.6f);
		glVertex3f(0.15f, -5.0f, 1.8f);

		glVertex3f(0.15f, -4.65f, 1.8f);
		glVertex3f(0.15f, -4.5f, 1.6f);
		glVertex3f(0.15f, -5.0f, 1.6f);

		//fronthalfright
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.85f, -4.65f, 1.8f);
		glVertex3f(0.85f, -5.0f, 1.6f);
		glVertex3f(0.85f, -5.0f, 1.8f);

		glVertex3f(0.85f, -4.65f, 1.8f);
		glVertex3f(0.85f, -4.5f, 1.6f);
		glVertex3f(0.85f, -5.0f, 1.6f);

		//fronttop
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.15f, -4.5f, 1.6f);
		glVertex3f(0.15f, -4.5f, 0.8f);
		glVertex3f(0.85f, -4.5f, 0.8f);

		glVertex3f(0.15f, -4.5f, 1.6f);
		glVertex3f(0.85f, -4.5f, 0.8f);
		glVertex3f(0.85f, -4.5f, 1.6f);

		//frontquatertop
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.15f, -4.35f, 0.8f);
		glVertex3f(0.15f, -4.5f, 1.2f);
		glVertex3f(0.85f, -4.5f, 1.2f);

		glVertex3f(0.15f, -4.35f, 0.8f);
		glVertex3f(0.85f, -4.35f, 0.8f);
		glVertex3f(0.85f, -4.5f, 1.2f);

		//frontquateraback
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.15f, -4.35f, 0.8f);
		glVertex3f(0.15f, -4.5f, 0.8f);
		glVertex3f(0.85f, -4.5f, 0.8f);

		glVertex3f(0.15f, -4.35f, 0.8f);
		glVertex3f(0.85f, -4.35f, 0.8f);
		glVertex3f(0.85f, -4.5f, 0.8f);

		//frontquaterleft
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.15f, -4.35f, 0.8f);
		glVertex3f(0.15f, -4.5f, 0.8f);
		glVertex3f(0.15f, -4.5f, 1.2f);

		//frontquaterright
		glColor3f(0.87f, 0.58f, 0.98f);
		glVertex3f(0.85f, -4.35f, 0.8f);
		glVertex3f(0.85f, -4.5f, 0.8f);
		glVertex3f(0.85f, -4.5f, 1.2f);

		glEnd();
	}

	void leftglove()
	{
		float radius = 0.8f;
		int sides = 20;

		for (float i = 0.0f; i < M_PI; i += M_PI / sides)
		{
			glBegin(GL_TRIANGLES);
			for (float j = 0.0f; j < 2.01*M_PI; j += M_PI / sides)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(-1.5f, -1.0f, 2.4f);
				glVertex3f(radius * cos(j)*sin(i)-1.5f, radius * sin(j)*sin(i)-1.0f, radius * cos(i)+ 2.4f);
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides) - 1.5f, radius * sin(j)*sin(i + M_PI / sides) - 1.0f, radius * cos(i + M_PI / sides) + 2.4f);

				glVertex3f(-1.5f, -1.0f, 2.2f);
				glVertex3f(radius * cos(j)*sin(i) - 1.5f, radius * sin(j)*sin(i) - 1.0f, radius * cos(i) + 2.2f);
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides) - 1.5f, radius * sin(j)*sin(i + M_PI / sides) - 1.0f, radius * cos(i + M_PI / sides) + 2.2f);

				glVertex3f(-1.5f, -1.0f, 2.4f);
				glVertex3f(radius * cos(j)*sin(i) - 1.5f, radius * cos(i) - 1.0f, radius * sin(j)*sin(i) + 2.4f);
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides) - 1.5f, radius * cos(i + M_PI / sides) - 1.0f, radius * sin(j)*sin(i + M_PI / sides) + 2.4f);

				glVertex3f(-1.5f, -1.0f, 2.2f);
				glVertex3f(radius * cos(j)*sin(i) - 1.5f, radius * cos(i) - 1.0f, radius * sin(j)*sin(i) + 2.2f);
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides) - 1.5f, radius * cos(i + M_PI / sides) - 1.0f, radius * sin(j)*sin(i + M_PI / sides) + 2.2f);
			}
			glEnd();
		}
	}

	void rightglove()
	{
		float radius = 0.8f;
		int sides = 20;

		for (float i = 0.0f; i < M_PI; i += M_PI / sides)
		{
			glBegin(GL_TRIANGLES);
			for (float j = 0.0f; j < 2.01*M_PI; j += M_PI / sides)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(1.5f, -0.2f, 4.0f);
				glVertex3f(radius * cos(j)*sin(i) + 1.5f, radius * sin(j)*sin(i) - 0.2f, radius * cos(i) + 4.0f);
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides) + 1.5f, radius * sin(j)*sin(i + M_PI / sides) - 0.2f, radius * cos(i + M_PI / sides) + 4.0f);

				glVertex3f(1.5f, -0.2f, 4.0f);
				glVertex3f(radius * cos(j)*sin(i) + 1.5f, radius * cos(i) - 0.2f, radius * sin(j)*sin(i) + 4.0f);
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides) + 1.5f, radius * cos(i + M_PI / sides) - 0.2f, radius * sin(j)*sin(i + M_PI / sides) + 4.0f);

				glVertex3f(1.5f, -0.2f, 3.8f);
				glVertex3f(radius * cos(j)*sin(i) + 1.5f, radius * sin(j)*sin(i) - 0.2f, radius * cos(i) + 3.8f);
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides) + 1.5f, radius * sin(j)*sin(i + M_PI / sides) - 0.2f, radius * cos(i + M_PI / sides) + 3.8f);

				glVertex3f(1.5f, -0.2f, 3.8f);
				glVertex3f(radius * cos(j)*sin(i) + 1.5f, radius * cos(i) - 0.2f, radius * sin(j)*sin(i) + 3.8f);
				glVertex3f(radius * cos(j)*sin(i + M_PI / sides) + 1.5f, radius * cos(i + M_PI / sides) - 0.2f, radius * sin(j)*sin(i + M_PI / sides) + 3.8f);
			}
			glEnd();
		}
	}

	void moveWholeBody(const Matrix& viewMatrix)
	{
		m_speed += 0.01f;
		Matrix translate1 = Matrix::makeTranslationMatrix(0.0f, sinf(m_speed)/7, 0.0f);
		Matrix modelMatrix = translate1;
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		upperbody();
		waist();		
		upperleftshoulder();
		upperrightshoulder();
		lowerwaist();				
	}

	void moveRightHand(const Matrix& viewMatrix)
	{
		m_speed += 0.01f;
		Matrix translate1 = Matrix::makeTranslationMatrix(0.0f, cosf(m_speed)/ 10, 0.0f);
		Matrix modelMatrix = translate1;
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
		upperrighthand();
		lowerrighthand();
		righthand();
		rightglove();
	}

	void moveLeftHand(const Matrix& viewMatrix)
	{
		m_speed += 0.01f;
		Matrix translate1 = Matrix::makeTranslationMatrix(0.0f, sinf(m_speed) / 10, 0.0f);
		Matrix modelMatrix = translate1;
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		upperlefthand();
		lowerlefthand();
		lefthand();
		leftglove();
	}

	void moveHead(const Matrix& viewMatrix)
	{
		m_speed += 0.01f;
		Matrix translate1 = Matrix::makeTranslationMatrix(0.0f, sinf(m_speed) / 15, 0.0f);
		Matrix modelMatrix = translate1;
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
		lefteyeball();
		leftiris();
		righteyeball();
		rightiris();
		head();
		mouth();
	}

	void drawPokemon(const Matrix& viewMatrix)
	{
		leftleg();
		rightleg();
		rightshoes();
		leftshoes();

		moveWholeBody(viewMatrix);
		moveRightHand(viewMatrix);
		moveLeftHand(viewMatrix);
		moveHead(viewMatrix);
	}

	void draw(const Matrix& viewMatrix)
	{
		drawAxis(viewMatrix);
		//WIREFRAME
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		drawPokemon(viewMatrix);
	}
};

#endif
