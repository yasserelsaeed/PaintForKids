#include "SendtoBackAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"



SendtoBackAction::SendtoBackAction(ApplicationManager * pApp):Action(pApp)
{}

void SendtoBackAction::ReadActionParameters() 
{

	
}

void SendtoBackAction::Execute() 
{	
	Output* pOut = pManager->GetOutput();
	if(pManager->GetSelectedCount()!=0){
	pManager->SendtoBack();
	pOut->PrintMessage("Sent to Back");}
	else pOut->PrintMessage("No Figure Selected");

}

