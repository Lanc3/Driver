#include "Model.h"


Model::Model()
{

}
Model::Model(string name, glm::vec3 startingPosition,glm::vec3 scale,float rotation)
{
	minModelPoint = glm::vec4(9999999999, 9999999999, 9999999999, 1);
	maxModelPoint = glm::vec4(-9999999999999, -9999999999999, -9999999999999, 1);
	worldScale = scale;
	worldRotationSpeed = rotation;
	worldRotation = glm::vec3(0, 1, 0);
	worldPosition = startingPosition;
	MakeModel(name);
}


void Model::MakeModel(string name)
{
	m_shader = ResourceManager::getInstance()->GetShader("model");
	meshes = ResourceManager::getInstance()->getInstance()->GetMesh(name);
	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i].model = glm::translate(model, worldPosition) * glm::rotate(model, worldRotationSpeed, worldRotation)* glm::scale(model, worldScale);
	}
}

void Model::Draw(Camera* cam, Shader shader)
{
	for (GLuint i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(cam,m_shader);
	}
}

void Model::Translate(glm::vec3 value)
{
	for (GLuint i = 0; i < meshes.size(); i++)
	{
		glLoadIdentity();
		meshes[i].model = glm::translate(meshes[i].model, value);
	}
}

void Model::Rotate(float angle)
{
	for (GLuint i = 0; i < meshes.size(); i++)
	{
		glLoadIdentity();
		meshes[i].model = glm::rotate(meshes[i].model, angle, glm::vec3(0, 1, 0));
	}
	
}

void Model::Update()
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i].model = glm::translate(model, worldPosition) * glm::rotate(model, worldRotationSpeed, worldRotation)* glm::scale(model, worldScale);
		
		this->meshes[i].model = glm::rotate(meshes[i].model, bank, glm::vec3(0, 0, 1));
		this->meshes[i].model = glm::rotate(meshes[i].model, pitch, glm::vec3(1, 0, 0));
	}
}

void Model::setPosition(glm::vec3 pos)
{
	worldPosition = pos;
}

void Model::setScale(glm::vec3 scale)
{
	worldScale = scale;	
}

void Model::setRotationSpeed(float speed)
{
	worldRotationSpeed = speed;
}

void Model::setRotation(glm::vec3 rotation, float speed, GLfloat m_bank, GLfloat m_pitch)
{
	worldRotation = rotation;
	worldRotationSpeed = speed;

	bank = -m_bank;
	pitch = m_pitch;
}

void Model::setRotation(glm::vec3 rotation)
{
	worldRotation = rotation;
}
