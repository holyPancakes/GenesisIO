/*
 * Author: Maru Gabriel S. Baul
 * Description: GenesisIO - Robot Control Platform using Online Reinforcement Learning of Evolved Neural Networks
 *
 */

#include "genio.hpp"

//mujoco headers
#include "mujoco.h"
#include "mjxmacro.h"

#include "stdio.h"
#include "string.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>



// main function
int main(int argc, const char** argv){

    //Initialize UI
    try {
        /*Main Window Loop*/{
            
        }

        //Shutdown UI
    }
    //catch Runtime Error
    catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        #if defined(_WIN32)
            MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
        #else
            std::cerr << error_msg << std::endl;
        #endif
        return -1;
    }   
    return 0;
}
