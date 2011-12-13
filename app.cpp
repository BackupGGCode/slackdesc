#include "app.h"

//(*AppHeaders
#include "mainframe.h"
#include <wx/image.h>
//*)

#include <wx/intl.h>

// language data
static const wxLanguage langIds[] =
{
    wxLANGUAGE_DEFAULT,
    wxLANGUAGE_ENGLISH,
    wxLANGUAGE_ENGLISH_US,
    wxLANGUAGE_CHINESE_SIMPLIFIED,

};

// note that it makes no sense to translate these strings, they are
// shown before we set the locale anyhow
const wxString langNames[] =
{
    _T("System default"),
    _T("English"),
    _T("English (U.S.)"),
    _T("Simplified Chinese"),

};


IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    SelectLanguage(wxLANGUAGE_ENGLISH);
	//(*AppInitialize
	bool wxsOK = true;
	::wxInitAllImageHandlers();
	if ( wxsOK )
	{
	    MainFrame* MainResource = new MainFrame(&m_Locale,0L);
	    if ( MainResource ) MainResource->Show();
	}
	//*)

	return wxsOK;
}

void MyApp::SelectLanguage(int lang) {

    m_Locale.Init(lang, wxLOCALE_CONV_ENCODING);
    m_Locale.AddCatalogLookupPathPrefix(wxT("."));
    m_Locale.AddCatalogLookupPathPrefix(wxT("lang"));
    m_Locale.AddCatalog(wxT("SlackDescBuild"));
}
