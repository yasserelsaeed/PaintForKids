#ifndef PICK_COLOR_ACTION_H
#define PICK_COLOR_ACTION_H

#include "Action.h"

class PickColorAction: public Action
{
private:
	color fill;
	int NFigures,tries,correct,incorrect;
	Point P1;
public:
	PickColorAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif