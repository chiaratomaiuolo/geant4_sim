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

    G4String SDName = preStepPoint->GetSensitiveDetector()->GetName();
    G4cout << "Triggered detector:" << SDName << G4endl; 

    if(track->GetTrackStatus()==2){
        G4cout << "Triggered detector:" << SDName << G4endl;
    }

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
/*
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0,evt);
    man->FillNtupleDColumn(1,posDetector[0]);
    man->FillNtupleDColumn(2,posDetector[1]);
    man->FillNtupleDColumn(3,posDetector[2]);
    man->AddNtupleRow(0);
*/
    return true;
}
