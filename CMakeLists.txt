#The cmake file creates the executable files needed for creating the simulation

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Simulation)

#packages to be included, Geant4 is mandatory, ui_all is for user interface and 
# vi_all is for creating a visual interface (if needed).
find_package(Geant4 REQUIRED ui_all vis_all)

#including the packages inside the written path
include(${Geant4_USE_FILE})

#For putting several classes and files inside the project
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

file(GLOB MACRO_FILES
    "*.mac"
)

set(CMAKE_CXX_FLAGS "-stdlib=libc++ -pthread -std=c++17 -m64 -I/opt/homebrew/Cellar/root/6.26.06_1/include/root -L/opt/homebrew/Cellar/root/6.26.06_1/lib/root -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -Wl,-rpath,/opt/homebrew/Cellar/root/6.26.06_1/lib/root -stdlib=libc++ -lpthread -lm -ldl")


#copying all the macro files inside the build directory (in this way 
#in build folder the .mac files are found in make)
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# for creating the executables
add_executable(geant4_sim geant4_sim.cc ${sources} ${headers})
target_link_libraries(geant4_sim ${Geant4_LIBRARIES})

add_custom_target(Simulation DEPENDS geant4_sim)