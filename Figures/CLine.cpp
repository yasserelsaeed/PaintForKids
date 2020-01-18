#include "CLine.h"

CLine::CLine(Point X1, Point X2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	P1 = X1;
	P2 = X2;
	Center.x=(P1.x+P2.x)/2;
	Center.y=(P1.y+P2.y)/2;
	type="LINE";
	Valid=IsValid();
}
	
CLine::CLine(GfxInfo init):CFigure(init)
{
	P1.x = 555;
	P2.x = 555;
	P1.y = 555;
	P2.y = 555;
	type="LINE";
	Valid=1;
}

void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawLine to draw a line on the screen	
	
		pOut->DrawLine(P1, P2, FigGfxInfo, Selected);
	
}

void CLine::Resize(double Factor)
{
	P1.x=Center.x+Factor*(P1.x-Center.x);
	P1.y=Center.y+Factor*(P1.y-Center.y);
	P2.x=Center.x+Factor*(P2.x-Center.x);
	P2.y=Center.y+Factor*(P2.y-Center.y);
	Valid=IsValid();
}

void CLine::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Selected Line, ID: "+to_string(ID)+", Point1:("+to_string(P1.x)+","+to_string(P1.y)+"), Point2:("+to_string(P2.x)+","+to_string(P2.y)+")"+", Length:"+to_string(getlength()));
}

double CLine::getlength()
{
	return sqrt((P1.x-P2.x)*(P1.x-P2.x)+(P1.y-P2.y)*(P1.y-P2.y));
}

bool CLine::IsPointInside(int x , int y)
{
	
	 int maxx,minx,maxy,miny;
 if (P1.x>P2.x){maxx=P1.x;minx=P2.x;}
 else {maxx=P2.x;minx=P1.x;}
  if (P1.y>P2.y){maxy=P1.y;miny=P2.y;}
 else {maxy=P2.y;miny=P1.y;}

	if(P1.x!=P2.x && P1.y!=P2.y)
{float m=float(P1.y-P2.y)/(P1.x-P2.x);
 int c=(P1.y)-(m*P1.x);


       if(int(y-(m*x))<=c+5 && int(y-(m*x))>=c-5 && x<=maxx && x>=minx && y>=miny && y<=maxy){return true;}
 else {return false;}

}
	if(P1.x==P2.x) {if(y<=maxy && y>=miny && x>P1.x-4 && x<P1.x+4){return true;}
	else return false;
	}

if(P1.y==P2.y) {if(x<=maxx && x>=minx && y>P1.y-4 && y<P1.y+4){return true;}
	else return false;
	}
}

void CLine::Paste(Point p)
 {
	 int diffx=P2.x-P1.x;
	 int diffy=P2.y-P1.y;
	 P1=p;
	 P2.x=p.x+diffx;
     P2.y=p.y+diffy;
 }
void CLine::Copy(CFigure*&c)
{
	c=new CLine(P1,P2,FigGfxInfo);
}

Point CLine::GetPastePoint()
{
	return P1;
}

void CLine::Save(ofstream &OutFile)
{
	OutFile<<type<<"\t"<<ID<<"\t"<<P1<<"\t"<<P2<<"\t"<<FigGfxInfo.DrawClr<<endl;
}

void CLine::Load(ifstream &Infile)
{
	Infile>>ID>>P1>>P2>>FigGfxInfo.DrawClr;
	Center.x=(P1.x+P2.x)/2;
	Center.y=(P1.y+P2.y)/2;
}

bool CLine::IsValid()
{
	if(P1.y<=UI.ToolBarHeight || P1.y>(UI.height-UI.StatusBarHeight) || P1.x>UI.width || P1.x<0 || P2.y<=UI.ToolBarHeight || P2.y>(UI.height-UI.StatusBarHeight) || P2.x>UI.width || P2.x<0)
		return false;
	return true;
}