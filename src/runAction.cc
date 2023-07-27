#include "runAction.hh"
#include <chrono>
#include <ctime>
#include <mutex>

std::mutex histogramMutex; //lock for the histogram to ensure thread safety (no race conditions for data reaching write -> only one thread at a time allowed$

runAction::runAction()
{

    G4AnalysisManager* man = G4AnalysisManager::Instance();

    man->CreateNtuple("Hits", "Hits"); //create Ntuple rows
    man->CreateNtupleIColumn("fEvent"); //create integer column for event no
    man->CreateNtupleSColumn("VolName");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");  //double columns with x,y,z coord of hit
    man->CreateNtupleDColumn("eDep");
    man->CreateNtupleDColumn("Dose");
    man->CreateNtupleDColumn("momX");
    man->CreateNtupleDColumn("momY");
    man->CreateNtupleDColumn("momZ");  //double columns with x,y,z coord of hit
    man->FinishNtuple(0); //finish this first Ntuple

    man->CreateH1("Eabs","Edep in detector", 100, 0., 150*keV);
}

runAction::~runAction()
{}

void runAction::BeginOfRunAction(const G4Run* run)
{

    G4AnalysisManager* man = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();

    std::stringstream strRunID;
        strRunID << runID;

    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the time to a string
    std::stringstream timeStream;
    timeStream << std::put_time(std::localtime(&currentTime), "%d%H%M%S");

    // Set the histogram name including the run ID
    G4String histogramName = "Hits" + timeStream.str();

    G4cout << histogramName << G4endl;

        // Create the histogram
    man->CreateH2(histogramName, "HitsXY",
                      1628, -8 * cm,  8 * cm,    
                      2430, -12 * cm,  12 * cm,
                      "um",
                      "um",
                      "none",
                      "none",
                      "linear",
                      "linear");

    man->GetH2( man->GetH2Id(histogramName))->reset();

       // Open the output file with the run ID included in the name
    man->OpenFile("Output" + timeStream.str() + ".csv");


}

void runAction::EndOfRunAction(const G4Run *)
{

    std::lock_guard<std::mutex> lock(histogramMutex);

    G4AnalysisManager* man = G4AnalysisManager::Instance();

    man->Write();
    G4cout << "Written" << G4endl;
    man->CloseFile(true);
    G4cout << "Closed" << G4endl;


}
