#include "PickColorAction.h"

#include "..\Figures\CLine.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

PickColorAction::PickColorAction(ApplicationManager * pApp):Action(pApp)
{
	NFigures=0;
	tries=0;
	correct=0;
	incorrect=0;
}

void PickColorAction::ReadActionParameters() 
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	fill=pManager->GetRandomFillClr();
	if(fill==BLACK)
		pOut->PrintMessage("Pick figures with Black fill color");
	else if(fill==WHITE)
		pOut->PrintMessage("Pick figures with White fill color");
	else if(fill==RED)
		pOut->PrintMessage("Pick figures with Red fill color");
	else if(fill==GREEN)
		pOut->PrintMessage("Pick figures with Green fill color");
	else if(fill==BLUE)
		pOut->PrintMessage("Pick figures with Blue fill color");
	else if(fill==INDIAN)
		pOut->PrintMessage("No Figures Remaining");
	else
		pOut->PrintMessage("Pick figures with no fill color");
}

//Execute the action
void PickColorAction::Execute() 
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();
	NFigures=pManager->GetNumberofFillClr(fill);

	if(fill==INDIAN){}
	else{
	while(correct!=NFigures)
	{
		pIn->GetPointClicked(P1.x, P1.y);
		CFigure *Selected=pManager->GetFigure(P1.x,P1.y);
		if(Selected==NULL)
		{
			pOut->PrintMessage("No new figure has been picked");
		}
		else if(pManager->IsCorrectFillClr(Selected,fill))
		{
			correct++;
			pOut->PrintMessage("Correct figure");
		}
		else
		{
			incorrect++;
			pOut->PrintMessage("Incorrect figure");
		}
		tries++;
			pManager->UpdateInterface();
	}
	pOut->PrintMessage("Congratulations! You have won the game. Total number of tries:"+to_string(tries)+". Correct tries:"+to_string(correct)+". Incorrect tries:"+to_string(incorrect)+".");
}
}