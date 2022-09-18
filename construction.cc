#include "construction.hh"
//#include ""
//#include "detector.hh"
#include <vector>
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
    G4Box *solidWorld = new G4Box("solid world", 20.*cm, 20.*cm, 20.*cm); 
    //logical features: material
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    //pysical features: rotations
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld, "physWorld",0,false, 0, true);

    //steps:
    //1) defining material

    //Carbon fiber material
    G4Material *Cu = nist->FindOrBuildMaterial("Cu");
    G4Element *C = nist->FindOrBuildElement("C");
    G4Material *Al = nist->FindOrBuildMaterial("Al");
    G4Material *Carbon_fiber = new G4Material("Carbon_fiber", 1.6*g/cm3,1); 
    Carbon_fiber->AddElement(C, 100*perCent);
    //2) defining properties of the material
    G4VisAttributes *cRed = new G4VisAttributes(G4Colour(1.,0.,0.));
    G4VisAttributes *cBlue = new G4VisAttributes(G4Colour(0.,0.,1.));
    cRed->SetForceWireframe(true);
    cBlue->SetForceWireframe(true);



    //3) defining the volume geometry
    //Source foil
    G4Tubs *SourceFoil = new G4Tubs("Source foil", 0.*mm,26*mm,10*um,0,CLHEP::twopi);
    //Support ring
    G4Tubs *SupportRing = new G4Tubs("Support ring",25.*mm,31.*mm,3.*mm,0,CLHEP::twopi);
    //Copper arm
    G4Tubs *CopperArm = new G4Tubs("Copper arm",0.*mm,3.*mm,100*mm,0,CLHEP::twopi);
    //Upper cylinder endcap
    G4Tubs *UpEndcap = new G4Tubs("Upper endcap",0.*mm,49.0*mm,2*mm,0,CLHEP::twopi);
    //Lower cylinder endcap
    G4Tubs *LowEndcap = new G4Tubs("Lower endcap",0.*mm,49.0*mm,2*mm,0,CLHEP::twopi);
    //Cylindrical walls
    G4Tubs *CylindricalWalls = new G4Tubs("Cylindrical walls",48.9*mm,49.0*mm,150*mm,0,CLHEP::twopi);
    
    
    //4) defining the material of the volume
    //Source foil
    G4LogicalVolume *logicFoil = new G4LogicalVolume(SourceFoil,Cu,"logicFoil");
    logicFoil->SetVisAttributes(cBlue);
    //Support ring 
    G4LogicalVolume *logicRing = new G4LogicalVolume(SupportRing,Cu,"logicRing");
    logicRing->SetVisAttributes(cRed);
    //Copper arm
    G4LogicalVolume *logicArm = new G4LogicalVolume(CopperArm,Cu,"logicArm");
    //Upper cylinder endcap
    G4LogicalVolume *logicUpEndcap = new G4LogicalVolume(UpEndcap,Al,"logicUpEndcap");
    //Lower cylinder endcap
    G4LogicalVolume *logicLowEndcap = new G4LogicalVolume(LowEndcap,Al,"logicLowEndcap");
    //Cylindrical walls
    G4LogicalVolume *logicCylinder = new G4LogicalVolume(CylindricalWalls,Carbon_fiber,"logicCylinder");


    //5) defining the physical features
    //Source foil
    G4VPhysicalVolume *physFoil = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicFoil,"physFoil",logicWorld,false,0,true);
    //Support ring
    G4VPhysicalVolume *physRing = new G4PVPlacement(0,G4ThreeVector(0.,0.,3.2*mm),logicRing,"physRing",logicWorld,false,0,true);
    //Copper arm
    G4VPhysicalVolume *physArm = new G4PVPlacement(0,G4ThreeVector(28*mm,0.,100.*mm),logicArm,"physArm",logicWorld,false,0,true);
    //Upper cylinder endcap
    G4VPhysicalVolume *physUpEndcap = new G4PVPlacement(0,G4ThreeVector(0.,0.,150.*mm),logicUpEndcap,"physUpEndcap",logicWorld,false,0,true);
    //Lower cylinder endcap
    G4VPhysicalVolume *physLowEndcap = new G4PVPlacement(0,G4ThreeVector(0.,0.,-150.*mm),logicLowEndcap,"physLowEndcap",logicWorld,false,0,true);
    //Cylindrical walls
    G4VPhysicalVolume *physCylinder = new G4PVPlacement(0,G4ThreeVector(0.,0.,2.*mm),logicCylinder,"physCylinder",logicWorld,false,0,true);


    
    //Always return the 'mother' volume, because contains all the other volumes
    return physWorld; 
    
}
/*
void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}
*/






