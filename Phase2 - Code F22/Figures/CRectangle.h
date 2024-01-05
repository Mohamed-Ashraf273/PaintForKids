#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
public:
	CRectangle() {}
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	virtual bool IsInside(int a, int b);
	virtual void printtypeoffigureselected(Output* pout);
	virtual void movefigure(int a, int b, Output* pout);
	virtual void Save(ofstream& OutFile);
	
	virtual void Load(ifstream& Infile);
	
	virtual Point MakeCenter();//to save informtion abount figure
	virtual int figuretype();
	virtual ~CRectangle() {}

};

#endif