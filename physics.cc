#include "physics.hh"



MyPhysicsList::MyPhysicsList()
{
    //Here we have to insert the libraries that contains the physics processes.
    //Like for the materials, a custom physics list can be implemented but most 
    //processes are alread done in Geant4 libraries.
    //In this example, we want to construct a Cherenkov detector.
    RegisterPhysics (new G4EmStandardPhysics());
    RegisterPhysics (new G4OpticalPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
