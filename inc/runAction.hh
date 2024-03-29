#ifndef RUN_HH
#define RUN_HH

#include "G4SystemOfUnits.hh"
#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

class runAction : public G4UserRunAction
{
    public:
        runAction();
        ~runAction();

        virtual void BeginOfRunAction(const G4Run*);
        virtual void EndOfRunAction(const G4Run*);
};

#endif