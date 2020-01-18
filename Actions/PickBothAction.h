#ifndef PICK_BOTH_ACTION_H
#define PICK_BOTH_ACTION_H

#include "Action.h"

class PickBothAction: public Action
{
private:
	color fill;
	string type;
	int NFigures,tries,correct,incorrect;
	Point P1;
public:
	PickBothAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif