/**
* Program for drawing a chessboard with cubes and a selector
* 
* The program can:
*   - Toggle textures for the chessboard and cubes on and off 
*   - Select the cubes by pressing space when the selector is udnerneath
*   - Move the selected cube by pressing arrowKeys
*   - Place the cube on a new empty square by pressing space when a cube is selected
*   - Move the camera around the chessboard
*   - Zoom in and out on origin
*/
#include "AssignmentApplication.h"

int main(int argc, char* argv[])
{
    Assignment application("Assignment", "1.0");

    application.ParseArguments(argc, argv);
    application.Init();

    return application.Run();
}