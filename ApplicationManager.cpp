#include "ApplicationManager.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
	SelectedCount=0;
	ClipboardCount=0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
	{
		FigList[i] = NULL;
		SelectedFig[i]=NULL;
		Clipboard[i]=NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;
		case DRAW_CIRC:
			pAct= new AddCircAction(this);
            break;
		case DRAW_LINE:
			pAct= new AddLineAction(this);
            break;
		case DRAW_TRI:
			pAct= new AddTriAction(this);
			break;
		case SELECT:
			pAct= new SelectAction(this);
			break;
		case CHNG_C_DRAW_CLR:
			pAct= new ChangeCDCAction(this);
			break;
		case CHNG_C_FILL_CLR:
			pAct= new ChangeCFCAction(this);
			break;
		case RESIZE:
			pAct=new ResizeAction(this);
			break;
		case COPY:
			pAct= new CopyAction(this);
			break;
		case CUT:
			pAct= new CutAction(this);
			break;
		case PASTE:
			pAct= new PasteAction(this);
			break;
		case DEL:
			pAct=new DeleteAction(this);
			break;
		case  TO_PLAY:
			pAct=new SwitchPM(this);
			break;
		case TO_DRAW:
			pAct=new SwitchDM(this);
			break;
		case EXIT:
			pAct=new ExitAction(this);
			break;
		case SAVE:
			pAct= new SaveAction(this);
			break;
		case LOAD:
			pAct= new LoadAction(this);
			break;

		case BRING_BACK:
			pAct=new SendtoBackAction(this);
			break;

		case SEND_FRONT:
			pAct=new BringtoFrontAction(this);
			break;

		case PICK_COLOUR:
			pAct=new PickColorAction(this);
			break;
		case PICK_SHAPE:
			pAct=new PickShapeAction(this);
			break;
		case PICK_BOTH:
			pAct=new PickBothAction(this);
			break;
		case RESTART:
			pAct=new RestartAction(this);
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
	{
		FigList[FigCount] = pFig;
		FigCount++;
	}

}

int ApplicationManager::GetFigCount() {return FigCount;}

void ApplicationManager:: ShiftAndDelete()
{
	for(int k=0;k<SelectedCount;k++)
	{
	   for(int i=0;i<FigCount;i++)
	{
		 if(SelectedFig[k]==FigList[i])	
		{
			FigList[i]=NULL;delete SelectedFig[k];SelectedFig[k]=NULL;
			for(int j=i;j<FigCount-1;j++)
			{
				FigList[j]=FigList[j+1];
			}
			 FigList[FigCount-1]=NULL;
			 FigCount--;
		}
	}
	}
	for(int i=0;i<SelectedCount;i++)
		SelectedFig[i]=NULL;
	SelectedCount=0;
}

void ApplicationManager::BringToFront()
{

	for(int u=SelectedCount-1;u>-1;u--)
	  {
	   
		  for(int i=0;i<FigCount;i++)
	    {
			if(SelectedFig[u]==FigList[i])
			{
				FigList[FigCount++]=FigList[i];
				FigList[i]=NULL;SelectedFig[u]=NULL;
				 for(int j=i;j<FigCount-1;j++)
			 {
					  FigList[j]=FigList[j+1];
			 }
				 FigList[FigCount-1]=NULL;FigCount--;
				 FigList[FigCount-1]->SetSelected(false);
				 
			}
	  }
     
   }
	SelectedCount=0;
	
}

void ApplicationManager::SendtoBack()
{
		for(int u=SelectedCount-1;u>-1;u--)
	  {
		for(int i=0;i<FigCount;i++)
		{
			if(SelectedFig[u]==FigList[i])
			{
				
				FigList[FigCount++]=FigList[i];
				FigList[i]=NULL;SelectedFig[u]=NULL;
				 for(int j=i;j>0;j--)
			 {
					  FigList[j]=FigList[j-1];
			 }
				 FigList[0] = FigList[FigCount-1];
				 FigList[FigCount--]=NULL;
				 FigList[0] ->SetSelected(false);
				
			}
		}

		}
		 SelectedCount=0;
}

	
	


void ApplicationManager::MakeCopy()
{
	for(int i=0;i<SelectedCount;i++)
	{
		SelectedFig[i]->Copy(Clipboard[i]);
	}
	ClipboardCount=SelectedCount;
	Clipboard[0]->setnexID(Clipboard[0]->GetID());
}

void ApplicationManager::Cut()
{
	for(int i=0;i<SelectedCount;i++)
	{
		SelectedFig[i]->Copy(Clipboard[i]);	
	}
	ClipboardCount=SelectedCount;
	ShiftAndDelete();
}

void  ApplicationManager::Paste(Point X)
{ 
	bool Valid=true;
	if(ClipboardCount!=0)
	{
		Point Y;
		Point Z=Clipboard[0]->GetPastePoint();
		Point W;
	for(int i=0;i<ClipboardCount;i++)
	{
		Y=Clipboard[i]->GetPastePoint();
		W.x=X.x+(Y.x-Z.x);
		W.y=X.y+(Y.y-Z.y);
		Clipboard[i]->Paste(W);
		if(!Clipboard[i]->IsValid())
			Valid=false;
	}
	}
	if(ClipboardCount!=0 && Valid)
	{
		Point Y;
		Point Z=Clipboard[0]->GetPastePoint();
		Point W;
	for(int i=0;i<ClipboardCount;i++)
	{
		Y=Clipboard[i]->GetPastePoint();
		W.x=X.x+(Y.x-Z.x);
		W.y=X.y+(Y.y-Z.y);
		Clipboard[i]->Paste(W);
		CFigure*clone;
		Clipboard[i]->Copy(clone);
		AddFigure(clone);
	}
	}
	else
		pOut->PrintMessage("Invalid Paste point");
}

int ApplicationManager::GetClipboardCount()
{
	return ClipboardCount;
}
	

////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	
	
	for(int i=FigCount-1;i>=0;i--)
	{
		if(FigList[i]->IsPointInside(x,y))
		{
			return FigList[i];
		}
	}

	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.
	return NULL;
}

CFigure* ApplicationManager::GetSelectedFig()
{
	return SelectedFig[0];
}

void ApplicationManager::ResizeFigures(double Factor)
{
	for(int i=0;i<SelectedCount;i++)
	{
		SelectedFig[i]->Resize(Factor);
		if(SelectedFig[i]->IsValid()==false)
		{
			pOut->PrintMessage("Invalid resize factor");
			for(int j=0;j<=i;j++)
			{
				SelectedFig[i]->Resize(1/Factor);
			}
			break;
		}
	}
}



void ApplicationManager::SaveAll(ofstream& out)
{
	out<<pOut->getCrntDrawColor()<<"\t"<<pOut->getCrntFillColor()<<endl;
	out<<FigCount<<endl;
	for(int i=0;i<FigCount;i++)
	{
		FigList[i]->Save(out);
	}
}

void ApplicationManager::LoadAll(ifstream& in)
{
	ClearFigList();
	int count;
	color draw,fill;
	in>>draw>>fill;
	ChangeCDrawingColor(draw);
	ChangeCFillColor(fill);
	if(fill==INDIAN) UI.FillFigures=0;
	in>>count;
	CFigure* LoadedFig;
	GfxInfo dummy;
		dummy.BorderWdth=pOut->getCrntPenWidth();
		dummy.DrawClr=pOut->getCrntDrawColor();
		dummy.FillClr=pOut->getCrntFillColor();
		dummy.isFilled=0;
	for(int i=0;i<count;i++)
	{
		string type;
		in>>type;
		if(type=="CIRCLE")
		{
			LoadedFig= new CCircle(dummy);
			LoadedFig->Load(in);
		}
		else if(type=="RECT")
		{
			LoadedFig= new CRectangle(dummy);
			LoadedFig->Load(in);
		}
		else if(type=="TRIANG")
		{
			LoadedFig= new CTriangle(dummy);
			LoadedFig->Load(in);
		}
	    else if(type=="LINE")
		{
			LoadedFig= new CLine(dummy);
			LoadedFig->Load(in);
		}
		AddFigure(LoadedFig);
	}
	LoadedFig->setnexID(FigList[FigCount-1]->GetID()+1);
}

void ApplicationManager::ClearFigList()
{
	for(int i=0;i<FigCount;i++)
	{
		delete FigList[i];
		FigList[i]=NULL;
	}
	FigCount=0;
}

void ApplicationManager::SetSelectedFigure(CFigure *Selected) 
{
	SelectedFig[SelectedCount]=Selected;
	if(SelectedFig[SelectedCount]->IsSelected()==true)
	{
		for(int i=0;i<SelectedCount;i++)
		{
			if(SelectedFig[i]->GetID()==SelectedFig[SelectedCount]->GetID())
			{
				SelectedFig[i]->SetSelected(false);
				if(SelectedCount-1==0) pOut->PrintMessage("Figure deselected. No figures are currently selected.");
				else if (SelectedCount-1==1) pOut->PrintMessage("Figure deselected. There is now 1 figure selected.");
				else pOut->PrintMessage("Figure deselected. There are now "+to_string(SelectedCount-1)+" figures selected.");
				SelectedFig[i]=SelectedFig[SelectedCount-1];
				SelectedFig[SelectedCount-1]=NULL;
				SelectedFig[SelectedCount]=NULL;
				SelectedCount--;
				break;
			}
		}
	}
	else if(SelectedFig!=NULL)
	{
		SelectedFig[SelectedCount]->SetSelected(true);
		SelectedFig[SelectedCount]->PrintInfo(pOut);
		SelectedCount++;
	}
}

int ApplicationManager::GetSelectedCount()
{
	return SelectedCount;
}

void ApplicationManager::ChangeCDrawingColor(color SelectedColor)
{
	pOut->changeCrntDrawColor(SelectedColor);
}

void ApplicationManager::ChangeSDrawingColor(color SelectedColor)
{
	for(int i=0;i<SelectedCount;i++)
	{
		SelectedFig[i]->ChngDrawClr(SelectedColor);
	}
}

void ApplicationManager::ChangeCFillColor(color SelectedColor)
{
	if(SelectedColor==UI.FillColor)
	{
		UI.FillFigures=0;
		UI.FillColor=INDIAN;
	}
	else
	{
		UI.FillFigures=1;
		pOut->changeCrntFillColor(SelectedColor);
	}
}

void ApplicationManager::ChangeSFillColor(color SelectedColor)
{
	for(int i=0;i<SelectedCount;i++)
	{
		SelectedFig[i]->ChngFillClr(SelectedColor);
	}
}

color ApplicationManager::GetRandomFillClr()
{
	if(FigCount!=0)
	{
		int x=rand() %FigCount;
		if(FigList[x]->GetType()=="LINE") return MAGENTA;
		return FigList[x]->GetFillClr();
	}
	else
		
	      return INDIAN;
}

string ApplicationManager::GetRandomShape()
{
	if(FigCount!=0)
	{
		int x=rand() %FigCount;
		return FigList[x]->GetType();
	}
	else
	
	  return "NULL";
	
}


int ApplicationManager::GetNumberofFillClr(color fill)
{
	int n=0;
	for(int i=0;i<FigCount;i++)
	{
		if(FigList[i]->GetFillClr()==fill)
			n++;
	}
	return n;
}

int ApplicationManager::GetNumberofBoth(color fill,string type)
{
	int n=0;
	for(int i=0;i<FigCount;i++)
	{
		if(FigList[i]->GetFillClr()==fill && FigList[i]->GetType()==type)
			n++;
	}
	return n;
}

int ApplicationManager::GetNumberofShapes(string type)
{
	int n=0;
	for(int i=0;i<FigCount;i++)
	{
		if(FigList[i]->GetType()==type)
			n++;
	}
	return n;
}

bool ApplicationManager::IsCorrectFillClr(CFigure* Selected, color fill)
{
	if(Selected->GetFillClr()==fill)
	{
		SelectedFig[0]=Selected;
		SelectedCount++;
		ShiftAndDelete();
		return true;
	}
	else
	{
		SelectedFig[0]=Selected;
		SelectedCount++;
		ShiftAndDelete();
		return false;
	}
}

bool ApplicationManager::IsCorrectShape(CFigure* Selected, string type)
{
	if(Selected->GetType()==type)
	{
		SelectedFig[0]=Selected;
		SelectedCount++;
		ShiftAndDelete();
		return true;
	}
	else
	{
		SelectedFig[0]=Selected;
		SelectedCount++;
		ShiftAndDelete();
		return false;
	}
}

bool ApplicationManager::IsCorrectBoth(CFigure* Selected,color fill, string type)
{
	if(Selected->GetType()==type && Selected->GetFillClr()==fill)
	{
		SelectedFig[0]=Selected;
		SelectedCount++;
		ShiftAndDelete();
		return true;
	}
	else
	{
		SelectedFig[0]=Selected;
		SelectedCount++;
		ShiftAndDelete();
		return false;
	}
}


void ApplicationManager::CleanSelectedFig()
{
	for(int i=0;i<SelectedCount;i++)
	{
		SelectedFig[i]->SetSelected(false);
		SelectedFig[i]=NULL;
	}
	SelectedCount=0;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }



void ApplicationManager:: switchPM()
{
	for(int i=0; i<FigCount; i++)
		FigList[i]->tempSave();
}



void ApplicationManager:: switchDM()
{
	for(int i=0; i<FigCount; i++)
		{
			FigList[i]->returntempborder();
			FigList[i]->returntempfilled();
	    }
}

////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{

	for(int i=0; i<SelectedCount; i++)
		{
			SelectedFig[i]=NULL;
		}


	for(int i=0; i<FigCount; i++)
	{
		delete FigList[i];
		FigList[i]=NULL;
	}

	
	for(int i=0; i<ClipboardCount; i++)
	{
		delete Clipboard[i];
		 Clipboard[i]=NULL;
	}

	delete pIn;
	delete pOut;
	
	
	

}