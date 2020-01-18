#include "Output.h"
#include <cmath>

Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1363;
	UI.height = 650;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 75;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = INDIAN;	//Filling color
	UI.MsgColor = BLACK;		//Messages color
	UI.BkGrndColor = WHEAT;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = SEAGREEN;
	UI.PenWidth = 3;	//width of the figures frames
	UI.FillFigures=0;

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor,1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

void Output:: ClearToolBar() const
{
	pWind->SetPen(UI.BkGrndColor, 2);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0,0,UI.width,UI.ToolBarHeight+1);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;
	ClearToolBar();

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_PALETTE] = "images\\MenuItemsd\\Menu_Palette.jpg";
	MenuItemImages[ITM_RECT] = "images\\MenuItemsd\\Menu_Rect.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItemsd\\Menu_Circ.jpg";
	MenuItemImages[ITM_TRI] = "images\\MenuItemsd\\Menu_Tri.jpg";
	MenuItemImages[ITM_LINE] = "images\\MenuItemsd\\Menu_Line.jpg";
	MenuItemImages[ITM_CHANGECDC] = "images\\MenuItemsd\\drawcolor.jpg";
	MenuItemImages[ITM_CHANGECFC] = "images\\MenuItemsd\\fillcolor.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItemsd\\Menu_SelFig.jpg";
	MenuItemImages[ITM_SAVEGRAPH] = "images\\MenuItemsd\\Menu_SaveGraph.jpg";
	MenuItemImages[ITM_LOADGRAPH] = "images\\MenuItemsd\\Menu_LoadGraph.jpg";
	MenuItemImages[ITM_EXITD] = "images\\MenuItemsd\\Menu_Exit.jpg";
	MenuItemImages[SITM_CHANGEFIGDC] = "images\\MenuItemsd\\RESIZE.jpg";
	MenuItemImages[STIM_CHANGEFIGFC] = "images\\MenuItemsd\\backandfront.jpg";
	MenuItemImages[SITM_DELFIG] = "images\\MenuItemsd\\Menu_DelFig.jpg";
	MenuItemImages[SITM_CPYFIG] = "images\\MenuItemsd\\Menu_CopyFig.jpg";
	MenuItemImages[SITM_CUTFIG] = "images\\MenuItemsd\\Menu_CutFig.jpg";
	MenuItemImages[SITM_PSTFIG] = "images\\MenuItemsd\\Menu_PasteFig.jpg";
	MenuItemImages[ITM_SWITCHPM] = "images\\MenuItemsd\\Menu_SwitchtoPlay.jpg";
	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.MenuItemWidth*DRAW_ITM_COUNT, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	ClearToolBar();
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_COLOUR] = "images\\MenuItemsp\\Menu_Colour.jpg";
	MenuItemImages[ITM_SHAPE] = "images\\MenuItemsp\\Menu_Shape.jpg";
	MenuItemImages[ITM_BOTH] = "images\\MenuItemsp\\Menu_Both.jpg";
	MenuItemImages[ITM_RESTART] = "images\\MenuItemsp\\Menu_Restart.jpg";
	MenuItemImages[ITM_SWITCHDM] = "images\\MenuItemsp\\Menu_SwitchDraw.jpg";
	MenuItemImages[ITM_EXITP] = "images\\MenuItemsp\\Menu_Exit.jpg";
	///TODO: write code to create Play mode menu

	//Draw menu item one image at a time
	for(int i=0; i<PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.MenuItemWidth*PLAY_ITM_COUNT, UI.ToolBarHeight);	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight+1, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}

void Output::changeCrntDrawColor(color SelectedColor)
{
	UI.DrawColor=SelectedColor;
}

void Output::changeCrntFillColor(color SelectedColor)
{
	UI.FillColor=SelectedColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr,UI.PenWidth);
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);	
}

void Output::DrawCircle(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr,UI.PenWidth);
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	int radius=sqrt(pow(P1.x-P2.x,2)+pow(P1.y-P2.y,2));

	
	pWind->DrawCircle(P1.x, P1.y, radius, style);
}

void Output:: DrawTriangle(Point P1, Point P2, Point P3, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr,UI.PenWidth);
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
		
	}
	else	
	{
		style = FRAME;
	}
	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}

void Output:: DrawLine(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr,UI.PenWidth);

	drawstyle style=FRAME;
	
	
	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);
}






//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

