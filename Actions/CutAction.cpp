#include "CutAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

CutAction::CutAction(ApplicationManager * pApp):Action(pApp)
{}

void CutAction::ReadActionParameters() 
{	
	
}

void CutAction::Execute() 
{
	Output* pOut = pManager->GetOutput();
	if(pManager->GetSelectedCount()!=0)
	{
			pOut->PrintMessage("Figure has been cut");
				pManager->Cut();
	}
	else
		pOut->PrintMessage("No Figure Selected");
	
}
