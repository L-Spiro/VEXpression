#include "UI/MainApp.h"
#include "UI/MainFrame.h"

// Generate the wxWidgets application internals, but DO NOT let it guess the main function.
wxIMPLEMENT_APP_NO_MAIN(vex::MainApp);

// ============================================================================
// BULLETPROOF NATIVE ENTRY POINTS
// ============================================================================

#if defined(_WIN32)
#include <windows.h>

// MSVC ANSI CRT Entry Point (Resolves exe_winmain.obj)
extern "C" int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow) {
	// Pass NULL for lpCmdLine; wxWidgets uses GetCommandLine() internally.
	return wxEntry(hInstance, hPrevInstance, NULL, nCmdShow);
}

// MSVC Unicode CRT Entry Point (Resolves exe_wwinmain.obj)
extern "C" int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, wchar_t* lpCmdLine, int nCmdShow) {
	// Pass NULL for lpCmdLine; wxWidgets uses GetCommandLineW() internally.
	return wxEntry(hInstance, hPrevInstance, NULL, nCmdShow);
}

#else
// macOS and Linux Standard Entry Point
int main(int argc, char** argv) {
	return wxEntry(argc, argv);
}
#endif

namespace vex {

	MainApp::MainApp() {
	}

	MainApp::~MainApp() {
	}

	/**
	 * Called upon application startup.
	 *
	 * \return			True if initialization was successful, false otherwise.
	 **/
	bool MainApp::OnInit() {
		if (!wxApp::OnInit()) {
			return false;
		}

		MainFrame* frame = new MainFrame("VEXpression Environment");
		frame->Show(true);

		return true;
	}

}	// namespace vex
