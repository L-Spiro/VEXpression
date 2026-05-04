#pragma once

#include "Engine/ExecutionContext.h"

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/stc/stc.h>
#include <wx/treelist.h>
#include <wx/listctrl.h>

namespace ve {

	/**
	 * The primary application window for VEXpression.
	 **/
	class MainFrame : public wxFrame {
	public :
		MainFrame(const wxString& title);
		virtual ~MainFrame();


	private :
		wxAuiManager			auiManager;				/**< The layout manager for dockable panes. */
		bool					realTimeRepl;			/**< Flag indicating if the REPL loop is active. */
		wxStyledTextCtrl*		editor;					/**< The syntax-highlighting text editor control. */
		wxTextCtrl*				outputArea;				/**< The read-only output text area. */
		wxListCtrl*				constantsList;			/**< The list of registered constants. */
		wxTreeListCtrl*			functionsTree;			/**< The tree-list view of registered functions. */

		ExecutionContext		ctx;					/**< The execution context for evaluating expressions. */


		// == Functions.
		/**
		 * A simple helper function to print the strongly-typed Result union.
		 * * \param res			The execution result to print.
		 * \return			A string representation of the result.
		 **/
		std::string				printResult(const ve::Result& res);

		/**
		 * Creates and configures the top toolbar.
		 **/
		void					createToolbar();

		/**
		 * Initializes all the UI controls before handing them to the AUI Manager.
		 **/
		void					createControls();

		/**
		 * Populates the constants list with default data.
		 **/
		void					populateConstants();

		/**
		 * Populates the functions tree with default data.
		 **/
		void					populateFunctions();

		/**
		 * Extracts the code from the editor and evaluates it.
		 **/
		void					evaluateScript();

		/**
		 * Event handler for when the text in the editor changes.
		 *
		 * \param event			The styled text event.
		 **/
		void					onEditorTextChanged(wxStyledTextEvent& event);

		/**
		 * Event handler for the Run button.
		 *
		 * \param event			The command event.
		 **/
		void					onRunClicked(wxCommandEvent& event);

		/**
		 * Event handler for the REPL toggle button.
		 *
		 * \param event			The command event.
		 **/
		void					onReplToggled(wxCommandEvent& event);
	};

}	// namespace ve
