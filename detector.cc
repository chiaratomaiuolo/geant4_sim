#include "detector.hh"
#include "TMath.h"
#include "G4EventManager.hh"
#include "construction.hh"
MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
    
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    //G4int copyNo = touchable->GetCopyNumber();
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4String SDName = preStepPoint->GetSensitiveDetector()->GetName();

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    //Useful variables for particle selection
    G4bool first_step = aStep->IsFirstStepInVolume();
    G4String ParticleName = track->GetParticleDefinition()->GetParticleName();
    G4String process_type = postStepPoint->GetProcessDefinedStep()->GetProcessName();

    //POSITION DISTRIBUTION TEST TO BE IMPLEMENTED


    //Screening factor due to support volumes histogram (comment if simulating the entire processes)
    /*
    if(ParticleName=="gamma" && track->GetTrackID()==1)
    {
        man->FillNtupleSColumn(0,0,SDName);
        man->AddNtupleRow(0);
        track->SetTrackStatus(fStopAndKill);
    }
    */
    /*
    if(SDName=="ControlFoilSensitiveDetector")
    {
        aStep->SetStepLength(0.01*mm);
    }
    */
    /*
    //Controlling how the disc foil is irradiated by the 'sphere' source
    if(ParticleName == "gamma" && track->GetTrackID() == 1 && SDName =="FoilSensitiveDetector" && aStep->IsFirstStepInVolume() == true)
    {
        man->FillNtupleDColumn(8,0,track->GetPosition()[0]);
        man->FillNtupleDColumn(8,1,track->GetPosition()[1]);
        man->FillNtupleDColumn(8,2,track->GetPosition()[2]);
        man->AddNtupleRow(8);
    }
    */
    
    //Studying the downstream e- momentum
    if(ParticleName == "e-" && (SDName == "RingSensitiveDetector" || SDName == "ArmSensitiveDetector" || SDName == "FoilSensitiveDetector") && aStep->IsLastStepInVolume() == true)
    {
        man->FillNtupleSColumn(9,0,track->GetCreatorProcess()->GetProcessName());
        man->FillNtupleDColumn(9,1,track->GetMomentum()[0]);
        man->FillNtupleDColumn(9,2,track->GetMomentum()[1]);
        man->FillNtupleDColumn(9,3,track->GetMomentum()[2]);
        man->AddNtupleRow(9);
        std::cout<<"Tracking an electron in "<<SDName<<" created by the following process: "<<track->GetCreatorProcess()->GetProcessName()<<std::endl;
        std::cout<<"Filling the array with the following ID value: "<<track->GetTrackID()<<std::endl;
        ElectronID.push_back(track->GetTrackID());
        for(G4int i:ElectronID)
        {
            std::cout<<i<<std::endl;
        }    
    }

    if(SDName == "WallsSensitiveDetector" && std::find(ElectronID.begin(), ElectronID.end(), track->GetTrackID())!= ElectronID.end() && aStep->IsLastStepInVolume() == true)
    {
        man->FillNtupleDColumn(10,0,track->GetPosition()[2]);
        //std::cout<<"Putting to -1 ElectronID element: "<<*(std::find(ElectronID.begin(), ElectronID.end(), track->GetTrackID()))<<std::endl;
        //*(std::find(ElectronID.begin(), ElectronID.end(), track->GetTrackID())) = -1;
        for(G4int i:ElectronID)
        {
            std::cout<<i<<std::endl;
        } 
        track->SetTrackStatus(fStopAndKill);
        man->AddNtupleRow(10);
    }

    if(ParticleName == "e-" && track->GetTrackStatus() == 2)
    {
        //*(std::find(ElectronID.begin(), ElectronID.end(), track->GetTrackID())) = -1;
    }
    


    // e-,e+ ENERGY SPECTRUM FOR PARTICLES ESCAPING THE EXTERNAL VOLUME
    
    if(ParticleName=="e-" && SDName=="ControlFoilSensitiveDetector" && aStep->IsLastStepInVolume() == true)
    {
        std::cout<<"UPSTREAM PARTICLE"<<std::endl;
        man->FillNtupleSColumn(7,0,track->GetCreatorProcess()->GetProcessName());
        man->FillNtupleDColumn(7,1,track->GetMomentum()[0]);
        man->FillNtupleDColumn(7,2,track->GetMomentum()[1]);
        man->FillNtupleDColumn(7,3,track->GetMomentum()[2]);
        man->AddNtupleRow(7);

    }
    
    //saving positron energies for e+ escaping the cylinder
    if(SDName=="WallsSensitiveDetector" && ParticleName == "e+" && aStep->IsLastStepInVolume() == true)
    {
        man->FillNtupleDColumn(2,0,preStepPoint->GetTotalEnergy());
        man->AddNtupleRow(2);
    }
    

    //saving electron energies for all e- escaping the cylinder
    if(SDName=="WallsSensitiveDetector" && ParticleName == "e-" && aStep->IsLastStepInVolume() == true)
    {   //filling total energy spectrum of e- histogram (all productions)
        man->FillNtupleDColumn(0,0,preStepPoint->GetTotalEnergy());
        man->AddNtupleRow(0);

        //filling energy spectrum of Compton e- (only Compton)
        if(track->GetCreatorProcess()->GetProcessName()=="compt")
        {
            //std::cout<<"storing Compton electron energy"<<std::endl;
            man->FillNtupleDColumn(3,0,preStepPoint->GetTotalEnergy());
            man->AddNtupleRow(3);

        }
        //filling energy spectrum of Photoelectric e- (only Photoelectric)
        else if(track->GetCreatorProcess()->GetProcessName()=="phot")
        {
            man->FillNtupleDColumn(4,0,preStepPoint->GetTotalEnergy());
            man->AddNtupleRow(4);
        }
        //filling energy spectrum of Ionization e- (only Ionization)
        else if(track->GetCreatorProcess()->GetProcessName()=="eIoni")
        {
            man->FillNtupleDColumn(5,0,preStepPoint->GetTotalEnergy());
            man->AddNtupleRow(5);
        }
        //filling energy spectrum of Conversion e- (only Conversion)
        else if(track->GetCreatorProcess()->GetProcessName()=="conv")
        {
            man->FillNtupleDColumn(6,0,preStepPoint->GetTotalEnergy());
            man->AddNtupleRow(6);
        }
        track->SetTrackStatus(fStopAndKill);
        
    }
    
    


    
    
    
    //Killing particles whose escape from cylinder (graphically ancd computationally useful)
    if(SDName=="WallsSensitiveDetector" && aStep->IsLastStepInVolume() == true)
    {
        track->SetTrackStatus(fStopAndKill);
        
    }

    if(SDName=="LowEndSensitiveDetector" && aStep->IsLastStepInVolume() == true)
    {
        track->SetTrackStatus(fStopAndKill);
        
    }

    if(SDName=="UpEndSensitiveDetector" && aStep->IsLastStepInVolume() == true)
    {
        track->SetTrackStatus(fStopAndKill);
        
    }

    
    

    return true;
}
