#pragma once

#include <wx/wx.h>

namespace vex {

	/**
	 * Main application logic for VEXpression.
	 **/
	class MainApp : public wxApp {
	public :
		MainApp();
		virtual ~MainApp();


		// == Functions.
		/**
		 * Called upon application startup.
		 *
		 * \return			True if initialization was successful, false otherwise.
		 **/
		virtual bool		OnInit() override;
	};

	// Tell wxWidgets about our application class so it can link wxEntry properly.
	wxDECLARE_APP(MainApp);

}	// namespace vex
