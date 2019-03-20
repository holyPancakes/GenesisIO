cmake_minimum_required(VERSION 3.10)
project(GenesisIO)

set(CMAKE_CXX_STANDARD
        11)
set(CMAKE_CXX_FLAGS
        "-O2 -mavx -pthread")
SET(CMAKE_C_FLAGS
        "-c -O2 -mavx")
set(MJ200_DIR
        Libraries/Mujoco200)
set(MULTINEAT_DIR
        Libraries/MultiNEAT)


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


#############___Basic Simulation Example___#############

#executable simulator basic from mujoco200 sample
add_executable(basic
        Sources/basic.cpp
        ${MULTINEAT_SOURCE_FILES})

####include Mujoco header
target_include_directories(basic PUBLIC
        ${MJ_HEADER_PATH})

####link libraries
target_link_libraries(basic PUBLIC
        ${MJ200_LIB}
        X11
        GL
        m
        GLU
        GLEW
        libglfw.so.3)

#############___Advanced Simulation Example___#############

add_executable(advanced
        Sources/simulate.cpp
        ${MULTINEAT_SOURCE_FILES})

####include Mujoco header
target_include_directories(advanced PUBLIC
        ${MJ_HEADER_PATH})

####link libraries
target_link_libraries(advanced PUBLIC
        ${MJ200_LIB}
        X11
        GL
        m
        GLU
        GLEW
        libglfw.so.3
        uitools)


#############___GenesisIO___#############


##executable GenesisIO
add_executable(GenesisIO
        Sources/genio.cpp
        Headers/genio.hpp
        ${MULTINEAT_SOURCE_FILES}  )

##headers directories
target_include_directories(GenesisIO PUBLIC
        Headers
        ${MJ_HEADER_PATH}           # Mujoco Header
        )


##link libraries
target_link_libraries(GenesisIO PUBLIC
        ${MJ200_LIB}
        libglfw.so.3
        X11
        GL
        m
        GLU
        GLEW
        uitools)
