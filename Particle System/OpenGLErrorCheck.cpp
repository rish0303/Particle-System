/*!
 * @author		Rishabh Anand
 * @copyright	© 2022 Digipen (USA) Corporation.
 * @date		mm.dd.2022
 * @brief		OPTIONAL
*/

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include<GLFW/glfw3.h>
#include "OpenGLErrorCheck.hpp"

void CheckError()
{
    // Get the current error value
    GLenum error = glGetError();
    // Check if there is an error
    if (error != GL_NO_ERROR)
    {
        // Print the error value to the console
        std::cout << "Error: " << static_cast<unsigned>(error) << std::endl;
        // Use assert to stop the program so we can see what is happening
        assert(false);
    }
}