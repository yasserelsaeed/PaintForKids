#ifndef CLINE_H
#define CLINE_H

#include "CFigure.h"
class CLine : public CFigure
{
private:
	Point P1;	
	Point P2;
public:
	CLine(Point , Point, GfxInfo FigureGfxInfo );
	CLine(GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	virtual bool IsPointInside(int x , int y);
	virtual void PrintInfo(Output* pOut);
	virtual void Resize(double Factor);
	double getlength();
	virtual void Paste(Point );
	virtual void Copy(CFigure*&);
	virtual Point GetPastePoint();
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	bool IsValid();
};

#endif