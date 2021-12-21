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

	struct {
		std::vector<std::string> curСolumns;
		std::string curColumn;
		int sortDirection = 1;
	} SortData;
	

public:
	void addRows(std::string table);
	void addRows(sqlitepp::result res);
	void OnTableButtonClicked(wxCommandEvent& evt);
	void sortByColumn(int column);

	cMain();
	~cMain();
};

