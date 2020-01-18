#include "CTriangle.h"


CTriangle::CTriangle(Point P1, Point P2,Point P3, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
	Center.x=(Corner1.x+Corner2.x+Corner3.x)/3;
	Center.y=(Corner1.y+Corner2.y+Corner3.y)/3;
	type="TRIANG";
	Valid=IsValid();
}
	
CTriangle::CTriangle(GfxInfo init):CFigure(init)
{
	Corner1.x=555;
	Corner1.y=555;
	Corner2.x=555;
	Corner2.y=555;
	Corner3.x=555;
	Corner3.y=555;
	type="TRIANG";
	Valid=1;
}

void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawTriangle to draw a triangle on the screen
	
		pOut->DrawTriangle(Corner1,Corner2, Corner3, FigGfxInfo,Selected);
	
}

void CTriangle::Resize(double Factor)
{
	Corner1.x=Center.x+Factor*(Corner1.x-Center.x);
	Corner1.y=Center.y+Factor*(Corner1.y-Center.y);
	Corner2.x=Center.x+Factor*(Corner2.x-Center.x);
	Corner2.y=Center.y+Factor*(Corner2.y-Center.y);
	Corner3.x=Center.x+Factor*(Corner3.x-Center.x);
	Corner3.y=Center.y+Factor*(Corner3.y-Center.y);
	Valid=IsValid();
}

void CTriangle::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Selected Triangle, ID: "+to_string(ID)+", Corner1:("+to_string(Corner1.x)+","+to_string(Corner1.y)+"), Corner2:("+to_string(Corner2.x)+","+to_string(Corner2.y)+"), Corner3:("+to_string(Corner3.x)+","+to_string(Corner3.y)+")");
}

bool CTriangle::IsPointInside(int x,int y)
{
	int as_x = x-Corner1.x;
    int as_y = y-Corner1.y;

    bool s_ab = (Corner2.x-Corner1.x)*as_y-(Corner2.y-Corner1.y)*as_x > 0;

    if((Corner3.x-Corner1.x)*as_y-(Corner3.y-Corner1.y)*as_x > 0 == s_ab) return false;

    if((Corner3.x-Corner2.x)*(y-Corner2.y)-(Corner3.y-Corner2.y)*(x-Corner2.x) > 0 != s_ab) return false;

    return true;
}

void CTriangle:: Paste(Point p)
{
	 int diffx2=Corner2.x-Corner1.x;
	 int diffy2=Corner2.y-Corner1.y;
	 int diffx3=Corner3.x-Corner1.x;
	 int diffy3=Corner3.y-Corner1.y;
	 Corner1=p;
	 Corner2.x=p.x+diffx2;
     Corner2.y=p.y+diffy2;
	 Corner3.x=p.x+diffx3;
     Corner3.y=p.y+diffy3;
}

Point CTriangle::GetPastePoint()
{
	return Corner1;
}

void CTriangle::Copy(CFigure*&c)
{
	c=new CTriangle(Corner1,Corner2,Corner3,FigGfxInfo);
}

void CTriangle::Save(ofstream &OutFile)
{
	OutFile<<type<<"\t"<<ID<<"\t"<<Corner1<<"\t"<<Corner2<<"\t"<<Corner3<<"\t"<<FigGfxInfo.DrawClr<<"\t";
	if(FigGfxInfo.isFilled) OutFile<<FigGfxInfo.FillClr<<endl;
	else OutFile<<"NO_FILL"<<endl;
}

void CTriangle::Load(ifstream &Infile)
{
	string read;
	Infile>>ID>>Corner1>>Corner2>>Corner3>>FigGfxInfo.DrawClr>>read;
	Center.x=(Corner1.x+Corner2.x+Corner3.x)/3;
	Center.y=(Corner1.y+Corner2.y+Corner3.y)/3;
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

bool CTriangle::IsValid()
{
	if(Corner1.y<=UI.ToolBarHeight || Corner1.y>(UI.height-UI.StatusBarHeight) || Corner1.x>UI.width || Corner1.x<0 || Corner2.y<=UI.ToolBarHeight || Corner2.y>(UI.height-UI.StatusBarHeight) || Corner2.x>UI.width || Corner2.x<0 || Corner3.y<=UI.ToolBarHeight || Corner3.y>(UI.height-UI.StatusBarHeight) || Corner3.x>UI.width || Corner3.x<0)
		return false;
	return true;
}