#include "physics.hh"



MyPhysicsList::MyPhysicsList()
{
    //Here we have to insert the libraries that contains the physics processes.
    //Like for the materials, a custom physics list can be implemented but most 
    //processes are alread done in Geant4 libraries.
    RegisterPhysics (new G4EmStandardPhysics_option4());
    RegisterPhysics (new G4OpticalPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
