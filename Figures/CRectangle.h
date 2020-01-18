#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"
class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
public:
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	CRectangle(GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	virtual bool IsPointInside(int x , int y);
	virtual void PrintInfo(Output* pOut);
	virtual void Resize(double Facotr);
	virtual void Paste(Point );
	virtual void Copy(CFigure*&);
	int getlength();
	int getwidth();
	virtual Point GetPastePoint();
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	bool IsValid();
};

#endif