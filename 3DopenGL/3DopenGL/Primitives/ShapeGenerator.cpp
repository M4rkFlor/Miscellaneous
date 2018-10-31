#include "ShapeGenerator.h"
#include<glm\glm.hpp>
#include<Primitives\Vertex.h>
#define NUM_ARRAY_ELEMENTS(Array) sizeof(Array) / sizeof(*Array);
using glm::vec3;
ShapeData ShapeGenerator::makeTriangle() {
	ShapeData generatedShape;
	const GLfloat triangleREDz = -0.5f;
	const GLfloat triangleGreenz = 0.5f;
	//lower z redered on top
	Vertex TriangleVerts[] = {
		glm::vec3(+0.0f,-1.0f,triangleREDz),//x,y,z
		glm::vec3(+1.0f,+0.0f,+0.0f),//RGB
		glm::vec3(+1.0f,+1.0f,triangleREDz),
		glm::vec3(+0.0f,+1.0f,+0.0f),
		glm::vec3(-1.0f,+1.0f,triangleREDz),
		glm::vec3(+0.0f,+0.0f,+1.0f),
		//NEW TRIANGLE
		glm::vec3(-1.0f,-1.0f,triangleGreenz),
		glm::vec3(+0.0f,+1.0f,+0.0f),
		glm::vec3(+1.0f,-1.0f,triangleGreenz),
		glm::vec3(+0.0f,+0.0f,+1.0f),
		glm::vec3(+0.0f,+1.0f,triangleGreenz),
		glm::vec3(+1.0f,+0.0f,+0.0f),

	};
	GLushort indices[] = { 0,1,2,3,4,5 };
	generatedShape.numVertices = NUM_ARRAY_ELEMENTS(TriangleVerts);
	generatedShape.vertices = new Vertex[generatedShape.numVertices];//alloc space on Heap
	memcpy(generatedShape.vertices, TriangleVerts, sizeof(TriangleVerts));//copy local stack data to location on heap
	//
	generatedShape.numIndices = NUM_ARRAY_ELEMENTS(indices);
	generatedShape.indices = new GLushort[generatedShape.numIndices];//alloc space on Heap
	memcpy(generatedShape.indices, indices, sizeof(indices));//copy local stack data to location on heap

	return generatedShape;
}

ShapeData ShapeGenerator::makeCube() {
	ShapeData ret;
	Vertex stackVerts[] = {
		vec3(-1.0f, +1.0f, +1.0f), // 0
		vec3(+1.0f, +0.0f, +0.0f), // Color
		vec3(+1.0f, +1.0f, +1.0f), // 1
		vec3(+0.0f, +1.0f, +0.0f), // Color
		vec3(+1.0f, +1.0f, -1.0f), // 2
		vec3(+0.0f, +0.0f, +1.0f), // Color
		vec3(-1.0f, +1.0f, -1.0f), // 3
		vec3(+1.0f, +1.0f, +1.0f), // Color

		vec3(-1.0f, +1.0f, -1.0f), // 4
		vec3(+1.0f, +0.0f, +1.0f), // Color
		vec3(+1.0f, +1.0f, -1.0f), // 5
		vec3(+0.0f, +0.5f, +0.2f), // Color
		vec3(+1.0f, -1.0f, -1.0f), // 6
		vec3(+0.8f, +0.6f, +0.4f), // Color
		vec3(-1.0f, -1.0f, -1.0f), // 7
		vec3(+0.3f, +1.0f, +0.5f), // Color

		vec3(+1.0f, +1.0f, -1.0f), // 8
		vec3(+0.2f, +0.5f, +0.2f), // Color
		vec3(+1.0f, +1.0f, +1.0f), // 9
		vec3(+0.9f, +0.3f, +0.7f), // Color
		vec3(+1.0f, -1.0f, +1.0f), // 10
		vec3(+0.3f, +0.7f, +0.5f), // Color
		vec3(+1.0f, -1.0f, -1.0f), // 11
		vec3(+0.5f, +0.7f, +0.5f), // Color

		vec3(-1.0f, +1.0f, +1.0f), // 12
		vec3(+0.7f, +0.8f, +0.2f), // Color
		vec3(-1.0f, +1.0f, -1.0f), // 13
		vec3(+0.5f, +0.7f, +0.3f), // Color
		vec3(-1.0f, -1.0f, -1.0f), // 14
		vec3(+0.4f, +0.7f, +0.7f), // Color
		vec3(-1.0f, -1.0f, +1.0f), // 15
		vec3(+0.2f, +0.5f, +1.0f), // Color

		vec3(+1.0f, +1.0f, +1.0f), // 16
		vec3(+0.6f, +1.0f, +0.7f), // Color
		vec3(-1.0f, +1.0f, +1.0f), // 17
		vec3(+0.6f, +0.4f, +0.8f), // Color
		vec3(-1.0f, -1.0f, +1.0f), // 18
		vec3(+0.2f, +0.8f, +0.7f), // Color
		vec3(+1.0f, -1.0f, +1.0f), // 19
		vec3(+0.2f, +0.7f, +1.0f), // Color

		vec3(+1.0f, -1.0f, -1.0f), // 20
		vec3(+0.8f, +0.3f, +0.7f), // Color
		vec3(-1.0f, -1.0f, -1.0f), // 21
		vec3(+0.8f, +0.9f, +0.5f), // Color
		vec3(-1.0f, -1.0f, +1.0f), // 22
		vec3(+0.5f, +0.8f, +0.5f), // Color
		vec3(+1.0f, -1.0f, +1.0f), // 23
		vec3(+0.9f, +1.0f, +0.2f), // Color
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(stackVerts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

	unsigned short stackIndices[] = {
		0,   1,  2,  0,  2,  3, // Top
		4,   5,  6,  4,  6,  7, // Front
		8,   9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, stackIndices, sizeof(stackIndices));

	return ret;
}

/*
ShapeGenerator::ShapeGenerator()
{
}
ShapeGenerator::~ShapeGenerator()
{
}
*/
