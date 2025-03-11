#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	/*fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
	
	fMessenger->DeclareProperty("xPos", xPosDet, "Adjust x-position of detector. Default 67.045 (cm)");
	fMessenger->DeclareProperty("yPos", yPosDet, "Adjust y-position of detector. Default -10 (cm)");
	fMessenger->DeclareProperty("zPos", zPosDet, "Adjust z-position of detector. Default 30 (cm)");
	
	/*xPosDet = 67.045;
	yPosDet = 7.;
	zPosDet = 30.;*/
	
	DefineMaterials();
	fDetectorMessenger = new DetectorMessenger(this);	
}

MyDetectorConstruction::~MyDetectorConstruction()
{
	delete fDetectorMessenger;
}

void MyDetectorConstruction::DefineMaterials()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	//Build materials
	
	////water
	H2O = new G4Material("H2O", 2.3*g/cm3, 2);
	H2O->AddElement(nist->FindOrBuildElement("H"), 2);
	H2O->AddElement(nist->FindOrBuildElement("O"), 1);
	
	//set world material
	air = nist->FindOrBuildMaterial("G4_AIR");
	
	fTargetMaterial = H2O;
	

}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4RotationMatrix *Rotation = new G4RotationMatrix();
	Rotation->rotateX(90*deg);
	Rotation->rotateY(0*deg);
	Rotation->rotateZ(0*deg);
	
	//set world dimensions and properties
	solidWorld =  new G4Box("solidWorld", 1.*m, 1.*m, 1.*m);
	logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	
	//target block with variable material messenger
	solidTarget = new G4Box("solidTarget", 100*mm, 100*mm, 20*mm);
	logicTarget = new G4LogicalVolume(solidTarget, fTargetMaterial, "logicTarget");
	physTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicTarget, "physTarget", logicWorld, false, 0, true);
	
	//detector
	solidDetector = new G4Box("solidDetector", 100*mm, 100*mm, 10*mm);
	logicDetector = new G4LogicalVolume(solidDetector, air, "logicDetector");
	physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 50.*mm), logicDetector, "physDetector", logicWorld, false, 0, true);
	
	fScoringVolume = logicDetector;
		
	G4cout << "Target material: " << fTargetMaterial->GetName() << G4endl;
	
		
	return physWorld;
		
}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	
	logicDetector->SetSensitiveDetector(sensDet);
};

void MyDetectorConstruction::SetTargetMaterial(const G4String& mat)
{
  G4Material* pmat = G4NistManager::Instance()->FindOrBuildMaterial(mat);
  if(pmat && fTargetMaterial != pmat)
  {
    fTargetMaterial = pmat;
    if(logicTarget)
    {
      logicTarget->SetMaterial(fTargetMaterial);
    }
    
    
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
    
    G4cout << "Target material set to " << fTargetMaterial->GetName() << G4endl;
  }
}

void MyDetectorConstruction::SetTargetCompA(const G4double& CompA)
{
  
  G4double pCompA = CompA;
  if(pCompA && fCompA != pCompA)
  {
    fCompA = pCompA;
    
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();    
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
    
    G4cout << "Material A wtperCent set to " << fCompA << G4endl;
  }
}

void MyDetectorConstruction::SetTargetCompB(const G4double& CompB)
{
  
  G4double pCompB = CompB;
  if(pCompB && fCompB != pCompB)
  {
    fCompB = pCompB;
    
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();    
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
    
    G4cout << "Boron wtperCent set to " << fCompB << G4endl;
  }
}

void MyDetectorConstruction::SetTargetDensity(const G4double& targetDensity)
{
  
    fTargetDensity = targetDensity;
    
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();    
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
    
    G4cout << "Density set to " << fTargetDensity << " g/cm3" << G4endl;
  
}

void MyDetectorConstruction::SetTargetThickness(const G4double& targetThickness)
{
  
  G4double pTargetThickness = targetThickness;
  if(pTargetThickness && fTargetThickness != pTargetThickness)
  {
    fTargetThickness = pTargetThickness;
    
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();    
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
    //G4RunManager::GetRunManager()->ReinitializeGeometry();
    double actualThickness = fTargetThickness*2;
    
    G4cout << "Target thickness set to " << actualThickness << " mm" <<G4endl;
  }
}

