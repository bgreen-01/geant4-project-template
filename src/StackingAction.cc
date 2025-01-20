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
/// \file B3/B3a/src/StackingAction.cc
/// \brief Implementation of the B3::StackingAction class

#include "StackingAction.hh"

#include "G4Track.hh"
#include "G4Neutron.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Alpha.hh"

namespace A93c_neutron_source
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track* track)
{
	
	G4double mass = track->GetDefinition()->GetPDGMass();
		
    ////keep Cf-252, Cm-248, gammas and neutrons 
    if (track->GetDefinition() == G4Gamma::Gamma()) return fUrgent;
    if (track->GetDefinition() == G4Neutron::Neutron()) return fUrgent;
    
	
	////mass is in amu (atomic number*931.49 MeV)
	if (mass >= 230000) return fUrgent; //retain cf-252 but kill decay prods
	//if (125000 <= mass <= 130000) return fUrgent; //retain cs-137 atoms
	
	////optional Alpha saving if potential for a,n production 
	if (track->GetDefinition() == G4Alpha::Alpha()) return fUrgent;
		
	
	//kill secondaries 
    else return fKill;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}

