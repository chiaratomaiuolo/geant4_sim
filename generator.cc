#include "generator.hh"

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
    //Shooting a proton
    G4String particleName = "proton";
    G4ParticleDefinition *particle = particleTable->FindParticle("proton");
    //Defining the position and starting momentum of the shot particle
    G4ThreeVector pos(0.,0.,0.);
    G4ThreeVector mom(0.,0.,1.);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(100.*GeV);
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);


}