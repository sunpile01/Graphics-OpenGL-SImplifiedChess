/**
* @file PerspectiveCamera.h
*
* @brief Subclass of camera that creates an ortographic projeciton for the camera.
*
* @author Aleksander Solhaug, Rafael Palomar
*/

#ifndef ORTHOGRAPHICCAMERA_H_
#define ORTHOGRAPHICCAMERA_H_

#include "Camera.h"

#include <glm/fwd.hpp>

#include <array>

class OrthographicCamera : public Camera
{
public:

	struct Frustrum {
		float left;
		float right;
		float bottom;
		float top;
		float near;
		float far;
	};

public:
	OrthographicCamera(const Frustrum& frustrum = { -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f },
		const glm::vec3& position = glm::vec3(0.0f), float rotation = 0.0f) {
		this->Rotation = rotation;
		this->Position = position;
		this->CameraFrustrum = frustrum;

		Camera::ProjectionMatrix = glm::ortho(CameraFrustrum.left, CameraFrustrum.right,
			CameraFrustrum.bottom, CameraFrustrum.top, CameraFrustrum.near, CameraFrustrum.far);
		Camera::ViewMatrix = glm::lookAt(Position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		Camera::ViewProjectionMatrix = Camera::ProjectionMatrix * Camera::ViewMatrix;

	}
	~OrthographicCamera() = default;

	OrthographicCamera(const OrthographicCamera& camera) : Camera(camera)
	{
		this->Rotation = camera.Rotation;
		this->CameraFrustrum = camera.CameraFrustrum;
	}

	void SetRotation(float rotation)
	{
		this->Rotation = rotation; this->RecalculateMatrix();
	}

	void SetFrustrum(const Frustrum& frustrum)
	{
		this->CameraFrustrum = frustrum; this->RecalculateMatrix();
	}

protected:
	/**
	*	@brief Recalculating both the projection and view matrix for the camera
	*/
	void RecalculateMatrix() {
		Camera::ProjectionMatrix = glm::ortho(CameraFrustrum.left, CameraFrustrum.right,
			CameraFrustrum.bottom, CameraFrustrum.top, CameraFrustrum.near, CameraFrustrum.far);
		Camera::ViewMatrix = glm::lookAt(Position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		Camera::ViewProjectionMatrix = Camera::ProjectionMatrix * Camera::ViewMatrix;
	}

protected:
	float Rotation; // in degrees around the Z axis
	Frustrum CameraFrustrum;
};

#endif // ORTHOGRAPHICCAMERA_H_


/*
My implementation attempt before you published the camerea class issue 
This was not fully developed yet

#pragma once
#ifndef OrtographicCamera_H
#define OrtographicCamera_H

#include <Camera.h>

class OrtographicCamera : public Camera {
public:
	OrtographicCamera(const std::array<float, 6>& frustrum = (-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f),
														const glm::vec3& position, float rotation) 
	{
		this->Position = position;
		this->Rotation = rotation;
		this->Frustrum = frustrum;
		this->RecalculateMatrix();
	}
	virtual void OrtographicCamera::RecalculateMatrix() {
		//Calculate Projection Matrix
		this->ProjectionMatrix = glm::ortho(this->Frustrum[0], this->Frustrum[1],
										this->Frustrum[2], this->Frustrum[3]);
		
		//Calculate View matrix
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f). this->Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(this->Rotation),
				glm::vec3(0.0f, 0.0f, 1.0f));

		this->ViewMatrix = glm::inverse(transform);

		//Calculate projection view matrix
		this->ProjecitonViewMatrix = this->ProjectionMatrix * this->ViewMatrix;
	}
private:
	glm::vec3 Position;
	float Rotation;
	std::is_array <float, 6>& Frustrum;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjecitonViewMatrix;
};
#endif*/