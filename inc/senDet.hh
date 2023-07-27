#ifndef SENDET_HH
#define SENDET_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

class G4Step;
class G4TouchableHistory;

class SenDetClass : public G4VSensitiveDetector
{
    public:
        SenDetClass(G4String name);
        ~SenDetClass();
    
    private:
        virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif
