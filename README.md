# format144 - Unconditional format of a 3.5" 1.44 MB floppy disk

Unconditionally formats a standard 1.44MB floppy disk in drive A:. Windows XP has a problem formatting demagnetized or corrupt diskettes: its format function only checks for diskette to be readable, and does not perform actual formatting if it is not. Format144 is a simple command-line tool that formats disktettes to the most common standard.

## Compiling with GCC

If you already have Cygwin intalled on your PC, make sure you have
`gcc-core` and `gcc-mingw-core`
packages installed. Unpack the source into a directory on your hard disk.
```
> cd \format144</div>
> gcc -mno-cygwin -o format144.exe format144.c</div>
```
## Compiling with MinGW

```
> \mingw\bin\gcc -o format144.exe format144.c
```

## Compiling with Borland C++ Compiler

Put the bcc32.cfg file into the compiler `bin` directory and edit paths if needed, this way
you won't need to specify include and library paths in the command line.
The included file assumes the compiler is installed in `c:\borland\bcc55`

```
> cd \format144
> bcc32 format144.c
```
