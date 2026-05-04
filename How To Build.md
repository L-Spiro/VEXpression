# HOW TO BUILD

## Generate a Microsoft® Visual Studio® Project

### Prerequisite: Install wxWidgets
This project requires wxWidgets for its graphical interface. On Windows, it is recommended to install it using the `vcpkg` package manager. Because VEXpression compiles using the static C++ runtime (`/MT`), you must install the static triplet for your target architecture.

**If you do not have vcpkg installed:**
1. Open a command prompt and navigate to a root directory (e.g., `cd C:\`).
2. Clone the vcpkg repository: `git clone https://github.com/microsoft/vcpkg.git`
3. Enter the directory: `cd vcpkg`
4. Bootstrap the executable: `.\bootstrap-vcpkg.bat`

Once installed, ensure you are still in the `vcpkg` directory (or add it to your system PATH), and run the following command to download and build wxWidgets.

For a 64-bit build:
```bash
.\vcpkg install wxwidgets:x64-windows-static
```
For a 32-bit build:
```bash
.\vcpkg install wxwidgets:x86-windows-static
```

### Build Instructions
Open a Microsoft® Visual Studio® Developer Command Prompt (`Microsoft® Visual Studio®` -> `Tools` -> `Command Line` -> `Developer Command Prompt`)

Go to the project:
```bash
cd "<path to project>"
```
Example:
```sh
cd "C:\My Projects\ExpressionEvaluator"
```

Remove previous build directories if any:
```sh
rmdir /s /q build
rmdir /s /q build64
rmdir /s /q build32
```

To generate a 64-bit project (replace `<path_to_vcpkg>` with your actual vcpkg installation directory):
```sh
cmake -B build64 -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE="<path_to_vcpkg>\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-static
```

To generate a 32-bit project (replace `<path_to_vcpkg>` with your actual vcpkg installation directory):
```sh
cmake -B build32 -G "Visual Studio 17 2022" -A Win32 -DCMAKE_TOOLCHAIN_FILE="<path_to_vcpkg>\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows-static
```

`"Visual Studio 18 2026"` is another option, or you may select a different version of Microsoft® Visual Studio®.

The `build64` or `build32` directories will contain the generated solution (`VEXpression.sln`).
Once loaded, right-click the `VEXpression` project and select `Set as Startup Project`.

## Generate an Xcode Project (macOS)

### Prerequisite: Install wxWidgets
Before generating the project, ensure you have installed wxWidgets on your macOS system. The easiest way to do this is using the Homebrew package manager:
```bash
brew install wxwidgets
```

### Build Instructions
Open the Terminal application.

Go to the project:
```bash
cd "<path to project>"
```

Remove previous build directories if any:

```bash
rm -rf build_xcode
```
To generate the Xcode project:

```bash
cmake -B build_xcode -G Xcode
```
The `build_xcode` directory will contain the generated project (`VEXpression.xcodeproj`).
Open this file in Xcode. At the top of the window, ensure the `VEXpression` scheme is selected next to the run button before building.

## Build on Linux (Command Line)

### Prerequisite: Install wxWidgets
Before configuring the build, you must install the required wxWidgets GTK and Scintilla (STC) development packages. On Debian/Ubuntu-based distributions, you can install them via APT:
```bash
sudo apt-get update
sudo apt-get install libwxgtk3.2-dev libwxgtk-stc3.2-dev
```

### Build Instructions
Open your terminal.

Go to the project:

```bash
cd "<path to project>"
```
Remove previous build directories if any:

```bash
rm -rf build
```
To configure the build files (this defaults to standard Makefiles):

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
```
To compile the project using all available CPU cores:

```bash
cmake --build build -j $(nproc)
```
Once compiled successfully, you can run the executable directly from the build directory:

```bash
./build/VEXpression
```
