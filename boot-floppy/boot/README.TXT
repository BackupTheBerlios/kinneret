grubinstall
-----------

Purpose:  allow GRUB to be booted from NT/2K/XP
-------

	This tool modifies the GRUB stage1 and stage2 image files
	located on an NTFS or FAT volume, to make them bootable 
	by NTLDR.


Author:
-------
	lode_leroy@hotmail.com


Acknowledgements:
-----------------
	* The AUTHORS of GNU GRUB 0.93 for creating GRUB
	* Samuel Leo for writing fsys_ntfs.c
	* Leonid Lisovskiy for writing fsys_iso9660.c
	* Gary Ng for updating the GRUB makefiles for NTFS+ISO9660
	* Chris Semler and Tobias Svensson for testing


Limitations:
------------
     booting OS'es from NTLDR requires stage1 to be on the same partition
     as NTLDR itself.

     Make sure that stage1 and stage2 are NOT on a compressed volume, 
     and that the files are NOT compressed by Windows.


Usage:
------
		let's say C: is the first partition on the first harddisk
		hence (hd0,0) is the GRUB name of this partition
		and C:\boot\stage1 is the NT name of the boot file

		* To make the files stage1 and stage2 bootable from NTLDR:

		C:\> grubinstall -d (hd0,0) -1 C:\boot\stage1 -2 C:\boot\stage2

		  When stage1, stage2, menu.lst are in C:\, use the following

		C:\> grubinstall -d C:

		* To make the installer detect the install location itself:

		C:\> grubinstall -a -1 C:\boot\stage1 -2 C:\boot\stage2

		* To make a boot floppy in A: (B: is not supported)

		C:\> grubinstall -b -1 C:\boot\stage1 -2 C:\boot\stage2


Changes:
--------
0.3: 
	 - first released version 
0.4: 
	 - added experimental FAT support (not released)
     - added support for DOS partition names 
           (ie. "C:" instead of "(hd0,0)")
           this works only on windows XP
0.5: 
	 - fixed bug with NTFS: hardcoded partition offset and clustersize
	replaced by information exposed by fsys_ntfs.c
     - fixed FAT support
     - added support for DOS path names 
       (ie. C:\boot\stage1 instead of "C:/boot/stage1");
     - code cleanup
0.6:
	 - removal of quotes from command line
	 - support for writing to a diskette	
0.7:
	 - bugfixes for win32_filepos and current_pos
	 - corrected debug info: use format %I64u (MSVCRT.DLL) instead of %llu (glibc)
	 - added option to write to a bootdisk image to a file

0.8:
	 - added autodetect '-a' command line option to probe disks+partitions

0.9:
	 - renamed ntfsinstall to grubinstall
	 - improved support for DOS names
	        grubinstall -d C:
         - somewhat improved (?) error messages 
	 - added an alternate grub name option

