#include "Light.h"

void Light::update(glm::vec3 lightColor, glm::vec3 direction)
{
	this->colour = lightColor;
	this->direction = direction;

	glUniform3fv(uColor,1, glm::value_ptr(this->colour));
	glUniform3fv(uDirection, 1, glm::value_ptr(this->direction));
}

Light::Light(uint32_t shaderProgram)
	:colour(glm::vec3(1.f, 1.f, 1.f)),
	 direction(glm::vec3(0.f,-1.f,0.f)),
	 program(shaderProgram)
{
	
	uColor = glGetUniformLocation(program, "directionalLight.colour");
	uDirection = glGetUniformLocation(program, "directionalLight.direction");
}

Light::~Light()
{
}
