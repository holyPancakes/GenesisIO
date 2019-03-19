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

#include <nanogui/nanogui.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::to_string;

class MainApplication : public nanogui::Screen{
public:
    MainApplication() : Screen(Vector2i(screen_width,screen_height), "GenesisIO - Robot Reinforcement Learning"){

        using namespace nanogui;

        /* WITH FORM HELPER
        
        FormHelper* h = new FormHelper(this);

        Window *window = h->addWindow(Vector2i(20, 20), "Experiment");
        h->setFixedSize(Vector2i(200,560));
        h->addGroup("Experiments");
        h->addButton("Add New Experiment",[this](){
            FormHelper* h = new FormHelper(this);
            Window *exp_name_window = h->addWindow(Vector2i(20 ,20 ), "New Expermiment Name");
            std::string exp_name = "<genioExpName>";
            h->addVariable("Experiment Name:",exp_name);
            h->addButton("Cancel", [&]{cout<<"CANCEL"<<endl;});
            h->addButton("OK", [&]{cout<<"OK"<<endl;});
            exp_name_window->center();
            performLayout();
        });
        
        */
        
        
        //*WITHOUT FORM HELPER
        Window *window = new Window(this, "Experiment");
        window->setPosition(Vector2i(20,20));
        window->setFixedSize(Vector2i(200,560));
        window->setLayout(new GroupLayout());
        Button *b = new Button(window, "New Experiment");
        //addExperiementBtn->setIcon(ENTYPO_ICON_ADD_TO_LIST);
        /*addExperiementBtn->setCallback([this]{
            Window *window = new Window(this, "New Experiment");
            window->setFixedSize(Vector2i(300,125));
            window->setModal(true);
            window->requestFocus();
            window->setLayout(new GroupLayout());
            new Label(window, "New Experiment Name:");
            performLayout();
            window->center();
        });
        */
        //*/
        
        performLayout();
        //set Window Position to Center
        GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primary_monitor);
        GLFWwindow *main_gl_window = this->glfwWindow();
        if( mode->width > screen_width ) {
            glfwSetWindowPos(main_gl_window, (mode->width - screen_width) / 2, (mode->height - screen_height) / 2);
        }
    }

private:

};

// main function
int main(int argc, const char** argv){

    //initialize nanogui

    nanogui::init();
    try {
        /* scoped variables */{
            nanogui::ref<MainApplication> app = new MainApplication();
            app->drawAll();
            app->setVisible(true);
            nanogui::mainloop();
        }
        nanogui::shutdown();
    }
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
