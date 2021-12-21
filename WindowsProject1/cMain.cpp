#include "cMain.h"


void cMain::addRows(std::string table)
{
	sqlitepp::db db("empl.db");
	sqlitepp::query q(db);
	q << "SELECT * FROM " << table << ";";
	sqlitepp::result res = q.store();
	db.close();

	addRows(res);
}

// From query
void cMain::addRows(sqlitepp::result res)
{	for (int i = 0; i < res.num_rows(); ++i)
	{
		list->InsertItem(i, ""); // Init row
		for (int j = 0; j < res[i].size(); ++j)
		{
			list->SetItem(i, j, res[i][j].operator std::string());
		}
	}
}

void cMain::OnTableButtonClicked(wxCommandEvent& evt)
{
	// Getting button object cuz label = name of selected table
	wxButton* button = wxDynamicCast(evt.GetEventObject(), wxButton);

	// Checking if columns already generated
	if (curTable == button->GetLabel())
	{
		//list->DeleteAllColumns();
		//addRows(curTable);
		return;
	}
	curTable = button->GetLabel();

	// Adding columns to list
	sqlitepp::db db("empl.db");
	sqlitepp::query q(db);

	q << "SELECT * FROM " << button->GetLabel() << ";";
	sqlitepp::result res = q.store();
	db.close();

	list->DeleteAllColumns(); // Clearing all columns before adding new ones
	SortData.curСolumns.clear(); // Clearing
	for (int i = 0; i < res[0].size(); ++i)
	{		
		list->AppendColumn(res[0][i].name());
		SortData.curСolumns.push_back(res[0][i].name());
	}

	// Adding rows
	list->DeleteAllItems();
	addRows(res);
}

void cMain::sortByColumn(int column)
{
	sqlitepp::db db("empl.db");
	sqlitepp::query q(db);
	q << "SELECT * FROM '" << curTable.c_str() << "' ORDER BY \"" << SortData.curСolumns[column].c_str() << "\"";
	// Check if we should change sort direction
	if (SortData.curColumn == SortData.curСolumns[column])
		SortData.sortDirection = -SortData.sortDirection;

	// 
	switch (SortData.sortDirection)
	{
		case 1:
			q << " ASC" << ";";
			break;
		case -1:
			q << " DESC" << ";";
			break;
	}
	
	//std::string debug = q.get_query();
	sqlitepp::result res = q.store();
	db.close();

	//Changing status about current column
	SortData.curColumn = SortData.curСolumns[column];

	//Refreshing rows
	list->DeleteAllItems();
	addRows(res);
}

cMain::cMain() : wxFrame(NULL, wxID_ANY, "Hello, world!")
{
	// Opening database
	sqlitepp::db db("empl.db");
	
	if (!db.is_open())
	{
		wxMessageBox("Can't open database!");
		Close(true);
	}

	// Creating panel, list and sizer
	panel = new wxPanel(this);
	list = new wxListView(panel);
	sizer = new wxBoxSizer(wxVERTICAL);

	// Adding buttons
	sqlitepp::query q(db, "SELECT name FROM sqlite_schema WHERE type = 'table' AND name NOT LIKE 'sqlite_%';");
	sqlitepp::result res = q.store();
	for (int i = 0; i < res.num_rows(); i++)
	{
		std::string text;
		text = res[i]["name"];
		wxButton* b = new wxButton(this->panel, i, text);
		b->Bind(wxEVT_BUTTON, &cMain::OnTableButtonClicked, this);
		sizer->Add(b, 0, wxTOP, 0);
	}

	list->Bind(wxEVT_LIST_COL_CLICK, [this](wxListEvent& evt)
		{
			this->sortByColumn(evt.GetColumn());
		});

	// Adding table after all buttons
	sizer->Add(list, 1, wxALL | wxEXPAND, 0);
	panel->SetSizerAndFit(sizer);

	db.close();
}

cMain::~cMain()
{
}
