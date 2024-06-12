/**
* @file KeyboardInput.cpp
* 
* @brief Processes all the input from the keyboard 
* 
* @author Aleksander Solhaug
*/

#include <vector>

/**
* @brief Checks if the square the cube will move to is available
* 
* @param translationVectors - The current location of all the cubes
* @param cubeToTranslate - The cube that will be moved
* @param wPress, aPress, sPress, dPress - Movement in each direction
* 
* @return bool - Wether the square was available or not
*/
bool squareAvailable(std::vector<glm::vec3>& translationVectors, int& cubeToTranslate,
	int& wPress, int& aPress, int& sPress, int& dPress) {
	
	for (int i = 0; i < 32; i++) {
		//Checking if the desired location is available or not and making sure it
		//Is not checking against itself
		if (translationVectors[cubeToTranslate - 1].x == translationVectors[i].x &&
			translationVectors[cubeToTranslate - 1].y == translationVectors[i].y
			&& i != cubeToTranslate - 1) {				
			//If already occupied, move the selected cube back to its original position
			if (wPress > 0)
				translationVectors[cubeToTranslate - 1].y -= 1.0f / 8.0f * wPress;
			if (aPress > 0)
				translationVectors[cubeToTranslate - 1].x += 1.0f / 8.0f * aPress;
			if (sPress > 0)
				translationVectors[cubeToTranslate - 1].y += 1.0f / 8.0f * sPress;
			if (dPress > 0)
				translationVectors[cubeToTranslate - 1].x -= 1.0f / 8.0f * dPress;
			return false;
		}
	}
	return true;
}


/**
* @brief Process the keyboard input 
* 
* @param window - the window for the application
* @param selector - The tile selector on the chessboard 
* @param keyPressed - whether a key has been pressed or not
* @param wPress, aPress, sPress, dPress - How many time respective keys have been pressed
* @param deltaXpress - Distance the selector has moved on the X axis (columns)
* @param deltaYpress - Distance the selector has moved on the Y axis (rows)
* @param gridSize - The size of the grid
* @param setTextures - Toggling textures on and off
* @param translationVectors - Vectors from origin to where the cubes are on the chessboard
* @param selectedCube - Number in the translationVectors array for the selected cube
* @param recalculateModelMatrix - if a cube has been moved, its model matrix needs to be recalculated
* @param noCubeSwap - If an empty square was selected, or cube did not move 
*/
static void processInput(GLFWwindow* window, std::vector <float> & selector, bool& keyPressed, int& wPress,
				int& aPress, int& sPress, int& dPress, bool& spacePressed, float& deltaXPress, float& deltaYPress,
				const glm::vec2 & gridSize, int& setTextures, std::vector<glm::vec3>& translationVectors,
				int& selectedCube, int& cubeToTranslate, bool& recalculateModelMatrixCube, bool& noCubeSwapp)
{
	
	//move selector up
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		float stepSize = (float)1/gridSize.y;	//Distance to move the selector.
		if (selector[5] < 0.5f) {				//So selector stays within the chessboard.
			deltaYPress += 0.875f;
			if (spacePressed == true)
				wPress++;
			//Changing the odd vertices to move the selector vertically
			for (int i = 0; i < selector.size(); i += 2) {
				selector[i + 1] += stepSize;
			}
		}
	}

	//Move selector down
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		float stepSize = (float)1/gridSize.y;
		if (selector[1] > -0.5f) {
			deltaYPress -= 0.875;
			if (spacePressed == true)
				sPress++;
			for (int i = 0; i < selector.size(); i += 2) {
				selector[i + 1] -= stepSize;
			}
		}
	}

	//move selector left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		float stepSize = (float)1/gridSize.x;
		if (selector[0] > -0.5f) {
			deltaXPress -= 0.875;
			if (spacePressed == true)
				aPress++;
			//Changing the even vertices to move the selector horisontaly
			for (int i = 0; i < selector.size(); i += 2) {
				selector[i] -= stepSize;
			}
		}
	}

	//move selector right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		float stepSize = (float) 1/gridSize.x;
		if (selector[2] < 0.5f) {
			//Changing the even vertices to move the selector horisontaly
			deltaXPress += 0.875;
			if (spacePressed == true)
				dPress++;
			for (int i = 0; i < selector.size(); i += 2) {
				selector[i] += stepSize;
			}
		}
	}

	//Selecting a cube, and moving if it is already selected
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		if (spacePressed == false) {
			spacePressed = true;
		}
		else {
			spacePressed = false;
			selectedCube = 0;
			noCubeSwapp = false;
		}
		if (spacePressed == true) {							//Cube is selected
			wPress = 0; aPress = 0; sPress = 0; dPress = 0;
			for (int i = 0; i < 32; i++) {					//Checking which cube was selected
				//Checking if a cube is within the same square as the selector
				if (
					selector[0] + (1.0f / (8.0f * 2)) <= translationVectors[i].x &&  
					selector[0] + 1 / 8.0f - (1.0f / (8.0f * 2)) >= translationVectors[i].x &&  
					selector[1] + (1.0f / (8.0f * 2)) <= translationVectors[i].y &&
					selector[1] + 1 / 8.0f - (1.0f / (8.0f * 2)) >= translationVectors[i].y) {
					cubeToTranslate = i + 1;
				}
			}
			if (cubeToTranslate == 0)			//No cube located within the selected square
				spacePressed = false;
		}
		else {
			//A cube is selected and about to be placed in a new square
			//Moves the translationvector to the new square
			if (cubeToTranslate != 0) {			
				if (wPress > 0) {
					translationVectors[cubeToTranslate - 1].y += 1.0f / gridSize.y * wPress;
				}
				if (aPress > 0) {
					translationVectors[cubeToTranslate - 1].x -= 1.0f / gridSize.x * aPress;
				}
				if (sPress > 0) {
					translationVectors[cubeToTranslate - 1].y -= 1.0f / gridSize.y * sPress;
				}
				if (dPress > 0) {
					translationVectors[cubeToTranslate - 1].x += 1.0f / gridSize.x * dPress;
				}
				//Checks if the square to move to is available
				if (!squareAvailable(translationVectors, cubeToTranslate, wPress, aPress, sPress, dPress)) {
					recalculateModelMatrixCube = false;
					cubeToTranslate = 0;
				}
				else recalculateModelMatrixCube = true;
				wPress = 0; aPress = 0; sPress = 0; dPress = 0;		//Resets the movement variables
			}
		}
	}

	//Toggles the setTextures variable that will be sent to the shaders 
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		if (setTextures == 0)
			setTextures = 1;
		else setTextures = 0;
	}
	
	//Check if no key is being pressed, if so, set pressed to false
	//Ensures that only one keyInput is processed per key press
	if (glfwGetKey(window, GLFW_KEY_UP)    == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_DOWN)  == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE && 
		glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_T)     == GLFW_RELEASE &&
		keyPressed == true)
		keyPressed = false;
}

/**
* @brief Processes the input related to the camera
* 
* @param window - The window for the application
* @param camera - Camera to perform operations on
* @param dt - delta time, time between each frame
* @param lockL, lockH, lockP, lockO - So only one button can be pressed at a time
*/
static void cameraInput(GLFWwindow* window, PerspectiveCamera* camera, float& dt, int& lockL, 
													int& lockH, int& lockP, int& lockO) {

	float rotation = dt * 500.0f;
	glm::vec3 oldCamPos = { 0.0f, 0.0f, 0.0f };
	glm::vec4 tmpPos = { 0.0f, 0.0f, 0.0f, 1.0f };
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && lockH == 0 && lockP == 0 && lockO == 0 ) {
		//Translating the tmpPos to the original camera position
		tmpPos = glm::translate(glm::mat4(1.0f), glm::vec3(camera->GetPosition().x, camera->GetPosition().y,
			camera->GetPosition().z)) * tmpPos;
		//Rotating the camera around the y axis so the distance to center remains the same
		tmpPos = glm::rotate(glm::mat4(1.0f), glm::radians(rotation / 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * tmpPos;
		//Setting the new camera position
		camera->SetPosition({ tmpPos.x, tmpPos.y, tmpPos.z });
		lockL = 1;
	}
	else lockL = 0;


	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && lockL == 0 && lockP == 0 && lockO == 0) {
		//Same as the H key, but adding a '-' to rotate clockwise
		tmpPos = glm::translate(glm::mat4(1.0f), glm::vec3(camera->GetPosition().x, camera->GetPosition().y,
			camera->GetPosition().z)) * tmpPos;
		tmpPos = glm::rotate(glm::mat4(1.0f), -glm::radians(rotation / 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * tmpPos;
		camera->SetPosition({ tmpPos.x, tmpPos.y, tmpPos.z });
		lockH = 1;
	}
	else lockH = 0;

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && lockH == 0 && lockP == 0 && lockL == 0) {
		//Getting the position of the camera
		if (camera->GetPosition().y < 10.0f) {
			tmpPos = glm::translate(glm::mat4(1.0f), glm::vec3(camera->GetPosition().x, camera->GetPosition().y,
				camera->GetPosition().z)) * tmpPos;
			//Scaling the scene from the camera perspective
			tmpPos = glm::scale(glm::mat4(1.0f), glm::vec3(1.005f, 1.005f, 1.005f)) * tmpPos;
			//Setting the new position
			camera->SetPosition({ tmpPos.x, tmpPos.y, tmpPos.z });
			lockO = 1;
		}
	}
	else lockO = 0;

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && lockH == 0 && lockL == 0 && lockO == 0) {
		if ( camera->GetPosition().y > 1.1f) {
			//Same as above just making the scene smaller from the cameras perspective
			tmpPos = glm::translate(glm::mat4(1.0f), glm::vec3(camera->GetPosition().x, camera->GetPosition().y,
				camera->GetPosition().z)) * tmpPos;
			tmpPos = glm::scale(glm::mat4(1.0f), glm::vec3(0.995f, 0.995f, 0.995f)) * tmpPos;
			camera->SetPosition({ tmpPos.x, tmpPos.y, tmpPos.z });
			lockP = 1;
		}
	}
	else lockP = 0;
}
