#include "App.h"
wxIMPLEMENT_APP(App);

App::App()
{
}

App::~App()
{
}

bool App::OnInit()
{
    mFrame = new cMain();
    mFrame->Show();
    return true;
}

int App::OnExit()
{
    return 0;
}