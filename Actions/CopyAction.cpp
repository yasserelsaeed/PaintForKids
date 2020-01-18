#include "CopyAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

CopyAction::CopyAction(ApplicationManager * pApp):Action(pApp)
{}

void CopyAction::ReadActionParameters() 
{	
	
}

void CopyAction::Execute() 
{
	Output* pOut = pManager->GetOutput();
	if(pManager->GetSelectedCount()!=0)
	{
		pOut->PrintMessage("Figure has been Copied");
		pManager->MakeCopy();
	}
	else
		pOut->PrintMessage("No Figure Selected");
	
}
