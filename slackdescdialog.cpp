
#include <wx/file.h>
#include <wx/sysopt.h>
#include <wx/settings.h>
#include <wx/filedlg.h>
#include "slackdescdialog.h"
#include "sharedata.h"

//(*IdInit(CSlackDescDialog)
const long CSlackDescDialog::ID_TEXTCTRL1 = wxNewId();
const long CSlackDescDialog::ID_STATICLINE1 = wxNewId();
const long CSlackDescDialog::ID_BUTTON1 = wxNewId();
const long CSlackDescDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CSlackDescDialog,wxDialog)
	//(*EventTable(CSlackDescDialog)
	EVT_BUTTON(ID_BUTTON1,CSlackDescDialog::OnSaveClick)
	EVT_BUTTON(ID_BUTTON2,CSlackDescDialog::OnCloseClick)
	//*)
END_EVENT_TABLE()

CSlackDescDialog::CSlackDescDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(CSlackDescDialog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	slackdesc = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(614,281), wxTE_AUTO_SCROLL|wxTE_MULTILINE|wxTE_READONLY|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	slackdesc->SetFocus();
	BoxSizer1->Add(slackdesc, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 10);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	BoxSizer1->Add(StaticLine1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	save = new wxButton(this, ID_BUTTON1, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(save, 0, wxRIGHT|wxALIGN_LEFT|wxALIGN_TOP, 10);
	close = new wxButton(this, ID_BUTTON2, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer2->Add(close, 0, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 0);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CSlackDescDialog::OnSaveClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CSlackDescDialog::OnCloseClick);
	//*)
	wxFont thisFont = wxSystemSettings::GetFont(wxSYS_ANSI_FIXED_FONT);
	if ( !thisFont.Ok() ) thisFont = wxSystemSettings::GetFont(wxSYS_OEM_FIXED_FONT);
#ifndef __WXMSW__
	thisFont.SetFaceName(_T("DejaVu Sans Mono"));
#endif
	//SetFont(thisFont);
	slackdesc->SetFont(thisFont);

}

CSlackDescDialog::~CSlackDescDialog()
{
}


void CSlackDescDialog::OnCloseClick(wxCommandEvent& event)
{
    Close();
}

void CSlackDescDialog::OnSaveClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this,_("Choose a file"),wxEmptyString,SLACK_DESC_FILENAME,
        wxT("All files (*.*)|*.*|TXT (*.txt)|*.txt"),wxSAVE|wxOVERWRITE_PROMPT|wxFD_CHANGE_DIR);
//    dlg.SetWindowStyle(wxSAVE|wxOVERWRITE_PROMPT);
//    dlg.SetWildcard(wxT("None (*.)|*.|TXT (*.txt)|*.txt|All files (*.*)|*.*"));
//    dlg.SetFilename(SLACK_DESC_FILENAME);
    if (dlg.ShowModal()==wxID_CANCEL) return ;
    wxString path=dlg.GetPath();
    //wxMessageBox(path);
    wxFile file(path,wxFile::write);
    file.Write(slackdesc->GetValue(),*wxConvCurrent);
}
