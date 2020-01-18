#include "LoadAction.h"



#include "..\Figures\CLine.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

LoadAction::LoadAction(ApplicationManager * pApp):Action(pApp){}

void LoadAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Enter file name to load from:");
	filename=pIn->GetSrting(pOut)+".txt";

	pOut->ClearStatusBar();
}

void LoadAction::Execute()
{
	Output* pOut=pManager->GetOutput();

	ReadActionParameters();
	ifstream fin(filename,ios::in);
	if(!fin.is_open())
	{
		pOut->PrintMessage("No graph with this file name, loading failed.");
	
	}
	else
	{
		pManager->LoadAll(fin);
		fin.close();
		pOut->PrintMessage("Loading successful from "+filename);
	}
	
}