# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio

# Include any dependencies generated for this target.
include example\CMakeFiles\example1.dir\depend.make
# Include the progress variables for this target.
include example\CMakeFiles\example1.dir\progress.make

# Include the compile flags for this target's objects.
include example\CMakeFiles\example1.dir\flags.make

example\CMakeFiles\example1.dir\example1.cpp.obj: example\CMakeFiles\example1.dir\flags.make
example\CMakeFiles\example1.dir\example1.cpp.obj: ..\example\example1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/example1.dir/example1.cpp.obj"
	cd C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio\example
	C:\PROGRA~2\MICROS~1\2017\BUILDT~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\example1.dir\example1.cpp.obj /FdCMakeFiles\example1.dir\ /FS -c C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\example\example1.cpp
<<
	cd C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio

example\CMakeFiles\example1.dir\example1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example1.dir/example1.cpp.i"
	cd C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio\example
	C:\PROGRA~2\MICROS~1\2017\BUILDT~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\example1.dir\example1.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\example\example1.cpp
<<
	cd C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio

example\CMakeFiles\example1.dir\example1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example1.dir/example1.cpp.s"
	cd C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio\example
	C:\PROGRA~2\MICROS~1\2017\BUILDT~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\example1.dir\example1.cpp.s /c C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\example\example1.cpp
<<
	cd C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio

# Object files for target example1
example1_OBJECTS = \
"CMakeFiles\example1.dir\example1.cpp.obj"

# External object files for target example1
example1_EXTERNAL_OBJECTS =

example\example1.exe: example\CMakeFiles\example1.dir\example1.cpp.obj
example\example1.exe: example\CMakeFiles\example1.dir\build.make
example\example1.exe: bayesian_inference\bayinf.lib
example\example1.exe: example\CMakeFiles\example1.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable example1.exe"
	cd C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio\example
	"C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\example1.dir --rc=rc --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100177~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~1\2017\BUILDT~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\example1.dir\objects1.rsp @<<
 /out:example1.exe /implib:example1.lib /pdb:C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio\example\example1.pdb /version:0.0 /machine:X86 /INCREMENTAL:NO /subsystem:console  ..\bayesian_inference\bayinf.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	cd C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio

# Rule to build all files generated by this target.
example\CMakeFiles\example1.dir\build: example\example1.exe
.PHONY : example\CMakeFiles\example1.dir\build

example\CMakeFiles\example1.dir\clean:
	cd C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio\example
	$(CMAKE_COMMAND) -P CMakeFiles\example1.dir\cmake_clean.cmake
	cd C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio
.PHONY : example\CMakeFiles\example1.dir\clean

example\CMakeFiles\example1.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\example C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio\example C:\Users\Sax\Desktop\POLI\Programmazione_di_sistema\Progetto\BayesianNetworks\cmake-build-release-visual-studio\example\CMakeFiles\example1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : example\CMakeFiles\example1.dir\depend
