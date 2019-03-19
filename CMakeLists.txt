cmake_minimum_required(VERSION 3.13)
project(GenesisIO)

set(CMAKE_CXX_STANDARD
        11)
set(CMAKE_CXX_FLAGS
        "-O2 -mavx -pthread")
SET(CMAKE_C_FLAGS
        "-c -O2 -mavx")
set(MJ200_DIR
        ~/.mujoco/mujoco200)
set(MULTINEAT_DIR
        ~/MultiNEAT/MultiNEAT)
set(NANOGUI_DIR
        ~/nanogui)


##### ---------  MULTINeat(by Peter Chervenski) SOURCE FILES --------- ####
set(MULITNEAT_SOURCE_FILES
        ${MULTINEAT_DIR}/src/Assert.h
        ${MULTINEAT_DIR}/src/Genes.h
        ${MULTINEAT_DIR}/src/Genome.cpp
        ${MULTINEAT_DIR}/src/Genome.h
        ${MULTINEAT_DIR}/src/Innovation.cpp
        ${MULTINEAT_DIR}/src/Innovation.
        ${MULTINEAT_DIR}/src/NeuralNetwork.cpp
        ${MULTINEAT_DIR}/src/NeuralNetwork.h
        ${MULTINEAT_DIR}/src/Parameters.cpp
        ${MULTINEAT_DIR}/src/Parameters.h
        ${MULTINEAT_DIR}/src/PhenotypeBehavior.cpp
        ${MULTINEAT_DIR}/src/PhenotypeBehavior.h
        ${MULTINEAT_DIR}/src/Population.cpp
        ${MULTINEAT_DIR}/src/Population.h
        ${MULTINEAT_DIR}/src/Random.cpp
        ${MULTINEAT_DIR}/src/Random.h
        ${MULTINEAT_DIR}/src/Species.cpp
        ${MULTINEAT_DIR}/src/Species.h
        ${MULTINEAT_DIR}/src/Substrate.cpp
        ${MULTINEAT_DIR}/src/Substrate.h
        ${MULTINEAT_DIR}/src/Utils.cpp
        ${MULTINEAT_DIR}/src/Utils.h
        ${MULTINEAT_DIR}/src/Traits.h
        ${MULTINEAT_DIR}/src/Traits.cpp)

#### ----------------------------- MUJOCO --------------------------------------####
##Mujoco Header Path
find_path(MJ_HEADER_PATH
        NAMES mujoco.h
        PATHS ${MJ200_DIR}/include)

##Mujoco Library
set(CMAKE_PREFIX_PATH
        ${MJ200_DIR}/bin)
find_library(MJ200_LIB NAMES
        mujoco200)

##UI Tools
add_library(uitools STATIC ${MJ200_DIR}/include/uitools.c)
target_include_directories(uitools PUBLIC ${MJ200_DIR}/include)


#### ----------------------------- NANOGUI --------------------------------------####

##Nanogui Header Path
find_path(NANOGUI_HEADER_PATH
        NAMES nanogui.h
        PATHS ${NANOGUI_DIR}/include/nanogui)

##NanoGUI Extra Libraries
set(NANOGUI_EXTRA_LIBS "")
list(APPEND NANOGUI_EXTRA_LIBS GL GLU GLEW Xxf86vm Xrandr Xinerama Xcursor Xi X11 pthread dl)

##NanoGUI Extra Include Directories Path
set(NANOGUI_EXTRA_INCS "")
list(APPEND NANOGUI_EXTRA_INCS "${NANOGUI_DIR}/ext/glad/include")
list(APPEND NANOGUI_EXTRA_INCS "${NANOGUI_DIR}/ext/glfw/include")
list(APPEND NANOGUI_EXTRA_INCS "${NANOGUI_DIR}/ext/nanovg/src")
list(APPEND NANOGUI_EXTRA_INCS "${NANOGUI_DIR}/ext/eigen")


#############___Basic Simulation Example___#############

#executable simulator basic from mujoco200 sample
add_executable(basic
        src/basic.cpp
        ${MULTINEAT_SOURCE_FILES})

####include Mujoco header
target_include_directories(basic PUBLIC
        ${MJ_HEADER_PATH})

####link libraries
target_link_libraries(basic PUBLIC
        ${MJ200_LIB}
        -lX11
        -lGL
        -lm
        -lGLU
        -lGLEW
        ${MJ200_DIR}/bin/libglfw.so.3)

#############___Advanced Simulation Example___#############

add_executable(advanced
        src/simulate.cpp
        ${MULTINEAT_SOURCE_FILES} include/genio.hpp)

####include Mujoco header
target_include_directories(advanced PUBLIC
        ${MJ_HEADER_PATH})

####link libraries
target_link_libraries(advanced PUBLIC
        ${MJ200_LIB}
        -lX11
        -lGL
        -lm
        -lGLU
        -lGLEW
        ${MJ200_DIR}/bin/libglfw.so.3
        uitools)


#############___NANOGUI EXAMPLE___#############


add_executable(guisample
        src/example2.cpp)

target_include_directories(guisample PUBLIC
        ${NANOGUI_HEADER_PATH}      # Nanogui Header
        ${NANOGUI_EXTRA_INCS}       # Nanogui Extra Include Directories
        )

target_link_libraries(guisample PUBLIC
        nanogui
        ${NANOGUI_EXTRA_LIBS})


#############___GenesisIO___#############


##executable GenesisIO
add_executable(GenesisIO
        include/genio.hpp
        src/genio.cpp
        ${MULTINEAT_SOURCE_FILES}  )

##include headers
target_include_directories(GenesisIO PUBLIC
        include
        ${MJ_HEADER_PATH}           # Mujoco Header
        ${NANOGUI_HEADER_PATH}      # Nanogui Header
        ${NANOGUI_EXTRA_INCS}       # Nanogui Extra Include Directories
        )

##link libraries
target_link_libraries(GenesisIO PUBLIC
        ${MJ200_LIB}
        ${MJ200_DIR}/bin/libglfw.so.3
        uitools
        nanogui
        ${NANOGUI_EXTRA_LIBS})
