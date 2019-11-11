#define GLFW_INCLUDE_ES2 1
#define GLFW_DLL 1
//#define GLFW_EXPOSE_NATIVE_WIN32 1
//#define GLFW_EXPOSE_NATIVE_EGL 1

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream> 
#include "angle_util/Matrix.h"
#include "angle_util/geometry_utils.h"
#include "bitmap.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 768

#define TEXTURE_COUNT 7

GLint GprogramID = -1;
GLuint GtextureID[TEXTURE_COUNT];


GLuint Gframebuffer;
GLuint GdepthRenderbuffer;

GLuint GfullscreenTexture;
GLuint GtextureBlurred;
GLuint GtextureBright;

GLFWwindow* window;

Matrix4 gPerspectiveMatrix;
Matrix4 gViewMatrix;

float m_Speed = 0.0f;
float m_Rotation = 0.0f;

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

GLuint LoadShader(GLenum type, const char *shaderSrc )
{
   GLuint shader;
   GLint compiled;
   
   // Create the shader object
   shader = glCreateShader ( type );

   if ( shader == 0 )
   	return 0;

   // Load the shader source
   glShaderSource ( shader, 1, &shaderSrc, NULL );
   
   // Compile the shader
   glCompileShader ( shader );

   // Check the compile status
   glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

   if ( !compiled ) 
   {
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
      
      if ( infoLen > 1 )
      {
		 char infoLog[4096];
         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
         printf ( "Error compiling shader:\n%s\n", infoLog );            
      }

      glDeleteShader ( shader );
      return 0;
   }

   return shader;
}

GLuint LoadShaderFromFile(GLenum shaderType, std::string path)
{
    GLuint shaderID = 0;
    std::string shaderString;
    std::ifstream sourceFile( path.c_str() );

    if( sourceFile )
    {
        shaderString.assign( ( std::istreambuf_iterator< char >( sourceFile ) ), std::istreambuf_iterator< char >() );
        const GLchar* shaderSource = shaderString.c_str();

		return LoadShader(shaderType, shaderSource);
    }
    else
        printf( "Unable to open file %s\n", path.c_str() );

    return shaderID;
}


void loadTexture(const char* path, GLuint textureID)
{
	CBitmap bitmap(path);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());
}

int Init ( void )
{
   GLuint vertexShader;
   GLuint fragmentShader;
   GLuint programObject;
   GLint linked;
   
   m_Speed = 0;
   m_Rotation = 0;

   //load textures
   glGenTextures(TEXTURE_COUNT, GtextureID);
   loadTexture("../media/rocks.bmp", GtextureID[0]);
   loadTexture("../media/glass.bmp", GtextureID[1]);
   loadTexture("../media/win8.bmp", GtextureID[2]);
   loadTexture("../media/fury_nano2.bmp", GtextureID[3]);
   loadTexture("../media/rainbow.bmp", GtextureID[4]);
   loadTexture("../media/skybox.bmp", GtextureID[5]);
   loadTexture("../media/plain.bmp", GtextureID[6]);
   //====



   //==================== set up frame buffer, render buffer, and create an empty texture for blurring purpose
   // create a new FBO
   glGenFramebuffers(1, &Gframebuffer);
   
   // create a new empty texture for blurring
   glGenTextures(1, &GtextureBlurred);
   glBindTexture(GL_TEXTURE_2D, GtextureBlurred);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

   // create a new empty texture for extract
   glGenTextures(1, &GtextureBright);
   glBindTexture(GL_TEXTURE_2D, GtextureBright);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

   // create a new empty texture for rendering original scene
   glGenTextures(1, &GfullscreenTexture);
   glBindTexture(GL_TEXTURE_2D, GfullscreenTexture);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

   // create and bind renderbuffer, and create a 16-bit depth buffer
   glGenRenderbuffers(1, &GdepthRenderbuffer);
   glBindRenderbuffer(GL_RENDERBUFFER, GdepthRenderbuffer);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, WINDOW_WIDTH, WINDOW_HEIGHT);
   //=================================


   fragmentShader = LoadShaderFromFile(GL_VERTEX_SHADER, "../vertexShader1.vert" );
   vertexShader = LoadShaderFromFile(GL_FRAGMENT_SHADER, "../fragmentShader1.frag" );

   // Create the program object
   programObject = glCreateProgram ( );
   
   if ( programObject == 0 )
      return 0;

   glAttachShader ( programObject, vertexShader );
   glAttachShader ( programObject, fragmentShader );

   glBindAttribLocation ( programObject, 0, "vPosition" );
   glBindAttribLocation ( programObject, 1, "vColor" );
   glBindAttribLocation ( programObject, 2, "vTexCoord" );

   // Link the program
   glLinkProgram ( programObject );

   // Check the link status
   glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

   if ( !linked ) 
   {
      GLint infoLen = 0;

      glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
      
      if ( infoLen > 1 )
      {
		 char infoLog[1024];
         glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
         printf ( "Error linking program:\n%s\n", infoLog );            
      }

      glDeleteProgram ( programObject );
      return 0;
   }

   // Store the program object
   GprogramID = programObject;


   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   //initialize matrices
   gPerspectiveMatrix = Matrix4::perspective(60.0f,
											(float)WINDOW_WIDTH/(float)WINDOW_HEIGHT,
                                             0.5f, 30.0f);

   gViewMatrix = Matrix4::translate(Vector3(0.0f, 0.0f, -2.0f));


   return 1;
}


void UpdateCamera(void)
{
	static float yaw = 0.0f;
	static float pitch = 0.0f;
	static float distance = 2.5f;

	if(glfwGetKey(window, 'A')) pitch -= 1.0f;
	if(glfwGetKey(window, 'D')) pitch += 1.0f;
	if(glfwGetKey(window, 'W')) yaw -= 1.0f;
	if(glfwGetKey(window, 'S')) yaw += 1.0f;

	if(glfwGetKey(window, 'R'))
	{
		distance -= 0.06f;
		if(distance < 1.0f)
			distance = 1.0f;
	}
	if(glfwGetKey(window, 'F')) distance += 0.06f;

	gViewMatrix =	Matrix4::translate(Vector3(0.0f, 0.0f, -distance)) * 
					Matrix4::rotate(yaw, Vector3(1.0f, 0.0f, 0.0f)) *
					Matrix4::rotate(pitch, Vector3(0.0f, 1.0f, 0.0f));
}

void DrawSquare(GLuint texture)
{
    static GLfloat vVertices[] = {-1.0f,  1.0f, 0.0f,
								-1.0f, -1.0f, 0.0f,
								1.0f, -1.0f,  0.0f,
								1.0f,  -1.0f, 0.0f,
								1.0f, 1.0f, 0.0f,
								-1.0f, 1.0f,  0.0f,};
					 

   static GLfloat vColors[] = {1.0f,  0.0f, 0.0f, 1.0f,
								0.0f, 1.0f, 0.0f, 1.0f,
								0.0f, 0.0f,  1.0f, 1.0f,
								0.0f,  0.0f, 1.0f, 1.0f,
								1.0f, 1.0f, 0.0f, 1.0f,
								1.0f, 0.0f,  0.0f, 1.0f};

   static GLfloat vTexCoords[] = {0.0f,  1.0f,
									0.0f, 0.0f,
									1.0f, 0.0f,
									1.0f,  0.0f,
									1.0f, 1.0f,
									0.0f, 1.0f};


   glBindTexture(GL_TEXTURE_2D, texture);


   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, vColors);
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, vTexCoords);

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);


   glDrawArrays(GL_TRIANGLES, 0, 6);


   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(2);
}

void DrawSkyBox(GLuint texture)
{
	float num = 3.0f;
	static GLfloat vVertices[] = { 
								//front
								-num,  num, num,
								-num, -num, num,
								num, -num,  num,
								num,  -num, num,
								num, num, num,
								-num, num,  num,

								//back
								-num,  num, -num,
								-num, -num, -num,
								num, -num,  -num,
								num,  -num, -num,
								num, num, -num,
								-num, num,  -num,

								//right
								num,  num, -num,
								num, -num, -num,
								num, -num,  num,
								num,  -num, num,
								num, num, num,
								num, num,  -num,

								//left
								-num,  num, -num,
								-num, -num, -num,
								-num, -num,  num,
								-num,  -num, num,
								-num, num, num,
								-num, num,  -num,

								//bottom
								-num,  -num, -num,
								num, -num,  num,								
								-num, -num, num,
								-num, -num,  -num,
								num,  -num, num,							
								num, -num, -num,
							
								//top
								-num,  num, -num,
								num, num,  num,
								-num, num, num,
								-num, num,  -num,
								num,  num, num,
								num, num, -num,
								
								
	};

	static GLfloat vColors[] = { 1.0f,  0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f, 0.0f,
								0.0f, 0.0f,  1.0f, 0.0f,
								0.0f,  0.0f, 1.0f, 0.0f,
								1.0f, 1.0f, 0.0f, 0.0f,
								1.0f, 0.0f,  0.0f, 0.0f };

	static GLfloat vTexCoords[] = {
		//front
		0.0f,  0.67f,
		0.0f, 0.34f,
		0.25f, 0.34f,
		0.25f,  0.34f,
		0.25f, 0.67f,
		0.0f, 0.67f,

		//back
		0.75f,  0.67f,
		0.75f, 0.34f,
		0.50f, 0.34f,
		0.50f,  0.34f,
		0.50f, 0.67f,
		0.75f, 0.67f,

	   //right
		0.50f,  0.67f,
		0.50f, 0.34f,
		0.25f, 0.34f,
		0.25f,0.34f,
		0.25f,0.67f,
		0.50f,0.67f,

		//left
		0.75,  0.67f,
		0.75f, 0.34f,
		1.0f, 0.34f,
		1.0f,0.34f,
		1.0f,0.67f,
		0.75f,0.67f,

		//top
		0.5f,0.01f,
		0.25f,0.34f,		
		0.25f,0.01f,
		0.5f,0.01f,
		0.25f,0.34f,
		0.5f,0.34f,

		//bottom
		0.5f,1.0f,
		0.25f,0.67f,
		0.25f,1.0f,		
		0.5f,1.0f,
		0.25f,0.67f,
		0.5f,0.67f,
		
				
};


	glBindTexture(GL_TEXTURE_2D, texture);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, vColors);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, vTexCoords);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	glDrawArrays(GL_TRIANGLES, 0, 36);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void DrawAnimateBox(GLuint texture)
{
	float num = 0.2f;
	static GLfloat vVertices[] = {
		//front
		-num,  num, num,
		-num, -num, num,
		num, -num,  num,
		num,  -num, num,
		num, num, num,
		-num, num,  num,

		//back
		-num,  num, -num,
		-num, -num, -num,
		num, -num,  -num,
		num,  -num, -num,
		num, num, -num,
		-num, num,  -num,

		//right
		num,  num, -num,
		num, -num, -num,
		num, -num,  num,
		num,  -num, num,
		num, num, num,
		num, num,  -num,

		//left
		-num,  num, -num,
		-num, -num, -num,
		-num, -num,  num,
		-num,  -num, num,
		-num, num, num,
		-num, num,  -num,

		//Bottom
		num, -num,  num,
		-num,  -num, -num,
		-num, -num, num,
		-num, -num,  -num,
		num,  -num, num,
		num, -num, -num,

		//top
		num, num,  num,
		-num,  num, -num,
		-num, num, num,
		-num, num,  -num,
		num,  num, num,
		num, num, -num,

	};

	static GLfloat vColors[] = {
		1.0f,  0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f,  1.0f, 1.0f,
		0.0f,  0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f,  0.0f, 1.0f,
	};

	static GLfloat vTexCoords[] = {
		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		1.0f,1.0f,
		0.0f,1.0f,
		0.0f,0.0f,

		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		1.0f,1.0f,
		0.0f,1.0f,
		0.0f,0.0f,

		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		1.0f,1.0f,
		0.0f,1.0f,
		0.0f,0.0f,

		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		1.0f,1.0f,
		0.0f,1.0f,
		0.0f,0.0f,

		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		1.0f,1.0f,
		0.0f,1.0f,
		0.0f,0.0f,

		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		1.0f,1.0f,
		0.0f,1.0f,
		0.0f,0.0f,
	};

	glBindTexture(GL_TEXTURE_2D, texture);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, vColors);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, vTexCoords);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void UpDownCube()
{
	m_Speed += 0.05f;
	Matrix4 modelMatrix, mvpMatrix;
	modelMatrix = Matrix4::rotate(220, Vector3(0.0f, 1.0f, 0.0f))* Matrix4::translate(Vector3(0.0f, cosf(m_Speed)*2.0f, 3.0f));
	mvpMatrix = gPerspectiveMatrix * gViewMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, mvpMatrix.data);
	DrawAnimateBox(GtextureID[6]);
}

void rotateAroundCube()
{
	m_Rotation += 3.0f;
	Matrix4 modelMatrix2, mvpMatrix2;
	modelMatrix2 = Matrix4::rotate(270, Vector3(0.0f, 1.0f, 0.0f))* Matrix4::rotate(m_Rotation, Vector3(0.0f, 1.0f, 0.0f)) * Matrix4::translate(Vector3(2.5f,0.5f,0.0f));
	mvpMatrix2 = gPerspectiveMatrix * gViewMatrix * modelMatrix2;
	glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, mvpMatrix2.data);
	DrawAnimateBox(GtextureID[6]);
}

void Draw(void)
{	
	// Use the program object, it's possible that you have multiple shader programs and switch it accordingly
    glUseProgram(GprogramID);

	// set the sampler2D varying variable to the first texture unit(index 0)
	glUniform1i(glGetUniformLocation(GprogramID, "sampler2d"), 0);

	//========pass texture size to shader
    glUniform1f(glGetUniformLocation(GprogramID, "uTextureW"), (GLfloat)WINDOW_WIDTH);
    glUniform1f(glGetUniformLocation(GprogramID, "uTextureH"), (GLfloat)WINDOW_HEIGHT);
    //=========


	UpdateCamera();

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//=====================draw 2 rectangles on a texture
	// bind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, Gframebuffer);

	// specify texture as color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GfullscreenTexture, 0);

	// specify depth_renderbufer as depth attachment
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, GdepthRenderbuffer);
	
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status == GL_FRAMEBUFFER_COMPLETE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniform1i(glGetUniformLocation(GprogramID, "uBlurDirection"), -1); //set to no blur

		Matrix4 modelMatrix, mvpMatrix;
		modelMatrix = Matrix4::translate(Vector3(0.0f, 0.0f, 0.0f)) *
						Matrix4::rotate(180, Vector3(0.0f, 0.0f, 0.0f));
		mvpMatrix = gPerspectiveMatrix * gViewMatrix * modelMatrix;
		glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, mvpMatrix.data);
		DrawSkyBox(GtextureID[5]);
	}
	else
	{
		printf("frame buffer is not ready!\n");
	}
	//=============================================

	UpDownCube();
	rotateAroundCube();

	//================== texture for bright ================================================
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GtextureBright, 0);

	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status == GL_FRAMEBUFFER_COMPLETE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// reset the mvpMatrix to identity matrix so that it renders fully on texture in normalized device coordinates
		glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, Matrix4::identity().data);

		// tell the shader to apply horizontal blurring, for details please check the "uBlurDirection" flag in the shader code
		glUniform1i(glGetUniformLocation(GprogramID, "uBlurDirection"), 2); //bright value

		DrawSquare(GfullscreenTexture);
	}
	else
	{
		printf("frame buffer is not ready!\n");
	}
	
	//==============blur the texture, first pass(horizontal blur)================================
	
	// change the render target to GtextureBlurred
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GtextureBlurred, 0);

	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status == GL_FRAMEBUFFER_COMPLETE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// reset the mvpMatrix to identity matrix so that it renders fully on texture in normalized device coordinates
		glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, Matrix4::identity().data);

		// tell the shader to apply horizontal blurring, for details please check the "uBlurDirection" flag in the shader code
		glUniform1i(glGetUniformLocation(GprogramID, "uBlurDirection"), 0);

		DrawSquare(GtextureBright);
	}
	else
	{
		printf("frame buffer is not ready!\n");
	}
	//=================================================
	
	//==============blur the texture, second pass(vertical blur)================================
	// this time, render directly to window system framebuffer

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthMask(GL_FALSE);
	// reset the mvpMatrix to identity matrix so that it renders fully on texture in normalized device coordinates
	glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, Matrix4::identity().data);
	
	// draw the texture that has been horizontally blurred, and apply vertical blurring
	glUniform1i(glGetUniformLocation(GprogramID, "uBlurDirection"), -1); 
	DrawSquare(GfullscreenTexture);
	//======================================================

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glUniform1i(glGetUniformLocation(GprogramID, "uBlurDirection"), 1);
	DrawSquare(GtextureBlurred);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthMask(GL_TRUE);

	
}



int main(void)
{
  glfwSetErrorCallback(error_callback);

  // Initialize GLFW library
  if (!glfwInit())
    return -1;

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // Create and open a window
  window = glfwCreateWindow(WINDOW_WIDTH,
                            WINDOW_HEIGHT,
                            "Hello World",
                            NULL,
                            NULL);

  if(!window)
  {
    glfwTerminate();
    printf("glfwCreateWindow Error\n");
    exit(1);
  }

  glfwMakeContextCurrent(window);

  Init();

  // Repeat
  while(!glfwWindowShouldClose(window))
  {
	  Draw();	 
	  glfwSwapBuffers(window);
	  glfwPollEvents();

	  if(glfwGetKey(window, GLFW_KEY_ESCAPE))
			break;
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
