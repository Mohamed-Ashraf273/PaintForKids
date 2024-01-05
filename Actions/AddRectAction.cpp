#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddRectAction::AddRectAction(ApplicationManager* pApp) :Action(pApp)
{
	CountC = 0;//count for color undo
	CountIn = 0;//count for point undo
	CountC2 = 0;//count for color redo
	CountIn2 = 0;
}

void AddRectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	if (pManager->IsAnyFigureIsSelected())
	{
		pManager->UnSelectAll();
	}
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{
		P1 = pManager->GetRecordControl()->GetActList()[pManager->GetPcount()].p;//error is here as it must start from 0 then increase to 1, here its start from 2
		P2 = pManager->GetRecordControl()->GetActList()[pManager->GetPcount()].p1;
		pManager->setPcount((pManager->GetPcount()) + 1);
	}
	else
	{
		pOut->PrintMessage("New Rectangle: Click at first corner");

		//Read 1st corner and store in point P1
		pIn->GetPointClicked(P1.x, P1.y);

		pOut->PrintMessage("New Rectangle: Click at second corner");

		//Read 2nd corner and store in point P2
		pIn->GetPointClicked(P2.x, P2.y);
	}


	RectGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddRectAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	//This action needs to read some parameters first
	ReadActionParameters();
	pManager->AddAction(this);
	this->SetAct(true);
	CRectangle* R = new CRectangle(P1, P2, RectGfxInfo);
	pManager->IfNotUndo();

	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{
		pManager->setlastact(this);
		pManager->setlastfig(R);
		pManager->getundoedactionandfig();
		pManager->getredoedactionandfig(this, R);
		pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cfill = R->GetFillColor();
		pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cdraw = R->GetDrawColor();
		pManager->setredoinfo((pManager->getredoinfo()) + 1);
	}
	if (pManager->isclicked())
	{
		pManager->GetRecordControl()->GetActList()[pManager->GetRecordControl()->getActCount()].p = P1;
		pManager->GetRecordControl()->GetActList()[pManager->GetRecordControl()->getActCount()].p1 = P2;
		Action* pAct = new AddRectAction(pManager);
		pManager->GetRecordControl()->AddAction(pAct);
		pManager->GetRecordControl()->Execute();
	}
	
	//Create a rectangle with the parameters read from the user

	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
	AddArrPoint(R->MakeCenter());//add point
	AddArrColor(R->GetColorIn());//add color
	pManager->AddFigForUndo(R);
}
void AddRectAction::UndoFig(CFigure* F)
{
	pManager->UnSelectAll();
	F->DeleteFi();
	F->SetIsDeleted(true);

	pManager->UpdateInterface();
	pManager->DeleteFigure(F);//to delete this figure
	CountIn--;//to decrease count point
	CountC--;//to decrease count Color

}
void AddRectAction::RedoFig(CFigure* F)
{
	pManager->UnSelectAll();
	if(CountC2>0)
	{ 
	F->ChngDrawClr(ArrColor2[CountC2 - 1].DrawClr);
	F->ChngFillClr(ArrColor2[CountC2 - 1].FillClr);
	pManager->AddFigure(F);//Add this figure after delete it because undo
	CountIn2--;//to decrease count point
	CountC2--;//to decrease count Color
	}

}