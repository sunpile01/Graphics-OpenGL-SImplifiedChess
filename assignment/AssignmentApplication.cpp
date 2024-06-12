/**
* @file AssignmentApplication.cpp
* 
* @brief main driver code for the application
* 
* @author Aleklsander Solhaug
*/

#include "AssignmentApplication.h"
#include <iostream>
#include <Camera.h>
#include <PerspectiveCamera.h>
#include <OrtographicCamera.h>
#include <Shader.h>
#include <RenderCommands.h>
#include <GeometricTools.h>
#include "Shader.cpp"
#include <TextureManager.h>
#include "KeyboardInput.cpp"

/**
* @brief Constructor that passes the name and version to GLFWApplication
* 
* @param name - Name of the application
* @param version - Current version of the application
* @see GLFWApplication::GLFWApplication(...)
*/
Assignment::Assignment(const std::string name, const std::string version) 
                                             :  GLFWApplication(name, version){}

/**
* @brief Destructor that closes the application
* @see  GLFWApplication::~GLFWApplication()
*/
Assignment::~Assignment() { GLFWApplication::~GLFWApplication(); }

/**
* @brief Parses the command line arguments so they are available in the code
* @see GLFWApplication::ParseArguments(...)
*/
unsigned int Assignment::ParseArguments(int argc, char** argv) {
    GLFWApplication::ParseArguments(argc, argv);
    return 0;
}

/**
* @brief Initializes the application
* @see GLFWApplication::Init()
*/
unsigned Assignment::Init() {
    GLFWApplication::Init();
    return 0;
}

/**
* @brief Creates everything that you can visibly see within the application
*/
unsigned Assignment::Run() const {
   
    glm::vec2 gridSize = { 8,8 };

    //Creating the geometry of the chessboard
    auto chessBoard = GeometricTools::UnitGridGeometry2DWTCoords(gridSize.x, gridSize.y);
    auto chessBoardTopology = GeometricTools::UnitGridTopologyTriangles(gridSize.x, gridSize.y);
    //Creating the geometry for the selector
    auto selector = GeometricTools::unitSquare2DTest();
    auto selectorTopology = GeometricTools::unitSquareTopologyTest();
    //Creating the geometry for the cube
    auto cube = GeometricTools::UnitCube3D;
    auto cubeTopology = GeometricTools::UnitCubeTopology;

    //Setting selector starting point to bottom left of chessboard
    //0 and 1 always starts in bottom left = (-0.5, -0.5), same y coordinate for 3
    selector[2] = -0.5f + (1.0f / gridSize.x);
    selector[4] = selector[2];  selector[5] = -0.5f + (1.0f / gridSize.y);
    selector[7] = selector[5];

    //Creating the buffers and the vertexArray to contain the geometry of the chessboard
    auto gridIndexBuffer = std::make_shared<IndexBuffer>(chessBoardTopology.data(),
        chessBoardTopology.size());
    auto gridBufferLayout = BufferLayout({ {ShaderDataType::Float2, "gridPosition"}, 
                                            {ShaderDataType::Float2, "gridTextureCords"} });
    auto gridVertexBuffer = std::make_shared<VertexBuffer>(chessBoard.data(),
                                            chessBoard.size() * sizeof(chessBoard[0]));
    gridVertexBuffer->SetLayout(gridBufferLayout);
    auto chessBoardvertexArray = std::make_shared<VertexArray>();
    chessBoardvertexArray->AddVertexBuffer(gridVertexBuffer, gridBufferLayout);
    chessBoardvertexArray->SetIndexBuffer(gridIndexBuffer);
    chessBoardvertexArray->Unbind();

    
    //Sizing down the cube geometry
    for (int i = 0; i < cube.size(); i++) {
        cube[i] /= 11;
    }

    //Creating the buffers and the vertexArray to contain the geometry of the cube
    auto cubeIndexBuffer = std::make_shared<IndexBuffer>(cubeTopology.data(),
        cubeTopology.size());
    auto cubeBufferLayout = BufferLayout({ {ShaderDataType::Float3, "cubePosition"} });
    auto cubeVertexBuffer = std::make_shared<VertexBuffer>(cube.data(),
        cube.size() * sizeof(cube[0]));
    cubeVertexBuffer->SetLayout(cubeBufferLayout);
    auto cubeVertexArray = std::make_shared<VertexArray>();
    cubeVertexArray->AddVertexBuffer(cubeVertexBuffer, cubeBufferLayout);
    cubeVertexArray->SetIndexBuffer(cubeIndexBuffer);
    cubeVertexArray->Unbind();
    

    //Creating the shaders
    auto chessBoardShader = std::make_shared<Shader>(chessBoardShaderSrc.c_str(), chessBoardFragmentShaderSrc.c_str());
    auto cubeShader = std::make_shared<Shader>(cubeVertexShaderSrc.c_str(), cubeFragmentShaderSrc.c_str());
    //Defining and uploading the colors that wont change during runtime to the shaders
    glm::vec4 squareColorA = { 1.0f, 1.0f,1.0f, 1.0f };
    glm::vec4 squareColorB = { 0.0f, 0.0f, 0.0f, 1.0f };
    glm::vec4 squareColorC = { 0.0f, 0.7f, 0.0f, 1.0f };
    glm::vec2 chessBoardSquareSize = { gridSize.x, gridSize.y };
    chessBoardShader->setUniformFloat2("u_gridSize", chessBoardSquareSize);
    chessBoardShader->SetUniform4fVector("u_ColorA", squareColorA);
    chessBoardShader->SetUniform4fVector("u_ColorB", squareColorB);
    chessBoardShader->SetUniform4fVector("u_ColorC", squareColorC);

    //Creating the texure instance and loading the cube and chessboard texture
    TextureManager* textures = TextureManager::GetInstance();
    textures->LoadTexture2DRGBA("chessBoardTexture",
                        std::string(TEXTURE_DIR) + std::string("floor_texture.png"), 0);
    textures->LoadCubeMapRGBA("cubeTexture",
                      std::string(TEXTURE_DIR) + std::string("cube_texture.png"), 1);


    //Creating the perspective camera for the scene
    PerspectiveCamera* camera2 = new PerspectiveCamera(GLFWApplication::m_width, GLFWApplication::m_height);
    glm::mat4 projMatrix = camera2->GetProjectionMatrix();
    glm::mat4 viewMatrix = camera2->GetViewMatrix();
    //Uploading the matrices created by the perspectiveCamera constructor to the shaders
    chessBoardShader->SetUniformMatrix4fv("u_projMatrix", projMatrix);
    chessBoardShader->SetUniformMatrix4fv("u_viewMatrix", viewMatrix);
    cubeShader->SetUniformMatrix4fv("u_projMatrix", projMatrix);
    cubeShader->SetUniformMatrix4fv("u_viewMatrix", viewMatrix);

    //Creating the modelMatrix for the Chessboard
    auto chessBoardModelMatrix = glm::mat4(1.0f);
    auto chessboardRotation = glm::rotate(chessBoardModelMatrix, glm::radians(-89.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    auto chessboardTranslation = glm::translate(chessBoardModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    auto chessboardScale = glm::scale(chessBoardModelMatrix, glm::vec3(4.0f, 4.0f, 4.0f));
    chessBoardModelMatrix = chessboardScale * chessboardRotation * chessboardTranslation;
    chessBoardShader->SetUniformMatrix4fv("u_modelMatrix", chessBoardModelMatrix);


    glm::mat4 modelCube[32];
    for (int i = 0; i < 32; i++)
        modelCube[i] = glm::mat4(1.0f);
    //Setting the initial rotation and scale of the cubes
    auto cubeRotation = glm::rotate(modelCube[0], glm::radians(-89.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    auto cubeScale = glm::scale(modelCube[0], glm::vec3(4.0f, 4.0f, 4.0f));

    //Initializing for each cube to the identity matrix
    glm::mat4 cubeTranslation[32];
    for (int i = 0; i < 32; i++) {
        cubeTranslation[i] = glm::mat4(1.0f);
    }

    //Initializing the cornervectors for the first chessboard square
    glm::vec3 cornerVector1 = { -0.5f, -0.5f, -0.5f };
    glm::vec3 cornerVector2 = { -0.5f, -0.5f, -0.5f };
    glm::vec3 cornerVector3 = { -0.5f, -0.375f, -0.375f };
    glm::vec3 cornerVector4 = { -0.5f, -0.375f, -0.375f };
    glm::vec3 middleOfSquare = { 0.0f, 0.0f, 0.0f };
    std::vector <glm::vec3> translationVectors;
    translationVectors.resize(32);

    float dSquare = 1.0f / 8;                  //distance between each square

    //Setting all the translation matrices for the cubes
    for (int i = 0; i < 32; i++) {

        //Moving the corner vectors x coordinate dSquare distance along the row
        //for each iteration of the loop
        if (i == 0 || i == 8 || i == 16 || i == 24) {
            cornerVector2.x += dSquare;
            cornerVector3.x += dSquare;
        }
        else {
            cornerVector1.x += dSquare;
            cornerVector2.x += dSquare;
            cornerVector3.x += dSquare;
            cornerVector4.x += dSquare;
        }

        //Finding the distance to the middle of the square
        middleOfSquare = (cornerVector1 + cornerVector2 + cornerVector3 + cornerVector4);
        middleOfSquare.x /= 4;
        middleOfSquare.y /= 4;
        middleOfSquare.z /= 4;

        //Setting the translation vector to the middle of the square
        cubeTranslation[i] = glm::translate(glm::mat4(1.0f), glm::vec3(middleOfSquare.x, middleOfSquare.y, 0.07f));
        translationVectors[i] = glm::vec3(middleOfSquare);
        //Resetting the corners to the start positions of the next row
        if (i == 7) {
            cornerVector1 = { -0.5f, -0.375f, -0.375f };
            cornerVector2 = { -0.5f, -0.375f, -0.375f };
            cornerVector3 = { -0.5f, -0.25f,  -0.25f };
            cornerVector4 = { -0.5f, -0.25f,  -0.25f };
        }
        if (i == 15) {                                  //Same as above
            cornerVector1 = { -0.5f, 0.25f,  0.25f };
            cornerVector2 = { -0.5f, 0.25f,  0.25f };
            cornerVector3 = { -0.5f, 0.375f, 0.375f };
            cornerVector4 = { -0.5f, 0.375f, 0.375f };
        }
        if (i == 23) {                                  //Same as above
            cornerVector1 = { -0.5f, 0.375f, 0.375f };
            cornerVector2 = { -0.5f, 0.375f, 0.375f };
            cornerVector3 = { -0.5f, 0.5f,  0.5f };
            cornerVector4 = { -0.5f, 0.5f,  0.5f };
        }
    }
    //Initilaizing the modelmatrix for all the cubes
    for (int i = 0; i < 32; i++) {
        modelCube[i] = cubeScale * cubeRotation * cubeTranslation[i];
    }
    
    glm::vec4 red = { 1.0f, 0.0f, 0.0f, 1.0f };
    glm::vec4 blue = { 0.0f, 0.0f, 1.0f, 1.0f };
    glm::vec4 gray = { 161.0f/255.0f, 161.0f / 255.0f, 161.0f / 255.0f, 1.0f };
    glm::vec4 colorSelected = { 1.0f, 1.0f, 0.0f, 1.0f };
    glm::vec2 selectorCenter = { 0, 0 };
    glm::vec2 selectorCenter2 = { 0,0 };
    glm::vec2 cubePos = { 0 ,0 };

    
    //Initializng variables related to key input
    float deltaYpress = 0;
    float deltaXpress = 0;
    bool pressed = false;
    int setTextures = 0;
    int wPress, aPress, sPress, dPress = 0;
    bool spacePressed = false;
    bool recalculateModelMatrix = false;
    bool noCubeSwapp = false;
    int selectedCube = 0;
    int cubeToTransalte = 0;
    int lockL, lockH, lockP, lockO = 0;
    float dt = 0.0f;
    float currentTime = 0.0f;
    float lastTime = 0.0f;
    
    RenderCommands::SetSolidMode();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    // the function used here is s*apha + d(1-alpha)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(GLFWApplication::m_window))
    {

        currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;
        glfwPollEvents();
        RenderCommands::SetClearColor(gray);
        RenderCommands::Clear();
        glm::mat4 viewMatrix = camera2->GetViewMatrix();

        cameraInput(GLFWApplication::m_window, camera2, dt, lockL, lockH, lockP, lockO);

        //Setting the position for the selector 
        if (selector[0] == -0.5f && selector[1] == -0.5f)
            selectorCenter = { selector[0], selector[1] };
        else if (selector[0] != -0.5f && selector[1] == -0.5f)
            selectorCenter = { selector[0] + deltaXpress, selector[1] };
        else if (selector[0] == -0.5f && selector[1] != -0.5f)
            selectorCenter = { selector[0], selector[1] + deltaYpress };
        else selectorCenter = { selector[0] + deltaXpress,  selector[1] + deltaYpress };
        selectorCenter2 = { selector[0], selector[1] };

        processInput(GLFWApplication::m_window, selector, pressed, wPress, aPress, sPress, dPress, spacePressed,
                      deltaXpress, deltaYpress, gridSize, setTextures, translationVectors, selectedCube, cubeToTransalte,
                                                                                    recalculateModelMatrix, noCubeSwapp);

        chessBoardShader->Bind();
        chessBoardShader->setUniformFloat2("u_selectorPosition", selectorCenter);
        chessBoardShader->SetUniformMatrix4fv("u_viewMatrix", viewMatrix);
        chessBoardShader->setInt("u_SetTextures", setTextures);
        chessBoardvertexArray->Bind();
        RenderCommands::DrawIndex(chessBoardvertexArray, GL_TRIANGLES);


        cubeShader->Bind();
        cubeShader->SetUniformMatrix4fv("u_viewMatrix", viewMatrix);
        cubeShader->setInt("u_SetTextures", setTextures);
        cubeVertexArray->Bind();

        //If cube is moved
        if (recalculateModelMatrix == true) {
            //Update the model matrix with the new translation matrix for the selected cube
            cubeTranslation[cubeToTransalte - 1] = glm::translate(glm::mat4(1.0f),
                                                   glm::vec3(translationVectors[cubeToTransalte - 1].x,
                                                   translationVectors[cubeToTransalte - 1].y, 0.07f));

            modelCube[cubeToTransalte - 1] = cubeScale * cubeRotation * cubeTranslation[cubeToTransalte - 1];
            recalculateModelMatrix = false;
            cubeToTransalte = 0;
        }

        for (int i = 0; i < 32; i++) {
            //Setting variable to the center of the square the cube will be drawn in
            cubePos.x = translationVectors[i].x;
            cubePos.y = translationVectors[i].y;
            cubeShader->SetUniformMatrix4fv("u_modelMatrix", modelCube[i]);

            if (i < 16)                             //Half of the cubes blue other red
                cubeShader->SetUniform4fVector("u_Color", blue);
            else cubeShader->SetUniform4fVector("u_Color", red);

            //Cube becomes green when selector is on the same square
            if (selectorCenter2.x <= cubePos.x &&
                selectorCenter2.x + (1 / gridSize.x) >= cubePos.x &&
                selectorCenter2.y <= cubePos.y &&
                selectorCenter2.y + (1 / gridSize.y) >= cubePos.y) {
                cubeShader->SetUniform4fVector("u_Color", squareColorC);
            }

            //Cubes becomes a different color when space is pressed on top of it
            if (selectorCenter2.x <= cubePos.x &&
                selectorCenter2.x + (1 / gridSize.x) >= cubePos.x &&
                selectorCenter2.y <= cubePos.y &&
                selectorCenter2.y + (1 / gridSize.y) >= cubePos.y &&
                spacePressed == true && noCubeSwapp == false) {
                cubeShader->SetUniform4fVector("u_Color", colorSelected);
                selectedCube = i + 1;
                noCubeSwapp = true;
            }
            //Cube is still selected color, even when selector is not under it
            if (spacePressed == true && selectedCube != 0 && selectedCube - 1 == i)
                cubeShader->SetUniform4fVector("u_Color", colorSelected);
            
            RenderCommands::DrawIndex(cubeVertexArray, GL_TRIANGLES);
        }

        glfwSwapBuffers(GLFWApplication::m_window);

        // Exit the loop if escape is pressed
        if (glfwGetKey(GLFWApplication::m_window, GLFW_KEY_Q) == GLFW_PRESS) break;
    }

    return EXIT_SUCCESS;
}



