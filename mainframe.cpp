

#include "mainframe.h"
#include <wx/icon.h>
#include <wx/settings.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/msgdlg.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/tokenzr.h>
#include <wx/filedlg.h>
#include "version.h"
#include "slackdescdialog.h"
#include "sharedata.h"

#ifdef __WXGTK__
    #include<gtk/gtk.h>
#endif

#include "image/icon.xpm"

//(*InternalHeaders(MainFrame)
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

int idMenuQuit = wxNewId();
int idMenuAbout = wxNewId();


//(*IdInit(MainFrame)
const long MainFrame::ID_STATICTEXT1 = wxNewId();
const long MainFrame::ID_STATICTEXT3 = wxNewId();
const long MainFrame::ID_TEXTCTRL3 = wxNewId();
const long MainFrame::ID_TEXTCTRL1 = wxNewId();
const long MainFrame::ID_STATICLINE1 = wxNewId();
const long MainFrame::ID_BUTTON1 = wxNewId();
const long MainFrame::ID_BUTTON_ABOUT = wxNewId();
//*)

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
	//(*EventTable(MainFrame)
	EVT_BUTTON(wxID_OK,MainFrame::OnCreateClick)
	EVT_BUTTON(ID_BUTTON1,MainFrame::OnLoadClick)
	EVT_BUTTON(wxID_CANCEL,MainFrame::OnQuit)
	//*)
	EVT_MENU(idMenuQuit, MainFrame::OnQuit)
	EVT_MENU(idMenuAbout, MainFrame::OnAbout)
END_EVENT_TABLE()

MainFrame::MainFrame(wxLocale* locale,wxWindow* parent,wxWindowID id)
{

    m_Locale=locale;

	//(*Initialize(MainFrame)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("SlackDescBuild"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX, _T("id"));
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	static_title = new wxStaticText(this, ID_STATICTEXT1, _("Slackware Packages Description Builder"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(static_title, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
	FlexGridSizer1 = new wxFlexGridSizer(2, 2, 0, 0);
	FlexGridSizer1->Add(-1,-1,0, wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
	ruler = new wxStaticText(this, ID_STATICTEXT3, _("|-----handy-ruler------------------------------------------------------|"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(ruler, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	soft_name = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(138,23), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	soft_name->SetFocus();
	FlexGridSizer1->Add(soft_name, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
	desc_text = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_NO_VSCROLL|wxTE_PROCESS_ENTER|wxTE_MULTILINE|wxFULL_REPAINT_ON_RESIZE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(desc_text, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(FlexGridSizer1, 0, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	BoxSizer1->Add(StaticLine1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	create = new wxButton(this, wxID_OK, _("Create"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	BoxSizer2->Add(create, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	LoadButton = new wxButton(this, ID_BUTTON1, _("Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(LoadButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	btnAbout = new wxButton(this, ID_BUTTON_ABOUT, _("About"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ABOUT"));
	BoxSizer2->Add(btnAbout, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	close = new wxButton(this, wxID_CANCEL, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	BoxSizer2->Add(close, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();

	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&MainFrame::Ondesc_textTextEnter);
	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OnCreateClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OnLoadClick);
	Connect(ID_BUTTON_ABOUT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OnbtnAboutClick);
	Connect(wxID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OnQuit);
	//*)
	wxFont thisFont = wxSystemSettings::GetFont(wxSYS_ANSI_FIXED_FONT);
	if ( !thisFont.Ok() ) thisFont = wxSystemSettings::GetFont(wxSYS_OEM_FIXED_FONT);

	//SetFont(thisFont);
	ruler->SetFont(thisFont);
	soft_name->SetFont(thisFont);
	desc_text->SetFont(thisFont);


    int charWidth,charHeight;
    desc_text->GetTextExtent(wxT("a"),&charWidth,&charHeight);
	desc_text->SetMinSize(wxSize(charWidth*(MAX_COLS+1),charHeight*(MAX_ROWS+1)));
    //wxSize ruler_size=ruler->GetSize();
    //desc_text->SetMinSize(wxSize(ruler_size.GetWidth()*(MAX_COLS+1)/(MAX_COLS+2),ruler_size.GetHeight()*MAX_ROWS));

	BoxSizer1->Fit(this);
	BoxSizer1->Layout();


	SetIcon(wxIcon(icon_xpm));
    static_title->SetLabel(desc_name);
//    int width,height;
//    GetTextExtent(wxT("-"),&width,&height);
//    desc_text->SetClientSize(20*MAX_COLS,20*MAX_ROWS);

}

MainFrame::~MainFrame()
{
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(_("wxWidgets Application Template"), _("Welcome to..."));
}

void MainFrame::OnCreateClick(wxCommandEvent& event)
{
    wxString desc,softname;
    desc<<wxT("# ")<<static_title->GetLabel()<<wxT("\n");
    desc<<desc_copyright;
    softname=soft_name->GetValue();
    if(softname.IsEmpty()) return ;
    if(softname.Last() != wxT(':')) softname<<wxT(":");

    desc<<wxString(wxT(' '),softname.Length()-1);
    desc<<ruler->GetLabel()<<wxT("\n");
    int nol;
#ifdef __WXGTK__
    nol=Gtk_GetNumberOfLines();
#else
    nol=desc_text->GetNumberOfLines();
#endif
    int i;
    for(i=0;i<nol;i++){
        desc<<softname;

#ifdef __WXGTK__
        desc<<wxT(" ")<<Gtk_GetLineText(i)<<wxT("\n");
#else
        desc<<wxT(" ")<<desc_text->GetLineText(i)<<wxT("\n");
#endif

    }
    for(int j=i;j<MAX_ROWS;j++){
        desc<<softname<<wxT("\n");
    }


    CSlackDescDialog dlg(this);
    dlg.Centre();
    dlg.SetSlackDesc(desc);
    dlg.ShowModal();
}

void MainFrame::OnLoadClick(wxCommandEvent& event)
{

    wxFileDialog dlg(this,_("Choose a file"),wxEmptyString,SLACK_DESC_FILENAME,
        wxT("All files (*.*)|*.*|TXT (*.txt)|*.txt"),wxOPEN|wxFILE_MUST_EXIST|wxFD_CHANGE_DIR);
    //    dlg.SetWindowStyle(wxOPEN|wxFILE_MUST_EXIST);
    //dlg.SetWildcard(wildcard);
//    dlg.SetWildcard(wxT("None (*.)|*.|TXT (*.txt)|*.txt|All files (*.*)|*.*"));
//    dlg.SetFilename(SLACK_DESC_FILENAME);
    if (dlg.ShowModal()==wxID_CANCEL) return ;
    wxString path=dlg.GetPath();
    wxFileInputStream input(path);
    wxTextInputStream text(input);
    wxString line;
    wxStringTokenizer token;
    wxString name,desc;
    int line_count=0;
    while(!input.Eof()){
        line=text.ReadLine();
        if(line.Left(1)==wxT("#")||line.Find(wxT(":"))==wxNOT_FOUND) continue;
        token.SetString(line,wxT(":"));
        if(token.HasMoreTokens()){
            name=token.GetNextToken();
            line_count++;
            if(line_count<MAX_ROWS) {
                desc<<token.GetNextToken().Trim(false)<<wxT("\n");
            }else {
                desc<<token.GetNextToken();
                break;
            }
        }
    }
    soft_name->SetValue(name);
    desc_text->SetValue(desc);

}

void MainFrame::OnbtnAboutClick(wxCommandEvent& event)
{
    wxString message;
    message<<wxT("\nSlackware Packages Description Builder \n") \
            <<wxT("\nVersion ")<<wxString::FromAscii(AutoVersion::FULLVERSION_STRING) \
            <<wxT(".")<<wxString::Format(wxT("%d"),AutoVersion::BUILDS_COUNT)   \
            <<wxT("\n\nCopyright (C) 2007 2008 2009 Liu Yugang, liuyug@yahoo.cn");
            //<<wxT("\nEMail : liuyug@yahoo.cn");

    wxMessageDialog dlg(this,message,_("About"),wxOK);
    dlg.ShowModal();
}

void MainFrame::Ondesc_textTextEnter(wxCommandEvent& event)
{
    int nol;
#ifdef __WXGTK__
    nol=Gtk_GetNumberOfLines();
#else
    nol=desc_text->GetNumberOfLines();
#endif
//    wxString ll;
//    ll<<nol;
//    wxMessageBox(ll);
    if(nol>=MAX_ROWS) {
        //wxMessageBox(wxT("out of scope"));
    }else event.Skip();
}

#ifdef __WXGTK__
int MainFrame::Gtk_GetNumberOfLines()
{
	int result = 1;
	int paragraphs;
	GtkTextIter iter;

	GtkWidget *text_view = gtk_bin_get_child(GTK_BIN(GTK_SCROLLED_WINDOW(desc_text->GetHandle())));

	// works on a dummy buffer if done during frozen state, but we don't use Freeze/Thaw for Input (yet?)
	gtk_text_buffer_get_start_iter(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)), &iter);
	while(gtk_text_view_forward_display_line(GTK_TEXT_VIEW(text_view), &iter))
		++result;

	paragraphs = desc_text->GetNumberOfLines();
	if(paragraphs != 1 && desc_text->GetLineLength(paragraphs - 1) == 0)
		++result;

	return result;
}
wxString MainFrame::Gtk_GetLineText(int line)
{
    int result=0;
    gchar *text;
	GtkTextIter iter,begin_iter,end_iter;

	GtkWidget *text_view = gtk_bin_get_child(GTK_BIN(GTK_SCROLLED_WINDOW(desc_text->GetHandle())));

	// works on a dummy buffer if done during frozen state, but we don't use Freeze/Thaw for Input (yet?)
	gtk_text_buffer_get_start_iter(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)), &iter);
	while(1){
		if(result == line) break;
		if(gtk_text_view_forward_display_line(GTK_TEXT_VIEW(text_view), &iter)==false) break;
		++result;
	}
	begin_iter=iter;
	gtk_text_view_forward_display_line_end(GTK_TEXT_VIEW(text_view), &iter);
    gtk_text_iter_forward_char(&iter);
	end_iter=iter;
	text=gtk_text_iter_get_text(&begin_iter,&end_iter);
    //text=gtk_text_buffer_get_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)),&begin_iter,&end_iter,true);
	return wxString::FromAscii((char*)text).Trim();

}

#endif
