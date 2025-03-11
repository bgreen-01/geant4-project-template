#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "DetectorMessenger.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Isotope.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
	
	virtual G4VPhysicalVolume *Construct();
	
	void SetTargetMaterial(const G4String&);
    G4Material* GetTargetMaterial() const { return fTargetMaterial; }
    
    void SetTargetCompA(const G4double&);
    G4double GetTargetCompA() const { return fCompA; }
    
    void SetTargetCompB(const G4double&);
    G4double GetTargetCompB() const { return fCompB; }
    
    void SetTargetDensity(const G4double&);
    G4double GetTargetDensity() const { return fTargetDensity; }
    
    void SetTargetThickness(const G4double&);
    G4double GetTargetThickness() const { return fTargetThickness; }
	
private:
	
	virtual void ConstructSDandField();
	
	G4GenericMessenger *fMessenger;
	DetectorMessenger* fDetectorMessenger = nullptr;
	
	G4Material* fTargetMaterial = nullptr;
	G4double fCompA = 1.;
	G4double fCompB = 0.;
	G4double fTargetDensity = 10.;
	G4double fTargetThickness = 5.;
	
	G4LogicalVolume *fScoringVolume, *logicWorld, *logicTarget, *logicDetector;
	G4VSolid *solidWorld, *solidTarget, *solidDetector;
	G4VPhysicalVolume *physWorld, *physTarget, *physDetector;
	
	
	G4Material *H2O, *air;
	
	void DefineMaterials();
};
#endif
