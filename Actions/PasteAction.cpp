#include "PasteAction.h"
#include "..\Figures\CLine.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

PasteAction::PasteAction(ApplicationManager *pApp):Action(pApp)
{
}

void PasteAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Select paste point");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->ClearStatusBar();	
}

void PasteAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	if(pManager->GetClipboardCount()!=0)
	{
		ReadActionParameters();
		pOut->PrintMessage("Figure pasted");
		pManager->Paste(P1);
	}
	else
		pOut->PrintMessage("No figures have been Cut/Copied");
}