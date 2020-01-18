#ifndef CCIRC_H
#define CCIRC_H

#include "CFigure.h"
class CCircle : public CFigure
{
private:
	float radius;
	Point PCircumfrence;
public:
	CCircle(Point , Point, GfxInfo FigureGfxInfo );
	CCircle(GfxInfo FigureGfxInfo );
	virtual bool IsPointInside(int x, int y);
	virtual void Draw(Output* pOut) const;
	virtual void PrintInfo(Output* pOut);
	virtual void Resize(double Factor);
	virtual void Paste(Point );
	virtual void Copy(CFigure*&);
	virtual Point GetPastePoint();
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	bool IsValid();
};

#endif