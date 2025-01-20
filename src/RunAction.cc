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
/// \file B1/src/RunAction.cc
/// \brief Implementation of the B1::RunAction class

#include "RunAction.hh"
#include "generator.hh"
#include "construction.hh"
// #include "Run.hh"

#include "G4RunManager.hh"
#include "G4Navigator.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

namespace A93c_neutron_source
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
	
  //G4RunManager::GetRunManager()->SetPrintProgress(1);

  // Create analysis manager
  // The choice of the output format is done via the specified
  // file extension.
    auto analysisManager = G4AnalysisManager::Instance();
    
  // Create directories
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
    analysisManager->SetVerboseLevel(0);
    analysisManager->SetNtupleMerging(true);
  
 
    // Note: merging ntuples is available only with Root output
	analysisManager->SetDefaultFileType("root");    
    analysisManager->SetFileName("Outputfile");
    
    analysisManager->CreateNtuple("Neutrons", "Neutrons incident on detector");
    analysisManager->CreateNtupleDColumn("fNEdep");
    analysisManager->CreateNtupleDColumn("fXlocN");
    analysisManager->CreateNtupleDColumn("fYlocN");
    analysisManager->FinishNtuple(0);
    
    analysisManager->CreateNtuple("Gammas", "Gammas incident on detector");
    analysisManager->CreateNtupleDColumn("fEdep");
    analysisManager->CreateNtupleDColumn("fXlocG");
    analysisManager->CreateNtupleDColumn("fYlocG");
    analysisManager->FinishNtuple(0);
    
 
  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);
  accumulableManager->RegisterAccumulable(fNEdep);
  accumulableManager->RegisterAccumulable(fXlocN);
  accumulableManager->RegisterAccumulable(fYlocN);
  accumulableManager->RegisterAccumulable(fXlocG);
  accumulableManager->RegisterAccumulable(fYlocG);
}

RunAction::~RunAction()
{
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* run)
{


    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
  
  analysisManager->OpenFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run *run)
{
	
	auto analysisManager = G4AnalysisManager::Instance();
		
	analysisManager->Write();
    analysisManager->CloseFile();
    
   

 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}

}
