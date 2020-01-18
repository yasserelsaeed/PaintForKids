#pragma once
#include "CFigure.h"

class CTriangle : public CFigure
{ 
private:
	Point Corner1;	
	Point Corner2;
	Point Corner3;
public:
	CTriangle(Point , Point, Point, GfxInfo FigureGfxInfo );
	CTriangle(GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	virtual bool IsPointInside(int x,int y);
	virtual void PrintInfo(Output* pOut);
	virtual void Resize(double Factor);
	virtual void Paste(Point );
	virtual void Copy(CFigure*&);
	virtual Point GetPastePoint();
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	bool IsValid();
};




