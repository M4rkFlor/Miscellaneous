#pragma once
#include <GL/glew.h>
#include <Primitives\Vertex.h>
struct ShapeData {
	ShapeData() :
		vertices(0), numVertices(0), indices(0), numIndices(0){}

	Vertex* vertices;
	GLuint numVertices;
	//An array of indices that choose the order to read vertices Data
	GLushort* indices;
	GLuint numIndices;
	GLsizeiptr vertexBufferSize() const
	{
		return numVertices * sizeof(Vertex);
	}
	GLsizeiptr indexBufferSize() const
	{
		return numIndices * sizeof(GLushort);
	}
	void cleanUp() {
		delete[] vertices;
		delete[] indices;
		numVertices = numIndices = 0;
		vertices = 0;
		indices = 0;
	}
};