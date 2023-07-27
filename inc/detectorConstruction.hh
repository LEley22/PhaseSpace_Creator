#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "senDet.hh"
#include "G4VisAttributes.hh"
#include "G4UImanager.hh"
#include "G4GenericMessenger.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;
class SenDetClass;

class detectorConstruction : public G4VUserDetectorConstruction
{
    public:
        detectorConstruction();
        ~detectorConstruction();

        std::vector<G4VisAttributes*> fVisAttributes();

        void ConstructSDandField();

        virtual G4VPhysicalVolume * Construct();

    private:
        G4LogicalVolume *detLogic;
        G4LogicalVolume *TargetLogic;

        G4GenericMessenger * Messenger;

        G4double Thickness;

        G4Box * worldSolid, *TargetSolid, *detSolid, *AlFilterSolid;

        G4LogicalVolume * worldLogic, * AlFilLogic; 

        G4VPhysicalVolume * worldPhysical, *TargetPhysical, *detPhysical,  *AlPhysical; 

        G4Material *vacuum, *Tantalum, *Tungsten, *Aluminium;

        void DefineMaterials();


        
};


#endif