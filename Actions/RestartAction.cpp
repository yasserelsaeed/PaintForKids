#include "RestartAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

RestartAction::RestartAction(ApplicationManager * pApp):Action(pApp)
{}

void RestartAction::ReadActionParameters() 
{	
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Restarting Play Mode");
}

void RestartAction::Execute() 
{
    Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	ifstream fin("tempsave.txt",ios::in);
	pManager->LoadAll(fin);
	fin.close();
}
