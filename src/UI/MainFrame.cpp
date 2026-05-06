#include "../Foundation/Text.h"
#include "UI/MainFrame.h"

#include <map>
#include <wx/artprov.h>
#include <wx/toplevel.h>

#ifdef __WXMSW__
#include <dwmapi.h>
#include <uxtheme.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "uxtheme.lib")

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

// Undocumented Windows API to force dark menus and global scrollbars
enum PreferredAppMode { Default, AllowDark, ForceDark, ForceLight, Max };
using fnSetPreferredAppMode = PreferredAppMode(WINAPI*)(PreferredAppMode);
using fnFlushMenuThemes = void(WINAPI*)();

// Callback to theme hidden child controls (Headers, Scrollbars) inside composite wxWidgets
BOOL CALLBACK ThemeEnumChildProc(HWND hwnd, LPARAM lParam) {
	wchar_t className[256];
	if (::GetClassNameW(hwnd, className, 256) > 0) {
		// Native TreeList headers require a specific theme class in Win 10/11 to go dark
		if (std::wcscmp(className, L"SysHeader32") == 0) {
			const wchar_t* theme = (std::wcscmp((const wchar_t*)lParam, L"Explorer") == 0) ? L"ItemsView" : L"DarkMode_ItemsView";
			::SetWindowTheme(hwnd, theme, NULL);
			return TRUE;
		}
	}
	::SetWindowTheme(hwnd, (const wchar_t*)lParam, NULL);
	return TRUE;
}
#endif

namespace vex {

	enum {
		ID_EDITOR = wxID_HIGHEST + 1,
		ID_TOGGLE_REPL,
		ID_RUN_SCRIPT,
		ID_REPL_TIMER,
		ID_VIEW_DARK_THEME,
		ID_WINDOW_CONSTANTS,
		ID_WINDOW_FUNCTIONS
	};

	MainFrame::MainFrame(const wxString& title) :
		wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 720)),
		realTimeRepl(true),
		isDarkMode(false),
		editor(nullptr),
		outputArea(nullptr),
		constantsTree(nullptr),
		functionsTree(nullptr) {
		
#ifdef __WXMSW__
		// Set app mode before any controls are created to catch initial scrollbar/menu states
		HMODULE hUxtheme = ::GetModuleHandleW(L"uxtheme.dll");
		if (hUxtheme) {
			fnSetPreferredAppMode SetAppMode = reinterpret_cast<fnSetPreferredAppMode>(::GetProcAddress(hUxtheme, MAKEINTRESOURCEA(135)));
			if (SetAppMode) {
				SetAppMode(ForceDark);
			}
		}
#endif

		auiManager.SetManagedWindow(this);

		createMenu();
		createToolbar();
		createControls();

		auiManager.AddPane(editor, wxAuiPaneInfo().Name("Editor").CenterPane().PaneBorder(false));

		auiManager.AddPane(constantsTree, wxAuiPaneInfo().Name("Constants").Caption("Constants").Right().Position(0).MinSize(200, 200));
		auiManager.AddPane(functionsTree, wxAuiPaneInfo().Name("Functions").Caption("Functions").Right().Position(1).MinSize(200, 200));

		auiManager.AddPane(outputArea, wxAuiPaneInfo().Name("Output").Caption("Output").Bottom().MinSize(100, 100));

		auiManager.Update();

		Bind(wxEVT_STC_CHANGE, &MainFrame::onEditorTextChanged, this, ID_EDITOR);
		Bind(wxEVT_MENU, &MainFrame::onReplToggled, this, ID_TOGGLE_REPL);
		Bind(wxEVT_MENU, &MainFrame::onRunClicked, this, ID_RUN_SCRIPT);
		Bind(wxEVT_TIMER, &MainFrame::onReplTimer, this, ID_REPL_TIMER);
		
		Bind(wxEVT_MENU, &MainFrame::onMenuThemeToggle, this, ID_VIEW_DARK_THEME);
		
		Bind(wxEVT_MENU, &MainFrame::onMenuFileOpen, this, wxID_OPEN);
		Bind(wxEVT_MENU, &MainFrame::onMenuFileSave, this, wxID_SAVE);
		Bind(wxEVT_MENU, &MainFrame::onMenuFileSaveAs, this, wxID_SAVEAS);
		Bind(wxEVT_MENU, &MainFrame::onMenuFileExit, this, wxID_EXIT);
		
		Bind(wxEVT_MENU, &MainFrame::onMenuWindowConstants, this, ID_WINDOW_CONSTANTS);
		Bind(wxEVT_MENU, &MainFrame::onMenuWindowFunctions, this, ID_WINDOW_FUNCTIONS);
		
		Bind(wxEVT_UPDATE_UI, &MainFrame::onUpdateWindowConstants, this, ID_WINDOW_CONSTANTS);
		Bind(wxEVT_UPDATE_UI, &MainFrame::onUpdateWindowFunctions, this, ID_WINDOW_FUNCTIONS);

		replTimer.SetOwner(this, ID_REPL_TIMER);
	}

	MainFrame::~MainFrame() {
		auiManager.UnInit();
	}

	// == Functions.
	/**
	 * A simple helper function to print the strongly-typed Result union.
	 *
	 * \param res			The execution result to print.
	 * \param extended		If true, extended information is printed.
	 * \return				A string representation of the result.
	 **/
	std::string MainFrame::printResult(const ve::Result& res, bool extended) {
		switch (res.type) {
			case ve::NumericConstant::Unsigned : {
				std::string tmp = ve::Text::toUnsigned(res.value.uintVal) + " (" + ve::Text::toHex(res.value.uintVal, size_t(-1));
				if (extended) {
					tmp += ", " + ve::Text::toBinary(res.value.uintVal, size_t(-1)) + ")";
				}
				else {
					tmp += ")";
				}
				return tmp;
			}
			case ve::NumericConstant::Signed : {
				if (res.value.intVal < 0) {
					std::string tmp = ve::Text::toSigned(res.value.intVal) + " (" + ve::Text::toHex(res.value.intVal, size_t(-1)) + ", -";
					tmp += ve::Text::toHex(-res.value.intVal, size_t(-1));
					if (extended) {
						tmp += ", -" + ve::Text::toBinary(-res.value.intVal, size_t(-1)) + ")";
					}
					else {
						tmp += ")";
					}
					
					return tmp;
				}
				else {
					std::string tmp = ve::Text::toUnsigned(res.value.intVal) + " (" + ve::Text::toHex(res.value.intVal, size_t(-1));
					if (extended) {
						tmp += ", " + ve::Text::toBinary(res.value.intVal, size_t(-1)) + ")";
					}
					else {
						tmp += ")";
					}
					return tmp;
				}
			}
			case ve::NumericConstant::Floating : {
				union {
					float		floatVal;
					uint32_t	uintVal;
				} flt;
				flt.floatVal = float(res.value.doubleVal);
				std::string tmp = ve::Text::toDouble(res.value.doubleVal) + " (" + ve::Text::toHex(flt.uintVal, sizeof(float) * 2) + ", " + ve::Text::toHex(res.value.uintVal, sizeof(double) * 2);
				if (extended) {
					tmp += ", " + ve::Text::toBinary(flt.uintVal, sizeof(float) * 8) + ", " + ve::Text::toBinary(res.value.uintVal, sizeof(double) * 8) + ")";
				}
				else {
					tmp += ")";
				}
				return tmp;
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
	 * Applies the current theme colors to all UI controls.
	 **/
	void MainFrame::applyTheme() {
		wxColour bg = isDarkMode ? wxColour(30, 30, 30) : wxColour(255, 255, 255);
		wxColour fg = isDarkMode ? wxColour(212, 212, 212) : wxColour(0, 0, 0);
		wxColour marginBg = isDarkMode ? wxColour(37, 37, 38) : wxColour(240, 240, 240);
		wxColour marginFg = isDarkMode ? wxColour(133, 133, 133) : wxColour(128, 128, 128);
		wxColour caret = isDarkMode ? wxColour(255, 255, 255) : wxColour(0, 0, 0);

		// Frame and Toolbar
		this->SetBackgroundColour(bg);
		this->SetForegroundColour(fg);
		if (GetToolBar()) {
			GetToolBar()->SetBackgroundColour(bg);
			GetToolBar()->SetForegroundColour(fg);
		}

		// AUI Splitters and Panes
		wxAuiDockArt* art = auiManager.GetArtProvider();
		art->SetColour(wxAUI_DOCKART_BACKGROUND_COLOUR, bg);
		art->SetColour(wxAUI_DOCKART_SASH_COLOUR, isDarkMode ? wxColour(50, 50, 50) : wxColour(200, 200, 200));
		art->SetColour(wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR, bg);
		art->SetColour(wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR, bg);
		art->SetColour(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR, fg);
		art->SetColour(wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR, marginBg);
		art->SetColour(wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR, marginBg);
		art->SetColour(wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR, isDarkMode ? wxColour(255, 255, 255) : wxColour(0, 0, 0));
		art->SetColour(wxAUI_DOCKART_BORDER_COLOUR, isDarkMode ? wxColour(50, 50, 50) : wxColour(200, 200, 200));
		art->SetColour(wxAUI_DOCKART_GRIPPER_COLOUR, bg);

		editor->StyleSetBackground(wxSTC_STYLE_DEFAULT, bg);
		editor->StyleSetForeground(wxSTC_STYLE_DEFAULT, fg);
		editor->StyleClearAll();

		editor->SetCaretForeground(caret);

		editor->StyleSetBackground(wxSTC_STYLE_LINENUMBER, marginBg);
		editor->StyleSetForeground(wxSTC_STYLE_LINENUMBER, marginFg);

		if (isDarkMode) {
			editor->StyleSetForeground(wxSTC_C_COMMENT, wxColour(106, 153, 85));
			editor->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColour(106, 153, 85));
			editor->StyleSetForeground(wxSTC_C_WORD, wxColour(86, 156, 214));
			editor->StyleSetForeground(wxSTC_C_WORD2, wxColour(220, 220, 170));
			editor->StyleSetForeground(wxSTC_C_GLOBALCLASS, wxColour(79, 193, 255));
			editor->StyleSetForeground(wxSTC_C_STRING, wxColour(206, 145, 120));
			editor->StyleSetForeground(wxSTC_C_OPERATOR, wxColour(180, 180, 180));
		}
		else {
			editor->StyleSetForeground(wxSTC_C_COMMENT, wxColour(0, 128, 0));
			editor->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColour(0, 128, 0));
			editor->StyleSetForeground(wxSTC_C_WORD, wxColour(0, 0, 255));
			editor->StyleSetForeground(wxSTC_C_WORD2, wxColour(43, 145, 175));
			editor->StyleSetForeground(wxSTC_C_GLOBALCLASS, wxColour(128, 0, 128));
			editor->StyleSetForeground(wxSTC_C_STRING, wxColour(163, 21, 21));
			editor->StyleSetForeground(wxSTC_C_OPERATOR, wxColour(100, 100, 100));
		}

		outputArea->StyleSetBackground(wxSTC_STYLE_DEFAULT, bg);
		outputArea->StyleSetForeground(wxSTC_STYLE_DEFAULT, fg);
		outputArea->StyleClearAll();

		constantsTree->SetBackgroundColour(bg);
		constantsTree->SetForegroundColour(fg);
		
		functionsTree->SetBackgroundColour(bg);
		functionsTree->SetForegroundColour(fg);

		editor->Refresh();
		outputArea->Refresh();
		constantsTree->Refresh();
		functionsTree->Refresh();
		auiManager.Update();

#ifdef __WXMSW__
		BOOL useDark = isDarkMode ? TRUE : FALSE;
		
		// 1. Force Dark Title Bars for the Main Frame AND all Floating AUI Frames
		for (wxWindowList::compatibility_iterator node = wxTopLevelWindows.GetFirst(); node; node = node->GetNext()) {
			wxTopLevelWindow* tlw = reinterpret_cast<wxTopLevelWindow*>(node->GetData());
			HWND hwnd = static_cast<HWND>(tlw->GetHWND());
			::DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &useDark, sizeof(useDark));
		}

		// 2. Dark Menus & Global Scrollbars (Undocumented Win32 hack)
		HMODULE hUxtheme = ::GetModuleHandleW(L"uxtheme.dll");
		if (hUxtheme) {
			fnSetPreferredAppMode SetAppMode = reinterpret_cast<fnSetPreferredAppMode>(::GetProcAddress(hUxtheme, MAKEINTRESOURCEA(135)));
			if (SetAppMode) {
				SetAppMode(isDarkMode ? ForceDark : Default);
			}

			fnFlushMenuThemes FlushMenu = reinterpret_cast<fnFlushMenuThemes>(::GetProcAddress(hUxtheme, MAKEINTRESOURCEA(136)));
			if (FlushMenu) {
				FlushMenu();
			}
		}

		// Attempt to theme the wxMenuBar directly
		wxMenuBar* mb = GetMenuBar();
		if (mb) {
			mb->SetBackgroundColour(bg);
			mb->SetForegroundColour(fg);
		}
		
		::DrawMenuBar(static_cast<HWND>(this->GetHWND()));

		const wchar_t* themeStr = isDarkMode ? L"DarkMode_Explorer" : L"Explorer";
		
		::SetWindowTheme(static_cast<HWND>(constantsTree->GetHWND()), themeStr, NULL);
		::EnumChildWindows(static_cast<HWND>(constantsTree->GetHWND()), ThemeEnumChildProc, reinterpret_cast<LPARAM>(themeStr));
		
		::SetWindowTheme(static_cast<HWND>(functionsTree->GetHWND()), themeStr, NULL);
		::EnumChildWindows(static_cast<HWND>(functionsTree->GetHWND()), ThemeEnumChildProc, reinterpret_cast<LPARAM>(themeStr));
		
		::SetWindowTheme(static_cast<HWND>(editor->GetHWND()), themeStr, NULL);
		::SetWindowTheme(static_cast<HWND>(outputArea->GetHWND()), themeStr, NULL);
#endif
	}

	/**
	 * Creates and configures the top menu bar.
	 **/
	void MainFrame::createMenu() {
		wxMenuBar* menuBar = new wxMenuBar();

		wxMenu* fileMenu = new wxMenu();
		fileMenu->Append(wxID_OPEN, "Open\tCtrl+O");
		fileMenu->Append(wxID_SAVE, "Save\tCtrl+S");
		fileMenu->Append(wxID_SAVEAS, "Save As...");
		fileMenu->AppendSeparator();
		fileMenu->Append(wxID_EXIT, "Exit\tAlt+F4");

		/*wxMenu* viewMenu = new wxMenu();
		viewMenu->AppendCheckItem(ID_VIEW_DARK_THEME, "Dark Theme");
		viewMenu->Check(ID_VIEW_DARK_THEME, isDarkMode);*/

		wxMenu* windowMenu = new wxMenu();
		windowMenu->Append(ID_WINDOW_CONSTANTS, "Constants");
		windowMenu->Append(ID_WINDOW_FUNCTIONS, "Functions");

		menuBar->Append(fileMenu, "&File");
		//menuBar->Append(viewMenu, "&View");
		menuBar->Append(windowMenu, "&Window");

		SetMenuBar(menuBar);
	}

	/**
	 * Creates and configures the top toolbar.
	 **/
	void MainFrame::createToolbar() {
		wxToolBar* toolbar = CreateToolBar(wxTB_HORIZONTAL | wxNO_BORDER | wxTB_FLAT | wxTB_TEXT);
		
		toolbar->AddCheckTool(ID_TOGGLE_REPL, "REPL: ON", wxArtProvider::GetBitmap(wxART_TICK_MARK, wxART_TOOLBAR));
		toolbar->ToggleTool(ID_TOGGLE_REPL, !realTimeRepl);

		toolbar->AddSeparator();
		toolbar->AddTool(ID_RUN_SCRIPT, "Run (Ctrl+Enter)", wxArtProvider::GetBitmap(wxART_EXECUTABLE_FILE, wxART_TOOLBAR));
		
		toolbar->Realize();
	}

	/**
	 * Initializes all the UI controls before handing them to the AUI Manager.
	 **/
	void MainFrame::createControls() {
		editor = new wxStyledTextCtrl(this, ID_EDITOR, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
		
		wxFont monoFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
		editor->StyleSetFont(wxSTC_STYLE_DEFAULT, monoFont);
		editor->StyleClearAll();
		
		editor->SetLexer(wxSTC_LEX_CPP);
		editor->SetTabWidth(4);

		editor->SetMarginType(1, wxSTC_MARGIN_NUMBER);
		editor->SetMarginWidth(1, 30);

		wxString baseKeywords = 
			"if else for in do while break continue return true True false False static_cast "
			"uint8_t u8 ui8 uint16_t u16 ui16 uint32_t u32 ui32 uint64_t u64 ui64 "
			"int8_t i8 int16_t i16 int32_t i32 int64_t i64 float16 f16 float f32 double f64 "
			"__m64 __m128 __m128d __m128i __m256 __m256d __m256i __m512 __m512d __m512i v128_t "
			"int8x8_t int16x4_t int32x2_t int64x1_t uint8x8_t uint16x4_t uint32x2_t uint64x1_t "
			"float32x2_t float64x1_t int8x16_t int16x8_t int32x4_t int64x2_t "
			"uint8x16_t uint16x8_t uint32x4_t uint64x2_t float32x4_t float64x2_t";
		editor->SetKeyWords(0, baseKeywords);

		wxString funcKeywords;
		for (size_t i = 0; ve::ExecutionContext::getBuiltinFunction(i); ++i) {
			const auto* funcDef = ve::ExecutionContext::getBuiltinFunction(i);
			funcKeywords << funcDef->name << " ";
		}
		editor->SetKeyWords(1, funcKeywords);

		wxString constKeywords;
		for (size_t i = 0; i < ve::ExecutionContext::totalBuiltInConstants(); ++i) {
			ve::Result res;
			ve::StringId strId;
			const char* name = ve::ExecutionContext::getBuiltinConstant(i, res, strId);
			constKeywords << name << " ";
		}
		editor->SetKeyWords(3, constKeywords);

		outputArea = new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
		outputArea->StyleSetFont(wxSTC_STYLE_DEFAULT, monoFont);
		outputArea->StyleClearAll();
		outputArea->SetReadOnly(true);
		outputArea->SetMarginWidth(0, 0);
		outputArea->SetMarginWidth(1, 0);
		outputArea->SetWrapMode(wxSTC_WRAP_WORD);

		constantsTree = new wxTreeListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE | wxBORDER_NONE);
		constantsTree->AppendColumn("Name", 120, wxALIGN_LEFT, wxCOL_RESIZABLE);
		constantsTree->AppendColumn("Value", 150, wxALIGN_LEFT, wxCOL_RESIZABLE);
		populateConstants();

		functionsTree = new wxTreeListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE | wxBORDER_NONE);
		functionsTree->AppendColumn("Name", 120, wxALIGN_LEFT, wxCOL_RESIZABLE);
		//functionsTree->AppendColumn("Params", 80, wxALIGN_LEFT, wxCOL_RESIZABLE);
		functionsTree->AppendColumn("Description", 300, wxALIGN_LEFT, wxCOL_RESIZABLE);
		populateFunctions();

		applyTheme();
	}

	/**
	 * Populates the constants tree with default data.
	 **/
	void MainFrame::populateConstants() {
		wxTreeListItem root = constantsTree->GetRootItem();

		std::map<ve::StringId, wxTreeListItem> groups;

		for (size_t i = 0; i < ve::ExecutionContext::totalBuiltInConstants(); ++i) {
			ve::Result res;
			ve::StringId strId;
			std::string name = ve::ExecutionContext::getBuiltinConstant(i, res, strId);
			
			wxTreeListItem thisGroup;
			auto groupItem = groups.find(strId);
			if (groupItem == groups.end()) {
				std::wstring groupName = ve::StrL(strId, ve::Languages::English);
				thisGroup = constantsTree->AppendItem(root, groupName);
				groups[strId] = thisGroup;
			}
			else {
				thisGroup = groupItem->second;
			}

			wxTreeListItem item = constantsTree->AppendItem(thisGroup, wxString::FromUTF8(name));
			constantsTree->SetItemText(item, 1, wxString::FromUTF8(printResult(res, false)));
		}

		//constantsTree->Expand(builtInGroup);
	}

	/**
	 * Populates the functions tree with default data.
	 **/
	void MainFrame::populateFunctions() {
		wxTreeListItem root = functionsTree->GetRootItem();

		std::map<ve::StringId, wxTreeListItem> groups;
		for (size_t i = 0; ve::ExecutionContext::getBuiltinFunction(i); ++i) {
			const auto* funcDef = ve::ExecutionContext::getBuiltinFunction(i);
			
			wxTreeListItem thisGroup;
			auto groupItem = groups.find(funcDef->category);
			if (groupItem == groups.end()) {
				std::wstring groupName = ve::StrL(funcDef->category, ve::Languages::English);
				thisGroup = functionsTree->AppendItem(root, groupName);
				groups[funcDef->category] = thisGroup;
			}
			else {
				thisGroup = groupItem->second;
			}

			wxTreeListItem item = functionsTree->AppendItem(thisGroup, wxString::FromUTF8(funcDef->name));

			std::u8string utf8Str = ve::StrU8(funcDef->description, ve::Languages::English);
			utf8Str = ve::Text::replaceUtf8<std::u8string>(utf8Str, std::u8string(u8"\r"), std::u8string(u8""));
			utf8Str = ve::Text::replaceUtf8<std::u8string>(utf8Str, std::u8string(u8"\n"), std::u8string(u8"    "));
			functionsTree->SetItemText(item, 1, wxString::FromUTF8(reinterpret_cast<const char*>(utf8Str.c_str())));
			for (size_t j = 0; j < funcDef->parameters.size(); ++j) {
				wxTreeListItem parm = functionsTree->AppendItem(item, wxString::FromUTF8(funcDef->parameters[j].name));
				functionsTree->SetItemText(parm, 1, ve::StrL(funcDef->parameters[j].description, ve::Languages::English));
			}
		}
		
		/*wxTreeListItem funcItem = functionsTree->AppendItem(mathGroup, "barthann");
		functionsTree->SetItemText(funcItem, 1, "n");
		functionsTree->SetItemText(funcItem, 2, "Returns a modified Bartlett-Hann window.");

		functionsTree->Expand(mathGroup);*/
	}

	/**
	 * Extracts the code from the editor and evaluates it.
	 **/
	void MainFrame::evaluateScript() {
		wxString code = editor->GetText();
		std::string testExpr = code.ToStdString(wxConvUTF8);
		ve::ExecutionContext context;
		
		outputArea->SetReadOnly(false);

		if (!context.compile(testExpr)) {
			outputArea->SetText("Syntax Error.\n");
		}
		else {
			try {
				ve::Result res = context.execute();
				wxString resultText = wxString::FromUTF8(printResult(res));
				outputArea->SetText(resultText);
			}
			catch (const std::exception& e) {
				wxString errorMsg = wxString::FromUTF8(e.what());
				outputArea->SetText("Runtime Exception: " + errorMsg + "\n");
			}
			catch (...) {
				outputArea->SetText("Unknown Runtime Error occurred.\n");
			}
		}

		outputArea->SetReadOnly(true);
	}

	/**
	 * Event handler for when the text in the editor changes.
	 *
	 * \param event			The styled text event.
	 **/
	void MainFrame::onEditorTextChanged(wxStyledTextEvent& event) {
		if (realTimeRepl) {
			replTimer.Start(100, wxTIMER_ONE_SHOT);
		}
	}

	/**
	 * Event handler for the REPL debounce timer.
	 *
	 * \param event			The timer event.
	 **/
	void MainFrame::onReplTimer(wxTimerEvent& event) {
		evaluateScript();
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
		realTimeRepl = !event.IsChecked();
		GetToolBar()->SetToolShortHelp(ID_TOGGLE_REPL, realTimeRepl ? "REPL: ON" : "REPL: OFF");
	}

	/**
	 * Event handler for the View -> Dark Theme menu item.
	 *
	 * \param event			The command event.
	 **/
	void MainFrame::onMenuThemeToggle(wxCommandEvent& event) {
		isDarkMode = event.IsChecked();
		applyTheme();
	}

	/**
	 * Event handler for the File -> Open menu item.
	 *
	 * \param event			The command event.
	 **/
	void MainFrame::onMenuFileOpen(wxCommandEvent& event) {
	}

	/**
	 * Event handler for the File -> Save menu item.
	 *
	 * \param event			The command event.
	 **/
	void MainFrame::onMenuFileSave(wxCommandEvent& event) {
	}

	/**
	 * Event handler for the File -> Save As menu item.
	 *
	 * \param event			The command event.
	 **/
	void MainFrame::onMenuFileSaveAs(wxCommandEvent& event) {
	}

	/**
	 * Event handler for the File -> Exit menu item.
	 *
	 * \param event			The command event.
	 **/
	void MainFrame::onMenuFileExit(wxCommandEvent& event) {
		Close(true);
	}

	/**
	 * Event handler for the Window -> Constants menu item.
	 *
	 * \param event			The command event.
	 **/
	void MainFrame::onMenuWindowConstants(wxCommandEvent& event) {
		auiManager.GetPane("Constants").Show();
		auiManager.Update();
	}

	/**
	 * Event handler for the Window -> Functions menu item.
	 *
	 * \param event			The command event.
	 **/
	void MainFrame::onMenuWindowFunctions(wxCommandEvent& event) {
		auiManager.GetPane("Functions").Show();
		auiManager.Update();
	}

	/**
	 * Event handler to update the Window -> Constants menu item state.
	 *
	 * \param event			The UI update event.
	 **/
	void MainFrame::onUpdateWindowConstants(wxUpdateUIEvent& event) {
		event.Enable(!auiManager.GetPane("Constants").IsShown());
	}

	/**
	 * Event handler to update the Window -> Functions menu item state.
	 *
	 * \param event			The UI update event.
	 **/
	void MainFrame::onUpdateWindowFunctions(wxUpdateUIEvent& event) {
		event.Enable(!auiManager.GetPane("Functions").IsShown());
	}

}	// namespace vex
