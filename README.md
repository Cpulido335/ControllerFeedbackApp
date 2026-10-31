## Controller Feedback App 🎮
<img width="1270" height="710" alt="MyProgram_siYFFdAKtk" src="https://github.com/user-attachments/assets/85fb35e2-d744-408c-a2a2-e8148bf40429" />


ControllerFeedbackApp / ControllerFeedbackGUI is a Windows 10/11 Application for diagnosing USB controller problems, analyzing inputs, and rebinding inputs to VK_Keys (windows virtual keys).
So far it supports Xbox One, Xbox 360, DS4, and DS5 controllers OEM and Knockoffs. It uses SDL3 for its Gamepad API system but the application is all my own C code inside a very basic Win32API window
It is entirely written in C with my own custom draw library. 

It Supports 5 Profiles which can be edited as a text file to rebind keys or key rebinds can be experimented with at runtime. 


## Building from Source (Windows)

ControllerFeedbackApp is written in C and uses **CMake**, **MSYS2 UCRT64 (GCC)**, and **SDL3**.

### Prerequisites

Before building, install:

- [Git](https://git-scm.com/downloads)
- [CMake](https://cmake.org/download/) (version 3.23 or newer; add it to your PATH)
- [MSYS2](https://www.msys2.org/) (install to the default location: `C:\msys64`)

### 1. Install the UCRT64 Toolchain and SDL3

Open the **MSYS2 UCRT64** terminal and run:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-sdl3
```

This installs GCC, GNU Make, the required build tools, and SDL3.

**Important:** Use the **UCRT64** environment, not MINGW64.

### 2. Clone the Repository

Open Command Prompt or PowerShell:

```bash
git clone https://github.com/Cpulido335/ControllerFeedbackApp.git
cd ControllerFeedbackApp
```

### 3. Build the Application

From the project's root directory, run:

```bat
build.bat
```

The script configures CMake using the UCRT64 toolchain and builds the application.

Once compilation finishes, the executable will be located at:

```text
build-ucrt64/MyProgram.exe
```

### 4. Run the Application

From the project's root directory, run:

```bat
build-ucrt64\MyProgram.exe
```


