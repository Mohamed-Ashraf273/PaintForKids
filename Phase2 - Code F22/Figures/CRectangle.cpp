#include "CRectangle.h"
#include<fstream>
#include<iostream>
#include"CFigure.h"
CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}
bool CRectangle::IsInside(int a, int b)
{
	if (FigGfxInfo.DrawClr == UI.BkGrndColor)
	{//check figure deleted
		return false;
	}
	if ((a >= Corner1.x && a <= Corner2.x) && (b >= Corner1.y && b <= Corner2.y))
	{
		return true;
	}
	return false;
}
void CRectangle::printtypeoffigureselected(Output* pout)
{
	pout->PrintMessage("you select a rectangle");
}
void CRectangle::movefigure(int a, int b, Output* pout)
{
	float dy, dx;
	dy= (Corner2.y - Corner1.y) / 2;
	dx= (Corner2.x - Corner1.x) / 2;
	Corner1.x = a - dx;
	Corner1.y = b - dy;
	Corner2.x = a + dx;
	Corner2.y = b + dy;
	pout->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);

}


void CRectangle::Save(ofstream& OutFile)
{
	
	
	OutFile << "RECT" <<"\t"<<ID<<"\t"<< Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t" << this->converttostring(UI.DrawColor) << "\t" << this->converttostring(CFigure::GetFillColor());
	
}



void CRectangle::Load(ifstream& Infile)
{
	string s;
	Infile >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y;
	Infile >> s;
	
	FigGfxInfo.DrawClr =this->converttoColor(s);

	Infile >> s;
	if (s == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = this->converttoColor(s);
	}


	Selected = false;

}


Point CRectangle::MakeCenter()
{
	Point P;
	P.x = (Corner1.x + Corner2.x) / 2;
	P.y = (Corner1.y + Corner2.y) / 2;
	return P;
}
int CRectangle::figuretype()
{
	return 3;
}