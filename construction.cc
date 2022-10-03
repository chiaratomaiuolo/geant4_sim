#include "construction.hh"
#include "detector.hh"
#include <vector>
/*
In this file, the detector is constructed, composed by many volume pieces:
1. a world box, containing all the pieces;
2. the source, a Cu foil where protons from CW hit;
3. The support pieces, composed by:
    - a Cu ring, where the source is stuck on;
    - a Cu arm, from the ring to the cylindrical external support
4. A cylindrical external support, composed by: 
    - Carbon fiber lateral surface;
    - Al endcaps.
*/

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    //Defining material of the detector (most of materials are already implemented)
    //inside Geant4, in G4Nist library. 
    
    //An instance of Nist is defined for selecting the material. 
    G4NistManager *nist = G4NistManager::Instance();

    //Constructing the mother box
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic"); 
    G4Box *solidWorld = new G4Box("solid world", 30.*cm, 30.*cm, 30.*cm); 
    //logical features: material
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    //pysical features: rotations
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false, 0, true);

    //steps:
    //1) defining material

    //Carbon fiber material
    G4Material *Cu = nist->FindOrBuildMaterial("G4_Cu");
    G4Element *C = nist->FindOrBuildElement("C");
    G4Material *Al = nist->FindOrBuildMaterial("G4_Al");
    G4Material *Carbon_fiber = new G4Material("Carbon_fiber", 1.6*g/cm3,1); 
    Carbon_fiber->AddElement(C, 100*perCent);
    //2) defining properties of the material
    G4VisAttributes *cRed = new G4VisAttributes(G4Colour(1.,0.,0.));
    G4VisAttributes *cBlue = new G4VisAttributes(G4Colour(0.,0.,1.));
    G4VisAttributes *cGreen = new G4VisAttributes(G4Colour(0.,1.,0.));
    cRed->SetForceWireframe(true);
    cBlue->SetForceWireframe(true);
    cGreen->SetForceWireframe(true);



    //3) defining the volume geometry
    //Source foil
    G4Tubs *SourceFoil = new G4Tubs("Source foil", 0.*mm,26*mm,12.5*um,0,CLHEP::twopi);
    //Control foil (for upstream/downstream discrimination)
    G4Tubs *ControlFoil = new G4Tubs("Control foil", 0.*mm,26*mm,0.5*mm,0,CLHEP::twopi);
    //Support ring
    G4Tubs *SupportRing = new G4Tubs("Support ring",25.*mm,31.*mm,3.*mm,0,CLHEP::twopi);
    //Copper arm
    G4Tubs *CopperArm = new G4Tubs("Copper arm",0.*mm,3.*mm,136.9875*mm,0,CLHEP::twopi);
    //Upper cylinder endcap
    G4Tubs *UpEndcap = new G4Tubs("Upper endcap",0.*mm,49.0*mm,1*mm,0,CLHEP::twopi);
    //Lower cylinder endcap
    G4Tubs *LowEndcap = new G4Tubs("Lower endcap",0.*mm,49.0*mm,1*mm,0,CLHEP::twopi);
    //Cylindrical walls
    G4Tubs *CylindricalWalls = new G4Tubs("Cylindrical walls",48.9*mm,49.0*mm,150*mm,0,CLHEP::twopi);
    //Vacuum sensitive detector on upper foil face
    
    
    //4) defining the material of the volume
    //Source foil
    logicFoil = new G4LogicalVolume(SourceFoil,Cu,"logicFoil");
    logicFoil->SetVisAttributes(cBlue);
    //Control foil (for upstream/downstream discrimination) it is made by vacuum, it is needed only for tagging
    logicControlFoil = new G4LogicalVolume(ControlFoil,worldMat,"logicFoil");
    //Support ring 
    logicRing = new G4LogicalVolume(SupportRing,Cu,"logicRing");
    logicRing->SetVisAttributes(cRed);
    //Copper arm
    logicArm = new G4LogicalVolume(CopperArm,Cu,"logicArm");
    logicArm->SetVisAttributes(cRed);
    //Upper cylinder endcap
    logicUpEndcap = new G4LogicalVolume(UpEndcap,Al,"logicUpEndcap");
    //Lower cylinder endcap
    logicLowEndcap = new G4LogicalVolume(LowEndcap,Al,"logicLowEndcap");
    //Cylindrical walls
    logicCylinder = new G4LogicalVolume(CylindricalWalls,Carbon_fiber,"logicCylinder");


    //5) defining the physical features
    //Source foil
    G4VPhysicalVolume *physFoil = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicFoil,"physFoil",logicWorld,false,0,true);
    //Control foil (for upstream/downstream discrimination)
    G4VPhysicalVolume *physControlFoil = new G4PVPlacement(0,G4ThreeVector(0.,0.,-0.5125*mm),logicControlFoil,"physControlFoil",logicWorld,false,0,true);
    //Support ring
    G4VPhysicalVolume *physRing = new G4PVPlacement(0,G4ThreeVector(0.,0.,3.0125*mm),logicRing,"physRing",logicWorld,false,0,true);
    //Copper arm
    G4VPhysicalVolume *physArm = new G4PVPlacement(0,G4ThreeVector(28*mm,0.,143.*mm),logicArm,"physArm",logicWorld,false,0,true);
    //Upper cylinder endcap
    G4VPhysicalVolume *physUpEndcap = new G4PVPlacement(0,G4ThreeVector(0.,0.,280.9875*mm),logicUpEndcap,"physUpEndcap",logicWorld,false,0,true);
    //Lower cylinder endcap
    G4VPhysicalVolume *physLowEndcap = new G4PVPlacement(0,G4ThreeVector(0.,0.,-21.0125*mm),logicLowEndcap,"physLowEndcap",logicWorld,false,0,true);
    //Cylindrical walls
    G4VPhysicalVolume *physCylinder = new G4PVPlacement(0,G4ThreeVector(0.,0.,129.9875),logicCylinder,"physCylinder",logicWorld,false,0,true);
    
    //Always return the 'mother' volume, because contains all the other volumes
    return physWorld; 

}

void MyDetectorConstruction::ConstructSDandField()
{

    //Foil disc detector
    MySensitiveDetector *sensDetFoil = new MySensitiveDetector("FoilSensitiveDetector");
    logicFoil->SetSensitiveDetector(sensDetFoil);
    //Control foil sensitive detector
    MySensitiveDetector *sensDetControlFoil = new MySensitiveDetector("ControlFoilSensitiveDetector");
    logicControlFoil->SetSensitiveDetector(sensDetControlFoil);
    //Cylindrical walls detector
    MySensitiveDetector *sensDetWalls = new MySensitiveDetector("WallsSensitiveDetector");
    logicCylinder->SetSensitiveDetector(sensDetWalls);
    //Ring detector 
    MySensitiveDetector *sensDetRing = new MySensitiveDetector("RingSensitiveDetector");
    logicRing->SetSensitiveDetector(sensDetRing);
    //Arm detector
    MySensitiveDetector *sensDetArm = new MySensitiveDetector("ArmSensitiveDetector");
    logicArm->SetSensitiveDetector(sensDetArm);
    //Low endcap detector
    MySensitiveDetector *sensDetLowEnd = new MySensitiveDetector("LowEndSensitiveDetector");
    logicLowEndcap->SetSensitiveDetector(sensDetLowEnd);
    //Up endcap detector
    MySensitiveDetector *sensDetUpEnd = new MySensitiveDetector("UpEndSensitiveDetector");
    logicUpEndcap->SetSensitiveDetector(sensDetUpEnd);

}








