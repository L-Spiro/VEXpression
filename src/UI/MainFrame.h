#pragma once

#include "Engine/ExecutionContext.h"

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/stc/stc.h>
#include <wx/timer.h>
#include <wx/treelist.h>

namespace ve {

	/**
	 * The primary application window for VEXpression.
	 **/
	class MainFrame : public wxFrame {
	public :
		MainFrame(const wxString& title);
		virtual ~MainFrame();


		// == Functions.

	private :
		// == Members.
		wxAuiManager			auiManager;				/**< The layout manager for dockable panes. */
		wxStyledTextCtrl*		editor;					/**< The syntax-highlighting text editor control. */
		wxStyledTextCtrl*		outputArea;				/**< The read-only output text area. */
		wxTreeListCtrl*			constantsTree;			/**< The tree-list view of registered constants. */
		wxTreeListCtrl*			functionsTree;			/**< The tree-list view of registered functions. */
		wxTimer					replTimer;				/**< The debounce timer. */

		ExecutionContext		ctx;					/**< The execution context for evaluating expressions. */

		bool					realTimeRepl;			/**< Flag indicating if the REPL loop is active. */


		// == Functions.
		/**
		 * A simple helper function to print the strongly-typed Result union.
		 *
		 * \param res			The execution result to print.
		 * \param extended		If true, extended information is printed.
		 * \return				A string representation of the result.
		 **/
		std::string				printResult(const ve::Result& res, bool extended = false);

		/**
		 * Creates and configures the top menu bar.
		 **/
		void					createMenu();

		/**
		 * Creates and configures the top toolbar.
		 **/
		void					createToolbar();

		/**
		 * Initializes all the UI controls before handing them to the AUI Manager.
		 **/
		void					createControls();

		/**
		 * Populates the constants tree with default data.
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
		 * Event handler for the REPL debounce timer.
		 *
		 * \param event			The timer event.
		 **/
		void					onReplTimer(wxTimerEvent& event);

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

		/**
		 * Event handler for the File -> Open menu item.
		 *
		 * \param event			The command event.
		 **/
		void					onMenuFileOpen(wxCommandEvent& event);

		/**
		 * Event handler for the File -> Save menu item.
		 *
		 * \param event			The command event.
		 **/
		void					onMenuFileSave(wxCommandEvent& event);

		/**
		 * Event handler for the File -> Save As menu item.
		 *
		 * \param event			The command event.
		 **/
		void					onMenuFileSaveAs(wxCommandEvent& event);

		/**
		 * Event handler for the File -> Exit menu item.
		 *
		 * \param event			The command event.
		 **/
		void					onMenuFileExit(wxCommandEvent& event);

		/**
		 * Event handler for the Window -> Constants menu item.
		 *
		 * \param event			The command event.
		 **/
		void					onMenuWindowConstants(wxCommandEvent& event);

		/**
		 * Event handler for the Window -> Functions menu item.
		 *
		 * \param event			The command event.
		 **/
		void					onMenuWindowFunctions(wxCommandEvent& event);

		/**
		 * Event handler to update the Window -> Constants menu item state.
		 *
		 * \param event			The UI update event.
		 **/
		void					onUpdateWindowConstants(wxUpdateUIEvent& event);

		/**
		 * Event handler to update the Window -> Functions menu item state.
		 *
		 * \param event			The UI update event.
		 **/
		void					onUpdateWindowFunctions(wxUpdateUIEvent& event);
	};

}	// namespace ve
