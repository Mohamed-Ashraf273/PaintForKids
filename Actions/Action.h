
#ifndef ACTION_H
#define ACTION_H
#include "..\defs.h"
#include "..\GUI\Output.h"
#include "..\DefS.h"

class ApplicationManager; //forward class declaration
class CFigure;

//Base class for all possible actions
class Action
{
protected:
	ApplicationManager* pManager;	//Actions needs AppMngr to do their job
	bool ButAct;//to know the action i want to put in arryAct
	int CountIn;//count for point redo
	int CountC;//count for color undo
	int CountC2;//count for color redo
	int CountIn2;//count for point redo
//Actual number of figures

	GfxInfo ArrColor[5];//for undo
	GfxInfo ArrColor2[5];//for redo
	Point ArrPoint[5];//for undo
	Point ArrPoint2[5];//for redo


public:
	Action(){}
	Action(ApplicationManager* pApp);// constructor
	void SetAct(bool b);

	bool getAct();//to check action
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() = 0;

	//Execute action (code depends on action type)
	virtual void Execute() = 0;
	virtual void UndoFig(CFigure* F) = 0;//vietual to undo figures
	void AddArrPoint(Point P);
	void AddArrColor(GfxInfo c);
	void AddArrPointRedo(Point P);
	void AddArrColorRedo(GfxInfo c);
	virtual void RedoFig(CFigure* F1) = 0;//virtual to make redo fig
};
#endif

