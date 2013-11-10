What?
=====
Support for encoded QuakeLive pk3 archives in 7-zip.

Anything that 7-zip can do with zip files, this modified version can also do with pk3 files. Both Quake 3 and Quake Live pk3 files can be read and updated. If you create a new pk3 file, it will be Quake Live style. (To instead create a new Quake 3 style pk3: create it as a zip file and then manually change the extension to pk3.)

Credits
=======
The vast majority of the code and functionality are still unmodified 7-zip, from the 7-zip 9.20 codebase. See [7-zip.org](http://7-zip.org/) for anything not specifically pk3-related. Huge thanks to Igor Pavlov for creating 7-zip and making it open source.

The XOR data for dealing with Quake Live pk3s was provided by Luigi Auriemma in the source for his quakelivedec utility. Many thanks to him too!

Building
========
See the [releases](https://github.com/neogeographica/7-zip-pk3/releases) for pre-built installers.

For building things yourself...

I haven't yet changed any of the *.dsp files in this repo, so they won't work. I have just been building with the makefiles and nmake, as follows:

* Open a command shell with the environment set up for either x64 or x86 compilation. (Using compilers from Visual Studio or the Windows SDK.) Note that the 7-zip File Manager does some integration with Windows Explorer. So if you are interested in the File Manager and are targetting a 64-bit OS, then you do need the x64 build.

* cd into to the <code>CPP\7zip</code> subfolder.

* For x86 build, execute this:
  <code>nmake NEW\_COMPILER=1 MY\_STATIC\_LINK=1</code>.
  Deliverables will end up in subfolders named "O".

* Or for x64 build, execute this:
  <code>nmake NEW\_COMPILER=1 MY\_STATIC\_LINK=1 CPU=AMD64 NO\_BUFFEROVERFLOWU=1</code>.
  Deliverables will end up in subfolders named "AMD64".

Misc Notes
==========
A Quake Live pk3 is just a zip archive that has been pushed through an XOR filter. So this modification of 7-zip simply wraps the file input or output stream with the appropriate filter when dealing with a Quake Live pk3, then delegates operations to the existing ziphandler code.

I disabled zip encryption for Quake Live pk3s, as that would make them unreadable. The option to split the archive into parts/volumes is also disabled for pk3 creation. There may be other zip compression options that aren't compatible with Quake Live (or with Quake 3), but I'm not aware of any such issues. So when composing a pk3 file you will have all the other normal options for composing a zip archive.

Some additional discussion and details may be posted at [neogeographica.com](http://neogeographica.com/).
