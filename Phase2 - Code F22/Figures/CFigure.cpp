#include "CFigure.h"
#include<fstream>

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	//FigureGfxInfo.FillClr = LIGHTGOLDENRODYELLOW;
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	deleted = false;

}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}
color CFigure::GetDrawColor()
{
	return FigGfxInfo.DrawClr;
}
color CFigure::GetFillColor()
{
	return FigGfxInfo.FillClr;
}
bool CFigure::GetFillingStatus()
{
	return FigGfxInfo.isFilled;
}

void CFigure::SetGfxInfo(GfxInfo& PickGfxInfo)
{
	PickGfxInfo.isFilled = filled;
	PickGfxInfo.FillClr =fill;
	PickGfxInfo.DrawClr = draw;
}
void CFigure::SetIsDeleted(bool b)
{
	deleted = b;
}
void CFigure::DeleteFi()//to draw first the figure backgroubd then remove from array
{
	this->ChngDrawClr(UI.BkGrndColor);
	this->ChngFillClr(UI.BkGrndColor);

}
bool CFigure::GetIsDeleted()
{
	return deleted;
}
GfxInfo CFigure::GetColorIn()
{
	return FigGfxInfo;
}

color CFigure::converttoColor(string s)
{
	if (s == "BLACK")
		return BLACK;
	if (s == "BLUE")
		return BLUE;
	if (s == "ORANGE")
		return ORANGE;
	if (s == "RED")
		return RED;
	if (s == "YELLOW")
		return YELLOW;
	if (s == "GREEN")
		return GREEN;
	if (s == "NO_FILL")
		return UI.BkGrndColor;
}
string CFigure::converttostring(color c)
{

	if (c == BLACK) return "BLACK";
	else if (c == ORANGE) return "ORANGE";
	else if (c == BLUE) return "BLUE";
	else if (c == RED) return "RED";
	else if (c == YELLOW) return "YELLOW";
	else if (c == GREEN) return "GREEN";
	else if (c == UI.BkGrndColor) return "NO_FILL";


}

