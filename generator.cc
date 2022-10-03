#include "generator.hh"
//#include "Parameters.hh"
#include "TMath.h"
#include "TF1.h"

//using namespace GunParameters;


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
    fParticleGun->SetParticleDefinition(particle);
    //Defining the position and starting momentum of the shot particle. 
    //The position inside the disk is gaussian distributed on x,y
    //The starting momentum direction is uniform on all the solid angle

    TF1 gauss_position = TF1("gauss_position", "gaus(0)",-9,9.);
    double mean_pos = 0.;
    double sigma_pos = 3.;
    double norm_pos = (1/(sigma_pos*TMath::Sqrt((TMath::TwoPi())))); 
    gauss_position.SetParameter(0,norm_pos);
    gauss_position.SetParameter(1,mean_pos);
    gauss_position.SetParameter(2,sigma_pos);
    gauss_position.Draw();
    double x_0 = gauss_position.GetRandom();
    double y_0 = gauss_position.GetRandom();
    G4ThreeVector starting_pos(x_0*mm,y_0*mm,12.5*um);
    fParticleGun->SetParticlePosition(starting_pos);


    TF1 random_pi = TF1("random_pi", "1", -TMath::Pi(), TMath::Pi());
    double theta_gamma = random_pi.GetRandom();
    TF1 random = TF1("random", "1", -1, 1);
    //TF1 random = TF1("random", "1", 0.01, TMath::Cos((0.5*TMath::Pi())-(TMath::ATan(5.99/25))));
    double phi_gamma = TMath::ACos(random.GetRandom());
    G4ThreeVector mom_direction(TMath::Sin(phi_gamma)*TMath::Cos(theta_gamma),TMath::Sin(phi_gamma)*TMath::Sin(theta_gamma),TMath::Cos(phi_gamma));
    fParticleGun->SetParticleMomentumDirection(mom_direction);


    TF1 gauss_energy = TF1("gauss_energy", "gaus(0)",16.,19.);
    double mean_energy = 18.1;
    double sigma_energy = 0.1;
    double norm_energy = (1/(sigma_energy*TMath::Sqrt((TMath::TwoPi()))));
    gauss_energy.SetParameter(0,norm_energy);
    gauss_energy.SetParameter(1,mean_energy);
    gauss_energy.SetParameter(2,sigma_energy);
    double photon_energy = gauss_energy.GetRandom();
    fParticleGun->SetParticleEnergy(photon_energy*MeV);


    fParticleGun->GeneratePrimaryVertex(anEvent);

}