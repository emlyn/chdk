* libptp2-1.1.0-canon-upload.diff
    Added ability to libptp2-1.1.0 to upload files to
    Canon cameras. WARNING: still very buggy - damages
    files, hangs, creates 4G files instead of errors 8) etc.

* gcc-3.4-arm.diff
    Patch for gcc-3.4.6.
    * Changes floating-point behaviour as follows:
	no parameters:	soft-float, VFP byte order
	msoft-float:	soft-float, FPA byte order
	mhard-float:	hard-float, FPA byte order

    from ieee754-df.S:
	For FPA, float words are always big-endian.                                   
	For VFP, floats words follow the memory system mode.                          

    * lib1funcs.asm: do not use PLT (if used relocations can not
    be resolved by WIF ELF loader)

    * build interwork multilib 

    To build a compiler use something similar to
	$ ../gcc-cource/configure --prefix=/opt/arm --target=arm-elf \
	    --enable-multilib --enable-languages=c --enable-clocale=gnu \
	    --with-cpu=arm9
	$ make

