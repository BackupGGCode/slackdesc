#ifndef SLACKDESCDIALOG_H
#define SLACKDESCDIALOG_H

#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

//(*Headers(CSlackDescDialog)
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class CSlackDescDialog: public wxDialog
{
	public:

		CSlackDescDialog(wxWindow* parent,wxWindowID id = -1);
		virtual ~CSlackDescDialog();

		//(*Identifiers(CSlackDescDialog)
		static const long ID_TEXTCTRL1;
		static const long ID_STATICLINE1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)
    wxString GetSlackDesc(){return slackdesc->GetValue();};
    void SetSlackDesc(wxString desc){slackdesc->SetValue(desc);};
	protected:

		//(*Handlers(CSlackDescDialog)
		void OnCloseClick(wxCommandEvent& event);
		void OnSaveClick(wxCommandEvent& event);
		//*)

		//(*Declarations(CSlackDescDialog)
		wxButton* save;
		wxBoxSizer* BoxSizer2;
		wxTextCtrl* slackdesc;
		wxStaticLine* StaticLine1;
		wxBoxSizer* BoxSizer1;
		wxButton* close;
		//*)

	private:

		DECLARE_EVENT_TABLE()
};

#endif
