#ifndef RESTART_ACTION_H
#define RESTART_ACTION_H

#include "Action.h"

class RestartAction: public Action
{
public:
	RestartAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif