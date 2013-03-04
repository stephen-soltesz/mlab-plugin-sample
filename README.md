mlab-plugin-sample
==================

firebreath depends on cmake, git, and a standard development environment with
gcc/g++/make and development headers installed.

After initial checkout run:

    git submodule update --init --recursive

Then generate a local build directory:

    ./firebreath/prepmake.sh MLabPlugin build

The build is separate from the sources in MLabPlugin, and you should re-run
prepmake.sh after changes or updates to source in MLabPlugin.

    cd build
    make

The initial build will take a while b/c all the dependencies are built.  Future
iteration on changes to MLabPlugin will be much faster. And, cmake helps make
that easy.

If you receive a build error like:

    project dir: /root/mlab-plugin-sample/MLabPlugin
    Single project: /root/mlab-plugin-sample/MLabPlugin
    CMake Error at src/libs/curl/CMakeLists.txt:19 (include):
      include could not find load file:

        FindCurl

Then this is probably b/c your version of cmake-data names the module FindCURL
instead of the referenced FindCurl.  A better work-around is unknown, but
manually updating the CMakeLists.txt with the correct name allows the prep to
finish.
