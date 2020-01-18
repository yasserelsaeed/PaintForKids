#ifndef PICK_SHAPE_ACTION_H
#define PICK_SHAPE_ACTION_H

#include "Action.h"

class PickShapeAction: public Action
{
private:
	string type;
	int NFigures,tries,correct,incorrect;
	Point P1;
public:
	PickShapeAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif