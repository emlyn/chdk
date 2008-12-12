
static FuncSig func_sig_SleepTask_1[] = {g
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   2, 0xe59f0038, 0xfdffffff }, // ldr:4:0xE59F0038g
	{   3, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   4, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   5, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   6, 0xc59f1048, 0xfdffffff }, // ldr:4:0xC59F1048g
	{   7, 0xc08f002c, 0xfdffffff }, // add:6:0xC28F002Cg
	{   8, 0xcb000000, 0xff000000 }, // b, bl:3:0xCBFFCA68g
	{   9, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000g
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001g
	{  11, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  13, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004g
	{  14, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFDE5g
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFA207g
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFF8g
	{  19, 0x000001f9, 0xfdffffff }, // and:6:0x000001F9g
	{  22, 0x00000000, 0xfdffffff }, // and:6:0x00000000g
	{  23, 0x00001cc4, 0xfdffffff }, // and:6:0x00001CC4g
	{  24, 0x00001cc8, 0xfdffffff }, // and:6:0x00001CC8g
	{  25, 0x3b000000, 0xff000000 }, // b, bl:3:0x3B9ACA00g
	{  26, 0x000001ca, 0xfdffffff }, // and:6:0x000001CAg
	{  27, 0xe51f002c, 0xfdffffff }, // ldr:4:0xE51F002Cg
	{  29, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  30, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  31, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{ -1, -1, -1 },g
	/* 26/32 */g
};g
g
static FuncSig func_sig_CreateTask_1[] = {g
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   2, 0xe59f0218, 0xfdffffff }, // ldr:4:0xE59F0218g
	{   3, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001g
	{   4, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   5, 0xe59d8028, 0xfdffffff }, // ldr:4:0xE59D8028g
	{   6, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   7, 0xe1a07003, 0xfdffffff }, // mov:6:0xE1A07003g
	{   8, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   9, 0xc1a010a3, 0xfdffffff }, // mov:6:0xC3A010A3g
	{  10, 0xc08f0f7f, 0xfdffffff }, // add:6:0xC28F0F7Fg
	{  11, 0xe1a05002, 0xfdffffff }, // mov:6:0xE1A05002g
	{  12, 0xcb000000, 0xff000000 }, // b, bl:3:0xCB000128g
	{  13, 0xe59f11fc, 0xfdffffff }, // ldr:4:0xE59F11FCg
	{  14, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000g
	{  15, 0x05914000, 0xfdffffff }, // ldr:4:0x05914000g
	{  16, 0xe0460001, 0xfdffffff }, // sub:6:0xE2460001g
	{  17, 0xe1500020, 0xfdffffff }, // cmp:7:0xE3500020g
	{  18, 0x2a000000, 0xff000000 }, // b, bl:3:0x2A000001g
	{  19, 0xe1570000, 0xfdffffff }, // cmp:7:0xE3570000g
	{  20, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001g
	{  21, 0xe1a00003, 0xfdffffff }, // mov:6:0xE3A00003g
	{  23, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000g
	{  24, 0x05915004, 0xfdffffff }, // ldr:4:0x05915004g
	{  25, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  27, 0xe1a01008, 0xfdffffff }, // mov:6:0xE1A01008g
	{  28, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007g
	{  29, 0xe1a03005, 0xfdffffff }, // mov:6:0xE1A03005g
	{  30, 0xe58d6000, 0xfdffffff }, // str:4:0xE58D6000g
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD7C9g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_ExitTask_1[] = {g
	{   0, 0xe51f0070, 0xfdffffff }, // ldr:4:0xE51F0070g
	{   2, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   3, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   4, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   5, 0xc59f1028, 0xfdffffff }, // ldr:4:0xC59F1028g
	{   6, 0xc04f0084, 0xfdffffff }, // sub:6:0xC24F0084g
	{   7, 0xcb000000, 0xff000000 }, // b, bl:3:0xCB000089g
	{   8, 0xe51f007c, 0xfdffffff }, // ldr:4:0xE51F007Cg
	{   9, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  11, 0xc1a01f87, 0xfdffffff }, // mov:6:0xC3A01F87g
	{  12, 0xc04f009c, 0xfdffffff }, // sub:6:0xC24F009Cg
	{  13, 0xcb000000, 0xff000000 }, // b, bl:3:0xCB000083g
	{  16, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFD76Cg
	{  17, 0x00000219, 0xfdffffff }, // and:6:0x00000219g
	{  18, 0xe1a0c003, 0xfdffffff }, // mov:6:0xE1A0C003g
	{  20, 0xe59d3010, 0xfdffffff }, // ldr:4:0xE59D3010g
	{  21, 0xe58d3000, 0xfdffffff }, // str:4:0xE58D3000g
	{  22, 0xe1a0300c, 0xfdffffff }, // mov:6:0xE1A0300Cg
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF43g
	{  24, 0xe1500005, 0xfdffffff }, // cmp:7:0xE3500005g
	{  25, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  26, 0x008f0f72, 0xfdffffff }, // add:6:0x028F0F72g
	{  27, 0x01a01013, 0xfdffffff }, // mov:6:0x03A01013g
	{  28, 0x0b000000, 0xff000000 }, // b, bl:3:0x0B000074g
	{  29, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{ -1, -1, -1 },g
	/* 26/32 */g
};g
g
static FuncSig func_sig_AllocateMemory_1[] = {g
	{   0, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   1, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF90666g
	{   3, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF90631g
	{   5, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{   7, 0xe0800004, 0xfdffffff }, // add:6:0xE2800004g
	{   8, 0xe5101004, 0xfdffffff }, // ldr:4:0xE5101004g
	{   9, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  10, 0xe5810000, 0xfdffffff }, // str:4:0xE5810000g
	{  11, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  13, 0x0000d71c, 0xfdffffff }, // and:6:0x0000D71Cg
	{  14, 0x0000000a, 0xfdffffff }, // and:6:0x0000000Ag
	{  16, 0x000a5838, 0xfdffffff }, // and:6:0x000A5838g
	{  17, 0x00000a0d, 0xfdffffff }, // and:6:0x00000A0Dg
	{  22, 0x00000020, 0xfdffffff }, // and:6:0x00000020g
	{  25, 0x00000020, 0xfdffffff }, // and:6:0x00000020g
	{  27, 0x00000020, 0xfdffffff }, // and:6:0x00000020g
	{  29, 0x00000020, 0xfdffffff }, // and:6:0x00000020g
	{  31, 0x00000020, 0xfdffffff }, // and:6:0x00000020g
	{ -1, -1, -1 },g
	/* 19/32 */g
};g
g
static FuncSig func_sig_ExecuteEventProcedure_1[] = {g
	{   2, 0xe59f00f8, 0xfdffffff }, // ldr:4:0xE59F00F8g
	{   3, 0xe59d1010, 0xfdffffff }, // ldr:4:0xE59D1010g
	{   4, 0xe0404014, 0xfdffffff }, // sub:6:0xE2404014g
	{   5, 0xe58d0000, 0xfdffffff }, // str:4:0xE58D0000g
	{   6, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{   7, 0xe08d5014, 0xfdffffff }, // add:6:0xE28D5014g
	{   8, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB003810g
	{  10, 0xe1500019, 0xfdffffff }, // cmp:7:0xE3500019g
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000007g
	{  12, 0xe59f00a0, 0xfdffffff }, // ldr:4:0xE59F00A0g
	{  13, 0xe59d3010, 0xfdffffff }, // ldr:4:0xE59D3010g
	{  14, 0xe08f20cc, 0xfdffffff }, // add:6:0xE28F20CCg
	{  15, 0xe08f10bc, 0xfdffffff }, // add:6:0xE28F10BCg
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00092Cg
	{  17, 0xe5941004, 0xfdffffff }, // ldr:4:0xE5941004g
	{  18, 0xe59f0088, 0xfdffffff }, // ldr:4:0xE59F0088g
	{  20, 0xe5942000, 0xfdffffff }, // ldr:4:0xE5942000g
	{  21, 0xe59d1010, 0xfdffffff }, // ldr:4:0xE59D1010g
	{  22, 0xe5940010, 0xfdffffff }, // ldr:4:0xE5940010g
	{  24, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{  26, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  29, 0xe49df014, 0xfdffffff }, // ldr:4:0xE49DF014g
	{  30, 0x00001b0c, 0xfdffffff }, // and:6:0x00001B0Cg
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig_FreeMemory_1[] = {g
	{   1, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF9066Bg
	{   3, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{   5, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   6, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF90666g
	{   8, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF90631g
	{  10, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  12, 0xe0800004, 0xfdffffff }, // add:6:0xE2800004g
	{  13, 0xe5101004, 0xfdffffff }, // ldr:4:0xE5101004g
	{  14, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  15, 0xe5810000, 0xfdffffff }, // str:4:0xE5810000g
	{  16, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  18, 0x0000d71c, 0xfdffffff }, // and:6:0x0000D71Cg
	{  19, 0x0000000a, 0xfdffffff }, // and:6:0x0000000Ag
	{  21, 0x000a5838, 0xfdffffff }, // and:6:0x000A5838g
	{  22, 0x00000a0d, 0xfdffffff }, // and:6:0x00000A0Dg
	{  27, 0x00000020, 0xfdffffff }, // and:6:0x00000020g
	{  30, 0x00000020, 0xfdffffff }, // and:6:0x00000020g
	{ -1, -1, -1 },g
	/* 19/32 */g
};g
g
static FuncSig func_sig_GetCurrentTargetDistance_1[] = {g
	{   0, 0xe51f0a94, 0xfdffffff }, // ldr:4:0xE51F0A94g
	{   2, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   3, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   4, 0x059f0388, 0xfdffffff }, // ldr:4:0x059F0388g
	{   5, 0x01a01fdb, 0xfdffffff }, // mov:6:0x03A01FDBg
	{   6, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFC394Fg
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0331BCg
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFDCg
	{  10, 0xe51f0abc, 0xfdffffff }, // ldr:4:0xE51F0ABCg
	{  12, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  13, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  14, 0x059f13d4, 0xfdffffff }, // ldr:4:0x059F13D4g
	{  15, 0x059f035c, 0xfdffffff }, // ldr:4:0x059F035Cg
	{  16, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFC3945g
	{  17, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  18, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100Dg
	{  19, 0xe08d0004, 0xfdffffff }, // add:6:0xE28D0004g
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001685g
	{  21, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB032FE0g
	{  26, 0xe51f0afc, 0xfdffffff }, // ldr:4:0xE51F0AFCg
	{  28, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  29, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  30, 0x059f1398, 0xfdffffff }, // ldr:4:0x059F1398g
	{  31, 0x059f031c, 0xfdffffff }, // ldr:4:0x059F031Cg
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_GetSystemTime_1[] = {g
	{   1, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF906F7g
	{   3, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{   6, 0xe1a0e001, 0xfdffffff }, // mov:6:0xE1A0E001g
	{   7, 0xe59f139c, 0xfdffffff }, // ldr:4:0xE59F139Cg
	{   8, 0xe1a0400d, 0xfdffffff }, // mov:6:0xE1A0400Dg
	{  10, 0xe1500004, 0xfdffffff }, // cmp:7:0xE3500004g
	{  11, 0x315e0050, 0xfdffffff }, // cmp:7:0x335E0050g
	{  12, 0x21a00001, 0xfdffffff }, // mov:6:0x23A00001g
	{  14, 0x2a000000, 0xff000000 }, // b, bl:3:0x2A00000Dg
	{  15, 0xe51f1118, 0xfdffffff }, // ldr:4:0xE51F1118g
	{  16, 0xe59f337c, 0xfdffffff }, // ldr:4:0xE59F337Cg
	{  18, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{  19, 0x1583e108, 0xfdffffff }, // str:4:0x1583E108g
	{  20, 0x11a02e1a, 0xfdffffff }, // mov:6:0x13A02E1Ag
	{  21, 0x0583e104, 0xfdffffff }, // str:4:0x0583E104g
	{  22, 0xe5940100, 0xfdffffff }, // ldr:4:0xE7940100g
	{  23, 0x01a02e19, 0xfdffffff }, // mov:6:0x03A02E19g
	{  24, 0xe5802000, 0xfdffffff }, // str:4:0xE5802000g
	{  25, 0x11a00000, 0xfdffffff }, // mov:6:0x13A00000g
	{  26, 0x01a00001, 0xfdffffff }, // mov:6:0x03A00001g
	{  28, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  29, 0xe08dd010, 0xfdffffff }, // add:6:0xE28DD010g
	{  31, 0xe0801004, 0xfdffffff }, // add:6:0xE2801004g
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig_memcmp_1[] = {g
	{   0, 0xe1520018, 0xfdffffff }, // cmp:7:0xE3520018g
	{   1, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000029g
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000Ag
	{   5, 0xe153000c, 0xfdffffff }, // cmp:7:0xE153000Cg
	{   6, 0x00800001, 0xfdffffff }, // add:6:0x02800001g
	{   7, 0x00811001, 0xfdffffff }, // add:6:0x02811001g
	{   8, 0x00422001, 0xfdffffff }, // sub:6:0x02422001g
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003g
	{  12, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001g
	{  14, 0xe1100003, 0xfdffffff }, // tst:7:0xE3100003g
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF2g
	{  16, 0xe0113003, 0xfdffffff }, // and:6:0xE2113003g
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000Dg
	{  18, 0xe1530001, 0xfdffffff }, // cmp:7:0xE3530001g
	{  19, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00001Ag
	{  20, 0xe1530002, 0xfdffffff }, // cmp:7:0xE3530002g
	{  21, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000013g
	{  22, 0xe1530003, 0xfdffffff }, // cmp:7:0xE3530003g
	{  23, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000016g
	{  24, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000012g
	{  25, 0xe5903000, 0xfdffffff }, // ldr:4:0xE5903000g
	{  26, 0xe591c000, 0xfdffffff }, // ldr:4:0xE591C000g
	{  27, 0xe153000c, 0xfdffffff }, // cmp:7:0xE153000Cg
	{  28, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000011g
	{  29, 0xe0800004, 0xfdffffff }, // add:6:0xE2800004g
	{  30, 0xe0811004, 0xfdffffff }, // add:6:0xE2811004g
	{  31, 0xe0422004, 0xfdffffff }, // sub:6:0xE2422004g
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_memcpy_1[] = {g
	{   0, 0xe1520010, 0xfdffffff }, // cmp:7:0xE3520010g
	{   1, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000g
	{   2, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000032g
	{   3, 0xe1130003, 0xfdffffff }, // tst:7:0xE3130003g
	{   5, 0x10422001, 0xfdffffff }, // sub:6:0x12422001g
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFAg
	{   8, 0xe011c003, 0xfdffffff }, // and:6:0xE211C003g
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000Dg
	{  10, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE35C0001g
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000029g
	{  12, 0xe15c0002, 0xfdffffff }, // cmp:7:0xE35C0002g
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000027g
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00001Ag
	{  15, 0xe491c004, 0xfdffffff }, // ldr:4:0xE491C004g
	{  16, 0xe0422010, 0xfdffffff }, // sub:6:0xE2422010g
	{  17, 0xe483c004, 0xfdffffff }, // str:4:0xE483C004g
	{  18, 0xe491c004, 0xfdffffff }, // ldr:4:0xE491C004g
	{  19, 0xe483c004, 0xfdffffff }, // str:4:0xE483C004g
	{  20, 0xe491c004, 0xfdffffff }, // ldr:4:0xE491C004g
	{  21, 0xe483c004, 0xfdffffff }, // str:4:0xE483C004g
	{  22, 0xe491c004, 0xfdffffff }, // ldr:4:0xE491C004g
	{  23, 0xe483c004, 0xfdffffff }, // str:4:0xE483C004g
	{  24, 0xe1520010, 0xfdffffff }, // cmp:7:0xE3520010g
	{  25, 0x2a000000, 0xff000000 }, // b, bl:3:0x2AFFFFF4g
	{  26, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000002g
	{  27, 0xe491c004, 0xfdffffff }, // ldr:4:0xE491C004g
	{  28, 0xe0422004, 0xfdffffff }, // sub:6:0xE2422004g
	{  29, 0xe483c004, 0xfdffffff }, // str:4:0xE483C004g
	{  30, 0xe1520004, 0xfdffffff }, // cmp:7:0xE3520004g
	{  31, 0x2a000000, 0xff000000 }, // b, bl:3:0x2AFFFFFAg
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
static FuncSig func_sig_memset_1[] = {g
	{   0, 0xe1a03001, 0xfdffffff }, // mov:6:0xE1A03001g
	{   1, 0xe1520010, 0xfdffffff }, // cmp:7:0xE3520010g
	{   2, 0xe003c0ff, 0xfdffffff }, // and:6:0xE203C0FFg
	{   3, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{   4, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000016g
	{   5, 0xe1110003, 0xfdffffff }, // tst:7:0xE3110003g
	{   6, 0x10422001, 0xfdffffff }, // sub:6:0x12422001g
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFBg
	{   9, 0xe1a03c0c, 0xfdffffff }, // mov:6:0xE1A03C0Cg
	{  13, 0xe1520010, 0xfdffffff }, // cmp:7:0xE3520010g
	{  14, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000007g
	{  15, 0xe4813004, 0xfdffffff }, // str:4:0xE4813004g
	{  16, 0xe4813004, 0xfdffffff }, // str:4:0xE4813004g
	{  17, 0xe4813004, 0xfdffffff }, // str:4:0xE4813004g
	{  18, 0xe0422010, 0xfdffffff }, // sub:6:0xE2422010g
	{  19, 0xe4813004, 0xfdffffff }, // str:4:0xE4813004g
	{  20, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFF7g
	{  21, 0xe0422004, 0xfdffffff }, // sub:6:0xE2422004g
	{  22, 0xe4813004, 0xfdffffff }, // str:4:0xE4813004g
	{  23, 0xe1520004, 0xfdffffff }, // cmp:7:0xE3520004g
	{  24, 0x2a000000, 0xff000000 }, // b, bl:3:0x2AFFFFFBg
	{  25, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000001g
	{  26, 0xe0422001, 0xfdffffff }, // sub:6:0xE2422001g
	{  28, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{  29, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFBg
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_Close_1[] = {g
	{   1, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD489g
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   4, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00AAC1g
	{   6, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{   9, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{  10, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD41Fg
	{  12, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  14, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001g
	{  15, 0xe59d1004, 0xfdffffff }, // ldr:4:0xE59D1004g
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B3FEg
	{  19, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF2g
	{  21, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008g
	{  23, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00AADCg
	{  25, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{  26, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000176g
	{  28, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000185g
	{  30, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_Open_1[] = {g
	{   1, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001g
	{   2, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD466g
	{   4, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   5, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006g
	{   6, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00AA8Dg
	{   8, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  11, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD489g
	{  13, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  14, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00AAC1g
	{  16, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  19, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{  20, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD41Fg
	{  22, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  24, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001g
	{  25, 0xe59d1004, 0xfdffffff }, // ldr:4:0xE59D1004g
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B3FEg
	{  29, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF2g
	{  31, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig_Read_1[] = {g
	{   1, 0xe1b04002, 0xfdffffff }, // mov:6:0xE1B04002g
	{   2, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{   3, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008g
	{   5, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{   6, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE27g
	{   8, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   9, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000004g
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE4CDg
	{  11, 0xe1a01009, 0xfdffffff }, // mov:6:0xE3A01009g
	{  12, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{  15, 0xe59f01a4, 0xfdffffff }, // ldr:4:0xE59F01A4g
	{  16, 0xe59d1004, 0xfdffffff }, // ldr:4:0xE59D1004g
	{  17, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004g
	{  18, 0xe5900101, 0xfdffffff }, // ldr:4:0xE7900101g
	{  19, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{  20, 0xe590300c, 0xfdffffff }, // ldr:4:0xE590300Cg
	{  21, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{  25, 0xe1b04002, 0xfdffffff }, // mov:6:0xE1B04002g
	{  26, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{  27, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{  28, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008g
	{  29, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{  30, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE0Fg
	{ -1, -1, -1 },g
	/* 26/32 */g
};g
g
static FuncSig func_sig_Write_1[] = {g
	{   1, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000g
	{   2, 0xe1a05002, 0xfdffffff }, // mov:6:0xE1A05002g
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD4EFg
	{   4, 0xe1500005, 0xfdffffff }, // cmp:7:0xE1500005g
	{   5, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   6, 0x11a00006, 0xfdffffff }, // mov:6:0x11A00006g
	{   7, 0x1b000000, 0xff000000 }, // b, bl:3:0x1B00AA87g
	{   8, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  11, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{  12, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  13, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD426g
	{  15, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000g
	{  18, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005g
	{  19, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE3A0100Bg
	{  20, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD529g
	{  22, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  23, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD448g
	{  25, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  28, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001g
	{  29, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFEAg
	{  31, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_Lseek_1[] = {g
	{   1, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{   2, 0xe04dd034, 0xfdffffff }, // sub:6:0xE24DD034g
	{   3, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   4, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001g
	{   5, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000Bg
	{   6, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004g
	{   7, 0xe1a01010, 0xfdffffff }, // mov:6:0xE3A01010g
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD510g
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  11, 0xba000000, 0xff000000 }, // b, bl:3:0xBA000023g
	{  12, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  13, 0xe1a0100f, 0xfdffffff }, // mov:6:0xE3A0100Fg
	{  14, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD50Ag
	{  16, 0xe08dd034, 0xfdffffff }, // add:6:0xE28DD034g
	{  18, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001g
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000Fg
	{  20, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  21, 0xe1a0100f, 0xfdffffff }, // mov:6:0xE3A0100Fg
	{  22, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD502g
	{  24, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  25, 0xba000000, 0xff000000 }, // b, bl:3:0xBA000015g
	{  26, 0xe0844000, 0xfdffffff }, // add:6:0xE0844000g
	{  27, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000011g
	{  28, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004g
	{  29, 0xe1a01010, 0xfdffffff }, // mov:6:0xE3A01010g
	{  30, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD4FAg
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
static FuncSig func_sig_strcmp_1[] = {g
	{   0, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000008g
	{   2, 0xe1520003, 0xfdffffff }, // cmp:7:0xE1520003g
	{   3, 0x00800001, 0xfdffffff }, // add:6:0x02800001g
	{   4, 0x00811001, 0xfdffffff }, // add:6:0x02811001g
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003g
	{   8, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001g
	{  11, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{  13, 0x01530000, 0xfdffffff }, // cmp:7:0x03530000g
	{  14, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF1g
	{  15, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  17, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  19, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{  21, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{  22, 0x10811001, 0xfdffffff }, // add:6:0x12811001g
	{  23, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFBg
	{  24, 0xe0410000, 0xfdffffff }, // sub:6:0xE0410000g
	{  26, 0xe1520018, 0xfdffffff }, // cmp:7:0xE3520018g
	{  27, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000029g
	{  28, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000Ag
	{  31, 0xe153000c, 0xfdffffff }, // cmp:7:0xE153000Cg
	{ -1, -1, -1 },g
	/* 20/32 */g
};g
g
static FuncSig func_sig_strcpy_1[] = {g
	{   0, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000g
	{   2, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000g
	{   4, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFBg
	{   6, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000g
	{   7, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009g
	{   9, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000g
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005g
	{  12, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  13, 0xe0422001, 0xfdffffff }, // sub:6:0xE2422001g
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFBg
	{  18, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001g
	{  19, 0x2a000000, 0xff000000 }, // b, bl:3:0x2AFFFFF3g
	{  21, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000008g
	{  23, 0xe1520003, 0xfdffffff }, // cmp:7:0xE1520003g
	{  24, 0x00800001, 0xfdffffff }, // add:6:0x02800001g
	{  25, 0x00811001, 0xfdffffff }, // add:6:0x02811001g
	{  26, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003g
	{  29, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001g
	{ -1, -1, -1 },g
	/* 18/32 */g
};g
g
static FuncSig func_sig_strlen_1[] = {g
	{   0, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{   4, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{   5, 0x10811001, 0xfdffffff }, // add:6:0x12811001g
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFBg
	{   7, 0xe0410000, 0xfdffffff }, // sub:6:0xE0410000g
	{   9, 0xe1520018, 0xfdffffff }, // cmp:7:0xE3520018g
	{  10, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000029g
	{  11, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000Ag
	{  14, 0xe153000c, 0xfdffffff }, // cmp:7:0xE153000Cg
	{  15, 0x00800001, 0xfdffffff }, // add:6:0x02800001g
	{  16, 0x00811001, 0xfdffffff }, // add:6:0x02811001g
	{  17, 0x00422001, 0xfdffffff }, // sub:6:0x02422001g
	{  18, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003g
	{  21, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001g
	{  23, 0xe1100003, 0xfdffffff }, // tst:7:0xE3100003g
	{  24, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF2g
	{  25, 0xe0113003, 0xfdffffff }, // and:6:0xE2113003g
	{  26, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000Dg
	{  27, 0xe1530001, 0xfdffffff }, // cmp:7:0xE3530001g
	{  28, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00001Ag
	{  29, 0xe1530002, 0xfdffffff }, // cmp:7:0xE3530002g
	{  30, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000013g
	{  31, 0xe1530003, 0xfdffffff }, // cmp:7:0xE3530003g
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig_TakeSemaphore_1[] = {g
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   2, 0xe59f009c, 0xfdffffff }, // ldr:4:0xE59F009Cg
	{   3, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{   4, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   5, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   7, 0xc59f109c, 0xfdffffff }, // ldr:4:0xC59F109Cg
	{   8, 0xc08f0088, 0xfdffffff }, // add:6:0xC28F0088g
	{   9, 0xcb000000, 0xff000000 }, // b, bl:3:0xCB000184g
	{  10, 0xe59f0094, 0xfdffffff }, // ldr:4:0xE59F0094g
	{  11, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  12, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  13, 0xc59f108c, 0xfdffffff }, // ldr:4:0xC59F108Cg
	{  14, 0xc08f0070, 0xfdffffff }, // add:6:0xC28F0070g
	{  15, 0xcb000000, 0xff000000 }, // b, bl:3:0xCB00017Eg
	{  16, 0xe0040001, 0xfdffffff }, // and:6:0xE2040001g
	{  17, 0xe0400001, 0xfdffffff }, // sub:6:0xE2400001g
	{  18, 0xe1100004, 0xfdffffff }, // tst:7:0xE1100004g
	{  19, 0x01a00007, 0xfdffffff }, // mov:6:0x03A00007g
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000014g
	{  21, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000g
	{  22, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{  23, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002g
	{  24, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{  25, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0034F7g
	{  27, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{  28, 0xe1a000a4, 0xfdffffff }, // mov:6:0xE1A000A4g
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFDA36g
	{  31, 0x01a00009, 0xfdffffff }, // mov:6:0x03A00009g
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
static FuncSig func_sig_vsprintf_1[] = {g
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004g
	{   1, 0xe04dd01c, 0xfdffffff }, // sub:6:0xE24DD01Cg
	{   2, 0xe58d0008, 0xfdffffff }, // str:4:0xE58D0008g
	{   3, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{   4, 0xe1a03002, 0xfdffffff }, // mov:6:0xE1A03002g
	{   5, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001g
	{   7, 0xe04f004c, 0xfdffffff }, // sub:6:0xE24F004Cg
	{   8, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE9A3g
	{  10, 0xe59d2008, 0xfdffffff }, // ldr:4:0xE59D2008g
	{  11, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  13, 0xe08dd01c, 0xfdffffff }, // add:6:0xE28DD01Cg
	{  14, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004g
	{  17, 0xe04dd054, 0xfdffffff }, // sub:6:0xE24DD054g
	{  18, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{  19, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  20, 0xe59d2068, 0xfdffffff }, // ldr:4:0xE59D2068g
	{  21, 0xe08d0004, 0xfdffffff }, // add:6:0xE28D0004g
	{  22, 0xe1a01050, 0xfdffffff }, // mov:6:0xE3A01050g
	{  23, 0xe08d306c, 0xfdffffff }, // add:6:0xE28D306Cg
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB004457g
	{  25, 0xe08d2004, 0xfdffffff }, // add:6:0xE28D2004g
	{  26, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{  27, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFCA11g
	{  29, 0xe08dd054, 0xfdffffff }, // add:6:0xE28DD054g
	{  31, 0xe49df014, 0xfdffffff }, // ldr:4:0xE49DF014g
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_GetFocusLensSubjectDistance_1[] = {g
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFAE5g
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{   3, 0xe08f006c, 0xfdffffff }, // add:6:0xE28F006Cg
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFC0987g
	{   5, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{   7, 0xe1a0001e, 0xfdffffff }, // mov:6:0xE3A0001Eg
	{   9, 0xe1a00010, 0xfdffffff }, // mov:6:0xE3A00010g
	{  12, 0xe5904000, 0xfdffffff }, // ldr:4:0xE5904000g
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFCF2D3g
	{  14, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100Dg
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFCF065g
	{  16, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{  17, 0xe0800084, 0xfdffffff }, // add:6:0xE0800084g
	{  23, 0x00006425, 0xfdffffff }, // and:6:0x00006425g
	{  27, 0x00642520, 0xfdffffff }, // rsb:6:0x00642520g
	{  31, 0x00642520, 0xfdffffff }, // rsb:6:0x00642520g
	{ -1, -1, -1 },g
	/* 16/32 */g
};g
g
static FuncSig func_sig_GetZoomLensCurrentPoint_1[] = {g
	{   1, 0xe51f41bc, 0xfdffffff }, // ldr:4:0xE51F41BCg
	{   2, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{   3, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   4, 0x059f1bf0, 0xfdffffff }, // ldr:4:0x059F1BF0g
	{   5, 0x004f0f6f, 0xfdffffff }, // sub:6:0x024F0F6Fg
	{   6, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFC2427g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB03340Fg
	{   8, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFEBg
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB03340Cg
	{  12, 0xe5941004, 0xfdffffff }, // ldr:4:0xE5941004g
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEA033197g
	{  16, 0xe1a09002, 0xfdffffff }, // mov:6:0xE1A09002g
	{  17, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000g
	{  18, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFEBg
	{  20, 0xe51f6208, 0xfdffffff }, // ldr:4:0xE51F6208g
	{  21, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  22, 0xe5960000, 0xfdffffff }, // ldr:4:0xE5960000g
	{  23, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  24, 0x01a010c6, 0xfdffffff }, // mov:6:0x03A010C6g
	{  25, 0x004f0f83, 0xfdffffff }, // sub:6:0x024F0F83g
	{  26, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFC2413g
	{  27, 0xe5960008, 0xfdffffff }, // ldr:4:0xE5960008g
	{  28, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  30, 0xe5960010, 0xfdffffff }, // ldr:4:0xE5960010g
	{  31, 0xe51f8208, 0xfdffffff }, // ldr:4:0xE51F8208g
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_GetZoomLensCurrentPosition_1[] = {g
	{   0, 0xea000000, 0xff000000 }, // b, bl:3:0xEA033137g
	{   1, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFE0Cg
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   3, 0x059f0100, 0xfdffffff }, // ldr:4:0x059F0100g
	{   4, 0xe51f2d48, 0xfdffffff }, // ldr:4:0xE51F2D48g
	{   5, 0xe5820028, 0xfdffffff }, // str:4:0xE5820028g
	{   6, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{   7, 0x1582102c, 0xfdffffff }, // str:4:0x1582102Cg
	{   8, 0x0582002c, 0xfdffffff }, // str:4:0x0582002Cg
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  11, 0x059f00e4, 0xfdffffff }, // ldr:4:0x059F00E4g
	{  12, 0xe51f2d68, 0xfdffffff }, // ldr:4:0xE51F2D68g
	{  13, 0xe5820018, 0xfdffffff }, // str:4:0xE5820018g
	{  14, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{  15, 0x1582101c, 0xfdffffff }, // str:4:0x1582101Cg
	{  16, 0x0582001c, 0xfdffffff }, // str:4:0x0582001Cg
	{  19, 0xe59f00c8, 0xfdffffff }, // ldr:4:0xE59F00C8g
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB033528g
	{  21, 0xe59f00c4, 0xfdffffff }, // ldr:4:0xE59F00C4g
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEA032DF1g
	{  24, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  25, 0x059f00a8, 0xfdffffff }, // ldr:4:0x059F00A8g
	{  26, 0xe51f2da0, 0xfdffffff }, // ldr:4:0xE51F2DA0g
	{  27, 0xe5820020, 0xfdffffff }, // str:4:0xE5820020g
	{  28, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{  29, 0x15821024, 0xfdffffff }, // str:4:0x15821024g
	{  30, 0x05820024, 0xfdffffff }, // str:4:0x05820024g
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_RefreshPhysicalScreen_1[] = {g
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000A4g
	{   2, 0xe1100001, 0xfdffffff }, // tst:7:0xE3100001g
	{   3, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000017g
	{   4, 0xe51f44d0, 0xfdffffff }, // ldr:4:0xE51F44D0g
	{   5, 0xe5940030, 0xfdffffff }, // ldr:4:0xE5940030g
	{   6, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000011g
	{   8, 0xe08f1f7b, 0xfdffffff }, // add:6:0xE28F1F7Bg
	{   9, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020g
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFBD744g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF1A8g
	{  13, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  14, 0xe58d1000, 0xfdffffff }, // str:4:0xE58D1000g
	{  16, 0xe594c028, 0xfdffffff }, // ldr:4:0xE594C028g
	{  17, 0xe594100c, 0xfdffffff }, // ldr:4:0xE594100Cg
	{  18, 0xe5943000, 0xfdffffff }, // ldr:4:0xE5943000g
	{  19, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF19Dg
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF084g
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF242g
	{  24, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  25, 0xe584002c, 0xfdffffff }, // str:4:0xE584002Cg
	{  26, 0xe5940018, 0xfdffffff }, // ldr:4:0xE5940018g
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFAA64Dg
	{  29, 0xe51f1534, 0xfdffffff }, // ldr:4:0xE51F1534g
	{  30, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  31, 0xe5810030, 0xfdffffff }, // str:4:0xE5810030g
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_GetPropertyCase_1[] = {g
	{   1, 0xe51f4130, 0xfdffffff }, // ldr:4:0xE51F4130g
	{   2, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   3, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{   4, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001g
	{   5, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   6, 0x059f1820, 0xfdffffff }, // ldr:4:0x059F1820g
	{   7, 0x004f0f51, 0xfdffffff }, // sub:6:0x024F0F51g
	{   8, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002g
	{   9, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFEC910g
	{  10, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{  11, 0xe59f3810, 0xfdffffff }, // ldr:4:0xE59F3810g
	{  12, 0xe59f1800, 0xfdffffff }, // ldr:4:0xE59F1800g
	{  13, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  14, 0xe04f2e16, 0xfdffffff }, // sub:6:0xE24F2E16g
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFEC8C4g
	{  16, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{  17, 0xe1a03007, 0xfdffffff }, // mov:6:0xE1A03007g
	{  18, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006g
	{  19, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFC5g
	{  21, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  22, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{  23, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFEC7A6g
	{  25, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  28, 0xe51f419c, 0xfdffffff }, // ldr:4:0xE51F419Cg
	{  29, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{  30, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  31, 0x059f17c4, 0xfdffffff }, // ldr:4:0x059F17C4g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_SetPropertyCase_1[] = {g
	{   0, 0xea000000, 0xff000000 }, // b, bl:3:0xEA002395g
	{   2, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002392g
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0023D2g
	{   7, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{   8, 0xe1510001, 0xfdffffff }, // cmp:7:0xE3510001g
	{   9, 0xe58d2008, 0xfdffffff }, // str:4:0xE58D2008g
	{  10, 0xe58d2004, 0xfdffffff }, // str:4:0xE58D2004g
	{  11, 0xe58d2000, 0xfdffffff }, // str:4:0xE58D2000g
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009g
	{  13, 0xe1510002, 0xfdffffff }, // cmp:7:0xE3510002g
	{  14, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000Cg
	{  15, 0xe1510004, 0xfdffffff }, // cmp:7:0xE3510004g
	{  16, 0x11a00002, 0xfdffffff }, // mov:6:0x11A00002g
	{  17, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003g
	{  18, 0xe1a02004, 0xfdffffff }, // mov:6:0xE3A02004g
	{  19, 0xe08d1008, 0xfdffffff }, // add:6:0xE28D1008g
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0023C3g
	{  21, 0xe59d0008, 0xfdffffff }, // ldr:4:0xE59D0008g
	{  23, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001g
	{  24, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100Dg
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0023BEg
	{  28, 0xe1a02004, 0xfdffffff }, // mov:6:0xE3A02004g
	{  29, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0023B9g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_VbattGet_1[] = {g
	{   1, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008AF0g
	{   3, 0xe51f183c, 0xfdffffff }, // ldr:4:0xE51F183Cg
	{   6, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001g
	{   7, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800g
	{   8, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840g
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFD64g
	{  11, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008A94g
	{  13, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008A92g
	{  15, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008A90g
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFEDg
	{  18, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE7BBg
	{  20, 0xe59f657c, 0xfdffffff }, // ldr:4:0xE59F657Cg
	{  21, 0xe59640e4, 0xfdffffff }, // ldr:4:0xE59640E4g
	{  22, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008A75g
	{  24, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008A73g
	{  26, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008A71g
	{  28, 0xe51fc8f4, 0xfdffffff }, // ldr:4:0xE51FC8F4g
	{  29, 0xe59c3028, 0xfdffffff }, // ldr:4:0xE59C3028g
	{  30, 0xe1530001, 0xfdffffff }, // cmp:7:0xE3530001g
	{  31, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000047g
	{ -1, -1, -1 },g
	/* 28/32 */g
};g
g
static FuncSig func_sig_kbd_read_keys_1[] = {g
	{   0, 0xe51f214c, 0xfdffffff }, // ldr:4:0xE51F214Cg
	{   2, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{   3, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{   4, 0xe5821100, 0xfdffffff }, // str:4:0xE7821100g
	{   5, 0xe0500001, 0xfdffffff }, // sub:6:0xE2500001g
	{   6, 0x5a000000, 0xff000000 }, // b, bl:3:0x5AFFFFFCg
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008FDEg
	{   8, 0xe51f016c, 0xfdffffff }, // ldr:4:0xE51F016Cg
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008FCFg
	{  10, 0xe51f0174, 0xfdffffff }, // ldr:4:0xE51F0174g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008E85g
	{  13, 0xea000000, 0xff000000 }, // b, bl:3:0xEA008FEEg
	{  15, 0xe51f5190, 0xfdffffff }, // ldr:4:0xE51F5190g
	{  16, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  17, 0xe5950008, 0xfdffffff }, // ldr:4:0xE5950008g
	{  18, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003g
	{  20, 0xe59f0150, 0xfdffffff }, // ldr:4:0xE59F0150g
	{  21, 0xe1540000, 0xfdffffff }, // cmp:7:0xE1540000g
	{  22, 0x11540c09, 0xfdffffff }, // cmp:7:0x13540C09g
	{  24, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0122C7g
	{  26, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000g
	{  27, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  28, 0x11a01004, 0xfdffffff }, // mov:6:0x11A01004g
	{  30, 0x108f0f4b, 0xfdffffff }, // add:6:0x128F0F4Bg
	{  31, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFB920g
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_kbd_p1_f_1[] = {g
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE3A04000g
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFBBg
	{   3, 0xe51f1260, 0xfdffffff }, // ldr:4:0xE51F1260g
	{   4, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{   5, 0xe041200c, 0xfdffffff }, // sub:6:0xE241200Cg
	{   6, 0xe0823018, 0xfdffffff }, // add:6:0xE2823018g
	{   7, 0xe1a0500d, 0xfdffffff }, // mov:6:0xE1A0500Dg
	{   8, 0xe593c100, 0xfdffffff }, // ldr:4:0xE793C100g
	{   9, 0xe592e100, 0xfdffffff }, // ldr:4:0xE792E100g
	{  10, 0xe00cc00e, 0xfdffffff }, // and:6:0xE00CC00Eg
	{  11, 0xe591e100, 0xfdffffff }, // ldr:4:0xE791E100g
	{  13, 0xe585c100, 0xfdffffff }, // str:4:0xE785C100g
	{  14, 0xe0500001, 0xfdffffff }, // sub:6:0xE2500001g
	{  15, 0x5a000000, 0xff000000 }, // b, bl:3:0x5AFFFFF7g
	{  16, 0xe51f2280, 0xfdffffff }, // ldr:4:0xE51F2280g
	{  17, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  18, 0xe042100c, 0xfdffffff }, // sub:6:0xE242100Cg
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE53g
	{  20, 0xe51f029c, 0xfdffffff }, // ldr:4:0xE51F029Cg
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008E30g
	{  22, 0xe51f12a4, 0xfdffffff }, // ldr:4:0xE51F12A4g
	{  23, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  24, 0x01a04001, 0xfdffffff }, // mov:6:0x03A04001g
	{  25, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{  26, 0xe081200c, 0xfdffffff }, // add:6:0xE281200Cg
	{  27, 0xe5923100, 0xfdffffff }, // ldr:4:0xE7923100g
	{  28, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000g
	{  29, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006g
	{  30, 0xe591c100, 0xfdffffff }, // ldr:4:0xE791C100g
	{  31, 0xe595e100, 0xfdffffff }, // ldr:4:0xE795E100g
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
static FuncSig func_sig_kbd_p1_f_cont_1[] = {g
	{   0, 0xe51f1260, 0xfdffffff }, // ldr:4:0xE51F1260g
	{   1, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{   2, 0xe041200c, 0xfdffffff }, // sub:6:0xE241200Cg
	{   3, 0xe0823018, 0xfdffffff }, // add:6:0xE2823018g
	{   4, 0xe1a0500d, 0xfdffffff }, // mov:6:0xE1A0500Dg
	{   5, 0xe593c100, 0xfdffffff }, // ldr:4:0xE793C100g
	{   6, 0xe592e100, 0xfdffffff }, // ldr:4:0xE792E100g
	{   7, 0xe00cc00e, 0xfdffffff }, // and:6:0xE00CC00Eg
	{   8, 0xe591e100, 0xfdffffff }, // ldr:4:0xE791E100g
	{  10, 0xe585c100, 0xfdffffff }, // str:4:0xE785C100g
	{  11, 0xe0500001, 0xfdffffff }, // sub:6:0xE2500001g
	{  12, 0x5a000000, 0xff000000 }, // b, bl:3:0x5AFFFFF7g
	{  13, 0xe51f2280, 0xfdffffff }, // ldr:4:0xE51F2280g
	{  14, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  15, 0xe042100c, 0xfdffffff }, // sub:6:0xE242100Cg
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE53g
	{  17, 0xe51f029c, 0xfdffffff }, // ldr:4:0xE51F029Cg
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB008E30g
	{  19, 0xe51f12a4, 0xfdffffff }, // ldr:4:0xE51F12A4g
	{  20, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  21, 0x01a04001, 0xfdffffff }, // mov:6:0x03A04001g
	{  22, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{  23, 0xe081200c, 0xfdffffff }, // add:6:0xE281200Cg
	{  24, 0xe5923100, 0xfdffffff }, // ldr:4:0xE7923100g
	{  25, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000g
	{  26, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006g
	{  27, 0xe591c100, 0xfdffffff }, // ldr:4:0xE791C100g
	{  28, 0xe595e100, 0xfdffffff }, // ldr:4:0xE795E100g
	{  30, 0xe003300e, 0xfdffffff }, // and:6:0xE003300Eg
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_kbd_p2_f_1[] = {g
	{   1, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018g
	{   2, 0xe59f656c, 0xfdffffff }, // ldr:4:0xE59F656Cg
	{   3, 0xe08d7008, 0xfdffffff }, // add:6:0xE28D7008g
	{   4, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00001Dg
	{   5, 0xe59f1554, 0xfdffffff }, // ldr:4:0xE59F1554g
	{   7, 0xe08d3008, 0xfdffffff }, // add:6:0xE28D3008g
	{   8, 0xe08d2014, 0xfdffffff }, // add:6:0xE28D2014g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0090FAg
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000Cg
	{  12, 0xe59d0014, 0xfdffffff }, // ldr:4:0xE59D0014g
	{  13, 0xe1500102, 0xfdffffff }, // cmp:7:0xE3500102g
	{  14, 0x11500000, 0xfdffffff }, // cmp:7:0x13500000g
	{  15, 0x11500106, 0xfdffffff }, // cmp:7:0x13500106g
	{  16, 0x11500001, 0xfdffffff }, // cmp:7:0x13500001g
	{  17, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005g
	{  18, 0xe59f1514, 0xfdffffff }, // ldr:4:0xE59F1514g
	{  19, 0xe5911004, 0xfdffffff }, // ldr:4:0xE5911004g
	{  20, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{  21, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001g
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0001B5g
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000000g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0001A0g
	{  25, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{  26, 0xe5971100, 0xfdffffff }, // ldr:4:0xE7971100g
	{  27, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{  28, 0x15962100, 0xfdffffff }, // ldr:4:0x17962100g
	{  30, 0x15861100, 0xfdffffff }, // str:4:0x17861100g
	{  31, 0xe0400001, 0xfdffffff }, // sub:6:0xE2400001g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_kbd_pwr_on_1[] = {g
	{   0, 0xe59f00f8, 0xfdffffff }, // ldr:4:0xE59F00F8g
	{   2, 0xe59010e0, 0xfdffffff }, // ldr:4:0xE59010E0g
	{   4, 0xe58010e0, 0xfdffffff }, // str:4:0xE58010E0g
	{   5, 0xe04f2028, 0xfdffffff }, // sub:6:0xE24F2028g
	{   6, 0xe0821000, 0xfdffffff }, // add:6:0xE2821000g
	{   7, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000g
	{   8, 0xe1a00032, 0xfdffffff }, // mov:6:0xE3A00032g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0081BDg
	{  10, 0xe1100001, 0xfdffffff }, // tst:7:0xE3100001g
	{  11, 0x11500015, 0xfdffffff }, // cmp:7:0x13500015g
	{  12, 0x11a010ec, 0xfdffffff }, // mov:6:0x13A010ECg
	{  13, 0x108f00c8, 0xfdffffff }, // add:6:0x128F00C8g
	{  14, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFF53FCg
	{  15, 0xe59f00b8, 0xfdffffff }, // ldr:4:0xE59F00B8g
	{  16, 0xe59f10c8, 0xfdffffff }, // ldr:4:0xE59F10C8g
	{  17, 0xe5900004, 0xfdffffff }, // ldr:4:0xE5900004g
	{  19, 0xe1a030ed, 0xfdffffff }, // mov:6:0xE3A030EDg
	{  20, 0xe08f20ac, 0xfdffffff }, // add:6:0xE28F20ACg
	{  21, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFF53AFg
	{  22, 0xe59f00a0, 0xfdffffff }, // ldr:4:0xE59F00A0g
	{  23, 0xe59010e0, 0xfdffffff }, // ldr:4:0xE59010E0g
	{  25, 0xe58010e0, 0xfdffffff }, // str:4:0xE58010E0g
	{  27, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  28, 0xe0000001, 0xfdffffff }, // and:6:0xE2000001g
	{  30, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_kbd_pwr_off_1[] = {g
	{   0, 0xe59f00a0, 0xfdffffff }, // ldr:4:0xE59F00A0g
	{   1, 0xe59010e0, 0xfdffffff }, // ldr:4:0xE59010E0g
	{   3, 0xe58010e0, 0xfdffffff }, // str:4:0xE58010E0g
	{   5, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   6, 0xe0000001, 0xfdffffff }, // and:6:0xE2000001g
	{   8, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{  10, 0xe59f0078, 0xfdffffff }, // ldr:4:0xE59F0078g
	{  11, 0xe59010e0, 0xfdffffff }, // ldr:4:0xE59010E0g
	{  13, 0xe58010e0, 0xfdffffff }, // str:4:0xE58010E0g
	{  15, 0xe59f0064, 0xfdffffff }, // ldr:4:0xE59F0064g
	{  16, 0xe59010e0, 0xfdffffff }, // ldr:4:0xE59010E0g
	{  18, 0xe58010e0, 0xfdffffff }, // str:4:0xE58010E0g
	{  21, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  22, 0xe59f0044, 0xfdffffff }, // ldr:4:0xE59F0044g
	{  23, 0xe1a04000, 0xfdffffff }, // mov:6:0xE3A04000g
	{  24, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  25, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  26, 0x11a010c7, 0xfdffffff }, // mov:6:0x13A010C7g
	{  27, 0x108f0038, 0xfdffffff }, // add:6:0x128F0038g
	{  28, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFF53D8g
	{  29, 0xe59f0040, 0xfdffffff }, // ldr:4:0xE59F0040g
	{  30, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000g
	{  31, 0x0590401c, 0xfdffffff }, // ldr:4:0x0590401Cg
	{ -1, -1, -1 },g
	/* 23/32 */g
};g
g
static FuncSig func_sig_kbd_read_keys_r2_1[] = {g
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   2, 0xe59f04bc, 0xfdffffff }, // ldr:4:0xE59F04BCg
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00016Bg
	{   4, 0xe51f608c, 0xfdffffff }, // ldr:4:0xE51F608Cg
	{   5, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{   8, 0xe1a002a0, 0xfdffffff }, // mov:6:0xE1A002A0g
	{   9, 0xe5942100, 0xfdffffff }, // ldr:4:0xE7942100g
	{  10, 0xe003301f, 0xfdffffff }, // and:6:0xE203301Fg
	{  12, 0xe5841100, 0xfdffffff }, // str:4:0xE7841100g
	{  13, 0xe59f0494, 0xfdffffff }, // ldr:4:0xE59F0494g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000160g
	{  15, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{  18, 0xe1a002a0, 0xfdffffff }, // mov:6:0xE1A002A0g
	{  19, 0xe5942100, 0xfdffffff }, // ldr:4:0xE7942100g
	{  20, 0xe003301f, 0xfdffffff }, // and:6:0xE203301Fg
	{  22, 0xe5841100, 0xfdffffff }, // str:4:0xE7841100g
	{  24, 0xe1a052a0, 0xfdffffff }, // mov:6:0xE1A052A0g
	{  25, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE3A0000Bg
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF67Dg
	{  28, 0xe050cc01, 0xfdffffff }, // sub:6:0xE250CC01g
	{  29, 0x205cc05b, 0xfdffffff }, // sub:6:0x225CC05Bg
	{  30, 0xe5941105, 0xfdffffff }, // ldr:4:0xE7941105g
	{  31, 0x31a00000, 0xfdffffff }, // mov:6:0x33A00000g
	{ -1, -1, -1 },g
	/* 23/32 */g
};g
g
static FuncSig func_sig_mkdir_1[] = {g
	{   1, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000g
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{   3, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{   4, 0xe1a06000, 0xfdffffff }, // mov:6:0xE3A06000g
	{   5, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000g
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000A2g
	{   7, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007g
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000ADg
	{   9, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000g
	{  10, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  11, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  12, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD369g
	{  14, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000g
	{  15, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000007g
	{  16, 0xe1a02008, 0xfdffffff }, // mov:6:0xE1A02008g
	{  17, 0xe1a01004, 0xfdffffff }, // mov:6:0xE3A01004g
	{  18, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD46Dg
	{  20, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  21, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD38Cg
	{  23, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000g
	{  24, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000A0g
	{  26, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000g
	{  27, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000008g
	{  28, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000g
	{  29, 0x01560000, 0xfdffffff }, // cmp:7:0x03560000g
	{  30, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005g
	{  31, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{ -1, -1, -1 },g
	/* 31/32 */g
};g
g
static FuncSig func_sig_GetParameterData_1[] = {g
	{   1, 0xe51f5cfc, 0xfdffffff }, // ldr:4:0xE51F5CFCg
	{   2, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   3, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000g
	{   4, 0xe59f6260, 0xfdffffff }, // ldr:4:0xE59F6260g
	{   5, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   6, 0xe1a07001, 0xfdffffff }, // mov:6:0xE1A07001g
	{   7, 0x059f01e4, 0xfdffffff }, // ldr:4:0x059F01E4g
	{   8, 0x01a01006, 0xfdffffff }, // mov:6:0x01A01006g
	{   9, 0xe1a08002, 0xfdffffff }, // mov:6:0xE1A08002g
	{  10, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFBBEACg
	{  11, 0xe1140901, 0xfdffffff }, // tst:7:0xE3140901g
	{  12, 0x059f01d0, 0xfdffffff }, // ldr:4:0x059F01D0g
	{  13, 0x01a01006, 0xfdffffff }, // mov:6:0x01A01006g
	{  14, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFBBEA8g
	{  16, 0xe1540072, 0xfdffffff }, // cmp:7:0xE3540072g
	{  17, 0x259f01bc, 0xfdffffff }, // ldr:4:0x259F01BCg
	{  18, 0x21a01006, 0xfdffffff }, // mov:6:0x21A01006g
	{  19, 0x2b000000, 0xff000000 }, // b, bl:3:0x2BFBBEA3g
	{  20, 0xe59f3224, 0xfdffffff }, // ldr:4:0xE59F3224g
	{  21, 0xe59f21ac, 0xfdffffff }, // ldr:4:0xE59F21ACg
	{  22, 0xe51f1d24, 0xfdffffff }, // ldr:4:0xE51F1D24g
	{  23, 0xe5950008, 0xfdffffff }, // ldr:4:0xE5950008g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFBBE8Fg
	{  25, 0xe51f0d3c, 0xfdffffff }, // ldr:4:0xE51F0D3Cg
	{  26, 0xe1a03008, 0xfdffffff }, // mov:6:0xE1A03008g
	{  27, 0xe5901004, 0xfdffffff }, // ldr:4:0xE5901004g
	{  28, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  29, 0xe1a02007, 0xfdffffff }, // mov:6:0xE1A02007g
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB030271g
	{  31, 0xe5950008, 0xfdffffff }, // ldr:4:0xE5950008g
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
static FuncSig func_sig_SetParameterData_1[] = {g
	{   1, 0xe51f5c6c, 0xfdffffff }, // ldr:4:0xE51F5C6Cg
	{   2, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   3, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000g
	{   4, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001g
	{   5, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   6, 0x059f0278, 0xfdffffff }, // ldr:4:0x059F0278g
	{   7, 0x01a01ff7, 0xfdffffff }, // mov:6:0x03A01FF7g
	{   8, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002g
	{   9, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFBBED1g
	{  10, 0xe1140901, 0xfdffffff }, // tst:7:0xE3140901g
	{  11, 0x059f0264, 0xfdffffff }, // ldr:4:0x059F0264g
	{  12, 0x01a01ff7, 0xfdffffff }, // mov:6:0x03A01FF7g
	{  13, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFBBECDg
	{  15, 0xe1540072, 0xfdffffff }, // cmp:7:0xE3540072g
	{  16, 0x259f0250, 0xfdffffff }, // ldr:4:0x259F0250g
	{  17, 0x21a01ff7, 0xfdffffff }, // mov:6:0x23A01FF7g
	{  18, 0x2b000000, 0xff000000 }, // b, bl:3:0x2BFBBEC8g
	{  19, 0xe59f32b0, 0xfdffffff }, // ldr:4:0xE59F32B0g
	{  20, 0xe59f2240, 0xfdffffff }, // ldr:4:0xE59F2240g
	{  21, 0xe51f1c90, 0xfdffffff }, // ldr:4:0xE51F1C90g
	{  22, 0xe5950008, 0xfdffffff }, // ldr:4:0xE5950008g
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFBBEB4g
	{  24, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000g
	{  25, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001g
	{  27, 0xe51f0cb4, 0xfdffffff }, // ldr:4:0xE51F0CB4g
	{  28, 0xe1a03007, 0xfdffffff }, // mov:6:0xE1A03007g
	{  29, 0xe5901004, 0xfdffffff }, // ldr:4:0xE5901004g
	{  30, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  31, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_IsStrobeChargeCompleted_1[] = {g
	{   1, 0xe59f33f0, 0xfdffffff }, // ldr:4:0xE59F33F0g
	{   2, 0xe51f60cc, 0xfdffffff }, // ldr:4:0xE51F60CCg
	{   3, 0xe51f50e4, 0xfdffffff }, // ldr:4:0xE51F50E4g
	{   4, 0xe58d3000, 0xfdffffff }, // str:4:0xE58D3000g
	{   5, 0xe5950004, 0xfdffffff }, // ldr:4:0xE5950004g
	{   6, 0xe04f30ec, 0xfdffffff }, // sub:6:0xE24F30ECg
	{   7, 0xe1a04000, 0xfdffffff }, // mov:6:0xE3A04000g
	{   8, 0xe1a01004, 0xfdffffff }, // mov:6:0xE3A01004g
	{   9, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006g
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFDD2B1g
	{  11, 0xe59f73cc, 0xfdffffff }, // ldr:4:0xE59F73CCg
	{  12, 0xe04f3f41, 0xfdffffff }, // sub:6:0xE24F3F41g
	{  13, 0xe58d7000, 0xfdffffff }, // str:4:0xE58D7000g
	{  14, 0xe5950008, 0xfdffffff }, // ldr:4:0xE5950008g
	{  15, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006g
	{  16, 0xe1a01003, 0xfdffffff }, // mov:6:0xE3A01003g
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFDD2B5g
	{  18, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  19, 0x11a01007, 0xfdffffff }, // mov:6:0x11A01007g
	{  20, 0x104f0f49, 0xfdffffff }, // sub:6:0x124F0F49g
	{  21, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFDD2D6g
	{  22, 0xe5950008, 0xfdffffff }, // ldr:4:0xE5950008g
	{  23, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFE0643g
	{  25, 0xe5950008, 0xfdffffff }, // ldr:4:0xE5950008g
	{  26, 0xe1a01003, 0xfdffffff }, // mov:6:0xE3A01003g
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFE0632g
	{  28, 0xe59d0004, 0xfdffffff }, // ldr:4:0xE59D0004g
	{  29, 0xe1100001, 0xfdffffff }, // tst:7:0xE3100001g
	{  30, 0x11a04001, 0xfdffffff }, // mov:6:0x13A04001g
	{  31, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{ -1, -1, -1 },g
	/* 31/32 */g
};g
g
static FuncSig func_sig_open_1[] = {g
	{   1, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002g
	{   2, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001g
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE9Cg
	{   5, 0xe0505000, 0xfdffffff }, // sub:6:0xE2505000g
	{   6, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000002g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE576g
	{   8, 0xe1a01017, 0xfdffffff }, // mov:6:0xE3A01017g
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009g
	{  10, 0xe08d2008, 0xfdffffff }, // add:6:0xE28D2008g
	{  11, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{  12, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFBCg
	{  14, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005g
	{  16, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEB1g
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE56Bg
	{  19, 0xe1a01002, 0xfdffffff }, // mov:6:0xE3A01002g
	{  20, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{  21, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000Dg
	{  22, 0xe59f0420, 0xfdffffff }, // ldr:4:0xE59F0420g
	{  23, 0xe59d1008, 0xfdffffff }, // ldr:4:0xE59D1008g
	{  24, 0xe58d5000, 0xfdffffff }, // str:4:0xE58D5000g
	{  25, 0xe5900101, 0xfdffffff }, // ldr:4:0xE7900101g
	{  26, 0xe59d1004, 0xfdffffff }, // ldr:4:0xE59D1004g
	{  27, 0xe590c000, 0xfdffffff }, // ldr:4:0xE590C000g
	{  28, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  29, 0xe1a03007, 0xfdffffff }, // mov:6:0xE1A03007g
	{  30, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006g
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
static FuncSig func_sig_write_1[] = {g
	{   1, 0xe1b04002, 0xfdffffff }, // mov:6:0xE1B04002g
	{   2, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{   3, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008g
	{   5, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{   6, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE0Fg
	{   8, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   9, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000004g
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE4B5g
	{  11, 0xe1a01009, 0xfdffffff }, // mov:6:0xE3A01009g
	{  12, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{  15, 0xe59f0144, 0xfdffffff }, // ldr:4:0xE59F0144g
	{  16, 0xe59d1004, 0xfdffffff }, // ldr:4:0xE59D1004g
	{  17, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004g
	{  18, 0xe5900101, 0xfdffffff }, // ldr:4:0xE7900101g
	{  19, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{  20, 0xe5903010, 0xfdffffff }, // ldr:4:0xE5903010g
	{  21, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{  25, 0xe1b04003, 0xfdffffff }, // mov:6:0xE1B04003g
	{  26, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{  27, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002g
	{  28, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{  29, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008g
	{  30, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{  31, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{ -1, -1, -1 },g
	/* 26/32 */g
};g
g
static FuncSig func_sig_close_1[] = {g
	{   1, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{   2, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEA4g
	{   5, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   6, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000004g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE54Ag
	{   8, 0xe1a01009, 0xfdffffff }, // mov:6:0xE3A01009g
	{   9, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{  12, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE89g
	{  14, 0xe59f0390, 0xfdffffff }, // ldr:4:0xE59F0390g
	{  15, 0xe59d1004, 0xfdffffff }, // ldr:4:0xE59D1004g
	{  16, 0xe5900101, 0xfdffffff }, // ldr:4:0xE7900101g
	{  17, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004g
	{  18, 0xe5902004, 0xfdffffff }, // ldr:4:0xE5902004g
	{  19, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{  23, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{  24, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE8Fg
	{  26, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  27, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000003g
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE535g
	{  29, 0xe1a01009, 0xfdffffff }, // mov:6:0xE3A01009g
	{  30, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{  31, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000005g
	{ -1, -1, -1 },g
	/* 26/32 */g
};g
g
static FuncSig func_sig_lseek_1[] = {g
	{   1, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{   2, 0xe04dd034, 0xfdffffff }, // sub:6:0xE24DD034g
	{   3, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   4, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001g
	{   5, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000Bg
	{   6, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004g
	{   7, 0xe1a01010, 0xfdffffff }, // mov:6:0xE3A01010g
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD510g
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  11, 0xba000000, 0xff000000 }, // b, bl:3:0xBA000023g
	{  12, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  13, 0xe1a0100f, 0xfdffffff }, // mov:6:0xE3A0100Fg
	{  14, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD50Ag
	{  16, 0xe08dd034, 0xfdffffff }, // add:6:0xE28DD034g
	{  18, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001g
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000Fg
	{  20, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  21, 0xe1a0100f, 0xfdffffff }, // mov:6:0xE3A0100Fg
	{  22, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD502g
	{  24, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  25, 0xba000000, 0xff000000 }, // b, bl:3:0xBA000015g
	{  26, 0xe0844000, 0xfdffffff }, // add:6:0xE0844000g
	{  27, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000011g
	{  28, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004g
	{  29, 0xe1a01010, 0xfdffffff }, // mov:6:0xE3A01010g
	{  30, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD4FAg
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
static FuncSig func_sig_read_1[] = {g
	{   1, 0xe1b04002, 0xfdffffff }, // mov:6:0xE1B04002g
	{   2, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{   3, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008g
	{   5, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{   6, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE27g
	{   8, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   9, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000004g
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE4CDg
	{  11, 0xe1a01009, 0xfdffffff }, // mov:6:0xE3A01009g
	{  12, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{  15, 0xe59f01a4, 0xfdffffff }, // ldr:4:0xE59F01A4g
	{  16, 0xe59d1004, 0xfdffffff }, // ldr:4:0xE59D1004g
	{  17, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004g
	{  18, 0xe5900101, 0xfdffffff }, // ldr:4:0xE7900101g
	{  19, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{  20, 0xe590300c, 0xfdffffff }, // ldr:4:0xE590300Cg
	{  21, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{  25, 0xe1b04002, 0xfdffffff }, // mov:6:0xE1B04002g
	{  26, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{  27, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{  28, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008g
	{  29, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{  30, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE0Fg
	{ -1, -1, -1 },g
	/* 26/32 */g
};g
g
static FuncSig func_sig_Fopen_Fut_1[] = {g
	{   1, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001g
	{   2, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   3, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000B3g
	{   5, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   6, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000D1g
	{   8, 0xe1a01006, 0xfdffffff }, // mov:6:0xE1A01006g
	{   9, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B190g
	{  11, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  12, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000B4g
	{  14, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  17, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{  19, 0xe04dd03c, 0xfdffffff }, // sub:6:0xE24DD03Cg
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000023g
	{  21, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE7A7g
	{  23, 0xe1500020, 0xfdffffff }, // cmp:7:0xE3500020g
	{  24, 0xd08d5018, 0xfdffffff }, // add:6:0xD28D5018g
	{  25, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000002g
	{  26, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001g
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001355g
	{  28, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  29, 0xe0841020, 0xfdffffff }, // add:6:0xE2841020g
	{  30, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE778g
	{ -1, -1, -1 },g
	/* 28/32 */g
};g
g
static FuncSig func_sig_Fwrite_Fut_1[] = {g
	{   1, 0xe1b04003, 0xfdffffff }, // mov:6:0xE1B04003g
	{   2, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000g
	{   4, 0xe1a08002, 0xfdffffff }, // mov:6:0xE1A08002g
	{   5, 0xe1a07001, 0xfdffffff }, // mov:6:0xE1A07001g
	{   7, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   8, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00005Eg
	{  10, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  11, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006g
	{  12, 0xe1a03004, 0xfdffffff }, // mov:6:0xE1A03004g
	{  13, 0xe1a02008, 0xfdffffff }, // mov:6:0xE1A02008g
	{  14, 0xe1a01007, 0xfdffffff }, // mov:6:0xE1A01007g
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B1DBg
	{  16, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  17, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00005Fg
	{  19, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  22, 0xe1b04002, 0xfdffffff }, // mov:6:0xE1B04002g
	{  23, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000g
	{  24, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{  25, 0xe1a07001, 0xfdffffff }, // mov:6:0xE1A07001g
	{  27, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{  28, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00004Ag
	{  30, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  31, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006g
	{ -1, -1, -1 },g
	/* 26/32 */g
};g
g
static FuncSig func_sig_Fclose_Fut_1[] = {g
	{   1, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{   3, 0xe04dd03c, 0xfdffffff }, // sub:6:0xE24DD03Cg
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000023g
	{   5, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE7A7g
	{   7, 0xe1500020, 0xfdffffff }, // cmp:7:0xE3500020g
	{   8, 0xd08d5018, 0xfdffffff }, // add:6:0xD28D5018g
	{   9, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000002g
	{  10, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001355g
	{  12, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  13, 0xe0841020, 0xfdffffff }, // add:6:0xE2841020g
	{  14, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE778g
	{  16, 0xe5946008, 0xfdffffff }, // ldr:4:0xE5946008g
	{  17, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{  18, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000094g
	{  20, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000g
	{  21, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000B2g
	{  23, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B1B4g
	{  25, 0xe1560000, 0xfdffffff }, // cmp:7:0xE3560000g
	{  26, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  27, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002g
	{  28, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD9Fg
	{  30, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000002g
	{  31, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100Dg
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
static FuncSig func_sig_Fread_Fut_1[] = {g
	{   1, 0xe1b04003, 0xfdffffff }, // mov:6:0xE1B04003g
	{   2, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000g
	{   4, 0xe1a08002, 0xfdffffff }, // mov:6:0xE1A08002g
	{   5, 0xe1a07001, 0xfdffffff }, // mov:6:0xE1A07001g
	{   7, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   8, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000073g
	{  10, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  11, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006g
	{  12, 0xe1a03004, 0xfdffffff }, // mov:6:0xE1A03004g
	{  13, 0xe1a02008, 0xfdffffff }, // mov:6:0xE1A02008g
	{  14, 0xe1a01007, 0xfdffffff }, // mov:6:0xE1A01007g
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B1A9g
	{  16, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  17, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000074g
	{  19, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  22, 0xe1b04003, 0xfdffffff }, // mov:6:0xE1B04003g
	{  23, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000g
	{  25, 0xe1a08002, 0xfdffffff }, // mov:6:0xE1A08002g
	{  26, 0xe1a07001, 0xfdffffff }, // mov:6:0xE1A07001g
	{  28, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{  29, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00005Eg
	{  31, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_Fseek_Fut_1[] = {g
	{   1, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{   3, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002g
	{   4, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001g
	{   6, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   7, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000037g
	{   9, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  10, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  11, 0xe1a02007, 0xfdffffff }, // mov:6:0xE1A02007g
	{  12, 0xe1a01006, 0xfdffffff }, // mov:6:0xE1A01006g
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B233g
	{  14, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  15, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000039g
	{  17, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  20, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{  23, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{  24, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000026g
	{  26, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  27, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B234g
	{  29, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  30, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00002Ag
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_Remove_1[] = {g
	{   1, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF2g
	{   3, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{   4, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008g
	{   5, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00AADCg
	{   7, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{   8, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000176g
	{  10, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000185g
	{  12, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  14, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  17, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFE2g
	{  19, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{  20, 0x01a00005, 0xfdffffff }, // mov:6:0x01A00005g
	{  21, 0x0b000000, 0xff000000 }, // b, bl:3:0x0B00AACDg
	{  22, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  24, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFD4DBg
	{  26, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000g
	{  27, 0xe1a05002, 0xfdffffff }, // mov:6:0xE1A05002g
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD4EFg
	{  29, 0xe1500005, 0xfdffffff }, // cmp:7:0xE1500005g
	{  30, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  31, 0x11a00006, 0xfdffffff }, // mov:6:0x11A00006g
	{ -1, -1, -1 },g
	/* 26/32 */g
};g
g
static FuncSig func_sig_rename_1[] = {g
	{   1, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{   3, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD426g
	{   5, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000g
	{   8, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005g
	{   9, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE3A0100Bg
	{  10, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD529g
	{  12, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD448g
	{  15, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  18, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001g
	{  19, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFEAg
	{  21, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{  22, 0x01a01006, 0xfdffffff }, // mov:6:0x01A01006g
	{  23, 0x01a00005, 0xfdffffff }, // mov:6:0x01A00005g
	{  24, 0x0b000000, 0xff000000 }, // b, bl:3:0x0B00AABDg
	{  25, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  28, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{  29, 0xe04dd034, 0xfdffffff }, // sub:6:0xE24DD034g
	{  30, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  31, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_GetDrive_ClusterSize_1[] = {g
	{   0, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{   2, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   3, 0xa59f0058, 0xfdffffff }, // ldr:4:0xA59F0058g
	{   4, 0xa59f1084, 0xfdffffff }, // ldr:4:0xA59F1084g
	{   5, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF32EEg
	{   6, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{   7, 0xe51f1778, 0xfdffffff }, // ldr:4:0xE51F1778g
	{   8, 0xe0000094, 0xfdffffff }, // and:6:0xE0000094 mul:11:0xE0000094g
	{   9, 0xe0810100, 0xfdffffff }, // add:6:0xE0810100g
	{  10, 0xe5900054, 0xfdffffff }, // ldr:4:0xE5900054g
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0008E5g
	{  13, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  15, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  16, 0xa59f0024, 0xfdffffff }, // ldr:4:0xA59F0024g
	{  17, 0xa1a01e57, 0xfdffffff }, // mov:6:0xA3A01E57g
	{  18, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF32E1g
	{  19, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{  20, 0xe51f17ac, 0xfdffffff }, // ldr:4:0xE51F17ACg
	{  21, 0xe0000094, 0xfdffffff }, // and:6:0xE0000094 mul:11:0xE0000094g
	{  22, 0xe0810100, 0xfdffffff }, // add:6:0xE0810100g
	{  23, 0xe5900054, 0xfdffffff }, // ldr:4:0xE5900054g
	{  25, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0008DCg
	{  26, 0x000004c4, 0xfdffffff }, // and:6:0x000004C4g
	{  28, 0x000004cf, 0xfdffffff }, // and:6:0x000004CFg
	{  29, 0x000004dd, 0xfdffffff }, // and:6:0x000004DDg
	{  30, 0x000004f7, 0xfdffffff }, // and:6:0x000004F7g
	{ -1, -1, -1 },g
	/* 28/32 */g
};g
g
static FuncSig func_sig_GetDrive_TotalClusters_1[] = {g
	{   0, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{   2, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   3, 0xa59f0024, 0xfdffffff }, // ldr:4:0xA59F0024g
	{   4, 0xa1a01e57, 0xfdffffff }, // mov:6:0xA3A01E57g
	{   5, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF32E1g
	{   6, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{   7, 0xe51f17ac, 0xfdffffff }, // ldr:4:0xE51F17ACg
	{   8, 0xe0000094, 0xfdffffff }, // and:6:0xE0000094 mul:11:0xE0000094g
	{   9, 0xe0810100, 0xfdffffff }, // add:6:0xE0810100g
	{  10, 0xe5900054, 0xfdffffff }, // ldr:4:0xE5900054g
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0008DCg
	{  13, 0x000004c4, 0xfdffffff }, // and:6:0x000004C4g
	{  15, 0x000004cf, 0xfdffffff }, // and:6:0x000004CFg
	{  16, 0x000004dd, 0xfdffffff }, // and:6:0x000004DDg
	{  17, 0x000004f7, 0xfdffffff }, // and:6:0x000004F7g
	{  19, 0x000004fd, 0xfdffffff }, // and:6:0x000004FDg
	{  21, 0x00005450, 0xfdffffff }, // and:6:0x00005450g
	{  22, 0x00000522, 0xfdffffff }, // and:6:0x00000522g
	{  23, 0x00000531, 0xfdffffff }, // and:6:0x00000531g
	{  24, 0x0000054e, 0xfdffffff }, // and:6:0x0000054Eg
	{  25, 0x00000554, 0xfdffffff }, // and:6:0x00000554g
	{  26, 0x0000055f, 0xfdffffff }, // and:6:0x0000055Fg
	{  27, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  29, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  30, 0xa51f0048, 0xfdffffff }, // ldr:4:0xA51F0048g
	{  31, 0xa59f12e0, 0xfdffffff }, // ldr:4:0xA59F12E0g
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_GetDrive_FreeClusters_1[] = {g
	{   0, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{   2, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   3, 0xa51f0048, 0xfdffffff }, // ldr:4:0xA51F0048g
	{   4, 0xa59f12e0, 0xfdffffff }, // ldr:4:0xA59F12E0g
	{   5, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF32C6g
	{   6, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{   7, 0xe51f1818, 0xfdffffff }, // ldr:4:0xE51F1818g
	{   8, 0xe0000094, 0xfdffffff }, // and:6:0xE0000094 mul:11:0xE0000094g
	{   9, 0xe0810100, 0xfdffffff }, // add:6:0xE0810100g
	{  10, 0xe5900054, 0xfdffffff }, // ldr:4:0xE5900054g
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0008C6g
	{  13, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  15, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  16, 0xa51f007c, 0xfdffffff }, // ldr:4:0xA51F007Cg
	{  17, 0xa59f12b0, 0xfdffffff }, // ldr:4:0xA59F12B0g
	{  18, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF32B9g
	{  19, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{  20, 0xe51f184c, 0xfdffffff }, // ldr:4:0xE51F184Cg
	{  21, 0xe0000094, 0xfdffffff }, // and:6:0xE0000094 mul:11:0xE0000094g
	{  22, 0xe0810100, 0xfdffffff }, // add:6:0xE0810100g
	{  23, 0xe5900054, 0xfdffffff }, // ldr:4:0xE5900054g
	{  25, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0008BDg
	{  26, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  28, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  29, 0xa59f1284, 0xfdffffff }, // ldr:4:0xA59F1284g
	{  30, 0xa04f0e85, 0xfdffffff }, // sub:6:0xA24F0E85g
	{  31, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF32ACg
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_LockMainPower_1[] = {g
	{   1, 0xe59f410c, 0xfdffffff }, // ldr:4:0xE59F410Cg
	{   2, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{   3, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{   4, 0x11a010c1, 0xfdffffff }, // mov:6:0x13A010C1g
	{   5, 0x108f0f41, 0xfdffffff }, // add:6:0x128F0F41g
	{   6, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFEC043g
	{   7, 0xe59f1108, 0xfdffffff }, // ldr:4:0xE59F1108g
	{   8, 0xe5940024, 0xfdffffff }, // ldr:4:0xE5940024g
	{   9, 0xe1a030c3, 0xfdffffff }, // mov:6:0xE3A030C3g
	{  10, 0xe08f20f0, 0xfdffffff }, // add:6:0xE28F20F0g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFEC02Fg
	{  12, 0xe5940018, 0xfdffffff }, // ldr:4:0xE5940018g
	{  13, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001g
	{  14, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  15, 0xe5840018, 0xfdffffff }, // str:4:0xE5840018g
	{  16, 0x05940028, 0xfdffffff }, // ldr:4:0x05940028g
	{  17, 0x01a01000, 0xfdffffff }, // mov:6:0x03A01000g
	{  18, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFFFB41g
	{  19, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{  20, 0xe5840008, 0xfdffffff }, // str:4:0xE5840008g
	{  21, 0xe5940004, 0xfdffffff }, // ldr:4:0xE5940004g
	{  22, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  23, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{  24, 0x05840004, 0xfdffffff }, // str:4:0x05840004g
	{  25, 0x0b000000, 0xff000000 }, // b, bl:3:0x0B00005Bg
	{  26, 0xe5940024, 0xfdffffff }, // ldr:4:0xE5940024g
	{  28, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFEF529g
	{  30, 0xe59f4098, 0xfdffffff }, // ldr:4:0xE59F4098g
	{  31, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_UnlockMainPower_1[] = {g
	{   1, 0xe59f41b8, 0xfdffffff }, // ldr:4:0xE59F41B8g
	{   2, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{   3, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{   4, 0x11a010d4, 0xfdffffff }, // mov:6:0x13A010D4g
	{   5, 0x108f0e1b, 0xfdffffff }, // add:6:0x128F0E1Bg
	{   6, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFEC06Eg
	{   7, 0xe5940018, 0xfdffffff }, // ldr:4:0xE5940018g
	{   8, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  10, 0xe5940024, 0xfdffffff }, // ldr:4:0xE5940024g
	{  11, 0xe59f11a4, 0xfdffffff }, // ldr:4:0xE59F11A4g
	{  12, 0xe1a030d9, 0xfdffffff }, // mov:6:0xE3A030D9g
	{  13, 0xe08f2e19, 0xfdffffff }, // add:6:0xE28F2E19g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFEC057g
	{  15, 0xe5940018, 0xfdffffff }, // ldr:4:0xE5940018g
	{  16, 0xe0500001, 0xfdffffff }, // sub:6:0xE2500001g
	{  17, 0xe5840018, 0xfdffffff }, // str:4:0xE5840018g
	{  18, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000014g
	{  19, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  20, 0xe5840008, 0xfdffffff }, // str:4:0xE5840008g
	{  21, 0xe594002c, 0xfdffffff }, // ldr:4:0xE594002Cg
	{  22, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFB67g
	{  24, 0xe594000c, 0xfdffffff }, // ldr:4:0xE594000Cg
	{  25, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  26, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000Cg
	{  27, 0xe5940010, 0xfdffffff }, // ldr:4:0xE5940010g
	{  28, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  29, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000009g
	{  30, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{  31, 0xe5840004, 0xfdffffff }, // str:4:0xE5840004g
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
static FuncSig func_sig_GetCurrentAvValue_1[] = {g
	{   0, 0xe51f093c, 0xfdffffff }, // ldr:4:0xE51F093Cg
	{   2, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   3, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   4, 0x059f154c, 0xfdffffff }, // ldr:4:0x059F154Cg
	{   5, 0x059f0514, 0xfdffffff }, // ldr:4:0x059F0514g
	{   6, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFC30F4g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB032C91g
	{   8, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   9, 0xe08d0004, 0xfdffffff }, // add:6:0xE28D0004g
	{  10, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100Dg
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB032E24g
	{  13, 0xe1540000, 0xfdffffff }, // cmp:7:0xE1540000g
	{  14, 0xb1a04000, 0xfdffffff }, // mov:6:0xB1A04000g
	{  16, 0xe1540000, 0xfdffffff }, // cmp:7:0xE1540000g
	{  17, 0xc1a04000, 0xfdffffff }, // mov:6:0xC1A04000g
	{  18, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB032E75g
	{  20, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000CB6g
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB032DB4g
	{  23, 0xe0840000, 0xfdffffff }, // add:6:0xE0840000g
	{  24, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800g
	{  25, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840g
	{  28, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002g
	{  29, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{  30, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000CACg
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_MoveFocusLensToDistance_1[] = {g
	{   1, 0xe59f5218, 0xfdffffff }, // ldr:4:0xE59F5218g
	{   2, 0xe5904000, 0xfdffffff }, // ldr:4:0xE5904000g
	{   3, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000g
	{   4, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF9CA23g
	{   6, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{   7, 0xe04f1fb6, 0xfdffffff }, // sub:6:0xE24F1FB6g
	{   8, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0g
	{  10, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000g
	{  12, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  13, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF9C9B2g
	{  16, 0xe59f41dc, 0xfdffffff }, // ldr:4:0xE59F41DCg
	{  17, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  18, 0x004f0fca, 0xfdffffff }, // sub:6:0x024F0FCAg
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFD5A77g
	{  21, 0xe584000c, 0xfdffffff }, // str:4:0xE584000Cg
	{  23, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  24, 0xe04f1fcf, 0xfdffffff }, // sub:6:0xE24F1FCFg
	{  25, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFD5ACBg
	{  27, 0xe59f41b0, 0xfdffffff }, // ldr:4:0xE59F41B0g
	{  28, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{  29, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF9CA0Ag
	{  31, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{ -1, -1, -1 },g
	/* 26/32 */g
};g
g
static FuncSig func_sig_MoveZoomLensWithPoint_1[] = {g
	{   2, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{   3, 0xe04f10cc, 0xfdffffff }, // sub:6:0xE24F10CCg
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD5Eg
	{   5, 0xe51f0c78, 0xfdffffff }, // ldr:4:0xE51F0C78g
	{   6, 0xe59f2148, 0xfdffffff }, // ldr:4:0xE59F2148g
	{   7, 0xe59f11b0, 0xfdffffff }, // ldr:4:0xE59F11B0g
	{   8, 0xe5900044, 0xfdffffff }, // ldr:4:0xE5900044g
	{   9, 0xe1a03e36, 0xfdffffff }, // mov:6:0xE3A03E36g
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFC2132g
	{  11, 0xe1100001, 0xfdffffff }, // tst:7:0xE3100001g
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFD0EEFg
	{  14, 0xe1b00a20, 0xfdffffff }, // mov:6:0xE1B00A20g
	{  19, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  20, 0xe04f1e11, 0xfdffffff }, // sub:6:0xE24F1E11g
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF1Ag
	{  22, 0xe59f3180, 0xfdffffff }, // ldr:4:0xE59F3180g
	{  23, 0xe04f2ecb, 0xfdffffff }, // sub:6:0xE24F2ECBg
	{  24, 0xe59f116c, 0xfdffffff }, // ldr:4:0xE59F116Cg
	{  25, 0xe51f0cc8, 0xfdffffff }, // ldr:4:0xE51F0CC8g
	{  26, 0xe5900044, 0xfdffffff }, // ldr:4:0xE5900044g
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFC2121g
	{  28, 0xe1100001, 0xfdffffff }, // tst:7:0xE3100001g
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFD0EDEg
	{  31, 0xe1b00a20, 0xfdffffff }, // mov:6:0xE1B00A20g
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig__log_1[] = {g
	{   2, 0xe04dd028, 0xfdffffff }, // sub:6:0xE24DD028g
	{   3, 0xe08d1028, 0xfdffffff }, // add:6:0xE28D1028g
	{   4, 0xe59f3378, 0xfdffffff }, // ldr:4:0xE59F3378g
	{   6, 0xe1a04000, 0xfdffffff }, // mov:6:0xE3A04000g
	{   7, 0xe1510003, 0xfdffffff }, // cmp:7:0xE1510003g
	{   8, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000006g
	{  10, 0xe1520003, 0xfdffffff }, // cmp:7:0xE1520003g
	{  11, 0x8a000000, 0xff000000 }, // b, bl:3:0x8A000003g
	{  12, 0xe1520003, 0xfdffffff }, // cmp:7:0xE1520003g
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008g
	{  14, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  15, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006g
	{  16, 0xe08d1028, 0xfdffffff }, // add:6:0xE28D1028g
	{  17, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001g
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0007C5g
	{  20, 0xe08dd030, 0xfdffffff }, // add:6:0xE28DD030g
	{  23, 0xe1510601, 0xfdffffff }, // cmp:7:0xE3510601g
	{  24, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000013g
	{  26, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003g
	{  27, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFDDg
	{  29, 0xe08f1fc6, 0xfdffffff }, // add:6:0xE28F1FC6g
	{  30, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000004g
	{  31, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig__log10_1[] = {g
	{   2, 0xe59f3134, 0xfdffffff }, // ldr:4:0xE59F3134g
	{   4, 0xe1a04000, 0xfdffffff }, // mov:6:0xE3A04000g
	{   5, 0xe1510003, 0xfdffffff }, // cmp:7:0xE1510003g
	{   6, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000006g
	{   8, 0xe1520003, 0xfdffffff }, // cmp:7:0xE1520003g
	{   9, 0x8a000000, 0xff000000 }, // b, bl:3:0x8A000003g
	{  10, 0xe1520003, 0xfdffffff }, // cmp:7:0xE1520003g
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000006g
	{  12, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  13, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004g
	{  15, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001g
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000BF7g
	{  19, 0xe1510601, 0xfdffffff }, // cmp:7:0xE3510601g
	{  20, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000011g
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003g
	{  23, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000410g
	{  25, 0xe08f10dc, 0xfdffffff }, // add:6:0xE28F10DCg
	{  26, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000004g
	{  27, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{  28, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000004g
	{  29, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00040Ag
	{  31, 0xe08f10cc, 0xfdffffff }, // add:6:0xE28F10CCg
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig__pow_1[] = {g
	{   2, 0xe59f4358, 0xfdffffff }, // ldr:4:0xE59F4358g
	{   4, 0xe04dd0a8, 0xfdffffff }, // sub:6:0xE24DD0A8g
	{   5, 0xe59d30ac, 0xfdffffff }, // ldr:4:0xE59D30ACg
	{   6, 0xe59d10b4, 0xfdffffff }, // ldr:4:0xE59D10B4g
	{   7, 0xe59de0b0, 0xfdffffff }, // ldr:4:0xE59DE0B0g
	{   9, 0xe59da0a8, 0xfdffffff }, // ldr:4:0xE59DA0A8g
	{  10, 0xe1500004, 0xfdffffff }, // cmp:7:0xE1500004g
	{  12, 0xca000000, 0xff000000 }, // b, bl:3:0xCA00000Ag
	{  13, 0xe1500004, 0xfdffffff }, // cmp:7:0xE1500004g
	{  14, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001g
	{  15, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000g
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000006g
	{  17, 0xe1520004, 0xfdffffff }, // cmp:7:0xE1520004g
	{  18, 0xca000000, 0xff000000 }, // b, bl:3:0xCA000004g
	{  19, 0xe082c209, 0xfdffffff }, // add:6:0xE282C209g
	{  20, 0xe05cc6ff, 0xfdffffff }, // sub:6:0xE25CC6FFg
	{  21, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000007g
	{  22, 0xe15e0000, 0xfdffffff }, // cmp:7:0xE35E0000g
	{  23, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000005g
	{  24, 0xe08d30a8, 0xfdffffff }, // add:6:0xE28D30A8g
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000546g
	{  27, 0xe08dd0b8, 0xfdffffff }, // add:6:0xE28DD0B8g
	{  30, 0xe59d40ac, 0xfdffffff }, // ldr:4:0xE59D40ACg
	{  31, 0xe59d50a8, 0xfdffffff }, // ldr:4:0xE59D50A8g
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig__sqrt_1[] = {g
	{   0, 0xe1a0c207, 0xfdffffff }, // mov:6:0xE3A0C207g
	{   2, 0xe111000c, 0xfdffffff }, // tst:7:0xE111000Cg
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000044g
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000047g
	{   7, 0xe1110102, 0xfdffffff }, // tst:7:0xE3110102g
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00004Dg
	{   9, 0xe1a0ca21, 0xfdffffff }, // mov:6:0xE1A0CA21g
	{  12, 0xe08cc0fd, 0xfdffffff }, // add:6:0xE28CC0FDg
	{  13, 0xe1b0c0ac, 0xfdffffff }, // mov:6:0xE1B0C0ACg
	{  14, 0xe08ccd06, 0xfdffffff }, // add:6:0xE28CCD06g
	{  15, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000001g
	{  16, 0xe1b00080, 0xfdffffff }, // mov:6:0xE1B00080g
	{  18, 0xe1a01501, 0xfdffffff }, // mov:6:0xE1A01501g
	{  20, 0xe0411101, 0xfdffffff }, // sub:6:0xE2411101g
	{  21, 0xe1a00500, 0xfdffffff }, // mov:6:0xE1A00500g
	{  22, 0xe1a02101, 0xfdffffff }, // mov:6:0xE3A02101g
	{  23, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000g
	{  24, 0xe1a0e201, 0xfdffffff }, // mov:6:0xE3A0E201g
	{  25, 0xe0514002, 0xfdffffff }, // sub:6:0xE0514002g
	{  26, 0x2054400e, 0xfdffffff }, // sub:6:0x2054400Eg
	{  27, 0x21a01004, 0xfdffffff }, // mov:6:0x21A01004g
	{  28, 0x2082208e, 0xfdffffff }, // add:6:0x2082208Eg
	{  29, 0xe1b00080, 0xfdffffff }, // mov:6:0xE1B00080g
	{  31, 0xe1b0e0ae, 0xfdffffff }, // mov:6:0xE1B0E0AEg
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig_malloc_1[] = {g
	{   1, 0xe0800007, 0xfdffffff }, // add:6:0xE2800007g
	{   3, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001g
	{   4, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{   6, 0xe59f6184, 0xfdffffff }, // ldr:4:0xE59F6184g
	{   7, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{   8, 0xe5960014, 0xfdffffff }, // ldr:4:0xE5960014g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFA6Ag
	{  10, 0xe5964010, 0xfdffffff }, // ldr:4:0xE5964010g
	{  11, 0xe0860008, 0xfdffffff }, // add:6:0xE2860008g
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000022g
	{  13, 0xe5941004, 0xfdffffff }, // ldr:4:0xE5941004g
	{  14, 0xe1510005, 0xfdffffff }, // cmp:7:0xE1510005g
	{  15, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A00001Dg
	{  16, 0xe5941004, 0xfdffffff }, // ldr:4:0xE5941004g
	{  17, 0xe0411005, 0xfdffffff }, // sub:6:0xE0411005g
	{  18, 0xe151000c, 0xfdffffff }, // cmp:7:0xE351000Cg
	{  19, 0x35941008, 0xfdffffff }, // ldr:4:0x35941008g
	{  20, 0x35801008, 0xfdffffff }, // str:4:0x35801008g
	{  21, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000009g
	{  22, 0xe0841005, 0xfdffffff }, // add:6:0xE0841005g
	{  23, 0xe0811008, 0xfdffffff }, // add:6:0xE2811008g
	{  24, 0xe5801008, 0xfdffffff }, // str:4:0xE5801008g
	{  25, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{  26, 0xe5810008, 0xfdffffff }, // str:4:0xE5810008g
	{  27, 0xe5940004, 0xfdffffff }, // ldr:4:0xE5940004g
	{  28, 0xe0400005, 0xfdffffff }, // sub:6:0xE0400005g
	{  29, 0xe0400008, 0xfdffffff }, // sub:6:0xE2400008g
	{  30, 0xe5810004, 0xfdffffff }, // str:4:0xE5810004g
	{  31, 0xe5845004, 0xfdffffff }, // str:4:0xE5845004g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_free_1[] = {g
	{   1, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   3, 0xe0404008, 0xfdffffff }, // sub:6:0xE2404008g
	{   4, 0xe59f50b8, 0xfdffffff }, // ldr:4:0xE59F50B8g
	{   5, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{   6, 0xe5950014, 0xfdffffff }, // ldr:4:0xE5950014g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFA37g
	{   8, 0xe5950020, 0xfdffffff }, // ldr:4:0xE5950020g
	{   9, 0xe5941004, 0xfdffffff }, // ldr:4:0xE5941004g
	{  10, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001g
	{  11, 0xe5850020, 0xfdffffff }, // str:4:0xE5850020g
	{  12, 0xe5950028, 0xfdffffff }, // ldr:4:0xE5950028g
	{  13, 0xe0400001, 0xfdffffff }, // sub:6:0xE2400001g
	{  14, 0xe5850028, 0xfdffffff }, // str:4:0xE5850028g
	{  15, 0xe5951010, 0xfdffffff }, // ldr:4:0xE5951010g
	{  16, 0xe0850008, 0xfdffffff }, // add:6:0xE2850008g
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00001Dg
	{  18, 0xe1510004, 0xfdffffff }, // cmp:7:0xE1510004g
	{  19, 0x9a000000, 0xff000000 }, // b, bl:3:0x9A000019g
	{  20, 0xe5841008, 0xfdffffff }, // str:4:0xE5841008g
	{  21, 0xe5942004, 0xfdffffff }, // ldr:4:0xE5942004g
	{  22, 0xe0823004, 0xfdffffff }, // add:6:0xE0823004g
	{  23, 0xe0833008, 0xfdffffff }, // add:6:0xE2833008g
	{  24, 0xe1530001, 0xfdffffff }, // cmp:7:0xE1530001g
	{  25, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005g
	{  26, 0xe5913004, 0xfdffffff }, // ldr:4:0xE5913004g
	{  27, 0xe0822003, 0xfdffffff }, // add:6:0xE0822003g
	{  28, 0xe0822008, 0xfdffffff }, // add:6:0xE2822008g
	{  29, 0xe5842004, 0xfdffffff }, // str:4:0xE5842004g
	{  30, 0xe5911008, 0xfdffffff }, // ldr:4:0xE5911008g
	{  31, 0xe5841008, 0xfdffffff }, // str:4:0xE5841008g
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
static FuncSig func_sig_FreeUncacheableMemory_1[] = {g
	{   0, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   1, 0x10400020, 0xfdffffff }, // sub:6:0x12400020g
	{   3, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFC3g
	{   6, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFEAg
	{   8, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{   9, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005g
	{  10, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{  11, 0xe08f0014, 0xfdffffff }, // add:6:0xE28F0014g
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFF9F47g
	{  13, 0xe1a01059, 0xfdffffff }, // mov:6:0xE3A01059g
	{  14, 0xe08f0014, 0xfdffffff }, // add:6:0xE28F0014g
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFC9F6g
	{  16, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  20, 0x00000064, 0xfdffffff }, // and:6:0x00000064g
	{  22, 0x00632e65, 0xfdffffff }, // rsb:6:0x00632E65g
	{  24, 0xe590200c, 0xfdffffff }, // ldr:4:0xE590200Cg
	{  25, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  26, 0xe59f0498, 0xfdffffff }, // ldr:4:0xE59F0498g
	{  27, 0xe1a01014, 0xfdffffff }, // mov:6:0xE3A01014g
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00EADDg
	{  29, 0xe5940004, 0xfdffffff }, // ldr:4:0xE5940004g
	{  30, 0xe5941000, 0xfdffffff }, // ldr:4:0xE5941000g
	{  31, 0xe5810004, 0xfdffffff }, // str:4:0xE5810004g
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig_AllocateUncacheableMemory_1[] = {g
	{   1, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   2, 0xe0800040, 0xfdffffff }, // add:6:0xE2800040g
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFCFg
	{   4, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{   6, 0xe0852040, 0xfdffffff }, // add:6:0xE2852040g
	{   7, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004g
	{   8, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFF9BDBg
	{  11, 0xe0800020, 0xfdffffff }, // add:6:0xE2800020g
	{  13, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  14, 0x10400020, 0xfdffffff }, // sub:6:0x12400020g
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFC3g
	{  19, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFEAg
	{  21, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005g
	{  23, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{  24, 0xe08f0014, 0xfdffffff }, // add:6:0xE28F0014g
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFF9F47g
	{  26, 0xe1a01059, 0xfdffffff }, // mov:6:0xE3A01059g
	{  27, 0xe08f0014, 0xfdffffff }, // add:6:0xE28F0014g
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFC9F6g
	{  29, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{ -1, -1, -1 },g
	/* 23/32 */g
};g
g
static FuncSig func_sig_rand_1[] = {g
	{   1, 0xe59f4064, 0xfdffffff }, // ldr:4:0xE59F4064g
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{   3, 0xe5940004, 0xfdffffff }, // ldr:4:0xE5940004g
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFCE68g
	{   5, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{   6, 0xe59f1054, 0xfdffffff }, // ldr:4:0xE59F1054g
	{   7, 0xe0000091, 0xfdffffff }, // and:6:0xE0000091 mul:11:0xE0000091g
	{   9, 0xe0800a03, 0xfdffffff }, // add:6:0xE2800A03g
	{  10, 0xe0800039, 0xfdffffff }, // add:6:0xE2800039g
	{  11, 0xe0015820, 0xfdffffff }, // and:6:0xE0015820g
	{  12, 0xe5840000, 0xfdffffff }, // str:4:0xE5840000g
	{  13, 0xe5940004, 0xfdffffff }, // ldr:4:0xE5940004g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFCE51g
	{  15, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  18, 0xe08f2028, 0xfdffffff }, // add:6:0xE28F2028g
	{  19, 0xe1a01002, 0xfdffffff }, // mov:6:0xE3A01002g
	{  20, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFCDE8g
	{  22, 0xe59f1010, 0xfdffffff }, // ldr:4:0xE59F1010g
	{  24, 0xe5810004, 0xfdffffff }, // str:4:0xE5810004g
	{  26, 0x11a00000, 0xfdffffff }, // mov:6:0x13A00000g
	{  28, 0x00001bf0, 0xfdffffff }, // and:6:0x00001BF0g
	{  31, 0x006d6553, 0xfdffffff }, // rsb:6:0x006D6553g
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig_srand_1[] = {g
	{   0, 0xe59f1074, 0xfdffffff }, // ldr:4:0xE59F1074g
	{   1, 0xe5810000, 0xfdffffff }, // str:4:0xE5810000g
	{   4, 0xe59f4064, 0xfdffffff }, // ldr:4:0xE59F4064g
	{   5, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{   6, 0xe5940004, 0xfdffffff }, // ldr:4:0xE5940004g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFCE68g
	{   8, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{   9, 0xe59f1054, 0xfdffffff }, // ldr:4:0xE59F1054g
	{  10, 0xe0000091, 0xfdffffff }, // and:6:0xE0000091 mul:11:0xE0000091g
	{  12, 0xe0800a03, 0xfdffffff }, // add:6:0xE2800A03g
	{  13, 0xe0800039, 0xfdffffff }, // add:6:0xE2800039g
	{  14, 0xe0015820, 0xfdffffff }, // and:6:0xE0015820g
	{  15, 0xe5840000, 0xfdffffff }, // str:4:0xE5840000g
	{  16, 0xe5940004, 0xfdffffff }, // ldr:4:0xE5940004g
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFCE51g
	{  18, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  21, 0xe08f2028, 0xfdffffff }, // add:6:0xE28F2028g
	{  22, 0xe1a01002, 0xfdffffff }, // mov:6:0xE3A01002g
	{  23, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFCDE8g
	{  25, 0xe59f1010, 0xfdffffff }, // ldr:4:0xE59F1010g
	{  27, 0xe5810004, 0xfdffffff }, // str:4:0xE5810004g
	{  29, 0x11a00000, 0xfdffffff }, // mov:6:0x13A00000g
	{  31, 0x00001bf0, 0xfdffffff }, // and:6:0x00001BF0g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_stat_1[] = {g
	{   1, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{   3, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD3D8g
	{   5, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000g
	{   8, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005g
	{   9, 0xe1a01012, 0xfdffffff }, // mov:6:0xE3A01012g
	{  10, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD4DBg
	{  12, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD3FAg
	{  15, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  18, 0xe04dd038, 0xfdffffff }, // sub:6:0xE24DD038g
	{  19, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001g
	{  20, 0xe08d1004, 0xfdffffff }, // add:6:0xE28D1004g
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFE9g
	{  22, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  24, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000Cg
	{  25, 0xe59d000c, 0xfdffffff }, // ldr:4:0xE59D000Cg
	{  26, 0xe5840000, 0xfdffffff }, // str:4:0xE5840000g
	{  28, 0xe5840004, 0xfdffffff }, // str:4:0xE5840004g
	{  29, 0xe59d0020, 0xfdffffff }, // ldr:4:0xE59D0020g
	{  30, 0xe5840008, 0xfdffffff }, // str:4:0xE5840008g
	{  31, 0xe59d001c, 0xfdffffff }, // ldr:4:0xE59D001Cg
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_openfastdir_1[] = {g
	{   1, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   2, 0xe1a00014, 0xfdffffff }, // mov:6:0xE3A00014g
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF95F20g
	{   4, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{   5, 0x01a01059, 0xfdffffff }, // mov:6:0x03A01059g
	{   6, 0x008f0e26, 0xfdffffff }, // add:6:0x028F0E26g
	{   7, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BF9295Cg
	{   9, 0xe5840000, 0xfdffffff }, // str:4:0xE5840000g
	{  10, 0xe1a00902, 0xfdffffff }, // mov:6:0xE3A00902g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF95F44g
	{  12, 0xe1a01902, 0xfdffffff }, // mov:6:0xE3A01902g
	{  14, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  15, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  16, 0xe584100c, 0xfdffffff }, // str:4:0xE584100Cg
	{  17, 0xe5841010, 0xfdffffff }, // str:4:0xE5841010g
	{  18, 0x01a01060, 0xfdffffff }, // mov:6:0x03A01060g
	{  19, 0x008f0f8b, 0xfdffffff }, // add:6:0x028F0F8Bg
	{  20, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BF9294Fg
	{  21, 0xe1a02f49, 0xfdffffff }, // mov:6:0xE3A02F49g
	{  22, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  23, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF94D26g
	{  26, 0xe5840000, 0xfdffffff }, // str:4:0xE5840000g
	{  27, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004g
	{  28, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFB0g
	{  30, 0xe1500002, 0xfdffffff }, // cmp:7:0xE3500002g
	{  31, 0x11a00004, 0xfdffffff }, // mov:6:0x11A00004g
	{ -1, -1, -1 },g
	/* 28/32 */g
};g
g
static FuncSig func_sig_readfastdir_1[] = {g
	{   1, 0xe1b05000, 0xfdffffff }, // mov:6:0xE1B05000g
	{   2, 0xe1a07001, 0xfdffffff }, // mov:6:0xE1A07001g
	{   3, 0xe1a06000, 0xfdffffff }, // mov:6:0xE3A06000g
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000027g
	{   5, 0xe5952010, 0xfdffffff }, // ldr:4:0xE5952010g
	{   6, 0xe595400c, 0xfdffffff }, // ldr:4:0xE595400Cg
	{   7, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000014g
	{   8, 0xe5950004, 0xfdffffff }, // ldr:4:0xE5950004g
	{   9, 0xe0800004, 0xfdffffff }, // add:6:0xE0800004g
	{  11, 0xe151000f, 0xfdffffff }, // cmp:7:0xE351000Fg
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000Ag
	{  13, 0xe1110008, 0xfdffffff }, // tst:7:0xE3110008g
	{  14, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008g
	{  16, 0xe15100e5, 0xfdffffff }, // cmp:7:0xE35100E5g
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009g
	{  18, 0xe1a01007, 0xfdffffff }, // mov:6:0xE1A01007g
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000029g
	{  20, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{  21, 0xe585000c, 0xfdffffff }, // str:4:0xE585000Cg
	{  22, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006g
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000008g
	{  25, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  26, 0x01a00001, 0xfdffffff }, // mov:6:0x03A00001g
	{  27, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004g
	{  28, 0xe0844020, 0xfdffffff }, // add:6:0xE2844020g
	{  29, 0xe1520004, 0xfdffffff }, // cmp:7:0xE1520004g
	{  30, 0xca000000, 0xff000000 }, // b, bl:3:0xCAFFFFE8g
	{  31, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{ -1, -1, -1 },g
	/* 28/32 */g
};g
g
static FuncSig func_sig_closefastdir_1[] = {g
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   2, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   4, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BF94CEBg
	{   5, 0xe5940004, 0xfdffffff }, // ldr:4:0xE5940004g
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF95EFDg
	{   7, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF95EC2g
	{  11, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{  12, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{  13, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  14, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  15, 0xe1a02008, 0xfdffffff }, // mov:6:0xE3A02008g
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000038g
	{  18, 0xe1510020, 0xfdffffff }, // cmp:7:0xE3510020g
	{  19, 0x11a0102e, 0xfdffffff }, // mov:6:0x13A0102Eg
	{  21, 0x10841008, 0xfdffffff }, // add:6:0x12841008g
	{  22, 0x11a02003, 0xfdffffff }, // mov:6:0x13A02003g
	{  23, 0x1b000000, 0xff000000 }, // b, bl:3:0x1B000031g
	{  24, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  27, 0xe1500005, 0xfdffffff }, // cmp:7:0xE3500005g
	{  28, 0x01a000e5, 0xfdffffff }, // mov:6:0x03A000E5g
	{ -1, -1, -1 },g
	/* 21/32 */g
};g
g
static FuncSig func_sig_qsort_1[] = {g
	{   3, 0xe1120003, 0xfdffffff }, // tst:7:0xE3120003g
	{   4, 0x059f2020, 0xfdffffff }, // ldr:4:0x059F2020g
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002g
	{   6, 0xe1120001, 0xfdffffff }, // tst:7:0xE3120001g
	{   7, 0x104f2e4b, 0xfdffffff }, // sub:6:0x124F2E4Bg
	{   8, 0x004f2e49, 0xfdffffff }, // sub:6:0x024F2E49g
	{   9, 0xe58d2008, 0xfdffffff }, // str:4:0xE58D2008g
	{  10, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFC1g
	{  13, 0x0000bb00, 0xfdffffff }, // and:6:0x0000BB00g
	{  17, 0xe59d100c, 0xfdffffff }, // ldr:4:0xE59D100Cg
	{  18, 0xe08d2010, 0xfdffffff }, // add:6:0xE28D2010g
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB02AE7Dg
	{  20, 0xe49d4004, 0xfdffffff }, // ldr:4:0xE49D4004g
	{  21, 0xe49df014, 0xfdffffff }, // ldr:4:0xE49DF014g
	{  22, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  23, 0x1590101c, 0xfdffffff }, // ldr:4:0x1590101Cg
	{  24, 0x11510000, 0xfdffffff }, // cmp:7:0x13510000g
	{  27, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  28, 0xe5802008, 0xfdffffff }, // str:4:0xE5802008g
	{  29, 0xe5802014, 0xfdffffff }, // str:4:0xE5802014g
	{  30, 0xe1a03001, 0xfdffffff }, // mov:6:0xE3A03001g
	{  31, 0xe5a02018, 0xfdffffff }, // str:4:0xE5A02018g
	{ -1, -1, -1 },g
	/* 23/32 */g
};g
g
static FuncSig func_sig_strncpy_1[] = {g
	{   0, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000g
	{   1, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009g
	{   3, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000g
	{   5, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005g
	{   6, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{   7, 0xe0422001, 0xfdffffff }, // sub:6:0xE2422001g
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFBg
	{  12, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001g
	{  13, 0x2a000000, 0xff000000 }, // b, bl:3:0x2AFFFFF3g
	{  15, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000008g
	{  17, 0xe1520003, 0xfdffffff }, // cmp:7:0xE1520003g
	{  18, 0x00800001, 0xfdffffff }, // add:6:0x02800001g
	{  19, 0x00811001, 0xfdffffff }, // add:6:0x02811001g
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003g
	{  23, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001g
	{  26, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{  28, 0x01530000, 0xfdffffff }, // cmp:7:0x03530000g
	{  29, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF1g
	{  30, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{ -1, -1, -1 },g
	/* 19/32 */g
};g
g
static FuncSig func_sig_strrchr_1[] = {g
	{   0, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{   1, 0xe00130ff, 0xfdffffff }, // and:6:0xE20130FFg
	{   3, 0xe1510003, 0xfdffffff }, // cmp:7:0xE1510003g
	{   4, 0x01a02000, 0xfdffffff }, // mov:6:0x01A02000g
	{   5, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{   6, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001g
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9g
	{   8, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002g
	{  10, 0xe1520010, 0xfdffffff }, // cmp:7:0xE3520010g
	{  11, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000g
	{  12, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000032g
	{  13, 0xe1130003, 0xfdffffff }, // tst:7:0xE3130003g
	{  15, 0x10422001, 0xfdffffff }, // sub:6:0x12422001g
	{  17, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFAg
	{  18, 0xe011c003, 0xfdffffff }, // and:6:0xE211C003g
	{  19, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000Dg
	{  20, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE35C0001g
	{  21, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000029g
	{  22, 0xe15c0002, 0xfdffffff }, // cmp:7:0xE35C0002g
	{  23, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000027g
	{  24, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00001Ag
	{  25, 0xe491c004, 0xfdffffff }, // ldr:4:0xE491C004g
	{  26, 0xe0422010, 0xfdffffff }, // sub:6:0xE2422010g
	{  27, 0xe483c004, 0xfdffffff }, // str:4:0xE483C004g
	{  28, 0xe491c004, 0xfdffffff }, // ldr:4:0xE491C004g
	{  29, 0xe483c004, 0xfdffffff }, // str:4:0xE483C004g
	{  30, 0xe491c004, 0xfdffffff }, // ldr:4:0xE491C004g
	{  31, 0xe483c004, 0xfdffffff }, // str:4:0xE483C004g
	{ -1, -1, -1 },g
	/* 28/32 */g
};g
g
static FuncSig func_sig_strncmp_1[] = {g
	{   0, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000008g
	{   2, 0xe153000c, 0xfdffffff }, // cmp:7:0xE153000Cg
	{   3, 0x00800001, 0xfdffffff }, // add:6:0x02800001g
	{   4, 0x00811001, 0xfdffffff }, // add:6:0x02811001g
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003g
	{   8, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001g
	{  10, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001g
	{  11, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000004g
	{  13, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000g
	{  15, 0x015c0000, 0xfdffffff }, // cmp:7:0x035C0000g
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFEFg
	{  17, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  19, 0xe00120ff, 0xfdffffff }, // and:6:0xE20120FFg
	{  21, 0xe1510002, 0xfdffffff }, // cmp:7:0xE1510002g
	{  23, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{  24, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001g
	{  25, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9g
	{  26, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  28, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  29, 0xe00130ff, 0xfdffffff }, // and:6:0xE20130FFg
	{  31, 0xe1510003, 0xfdffffff }, // cmp:7:0xE1510003g
	{ -1, -1, -1 },g
	/* 21/32 */g
};g
g
static FuncSig func_sig_strchr_1[] = {g
	{   0, 0xe00120ff, 0xfdffffff }, // and:6:0xE20120FFg
	{   2, 0xe1510002, 0xfdffffff }, // cmp:7:0xE1510002g
	{   4, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{   5, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001g
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9g
	{   7, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{   9, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  10, 0xe00130ff, 0xfdffffff }, // and:6:0xE20130FFg
	{  12, 0xe1510003, 0xfdffffff }, // cmp:7:0xE1510003g
	{  13, 0x01a02000, 0xfdffffff }, // mov:6:0x01A02000g
	{  14, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{  15, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001g
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9g
	{  17, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002g
	{  19, 0xe1520010, 0xfdffffff }, // cmp:7:0xE3520010g
	{  20, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000g
	{  21, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000032g
	{  22, 0xe1130003, 0xfdffffff }, // tst:7:0xE3130003g
	{  24, 0x10422001, 0xfdffffff }, // sub:6:0x12422001g
	{  26, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFAg
	{  27, 0xe011c003, 0xfdffffff }, // and:6:0xE211C003g
	{  28, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000Dg
	{  29, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE35C0001g
	{  30, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000029g
	{  31, 0xe15c0002, 0xfdffffff }, // cmp:7:0xE35C0002g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_strcat_1[] = {g
	{   0, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000g
	{   2, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{   3, 0x10800001, 0xfdffffff }, // add:6:0x12800001g
	{   4, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFBg
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000001g
	{   6, 0xe0811001, 0xfdffffff }, // add:6:0xE2811001g
	{   9, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFAg
	{  11, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  13, 0xe1a00003, 0xfdffffff }, // mov:6:0xE1A00003g
	{  15, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000008g
	{  17, 0xe153000c, 0xfdffffff }, // cmp:7:0xE153000Cg
	{  18, 0x00800001, 0xfdffffff }, // add:6:0x02800001g
	{  19, 0x00811001, 0xfdffffff }, // add:6:0x02811001g
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003g
	{  23, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001g
	{  25, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001g
	{  26, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000004g
	{  28, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000g
	{  30, 0x015c0000, 0xfdffffff }, // cmp:7:0x035C0000g
	{  31, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFEFg
	{ -1, -1, -1 },g
	/* 21/32 */g
};g
g
static FuncSig func_sig_strtol_1[] = {g
	{   0, 0xe1a03001, 0xfdffffff }, // mov:6:0xE3A03001g
	{   1, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFF7Eg
	{   2, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000g
	{   3, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFF7Cg
	{   5, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000g
	{   6, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000Fg
	{   7, 0xe151000a, 0xfdffffff }, // cmp:7:0xE351000Ag
	{   8, 0xe042c030, 0xfdffffff }, // sub:6:0xE242C030g
	{   9, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000002g
	{  10, 0xe15c000a, 0xfdffffff }, // cmp:7:0xE35C000Ag
	{  11, 0x2a000000, 0xff000000 }, // b, bl:3:0x2A00000Fg
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000007g
	{  13, 0xe15c000a, 0xfdffffff }, // cmp:7:0xE35C000Ag
	{  14, 0x2042c061, 0xfdffffff }, // sub:6:0x2242C061g
	{  15, 0x215c0006, 0xfdffffff }, // cmp:7:0x235C0006g
	{  16, 0x2a000000, 0xff000000 }, // b, bl:3:0x2A00000Ag
	{  17, 0xe042c061, 0xfdffffff }, // sub:6:0xE242C061g
	{  18, 0xe15c0005, 0xfdffffff }, // cmp:7:0xE35C0005g
	{  19, 0x90422057, 0xfdffffff }, // sub:6:0x92422057g
	{  20, 0x9a000000, 0xff000000 }, // b, bl:3:0x9A000000g
	{  21, 0xe0422030, 0xfdffffff }, // sub:6:0xE2422030g
	{  24, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{  25, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFECg
	{  26, 0xe1a00003, 0xfdffffff }, // mov:6:0xE1A00003g
	{  28, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002C2Fg
	{ -1, -1, -1 },g
	/* 26/32 */g
};g
g
static FuncSig func_sig_time_1[] = {g
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   3, 0xe58d0000, 0xfdffffff }, // str:4:0xE58D0000g
	{   4, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB02F26Eg
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000002g
	{   8, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000g
	{   9, 0x159d0000, 0xfdffffff }, // ldr:4:0x159D0000g
	{  10, 0x15840000, 0xfdffffff }, // str:4:0x15840000g
	{  11, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{  14, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  15, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  16, 0xe5840024, 0xfdffffff }, // str:4:0xE5840024g
	{  17, 0xe5940014, 0xfdffffff }, // ldr:4:0xE5940014g
	{  18, 0xe0401046, 0xfdffffff }, // sub:6:0xE2401046g
	{  19, 0xe1510044, 0xfdffffff }, // cmp:7:0xE3510044g
	{  20, 0x2a000000, 0xff000000 }, // b, bl:3:0x2A000025g
	{  21, 0xe59f129c, 0xfdffffff }, // ldr:4:0xE59F129Cg
	{  22, 0xe0811100, 0xfdffffff }, // add:6:0xE0811100g
	{  23, 0xe5113118, 0xfdffffff }, // ldr:4:0xE5113118g
	{  24, 0xe59f1294, 0xfdffffff }, // ldr:4:0xE59F1294g
	{  25, 0xe0811100, 0xfdffffff }, // add:6:0xE0811100g
	{  26, 0xe5112118, 0xfdffffff }, // ldr:4:0xE5112118g
	{  27, 0xe5941010, 0xfdffffff }, // ldr:4:0xE5941010g
	{  28, 0xe151000c, 0xfdffffff }, // cmp:7:0xE351000Cg
	{  29, 0x2a000000, 0xff000000 }, // b, bl:3:0x2A00001Cg
	{  30, 0xe59fc280, 0xfdffffff }, // ldr:4:0xE59FC280g
	{  31, 0xe0833083, 0xfdffffff }, // add:6:0xE0833083g
	{ -1, -1, -1 },g
	/* 28/32 */g
};g
g
static FuncSig func_sig_LocalTime_1[] = {g
	{   1, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   2, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001g
	{   3, 0xe59f11b0, 0xfdffffff }, // ldr:4:0xE59F11B0g
	{   4, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   5, 0xe1500001, 0xfdffffff }, // cmp:7:0xE1500001g
	{   6, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000003g
	{   7, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004g
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB006F3Cg
	{  10, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000049g
	{  11, 0xe59f217c, 0xfdffffff }, // ldr:4:0xE59F217Cg
	{  12, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  13, 0xe5923101, 0xfdffffff }, // ldr:4:0xE7923101g
	{  14, 0xe1530000, 0xfdffffff }, // cmp:7:0xE1530000g
	{  15, 0xd0811001, 0xfdffffff }, // add:6:0xD2811001g
	{  16, 0xd1510044, 0xfdffffff }, // cmp:7:0xD3510044g
	{  17, 0xba000000, 0xff000000 }, // b, bl:3:0xBAFFFFFAg
	{  18, 0xe0511001, 0xfdffffff }, // sub:6:0xE2511001g
	{  19, 0x4a000000, 0xff000000 }, // b, bl:3:0x4AFFFFF2g
	{  20, 0xe0816046, 0xfdffffff }, // add:6:0xE2816046g
	{  21, 0xe5846014, 0xfdffffff }, // str:4:0xE5846014g
	{  22, 0xe5921101, 0xfdffffff }, // ldr:4:0xE7921101g
	{  23, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  24, 0xe0401001, 0xfdffffff }, // sub:6:0xE0401001g
	{  25, 0xe59f0140, 0xfdffffff }, // ldr:4:0xE59F0140g
	{  26, 0xe0800106, 0xfdffffff }, // add:6:0xE0800106g
	{  27, 0xe5100118, 0xfdffffff }, // ldr:4:0xE5100118g
	{  28, 0xe0808080, 0xfdffffff }, // add:6:0xE0808080g
	{  29, 0xe59f0138, 0xfdffffff }, // ldr:4:0xE59F0138g
	{  30, 0xe0800208, 0xfdffffff }, // add:6:0xE0800208g
	{  31, 0xe5903102, 0xfdffffff }, // ldr:4:0xE7903102g
	{ -1, -1, -1 },g
	/* 31/32 */g
};g
g
static FuncSig func_sig_UpdateMBROnFlash_1[] = {g
	{   1, 0xe1a07001, 0xfdffffff }, // mov:6:0xE1A07001g
	{   2, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002g
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   4, 0xe1a00003, 0xfdffffff }, // mov:6:0xE3A00003g
	{   5, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{   6, 0xe1a01c02, 0xfdffffff }, // mov:6:0xE3A01C02g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB005DB9g
	{   8, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   9, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{  10, 0xe0010490, 0xfdffffff }, // and:6:0xE0010490 mul:11:0xE0010490g
	{  11, 0xe51f0550, 0xfdffffff }, // ldr:4:0xE51F0550g
	{  12, 0xe1a03005, 0xfdffffff }, // mov:6:0xE1A03005g
	{  13, 0xe0804101, 0xfdffffff }, // add:6:0xE0804101g
	{  14, 0xe594c04c, 0xfdffffff }, // ldr:4:0xE594C04Cg
	{  15, 0xe5940038, 0xfdffffff }, // ldr:4:0xE5940038g
	{  16, 0xe5941044, 0xfdffffff }, // ldr:4:0xE5941044g
	{  17, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001g
	{  19, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006g
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFF3D7Ag
	{  21, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000g
	{  22, 0xe0850007, 0xfdffffff }, // add:6:0xE0850007g
	{  23, 0xe1a01006, 0xfdffffff }, // mov:6:0xE1A01006g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFF3D56g
	{  25, 0xe5b40038, 0xfdffffff }, // ldr:4:0xE5B40038g
	{  26, 0xe5b4100c, 0xfdffffff }, // ldr:4:0xE5B4100Cg
	{  27, 0xe594c00c, 0xfdffffff }, // ldr:4:0xE594C00Cg
	{  28, 0xe1a03005, 0xfdffffff }, // mov:6:0xE1A03005g
	{  29, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_opendir_1[] = {g
	{   1, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   2, 0xe1a00014, 0xfdffffff }, // mov:6:0xE3A00014g
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF95F20g
	{   4, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{   5, 0x01a01059, 0xfdffffff }, // mov:6:0x03A01059g
	{   6, 0x008f0e26, 0xfdffffff }, // add:6:0x028F0E26g
	{   7, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BF9295Cg
	{   9, 0xe5840000, 0xfdffffff }, // str:4:0xE5840000g
	{  10, 0xe1a00902, 0xfdffffff }, // mov:6:0xE3A00902g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF95F44g
	{  12, 0xe1a01902, 0xfdffffff }, // mov:6:0xE3A01902g
	{  14, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  15, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  16, 0xe584100c, 0xfdffffff }, // str:4:0xE584100Cg
	{  17, 0xe5841010, 0xfdffffff }, // str:4:0xE5841010g
	{  18, 0x01a01060, 0xfdffffff }, // mov:6:0x03A01060g
	{  19, 0x008f0f8b, 0xfdffffff }, // add:6:0x028F0F8Bg
	{  20, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BF9294Fg
	{  21, 0xe1a02f49, 0xfdffffff }, // mov:6:0xE3A02F49g
	{  22, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  23, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF94D26g
	{  26, 0xe5840000, 0xfdffffff }, // str:4:0xE5840000g
	{  27, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004g
	{  28, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFB0g
	{  30, 0xe1500002, 0xfdffffff }, // cmp:7:0xE3500002g
	{  31, 0x11a00004, 0xfdffffff }, // mov:6:0x11A00004g
	{ -1, -1, -1 },g
	/* 28/32 */g
};g
g
static FuncSig func_sig_ReadFastDir_1[] = {g
	{   1, 0xe1b05000, 0xfdffffff }, // mov:6:0xE1B05000g
	{   2, 0xe1a07001, 0xfdffffff }, // mov:6:0xE1A07001g
	{   3, 0xe1a06000, 0xfdffffff }, // mov:6:0xE3A06000g
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000027g
	{   5, 0xe5952010, 0xfdffffff }, // ldr:4:0xE5952010g
	{   6, 0xe595400c, 0xfdffffff }, // ldr:4:0xE595400Cg
	{   7, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000014g
	{   8, 0xe5950004, 0xfdffffff }, // ldr:4:0xE5950004g
	{   9, 0xe0800004, 0xfdffffff }, // add:6:0xE0800004g
	{  11, 0xe151000f, 0xfdffffff }, // cmp:7:0xE351000Fg
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000Ag
	{  13, 0xe1110008, 0xfdffffff }, // tst:7:0xE3110008g
	{  14, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008g
	{  16, 0xe15100e5, 0xfdffffff }, // cmp:7:0xE35100E5g
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009g
	{  18, 0xe1a01007, 0xfdffffff }, // mov:6:0xE1A01007g
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000029g
	{  20, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{  21, 0xe585000c, 0xfdffffff }, // str:4:0xE585000Cg
	{  22, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006g
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000008g
	{  25, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  26, 0x01a00001, 0xfdffffff }, // mov:6:0x03A00001g
	{  27, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004g
	{  28, 0xe0844020, 0xfdffffff }, // add:6:0xE2844020g
	{  29, 0xe1520004, 0xfdffffff }, // cmp:7:0xE1520004g
	{  30, 0xca000000, 0xff000000 }, // b, bl:3:0xCAFFFFE8g
	{  31, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002g
	{ -1, -1, -1 },g
	/* 28/32 */g
};g
g
static FuncSig func_sig_closedir_1[] = {g
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   2, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   4, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BF94CEBg
	{   5, 0xe5940004, 0xfdffffff }, // ldr:4:0xE5940004g
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF95EFDg
	{   7, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF95EC2g
	{  11, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{  12, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{  13, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  14, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  15, 0xe1a02008, 0xfdffffff }, // mov:6:0xE3A02008g
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000038g
	{  18, 0xe1510020, 0xfdffffff }, // cmp:7:0xE3510020g
	{  19, 0x11a0102e, 0xfdffffff }, // mov:6:0x13A0102Eg
	{  21, 0x10841008, 0xfdffffff }, // add:6:0x12841008g
	{  22, 0x11a02003, 0xfdffffff }, // mov:6:0x13A02003g
	{  23, 0x1b000000, 0xff000000 }, // b, bl:3:0x1B000031g
	{  24, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  27, 0xe1500005, 0xfdffffff }, // cmp:7:0xE3500005g
	{  28, 0x01a000e5, 0xfdffffff }, // mov:6:0x03A000E5g
	{ -1, -1, -1 },g
	/* 21/32 */g
};g
g
static FuncSig func_sig_NewTaskShell_1[] = {g
	{   1, 0xe51f4728, 0xfdffffff }, // ldr:4:0xE51F4728g
	{   2, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{   3, 0xe1500064, 0xfdffffff }, // cmp:7:0xE3500064g
	{   4, 0xa1a00005, 0xfdffffff }, // mov:6:0xA3A00005g
	{   5, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000010g
	{   6, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001g
	{   7, 0xe5840000, 0xfdffffff }, // str:4:0xE5840000g
	{   8, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000g
	{   9, 0xe58d3000, 0xfdffffff }, // str:4:0xE58D3000g
	{  10, 0xe04f30e4, 0xfdffffff }, // sub:6:0xE24F30E4g
	{  11, 0xe08f00dc, 0xfdffffff }, // add:6:0xE28F00DCg
	{  12, 0xe1a02902, 0xfdffffff }, // mov:6:0xE3A02902g
	{  13, 0xe1a01018, 0xfdffffff }, // mov:6:0xE3A01018g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFEC934g
	{  15, 0xe1100001, 0xfdffffff }, // tst:7:0xE3100001g
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005g
	{  17, 0xe59f10d8, 0xfdffffff }, // ldr:4:0xE59F10D8g
	{  18, 0xe5940004, 0xfdffffff }, // ldr:4:0xE5940004g
	{  19, 0xe1a030af, 0xfdffffff }, // mov:6:0xE3A030AFg
	{  20, 0xe08f20c0, 0xfdffffff }, // add:6:0xE28F20C0g
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFECA1Dg
	{  22, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  25, 0xe59f10bc, 0xfdffffff }, // ldr:4:0xE59F10BCg
	{  26, 0xe08f00bc, 0xfdffffff }, // add:6:0xE28F00BCg
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFECAABg
	{  28, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{  29, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFEC9F9g
	{  31, 0xe51f17a0, 0xfdffffff }, // ldr:4:0xE51F17A0g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_UIFS_WriteFirmInfoToFile_1[] = {g
	{   1, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   2, 0xe04dd0a0, 0xfdffffff }, // sub:6:0xE24DD0A0g
	{   3, 0x11a04000, 0xfdffffff }, // mov:6:0x11A04000g
	{   4, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000g
	{   5, 0xe08d0050, 0xfdffffff }, // add:6:0xE28D0050g
	{   6, 0x008f4ff2, 0xfdffffff }, // add:6:0x028F4FF2g
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFB0FDCg
	{   9, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000g
	{  10, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  11, 0xe08d2050, 0xfdffffff }, // add:6:0xE28D2050g
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFB26B3g
	{  14, 0xe08f1fee, 0xfdffffff }, // add:6:0xE28F1FEEg
	{  15, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFB2815g
	{  17, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000g
	{  18, 0xe59f03ac, 0xfdffffff }, // ldr:4:0xE59F03ACg
	{  19, 0xe1a02020, 0xfdffffff }, // mov:6:0xE3A02020g
	{  20, 0xe08d1050, 0xfdffffff }, // add:6:0xE28D1050g
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFC4855g
	{  22, 0xe08d2050, 0xfdffffff }, // add:6:0xE28D2050g
	{  23, 0xe08f1fe7, 0xfdffffff }, // add:6:0xE28F1FE7g
	{  24, 0xe08d0050, 0xfdffffff }, // add:6:0xE28D0050g
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFB0F74g
	{  26, 0xe08d0050, 0xfdffffff }, // add:6:0xE28D0050g
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFB0FC9g
	{  28, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{  29, 0xe08d0050, 0xfdffffff }, // add:6:0xE28D0050g
	{  30, 0xe1a03008, 0xfdffffff }, // mov:6:0xE1A03008g
	{  31, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_SetAutoShutdownTime_1[] = {g
	{   1, 0xe59f4098, 0xfdffffff }, // ldr:4:0xE59F4098g
	{   2, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   3, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{   4, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{   5, 0x11a010a9, 0xfdffffff }, // mov:6:0x13A010A9g
	{   6, 0x108f008c, 0xfdffffff }, // add:6:0x128F008Cg
	{   7, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFEC025g
	{   8, 0xe59f1090, 0xfdffffff }, // ldr:4:0xE59F1090g
	{   9, 0xe5940024, 0xfdffffff }, // ldr:4:0xE5940024g
	{  10, 0xe1a030aa, 0xfdffffff }, // mov:6:0xE3A030AAg
	{  11, 0xe08f2078, 0xfdffffff }, // add:6:0xE28F2078g
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFEC011g
	{  13, 0xe1a00ffa, 0xfdffffff }, // mov:6:0xE3A00FFAg
	{  14, 0xe0000095, 0xfdffffff }, // and:6:0xE0000095 mul:11:0xE0000095g
	{  15, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000g
	{  16, 0xe584001c, 0xfdffffff }, // str:4:0xE584001Cg
	{  17, 0xe5940004, 0xfdffffff }, // ldr:4:0xE5940004g
	{  18, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  19, 0x05845004, 0xfdffffff }, // str:4:0x05845004g
	{  20, 0x0b000000, 0xff000000 }, // b, bl:3:0x0B000043g
	{  21, 0xe594001c, 0xfdffffff }, // ldr:4:0xE594001Cg
	{  22, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  23, 0x0584500c, 0xfdffffff }, // str:4:0x0584500Cg
	{  24, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000Cg
	{  25, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{  26, 0xe584100c, 0xfdffffff }, // str:4:0xE584100Cg
	{  27, 0xe5942008, 0xfdffffff }, // ldr:4:0xE5942008g
	{  28, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{  29, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000007g
	{  30, 0xe5841004, 0xfdffffff }, // str:4:0xE5841004g
	{  31, 0xe04f2e2a, 0xfdffffff }, // sub:6:0xE24F2E2Ag
	{ -1, -1, -1 },g
	/* 32/32 */g
};g
g
static FuncSig func_sig_Fgets_Fut_1[] = {g
	{   1, 0xe1b04002, 0xfdffffff }, // mov:6:0xE1B04002g
	{   2, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000g
	{   3, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{   4, 0xe1a07001, 0xfdffffff }, // mov:6:0xE1A07001g
	{   6, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   7, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00004Ag
	{   9, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  10, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006g
	{  11, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004g
	{  12, 0xe1a01007, 0xfdffffff }, // mov:6:0xE1A01007g
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B206g
	{  14, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  15, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00004Cg
	{  17, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{ -1, -1, -1 },g
	/* 16/19 */g
};g
g
static FuncSig func_sig_Feof_Fut_1[] = {g
	{   1, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{   4, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   5, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000026g
	{   7, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   8, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B234g
	{  10, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  11, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00002Ag
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{ -1, -1, -1 },g
	/* 11/14 */g
};g
g
static FuncSig func_sig_Fflush_Fut_1[] = {g
	{   1, 0xe1b04000, 0xfdffffff }, // mov:6:0xE1B04000g
	{   4, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   5, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000017g
	{   7, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   8, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B22Bg
	{  10, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000g
	{  11, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020g
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD26g
	{  13, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000019g
	{  15, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006g
	{ -1, -1, -1 },g
	/* 13/17 */g
};g
g
static FuncSig func_sig_strftime_1[] = {g
	{   1, 0xe59f940c, 0xfdffffff }, // ldr:4:0xE59F940Cg
	{   2, 0xe1a0b025, 0xfdffffff }, // mov:6:0xE3A0B025g
	{   3, 0xe1a08002, 0xfdffffff }, // mov:6:0xE1A08002g
	{   4, 0xe0417001, 0xfdffffff }, // sub:6:0xE2417001g
	{   5, 0xe1a06003, 0xfdffffff }, // mov:6:0xE1A06003g
	{   6, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000g
	{   7, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   8, 0xe089a01c, 0xfdffffff }, // add:6:0xE289A01Cg
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00012Fg
	{  10, 0xe1500025, 0xfdffffff }, // cmp:7:0xE3500025g
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004g
	{  12, 0xe0855001, 0xfdffffff }, // add:6:0xE2855001g
	{  13, 0xe1550007, 0xfdffffff }, // cmp:7:0xE1550007g
	{  14, 0x8a000000, 0xff000000 }, // b, bl:3:0x8A000125g
	{  16, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00011Eg
	{  18, 0xe1500059, 0xfdffffff }, // cmp:7:0xE3500059g
	{  19, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00010Cg
	{  20, 0xca000000, 0xff000000 }, // b, bl:3:0xCA00003Ag
	{  21, 0xe150004d, 0xfdffffff }, // cmp:7:0xE350004Dg
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A0000BEg
	{  23, 0xca000000, 0xff000000 }, // b, bl:3:0xCA000023g
	{  24, 0xe1500042, 0xfdffffff }, // cmp:7:0xE3500042g
	{  25, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00007Ag
	{  26, 0xca000000, 0xff000000 }, // b, bl:3:0xCA000010g
	{  27, 0xe1500025, 0xfdffffff }, // cmp:7:0xE3500025g
	{  28, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00010Eg
	{  29, 0xe1500041, 0xfdffffff }, // cmp:7:0xE3500041g
	{  30, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000112g
	{  31, 0xe59f1398, 0xfdffffff }, // ldr:4:0xE59F1398g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_mktime_ext_1[] = {g
	{   1, 0xe5905024, 0xfdffffff }, // ldr:4:0xE5905024g
	{   2, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   3, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{   4, 0xe5840024, 0xfdffffff }, // str:4:0xE5840024g
	{   5, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFE4684g
	{   7, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFE3BDFg
	{  11, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{  12, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFC5g
	{  14, 0xe5845024, 0xfdffffff }, // str:4:0xE5845024g
	{ -1, -1, -1 },g
	/* 12/16 */g
};g
g
static FuncSig func_sig_DeleteFile_Fut_1[] = {g
	{   0, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   1, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000192g
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{   3, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000190g
	{   5, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   6, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000FFg
	{   8, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   9, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  10, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEC4g
	{  12, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000102g
	{  15, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  18, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  19, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000F2g
	{  21, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  22, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B394g
	{  24, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  25, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000F6g
	{  27, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  30, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{  31, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_RenameFile_Fut_1[] = {g
	{   1, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001g
	{   2, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   3, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000117g
	{   5, 0xe59f1604, 0xfdffffff }, // ldr:4:0xE59F1604g
	{   6, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   7, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{   8, 0xe5810104, 0xfdffffff }, // str:4:0xE7810104g
	{   9, 0xe1a01006, 0xfdffffff }, // mov:6:0xE1A01006g
	{  10, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000137g
	{  12, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000117g
	{  15, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{ -1, -1, -1 },g
	/* 15/17 */g
};g
g
static FuncSig func_sig_MakeDirectory_Fut_1[] = {g
	{   1, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{   2, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   3, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000g
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000E5g
	{   5, 0xe59f253c, 0xfdffffff }, // ldr:4:0xE59F253Cg
	{   6, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   7, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   8, 0xe5821100, 0xfdffffff }, // str:4:0xE7821100g
	{  10, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{  11, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000g
	{  12, 0x0b000000, 0xff000000 }, // b, bl:3:0x0B010573g
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00B300g
	{  14, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006g
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000FBg
	{  16, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006g
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0002C6g
	{  18, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  19, 0x059f5534, 0xfdffffff }, // ldr:4:0x059F5534g
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002g
	{  21, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006g
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFDE8g
	{  23, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000g
	{  24, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000DAg
	{  26, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{ -1, -1, -1 },g
	/* 25/28 */g
};g
g
static FuncSig func_sig_SetFileTimeStamp_1[] = {g
	{   1, 0xe58d1004, 0xfdffffff }, // str:4:0xE58D1004g
	{   2, 0xe58d2000, 0xfdffffff }, // str:4:0xE58D2000g
	{   3, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{   4, 0xe1a01002, 0xfdffffff }, // mov:6:0xE3A01002g
	{   5, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD4ACg
	{   7, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008g
	{   9, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00A9F8g
	{  11, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  12, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004g
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD4A4g
	{  15, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  16, 0x01a00001, 0xfdffffff }, // mov:6:0x03A00001g
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000g
	{  18, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{ -1, -1, -1 },g
	/* 18/20 */g
};g
g
static FuncSig func_sig_AllocateMemory_2[] = {g
	{   0, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   1, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF80561g
	{   2, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{   8, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  15, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  16, 0xe58d0000, 0xfdffffff }, // str:4:0xE58D0000g
	{  17, 0xe040087f, 0xfdffffff }, // sub:6:0xE240087Fg
	{  18, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100Dg
	{  19, 0xe1a02004, 0xfdffffff }, // mov:6:0xE3A02004g
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFC5F73g
	{  23, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF8061Fg
	{  25, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{  28, 0xe5905000, 0xfdffffff }, // ldr:4:0xE5905000g
	{  29, 0xe04dd01c, 0xfdffffff }, // sub:6:0xE24DD01Cg
	{  30, 0xe0804004, 0xfdffffff }, // add:6:0xE2804004g
	{  31, 0xe08d0008, 0xfdffffff }, // add:6:0xE28D0008g
	{ -1, -1, -1 },g
	/* 17/32 */g
};g
g
static FuncSig func_sig_ExecuteEventProcedure_2[] = {g
	{   2, 0xe59f0104, 0xfdffffff }, // ldr:4:0xE59F0104g
	{   3, 0xe59d1010, 0xfdffffff }, // ldr:4:0xE59D1010g
	{   4, 0xe0404014, 0xfdffffff }, // sub:6:0xE2404014g
	{   5, 0xe58d0000, 0xfdffffff }, // str:4:0xE58D0000g
	{   6, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{   7, 0xe08d5014, 0xfdffffff }, // add:6:0xE28D5014g
	{   8, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200Dg
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFECFg
	{  10, 0xe1500019, 0xfdffffff }, // cmp:7:0xE3500019g
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000Ag
	{  12, 0xe59f00ac, 0xfdffffff }, // ldr:4:0xE59F00ACg
	{  13, 0xe59d3010, 0xfdffffff }, // ldr:4:0xE59D3010g
	{  14, 0xe08f20d8, 0xfdffffff }, // add:6:0xE28F20D8g
	{  15, 0xe08f10c8, 0xfdffffff }, // add:6:0xE28F10C8g
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFED162g
	{  17, 0xe5941004, 0xfdffffff }, // ldr:4:0xE5941004g
	{  18, 0xe59f0094, 0xfdffffff }, // ldr:4:0xE59F0094g
	{  20, 0xe1a010dd, 0xfdffffff }, // mov:6:0xE3A010DDg
	{  21, 0xe08f00d0, 0xfdffffff }, // add:6:0xE28F00D0g
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFECAD8g
	{  23, 0xe5942000, 0xfdffffff }, // ldr:4:0xE5942000g
	{  24, 0xe59d1010, 0xfdffffff }, // ldr:4:0xE59D1010g
	{  25, 0xe5940010, 0xfdffffff }, // ldr:4:0xE5940010g
	{  27, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{  29, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_EnterToCompensationEVF_2[] = {g
	{   1, 0xe08f1f77, 0xfdffffff }, // add:6:0xE28F1F77g
	{   2, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020g
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB01107Dg
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00060Bg
	{   5, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000611g
	{   8, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  10, 0xe1a02002, 0xfdffffff }, // mov:6:0xE3A02002g
	{  11, 0xe59f11d4, 0xfdffffff }, // ldr:4:0xE59F11D4g
	{  12, 0xe1a000cf, 0xfdffffff }, // mov:6:0xE3A000CFg
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB011B7Fg
	{  14, 0xe1100001, 0xfdffffff }, // tst:7:0xE3100001g
	{  15, 0x159f11c8, 0xfdffffff }, // ldr:4:0x159F11C8g
	{  16, 0x151f0f5c, 0xfdffffff }, // ldr:4:0x151F0F5Cg
	{  17, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFFD789g
	{  19, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00DEFBg
	{  21, 0xe08f1f6d, 0xfdffffff }, // add:6:0xE28F1F6Dg
	{  22, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020g
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB011069g
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0005F7g
	{  25, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0005FDg
	{  28, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  30, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00DEFAg
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig_ExitFromCompensationEVF_2[] = {g
	{   1, 0xe08f1f6d, 0xfdffffff }, // add:6:0xE28F1F6Dg
	{   2, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020g
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB011069g
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0005F7g
	{   5, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0005FDg
	{   8, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  10, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00DEFAg
	{  13, 0xe08f1f69, 0xfdffffff }, // add:6:0xE28F1F69g
	{  14, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020g
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB01105Dg
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0005EBg
	{  17, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0005F1g
	{  20, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  22, 0xe1a02002, 0xfdffffff }, // mov:6:0xE3A02002g
	{  23, 0xe59f1154, 0xfdffffff }, // ldr:4:0xE59F1154g
	{  24, 0xe1a000cf, 0xfdffffff }, // mov:6:0xE3A000CFg
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB011B5Fg
	{  26, 0xe1100001, 0xfdffffff }, // tst:7:0xE3100001g
	{  27, 0x159f1190, 0xfdffffff }, // ldr:4:0x159F1190g
	{  28, 0x151f0fdc, 0xfdffffff }, // ldr:4:0x151F0FDCg
	{  29, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFFD769g
	{  31, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00DEDBg
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig_FreeMemory_2[] = {g
	{   0, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   1, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF80564g
	{   2, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   3, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF80561g
	{   4, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{  10, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  17, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  18, 0xe58d0000, 0xfdffffff }, // str:4:0xE58D0000g
	{  19, 0xe040087f, 0xfdffffff }, // sub:6:0xE240087Fg
	{  20, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100Dg
	{  21, 0xe1a02004, 0xfdffffff }, // mov:6:0xE3A02004g
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFC5F73g
	{  25, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF8061Fg
	{  27, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{  30, 0xe5905000, 0xfdffffff }, // ldr:4:0xE5905000g
	{  31, 0xe04dd01c, 0xfdffffff }, // sub:6:0xE24DD01Cg
	{ -1, -1, -1 },g
	/* 17/32 */g
};g
g
static FuncSig func_sig_GetBatteryTemperature_2[] = {g
	{   1, 0xe59f40d8, 0xfdffffff }, // ldr:4:0xE59F40D8g
	{   2, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{   3, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   4, 0x059f10f0, 0xfdffffff }, // ldr:4:0x059F10F0g
	{   5, 0x008f00d8, 0xfdffffff }, // add:6:0x028F00D8g
	{   6, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFF5AE1g
	{   7, 0xe594000c, 0xfdffffff }, // ldr:4:0xE594000Cg
	{   9, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000Fg
	{  12, 0xe1510001, 0xfdffffff }, // cmp:7:0xE3510001g
	{  14, 0x0a000000, 0xff000000 }, // b, bl:3:0x0AFFFFD4g
	{  15, 0xe5900010, 0xfdffffff }, // ldr:4:0xE5900010g
	{  16, 0xe1500002, 0xfdffffff }, // cmp:7:0xE3500002g
	{  17, 0x059f10c0, 0xfdffffff }, // ldr:4:0x059F10C0g
	{  18, 0x008f00a4, 0xfdffffff }, // add:6:0x028F00A4g
	{  19, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFF5AD4g
	{  20, 0xe594100c, 0xfdffffff }, // ldr:4:0xE594100Cg
	{  22, 0xe5911010, 0xfdffffff }, // ldr:4:0xE5911010g
	{  23, 0xe59f20a0, 0xfdffffff }, // ldr:4:0xE59F20A0g
	{  24, 0xe0811181, 0xfdffffff }, // add:6:0xE0811181g
	{  26, 0xe0821201, 0xfdffffff }, // add:6:0xE0821201g
	{  27, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFADg
	{  29, 0xe59f4068, 0xfdffffff }, // ldr:4:0xE59F4068g
	{  30, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{  31, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_GetCCDTemperature_2[] = {g
	{   1, 0xe59f4148, 0xfdffffff }, // ldr:4:0xE59F4148g
	{   2, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{   3, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   4, 0x01a010fa, 0xfdffffff }, // mov:6:0x03A010FAg
	{   5, 0x008f0f52, 0xfdffffff }, // add:6:0x028F0F52g
	{   6, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFF5AFDg
	{   7, 0xe594000c, 0xfdffffff }, // ldr:4:0xE594000Cg
	{   9, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00002Bg
	{  12, 0xe1510001, 0xfdffffff }, // cmp:7:0xE3510001g
	{  14, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000Cg
	{  15, 0xe5900008, 0xfdffffff }, // ldr:4:0xE5900008g
	{  16, 0xe1500002, 0xfdffffff }, // cmp:7:0xE3500002g
	{  17, 0x01a010ff, 0xfdffffff }, // mov:6:0x03A010FFg
	{  18, 0x008f0f45, 0xfdffffff }, // add:6:0x028F0F45g
	{  19, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFF5AF0g
	{  20, 0xe594100c, 0xfdffffff }, // ldr:4:0xE594100Cg
	{  22, 0xe5911008, 0xfdffffff }, // ldr:4:0xE5911008g
	{  23, 0xe59f2110, 0xfdffffff }, // ldr:4:0xE59F2110g
	{  24, 0xe0811181, 0xfdffffff }, // add:6:0xE0811181g
	{  26, 0xe0821201, 0xfdffffff }, // add:6:0xE0821201g
	{  27, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFC9g
	{  29, 0xe59f40d8, 0xfdffffff }, // ldr:4:0xE59F40D8g
	{  30, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{  31, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_GetCurrentAvValue_2[] = {g
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB03B1EBg
	{   2, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   3, 0xe51f00ac, 0xfdffffff }, // ldr:4:0xE51F00ACg
	{   4, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   5, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   6, 0x01a010be, 0xfdffffff }, // mov:6:0x03A010BEg
	{   7, 0x004f00b8, 0xfdffffff }, // sub:6:0x024F00B8g
	{   8, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFBBE5Cg
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0003E1g
	{  10, 0xe0804004, 0xfdffffff }, // add:6:0xE0804004g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000B5Cg
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB03B1B1g
	{  13, 0xe0800004, 0xfdffffff }, // add:6:0xE0800004g
	{  14, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800g
	{  15, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840g
	{  18, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  19, 0xe51f00ec, 0xfdffffff }, // ldr:4:0xE51F00ECg
	{  20, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001g
	{  21, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  22, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002g
	{  23, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  24, 0x01a010cc, 0xfdffffff }, // mov:6:0x03A010CCg
	{  25, 0x004f0c01, 0xfdffffff }, // sub:6:0x024F0C01g
	{  26, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFBBE4Ag
	{  27, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006g
	{  28, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100Dg
	{  29, 0xe08d0004, 0xfdffffff }, // add:6:0xE28D0004g
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB03B1A8g
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000B48g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_GetDrive_ClusterSize_2[] = {g
	{   0, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{   2, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   3, 0xa59f02a0, 0xfdffffff }, // ldr:4:0xA59F02A0g
	{   4, 0xa1a01e57, 0xfdffffff }, // mov:6:0xA3A01E57g
	{   5, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF3332g
	{   6, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{   7, 0xe51f181c, 0xfdffffff }, // ldr:4:0xE51F181Cg
	{   8, 0xe0000094, 0xfdffffff }, // and:6:0xE0000094 mul:11:0xE0000094g
	{   9, 0xe0810100, 0xfdffffff }, // add:6:0xE0810100g
	{  10, 0xe5900054, 0xfdffffff }, // ldr:4:0xE5900054g
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00095Bg
	{  13, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  15, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  16, 0xa59f026c, 0xfdffffff }, // ldr:4:0xA59F026Cg
	{  17, 0xa59f1290, 0xfdffffff }, // ldr:4:0xA59F1290g
	{  18, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF3325g
	{  19, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{  20, 0xe51f1850, 0xfdffffff }, // ldr:4:0xE51F1850g
	{  21, 0xe0000094, 0xfdffffff }, // and:6:0xE0000094 mul:11:0xE0000094g
	{  22, 0xe0810100, 0xfdffffff }, // add:6:0xE0810100g
	{  23, 0xe5900054, 0xfdffffff }, // ldr:4:0xE5900054g
	{  25, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000952g
	{  26, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  28, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  29, 0xa59f0238, 0xfdffffff }, // ldr:4:0xA59F0238g
	{  30, 0xa59f1260, 0xfdffffff }, // ldr:4:0xA59F1260g
	{  31, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF3318g
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_GetDrive_FreeClusters_2[] = {g
	{   0, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{   2, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   3, 0xa59f0238, 0xfdffffff }, // ldr:4:0xA59F0238g
	{   4, 0xa59f1260, 0xfdffffff }, // ldr:4:0xA59F1260g
	{   5, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF3318g
	{   6, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{   7, 0xe51f1884, 0xfdffffff }, // ldr:4:0xE51F1884g
	{   8, 0xe0000094, 0xfdffffff }, // and:6:0xE0000094 mul:11:0xE0000094g
	{   9, 0xe0810100, 0xfdffffff }, // add:6:0xE0810100g
	{  10, 0xe5900054, 0xfdffffff }, // ldr:4:0xE5900054g
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00094Ag
	{  13, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  15, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  16, 0xa59f1234, 0xfdffffff }, // ldr:4:0xA59F1234g
	{  17, 0xa04f0d22, 0xfdffffff }, // sub:6:0xA24F0D22g
	{  18, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF330Bg
	{  19, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{  20, 0xe51f18b8, 0xfdffffff }, // ldr:4:0xE51F18B8g
	{  21, 0xe0000094, 0xfdffffff }, // and:6:0xE0000094 mul:11:0xE0000094g
	{  22, 0xe0810100, 0xfdffffff }, // add:6:0xE0810100g
	{  23, 0xe5900054, 0xfdffffff }, // ldr:4:0xE5900054g
	{  25, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000941g
	{  26, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  28, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  29, 0xa59f01d0, 0xfdffffff }, // ldr:4:0xA59F01D0g
	{  30, 0xa59f1200, 0xfdffffff }, // ldr:4:0xA59F1200g
	{  31, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF32FEg
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_GetDrive_TotalClusters_2[] = {g
	{   0, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{   2, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{   3, 0xa59f026c, 0xfdffffff }, // ldr:4:0xA59F026Cg
	{   4, 0xa59f1290, 0xfdffffff }, // ldr:4:0xA59F1290g
	{   5, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF3325g
	{   6, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{   7, 0xe51f1850, 0xfdffffff }, // ldr:4:0xE51F1850g
	{   8, 0xe0000094, 0xfdffffff }, // and:6:0xE0000094 mul:11:0xE0000094g
	{   9, 0xe0810100, 0xfdffffff }, // add:6:0xE0810100g
	{  10, 0xe5900054, 0xfdffffff }, // ldr:4:0xE5900054g
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000952g
	{  13, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  15, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  16, 0xa59f0238, 0xfdffffff }, // ldr:4:0xA59F0238g
	{  17, 0xa59f1260, 0xfdffffff }, // ldr:4:0xA59F1260g
	{  18, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF3318g
	{  19, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017g
	{  20, 0xe51f1884, 0xfdffffff }, // ldr:4:0xE51F1884g
	{  21, 0xe0000094, 0xfdffffff }, // and:6:0xE0000094 mul:11:0xE0000094g
	{  22, 0xe0810100, 0xfdffffff }, // add:6:0xE0810100g
	{  23, 0xe5900054, 0xfdffffff }, // ldr:4:0xE5900054g
	{  25, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00094Ag
	{  26, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001g
	{  28, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000g
	{  29, 0xa59f1234, 0xfdffffff }, // ldr:4:0xA59F1234g
	{  30, 0xa04f0d22, 0xfdffffff }, // sub:6:0xA24F0D22g
	{  31, 0xab000000, 0xff000000 }, // b, bl:3:0xABFF330Bg
	{ -1, -1, -1 },g
	/* 29/32 */g
};g
g
static FuncSig func_sig_GetOpticalTemperature_2[] = {g
	{   1, 0xe59f4068, 0xfdffffff }, // ldr:4:0xE59F4068g
	{   2, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{   3, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   4, 0x01a010de, 0xfdffffff }, // mov:6:0x03A010DEg
	{   5, 0x008f0068, 0xfdffffff }, // add:6:0x028F0068g
	{   6, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFF5AC5g
	{   7, 0xe594000c, 0xfdffffff }, // ldr:4:0xE594000Cg
	{   9, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000Cg
	{  11, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  12, 0xe1500002, 0xfdffffff }, // cmp:7:0xE3500002g
	{  13, 0x01a010e0, 0xfdffffff }, // mov:6:0x03A010E0g
	{  14, 0x008f0044, 0xfdffffff }, // add:6:0x028F0044g
	{  15, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFF5ABCg
	{  16, 0xe594100c, 0xfdffffff }, // ldr:4:0xE594100Cg
	{  18, 0xe5911000, 0xfdffffff }, // ldr:4:0xE5911000g
	{  19, 0xe59f2040, 0xfdffffff }, // ldr:4:0xE59F2040g
	{  20, 0xe0811181, 0xfdffffff }, // add:6:0xE0811181g
	{  22, 0xe0821201, 0xfdffffff }, // add:6:0xE0821201g
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFF95g
	{  24, 0xe1510001, 0xfdffffff }, // cmp:7:0xE3510001g
	{  26, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFC8g
	{  28, 0x0a000000, 0xff000000 }, // b, bl:3:0x0AFFFFAAg
	{  29, 0x000026d8, 0xfdffffff }, // and:6:0x000026D8g
	{  30, 0x70656854, 0xfdffffff }, // rsb:6:0x72656854g
	{ -1, -1, -1 },g
	/* 25/32 */g
};g
g
static FuncSig func_sig_GetSystemTime_2[] = {g
	{   1, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF8061Fg
	{   3, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000g
	{   6, 0xe5905000, 0xfdffffff }, // ldr:4:0xE5905000g
	{   7, 0xe04dd01c, 0xfdffffff }, // sub:6:0xE24DD01Cg
	{   8, 0xe0804004, 0xfdffffff }, // add:6:0xE2804004g
	{   9, 0xe08d0008, 0xfdffffff }, // add:6:0xE28D0008g
	{  10, 0xe1a01014, 0xfdffffff }, // mov:6:0xE3A01014g
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB01F745g
	{  12, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000g
	{  13, 0x108d3008, 0xfdffffff }, // add:6:0x128D3008g
	{  14, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004g
	{  16, 0xe08f00ac, 0xfdffffff }, // add:6:0xE28F00ACg
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF7A94Ag
	{  18, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001g
	{  19, 0xe08dd01c, 0xfdffffff }, // add:6:0xE28DD01Cg
	{  21, 0xe0844004, 0xfdffffff }, // add:6:0xE2844004g
	{  22, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{  23, 0xe5142004, 0xfdffffff }, // ldr:4:0xE5142004g
	{  24, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001g
	{  25, 0xe1500005, 0xfdffffff }, // cmp:7:0xE3500005g
	{  26, 0xe5832101, 0xfdffffff }, // str:4:0xE7832101g
	{  27, 0xba000000, 0xff000000 }, // b, bl:3:0xBAFFFFF8g
	{  28, 0xe59d3018, 0xfdffffff }, // ldr:4:0xE59D3018g
	{  29, 0xe58d3000, 0xfdffffff }, // str:4:0xE58D3000g
	{  30, 0xe08d3008, 0xfdffffff }, // add:6:0xE28D3008g
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_GetZoomLensCurrentPosition_2[] = {g
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB01E38Fg
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0AFFFAA0g
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A01E38Fg
	{   7, 0xea000000, 0xff000000 }, // b, bl:3:0xEA01E3A9g
	{   8, 0xe51f02d0, 0xfdffffff }, // ldr:4:0xE51F02D0g
	{  11, 0xe51f02dc, 0xfdffffff }, // ldr:4:0xE51F02DCg
	{  12, 0xe590102c, 0xfdffffff }, // ldr:4:0xE590102Cg
	{  13, 0xe5900028, 0xfdffffff }, // ldr:4:0xE5900028g
	{  14, 0xe0410000, 0xfdffffff }, // sub:6:0xE0410000g
	{  16, 0xe51f22f0, 0xfdffffff }, // ldr:4:0xE51F22F0g
	{  17, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{  18, 0xe5821008, 0xfdffffff }, // str:4:0xE5821008g
	{  19, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{  20, 0xe51f02ec, 0xfdffffff }, // ldr:4:0xE51F02ECg
	{  21, 0xe1a0200c, 0xfdffffff }, // mov:6:0xE3A0200Cg
	{  22, 0xea000000, 0xff000000 }, // b, bl:3:0xEA021E93g
	{  23, 0xe51f130c, 0xfdffffff }, // ldr:4:0xE51F130Cg
	{  24, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  25, 0xe5810008, 0xfdffffff }, // str:4:0xE5810008g
	{  27, 0xe51f031c, 0xfdffffff }, // ldr:4:0xE51F031Cg
	{  28, 0xe5900014, 0xfdffffff }, // ldr:4:0xE5900014g
	{  30, 0xe51f0328, 0xfdffffff }, // ldr:4:0xE51F0328g
	{  31, 0xe590001c, 0xfdffffff }, // ldr:4:0xE590001Cg
	{ -1, -1, -1 },g
	/* 24/32 */g
};g
g
static FuncSig func_sig_SetPropertyCase_2[] = {g
	{   1, 0xe51f4020, 0xfdffffff }, // ldr:4:0xE51F4020g
	{   2, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   3, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{   4, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001g
	{   5, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   6, 0x059f1908, 0xfdffffff }, // ldr:4:0x059F1908g
	{   7, 0x004f0034, 0xfdffffff }, // sub:6:0x024F0034g
	{   8, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002g
	{   9, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFEBC43g
	{  10, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{  11, 0xe59f38f8, 0xfdffffff }, // ldr:4:0xE59F38F8g
	{  12, 0xe59f18f8, 0xfdffffff }, // ldr:4:0xE59F18F8g
	{  13, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  14, 0xe04f2050, 0xfdffffff }, // sub:6:0xE24F2050g
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFEBBF7g
	{  16, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{  17, 0xe1a03007, 0xfdffffff }, // mov:6:0xE1A03007g
	{  18, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006g
	{  19, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005g
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF87g
	{  21, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  22, 0x159f18d4, 0xfdffffff }, // ldr:4:0x159F18D4g
	{  23, 0x104f0074, 0xfdffffff }, // sub:6:0x124F0074g
	{  24, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFEBC34g
	{  25, 0xe5940008, 0xfdffffff }, // ldr:4:0xE5940008g
	{  26, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  28, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFEBAD3g
	{  29, 0xe1a0c000, 0xfdffffff }, // mov:6:0xE1A0C000g
	{  30, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002g
	{  31, 0xe1510e12, 0xfdffffff }, // cmp:7:0xE3510E12g
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
static FuncSig func_sig_kbd_pwr_off_2[] = {g
	{   0, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{   1, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFEC5g
	{   2, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{   3, 0xe0000001, 0xfdffffff }, // and:6:0xE2000001g
	{   5, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{   7, 0xe59f107c, 0xfdffffff }, // ldr:4:0xE59F107Cg
	{   8, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020g
	{   9, 0xe581001c, 0xfdffffff }, // str:4:0xE581001Cg
	{  10, 0xe5810024, 0xfdffffff }, // str:4:0xE5810024g
	{  14, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{  15, 0xe59f0044, 0xfdffffff }, // ldr:4:0xE59F0044g
	{  16, 0xe1a04000, 0xfdffffff }, // mov:6:0xE3A04000g
	{  17, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  18, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  19, 0x11a010d4, 0xfdffffff }, // mov:6:0x13A010D4g
	{  20, 0x108f0038, 0xfdffffff }, // add:6:0x128F0038g
	{  21, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFF64B5g
	{  22, 0xe59f0040, 0xfdffffff }, // ldr:4:0xE59F0040g
	{  23, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000g
	{  24, 0x0590401c, 0xfdffffff }, // ldr:4:0x0590401Cg
	{  25, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000005g
	{  26, 0xe1550001, 0xfdffffff }, // cmp:7:0xE3550001g
	{  27, 0x05904024, 0xfdffffff }, // ldr:4:0x05904024g
	{  28, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002g
	{  29, 0xe1a010e5, 0xfdffffff }, // mov:6:0xE3A010E5g
	{  30, 0xe08f0010, 0xfdffffff }, // add:6:0xE28F0010g
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFF64ABg
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_kbd_pwr_on_2[] = {g
	{   1, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020g
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFED8g
	{   3, 0xe04f2020, 0xfdffffff }, // sub:6:0xE24F2020g
	{   4, 0xe0821000, 0xfdffffff }, // add:6:0xE2821000g
	{   5, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000g
	{   6, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE3A0000Ag
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0096D6g
	{   8, 0xe1100001, 0xfdffffff }, // tst:7:0xE3100001g
	{   9, 0x11500015, 0xfdffffff }, // cmp:7:0x13500015g
	{  10, 0x11a010f9, 0xfdffffff }, // mov:6:0x13A010F9g
	{  11, 0x108f00ac, 0xfdffffff }, // add:6:0x128F00ACg
	{  12, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFF64D2g
	{  13, 0xe59f009c, 0xfdffffff }, // ldr:4:0xE59F009Cg
	{  14, 0xe59f10ac, 0xfdffffff }, // ldr:4:0xE59F10ACg
	{  15, 0xe5900004, 0xfdffffff }, // ldr:4:0xE5900004g
	{  17, 0xe1a030fa, 0xfdffffff }, // mov:6:0xE3A030FAg
	{  18, 0xe08f2090, 0xfdffffff }, // add:6:0xE28F2090g
	{  19, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFF6485g
	{  20, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  21, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFEC5g
	{  22, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000g
	{  23, 0xe0000001, 0xfdffffff }, // and:6:0xE2000001g
	{  25, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000g
	{  27, 0xe59f107c, 0xfdffffff }, // ldr:4:0xE59F107Cg
	{  28, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020g
	{  29, 0xe581001c, 0xfdffffff }, // str:4:0xE581001Cg
	{  30, 0xe5810024, 0xfdffffff }, // str:4:0xE5810024g
	{ -1, -1, -1 },g
	/* 27/32 */g
};g
g
static FuncSig func_sig_strrchr_2[] = {g
	{   0, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{   1, 0xe00130ff, 0xfdffffff }, // and:6:0xE20130FFg
	{   3, 0xe1510003, 0xfdffffff }, // cmp:7:0xE1510003g
	{   4, 0x01a02000, 0xfdffffff }, // mov:6:0x01A02000g
	{   5, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000g
	{   6, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001g
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9g
	{   8, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002g
	{  10, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000g
	{  11, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004g
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000006g
	{  13, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001g
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000001g
	{  15, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000g
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000005g
	{  18, 0xe15c000e, 0xfdffffff }, // cmp:7:0xE15C000Eg
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFAg
	{  21, 0xe15e0000, 0xfdffffff }, // cmp:7:0xE35E0000g
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF5g
	{  23, 0xe0430000, 0xfdffffff }, // sub:6:0xE0430000g
	{  24, 0xe0400001, 0xfdffffff }, // sub:6:0xE2400001g
	{  25, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004g
	{  26, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  28, 0x05920000, 0xfdffffff }, // ldr:4:0x05920000g
	{  29, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  30, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003g
	{ -1, -1, -1 },g
	/* 26/32 */g
};g
g
static FuncSig func_sig_strcpy_2[] = {g
	{   0, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000g
	{   2, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000g
	{   4, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFBg
	{   6, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000008g
	{   8, 0xe1520003, 0xfdffffff }, // cmp:7:0xE1520003g
	{   9, 0x00800001, 0xfdffffff }, // add:6:0x02800001g
	{  10, 0x00811001, 0xfdffffff }, // add:6:0x02811001g
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003g
	{  14, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001g
	{  17, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{  19, 0x01530000, 0xfdffffff }, // cmp:7:0x03530000g
	{  20, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF1g
	{  21, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  23, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  25, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000g
	{  27, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000g
	{  28, 0x10811001, 0xfdffffff }, // add:6:0x12811001g
	{  29, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFBg
	{  30, 0xe0410000, 0xfdffffff }, // sub:6:0xE0410000g
	{ -1, -1, -1 },g
	/* 19/32 */g
};g
g
static FuncSig func_sig_strncpy_2[] = {g
	{   0, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000g
	{   1, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009g
	{   3, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000g
	{   5, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005g
	{   6, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{   7, 0xe0422001, 0xfdffffff }, // sub:6:0xE2422001g
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFBg
	{  12, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001g
	{  13, 0x2a000000, 0xff000000 }, // b, bl:3:0x2AFFFFF3g
	{  16, 0xe1b09001, 0xfdffffff }, // mov:6:0xE1B09001g
	{  17, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000g
	{  18, 0xe59f11f8, 0xfdffffff }, // ldr:4:0xE59F11F8g
	{  19, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004g
	{  20, 0xe1a0400b, 0xfdffffff }, // mov:6:0xE1A0400Bg
	{  21, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE3A0A001g
	{  22, 0xe1a08000, 0xfdffffff }, // mov:6:0xE3A08000g
	{  23, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002g
	{  24, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000g
	{  25, 0x1589b000, 0xfdffffff }, // str:4:0x1589B000g
	{  28, 0xe1100040, 0xfdffffff }, // tst:7:0xE3100040g
	{  29, 0x10844001, 0xfdffffff }, // add:6:0x12844001g
	{  30, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFAg
	{ -1, -1, -1 },g
	/* 22/32 */g
};g
g
static FuncSig func_sig_time_2[] = {g
	{   1, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000g
	{   2, 0xe51f40c8, 0xfdffffff }, // ldr:4:0xE51F40C8g
	{   4, 0xe58d0000, 0xfdffffff }, // str:4:0xE58D0000g
	{   5, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000007g
	{   8, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001g
	{   9, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000g
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFED224g
	{  11, 0xe1100001, 0xfdffffff }, // tst:7:0xE3100001g
	{  12, 0xe5840000, 0xfdffffff }, // str:4:0xE5840000g
	{  13, 0x159f12cc, 0xfdffffff }, // ldr:4:0x159F12CCg
	{  14, 0x104f00f0, 0xfdffffff }, // sub:6:0x124F00F0g
	{  15, 0x1b000000, 0xff000000 }, // b, bl:3:0x1BFED40Bg
	{  16, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000g
	{  17, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFED277g
	{  19, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFF05A2g
	{  21, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001g
	{  22, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000g
	{  23, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000Dg
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFBEg
	{  25, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000g
	{  26, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000009g
	{  27, 0xe594000c, 0xfdffffff }, // ldr:4:0xE594000Cg
	{  28, 0xe5941010, 0xfdffffff }, // ldr:4:0xE5941010g
	{  29, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000g
	{  30, 0xe0800001, 0xfdffffff }, // add:6:0xE0800001g
	{  31, 0xe59d1000, 0xfdffffff }, // ldr:4:0xE59D1000g
	{ -1, -1, -1 },g
	/* 30/32 */g
};g
g
FuncsList func_list[] = {
	{ "AllocateMemory", func_sig_AllocateMemory_1 },g
	{ "AllocateMemory", func_sig_AllocateMemory_2 },g
	{ "AllocateUncacheableMemory", func_sig_AllocateUncacheableMemory_1 },g
	{ "Close", func_sig_Close_1 },g
	{ "CreateTask", func_sig_CreateTask_1 },g
	{ "DeleteFile_Fut", func_sig_DeleteFile_Fut_1 },g
	{ "EnterToCompensationEVF", func_sig_EnterToCompensationEVF_2 },g
	{ "ExecuteEventProcedure", func_sig_ExecuteEventProcedure_1 },g
	{ "ExecuteEventProcedure", func_sig_ExecuteEventProcedure_2 },g
	{ "ExitFromCompensationEVF", func_sig_ExitFromCompensationEVF_2 },g
	{ "ExitTask", func_sig_ExitTask_1 },g
	{ "Fclose_Fut", func_sig_Fclose_Fut_1 },g
	{ "Feof_Fut", func_sig_Feof_Fut_1 },g
	{ "Fflush_Fut", func_sig_Fflush_Fut_1 },g
	{ "Fgets_Fut", func_sig_Fgets_Fut_1 },g
	{ "Fopen_Fut", func_sig_Fopen_Fut_1 },g
	{ "Fread_Fut", func_sig_Fread_Fut_1 },g
	{ "FreeMemory", func_sig_FreeMemory_1 },g
	{ "FreeMemory", func_sig_FreeMemory_2 },g
	{ "FreeUncacheableMemory", func_sig_FreeUncacheableMemory_1 },g
	{ "Fseek_Fut", func_sig_Fseek_Fut_1 },g
	{ "Fwrite_Fut", func_sig_Fwrite_Fut_1 },g
	{ "GetBatteryTemperature", func_sig_GetBatteryTemperature_2 },g
	{ "GetCCDTemperature", func_sig_GetCCDTemperature_2 },g
	{ "GetCurrentAvValue", func_sig_GetCurrentAvValue_1 },g
	{ "GetCurrentAvValue", func_sig_GetCurrentAvValue_2 },g
	{ "GetCurrentTargetDistance", func_sig_GetCurrentTargetDistance_1 },g
	{ "GetDrive_ClusterSize", func_sig_GetDrive_ClusterSize_1 },g
	{ "GetDrive_ClusterSize", func_sig_GetDrive_ClusterSize_2 },g
	{ "GetDrive_FreeClusters", func_sig_GetDrive_FreeClusters_1 },g
	{ "GetDrive_FreeClusters", func_sig_GetDrive_FreeClusters_2 },g
	{ "GetDrive_TotalClusters", func_sig_GetDrive_TotalClusters_1 },g
	{ "GetDrive_TotalClusters", func_sig_GetDrive_TotalClusters_2 },g
	{ "GetFocusLensSubjectDistance", func_sig_GetFocusLensSubjectDistance_1 },g
	{ "GetOpticalTemperature", func_sig_GetOpticalTemperature_2 },g
	{ "GetParameterData", func_sig_GetParameterData_1 },g
	{ "GetPropertyCase", func_sig_GetPropertyCase_1 },g
	{ "GetSystemTime", func_sig_GetSystemTime_1 },g
	{ "GetSystemTime", func_sig_GetSystemTime_2 },g
	{ "GetZoomLensCurrentPoint", func_sig_GetZoomLensCurrentPoint_1 },g
	{ "GetZoomLensCurrentPosition", func_sig_GetZoomLensCurrentPosition_1 },g
	{ "GetZoomLensCurrentPosition", func_sig_GetZoomLensCurrentPosition_2 },g
	{ "IsStrobeChargeCompleted", func_sig_IsStrobeChargeCompleted_1 },g
	{ "LocalTime", func_sig_LocalTime_1 },g
	{ "LockMainPower", func_sig_LockMainPower_1 },g
	{ "Lseek", func_sig_Lseek_1 },g
	{ "MakeDirectory_Fut", func_sig_MakeDirectory_Fut_1 },g
	{ "MoveFocusLensToDistance", func_sig_MoveFocusLensToDistance_1 },g
	{ "MoveZoomLensWithPoint", func_sig_MoveZoomLensWithPoint_1 },g
	{ "NewTaskShell", func_sig_NewTaskShell_1 },g
	{ "Open", func_sig_Open_1 },g
	{ "Read", func_sig_Read_1 },g
	{ "ReadFastDir", func_sig_ReadFastDir_1 },g
	{ "RefreshPhysicalScreen", func_sig_RefreshPhysicalScreen_1 },g
	{ "Remove", func_sig_Remove_1 },g
	{ "RenameFile_Fut", func_sig_RenameFile_Fut_1 },g
	{ "SetAutoShutdownTime", func_sig_SetAutoShutdownTime_1 },g
	{ "SetFileTimeStamp", func_sig_SetFileTimeStamp_1 },g
	{ "SetParameterData", func_sig_SetParameterData_1 },g
	{ "SetPropertyCase", func_sig_SetPropertyCase_1 },g
	{ "SetPropertyCase", func_sig_SetPropertyCase_2 },g
	{ "SleepTask", func_sig_SleepTask_1 },g
	{ "TakeSemaphore", func_sig_TakeSemaphore_1 },g
	{ "UIFS_WriteFirmInfoToFile", func_sig_UIFS_WriteFirmInfoToFile_1 },g
	{ "UnlockMainPower", func_sig_UnlockMainPower_1 },g
	{ "UpdateMBROnFlash", func_sig_UpdateMBROnFlash_1 },g
	{ "VbattGet", func_sig_VbattGet_1 },g
	{ "Write", func_sig_Write_1 },g
	{ "_log", func_sig__log_1 },g
	{ "_log10", func_sig__log10_1 },g
	{ "_pow", func_sig__pow_1 },g
	{ "_sqrt", func_sig__sqrt_1 },g
	{ "close", func_sig_close_1 },g
	{ "closedir", func_sig_closedir_1 },g
	{ "closefastdir", func_sig_closefastdir_1 },g
	{ "free", func_sig_free_1 },g
	{ "kbd_p1_f", func_sig_kbd_p1_f_1 },g
	{ "kbd_p1_f_cont", func_sig_kbd_p1_f_cont_1 },g
	{ "kbd_p2_f", func_sig_kbd_p2_f_1 },g
	{ "kbd_pwr_off", func_sig_kbd_pwr_off_1 },g
	{ "kbd_pwr_off", func_sig_kbd_pwr_off_2 },g
	{ "kbd_pwr_on", func_sig_kbd_pwr_on_1 },g
	{ "kbd_pwr_on", func_sig_kbd_pwr_on_2 },g
	{ "kbd_read_keys", func_sig_kbd_read_keys_1 },g
	{ "kbd_read_keys_r2", func_sig_kbd_read_keys_r2_1 },g
	{ "lseek", func_sig_lseek_1 },g
	{ "malloc", func_sig_malloc_1 },g
	{ "memcmp", func_sig_memcmp_1 },g
	{ "memcpy", func_sig_memcpy_1 },g
	{ "memset", func_sig_memset_1 },g
	{ "mkdir", func_sig_mkdir_1 },g
	{ "mktime_ext", func_sig_mktime_ext_1 },g
	{ "open", func_sig_open_1 },g
	{ "opendir", func_sig_opendir_1 },g
	{ "openfastdir", func_sig_openfastdir_1 },g
	{ "qsort", func_sig_qsort_1 },g
	{ "rand", func_sig_rand_1 },g
	{ "read", func_sig_read_1 },g
	{ "readfastdir", func_sig_readfastdir_1 },g
	{ "rename", func_sig_rename_1 },g
	{ "srand", func_sig_srand_1 },g
	{ "stat", func_sig_stat_1 },g
	{ "strcat", func_sig_strcat_1 },g
	{ "strchr", func_sig_strchr_1 },g
	{ "strcmp", func_sig_strcmp_1 },g
	{ "strcpy", func_sig_strcpy_1 },g
	{ "strcpy", func_sig_strcpy_2 },g
	{ "strftime", func_sig_strftime_1 },g
	{ "strlen", func_sig_strlen_1 },g
	{ "strncmp", func_sig_strncmp_1 },g
	{ "strncpy", func_sig_strncpy_1 },g
	{ "strncpy", func_sig_strncpy_2 },g
	{ "strrchr", func_sig_strrchr_1 },g
	{ "strrchr", func_sig_strrchr_2 },g
	{ "strtol", func_sig_strtol_1 },g
	{ "time", func_sig_time_1 },g
	{ "time", func_sig_time_2 },g
	{ "vsprintf", func_sig_vsprintf_1 },g
	{ "write", func_sig_write_1 },g
	{ NULL }
};
