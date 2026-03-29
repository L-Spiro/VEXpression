# HOW TO BUILD

## Generate a Visual Studio Project
Open a Visual Studio Developer Command Prompt (`Visual Studio` -> `Tools` -> `Command Line` -> `Developer Command Prompt`)

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

To generate a 64-bit project:
```sh
cmake -B build64 -G "Visual Studio 17 2022" -A x64
```

To generate a 32-bit project:
```sh
cmake -B build32 -G "Visual Studio 17 2022" -A Win32
```

`"Visual Studio 18 2026"` is another option.

The `build64` or `build32` directories will contain the generated solution (`VEXpression.sln`).
Once loaded, right-click the `VEXpression` project and select `Set as Startup Project`.

## Generate an Xcode Project (macOS)
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
