#include "detectorConstruction.hh"
#include "senDet.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4UserLimits.hh"
#include <fstream>
#include <iostream>
#include <string>
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"



detectorConstruction::detectorConstruction()//constructor
{
    Thickness = 6;
    G4RunManager* runManager = G4RunManager::GetRunManager();
    Messenger = new G4GenericMessenger(this, "/detector/", "thickness");
    Messenger->DeclareProperty("thickness", Thickness, "Target thickness");
    runManager->GeometryHasBeenModified();

    DefineMaterials();

}


detectorConstruction::~detectorConstruction() //destructor
{
  if(TargetLogic)
  {
    delete TargetLogic;
    delete worldLogic;
  }
}


void detectorConstruction::DefineMaterials()
{
    //Manager
    G4NistManager* nist = G4NistManager::Instance();
    //Materials
    vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    Tantalum = nist->FindOrBuildMaterial("G4_Ta");  //tantalum (material)
    Aluminium = nist->FindOrBuildMaterial("G4_Al");  //aluminium (material)
    Tungsten= nist->FindOrBuildMaterial("G4_W");  //tungsten (material)

}

G4VPhysicalVolume * detectorConstruction::Construct()
{
  
//WORLD CREATION//
    worldSolid = new G4Box("worldSolid", 0.5*m, 0.5*m, 1.*m); //name and half size in m

    worldLogic = new G4LogicalVolume(worldSolid,   //call solid
                                      vacuum,         //material to be made of
                                      "worldLogic"); //name

    worldPhysical = new G4PVPlacement(0,    //rotation
                                                        G4ThreeVector(0,0,0), //location
                                                        worldLogic, //logic volume
                                                        "worldPhysical", //name
                                                        0, //mother volume (0 as it is mother)
                                                        false,
                                                        0, //copy number
                                                        true); //check overlaps

    // TARGET CREATION


    TargetSolid = new G4Box("TargetSolid", 0.5*m, 0.5*m, Thickness * um); //name and half size in m
    //half thickness is 6um for 90 keV, 9 um for 120 keV

    G4cout << "Thickness is " << Thickness << G4endl;

    TargetLogic = new G4LogicalVolume(TargetSolid,   //call solid
                                                        Tantalum,         //material to be made of
                                                        "TargetLogic"); //name

    TargetPhysical = new G4PVPlacement(0,    //rotation
                                                        G4ThreeVector(0,0,0*m), //location
                                                        TargetLogic, //logic volume
                                                        "TargetPhysical", //name
                                                        worldLogic, //mother volume (0 as it is mother)
                                                        false,
                                                        0, //copy number
                                                        true); //check overlaps



//FILTER CREATION
//REGULATORY MIN AL 
   AlFilterSolid = new G4Box("AlFilterSolid", 0.5*m, 0.5*m, 1.25*mm); //name and half size in m

   AlFilLogic = new G4LogicalVolume(AlFilterSolid,   //call solid
                                                       Aluminium,         //material to be made of
                                                       "AlFilLogic"); //name

   AlPhysical = new G4PVPlacement(0,    //rotation
                                                       G4ThreeVector(0,0,10*cm), //location
                                                       AlFilLogic, //logic volume
                                                       "AlPhysical", //name
                                                       worldLogic, //mother volume
                                                       false,
                                                       0, //copy number
                                                       true); //check overlaps



//DETECTOR CREATION
    detSolid = new G4Box("detSolid", 0.5*m, 0.5*m, 1*mm); //name and half size in m
    //to match ipioni (which is 43 x 43 bin with 1cm/pixel you need 43/2 cm widths)


    detLogic = new G4LogicalVolume(detSolid,   //call solid
                                                        vacuum,         //material to be made of
                                                        "detLogic"); //name

    G4ThreeVector DetPosition = G4ThreeVector(0.,0.,10.25*cm); //originally 0.100006m but moved for now

    detPhysical = new G4PVPlacement(0,    //rotation
                                                        DetPosition, //location
                                                        detLogic, //logic volume
                                                        "detPhysical", //name
                                                        worldLogic, //mother volume
                                                        false,
                                                        0, //copy number
                                                        true); //check overlaps

//VIS ATTRIBUTES (FOR UI)

    G4VisAttributes* visAtt1 = new G4VisAttributes(G4Colour(0.0,1.0,1.0)); //detector is cyan
    visAtt1->SetForceSolid(true);
    detLogic->SetVisAttributes(visAtt1);

    G4VisAttributes* visAtt2 = new G4VisAttributes(G4Colour(0.0,0.0,1.0)); //target is blue
    visAtt2->SetForceSolid(true);
    TargetLogic->SetVisAttributes(visAtt2);

    G4VisAttributes* visAtt4 = new G4VisAttributes(G4Colour(0.5,0.5,0.5)); //aluminium is grey
    visAtt4->SetForceSolid(true);
    AlFilLogic->SetVisAttributes(visAtt4);


 //USER LIMITS

  // Set a minimum kinetic energy for charged particles
//   G4UserLimits* fStepLimit = new G4UserLimits();
//   fStepLimit->SetUserMinEkine(15*keV);
//   G4LogicalVolumeStore* store = G4LogicalVolumeStore::GetInstance();
//   std::vector<G4LogicalVolume*>::iterator it;
//   for (it=store->begin(); it!=store->end(); it++){
//     (*it)->SetUserLimits(fStepLimit);
//   }



return worldPhysical;
}

void detectorConstruction::ConstructSDandField()
{
    SenDetClass *senDet  = new SenDetClass("SensitiveDetector");
    detLogic -> SetSensitiveDetector(senDet);

  
}
