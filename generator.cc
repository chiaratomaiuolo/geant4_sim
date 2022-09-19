#include "generator.hh"
#include "Parameters.hh"
#include "TMath.h"
#include "TF1.h"

using namespace GunParameters;


MyPrimaryGenerator::MyPrimaryGenerator()
{
    //Defining the particle gun characteristics. Here it is chosen to have one 
    //primary particle per event. (The hierarchy is: run(events(particles)))
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    //Defining the kind of particle to be shot
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    //Shooting a photon
    G4String particleName = "gamma";
    G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
    //Defining the position and starting momentum of the shot particle
    G4ThreeVector starting_pos(0.,0.,0.);
    G4ThreeVector mom(0.,0.,1.);
    TF1 random_pi = TF1("random_pi", "1", -3.14, 3.14);
    double theta_gamma = random_pi.GetRandom();
    TF1 random = TF1("random", "1", 0, 1);
    double phi_gamma = TMath::ACos(1-2*random.GetRandom());
    G4ThreeVector mom_direction(TMath::Sin(phi_gamma)*TMath::Cos(theta_gamma),TMath::Sin(phi_gamma)*TMath::Sin(theta_gamma),TMath::Cos(phi_gamma));


    //Setting the particle gun characteristics
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(starting_pos);
    fParticleGun->SetParticleMomentumDirection(mom_direction);
    if(function=="gaussian"){
        TF1 gauss = TF1("gauss", "gaus(0)",16.,19.);
        gauss.SetParameter(0,1);
        gauss.SetParameter(1,mean);
        gauss.SetParameter(2,sigma);
        double photon_energy = gauss.GetRandom();
        fParticleGun->SetParticleEnergy(photon_energy*MeV);
    }
    else{
        fParticleGun->SetParticleEnergy(17.6*MeV);
    }
    fParticleGun->GeneratePrimaryVertex(anEvent);

}