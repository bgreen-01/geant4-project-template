#include "action.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "StackingAction.hh"


namespace placeholder
{

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}
	
void MyActionInitialization::BuildForMaster() const
{
	RunAction *runAction = new RunAction;
	SetUserAction(runAction);
	
}


void MyActionInitialization::Build() const
{
	MyPrimaryGenerator *generator = new MyPrimaryGenerator();
	SetUserAction(generator);
	
	RunAction *runAction = new RunAction;
	SetUserAction(runAction);
	
	EventAction *eventAction = new EventAction(runAction);
	SetUserAction(eventAction);
	
	SteppingAction *steppingAction = new SteppingAction(eventAction);
	SetUserAction(steppingAction);
	
	StackingAction *stackingAction = new StackingAction;
	SetUserAction(stackingAction);
	
		
}

}
