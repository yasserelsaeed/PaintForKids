#include "SaveAction.h"



#include "..\Figures\CLine.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SaveAction::SaveAction(ApplicationManager * pApp):Action(pApp){}

void SaveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Enter file name to save to:");
	filename=pIn->GetSrting(pOut)+".txt";
	pOut->ClearStatusBar();
}

void SaveAction::Execute()
{
	Output* pOut=pManager->GetOutput();
	ReadActionParameters();
	ofstream fout(filename,ios::out);
	pManager->SaveAll(fout);
	fout.close();
	pOut->PrintMessage("Save succesfull to "+filename);
}