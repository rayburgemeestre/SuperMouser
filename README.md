Super Mouser
=============

TODO description



Compiling
------------

SuperMouser is compatible with windows, linux and mac. 



### OSX

Download the latest stable version of wxWidgets.

Compile wxWidgets as documented by wxWidgets, e.g.

    # For Mac OS X 10.6 Snow Leopard or later, with a 64-bit processor, build the
    # Carbon libraries like this

    cd wxWidgets-2.8.12
    mkdir build-carbon-debug
    cd build-carbon-debug
    arch_flags="-arch i386"
    ../configure CFLAGS="$arch_flags" CXXFLAGS="$arch_flags" CPPFLAGS="$arch_flags" LDFLAGS="$arch_flags" OBJCFLAGS="$arch_flags" OBJCXXFLAGS="$arch_flags" --disable-unicode --enable-debug --disable-shared
    make
    cd ..


Open the project in DialogBlocks.

Set the wxWidgets path to the wxWidgets-2.8.12 directory above.

If you press build you'll get an error that wx/setup.h is not found.

To fix this make sure this file exists, you should create a symlink to build-carbon-debug with the correct name:

    cd wxWidgets-2.8.12
    ln -s build-carbon-debug GCCBuildReleaseMac

Now you can build the project.


### CMake (experimental)

Tried it only on linux..

* Please install wxWidgets version 3.0.x, and make sure wx-config --libs for example returns the libs
  (I use dialogblocks to compile wxWidgets, and then symlink to the /usr/bin/wx-config to
   /usr/local/src/wxWidgets-3.0.0/GCCBuildReleaseGTK2Unicode/wx-config)
* cmake .
* make
