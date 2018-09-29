masm /c /Zi /Zd %1.asm
masm /c /Zi /Zd x86rtld.asm,x86rtl.obj
link /CODEVIEW %1.obj x86rtl.obj,%1.exe,,,,


