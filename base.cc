#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"

#include "G4PhysListFactory.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4GenericBiasingPhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmStandardPhysics.hh"


#include "detectorConstruction.hh"
#include "actionInitialization.hh"

int main(int argc, char** argv)
{
    
    CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine);
    
//    #ifdef G4MULTITHREADED
        G4MTRunManager * runManager = new G4MTRunManager();
        runManager->SetNumberOfThreads(4);
//    #else
//         G4RunManager * runManager = new G4RunManager();
//    #endif
    
    G4PhysListFactory factory;
    G4VModularPhysicsList* physList=factory.GetReferencePhysList("FTFP_BERT__SS"); //add __SS for single scatter
    physList->RegisterPhysics(new G4StepLimiterPhysics());

    runManager->SetUserInitialization(new detectorConstruction());
    runManager->SetUserInitialization(physList);
    runManager->SetUserInitialization(new actionInitialization());
    
    runManager->Initialize();

    G4UIExecutive * ui = 0;
    
    if(argc ==1){
            ui = new G4UIExecutive(argc, argv);
        }

        G4VisManager * visManager = new G4VisExecutive();
        visManager->Initialize();

        G4UImanager* UImanager = G4UImanager::GetUIpointer();

        if(ui){
            UImanager->ApplyCommand("/control/execute vis.mac");
            ui->SessionStart();
            delete ui;
        }
        else{
            CLHEP::HepRandom::setTheSeed((unsigned)clock());
            G4String command = "/control/execute ";
            G4String fileName = argv[1];
            UImanager->ApplyCommand(command+fileName);
        }

    
    delete visManager;
    delete runManager;
    
    return 0;
    
}