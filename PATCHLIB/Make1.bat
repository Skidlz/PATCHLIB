lastdrive = z
subst L: C:\tc\lib
c:\tc\tcc -c chain.c
c:\tc\tcc -c patched.c
c:\tc\tcc -c patchlib.c
c:\tc\tcc -c patchlod.c
c:\tc\tcc -c patchprt.c
c:\tc\tcc -c patchut1.c
c:\tc\tcc -c patchut2.c
c:\tc\tcc -c writscrn.c

c:\tc\tlink patchlib chain patched patchlod patchprt patchut1 patchut2 writscrn io401 bioscall C:\tc\lib\c0s,,, C:\tc\lib\cs