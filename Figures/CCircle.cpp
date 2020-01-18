#include "CCircle.h"
#include <cmath>

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Center = P1;
	PCircumfrence = P2;
	type="CIRCLE";
	radius=sqrt(pow((Center.x-PCircumfrence.x),2)+pow((Center.y-PCircumfrence.y),2));
	Valid=IsValid();
}
	
CCircle::CCircle(GfxInfo init):CFigure(init)
{
	Center.x = 555;
	PCircumfrence.x = 555;
	Center.y = 555;
	PCircumfrence.y = 555;
	radius=0;
	type="CIRCLE";
	Valid=1;
}

void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawCircle to draw a Circle on the screen	

	pOut->DrawCircle(Center, PCircumfrence, FigGfxInfo, Selected);
	
}

void CCircle::Resize(double Factor)
{
	radius*=Factor;
	PCircumfrence.x=Center.x+radius;
	PCircumfrence.y=Center.y+radius;
	Valid=IsValid();
}

void CCircle::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Selected Circle, ID: "+to_string(ID)+", Center:("+to_string(Center.x)+","+to_string(Center.y)+"), Radius: "+to_string(radius));
}

bool CCircle::IsPointInside(int x, int y)
{

	float newrad;

	newrad=sqrt(pow((x-Center.x),2)+pow((y-Center.y),2));

	if(newrad <= radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CCircle::Paste(Point p)
{

    int DiffX=PCircumfrence.x-Center.x;
	int DiffY=PCircumfrence.y-Center.y;
	Center.x=p.x;
	Center.y=p.y;
	PCircumfrence.x=DiffX+Center.x;
	PCircumfrence.y=DiffY+Center.y;
}


void CCircle::Copy(CFigure*&c)
{
c=new CCircle(Center,PCircumfrence,FigGfxInfo);
}

Point CCircle::GetPastePoint()
{
	return Center;
}

void CCircle::Save(ofstream &OutFile)
{
	OutFile<<type<<"\t"<<ID<<"\t"<<Center<<"\t"<<radius<<"\t"<<FigGfxInfo.DrawClr<<"\t";
	if(FigGfxInfo.isFilled) OutFile<<FigGfxInfo.FillClr<<endl;
	else OutFile<<"NO_FILL"<<endl;
}

void CCircle::Load(ifstream &Infile)
{
	string read;
	Infile>>ID>>Center>>radius>>FigGfxInfo.DrawClr>>read;
	PCircumfrence.x=Center.x+radius;
	PCircumfrence.y=Center.y;
	if(read=="NO_FILL")
	{
		FigGfxInfo.isFilled=0;
		return;
	}
	if(read=="BLACK") FigGfxInfo.FillClr=BLACK;
	else if(read=="WHITE") FigGfxInfo.FillClr=WHITE;
	else if(read=="BLUE") FigGfxInfo.FillClr=BLUE;
	else if(read=="GREEN") FigGfxInfo.FillClr=GREEN;
	else if(read=="RED")FigGfxInfo.FillClr=RED;
	FigGfxInfo.isFilled=1;
}

bool CCircle::IsValid()
{
	if(Center.y-radius<=UI.ToolBarHeight || Center.y+radius>(UI.height-UI.StatusBarHeight) || Center.x+radius>UI.width || Center.x-radius<0)
		return false;
	return true;
}