#include "Model.h"
//----------------------------------------------------------------------------

Model::Model(){} //default constructor; unused.
//----------------------------------------------------------------------------

Model::Model(string name){	

	FILE * file = fopen(name.c_str(), "r"); //fopen inherited from C; needs c-strings
	if (file == NULL){
		printf("Cannot locate object file...\n");
	}

	while (true){

		char input[128]; //this hard-cap limit could cause issues...

		// read the first word of the line
		int res = fscanf(file, "%s", input);
		if (res == EOF)
			break; // EOF

		//compare first word with various flags
		if (strcmp(input, "v") == 0){
			vec4 vertex(0.0, 0.0, 0.0, 1.0);

			//fscanf( stream, format, storage location(s) ) 
			//reads formatted data from an input stream and stores for use
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			if (abs(vertex.x) > abs(extX))
				extX = vertex.x;
			if (abs(vertex.y) > abs(extY))
				extY = vertex.y;
			if (abs(vertex.z) > abs(extZ))
				extZ = vertex.z;
			
			if ((abs(vertex.x) > abs(vertex.y)) && 
				(abs(vertex.x) > abs(vertex.z)) && 
				(abs(vertex.x) > boxLength)){

				boxLength = abs(vertex.x);
			}
			else if ((abs(vertex.y) > abs(vertex.z)) && 
				(abs(vertex.y) > boxLength)){

				boxLength = abs(vertex.y);
			}
			else if (abs(vertex.z) > boxLength){

				boxLength = abs(vertex.z);
			}

			vertices.push_back(vertex);
			numvertices++;	//total number of vertices
		}
		else if (strcmp(input, "vn") == 0){
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(input, "f") == 0){
			GLuint vertexIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n",
				&vertexIndex[0], &normalIndex[0],
				&vertexIndex[1], &normalIndex[1],
				&vertexIndex[2], &normalIndex[2]);

			if (matches != 6){
				printf("File is incorrect in format\n");
			}

			//Translate from 1-index to 0-index (This is used for glDrawElements())
			/*vertexIndices.push_back(vertexIndex[0] - 1);
			vertexIndices.push_back(vertexIndex[1] - 1);
			vertexIndices.push_back(vertexIndex[2] - 1);*/

			//Still uses vertex indices, circumvents the need for seperate
			//	array by using the index obtained in series from the
			//	vertexIdex array as the index into the vertices array
			//	in order to store the appropriate vertex into the points array
			points.push_back(vertices[(vertexIndex[0] - 1)]);
			points.push_back(vertices[(vertexIndex[1] - 1)]);
			points.push_back(vertices[(vertexIndex[2] - 1)]);

			normalIndices.push_back(normalIndex[0] - 1);
			normalIndices.push_back(normalIndex[1] - 1);
			normalIndices.push_back(normalIndex[2] - 1);
		}
	}

	//number of indices
	/*numberOfPoints = vertexIndices.size(); //(This is used for glDrawElements())*/
	numberOfPoints = points.size();
}		
//----------------------------------------------------------------------------

void Model::load(GLuint program){

	//each vertex needs 16-bytes
	/*int size = numvertices * 16; //(This is used for glDrawElements())*/
	int size = numberOfPoints * 16;

	// Create and initialize a buffer object
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size + size, NULL, GL_STATIC_DRAW);

	//Bind vertices to buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, &points[0]);
	glBufferSubData(GL_ARRAY_BUFFER, size, size, &points[0]); //color hack

	// set up vertex arrays
	//VertexShader
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	//Fragment Shader
	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(size));
}
//----------------------------------------------------------------------------

void Model::draw(){
	glDrawArrays(GL_TRIANGLES, 0, numberOfPoints);
}
//----------------------------------------------------------------------------

float Model::getLength(){
	float point1;
	float point2;
	float distance;

	if (abs(extX) > abs(extY) && abs(extX) > abs(extZ)){
		point1 = abs(extX);
		if (abs(extY) > abs(extZ))
			point2 = abs(extY);
		else
			point2 = abs(extZ);
	}
	else if (abs(extY) > abs(extZ)){
		point1 = abs(extY);
		if (abs(extX) > abs(extZ))
			point2 = abs(extX);
		else
			point2 = abs(extZ);
	}
	else{
		point1 = abs(extZ);
		if (abs(extX) > abs(extY))
			point2 = abs(extX);
		else
			point2 = abs(extY);
	}

	distance = sqrt((point1 * point1) + (point2 * point2));
	return distance * 1.3;
}

vec3 Model::getCenter(){
	return (vec3(0.0, 0.0, 0.0));
}

Model::~Model(){}
