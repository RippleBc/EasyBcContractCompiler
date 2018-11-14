0x00, 'IBAND', 2, 1
0x01, 'IBOR', 2, 1
0x03, 'IXOR', 2, 1
0x04, 'UIBAND', 2, 1
0x05, 'UIBOR', 2, 1
0x06, 'UIXOR', 2, 1
0x07, 'RBAND', 2, 1
0x08, 'RBOR', 2, 1
0x09, 'RXOR', 2, 1
0x0a, 'CBAND', 2, 1
0x0b, 'CBOR', 2, 1
0x0c, 'CXOR', 2, 1
0x0d, 'UCBAND', 2, 1
0x0e, 'UCBOR', 2, 1
0x0f, 'UCXOR', 2, 1

0x10, 'LSH', 2, 1
0x11, 'RSH', 2, 1

0x12, 'IADD', 2, 1
0x13, 'ISUB', 2, 1
0x14, 'IMUL', 2, 1
0x15, 'IDIV', 2, 1
0x16, 'UIADD', 2, 1
0x17, 'UISUB', 2, 1
0x18, 'UIMUL', 2, 1
0x19, 'UIDIV', 2, 1
0x1a, 'RADD', 2, 1
0x1b, 'RSUB', 2, 1
0x1c, 'RMUL', 2, 1
0x1d, 'RDIV', 2, 1
0x1e, 'UCADD', 2, 1
0x1f, 'UCSUB', 2, 1
0x20, 'UCMUL', 2, 1
0x21, 'UCDIV', 2, 1

0x22, 'MOD', 2, 1

0x23, 'AND', 2, 1
0x24, 'OR', 2, 1
0x25, 'IEQ', 2, 1
0x26, 'INE', 2, 1
0x27, 'IGE', 2, 1
0x28, 'IGT', 2, 1
0x29, 'ILE', 2, 1
0x2a, 'ILT', 2, 1
0x2b, 'UIEQ', 2, 1
0x2c, 'UINE', 2, 1
0x2d, 'UIGE', 2, 1
0x2e, 'UIGT', 2, 1
0x2f, 'UILE', 2, 1
0x30, 'UILT', 2, 1
0x31, 'REQ', 2, 1
0x32, 'RNE', 2, 1
0x33, 'RGE', 2, 1
0x34, 'RGT', 2, 1
0x35, 'RLE', 2, 1
0x36, 'RLT', 2, 1
0x37, 'CEQ', 2, 1
0x38, 'CNE', 2, 1
0x39, 'CGE', 2, 1
0x3a, 'CGT', 2, 1
0x3b, 'CLE', 2, 1
0x3c, 'CLT', 2, 1
0x3d, 'UCEQ', 2, 1
0x3e, 'UCNE', 2, 1
0x3f, 'UCGE', 2, 1
0x40, 'UCGT', 2, 1
0x41, 'UCLE', 2, 1
0x42, 'UCLT', 2, 1

0X12, 'INEG', 1, 1
0X12, 'FNEG', 1, 1

0x13, 'NOT', 1, 1

0x14, 'IBCOM', 1, 1
0x15, 'ICVF', 1, 1
0x16, 'ICVI', 1, 1
0x17, 'ICVB', 1, 1
0x18, 'ICVUI', 1, 1
0x19, 'ICVUC', 1, 1
0x14, 'UIBCOM', 1, 1
0x15, 'UICVF', 1, 1
0x16, 'UICVI', 1, 1
0x17, 'UICVB', 1, 1
0x18, 'UICVUI', 1, 1
0x19, 'UICVUC', 1, 1
0x14, 'RBCOM', 1, 1
0x15, 'RCVF', 1, 1
0x16, 'RCVI', 1, 1
0x17, 'RCVB', 1, 1
0x18, 'RCVUI', 1, 1
0x19, 'RCVUC', 1, 1
0x14, 'CBCOM', 1, 1
0x15, 'CCVF', 1, 1
0x16, 'CCVI', 1, 1
0x17, 'CCVB', 1, 1
0x18, 'CCVUI', 1, 1
0x19, 'CCVUC', 1, 1
0x14, 'UCBCOM', 1, 1
0x15, 'UCCVF', 1, 1
0x16, 'UCCVI', 1, 1
0x17, 'UCCVB', 1, 1
0x18, 'UCCVUI', 1, 1
0x19, 'UCCVUC', 1, 1
0x1a, 'IINCR', 1, 1
0x1b, 'IDECR', 1, 1
0x1c, 'UIINCR', 1, 1
0x1d, 'UIDECR', 1, 1
0x1e, 'RINCR', 1, 1
0x1f, 'RDECR', 1, 1
0x20, 'CINCR', 1, 1
0x21, 'CDECR', 1, 1
0x22, 'UCINCR', 1, 1
0x23, 'UCDECR', 1, 1


0x30, 'JUMP', 1, 0
0x31, 'COND', 2, 0

0x40, 'PUSH', 0, 1
0x41, 'POP', 1, 0

0x42, 'ASSIGN_GLOBAL', 2, 0
0x43, 'LOAD_GLOBAL', 1, 1
0x44, 'ASSIGN_CALL', 2, 0
0x45, 'LOAD_CALL', 1, 1
0x46, 'PUSH_CALL', 1, 0
0x47, 'POP_CALL', 1, 0
0X48, 'TOP_CALL', 0, 1

0x50, 'READLN', 1, 0
0x51, 'WRITELN', 1, 0
