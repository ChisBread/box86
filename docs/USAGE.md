
Usage
----

There are many environment variables to control Box86 behaviour. 
Env. var with * can also be put inside box64rc files

#### BOX86_LOG *
Controls the Verbosity level of the logs
 * 0: NONE : No message (except some fatal error). (Default.)
 * 1: INFO : Show some minimum log (Example: librairies not found)
 * 2: DEBUG : Details a lot of stuff (Example: relocations or functions called).
 * 3: DUMP : All DEBUG plus DUMP of all ELF Info (so same as `BOX86_LOG=2 BOX86_DUMP=1`)

#### BOX86_DUMP *
Controls the Dump of elf content
 * 0: No dump of elf information (Default)
 * 1: Dump elf sections and relocations and other information (also active if using `BOX86_LOG=3`)

#### BOX86_ROLLING_LOG *
Show last few wrapped function call when a Signal is caught
 * 0: No last function call printed (Default.)
 * 1: Last 16 wrapped functions calls printed when a signal is printed. Incompatible with BOX86_LOG>1 (may need BOX86_SHOWSEGV=1 also)
 * N: Last N wrapped functions calls printed when a signal is printed. Incompatible with BOX86_LOG>1 (may need BOX86_SHOWSEGV=1 also)

#### BOX86_NOBANNER
Disables Box86 printing its version and build
 * 0 : Enable printing its banner. (Default.)
 * 1 : Disable printing its banner. 

#### BOX86_LD_LIBRARY_PATH *
Path to look for x86 libraries. Default is current folder and `lib` in current folder.
Also, `/usr/lib/i386-linux-gnu` and `/lib/i386-linux-gnu` are added if they exist.

#### BOX86_PATH *
Path to look for x86 executable. Default is current folder and `bin` in current folder.

#### BOX86_DLSYM_ERROR *
Enables/Disables the logging of `dlsym` errors.
 * 0 : Don't log `dlsym` errors. (Default.)
 * 1 : Log dlsym errors.

#### BOX86_TRACE_FILE *
Send all log and trace to a file instead of `stdout`
Also, if name contains `%pid` then this is replaced by the actual PID of box86 instance
Use `stderr` to use this instead of default `stdout` 

#### BOX86_TRACE *
Only on build with trace enabled. Trace allow the logging of all instruction executed, along with register dump
 * 0 : No trace. (Default.) 
 * 1 : Trace enabled. Trace start after the initialisation of all depending libraries is done.
 * symbolname : Trace only `symbolname` (trace is disable if the symbol is not found).
 * 0xXXXXXXX-0xYYYYYYY : Trace only between the 2 addresses.

#### BOX86_TRACE_INIT *
Use BOX86_TRACE_INIT instead of BOX_TRACE to start trace before the initialisation of libraries and the running program
 * 0 : No trace. (Default.)
 * 1 : Trace enabled. The trace start with the initialisation of all depending libraries is done.

#### BOX86_TRACE_START *
Only on builds with trace enabled.
 * NNNNNNN : Start trace only after NNNNNNNN opcode execute (number is an `uint64_t`).

#### BOX86_TRACE_XMM *
Only on builds with trace enabled.
 * 0 : The XMM (i.e. SSE/SSE2) register will not be logged with the general and x86 registers. (Default.)
 * 1 : Dump the XMM registers.

#### BOX86_TRACE_EMM *
Only on builds with trace enabled.
 * 0 : The EMM (i.e. MMX) register will not be logged with the general and x86 registers. (Default.)
 * 1 : Dump the EMM registers.

#### BOX86_LOAD_ADDR *
Try to load at 0xXXXXXX main binary (if binary is a PIE)
 * 0xXXXXXXXX : The load address . (Only active on PIE programs.)

#### BOX86_NOSIGSEGV *
Disable handling of SigSEGV. (Very useful for debugging.)
 * 0 : Let the x86 program set sighandler for SEGV (Default.)
 * 1 : Disable the handling of SigSEGV.

#### BOX86_NOSIGILL *
Disable handling of SigILL (to ease debugging mainly).
 * 0 : Let x86 program set sighandler for Illegal Instruction
 * 1 : Disables the handling of SigILL 

#### BOX86_X11COLOR16 *
PANDORA only: Try converting X11 color from 32 bits to 16 bits (to avoid light green on light cyan windows).
 * 0 : Don't touch X11 colors. (Default.)
 * 1 : Change colors arguments in XSetForeground, XSetBackground and XCreateGC.

#### BOX86_X11THREADS *
Call XInitThreads when loading X11. (This is mostly for old Loki games with the Loki_Compat library.)
 * 0 : Don't force call XInitThreads. (Default.)
 * 1 : Call XInitThreads as soon as libX11 is loaded.

#### BOX86_X11GLX *
Force libX11's GLX extension to be present.
* 0 : Do not force libX11's GLX extension to be present. 
* 1 : GLX will always be present when using XQueryExtension. (Default.)

#### BOX86_DYNAREC_DUMP *
Enables/disables Box86's Dynarec's dump.
 * 0 : Disable Dynarec's blocks dump. (Default.)
 * 1 : Enable Dynarec's blocks dump.
 * 2 : Enable Dynarec's blocks dump with some colors.

#### BOX86_DYNAREC_LOG *
Set the level of DynaRec's logs.
 * 0 : NONE : No Logs for DynaRec. (Default.)
 * 1 :INFO : Minimum Dynarec Logs (only unimplemented OpCode).
 * 2 : DEBUG : Debug Logs for Dynarec (with details on block created / executed).
 * 3 : VERBOSE : All of the above plus more.

#### BOX86_DYNAREC *
Enables/Disables Box86's Dynarec.
 * 0 : Disables Dynarec.
 * 1 : Enable Dynarec. (Default.)

#### BOX86_DYNAREC_TRACE *
Enables/Disables trace for generated code.
 * 0 : Disable trace for generated code. (Default.)
 * 1 : Enable trace for generated code (like regular Trace, this will slow down the program a lot and generate huge logs).

#### BOX86_NODYNAREC *
Forbid dynablock creation in the interval specified (helpfull for debugging behaviour difference between Dynarec and Interpretor)
 * 0xXXXXXXXX-0xYYYYYYYY : define the interval where dynablock cannot start (inclusive-exclusive)

#### BOX86_DYNAREC_BIGBLOCK *
Enables/Disables Box86's Dynarec building BigBlock.
 * 0 : Don't try to build block as big as possible (can help program using lots of thread and a JIT, like C#/Unity) (Default when libmonobdwgc-2.0.so is loaded)
 * 1 : Build Dynarec block as big as possible (Default.)
 * 2 : Build Dynarec block bigger (don't stop when block overlaps)

#### BOX86_DYNAREC_STRONGMEM *
Enable/Disable simulation of Strong Memory model
* 0 : Don't try anything special (Default.)
* 1 : Enable some Memory Barrier when reading from memory (on some MOV opcode) to simulate Strong Memory Model while trying to limit performance impact (Default when libmonobdwgc-2.0.so is loaded)
* 2 : Enable some Memory Barrier when reading from memory (on some MOV opcode) to simulate Strong Memory Model

#### BOX86_DYNAREC_X87DOUBLE *
Force the use of Double for x87 emulation
* 0 : Try to use float when possible for x87 emulation (faster, Default)
* 1 : Only use Double for x87 emulation (slower, may be needed for some specific games, like Crysis were it's enable automatically)

#### BOX86_DYNAREC_FASTNAN *
Enable/Disable generation of -NAN
* 0 : Generate -NAN like on x86 (slower, more x86 accurate)
* 1 : Don't do anything special with NAN, to go as fast as possible (Default)

#### BOX86_DYNAREC_SAFEFLAGS *
Handling of flags on CALL/RET opcodes
* 0 : Treat CALL/RET as if it never needs any flags (faster but may have side-effects)
* 1 : most of RET will need flags, most of CALLS will not (Default)
* 2 : All CALL/RET will need flags (slower, but might be needed. Automatically enabled for Vara.exe)

#### BOX86_DYNAREC_HOTPAGE *
Handling of HotPage (Page beeing both executed and writen)
* 0 : Don't track hotpage
* 1-255 : Trak HotPage, and disable execution of a page beeing writen for N attempts (default is 16)

#### BOX86_DYNAREC_BLEEDING_EDGE *
Detect MonoBleedingEdge and apply conservative settings
* 0 : Don't detect MonoBleedingEdge
* 1 : Detect MonoBleedingEdge, and apply BIGBLOCK=0 STRONGMEM=1 if detected (Default)

#### BOX86_LIBGL *
 * libXXXX set the name for libGL (defaults to libGL.so.1).
 * /PATH/TO/libGLXXX : Sets the name and path for libGL
 You can also use SDL_VIDEO_GL_DRIVER

#### BOX86_LD_PRELOAD
 * XXXX[:YYYYY] force loading XXXX (and YYYY...) libraries with the binary
 PreLoaded libs can be emulated or native, and are treated the same way as if they were comming from the binary
 
#### BOX86_EMULATED_LIBS *
 * XXXX[:YYYYY] force lib XXXX (and YYYY...) to be emulated (and not wrapped)
Some games uses an old version of some libraries, with an ABI incompatible with native version.
Note that LittleInferno for example is auto detected, and libvorbis.so.0 is automatical added to emulated libs, and same for Don't Starve (and Together / Server variant) that use an old SDL2 too

#### BOX86_ALLOWMISSING_LIBS *
Allow Box86 to continue even if a library is missing (renamed from BOX86_ALLOWMISSINGLIBS). 
 * 0 : Box86 will stop if a library cannot be loaded. (Default.)
 * 1 : Continue even if a needed library cannot be loaded. Unadvised, this will, in most cases, crash later on.

#### BOX86_ALLOWMISSING_SYMBOLS *
Allow dlopen with RTLD_NOW flag to not resolve all symbols. 
 * 0 : Box86 will stop if a library have unresolved symbols. (Default.)
 * 1 : Continue even if a needed library have unresolved symbols (like symbols not yet wrapped).

#### BOX86_PREFER_WRAPPED *
Box86 will use wrapped libs even if the lib is specified with absolute path
 * 0 : Try to use emulated libs when they are defined with absolute path  (Default.)
 * 1 : Use Wrapped native libs even if path is absolute

#### BOX86_PREFER_EMULATED *
Box86 will prefer emulated libs first (execpt for glibc, alsa, pulse, GL, vulkan and X11
 * 0 : Native libs are prefered (Default.)
 * 1 : Emulated libs are prefered (Default for program running inside pressure-vessel)

#### BOX86_NOPULSE *
Disables the load of pulseaudio libraries.
 * 0 : Load pulseaudio libraries if found. (Default.)
 * 1 : Disables the load of pulse audio libraries (libpulse and libpulse-simple), both the native library and the x86 library

#### BOX86_NOGTK *
Disables the loading of wrapped GTK libraries.
 * 0 : Load wrapped GTK libraries if found. (Default.)
 * 1 : Disables loading wrapped GTK libraries.

#### BOX86_NOVULKAN *
Disables the load of vulkan libraries.
 * 0 : Load vulkan libraries if found.
 * 1 : Disables the load of vulkan libraries, both the native and the i386 version (can be useful on Pi4, where the vulkan driver is not quite there yet.)

#### BOX86_ENV
 * XXX=yyyy
 will add XXX=yyyy env. var.

#### BOX86_ENV1
 * XXX=yyyy
 will add XXX=yyyy env. var. and continue with BOX86_ENV2 ... until var doesn't exist

#### BOX86_FIX_64BIT_INODES *
Fix/Don't fix 64bit inodes
 * 0 : Don't fix 64bit inodes. (Default.)
 * 1 : Fix 64bit inodes. Helps when running on Filesystems with 64bit inodes. Is useful when a program uses API functions which doesn't support it and the program doesn't use inodes information.

#### BOX86_SHOWSEGV *
Show Segfault signal even if a signal handler is present
 * 0 : Don't force segfault details when a signal handler is install (Default, to limit message spamming)
 * 1 : Show segfault details

#### BOX86_SHOWBT *
Show a backtrace (native and emulated) on Signal
 * 0 : Don't show any backtrace (Default.)
 * 1 : Show native backtrace when a signal is dumped (not available on Andoid build)

#### BOX86_BASH *
Define x86 bash to launch script
 * yyyy
Will use yyyy as x86 bash to launch script. yyyy needs to be a full path to a valid x86 version of bash. Note that is Box64 is available, an x86_64 version of bash can also be used. Also, BOX64_BASH env. var. will also be read if BOX86_BASH is not defined.

#### BOX86_BOX64
Define where to find box64 binary
 * yyyy
Will use yyyy as x86_64 interpretor, to launch x64_64 binaries

#### BOX86_JITGDB *

 * 0 : Just print the Segfault message on segfault (default)
 * 1 : Launch `gdb` when a segfault, bus error or illegal instruction signal is trapped, attached to the offending process and go in an endless loop, waiting.
 When in gdb, you need to find the correct thread yourself (the one with `my_box86signalhandler` in is stack)
 then probably need to `finish` 1 or 2 functions (inside `usleep(..)`) and then you'll be in `my_box86signalhandler`, 
 just before the printf of the Segfault message. Then simply 
 `set waiting=0` to exit the infinite loop.
 * 2 : Launch `gdbserver` when a segfault, bus error or illegal instruction signal is trapped, attached to the offending process, and go in an endless loop, waiting.
 Use `gdb /PATH/TO/box86` and then `target remote 127.0.0.1:1234` to connect to the gdbserver (or use actual IP if not on the machine). After that, the procedure is the same as with ` BOX86_JITGDB=1`.
 This mode can be usefullwhen programs redirect all console output to a file (like Unity3D Games)

#### BOX86_NORCFILES
If the env var exist, no rc files (like /etc/box86.box86rc and ~/.box86rc) will be loaded
