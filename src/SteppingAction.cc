//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1/src/SteppingAction.cc
/// \brief Implementation of the B1::SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "construction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Types.hh"

#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4ParticleTypes.hh"

namespace placeholder
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction) : fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step *step)
{
  	
  	G4Track *track=step->GetTrack();
         
    G4String ParticleName = track->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();
    G4double energyHigh = track->GetVertexKineticEnergy()/MeV;

    

    const G4VTouchable *touchable = step->GetPreStepPoint()->GetTouchable();
    	
	if (!fScoringVolume) 
	{
    	const auto detConstruction = static_cast<const MyDetectorConstruction*>(
    	G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    	fScoringVolume = detConstruction->GetScoringVolume();
    }
	
	//get volume of the current step
	G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	G4ThreeVector *loc = new G4ThreeVector();
	
	if (volume == fScoringVolume)
	{
		if (ParticleName == "gamma")
		{
			G4double edep = track->GetKineticEnergy()/eV;
			*loc = track->GetPosition();
			G4double xlocg = loc->getX();
			G4double ylocg = loc->getY();
			
			fEventAction->AddEdep(edep);
			fEventAction->AddXloc(xlocg);
			fEventAction->AddYloc(ylocg);
			track->SetTrackStatus(fStopAndKill); 
		}
		
		if (ParticleName == "neutron")
		{
			G4double Nedep = track->GetKineticEnergy()/eV;
			*loc = track->GetPosition();
			G4double xlocn = loc->getX();
			G4double ylocn = loc->getY();
			
  			fEventAction->AddNEdep(Nedep);
  			fEventAction->AddXloc(xlocn);
			fEventAction->AddYloc(ylocn);  		
			track->SetTrackStatus(fStopAndKill); 
		}
	}
	
	delete loc;
	
	if (volume != fScoringVolume) return;
	
}
	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
