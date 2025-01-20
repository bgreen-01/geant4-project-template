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
/// \file optical/OpNovice2/src/DetectorMessenger.cc
/// \brief Implementation of the DetectorMessenger class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "construction.hh"
#include "DetectorMessenger.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIparameter.hh"

#include <sstream>
#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(MyDetectorConstruction* Det)
  : G4UImessenger()
  , fDetector(Det)
{
  fMatDir = new G4UIdirectory("/targetMat/");
  fMatDir->SetGuidance("Change properties of the target material");

  fMaterialCmd = new G4UIcmdWithAString("/targetMat/material", this);
  fMaterialCmd->SetGuidance("Select material");
  fMaterialCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fMaterialCmd->SetToBeBroadcasted(false);
  
  fMaterialCompA = new G4UIcmdWithADouble("/targetMat/compA", this);
  fMaterialCompA->SetGuidance("Adjust mass percent of target material part A (0.-1.)");
  fMaterialCompA->SetParameterName("wtpercentA", false);
  fMaterialCompA->SetRange("wtpercentA>=0. && wtpercentA<=1.");
  fMaterialCompA->SetDefaultValue(1.);
  fMaterialCompA->AvailableForStates(G4State_PreInit, G4State_Idle);
  fMaterialCompA->SetToBeBroadcasted(false);
  
  fMaterialCompB = new G4UIcmdWithADouble("/targetMat/compB", this);
  fMaterialCompB->SetGuidance("Adjust mass percent of target material part B (0.-1.)");
  fMaterialCompB->SetParameterName("wtpercentB", false);
  fMaterialCompB->SetRange("wtpercentB>=0. && wtpercentB<=1.");
  fMaterialCompB->SetDefaultValue(0.);
  fMaterialCompB->AvailableForStates(G4State_PreInit, G4State_Idle);
  fMaterialCompB->SetToBeBroadcasted(false);
  
  fMaterialDensity = new G4UIcmdWithADoubleAndUnit("/targetMat/density", this);
  fMaterialDensity->SetGuidance("Adjust the density of target material to accomodate composition change");
  fMaterialDensity->SetParameterName("targetDensity", false);
  fMaterialCompB->SetRange("targetDensity>=0. && targetDensity<=100.");
  fMaterialDensity->SetDefaultValue(10.);
  fMaterialDensity->SetDefaultUnit("g/cm3");
  fMaterialDensity->AvailableForStates(G4State_PreInit, G4State_Idle);
  fMaterialDensity->SetToBeBroadcasted(false);
  
  fMaterialThickness = new G4UIcmdWithADoubleAndUnit("/targetMat/thickness", this);
  fMaterialThickness->SetGuidance("Set the half thickness value of the target material (x-direction)");
  fMaterialThickness->SetParameterName("targetThickness", false);
  fMaterialCompB->SetRange("targetThickness>=0.25");
  fMaterialThickness->SetDefaultValue(5.);
  fMaterialThickness->SetDefaultUnit("mm");
  fMaterialThickness->AvailableForStates(G4State_PreInit, G4State_Idle);
  fMaterialThickness->SetToBeBroadcasted(false);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fMatDir;
  delete fMaterialCmd;
  delete fMaterialCompA;
  delete fMaterialCompB;
  delete fMaterialDensity;
  delete fMaterialThickness;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{

  if(command == fMaterialCmd)
  {
    fDetector->SetTargetMaterial(newValue);
  }
  
  if(command == fMaterialCompA)
  {
    fDetector->SetTargetCompA(fMaterialCompA->GetNewDoubleValue(newValue));
  }
  
  if(command == fMaterialCompB)
  {
    fDetector->SetTargetCompB(fMaterialCompB->GetNewDoubleValue(newValue));
  }
  
  if(command == fMaterialDensity)
  {
    fDetector->SetTargetDensity(fMaterialDensity->GetNewDoubleValue(newValue));
  }
  
  if(command == fMaterialThickness)
  {
  	fDetector->SetTargetThickness(fMaterialThickness->GetNewDoubleValue(newValue));
  }
  
  
  else return;
  
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
