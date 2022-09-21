#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    //G4ThreeVector posPhoton = preStepPoint->GetPosition();
    // G4cout << "Photon position:" << posPhoton << G4endl;
   
    //We usually need the position of the detector (this is what is effectively
    //detected) inside the world volume. 
    
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    //G4int copyNo = touchable->GetCopyNumber();
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4String SDName = preStepPoint->GetSensitiveDetector()->GetName();
    G4cout << "Triggered detector:" << SDName << G4endl; 

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    if(track->GetTrackStatus()==2){
        G4cout << "particle stopped in this detector:" << SDName << G4endl;
    }
    //Killing particles whose escape from cylinder
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

    

    //Selecting electrons and positrons inside the ring, saving global times for further selection offline
    //Selecting values
    G4bool first_step = aStep->IsFirstStepInVolume();
    G4String ParticleName = track->GetParticleDefinition()->GetParticleName();
    //If selections and storing in histos
    if(SDName=="RingSensitiveDetector" && aStep->IsFirstStepInVolume() == true && track->GetParticleDefinition()->GetParticleName() == "e-")
    {
        G4double time_electron = track->GetGlobalTime(); 
        man->FillNtupleDColumn(0,0,time_electron);
        man->FillNtupleDColumn(0,1,track->GetTotalEnergy());
        man->AddNtupleRow(0);
    }

    if(SDName=="RingSensitiveDetector" && first_step == true && ParticleName == "e+")
    {
        G4double time_positron = track->GetGlobalTime(); 
        man->FillNtupleDColumn(1,0,time_positron);
        man->FillNtupleDColumn(1,1,track->GetTotalEnergy());
        man->AddNtupleRow(1);
    }

    //G4String process_type = preStepPoint->GetProcessDefinedStep()->GetProcessName();
    
    //man->FillNtupleIColumn(0,0,evt);
    //man->FillNtupleSColumn(0,0,process_type);
    //man->FillNtupleSColumn(0,1,SDName);

    

    return true;
}
