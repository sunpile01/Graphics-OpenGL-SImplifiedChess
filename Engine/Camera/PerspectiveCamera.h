/**
* @file PerspectiveCamera.h
* 
* @brief Subclass of camera that creates a perspective projeciton for the camera.
* 
* @author Aleksander Solhaug, Rafael Palomar
*/

#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_

#include "Camera.h"
#include "GLFWApplication.h"
#include <array>

class PerspectiveCamera : public Camera
{
public:

	struct Frustrum {
		float angle;
		float width;
		float height;
		float near;
		float far;
	};

public:
	PerspectiveCamera(const GLint width, const GLint heigth,
		const Frustrum& frustrum = { 45.0f, 800, 800, 0.1f, -10.0f},
		const glm::vec3& position = glm::vec3(0.0f, 5.0f, 7.0f),
		const glm::vec3& lookAt = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& upVector = glm::vec3(0.0f, 1.0f, 0.0f)) {

		CameraFrustrum = frustrum;
		CameraFrustrum.width = width;
		CameraFrustrum.height = heigth;
		Camera::Position = position;
		LookAt = lookAt;
		UpVector = upVector;

		Camera::ProjectionMatrix = glm::perspective(glm::radians(CameraFrustrum.angle), 
			CameraFrustrum.width / CameraFrustrum.height, CameraFrustrum.near, CameraFrustrum.far);
		Camera::ViewMatrix = glm::lookAt(Position, LookAt, UpVector);

		Camera::ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

	~PerspectiveCamera() = default;
	PerspectiveCamera(const PerspectiveCamera& camera) : Camera(camera)
	{
		this->LookAt = camera.LookAt;
		this->UpVector = camera.UpVector;
		this->CameraFrustrum = camera.CameraFrustrum;
	}

	void SetLookAt(const glm::vec3& lookAt)
	{
		this->LookAt = lookAt; this->RecalculateMatrix();
	}

	void SetUpVector(const glm::vec3& upVector)
	{
		this->UpVector = upVector; this->RecalculateMatrix();
	}
	void SetFrustrum(const Frustrum& frustrum)
	{
		this->CameraFrustrum = frustrum; this->RecalculateMatrix();
	}

protected:
	/**
	*	@brief Recalculating both the projection and view matrix for the camera
	*	
	*/
	void RecalculateMatrix() {
		Camera::ProjectionMatrix = glm::perspective(glm::radians(CameraFrustrum.angle),
			CameraFrustrum.width / CameraFrustrum.height, CameraFrustrum.near, CameraFrustrum.far);

		Camera::ViewMatrix = glm::lookAt(Camera::Position, LookAt, UpVector);

		Camera::ViewProjectionMatrix = Camera::ProjectionMatrix * Camera::ViewMatrix;
	}

protected:
	glm::vec3 LookAt;
	glm::vec3 UpVector;
	Frustrum CameraFrustrum;
};

#endif // PERSPECTIVECAMERA_H_



//The implementation attempt of the camera i created before you realeased the class 
//(Was not completely finished yet)
/*#pragma once
#ifndef PerspectiveCamera_H
#define PerspectiveCamera_H
#include <Camera.h>

class PerspectiveCamera : public Camera {
public:
	struct Frustrum {
		float angle;
		float width;
		float height;
		float near;
		float far;
	};
	PerspectiveCamera() {
		ProjectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, -10.0f);
		//First vector = eye = point where virtual 3d camera is located
		//second vector is center, point camera looks at (center of the scene)
		//third vector is Up, upwards direction in 3D world, now towards positive y
		ViewMatrix = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		//auto ModelMatrix = glm::mat4(1.0f);
		auto Rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		auto Translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		auto Scale = glm::scale(glm::mat4(1.0f), glm::vec3(8.0f, 8.0f, 8.0f));
		m_ModelMatrix = Translation * Rotation * Scale;
		MVPMatrix = ProjectionMatrix * ViewMatrix * m_ModelMatrix;
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}

	virtual void PerspectiveCamera::SetFrustrum(const Frustrum& frustrum)
	{
		this->CameraFrustrum = frustrum; this->RecalculateMatrix();
	}

	virtual void PerspectiveCamera::SetLookAt(const glm::vec3& lookAt)
	{
		this->LookAt = lookAt; this->RecalculateMatrix();
	}

	virtual void PerspectiveCamera::SetUpVector(const glm::vec3& upVector)
	{
		this->UpVector = upVector; this->RecalculateMatrix();
	}

	~PerspectiveCamera() = default;

	const virtual glm::mat4& PerspectiveCamera::GetProjectionMatrix() 
													{ return ProjectionMatrix; }
	const virtual glm::mat4& PerspectiveCamera::GetViewMatrix() 
													{ return ViewMatrix; }
	const virtual glm::mat4& PerspectiveCamera::GetModelMatrix() 
													{ return m_ModelMatrix; }
	const virtual glm::mat4& PerspectiveCamera::GetProjectionViewMatrix() 
													{ return ProjectionMatrix * ViewMatrix; }
	const virtual glm::mat4& PerspectiveCamera::GetMVPMatrix() 
													{ return  MVPMatrix; }

private:
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 m_ModelMatrix;
	glm::mat4 MVPMatrix;

protected:
	glm::vec3 LookAt = {0.0f, 0.0f, 0.0f};	//Is lookAt second vector of lookat funciton?
	glm::vec3 UpVector = { 0.0f, 1.0f, 0.0f }; // is upVector third vector of the LookAt function?
	glm::vec3 Position = { 0.0f, -1.0f, 0.0f };
	float Rotation = 90.0f;
	Frustrum CameraFrustrum;

	virtual void PerspectiveCamera::RecalculateMatrix() {
		ProjectionMatrix = glm::perspective(glm::radians(CameraFrustrum.angle),
								1.0f, CameraFrustrum.near, CameraFrustrum.far);
		ViewMatrix = glm::lookAt(glm::vec3(0, 0, 5), UpVector, LookAt);
		auto Rotation = glm::rotate(glm::mat4(1.0f), glm::radians(this->Rotation), glm::vec3(1.0f, 0.0f, 0.0f));
		auto Translation = glm::translate(glm::mat4(1.0f), glm::vec3(Position));
		auto Scale = glm::scale(glm::mat4(1.0f), glm::vec3(8.0f, 8.0f, 8.0f));
		m_ModelMatrix = Translation * Rotation * Scale;
		MVPMatrix = ProjectionMatrix * ViewMatrix * m_ModelMatrix;
	}
};

#endif
*/