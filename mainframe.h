#ifndef MAINFRAME_H
#define MAINFRAME_H


//(*Headers(MainFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/frame.h>
//*)

#include <wx/richtext/richtextctrl.h>
#include <wx/intl.h>


class MainFrame: public wxFrame
{
	public:

		MainFrame(wxLocale* locale,wxWindow* parent,wxWindowID id = -1);
		virtual ~MainFrame();

		//(*Identifiers(MainFrame)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICLINE1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON_ABOUT;
		//*)
        wxLocale* m_Locale;
	protected:


		//(*Handlers(MainFrame)
		void OnQuit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnCreateClick(wxCommandEvent& event);
		void OnLoadClick(wxCommandEvent& event);
		void OnbtnAboutClick(wxCommandEvent& event);
		void Ondesc_textTextEnter(wxCommandEvent& event);
		//*)


		//(*Declarations(MainFrame)
		wxButton* create;
		wxButton* LoadButton;
		wxButton* btnAbout;
		wxStaticText* static_title;
		wxTextCtrl* soft_name;
		wxTextCtrl* desc_text;
		wxStaticLine* StaticLine1;
		wxButton* close;
		wxStaticText* ruler;
		//*)
#ifdef __WXGTK__
        int Gtk_GetNumberOfLines();
        wxString Gtk_GetLineText(int line);
#endif
	private:

		DECLARE_EVENT_TABLE()
};

#endif
