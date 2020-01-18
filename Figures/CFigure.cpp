#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)//FOR NEW ADDED FIGS
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	ID=nextID++;
}

int CFigure:: nextID=0;

void CFigure::setnexID(int num){nextID=num;}

void CFigure::SetSelected(bool s)
{	Selected = s; }

color CFigure::GetFillClr()
{
	if(FigGfxInfo.isFilled == true)
	{
		return FigGfxInfo.FillClr;
	}
	else
	{
		return MAGENTA;
	}
}

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	
	FigGfxInfo.DrawClr = Dclr;
}

void CFigure::ChngFillClr(color Fclr)
{	
	if(FigGfxInfo.isFilled && FigGfxInfo.FillClr==Fclr)
	{
		FigGfxInfo.isFilled=0;
	}
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = Fclr; 
	}
}

int CFigure::GetID()
{
	return ID;
}

Point CFigure::GetCenter()
{
	return Center;
}

void CFigure::tempSave()
{
	tempfilled=FigGfxInfo.FillClr;
	tempborder=FigGfxInfo.DrawClr;
}

void CFigure:: returntempfilled()
{
	 FigGfxInfo.FillClr=tempfilled;
}
void CFigure::returntempborder()
{
	FigGfxInfo.DrawClr=tempborder;
}

string CFigure::GetType()
{
	return type;
}