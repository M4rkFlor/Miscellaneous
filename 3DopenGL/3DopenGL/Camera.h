#pragma once
#include <glm\glm.hpp>
class Camera
{
	float mouseSens = 0.05f;
	float mydeltaTime= 0.0f;
	glm::vec2 MouseOrigPos;
	glm::vec3 position;
	glm::vec3 oldViewDirection;
	glm::vec3 viewDirection;
	const glm::vec3 UP;
public:
	Camera();
	glm::vec3 getPosition() const;
	glm::mat4 getModelToWorldMatrix() const;
	void mouseUpdate(const glm::vec2 &newMousePos);
	void setMouseOrigin(const glm::vec2 &windowSize);

	void deltaTime(const float &_deltaTime);
	void moveForward();
	void moveLeft();
	void moveBackward();
	void moveRight();
	void moveUp();
	void moveDown();
};

