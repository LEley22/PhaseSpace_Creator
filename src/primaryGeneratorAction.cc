#include "primaryGeneratorAction.hh"

//PRIMARY GENERATOR USING GAUSSIAN PENCIL BEAM

primaryGeneratorAction::primaryGeneratorAction() //info in here to allow overrun by macro files
{
    ParticleGun = new G4ParticleGun(1); //no of particles per event

     G4ParticleTable * particleTable = G4ParticleTable::GetParticleTable();

    G4String particleName = "e-";
    G4ParticleDefinition * particle = particleTable->FindParticle("e-");

    G4ThreeVector momentum(0.,0.,1.); //momentum direction
    
    ParticleGun->SetParticleMomentumDirection(momentum);
    ParticleGun->SetParticleDefinition(particle);
}

primaryGeneratorAction::~primaryGeneratorAction()
{

    delete ParticleGun;
}

void primaryGeneratorAction::GeneratePrimaries(G4Event * anEvent)
{
     G4double c0=(G4RandGauss::shoot(0,100./6))*um; //mean, sigma
     G4double d0=(G4RandGauss::shoot(0,100./6))*um;
    
     ParticleGun->SetParticlePosition(G4ThreeVector(c0, d0, -0.81*m));
     ParticleGun->GeneratePrimaryVertex(anEvent);
}