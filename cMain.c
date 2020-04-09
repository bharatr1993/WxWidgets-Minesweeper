#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Minesweeper - v1",wxPoint(30,30), wxSize(800,600))
{
	btn = new wxButton*[cMain::nFieldWidth * cMain::nFieldHeight];
	wxGridSizer *grid = new wxGridSizer(cMain::nFieldWidth, cMain::nFieldHeight, 0, 0);
	cMain::nField = new int[cMain::nFieldWidth * cMain:: nFieldHeight];
	cMain::mineloc = new int[cMain::nFieldWidth * cMain:: nFieldHeight];
	
	for(int x=0;x<cMain::nFieldWidth;x++)
	{
		for(int y=0;y<cMain::nFieldHeight;y++)
		{
			btn[y * (cMain::nFieldWidth) + x] = new wxButton(this, 10000 + (y * (cMain::nFieldWidth) + x));
			grid -> Add(btn[y * (cMain::nFieldWidth) + x], 1, wxEXPAND | wxALL);
			btn[y * cMain::nFieldWidth + x] -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			btn[y * cMain::nFieldWidth + x] -> Bind(wxEVT_RIGHT_DOWN, &cMain::rclick, this);
			cMain::nField[y * cMain::nFieldWidth + x] = 0;
			cMain::mineloc[y * cMain::nFieldWidth + x] = 0;
		}
	}
	
	this -> SetSizer(grid);
	grid -> Layout();
	
}
cMain::~cMain()
{
	delete[]btn;
}

void cMain::OnButtonClicked(wxCommandEvent &evt)
{
	int x = (evt.GetId() - 10000) % cMain::nFieldWidth;
	int y = (evt.GetId() - 10000) / cMain::nFieldWidth;
	
	if(cMain::bFirstClick)
	{
		int mines = 30;
		cMain::gameminectr=mines;
		
		while (mines)
		{
			int rx = rand() % cMain::nFieldWidth;
			int ry = rand() % cMain::nFieldHeight;
			
			if(cMain::nField[ry * cMain::nFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				cMain::nField[ry * cMain::nFieldWidth + rx] = -1;
				mines--;
			}
		}
		cMain::bFirstClick = false;
	}
	
	
	
	if(cMain::nField[y * cMain::nFieldWidth + x] == -1 && cMain::mineloc[y * cMain::nFieldWidth + x] != 1)
	{
		wxMessageBox("BOOOM! You are dead...");
		cMain::bFirstClick = true;
		
		for(int x=0;x<cMain::nFieldWidth;x++)
		{
			for(int y=0;y<cMain::nFieldHeight;y++)
			{
				cMain::nField[y * cMain::nFieldWidth + x] = 0;
				btn[y * cMain::nFieldWidth + x] -> SetLabel("");
				btn[y * cMain::nFieldWidth + x] -> Enable(true);
				cMain::mineloc[y * cMain::nFieldWidth + x] = 0;
			}
		}
	}
	else
	{
		int mine_count = 0;
		
		for(int i=-1; i<2; i++)
		{
			for(int j = -1; j<2; j++)
			{
				if(x + i >= 0 && x + i < cMain::nFieldWidth && y + j >=0 && y + j < cMain::nFieldHeight)
				{
					if(cMain::nField[(y + j) * cMain::nFieldWidth + (x + i)] == -1)
					{
						mine_count++;
						
					}
				}
			}
		}
		
		if(cMain::mineloc[y * cMain::nFieldWidth + x] != 1)
		{
			btn[y * cMain::nFieldWidth + x] -> SetLabel(std::to_string(mine_count));
			
			btn[y*cMain::nFieldWidth + x] -> Enable(false);
		}

	}
	
	if(gameminectr==0)
	{
		wxMessageBox("You Won! Congrats");
		cMain::bFirstClick = true;
		
		for(int x=0;x<cMain::nFieldWidth;x++)
		{
			for(int y=0;y<cMain::nFieldHeight;y++)
			{
				cMain::nField[y * cMain::nFieldWidth + x] = 0;
				btn[y * cMain::nFieldWidth + x] -> SetLabel("");
				btn[y * cMain::nFieldWidth + x] -> Enable(true);
				cMain::mineloc[y * cMain::nFieldWidth + x] = 0;
			}
		}
	}
	
	
	
	evt.Skip();

}

void cMain::rclick(wxMouseEvent &evt)
{	
	int x = (evt.GetId() - 10000) % cMain::nFieldWidth;
	int y = (evt.GetId() - 10000) / cMain::nFieldWidth;
	
	if(cMain::mineloc[y * cMain::nFieldWidth + x] == 0)
	{
		cMain::mineloc[y * cMain::nFieldWidth + x] = 1;
		btn[y * cMain::nFieldWidth + x] -> SetLabel("M");
		//btn[y * cMain::nFieldWidth + x] -> Enable(false);
	}
	else
	{
		cMain::mineloc[y * cMain::nFieldWidth + x] = 0;
		btn[y * cMain::nFieldWidth + x] -> SetLabel("");
		//btn[y * cMain::nFieldWidth + x] -> Enable(true);
	}
	if(cMain::mineloc[y * cMain::nFieldWidth + x] == 1 && cMain::nField[y * cMain::nFieldWidth + x] == -1)
	{
		cMain::gameminectr--;
	}
	evt.Skip();
}
