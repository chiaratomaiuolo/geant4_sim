#include "run.hh"

MyRunAction::MyRunAction()
{
    //G4int runID = run->GetRunID();
    //std::stringstream strRunID;
    //strRunID << runID;
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    /*
    //Volumes screening evaluation (to be commented if other studies are to be done)
    //REMEMBER TO CHANGE NTUPLE ID NUMBER HERE AND IN DETECTOR.CC
    man->CreateNtuple("PhotonHits","PhotonHits");
    man->CreateNtupleSColumn("PhotonHitVolume");
    man->FinishNtuple(0);
    */

    
    //DATAS FOR STUDYING THE e- e+ PAIR 
    
    //Histos for energy spectrum of e-
    man->CreateNtuple("elEnergySpectra","elEnergySpectra");
    man->CreateNtupleDColumn("ElectronEnergies");
    man->FinishNtuple(0);
    
    //DATAS FOR STUDYING e- e+ PRODUCTION ASYMMETRY
    //Histo collecting electron generation processes (wherever they are generated)
    man->CreateNtuple("electronProcesses","electronProcesses");
    man->CreateNtupleSColumn("ElectronProcesses");
    man->FinishNtuple(1);

    //Histo for energy spectrum of e+
    man->CreateNtuple("posEnergySpectra","posEnergySpectra");
    man->CreateNtupleDColumn("PositronEnergies");
    man->FinishNtuple(2);

    //Histo for Compton electron energy spectrum (those arriving at the end of the cylinder) 
    man->CreateNtuple("ComptonEnergySpectrum","ComptonEnergySpectrum");
    man->CreateNtupleDColumn("ComptonElectronEnergies");
    man->FinishNtuple(3);

    //Histo for Photoelectric electron energy spectrum (those arriving at the end of the cylinder) 
    man->CreateNtuple("PhotoelectricEnergySpectrum","PhotoelectricEnergySpectrum");
    man->CreateNtupleDColumn("PhotoelectricElectronEnergies");
    man->FinishNtuple(4);

    //Histo for Ionization electron energy spectrum (those arriving at the end of the cylinder) 
    man->CreateNtuple("IonizationEnergySpectrum","IonizationEnergySpectrum");
    man->CreateNtupleDColumn("IonizationElectronEnergies");
    man->FinishNtuple(5);

    //Histo for Ionization electron energy spectrum (those arriving at the end of the cylinder) 
    man->CreateNtuple("ConvEnergySpectrum","ConvEnergySpectrum");
    man->CreateNtupleDColumn("ConvElectronEnergies");
    man->FinishNtuple(6);

    //Histos UPSTREAM e-
    man->CreateNtuple("UpstreamElectrons","UpstreamElectrons");
    man->CreateNtupleSColumn("UpstreamElectronProcesses");
    man->CreateNtupleDColumn("UpstreamElectronExitPX");
    man->CreateNtupleDColumn("UpstreamElectronExitPY");
    man->CreateNtupleDColumn("UpstreamElectronExitPZ");
    man->FinishNtuple(7);

    //Irradiation study
    man->CreateNtuple("Irradiation","Irradiation");
    man->CreateNtupleDColumn("X");
    man->CreateNtupleDColumn("Y");
    man->CreateNtupleDColumn("Z");
    man->FinishNtuple(8);

    //downstream electron study 
    man->CreateNtuple("DownstreamElectrons","DownstreamElectrons");
    man->CreateNtupleSColumn("CreatorProcess");
    man->CreateNtupleDColumn("PX");
    man->CreateNtupleDColumn("PY");
    man->CreateNtupleDColumn("PZ");
    man->FinishNtuple(9);

    man->CreateNtuple("DownstreamExitZ","DownstreamExitZ");
    man->CreateNtupleDColumn("ExitZ");
    man->FinishNtuple(10);



    
    
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
