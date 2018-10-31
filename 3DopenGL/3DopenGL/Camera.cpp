#include "Camera.h"
#include <glm\gtx\transform.hpp>
#include<iostream>
//Member initialization in constructors
Camera::Camera():
	viewDirection(0.0f,0.0f,-1.0f),
	UP(0.0f,1.0f,0.0f)
{
}

glm::mat4  Camera::getModelToWorldMatrix() const {
	return glm::lookAt(position,position + viewDirection,UP);
}

void Camera::mouseUpdate(const glm::vec2 &newMousePos) {
	glm::vec2 deltaMouse = newMousePos + MouseOrigPos; // flip sign to invert mouse
	glm::vec3 rotateAround = glm::cross(viewDirection,UP);
	/*viewDirection = glm::mat3(glm::rotate(glm::radians(deltaMouse.y * mouseSens), glm::vec3(1.0f, 0.0f, 0.0f))) * 
					glm::mat3(glm::rotate(glm::radians(deltaMouse.x * mouseSens), UP)) * viewDirection;
	*/
	//camera does 180 when looking up need to fix down
			oldViewDirection = viewDirection;//save a valid position to revert to
			//only rotate if valid not working yet
			viewDirection = glm::mat3(glm::rotate(glm::radians(deltaMouse.x * mouseSens), UP) *
				glm::rotate(glm::radians(deltaMouse.y * mouseSens), rotateAround)) *
				viewDirection;
		//clamp the x rotation
		if (viewDirection.y > 0.999f) {
			viewDirection = oldViewDirection;
			viewDirection.y = 0.999f;
		}
}

void Camera::setMouseOrigin(const glm::vec2 &windowSize)
{
	MouseOrigPos = glm::vec2(windowSize.x / 2, windowSize.y / 2);
}
void Camera::deltaTime(const float &_deltaTime) {
	mydeltaTime = _deltaTime;
}
//Movement
const float MovementSpeed = 10.0f;
void Camera::moveForward() {
	position += MovementSpeed * viewDirection * mydeltaTime;
}
void Camera::moveLeft() {
	position += -MovementSpeed * glm::cross(viewDirection, UP) * mydeltaTime;
}
void Camera::moveBackward() {
	position += -MovementSpeed * viewDirection * mydeltaTime;
}
void Camera::moveRight() {
	position += MovementSpeed * glm::cross(viewDirection, UP) * mydeltaTime;
}
void Camera::moveUp() {
	position += MovementSpeed * UP * mydeltaTime;
}
void Camera::moveDown() {
	position += -MovementSpeed * UP * mydeltaTime;
}