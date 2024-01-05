#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"

//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	color draw, fill;
	bool filled;
	bool deleted;/// Add more parameters if needed.
	/// Add more parameters if needed.

public:
	CFigure(){}
	GfxInfo GetColorIn();
	CFigure(GfxInfo FigureGfxInfo);
	virtual void movefigure(int a, int b,Output* pout)=0;
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	virtual bool IsInside(int a, int b)=0;
	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	virtual void printtypeoffigureselected(Output* pout) = 0;
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	color GetDrawColor();//get the drawing color
	color CFigure::GetFillColor();
	bool GetFillingStatus();
	void DeleteFi();//to delete fig
	virtual Point MakeCenter() = 0;//to get senter of anay array
	void SetIsDeleted(bool b);//to know if this figure is deleted or not
	bool GetIsDeleted();
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	
	virtual ~CFigure(){}

	virtual void Save(ofstream &OutFile)=0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file
	void SetGfxInfo(GfxInfo& PickGfxInfo);
	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
	color converttoColor(string s);
	string converttostring(color c);
	virtual int figuretype() = 0;
	

};
#endif