#pragma once

#include "wx/wx.h"
#include "wx/listctrl.h"
#include "sqlitepp.h"

class cMain: public wxFrame
{
private:
	wxPanel* panel;
	wxListView* list;
	wxBoxSizer* sizer;

	

	std::string curTable;
public:
	void addRows(std::string table);
	void addRows(sqlitepp::result res);
	void OnButtonClicked(wxCommandEvent& evt);
	
	
	cMain();
	~cMain();
};

