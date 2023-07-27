#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"
#include <cmath>
#include "G4RunManager.hh"

class primaryGeneratorAction:public G4VUserPrimaryGeneratorAction
{
public: 
    primaryGeneratorAction();
    ~primaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event *);

private:
    G4ParticleGun * ParticleGun;
};

#endif