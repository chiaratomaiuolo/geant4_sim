#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH


#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4SDParticleFilter.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();
    
    //The function containing all detector characteristics has to be defined
    virtual G4VPhysicalVolume *Construct();

private: //the sensitive volume of the detector has to refer to the logical volume
         //so it has to be defined outside the construction void function.
         //For each sensitive geometry, a different logical volume has to be declared.


    G4LogicalVolume *logicFoil;
    G4LogicalVolume *logicControlFoil;
    G4LogicalVolume *logicCylinder;
    G4LogicalVolume *logicRing;
    G4LogicalVolume *logicArm;
    G4LogicalVolume *logicLowEndcap;
    G4LogicalVolume *logicUpEndcap;
    //Defining the function that constructs the sensitive detector
    virtual void ConstructSDandField();
    
};

#endif
