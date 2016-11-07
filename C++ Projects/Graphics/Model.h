#include "Angel.h"
#include <vector>
#pragma comment(lib, "freeglut")
#pragma comment(lib, "glew32")
using namespace std;
//----------------------------------------------------------------------------

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;
const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)
//----------------------------------------------------------------------------

class Model
{
private:
	// quad generates two triangles for each face and assigns colors
	//    to the vertices
	
	int numberOfPoints = 0;
	int numvertices = 0;
	float boxLength = 0.0;

	vector<GLuint> vertexIndices, normalIndices;
	vector<vec3> temp_vertices;
	vector<vec3> temp_normals;


	GLuint iBuffer;
	GLuint buffer;

	GLfloat extX = 0.0;
	GLfloat extY = 0.0;
	GLfloat extZ = 0.0;

	vector<point4> vertices;
	vector<point4> points;

	GLuint program;
//----------------------------------------------------------------------------

public:
	Model();
	Model(string);

	void load(GLuint);
	void draw(void);
	float getLength(void);
	vec3 getCenter(void);

	~Model();
};

