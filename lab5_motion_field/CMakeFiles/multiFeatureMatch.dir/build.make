# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/benjamin/gitRepos/computer_vision/lab5_motion_field

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/benjamin/gitRepos/computer_vision/lab5_motion_field

# Include any dependencies generated for this target.
include CMakeFiles/multiFeatureMatch.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/multiFeatureMatch.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multiFeatureMatch.dir/flags.make

CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o: CMakeFiles/multiFeatureMatch.dir/flags.make
CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o: multi_feature_matching.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/benjamin/gitRepos/computer_vision/lab5_motion_field/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o -c /home/benjamin/gitRepos/computer_vision/lab5_motion_field/multi_feature_matching.cpp

CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/benjamin/gitRepos/computer_vision/lab5_motion_field/multi_feature_matching.cpp > CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.i

CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/benjamin/gitRepos/computer_vision/lab5_motion_field/multi_feature_matching.cpp -o CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.s

CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o.requires:
.PHONY : CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o.requires

CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o.provides: CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o.requires
	$(MAKE) -f CMakeFiles/multiFeatureMatch.dir/build.make CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o.provides.build
.PHONY : CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o.provides

CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o.provides.build: CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o

# Object files for target multiFeatureMatch
multiFeatureMatch_OBJECTS = \
"CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o"

# External object files for target multiFeatureMatch
multiFeatureMatch_EXTERNAL_OBJECTS =

multiFeatureMatch: CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o
multiFeatureMatch: CMakeFiles/multiFeatureMatch.dir/build.make
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_nonfree.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_nonfree.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
multiFeatureMatch: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
multiFeatureMatch: CMakeFiles/multiFeatureMatch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable multiFeatureMatch"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multiFeatureMatch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multiFeatureMatch.dir/build: multiFeatureMatch
.PHONY : CMakeFiles/multiFeatureMatch.dir/build

CMakeFiles/multiFeatureMatch.dir/requires: CMakeFiles/multiFeatureMatch.dir/multi_feature_matching.cpp.o.requires
.PHONY : CMakeFiles/multiFeatureMatch.dir/requires

CMakeFiles/multiFeatureMatch.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multiFeatureMatch.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multiFeatureMatch.dir/clean

CMakeFiles/multiFeatureMatch.dir/depend:
	cd /home/benjamin/gitRepos/computer_vision/lab5_motion_field && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/gitRepos/computer_vision/lab5_motion_field /home/benjamin/gitRepos/computer_vision/lab5_motion_field /home/benjamin/gitRepos/computer_vision/lab5_motion_field /home/benjamin/gitRepos/computer_vision/lab5_motion_field /home/benjamin/gitRepos/computer_vision/lab5_motion_field/CMakeFiles/multiFeatureMatch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multiFeatureMatch.dir/depend

