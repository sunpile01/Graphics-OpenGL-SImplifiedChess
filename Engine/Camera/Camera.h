/**
* @file Camera.h
* 
* @brief Class for creating the base camera without any type of projection
* 
* @author Rafael Palomar
*/
#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

class Camera
{
public:
	Camera() = default;
	~Camera() = default;

	// Get camera matrices
	const glm::mat4& GetProjectionMatrix() const
	{
		return this->ProjectionMatrix;
	}
	const glm::mat4& GetViewMatrix() const
	{
		return this->ViewMatrix;
	}
	const glm::mat4& GetViewProjectionMatrix() const
	{
		return this->ViewProjectionMatrix;
	}
	const glm::vec3& GetPosition() const
	{
		return this->Position;
	}
	void SetPosition(const glm::vec3& pos)
	{
		this->Position = pos; this->RecalculateMatrix();
	}


protected:
	virtual void RecalculateMatrix() = 0;

protected:
	Camera(const Camera& camera)
	{
		this->ProjectionMatrix = camera.ProjectionMatrix;
		this->ViewMatrix = camera.ViewMatrix;
		this->Position = camera.Position;
		this->ViewProjectionMatrix = camera.ViewProjectionMatrix;
	}

protected:
	glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
	glm::mat4 ViewMatrix = glm::mat4(1.0f);
	glm::mat4 ViewProjectionMatrix = glm::mat4(1.0f);
	glm::vec3 Position = glm::vec3(0.0f);
};

#endif // CAMERA_H_


/*
My implementation of the camera class before you realeased issue 22 
Was not fully developed yet

#pragma once
#ifndef Camera_H
#define Camera_H
#include <glm/glm.hpp>
#include <glad/glad.h>

struct Frustrum {
	float angle;
	float width;
	float height;
	float near;
	float far;
};

class Camera {
public:
	Camera() = default;
	const virtual glm::mat4& GetProjectionMatrix() = 0;
	const virtual glm::mat4& GetViewMatrix() = 0;
	const virtual glm::mat4& GetProjectionViewMatrix() = 0;
	const virtual glm::mat4& GetModelMatrix() = 0;
	const virtual glm::mat4& GetMVPMatrix() = 0;
	virtual void setFrustrum(const Frustrum& frustrum) = 0;

	const glm::vec3& GetPosition() const { return this->Position; }
	void SetPosition(const glm::vec3& pos) { this->Position = pos; this->RecalculateMatrix(); }


protected: 
	virtual void RecalculateMatrix() = 0;

private: 
	glm::vec3 Position;
};

#endif

*/