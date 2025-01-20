#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "StackingAction.hh"


namespace placeholder
{


class MyActionInitialization : public G4VUserActionInitialization
{
public: 
	MyActionInitialization();
	virtual ~MyActionInitialization();
	
	virtual void BuildForMaster() const;
	virtual void Build() const;
};

}
#endif 
