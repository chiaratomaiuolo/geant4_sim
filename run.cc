#include "run.hh"

MyRunAction::MyRunAction()
{
    //G4int runID = run->GetRunID();
    //std::stringstream strRunID;
    //strRunID << runID;
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    man->CreateNtuple("electronHits","electronHits");
    man->CreateNtupleDColumn("electronTimeInSupportRing");
    man->CreateNtupleDColumn("electronEnergy");
    man->FinishNtuple(0);
    man->CreateNtuple("positronHits","positronHits");
    man->CreateNtupleDColumn("positronTimeInSupportRing");
    man->CreateNtupleDColumn("positronEnergy");
    man->FinishNtuple(1);
    
    
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* )
{   
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->OpenFile("output.root");
    
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    

    man->Write();
    man->CloseFile();
    
}
