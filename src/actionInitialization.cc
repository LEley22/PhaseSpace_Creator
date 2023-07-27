#include "actionInitialization.hh"

actionInitialization::actionInitialization()
{}

actionInitialization::~actionInitialization()
{}

void actionInitialization::BuildForMaster() const
{
    runAction* runaction = new runAction();
    SetUserAction(runaction);
}

void actionInitialization::Build() const
{
    primaryGeneratorAction * generator = new primaryGeneratorAction();
    SetUserAction(generator);

    runAction * runaction = new runAction();
    SetUserAction(runaction);
}