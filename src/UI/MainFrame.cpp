#include "../Foundation/Text.h"
#include "UI/MainFrame.h"

#include <wx/artprov.h>

namespace ve {

	enum {
		ID_EDITOR = wxID_HIGHEST + 1,
		ID_TOGGLE_REPL,
		ID_RUN_SCRIPT
	};

	MainFrame::MainFrame(const wxString& title) :
		wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 720)),
		realTimeRepl(true),
		editor(nullptr),
		outputArea(nullptr),
		constantsList(nullptr),
		functionsTree(nullptr) {
		
		auiManager.SetManagedWindow(this);

		createToolbar();
		createControls();

		auiManager.AddPane(editor, wxAuiPaneInfo().Name("Editor").CenterPane().PaneBorder(false));

		auiManager.AddPane(constantsList, wxAuiPaneInfo().Name("Constants").Caption("Constants").Left().Position(0).MinSize(200, 200));
		auiManager.AddPane(functionsTree, wxAuiPaneInfo().Name("Functions").Caption("Functions").Left().Position(1).MinSize(200, 200));

		auiManager.AddPane(outputArea, wxAuiPaneInfo().Name("Output").Caption("Output").Bottom().MinSize(100, 100));

		auiManager.Update();

		Bind(wxEVT_STC_CHANGE, &MainFrame::onEditorTextChanged, this, ID_EDITOR);
		Bind(wxEVT_MENU, &MainFrame::onReplToggled, this, ID_TOGGLE_REPL);
		Bind(wxEVT_MENU, &MainFrame::onRunClicked, this, ID_RUN_SCRIPT);
	}

	MainFrame::~MainFrame() {
		auiManager.UnInit();
	}

	// == Functions.
	/**
	 * A simple helper function to print the strongly-typed Result union.
	 *
	 * \param res			The execution result to print.
	 * \return			A string representation of the result.
	 **/
	std::string MainFrame::printResult(const ve::Result& res) {
		switch (res.type) {
			case ve::NumericConstant::Unsigned : {
				return ve::Text::toUnsigned(res.value.uintVal) + " (" + ve::Text::toHex(res.value.uintVal) + ")";
			}
			case ve::NumericConstant::Signed : {
				if (res.value.intVal < 0) {
					return ve::Text::toSigned(res.value.intVal) + " (" + ve::Text::toHex(res.value.intVal) + ", -" + ve::Text::toHex(-res.value.intVal) + ")";
				}
				else {
					return ve::Text::toSigned(res.value.intVal) + " (" + ve::Text::toHex(res.value.intVal) + ")";
				}
			}
			case ve::NumericConstant::Floating : {
				union {
					float		floatVal;
					uint32_t	uintVal;
				} flt;
				flt.floatVal = float(res.value.doubleVal);
				return ve::Text::toDouble(res.value.doubleVal) + " (" + ve::Text::toHex(flt.uintVal) + ", " + ve::Text::toHex(res.value.uintVal) + ")";
			}
			case ve::NumericConstant::Object : {
				if (res.value.objectVal) {
					std::string utf8Str;
				
					if (res.value.objectVal->toString(utf8Str, 0, 0)) {
						return utf8Str;
					}
					else {
						return "[Object String Conversion Failed]";
					}
				}
				else {
					return "[Null Object Pointer]\n";
				}
				break;
			}
			case ve::NumericConstant::Invalid : {}
			default : {
				return "[Invalid or Uninitialized]";
			}
		}
	}

	/**
	 * Creates and configures the top toolbar.
	 **/
	void MainFrame::createToolbar() {
		wxToolBar* toolbar = CreateToolBar(wxTB_HORIZONTAL | wxNO_BORDER | wxTB_FLAT | wxTB_TEXT);
		
		toolbar->AddTool(ID_TOGGLE_REPL, "REPL: ON", wxArtProvider::GetBitmap(wxART_TICK_MARK, wxART_TOOLBAR));
		toolbar->AddSeparator();
		toolbar->AddTool(ID_RUN_SCRIPT, "Run (Ctrl+Enter)", wxArtProvider::GetBitmap(wxART_EXECUTABLE_FILE, wxART_TOOLBAR));
		
		toolbar->Realize();
	}

	/**
	 * Initializes all the UI controls before handing them to the AUI Manager.
	 **/
	void MainFrame::createControls() {
		editor = new wxStyledTextCtrl(this, ID_EDITOR);
		
		wxFont monoFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
		editor->StyleSetFont(wxSTC_STYLE_DEFAULT, monoFont);
		editor->StyleClearAll();
		
		editor->SetLexer(wxSTC_LEX_CPP);
		editor->StyleSetForeground(wxSTC_C_COMMENT, wxColour(0, 128, 0));
		editor->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColour(0, 128, 0));
		editor->StyleSetForeground(wxSTC_C_WORD, wxColour(0, 0, 255));
		editor->StyleSetForeground(wxSTC_C_STRING, wxColour(163, 21, 21));
		editor->SetMarginType(1, wxSTC_MARGIN_NUMBER);
		editor->SetMarginWidth(1, 30);

		outputArea = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxBORDER_NONE);
		outputArea->SetFont(monoFont);

		constantsList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_NONE);
		constantsList->InsertColumn(0, "Name", wxLIST_FORMAT_LEFT, 100);
		constantsList->InsertColumn(1, "Value", wxLIST_FORMAT_LEFT, 150);
		populateConstants();

		functionsTree = new wxTreeListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE | wxBORDER_NONE);
		functionsTree->AppendColumn("Name", 120, wxALIGN_LEFT, wxCOL_RESIZABLE);
		functionsTree->AppendColumn("Params", 80, wxALIGN_LEFT, wxCOL_RESIZABLE);
		functionsTree->AppendColumn("Description", 300, wxALIGN_LEFT, wxCOL_RESIZABLE);
		populateFunctions();
	}

	/**
	 * Populates the constants list with default data.
	 **/
	void MainFrame::populateConstants() {
		for (size_t i = 0; i < ExecutionContext::totalBuiltInConstants(); ++i) {
			Result res;

			long index = constantsList->InsertItem(constantsList->GetItemCount(), ExecutionContext::getBuiltinConstant(i, res));

			constantsList->SetItem(index, 1, wxString::FromUTF8(printResult(res)));
		}
	}

	/**
	 * Populates the functions tree with default data.
	 **/
	void MainFrame::populateFunctions() {
		wxTreeListItem root = functionsTree->GetRootItem();
		wxTreeListItem mathGroup = functionsTree->AppendItem(root, "Math");
		
		wxTreeListItem funcItem = functionsTree->AppendItem(mathGroup, "barthann");
		functionsTree->SetItemText(funcItem, 1, "n");
		functionsTree->SetItemText(funcItem, 2, "Returns a modified Bartlett-Hann window.");

		functionsTree->Expand(mathGroup);
	}

	/**
	 * Extracts the code from the editor and evaluates it.
	 **/
	void MainFrame::evaluateScript() {
		wxString code = editor->GetText();
		std::string testExpr = code.ToStdString(wxConvUTF8);
		ve::ExecutionContext context;
		
		if (!context.compile(testExpr)) {
			outputArea->SetValue("Syntax Error.\n");
		}
		else {
			try {
				ve::Result res = context.execute();
				wxString resultText = wxString::FromUTF8(printResult(res));
				outputArea->SetValue(resultText);
			}
			catch (const std::exception& e) {
				wxString errorMsg = wxString::FromUTF8(e.what());
				outputArea->SetValue("Runtime Exception: " + errorMsg + "\n");
			}
			catch (...) {
				outputArea->SetValue("Unknown Runtime Error occurred.\n");
			}
		}
	}

	/**
	 * Event handler for when the text in the editor changes.
	 *
	 * \param event			The styled text event.
	 **/
	void MainFrame::onEditorTextChanged(wxStyledTextEvent& event) {
		if (realTimeRepl) {
			evaluateScript();
		}
	}

	/**
	 * Event handler for the Run button.
	 *
	 * \param event			The command event.
	 **/
	void MainFrame::onRunClicked(wxCommandEvent& event) {
		evaluateScript();
	}

	/**
	 * Event handler for the REPL toggle button.
	 *
	 * \param event			The command event.
	 **/
	void MainFrame::onReplToggled(wxCommandEvent& event) {
		realTimeRepl = !realTimeRepl;
		GetToolBar()->SetToolShortHelp(ID_TOGGLE_REPL, realTimeRepl ? "REPL: ON" : "REPL: OFF");
	}

}	// namespace ve
