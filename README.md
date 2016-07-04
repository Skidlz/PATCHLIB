# PATCHLIB
An Alpha Juno editor for DOS (from C Programming for MIDI, ISBN:0934375860)

Requires an MPU-401 compatible card at 0x330 (can be changed in io401.asm).

This was copied from the book instead of the optional floppy disk.
The book has a number of errors and typos. I've corrected what I found and added my own!
I also added some header files so that Eclipse stops compaining about implicit declarations.

The assembly portions are already assembled and ready for linking. They can be re-assembled with MASM or TASM though.
The rest of the files have been compiled with Turbo C, but the book says Microsoft's C compiler will work too.
