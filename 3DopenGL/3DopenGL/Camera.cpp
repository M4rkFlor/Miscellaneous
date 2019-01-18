#include "Camera.h"
#include <glm\gtx\transform.hpp>
#include<iostream>
//Member initialization in constructors
Camera::Camera():
	viewDirection(0.0f,0.0f,-1.0f),
	UP(0.0f,1.0f,0.0f)
{
}

glm::vec3 Camera::getPosition() const
{
	return position;
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
			
			//oldViewDirection = viewDirection;//save a valid position to revert to//not needed
			//camera does 180 when looking up or down
			float dontRotate = 1.0f;
			glm::vec3 tempYrot = glm::mat3(glm::rotate(glm::radians(deltaMouse.y * mouseSens), rotateAround))*viewDirection;
			//only rotate if valid
			if (tempYrot.y > 0.999f || tempYrot.y < -0.999f){
				dontRotate = 0.0f;
			}

			viewDirection = glm::mat3(glm::rotate(glm::radians(deltaMouse.y * mouseSens * dontRotate), rotateAround)*
				glm::rotate(glm::radians(deltaMouse.x * mouseSens), UP) 
				) *
				viewDirection;

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