#include <iostream>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <Primitives\Vertex.h>
#include <Primitives\ShapeGenerator.h>
#include "Camera.h"
//maybe need shape data
using namespace std;
using glm::vec3;
using glm::mat4;
extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;
Camera camera;
 GLushort windowX = 800;
 GLushort windowY = 600;
 GLuint programID;
 GLuint numIndices;
 GLuint cycleIndex;
 GLfloat floatcycleIndex;
void sendDataToOpeGl(){
	ShapeData shape = ShapeGenerator::makeCube();
	/*
	const GLfloat triangleREDz = 0.5f;
	const GLfloat triangleGreenz = -0.5f;
	Vertex verts[] = {
		glm::vec3(+0.0f,-1.0f,triangleREDz),//x,y,z
		glm::vec3(+1.0f,+0.0f,+0.0f),//RGB
		glm::vec3(+1.0f,+1.0f,triangleREDz),
		glm::vec3(+1.0f,+0.0f,+0.0f),
		glm::vec3(-1.0f,+1.0f,triangleREDz),
		glm::vec3(+1.0f,+0.0f,+0.0f),
		//NEW TRIANGLE
		glm::vec3(-1.0f,-1.0f,triangleGreenz),
		glm::vec3(+0.0f,+1.0f,+0.0f),
		glm::vec3(+1.0f,-1.0f,triangleGreenz),
		glm::vec3(+0.0f,+1.0f,+0.0f),
		glm::vec3(+0.0f,+1.0f,triangleGreenz),
		glm::vec3(+0.0f,+1.0f,+0.0f),

	};
	*/

	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);//AttribArray uses currently bound vertex array object, glEnableVertexArrayAttrib updates state of the vertex array object with ID vaobj.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));


	//GLushort indices[] = { 0,1,2,3,4,5 };
	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	numIndices = shape.numIndices;
	shape.cleanUp();//delete shape off heap
	//instanced drawing
	GLuint transformBufferID;
	glGenBuffers(1, &transformBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, transformBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mat4)*2, 0, GL_DYNAMIC_DRAW);// mat4 * 2 because 2 squares will be drawn,0 paramater sends data later
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 0));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 4));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 8));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 12));
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

}
void draw() {
	glClearColor(0.0f / 255, 0.0f / 255, 153.0f / 255, 1);//BGCOLOR
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears both buffers
	glViewport(0,0, windowX, windowY);
	//Buffers need to before drawing
	cycleIndex += 1;
	if (cycleIndex % 60 == 0) { cycleIndex = 0; floatcycleIndex += 1; if (floatcycleIndex >= 360) { floatcycleIndex = 0; } }

	mat4 ProjectionTransformMatrix = glm::perspective(glm::radians(90.0f), ((GLfloat)windowX) / windowY, 1.0f, 300.0f);
	mat4 TranslateTransformMatrix = glm::translate(ProjectionTransformMatrix, vec3(-4.0f, 2.0f, -6.0f));
	mat4 TransformMatrix = glm::rotate(TranslateTransformMatrix, glm::radians(floatcycleIndex), vec3(-1.0f, -1.0f, 0.0f));
	GLint TransformMatrixLocation = glGetUniformLocation(programID, "TransformMatrix");
	glUniformMatrix4fv(TransformMatrixLocation, 1, GL_FALSE, &TransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
	//Uniforms
	TransformMatrixLocation = glGetUniformLocation(programID, "TransformMatrix");
	//cube 2
	TranslateTransformMatrix = glm::translate(ProjectionTransformMatrix, vec3(3.0f, 2.0f, -6.0));
	TransformMatrix = glm::rotate(TranslateTransformMatrix, glm::radians(floatcycleIndex), vec3(0.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(TransformMatrixLocation, 1, GL_FALSE, &TransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
	//shit ton of cubes
	for(int i=0;i<60;i++){
		TranslateTransformMatrix = glm::translate(ProjectionTransformMatrix, vec3(-5.0f+((float)i)*((float)i)/10, -3.0f, ((float)i)*-3.0f));
		TransformMatrix = glm::rotate(TranslateTransformMatrix, glm::radians(0.0f + ((float)i)*30.0f), vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(TransformMatrixLocation, 1, GL_FALSE, &TransformMatrix[0][0]);

		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
	}
		
	//glDrawArrays(GL_TRIANGLES, 0, 6); drawElements is better for optimizing shared vertexes and is faster in every way or so i heard.
	//glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}
void drawInstanced() {
	//animation logic
	cycleIndex += 1;//60 times faster than floatcycleIndex
	if (cycleIndex % 60 == 0) { cycleIndex = 0; floatcycleIndex += 1; if (floatcycleIndex >= 360) { floatcycleIndex = 0; } }
	//Projection
	mat4 ProjectionTransformMatrix = glm::perspective(glm::radians(60.0f), ((GLfloat)windowX) / windowY, 1.0f, 100.0f);
	mat4 cameraMatrix = ProjectionTransformMatrix*camera.getModelToWorldMatrix();
	//cube 1
	mat4 TranslateTransformMatrix = glm::translate(cameraMatrix, vec3(-4.0f, 2.0f, -6.0f));
	mat4 TransformMatrix = glm::rotate(TranslateTransformMatrix, glm::radians(floatcycleIndex+30.0f), vec3(-1.0f, -1.0f, 0.0f));
	//cube 2
	mat4 TranslateTransformMatrix2 = glm::translate(cameraMatrix, vec3(3.0f, 2.0f, -6.0));
	mat4 TransformMatrix2 = glm::rotate(TranslateTransformMatrix2, glm::radians(floatcycleIndex+60.0f), vec3(0.0f, 1.0f, 1.0f));

	mat4 TransForms[] = {
		TransformMatrix,TransformMatrix2
	};

	//Send GL BUFFERS
	glBufferData(GL_ARRAY_BUFFER, sizeof(TransForms), TransForms, GL_DYNAMIC_DRAW);
	//
	glClearColor(0.0f / 255, 0.0f / 255, 153.0f / 255, 1);//BGCOLOR
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears both buffers
	glViewport(0, 0, windowX, windowY);
	//Buffers need to be cleared before drawing
	glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0, 2);
}
bool checkStatus(GLuint objectID,PFNGLGETSHADERIVPROC  functionIVPointer, PFNGLGETSHADERINFOLOGPROC getInfoLog,GLenum statusType) {
	GLint status;
	functionIVPointer(objectID, statusType, &status);
	if (status != GL_TRUE) {
		GLint infoLogLength;
		functionIVPointer(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLog(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		delete[] buffer;
		return false;
	}

	return true;
}
bool checkShaderStatus(GLuint shaderID) {
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}
bool checkProgramStatus(GLuint programID) {
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}
void installShaders() {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* adapter[1];
	adapter[0] = vertexShaderCode;
	glShaderSource(vertexShaderID,1,adapter,0);
	adapter[0] = fragmentShaderCode;
	glShaderSource(fragmentShaderID, 1, adapter, 0);


	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
	{
		cout << "error compiling shader";
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
	{
		cout << "error linking program";
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);

	
	/* UNIFORMS
	vec3 mainColorsColor(0.0f, 1.0f, 0.0f);
	GLint mainColorLocation = glGetUniformLocation(programID, "mainColor");
	glUniform3fv(mainColorLocation,1, &mainColorsColor[0]);
	GLint yFlipLocation = glGetUniformLocation(programID, "yFlip");
	glUniform1f(yFlipLocation, -1.0f);
	*/
}
int main() {

#pragma region WindowGLEWSetup
	sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.depthBits = 24;

	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Window Title Here!", sf::Style::Default, settings);
	window.setActive(true);
	window.setMouseCursorVisible(false);
	camera.setMouseOrigin(glm::vec2(windowX, windowY));
	
	glewExperimental = true;
	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		std::cout << "Glew failed to Initialize" << glewGetErrorString(result) << std::endl;
	}
#pragma endregion WindowGLEWSetup 
	// load resources, initialize the OpenGL states, ...
	glEnable(GL_DEPTH_TEST);
	installShaders();
	sendDataToOpeGl();
	bool running = true;
	cycleIndex = 0;
	sf::Clock clock; // starts the clock
	sf::Time deltaTime = clock.getElapsedTime();
	while (running)
	{
		camera.deltaTime(deltaTime.asSeconds());
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			switch (ev.type) {
				case sf::Event::Closed:
					running = false;
					break;
				case sf::Event::Resized:
					glViewport(0, 0, ev.size.width, ev.size.height);
					windowX = ev.size.width;
					windowY = ev.size.height;
					camera.setMouseOrigin(glm::vec2(windowX, windowY));
					break;
				case sf::Event::MouseMoved:
					camera.mouseUpdate(glm::vec2(-ev.mouseMove.x, -ev.mouseMove.y));// flip signs to invert mouse
					sf::Mouse::setPosition(sf::Vector2i(windowX / 2, windowY / 2), window);
					//repaint();
					break;
				}
		}
		//handle keyboard input //not an event because it stutters more
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			running = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			camera.moveForward();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			camera.moveLeft();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			camera.moveBackward();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			camera.moveRight();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			camera.moveUp();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			camera.moveDown();
		}
		// clearing buffers are done in draw
		
		//draw();
		drawInstanced();
		deltaTime = clock.restart();//restarts and returns deltaTime
		// end the current frame (internally swaps the front and back buffers)
		window.display();//error occurs if you display after the window closses.
		
	}
	//release resources here
	glUseProgram(0);
	glDeleteProgram(programID);
	window.close();

	return 0;
}