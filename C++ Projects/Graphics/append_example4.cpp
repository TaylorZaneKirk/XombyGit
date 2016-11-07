//
// Display a color cube
//
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.  We us an orthographic projection
//   as the default projetion.
#include <string>
#include "Model.h"
//----------------------------------------------------------------------------

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int      Axis = Xaxis;
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };
GLuint  theta;
//----------------------------------------------------------------------------

//Initialize the model to draw
const int numModels = 3;
Model myObj[numModels] = { "someshapes.obj", "cube.obj", "drawcube.obj" };
GLuint vao[numModels];

int frame, fps, time, timebase, selectedModel = 0;
int speed = 1;

mat4 projection;
GLuint modelviewLoc;
GLuint projectionLoc;
GLfloat aspect = 1.0;
GLfloat zoom = 45.0;
GLfloat pnear;
GLfloat pfar;
GLfloat zeye;
GLfloat bmax;
vec3 cb;
vec4 eye;

// Load shaders and use the resulting shader program
GLuint program;
//----------------------------------------------------------------------------

void init(){

	glGenVertexArrays(numModels, vao);
	program = InitShader("vshader_a4.glsl", "fshader_a4.glsl");
	glUseProgram(program);

	for (int i = 0; i < numModels; i++){
		glBindVertexArray(vao[i]);
		myObj[i].load(program);
	}
	glBindVertexArray(vao[0]);

	theta = glGetUniformLocation(program, "theta");

	modelviewLoc = glGetUniformLocation(program, "modelView");
	projectionLoc = glGetUniformLocation(program, "projection");

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
//----------------------------------------------------------------------------

void display(void){

	mat4 model_view;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 rot = RotateX(Theta[Xaxis]) * RotateY(Theta[Yaxis]) * RotateZ(Theta[Zaxis]);
	glUniform3fv(theta, 1, Theta);

	eye = vec4(0.0, 0.0, zeye, 1.0);
	model_view = LookAt(eye, cb, vec4(0.0, 1.0, 0.0, 1.0));
	model_view *= rot;
	glUniformMatrix4fv(modelviewLoc, 1, GL_TRUE, model_view);

	myObj[selectedModel].draw();

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	char displayString[100];

	if (time - timebase > 1000){
		fps = (frame * 1000.0) / (time - timebase);
		sprintf(displayString, "Taylor's Rotating Object: FPS: %d ", fps);
		glutSetWindowTitle(displayString);
		timebase = time;
		frame = 0;
	}
	
	glutSwapBuffers();
	
};
//----------------------------------------------------------------------------

void reshape(int width, int height){
	glViewport(0, 0, width, height);
	aspect = GLfloat(width) / height;

	bmax = myObj[selectedModel].getLength();
	cb = myObj[selectedModel].getCenter();
	pnear = bmax;
	pfar = pnear + 10 * bmax;
	zeye = 2 * bmax + cb.z;
	eye = vec4(0.0, 0.0, zeye, 1.0);

	projection = Perspective(zoom, aspect, pnear, pfar);
	glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, projection);
}

void keyboard( unsigned char key, int x, int y )
{
	switch( key ) {
	case 033: // Escape Key
	case 'q': case 'Q':
		exit( EXIT_SUCCESS );
		break;

	case 's':
		Theta[0] = Theta[1] = Theta[2] = 0.0;
		zoom = 45.0;
		selectedModel = (selectedModel + 1) % numModels;

		glBindVertexArray(vao[selectedModel]);

		bmax = myObj[selectedModel].getLength();
		cb = myObj[selectedModel].getCenter();
		pnear = bmax;
		pfar = pnear + 10 * bmax;
		zeye = 2 * bmax + cb.z;
		eye = vec4(0.0, 0.0, zeye, 1.0);

		projection = Perspective(zoom, aspect, pnear, pfar);
		glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, projection);
		break;

	case 'z':
		projection = Perspective(--zoom, aspect, pnear, pfar);
		glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, projection);
		break;

	case 'x':
		projection = Perspective(++zoom, aspect, pnear, pfar);
		glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, projection);
		break;
	}


}
//----------------------------------------------------------------------------

void mouse( int button, int state, int x, int y )
{
	if ( state == GLUT_DOWN ) {
		switch( button ) {
			case GLUT_LEFT_BUTTON:    Axis = Xaxis;  break;
			case GLUT_MIDDLE_BUTTON:  Axis = Yaxis;  break;
			case GLUT_RIGHT_BUTTON:   Axis = Zaxis;  break;
		}
	}
	Theta[Axis] += speed;
}
//----------------------------------------------------------------------------

void idle( void ){


	if (Theta[Axis] > 360.0) {
		Theta[Axis] -= 360.0;
	}
	
	glutPostRedisplay();
}
//----------------------------------------------------------------------------

int main( int argc, char **argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( 512, 512 );
	glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );
	glutCreateWindow( "3D Object Viewer (.Obj)" );
	glewExperimental = GL_TRUE;
	
	glewInit();

	init();

	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );
	glutMouseFunc( mouse );
	glutReshapeFunc( reshape );
	glutIdleFunc( idle );

	glutMainLoop();
	return 0;
}
