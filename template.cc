#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "generator.hh"
#include "QGSP_BIC_HP.hh"

using namespace placeholder;

int main(int argc, char** argv)
{
	
	#ifdef G4MULTITHREADED
		std::unique_ptr<G4MTRunManager>runManager = std::make_unique<G4MTRunManager>();
	#else
		std::unique_ptr<G4RunManager>runManager = std::make_unique<G4RunManager>();
	#endif
	
	runManager->SetUserInitialization(new MyDetectorConstruction());
	runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
	runManager->SetNumberOfThreads(10);
	runManager->SetVerboseLevel(1);
	
	runManager->Initialize();
	
	std::unique_ptr<G4UIExecutive>ui;
		
	//checks if one argument is present
	if(argc == 1)
	{
		ui = std::make_unique<G4UIExecutive>(argc, argv);
	}
	
	std::unique_ptr<G4VisManager>visManager = std::make_unique<G4VisExecutive>();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	//if only one argument then runs vis.mac for interactive mode
	if(ui)
	{
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
	}
	
	//if a macro is passed in the terminal, interactive mode is 
	//not enabled and batch mode is used
	else
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
	
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

	return 0;
}
