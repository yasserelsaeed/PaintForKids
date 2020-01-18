#include "PickBothAction.h"
#include "..\Figures\CLine.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

PickBothAction::PickBothAction(ApplicationManager * pApp):Action(pApp)
{
	NFigures=0;
	tries=0;
	correct=0;
	incorrect=0;
}

void PickBothAction::ReadActionParameters() 
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	fill=pManager->GetRandomFillClr();
	type=pManager->GetRandomShape();
	string temp;
	if(fill==BLACK)
		temp=" Black fill color";
	else if(fill==WHITE)
		temp=" White fill color";
	else if(fill==RED)
		temp=" Red fill color";
	else if(fill==GREEN)
		temp=" Green fill color";
	else if(fill==BLUE)
		temp=" Blue fill color";

	else
		temp=" no fill color";
	if(type!="NULL"){
		pOut->PrintMessage("Pick all "+type+"S with"+temp);}
		else {pOut->PrintMessage("No Figures Remaining");}
}

//Execute the action
void PickBothAction::Execute() 
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();
	NFigures=pManager->GetNumberofBoth(fill,type);

	if(type!="NULL"){
	while(correct!=NFigures)
	{
		pIn->GetPointClicked(P1.x, P1.y);
		CFigure *Selected=pManager->GetFigure(P1.x,P1.y);
		if(Selected==NULL)
		{
			pOut->PrintMessage("No new figure has been picked");
		}
		else if(pManager->IsCorrectBoth(Selected,fill,type))
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