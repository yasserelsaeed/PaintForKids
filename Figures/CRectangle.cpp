#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Center.x=(Corner1.x+Corner2.x)/2;
	Center.y=(Corner1.y+Corner2.y)/2;
	type="RECT";
	Valid=IsValid();
}
	
int CRectangle:: getlength()
{
	int l=Corner1.y-Corner2.y;
	if(l<0) l=-l;
	return l;
}

int CRectangle:: getwidth()
{
	int w=Corner1.x-Corner2.x;
	if(w<0) w=-w;
	return w;
}


CRectangle::CRectangle(GfxInfo init):CFigure(init)
{
	Corner1.x = 555;
	Corner2.x = 555;
	Corner1.y = 555;
	Corner2.y = 555;
	type="RECT";
	Valid=1;
}

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	
		pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
	

}

void CRectangle::Resize(double Factor)
{
	Corner1.x=Center.x+Factor*(Corner1.x-Center.x);
	Corner1.y=Center.y+Factor*(Corner1.y-Center.y);
	Corner2.x=Center.x+Factor*(Corner2.x-Center.x);
	Corner2.y=Center.y+Factor*(Corner2.y-Center.y);
	Valid=IsValid();
}

void CRectangle::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Selected Rectangle, ID: "+to_string(ID)+", Width:"+to_string(getwidth())+", Height:"+to_string(getlength()));
}

bool CRectangle::IsPointInside(int x, int y) {
 bool a=false;bool b=false;
	if(Corner1.x>Corner2.x){
		if (x>=Corner2.x && x<=Corner1.x){a=true;}}
	else {if(x<=Corner2.x && x>=Corner1.x){a=true;}}

	if(Corner1.y>Corner2.y){
		if (y>=Corner2.y && y<=Corner1.y){b=true;}}
	else {if(y<=Corner2.y && y>=Corner1.y){b=true;}}

	if(a==true && b==true){return true;}
	else {return false;}
}

 void CRectangle::Paste(Point p)
 {
	 int diffx=Corner2.x-Corner1.x;
	 int diffy=Corner2.y-Corner1.y;

	 Corner1=p;
	 Corner2.x=p.x+diffx;
     Corner2.y=p.y+diffy;
 }

 Point CRectangle::GetPastePoint()
 {
	 return Corner1;
 }

 void CRectangle::Copy(CFigure*&c){

	 c=new CRectangle(Corner1,Corner2,FigGfxInfo);
}

 void CRectangle::Save(ofstream &OutFile)
{
	OutFile<<type<<"\t"<<ID<<"\t"<<Corner1<<"\t"<<Corner2<<"\t"<<FigGfxInfo.DrawClr<<"\t";
	if(FigGfxInfo.isFilled) OutFile<<FigGfxInfo.FillClr<<endl;
	else OutFile<<"NO_FILL"<<endl;
}

void CRectangle::Load(ifstream &Infile)
{
	string read;
	Infile>>ID>>Corner1>>Corner2>>FigGfxInfo.DrawClr>>read;
	Center.x=(Corner1.x+Corner2.x)/2;
	Center.y=(Corner1.y+Corner2.y)/2;
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

bool CRectangle::IsValid()
{
	if(Corner1.y<=UI.ToolBarHeight || Corner1.y>(UI.height-UI.StatusBarHeight) || Corner1.x>UI.width || Corner1.x<0 || Corner2.y<=UI.ToolBarHeight || Corner2.y>(UI.height-UI.StatusBarHeight) || Corner2.x>UI.width || Corner2.x<0)
		return false;
	return true;
}
