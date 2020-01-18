#ifndef PASTE_ACTION_H
#define PASTE_ACTION_H

#include "Action.h"

class PasteAction: public Action
{
private:
	Point P1;
public:
	PasteAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif