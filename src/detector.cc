#include "detector.hh"
#include "construction.hh"
#include "G4ParticleTypes.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
		
	G4Track *track = aStep->GetTrack();
	
	G4LogicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	if (volume == fScoringVolume)
	{
		track->SetTrackStatus(fStopAndKill);
	}
	
	//prevents particle (photon) from registering multiple times 
	//i.e. particle only detected on exposed detector face -> all energy deposited in one go
	/*
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	G4String ParticleName = track->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();
	G4double particleEnergy = track->GetVertexKineticEnergy()/MeV;
  
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	
	*/
	
	return true;
		 	
}
