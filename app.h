#ifndef APP_H
#define APP_H

#include <wx/wxprec.h>

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    void SelectLanguage(int lang);
protected:
    wxLocale  m_Locale;
};

#endif // APP_H
