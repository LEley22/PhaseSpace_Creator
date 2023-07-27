#include "senDet.hh"



SenDetClass::SenDetClass(G4String name): G4VSensitiveDetector(name)
{}

SenDetClass::~SenDetClass()
{}

G4bool SenDetClass::ProcessHits(G4Step *aStep, G4TouchableHistory * R0hist)
{


    G4Track * track = aStep->GetTrack();
    //track->SetTrackStatus(fStopAndKill); //kill photons after enter detector

    const G4String& VolName = track->GetVolume()->GetName();

    auto material = aStep->GetTrack()->GetMaterial();
    auto density = material->GetDensity();
    G4double Volume = (aStep->GetTrack()->GetVolume()->GetLogicalVolume()->GetSolid()->GetCubicVolume());
    G4double mass= Volume * density;

    G4StepPoint *preStepPoint = aStep -> GetPreStepPoint(); //enter detector
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); //exits detector
    
    G4double edep1 = preStepPoint->GetTotalEnergy(); //get photon energy when it enters step
    G4ThreeVector MomDir = aStep->GetPreStepPoint()->GetMomentumDirection();
    
    G4double Dose = edep1/mass;

    G4ThreeVector posPhoton = preStepPoint->GetPosition(); //get photon position when it enters

//    #ifndef G4MULTITHREADED
//        G4cout << "Photon position " << posPhoton << G4endl; //to print pos
//    #endif

    G4AnalysisManager * man = G4AnalysisManager::Instance();

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();



    man->FillNtupleIColumn(0, evt);                 //fill N tuple
    man->FillNtupleSColumn(1, VolName);
    man->FillNtupleDColumn(2, posPhoton[0]);
    man->FillNtupleDColumn(3, posPhoton[1]);
    man->FillNtupleDColumn(4, posPhoton[2]);
    man->FillNtupleDColumn(5, edep1);  //take INITIAL energy of photon at end (detector is air so should not affect E)
    man->FillNtupleDColumn(6, Dose);
    man->FillNtupleDColumn(7, MomDir[0]);
    man->FillNtupleDColumn(8, MomDir[1]);
    man->FillNtupleDColumn(9, MomDir[2]);
    man->AddNtupleRow(0);

    if (VolName == "detPhysical"){
        man->FillH1(0, edep1);

        man->FillH2(0, posPhoton[0], posPhoton[1], 0.0); //ID, x, y, weighting
    }

    else{
        G4cout << "That's not a sensitive detector!" << G4endl;
    };


return true;
}
