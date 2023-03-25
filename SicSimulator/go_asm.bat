copy %1 SRCFILE
sicasm
@copy LISFILE %1.lst
@copy OBJFILE %1.obj
@del INTFILE
@del OBJFILE
@del LISFILE
dir/od  
