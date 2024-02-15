# Compilation Guide for Windows

This guide provides instructions on how to set up your Windows environment for compiling projects using `make` and Microsoft Visual Studio's `cl.exe`.

## Compilation with only msbuild tools

Run the `build_without_makefile.bat`

## Requirements

### Installing Chocolatey

Chocolatey is a Windows package manager that simplifies the installation of software and tools. To install Chocolatey, run the following command in an elevated PowerShell prompt:

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```

### Installing Make

After installing Chocolatey, you can easily install GNU Make, a tool which controls the generation of executables and other non-source files of a program from the program's source files. To install `make`, run the following command in PowerShell or CMD:

```powershell
choco install make
```

## Compiling with CL (Visual Studio Compiler)

To compile projects that require Visual Studio's `cl.exe`, a batch script is used to set up the environment properly.

### Batch Script Setup

The batch script calls `vcvars64.bat` to ensure all Visual Studio command-line tools are available in the PATH, and then it executes `make`. This setup enables the compilation of projects with `cl.exe`.

### Steps to Compile

1. **Create a Batch File**: Create a `build.bat` file in your project directory with the necessary commands to set up the environment and invoke `make`.

```powershell
@echo off
CALL "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
make %*
```

2. **Compile the Project**: Execute the batch script by typing `build.bat` in the command prompt within your project directory. This compiles your project into a Windows executable.

```powershell
build.bat
```

## Cleaning Up

- **Delete Object Files**: To clean up object files generated during the compilation process, run:

    ```
    make clean
    ```

- **Delete Object Files and Executable**: To remove both object files and the generated executable, ensuring a clean start, run:

    ```
    make fclean
    ```
