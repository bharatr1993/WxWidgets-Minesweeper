#pragma once

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	
public:
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton **btn;
	int* nField = nullptr;
	bool bFirstClick = true;
	int* mineloc = nullptr;
	int gameminectr = 0;
	
	void OnButtonClicked(wxCommandEvent &evt);
	void rclick(wxMouseEvent &evt);
	wxDECLARE_EVENT_TABLE();
};
