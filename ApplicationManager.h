#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"

#include "Figures\CFigure.h"
#include "Figures\CCircle.h"
#include "Figures\CRectangle.h"
#include "Figures\CTriangle.h"
#include "Figures\CLine.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddCircAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\SelectAction.h"
#include "Actions\ChangeCDCAction.h"
#include "Actions\ChangeCFCAction.h"
#include "Actions\ResizeAction.h"
#include "Actions\CopyAction.h"
#include "Actions\CutAction.h"
#include "Actions\PasteAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\BringtoFrontAction.h"
#include "Actions\SendtoBackAction.h"
#include "Actions\SaveAction.h"
#include "Actions\LoadAction.h"
#include "Actions\SwitchDMAction.h"
#include "Actions\SwitchPMAction.h"
#include "Actions\ExitAction.h"
#include "Actions\PickColorAction.h"
#include "Actions\PickShapeAction.h"
#include "Actions\PickBothAction.h"
#include "Actions\RestartAction.h"
#include "operators.h"
//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	int SelectedCount;
	int ClipboardCount;
	CFigure* SelectedFig[MaxFigCount]; //Pointer to the selected figure
	CFigure* Clipboard[MaxFigCount];   //Pointer to the copied/cut figure

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
		
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window
	void SetSelectedFigure(CFigure *Selected);
	CFigure* GetSelectedFig();
	void ChangeCDrawingColor(color);
	void ChangeSDrawingColor(color);
	void ChangeCFillColor(color);
	void ChangeSFillColor(color);
	void MakeCopy(); 
	void Cut();  
	void Paste(Point);
	void ShiftAndDelete();  //delete selected figure and shift
	int GetSelectedCount();
	void ResizeFigures(double Factor);
	void SaveAll(ofstream& out);
	void LoadAll(ifstream& in);
	void ClearFigList();
	void switchPM();
	void switchDM();
	color GetRandomFillClr();
	string GetRandomShape();
	int GetNumberofFillClr(color);
	int GetNumberofShapes(string);
	int GetNumberofBoth(color,string);
	void CleanSelectedFig();
	bool IsCorrectFillClr(CFigure*,color);
	bool IsCorrectShape(CFigure*,string);
	bool IsCorrectBoth(CFigure*,color,string);
	int GetClipboardCount();
	void SendtoBack();
	void BringToFront();
	int GetFigCount();
};

#endif