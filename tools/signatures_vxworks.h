
static FuncSig func_sig_AllocateMemory_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0AF4DC
	{   3, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   4, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0AF4DC
	{   8, 0x00000064, 0xfdffffff }, // and:6:0x00000064
	{  11, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  13, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  15, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  16, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  17, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{  18, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0ADFDA
	{  20, 0xe59f0010, 0xfdffffff }, // ldr:4:0xE59F0010
	{  21, 0xe1a01043, 0xfdffffff }, // mov:6:0xE3A01043
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0007D5
	{  23, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  27, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  28, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  29, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0AF25C
	{  30, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  31, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_close_1[] = {
	{   1, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{   2, 0xe59fb95c, 0xfdffffff }, // ldr:4:0xE59FB95C
	{   3, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   4, 0xe59ba000, 0xfdffffff }, // ldr:4:0xE59BA000
	{   5, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   7, 0xe08d1008, 0xfdffffff }, // add:6:0xE28D1008
	{   8, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   9, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  10, 0xe1a0f00a, 0xfdffffff }, // mov:6:0xE1A0F00A
	{  11, 0xe1a00009, 0xfdffffff }, // mov:6:0xE1A00009
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000321
	{  13, 0xe59bb000, 0xfdffffff }, // ldr:4:0xE59BB000
	{  14, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  15, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  17, 0xe59d0008, 0xfdffffff }, // ldr:4:0xE59D0008
	{  18, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  19, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  20, 0xe1a0f00b, 0xfdffffff }, // mov:6:0xE1A0F00B
	{  21, 0xe08dd00c, 0xfdffffff }, // add:6:0xE28DD00C
	{  22, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  25, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{  26, 0xe59fb8fc, 0xfdffffff }, // ldr:4:0xE59FB8FC
	{  27, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{  28, 0xe1a08001, 0xfdffffff }, // mov:6:0xE1A08001
	{  29, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002
	{  30, 0xe59ba000, 0xfdffffff }, // ldr:4:0xE59BA000
	{  31, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_CreateTaskStrict_1[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe59dc00c, 0xfdffffff }, // ldr:4:0xE59DC00C
	{   3, 0xe58dc000, 0xfdffffff }, // str:4:0xE58DC000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBA0
	{   5, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   6, 0xe1540005, 0xfdffffff }, // cmp:7:0xE3540005
	{   7, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{   8, 0xe1a01019, 0xfdffffff }, // mov:6:0xE3A01019
	{   9, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFC5BA
	{  11, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  12, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  14, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 13/32 */
};

static FuncSig func_sig_DisableDispatch_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF165
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   3, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF177
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF1C4
	{   7, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   8, 0x01a0000f, 0xfdffffff }, // mov:6:0x03A0000F
	{   9, 0x11a00000, 0xfdffffff }, // mov:6:0x13A00000
	{  10, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  12, 0x60616e45, 0xfdffffff }, // rsb:6:0x62616E45
	{  15, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A206863
	{  17, 0x7066206c, 0xfdffffff }, // rsb:6:0x7266206C
	{  19, 0x7065746e, 0xfdffffff }, // rsb:6:0x7265746E
	{  22, 0x70656c64, 0xfdffffff }, // rsb:6:0x72656C64
	{  23, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  24, 0x60616e45, 0xfdffffff }, // rsb:6:0x62616E45
	{  27, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A206863
	{ -1, -1, -1 },
	/* 19/32 */
};

static FuncSig func_sig_EnableDispatch_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF142
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   3, 0xe59f0020, 0xfdffffff }, // ldr:4:0xE59F0020
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF154
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF1AD
	{   7, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   8, 0xe59f0010, 0xfdffffff }, // ldr:4:0xE59F0010
	{   9, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF14F
	{  11, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  12, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  21, 0x70726574, 0xfdffffff }, // rsb:6:0x72726574
	{  22, 0x20747075, 0xfdffffff }, // rsb:6:0x20747075
	{  24, 0x0072656c, 0xfdffffff }, // rsb:6:0x0072656C
	{  26, 0xe0507000, 0xfdffffff }, // sub:6:0xE2507000
	{  27, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{  28, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000023
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF126
	{  30, 0xe1a08000, 0xfdffffff }, // mov:6:0xE3A08000
	{  31, 0xe1500008, 0xfdffffff }, // cmp:7:0xE1500008
	{ -1, -1, -1 },
	/* 22/32 */
};

static FuncSig func_sig_ExitTask_1[] = {
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFEFFE
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   3, 0xe1a07000, 0xfdffffff }, // mov:6:0xE3A07000
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{   5, 0xe59f00e8, 0xfdffffff }, // ldr:4:0xE59F00E8
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF00F
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF0D5
	{   8, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF074
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  12, 0xe59f00d0, 0xfdffffff }, // ldr:4:0xE59F00D0
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF008
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFEFE7
	{  15, 0xe59f60c8, 0xfdffffff }, // ldr:4:0xE59F60C8
	{  16, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  17, 0xe1a01065, 0xfdffffff }, // mov:6:0xE3A01065
	{  18, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  19, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF950
	{  21, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000025
	{  23, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  24, 0xe5047058, 0xfdffffff }, // str:4:0xE5047058
	{  25, 0xe1a01065, 0xfdffffff }, // mov:6:0xE3A01065
	{  26, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF930
	{  28, 0xe0841008, 0xfdffffff }, // add:6:0xE2841008
	{  29, 0xe5942008, 0xfdffffff }, // ldr:4:0xE5942008
	{  30, 0xe5913004, 0xfdffffff }, // ldr:4:0xE5913004
	{  31, 0xe5823004, 0xfdffffff }, // str:4:0xE5823004
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_FreeMemory_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0AF4DC
	{   5, 0x00000064, 0xfdffffff }, // and:6:0x00000064
	{   8, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  10, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  12, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  13, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  14, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0ADFDA
	{  17, 0xe59f0010, 0xfdffffff }, // ldr:4:0xE59F0010
	{  18, 0xe1a01043, 0xfdffffff }, // mov:6:0xE3A01043
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0007D5
	{  20, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  24, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  25, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  26, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0AF25C
	{  27, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  28, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  29, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0AF4A1
	{  30, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  31, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_GetSystemTime_1[] = {
	{   1, 0xe59f6030, 0xfdffffff }, // ldr:4:0xE59F6030
	{   2, 0xe5965000, 0xfdffffff }, // ldr:4:0xE5965000
	{   3, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{   4, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   5, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017
	{   6, 0x11a03000, 0xfdffffff }, // mov:6:0x13A03000
	{   7, 0x15843000, 0xfdffffff }, // str:4:0x15843000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002C50
	{  10, 0xe5963008, 0xfdffffff }, // ldr:4:0xE5963008
	{  11, 0xe5843000, 0xfdffffff }, // str:4:0xE5843000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002C50
	{  13, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  15, 0x00001d34, 0xfdffffff }, // and:6:0x00001D34
	{  17, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  18, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002
	{  19, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{  20, 0xe1a08003, 0xfdffffff }, // mov:6:0xE1A08003
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002C44
	{  22, 0xe085e014, 0xfdffffff }, // add:6:0xE285E014
	{  23, 0xe59e2004, 0xfdffffff }, // ldr:4:0xE59E2004
	{  24, 0xe085c014, 0xfdffffff }, // add:6:0xE285C014
	{  25, 0xe152000c, 0xfdffffff }, // cmp:7:0xE152000C
	{  26, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  27, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000002
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002C40
	{  29, 0xe1a00005, 0xfdffffff }, // mov:6:0xE3A00005
	{  31, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_ints_disable_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0A5A9D
	{   3, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   4, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0A5A9F
	{   6, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   7, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   8, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0A5A9B
	{  10, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  11, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0ABA09
	{  13, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001
	{  14, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 15/32 */
};

static FuncSig func_sig_ints_enable_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0A5A9F
	{   3, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   4, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   5, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   6, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0A5A9B
	{   7, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   8, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0ABA09
	{  10, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001
	{  11, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 12/32 */
};

static FuncSig func_sig_ioctl_1[] = {
	{   0, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00037F
	{   1, 0xe1b02002, 0xfdffffff }, // mov:6:0xE1B02002
	{   3, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   4, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   5, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{   7, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{   9, 0xe1520002, 0xfdffffff }, // cmp:7:0xE3520002
	{  10, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000015
	{  11, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00002B
	{  12, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{  13, 0xe1a01007, 0xfdffffff }, // mov:6:0xE3A01007
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  15, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  17, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  18, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000025
	{  19, 0xe1a01008, 0xfdffffff }, // mov:6:0xE3A01008
	{  20, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFE9
	{  23, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00001F
	{  24, 0xe08bb000, 0xfdffffff }, // add:6:0xE08BB000
	{  25, 0xe1a00009, 0xfdffffff }, // mov:6:0xE1A00009
	{  26, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{  27, 0xe1a01007, 0xfdffffff }, // mov:6:0xE3A01007
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFE2
	{  29, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  31, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{ -1, -1, -1 },
	/* 28/32 */
};

static FuncSig func_sig_kbd_p1_f_1[] = {
	{   1, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00002F
	{   3, 0xe59f70a4, 0xfdffffff }, // ldr:4:0xE59F70A4
	{   4, 0xe1a0600d, 0xfdffffff }, // mov:6:0xE1A0600D
	{   5, 0xe59f50a0, 0xfdffffff }, // ldr:4:0xE59F50A0
	{   6, 0xe59f40a0, 0xfdffffff }, // ldr:4:0xE59F40A0
	{   7, 0xe1a0c002, 0xfdffffff }, // mov:6:0xE3A0C002
	{   8, 0xe1a0e006, 0xfdffffff }, // mov:6:0xE1A0E006
	{   9, 0xe1a0210c, 0xfdffffff }, // mov:6:0xE1A0210C
	{  10, 0xe5973002, 0xfdffffff }, // ldr:4:0xE7973002
	{  11, 0xe5951002, 0xfdffffff }, // ldr:4:0xE7951002
	{  12, 0xe5940002, 0xfdffffff }, // ldr:4:0xE7940002
	{  13, 0xe0033001, 0xfdffffff }, // and:6:0xE0033001
	{  15, 0xe05cc001, 0xfdffffff }, // sub:6:0xE25CC001
	{  16, 0xe58e3002, 0xfdffffff }, // str:4:0xE78E3002
	{  17, 0x5a000000, 0xff000000 }, // b, bl:3:0x5AFFFFF6
	{  18, 0xe59f4074, 0xfdffffff }, // ldr:4:0xE59F4074
	{  19, 0xe59f5074, 0xfdffffff }, // ldr:4:0xE59F5074
	{  20, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  21, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  22, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00002B
	{  24, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000345
	{  26, 0xe1a01002, 0xfdffffff }, // mov:6:0xE3A01002
	{  27, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001
	{  28, 0x11a00000, 0xfdffffff }, // mov:6:0x13A00000
	{  29, 0x01a00001, 0xfdffffff }, // mov:6:0x03A00001
	{  30, 0xe1a0e101, 0xfdffffff }, // mov:6:0xE1A0E101
	{  31, 0xe595c00e, 0xfdffffff }, // ldr:4:0xE795C00E
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_kbd_p1_f_cont_1[] = {
	{   0, 0xe59f70a4, 0xfdffffff }, // ldr:4:0xE59F70A4
	{   1, 0xe1a0600d, 0xfdffffff }, // mov:6:0xE1A0600D
	{   2, 0xe59f50a0, 0xfdffffff }, // ldr:4:0xE59F50A0
	{   3, 0xe59f40a0, 0xfdffffff }, // ldr:4:0xE59F40A0
	{   4, 0xe1a0c002, 0xfdffffff }, // mov:6:0xE3A0C002
	{   5, 0xe1a0e006, 0xfdffffff }, // mov:6:0xE1A0E006
	{   6, 0xe1a0210c, 0xfdffffff }, // mov:6:0xE1A0210C
	{   7, 0xe5973002, 0xfdffffff }, // ldr:4:0xE7973002
	{   8, 0xe5951002, 0xfdffffff }, // ldr:4:0xE7951002
	{   9, 0xe5940002, 0xfdffffff }, // ldr:4:0xE7940002
	{  10, 0xe0033001, 0xfdffffff }, // and:6:0xE0033001
	{  12, 0xe05cc001, 0xfdffffff }, // sub:6:0xE25CC001
	{  13, 0xe58e3002, 0xfdffffff }, // str:4:0xE78E3002
	{  14, 0x5a000000, 0xff000000 }, // b, bl:3:0x5AFFFFF6
	{  15, 0xe59f4074, 0xfdffffff }, // ldr:4:0xE59F4074
	{  16, 0xe59f5074, 0xfdffffff }, // ldr:4:0xE59F5074
	{  17, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  18, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  19, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00002B
	{  21, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000345
	{  23, 0xe1a01002, 0xfdffffff }, // mov:6:0xE3A01002
	{  24, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001
	{  25, 0x11a00000, 0xfdffffff }, // mov:6:0x13A00000
	{  26, 0x01a00001, 0xfdffffff }, // mov:6:0x03A00001
	{  27, 0xe1a0e101, 0xfdffffff }, // mov:6:0xE1A0E101
	{  28, 0xe595c00e, 0xfdffffff }, // ldr:4:0xE795C00E
	{  29, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  30, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{  31, 0xe594200e, 0xfdffffff }, // ldr:4:0xE794200E
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_kbd_p2_f_1[] = {
	{   1, 0xe04dd014, 0xfdffffff }, // sub:6:0xE24DD014
	{   2, 0xe08d5007, 0xfdffffff }, // add:6:0xE28D5007
	{   3, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00001F
	{   4, 0xe08d4008, 0xfdffffff }, // add:6:0xE28D4008
	{   6, 0xe59f1190, 0xfdffffff }, // ldr:4:0xE59F1190
	{   7, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200D
	{   8, 0xe1a03004, 0xfdffffff }, // mov:6:0xE1A03004
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00032D
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000A
	{  12, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000
	{  13, 0xe1500102, 0xfdffffff }, // cmp:7:0xE3500102
	{  14, 0x11500000, 0xfdffffff }, // cmp:7:0x13500000
	{  15, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  16, 0xe1500106, 0xfdffffff }, // cmp:7:0xE3500106
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  18, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000059
	{  21, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000000
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000081
	{  23, 0xe59fc150, 0xfdffffff }, // ldr:4:0xE59FC150
	{  24, 0xe1a0e004, 0xfdffffff }, // mov:6:0xE1A0E004
	{  25, 0xe1a03402, 0xfdffffff }, // mov:6:0xE3A03402
	{  26, 0xe1a03c43, 0xfdffffff }, // mov:6:0xE1A03C43
	{  27, 0xe1a01103, 0xfdffffff }, // mov:6:0xE1A01103
	{  28, 0xe59e2001, 0xfdffffff }, // ldr:4:0xE79E2001
	{  29, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  30, 0xe0430001, 0xfdffffff }, // sub:6:0xE2430001
	{  31, 0x159c3001, 0xfdffffff }, // ldr:4:0x179C3001
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_kbd_pwr_off_1[] = {
	{   0, 0xe1a020d0, 0xfdffffff }, // mov:6:0xE3A020D0
	{   1, 0xe0822103, 0xfdffffff }, // add:6:0xE2822103
	{   2, 0xe0822822, 0xfdffffff }, // add:6:0xE2822822
	{   3, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{   5, 0xe5823000, 0xfdffffff }, // str:4:0xE5823000
	{   6, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 6/7 */
};

static FuncSig func_sig_kbd_pwr_on_1[] = {
	{   0, 0xe1a020d0, 0xfdffffff }, // mov:6:0xE3A020D0
	{   1, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   2, 0xe0822103, 0xfdffffff }, // add:6:0xE2822103
	{   3, 0xe0822822, 0xfdffffff }, // add:6:0xE2822822
	{   4, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{   6, 0xe5823000, 0xfdffffff }, // str:4:0xE5823000
	{   7, 0xe1a00032, 0xfdffffff }, // mov:6:0xE3A00032
	{   8, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009
	{ -1, -1, -1 },
	/* 9/10 */
};

static FuncSig func_sig_kbd_read_keys_r2_1[] = {
	{   1, 0xe1a04822, 0xfdffffff }, // mov:6:0xE3A04822
	{   2, 0xe0844a03, 0xfdffffff }, // add:6:0xE2844A03
	{   3, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000186
	{   6, 0xe59f6038, 0xfdffffff }, // ldr:4:0xE59F6038
	{   8, 0xe1a012a3, 0xfdffffff }, // mov:6:0xE1A012A3
	{   9, 0xe5952101, 0xfdffffff }, // ldr:4:0xE7952101
	{  10, 0xe003301f, 0xfdffffff }, // and:6:0xE203301F
	{  12, 0xe5852101, 0xfdffffff }, // str:4:0xE7852101
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00017D
	{  16, 0xe1a012a2, 0xfdffffff }, // mov:6:0xE1A012A2
	{  17, 0xe5953101, 0xfdffffff }, // ldr:4:0xE7953101
	{  18, 0xe002201f, 0xfdffffff }, // and:6:0xE202201F
	{  20, 0xe5853101, 0xfdffffff }, // str:4:0xE7853101
	{  24, 0xe1a08001, 0xfdffffff }, // mov:6:0xE1A08001
	{  25, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{  26, 0xe1a0e000, 0xfdffffff }, // mov:6:0xE3A0E000
	{  27, 0xe1a0500d, 0xfdffffff }, // mov:6:0xE1A0500D
	{  29, 0xe59f6080, 0xfdffffff }, // ldr:4:0xE59F6080
	{  30, 0xe1a0c002, 0xfdffffff }, // mov:6:0xE3A0C002
	{  31, 0xe1a04005, 0xfdffffff }, // mov:6:0xE1A04005
	{ -1, -1, -1 },
	/* 21/32 */
};

static FuncSig func_sig_lseek_1[] = {
	{   0, 0xe1b02002, 0xfdffffff }, // mov:6:0xE1B02002
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   4, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{   6, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{   8, 0xe1520002, 0xfdffffff }, // cmp:7:0xE3520002
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000015
	{  10, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00002B
	{  11, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{  12, 0xe1a01007, 0xfdffffff }, // mov:6:0xE3A01007
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  14, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  16, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000025
	{  18, 0xe1a01008, 0xfdffffff }, // mov:6:0xE3A01008
	{  19, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFE9
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00001F
	{  23, 0xe08bb000, 0xfdffffff }, // add:6:0xE08BB000
	{  24, 0xe1a00009, 0xfdffffff }, // mov:6:0xE1A00009
	{  25, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{  26, 0xe1a01007, 0xfdffffff }, // mov:6:0xE3A01007
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFE2
	{  28, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  30, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  31, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000017
	{ -1, -1, -1 },
	/* 28/32 */
};

static FuncSig func_sig_MakeDirectory_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFCD
	{   4, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   5, 0xe1a0500d, 0xfdffffff }, // mov:6:0xE1A0500D
	{   6, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   7, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF1A
	{  10, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF29
	{  12, 0xe1a06000, 0xfdffffff }, // mov:6:0xE3A06000
	{  13, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  14, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  15, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  16, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097EA9
	{  18, 0xe0507000, 0xfdffffff }, // sub:6:0xE2507000
	{  19, 0xe1a01020, 0xfdffffff }, // mov:6:0xE3A01020
	{  20, 0xe1a02008, 0xfdffffff }, // mov:6:0xE1A02008
	{  21, 0xe1a0a006, 0xfdffffff }, // mov:6:0xE1A0A006
	{  22, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000004
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097D62
	{  24, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  25, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097D0F
	{  27, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  28, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF1F
	{  30, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  31, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_memchr_1[] = {
	{   1, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   2, 0xe00110ff, 0xfdffffff }, // and:6:0xE20110FF
	{   3, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000004
	{   5, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE15C0001
	{   6, 0x004b0001, 0xfdffffff }, // sub:6:0x024B0001
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   8, 0xe0422001, 0xfdffffff }, // sub:6:0xE2422001
	{   9, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF8
	{  11, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  13, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  14, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  15, 0x01a0f00e, 0xfdffffff }, // mov:6:0x01A0F00E
	{  18, 0xe15c0003, 0xfdffffff }, // cmp:7:0xE15C0003
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  20, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001
	{  21, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9
	{  22, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  23, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 19/32 */
};

static FuncSig func_sig_memcmp_1[] = {
	{   0, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   1, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{   2, 0x01a0f00e, 0xfdffffff }, // mov:6:0x01A0F00E
	{   5, 0xe15c0003, 0xfdffffff }, // cmp:7:0xE15C0003
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{   7, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9
	{   9, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  10, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 9/32 */
};

static FuncSig func_sig_memcpy_1[] = {
	{   1, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   2, 0xe1a00001, 0xfdffffff }, // mov:6:0xE1A00001
	{   3, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFB3B7
	{   5, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{   7, 0xe1510000, 0xfdffffff }, // cmp:7:0xE1510000
	{   9, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  10, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{  11, 0x2a000000, 0xff000000 }, // b, bl:3:0x2A00000E
	{  12, 0xe081c002, 0xfdffffff }, // add:6:0xE081C002
	{  13, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE15C0000
	{  14, 0x9a000000, 0xff000000 }, // b, bl:3:0x9A00000B
	{  15, 0xe0811002, 0xfdffffff }, // add:6:0xE0811002
	{  16, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  17, 0xe080b002, 0xfdffffff }, // add:6:0xE080B002
	{  18, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{  20, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000004
	{  25, 0xe0422001, 0xfdffffff }, // sub:6:0xE2422001
	{  27, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  28, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFA
	{  31, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{ -1, -1, -1 },
	/* 23/32 */
};

static FuncSig func_sig_memset_1[] = {
	{   1, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   2, 0xe1a03002, 0xfdffffff }, // mov:6:0xE1A03002
	{   3, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   4, 0xe1a01003, 0xfdffffff }, // mov:6:0xE1A01003
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFB5B8
	{   6, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{   8, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{  10, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFC
	{  12, 0xe0400001, 0xfdffffff }, // sub:6:0xE2400001
	{  14, 0xe013c0ff, 0xfdffffff }, // and:6:0xE213C0FF
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{  17, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{  18, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 14/32 */
};

static FuncSig func_sig_mkdir_1[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe1a0500d, 0xfdffffff }, // mov:6:0xE1A0500D
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   4, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{   5, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF4C
	{   7, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF5B
	{   9, 0xe1a06000, 0xfdffffff }, // mov:6:0xE3A06000
	{  10, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  11, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  12, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  13, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097EDB
	{  15, 0xe0507000, 0xfdffffff }, // sub:6:0xE2507000
	{  16, 0xe1a0101f, 0xfdffffff }, // mov:6:0xE3A0101F
	{  17, 0xe1a02008, 0xfdffffff }, // mov:6:0xE1A02008
	{  18, 0xe1a0a006, 0xfdffffff }, // mov:6:0xE1A0A006
	{  19, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000004
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097D94
	{  21, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  22, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097D41
	{  24, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  25, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF51
	{  27, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  28, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0001D7
	{  30, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  31, 0xe1570000, 0xfdffffff }, // cmp:7:0xE1570000
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_open_1[] = {
	{   0, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{   1, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFF68
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   4, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{   6, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{   9, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  11, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF04A
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000E
	{  15, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  16, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFED
	{  18, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  19, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  21, 0xba000000, 0xff000000 }, // b, bl:3:0xBA000007
	{  22, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  23, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{  24, 0xe1a0100a, 0xfdffffff }, // mov:6:0xE3A0100A
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEA4
	{  26, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  27, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE51
	{  29, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_PhySw_testgpio_1[] = {
	{   1, 0xe59f3068, 0xfdffffff }, // ldr:4:0xE59F3068
	{   2, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   3, 0xe1a03800, 0xfdffffff }, // mov:6:0xE1A03800
	{   4, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   5, 0xe1a010c1, 0xfdffffff }, // mov:6:0xE3A010C1
	{   6, 0xe59f0058, 0xfdffffff }, // ldr:4:0xE59F0058
	{   7, 0xe1a04843, 0xfdffffff }, // mov:6:0xE1A04843
	{   8, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFB112
	{  11, 0xe1a02822, 0xfdffffff }, // mov:6:0xE3A02822
	{  12, 0xe1a03804, 0xfdffffff }, // mov:6:0xE1A03804
	{  13, 0xe0822a03, 0xfdffffff }, // add:6:0xE2822A03
	{  14, 0xe1b03823, 0xfdffffff }, // mov:6:0xE1B03823
	{  15, 0xe0822173, 0xfdffffff }, // add:6:0xE2822173
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{  17, 0xe1a02822, 0xfdffffff }, // mov:6:0xE3A02822
	{  18, 0xe0822a03, 0xfdffffff }, // add:6:0xE2822A03
	{  19, 0xe1530001, 0xfdffffff }, // cmp:7:0xE3530001
	{  20, 0xe0822193, 0xfdffffff }, // add:6:0xE2822193
	{  21, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{  22, 0xe1a010d2, 0xfdffffff }, // mov:6:0xE3A010D2
	{  23, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001
	{  24, 0xe5925000, 0xfdffffff }, // ldr:4:0xE5925000
	{  25, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000000
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFB102
	{  27, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  29, 0x00001fac, 0xfdffffff }, // and:6:0x00001FAC
	{  31, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_ProtectFile_1[] = {
	{   1, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018
	{   2, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001D94
	{   5, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   7, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   8, 0xe1a00001, 0xfdffffff }, // mov:6:0xE1A00001
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000E
	{  10, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001D46
	{  12, 0xe0505000, 0xfdffffff }, // sub:6:0xE2505000
	{  13, 0xd1a00000, 0xfdffffff }, // mov:6:0xD3A00000
	{  14, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000009
	{  15, 0xe59d1004, 0xfdffffff }, // ldr:4:0xE59D1004
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001DB8
	{  18, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  19, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001D47
	{  21, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000
	{  23, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  24, 0x11a00001, 0xfdffffff }, // mov:6:0x13A00001
	{  25, 0xe08dd018, 0xfdffffff }, // add:6:0xE28DD018
	{  27, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 23/32 */
};

static FuncSig func_sig_read_1[] = {
	{   1, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{   2, 0xe59fb8fc, 0xfdffffff }, // ldr:4:0xE59FB8FC
	{   3, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   4, 0xe1a08001, 0xfdffffff }, // mov:6:0xE1A08001
	{   5, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002
	{   6, 0xe59ba000, 0xfdffffff }, // ldr:4:0xE59BA000
	{   7, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   9, 0xe08d1008, 0xfdffffff }, // add:6:0xE28D1008
	{  10, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  11, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  12, 0xe1a0f00a, 0xfdffffff }, // mov:6:0xE1A0F00A
	{  13, 0xe1a00009, 0xfdffffff }, // mov:6:0xE1A00009
	{  14, 0xe1a01008, 0xfdffffff }, // mov:6:0xE1A01008
	{  15, 0xe1a02007, 0xfdffffff }, // mov:6:0xE1A02007
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000339
	{  17, 0xe59bb000, 0xfdffffff }, // ldr:4:0xE59BB000
	{  18, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  19, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  21, 0xe59d0008, 0xfdffffff }, // ldr:4:0xE59D0008
	{  22, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  23, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  24, 0xe1a0f00b, 0xfdffffff }, // mov:6:0xE1A0F00B
	{  25, 0xe08dd00c, 0xfdffffff }, // add:6:0xE28DD00C
	{  26, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  29, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{  30, 0xe59fb88c, 0xfdffffff }, // ldr:4:0xE59FB88C
	{  31, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_strcmp_1[] = {
	{   2, 0xe15c0003, 0xfdffffff }, // cmp:7:0xE15C0003
	{   4, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{   5, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF8
	{   7, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   8, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 6/32 */
};

static FuncSig func_sig_strcpy_1[] = {
	{   0, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{   2, 0xe013c0ff, 0xfdffffff }, // and:6:0xE213C0FF
	{   4, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{   5, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{   6, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 5/32 */
};

static FuncSig func_sig_strlen_1[] = {
	{   0, 0xe0801001, 0xfdffffff }, // add:6:0xE2801001
	{   2, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   3, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFC
	{   4, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001
	{   5, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 5/32 */
};

static FuncSig func_sig_TakeSemaphore_1[] = {
	{   1, 0xe0506000, 0xfdffffff }, // sub:6:0xE2506000
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xe1a08001, 0xfdffffff }, // mov:6:0xE1A08001
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000015
	{   5, 0xe0165003, 0xfdffffff }, // and:6:0xE2165003
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000013
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF264
	{   8, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  10, 0xe59f0140, 0xfdffffff }, // ldr:4:0xE59F0140
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF276
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF2DD
	{  13, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  14, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  15, 0xe59f0130, 0xfdffffff }, // ldr:4:0xE59F0130
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF271
	{  17, 0xe58d5000, 0xfdffffff }, // str:4:0xE58D5000
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF336
	{  19, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF24D
	{  21, 0xe5963000, 0xfdffffff }, // ldr:4:0xE5963000
	{  22, 0xe0433002, 0xfdffffff }, // sub:6:0xE2433002
	{  23, 0xe1530001, 0xfdffffff }, // cmp:7:0xE3530001
	{  24, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{  25, 0x9a000000, 0xff000000 }, // b, bl:3:0x9A000002
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF24A
	{  27, 0xe1a00007, 0xfdffffff }, // mov:6:0xE3A00007
	{  28, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00003B
	{  29, 0xe5963008, 0xfdffffff }, // ldr:4:0xE5963008
	{  30, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  31, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_taskIdListGet_1[] = {
	{   1, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{   2, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   3, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0001A9
	{   5, 0xe59f005c, 0xfdffffff }, // ldr:4:0xE59F005C
	{   6, 0xe1a0200a, 0xfdffffff }, // mov:6:0xE1A0200A
	{   7, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{   8, 0xe590300c, 0xfdffffff }, // ldr:4:0xE590300C
	{   9, 0xe5933030, 0xfdffffff }, // ldr:4:0xE5933030
	{  10, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  11, 0xe1a0f003, 0xfdffffff }, // mov:6:0xE1A0F003
	{  12, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0001CA
	{  14, 0xe1590000, 0xfdffffff }, // cmp:7:0xE3590000
	{  15, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000005
	{  16, 0xe1a0a009, 0xfdffffff }, // mov:6:0xE1A0A009
	{  17, 0xe59bc000, 0xfdffffff }, // ldr:4:0xE59BC000
	{  18, 0xe05aa001, 0xfdffffff }, // sub:6:0xE25AA001
	{  19, 0xe04cc020, 0xfdffffff }, // sub:6:0xE24CC020
	{  20, 0xe48bc004, 0xfdffffff }, // str:4:0xE48BC004
	{  21, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFA
	{  22, 0xe08dd008, 0xfdffffff }, // add:6:0xE28DD008
	{  23, 0xe1a00009, 0xfdffffff }, // mov:6:0xE1A00009
	{  25, 0x0000e9e0, 0xfdffffff }, // and:6:0x0000E9E0
	{  26, 0x00430001, 0xfdffffff }, // sub:6:0x00430001
	{  27, 0x000a06ac, 0xfdffffff }, // and:6:0x000A06AC
	{  28, 0x000a065c, 0xfdffffff }, // and:6:0x000A065C
	{  29, 0x0000fb0c, 0xfdffffff }, // and:6:0x0000FB0C
	{  30, 0x0000fa2c, 0xfdffffff }, // and:6:0x0000FA2C
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_taskLock_1[] = {
	{   1, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018
	{   2, 0xe59fc970, 0xfdffffff }, // ldr:4:0xE59FC970
	{   3, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   4, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00001B
	{   6, 0xe59f3964, 0xfdffffff }, // ldr:4:0xE59F3964
	{   7, 0xe1a0b211, 0xfdffffff }, // mov:6:0xE3A0B211
	{   8, 0xe5933000, 0xfdffffff }, // ldr:4:0xE5933000
	{   9, 0xe0033211, 0xfdffffff }, // and:6:0xE2033211
	{  10, 0xe153000b, 0xfdffffff }, // cmp:7:0xE153000B
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  12, 0xe59fcea0, 0xfdffffff }, // ldr:4:0xE59FCEA0
	{  13, 0xe1a00039, 0xfdffffff }, // mov:6:0xE3A00039
	{  14, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  15, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  16, 0xe1a0f00c, 0xfdffffff }, // mov:6:0xE1A0F00C
	{  17, 0xe59fca14, 0xfdffffff }, // ldr:4:0xE59FCA14
	{  18, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  19, 0xe00cc00b, 0xfdffffff }, // and:6:0xE00CC00B
	{  20, 0xe15c000b, 0xfdffffff }, // cmp:7:0xE15C000B
	{  21, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000B
	{  22, 0xe59fca08, 0xfdffffff }, // ldr:4:0xE59FCA08
	{  23, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  24, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  25, 0xe58d1000, 0xfdffffff }, // str:4:0xE58D1000
	{  26, 0xe58d1004, 0xfdffffff }, // str:4:0xE58D1004
	{  27, 0xe58d1008, 0xfdffffff }, // str:4:0xE58D1008
	{  28, 0xe58d100c, 0xfdffffff }, // str:4:0xE58D100C
	{  29, 0xe1a00039, 0xfdffffff }, // mov:6:0xE3A00039
	{  30, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  31, 0xe1a03001, 0xfdffffff }, // mov:6:0xE1A03001
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_taskName_1[] = {
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000606
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   3, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{   5, 0xe5900034, 0xfdffffff }, // ldr:4:0xE5900034
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   7, 0x059f0158, 0xfdffffff }, // ldr:4:0x059F0158
	{  10, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{  11, 0xe59fb14c, 0xfdffffff }, // ldr:4:0xE59FB14C
	{  12, 0xe59f114c, 0xfdffffff }, // ldr:4:0xE59F114C
	{  13, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{  14, 0xe59b300c, 0xfdffffff }, // ldr:4:0xE59B300C
	{  15, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  16, 0xe5933034, 0xfdffffff }, // ldr:4:0xE5933034
	{  17, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  18, 0xe1a0f003, 0xfdffffff }, // mov:6:0xE1A0F003
	{  19, 0xe1b0a000, 0xfdffffff }, // mov:6:0xE1B0A000
	{  20, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFAEE0
	{  22, 0xe59fc128, 0xfdffffff }, // ldr:4:0xE59FC128
	{  23, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{  25, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000000
	{  26, 0xe0400020, 0xfdffffff }, // sub:6:0xE2400020
	{  27, 0xe08dd008, 0xfdffffff }, // add:6:0xE28DD008
	{  29, 0xe0400020, 0xfdffffff }, // sub:6:0xE2400020
	{  31, 0xe5900034, 0xfdffffff }, // ldr:4:0xE5900034
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_taskResume_1[] = {
	{   1, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018
	{   2, 0xe59fcd50, 0xfdffffff }, // ldr:4:0xE59FCD50
	{   3, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{   4, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   5, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000032
	{   7, 0xe59f3d40, 0xfdffffff }, // ldr:4:0xE59F3D40
	{   8, 0xe1a0b271, 0xfdffffff }, // mov:6:0xE3A0B271
	{   9, 0xe5933000, 0xfdffffff }, // ldr:4:0xE5933000
	{  10, 0xe0033271, 0xfdffffff }, // and:6:0xE2033271
	{  11, 0xe153000b, 0xfdffffff }, // cmp:7:0xE153000B
	{  12, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000018
	{  13, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  14, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000016
	{  15, 0xe59f0d08, 0xfdffffff }, // ldr:4:0xE59F0D08
	{  16, 0xe59ab030, 0xfdffffff }, // ldr:4:0xE59AB030
	{  17, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{  18, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE15B0000
	{  19, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008
	{  20, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  21, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  22, 0xe590c024, 0xfdffffff }, // ldr:4:0xE590C024
	{  23, 0xe15c000b, 0xfdffffff }, // cmp:7:0xE15C000B
	{  24, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFADE3
	{  26, 0xe59fccf8, 0xfdffffff }, // ldr:4:0xE59FCCF8
	{  27, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{  28, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000008
	{  29, 0xe59bb030, 0xfdffffff }, // ldr:4:0xE59BB030
	{  30, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  31, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000005
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_taskSuspend_1[] = {
	{   1, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018
	{   2, 0xe1b09000, 0xfdffffff }, // mov:6:0xE1B09000
	{   3, 0x059faf1c, 0xfdffffff }, // ldr:4:0x059FAF1C
	{   4, 0xe59fcf1c, 0xfdffffff }, // ldr:4:0xE59FCF1C
	{   5, 0x059aa000, 0xfdffffff }, // ldr:4:0x059AA000
	{   6, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   7, 0x11a0a000, 0xfdffffff }, // mov:6:0x11A0A000
	{   8, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000032
	{  10, 0xe59f3f08, 0xfdffffff }, // ldr:4:0xE59F3F08
	{  11, 0xe1a0b271, 0xfdffffff }, // mov:6:0xE3A0B271
	{  12, 0xe5933000, 0xfdffffff }, // ldr:4:0xE5933000
	{  13, 0xe0033271, 0xfdffffff }, // and:6:0xE2033271
	{  14, 0xe153000b, 0xfdffffff }, // cmp:7:0xE153000B
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000019
	{  16, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000017
	{  18, 0xe59f0ed0, 0xfdffffff }, // ldr:4:0xE59F0ED0
	{  19, 0xe59ab030, 0xfdffffff }, // ldr:4:0xE59AB030
	{  20, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{  21, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE15B0000
	{  22, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000
	{  23, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{  24, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  25, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  26, 0xe590c024, 0xfdffffff }, // ldr:4:0xE590C024
	{  27, 0xe1a0300b, 0xfdffffff }, // mov:6:0xE1A0300B
	{  28, 0xe15c000b, 0xfdffffff }, // cmp:7:0xE15C000B
	{  29, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFAE53
	{  31, 0xe59fceb8, 0xfdffffff }, // ldr:4:0xE59FCEB8
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_taskUnlock_1[] = {
	{   1, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018
	{   2, 0xe59f98c8, 0xfdffffff }, // ldr:4:0xE59F98C8
	{   3, 0xe59fb8c0, 0xfdffffff }, // ldr:4:0xE59FB8C0
	{   4, 0xe599c000, 0xfdffffff }, // ldr:4:0xE599C000
	{   5, 0xe59bb000, 0xfdffffff }, // ldr:4:0xE59BB000
	{   6, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00001B
	{   8, 0xe59f38b4, 0xfdffffff }, // ldr:4:0xE59F38B4
	{   9, 0xe1a0a211, 0xfdffffff }, // mov:6:0xE3A0A211
	{  10, 0xe5933000, 0xfdffffff }, // ldr:4:0xE5933000
	{  11, 0xe0033211, 0xfdffffff }, // and:6:0xE2033211
	{  12, 0xe153000a, 0xfdffffff }, // cmp:7:0xE153000A
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  14, 0xe59fcdf0, 0xfdffffff }, // ldr:4:0xE59FCDF0
	{  15, 0xe1a0003a, 0xfdffffff }, // mov:6:0xE3A0003A
	{  16, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  17, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  18, 0xe1a0f00c, 0xfdffffff }, // mov:6:0xE1A0F00C
	{  19, 0xe59fc964, 0xfdffffff }, // ldr:4:0xE59FC964
	{  20, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  21, 0xe00cc00a, 0xfdffffff }, // and:6:0xE00CC00A
	{  22, 0xe15c000a, 0xfdffffff }, // cmp:7:0xE15C000A
	{  23, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000B
	{  24, 0xe59fc958, 0xfdffffff }, // ldr:4:0xE59FC958
	{  25, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  26, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  27, 0xe58d1000, 0xfdffffff }, // str:4:0xE58D1000
	{  28, 0xe58d1004, 0xfdffffff }, // str:4:0xE58D1004
	{  29, 0xe58d1008, 0xfdffffff }, // str:4:0xE58D1008
	{  30, 0xe58d100c, 0xfdffffff }, // str:4:0xE58D100C
	{  31, 0xe1a0003a, 0xfdffffff }, // mov:6:0xE3A0003A
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_write_1[] = {
	{   1, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{   2, 0xe59fb88c, 0xfdffffff }, // ldr:4:0xE59FB88C
	{   3, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   4, 0xe1a08001, 0xfdffffff }, // mov:6:0xE1A08001
	{   5, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002
	{   6, 0xe59ba000, 0xfdffffff }, // ldr:4:0xE59BA000
	{   7, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   9, 0xe08d1008, 0xfdffffff }, // add:6:0xE28D1008
	{  10, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  11, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  12, 0xe1a0f00a, 0xfdffffff }, // mov:6:0xE1A0F00A
	{  13, 0xe1a00009, 0xfdffffff }, // mov:6:0xE1A00009
	{  14, 0xe1a01008, 0xfdffffff }, // mov:6:0xE1A01008
	{  15, 0xe1a02007, 0xfdffffff }, // mov:6:0xE1A02007
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000354
	{  17, 0xe59bb000, 0xfdffffff }, // ldr:4:0xE59BB000
	{  18, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  19, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  21, 0xe59d0008, 0xfdffffff }, // ldr:4:0xE59D0008
	{  22, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  23, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  24, 0xe1a0f00b, 0xfdffffff }, // mov:6:0xE1A0F00B
	{  25, 0xe08dd00c, 0xfdffffff }, // add:6:0xE28DD00C
	{  26, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  28, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00037F
	{  29, 0xe1b02002, 0xfdffffff }, // mov:6:0xE1B02002
	{  31, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_taskCreateHookAdd_1[] = {
	{   0, 0xe59f1380, 0xfdffffff }, // ldr:4:0xE59F1380
	{   1, 0xe1a02010, 0xfdffffff }, // mov:6:0xE3A02010
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFE3
	{   4, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   5, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   6, 0xe1a0a002, 0xfdffffff }, // mov:6:0xE1A0A002
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002B17
	{   8, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   9, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  10, 0xda000000, 0xff000000 }, // b, bl:3:0xDA00000E
	{  11, 0xe59bc100, 0xfdffffff }, // ldr:4:0xE79BC100
	{  12, 0xe15c0009, 0xfdffffff }, // cmp:7:0xE15C0009
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008
	{  14, 0xe08bb100, 0xfdffffff }, // add:6:0xE08BB100
	{  15, 0xe59bc004, 0xfdffffff }, // ldr:4:0xE59BC004
	{  16, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001
	{  17, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  18, 0xe48bc004, 0xfdffffff }, // str:4:0xE48BC004
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFA
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002B34
	{  21, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  22, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000006
	{  23, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001
	{  24, 0xe150000a, 0xfdffffff }, // cmp:7:0xE150000A
	{  25, 0xba000000, 0xff000000 }, // b, bl:3:0xBAFFFFF0
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002B2E
	{  27, 0xe59f0308, 0xfdffffff }, // ldr:4:0xE59F0308
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD81B
	{  31, 0xe59f12fc, 0xfdffffff }, // ldr:4:0xE59F12FC
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_taskDeleteHookAdd_1[] = {
	{   1, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{   2, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE3A0B000
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002B4C
	{   4, 0xe59f042c, 0xfdffffff }, // ldr:4:0xE59F042C
	{   5, 0xe590c040, 0xfdffffff }, // ldr:4:0xE590C040
	{   6, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   8, 0xe59f0410, 0xfdffffff }, // ldr:4:0xE59F0410
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD85F
	{  11, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000008
	{  12, 0xe1a0200e, 0xfdffffff }, // mov:6:0xE3A0200E
	{  13, 0xe0801038, 0xfdffffff }, // add:6:0xE2801038
	{  14, 0xe591c000, 0xfdffffff }, // ldr:4:0xE591C000
	{  15, 0xe0422001, 0xfdffffff }, // sub:6:0xE2422001
	{  16, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  17, 0xe581c004, 0xfdffffff }, // str:4:0xE581C004
	{  18, 0xe0411004, 0xfdffffff }, // sub:6:0xE2411004
	{  19, 0xaa000000, 0xff000000 }, // b, bl:3:0xAAFFFFF9
	{  20, 0xe580a000, 0xfdffffff }, // str:4:0xE580A000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002B64
	{  22, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  25, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{  26, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{  27, 0xe1a0b002, 0xfdffffff }, // mov:6:0xE1A0B002
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002B33
	{  29, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  30, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000009
	{  31, 0xe04aa004, 0xfdffffff }, // sub:6:0xE24AA004
	{ -1, -1, -1 },
	/* 28/32 */
};

static FuncSig func_sig_SleepTask_1[] = {
	{   1, 0xe0507000, 0xfdffffff }, // sub:6:0xE2507000
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000023
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF126
	{   5, 0xe1a08000, 0xfdffffff }, // mov:6:0xE3A08000
	{   6, 0xe1500008, 0xfdffffff }, // cmp:7:0xE1500008
	{   7, 0xe59f0088, 0xfdffffff }, // ldr:4:0xE59F0088
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF137
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF1FD
	{  11, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF114
	{  13, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{  14, 0xe1a01065, 0xfdffffff }, // mov:6:0xE3A01065
	{  15, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  16, 0xe59f0068, 0xfdffffff }, // ldr:4:0xE59F0068
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFA7E
	{  18, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  19, 0xe1a01007, 0xfdffffff }, // mov:6:0xE1A01007
	{  20, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200D
	{  21, 0xe0440014, 0xfdffffff }, // sub:6:0xE2440014
	{  22, 0xe0445058, 0xfdffffff }, // sub:6:0xE2445058
	{  23, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  24, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF10A
	{  26, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF191
	{  28, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009
	{  29, 0xe58d8000, 0xfdffffff }, // str:4:0xE58D8000
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0002E6
	{  31, 0xe5953008, 0xfdffffff }, // ldr:4:0xE5953008
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_CreateTask_1[] = {
	{   1, 0xe0509000, 0xfdffffff }, // sub:6:0xE2509000
	{   2, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{   3, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   4, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002
	{   5, 0xe1a0b003, 0xfdffffff }, // mov:6:0xE1A0B003
	{   6, 0x059f31a8, 0xfdffffff }, // ldr:4:0x059F31A8
	{   7, 0x05939000, 0xfdffffff }, // ldr:4:0x05939000
	{   8, 0xe04a3001, 0xfdffffff }, // sub:6:0xE24A3001
	{   9, 0xe153001f, 0xfdffffff }, // cmp:7:0xE353001F
	{  10, 0x8a000000, 0xff000000 }, // b, bl:3:0x8A000001
	{  11, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  12, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001
	{  13, 0xe1a00003, 0xfdffffff }, // mov:6:0xE3A00003
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00005F
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF0E0
	{  16, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  18, 0xe59f017c, 0xfdffffff }, // ldr:4:0xE59F017C
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF0F2
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF0D1
	{  21, 0xe59f2174, 0xfdffffff }, // ldr:4:0xE59F2174
	{  22, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{  23, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  24, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  25, 0xba000000, 0xff000000 }, // b, bl:3:0xBA000006
	{  26, 0xe0433001, 0xfdffffff }, // sub:6:0xE2433001
	{  27, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  28, 0xe5823000, 0xfdffffff }, // str:4:0xE5823000
	{  29, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000002
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF0CA
	{  31, 0xe1a00005, 0xfdffffff }, // mov:6:0xE3A00005
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_CreatePhysicalVram_1[] = {
	{   1, 0xe59fc098, 0xfdffffff }, // ldr:4:0xE59FC098
	{   2, 0xe59ce000, 0xfdffffff }, // ldr:4:0xE59CE000
	{   3, 0xe15e0001, 0xfdffffff }, // cmp:7:0xE35E0001
	{   4, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{   5, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   6, 0xe59f0088, 0xfdffffff }, // ldr:4:0xE59F0088
	{   7, 0xe1a010d4, 0xfdffffff }, // mov:6:0xE3A010D4
	{   8, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   9, 0xe1a04003, 0xfdffffff }, // mov:6:0xE1A04003
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFBC6EE
	{  12, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{  13, 0x11a03000, 0xfdffffff }, // mov:6:0x13A03000
	{  14, 0x01a03001, 0xfdffffff }, // mov:6:0x03A03001
	{  15, 0xe1570000, 0xfdffffff }, // cmp:7:0xE3570000
	{  17, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  18, 0xe59f0058, 0xfdffffff }, // ldr:4:0xE59F0058
	{  19, 0xe1a010d7, 0xfdffffff }, // mov:6:0xE3A010D7
	{  20, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000006
	{  21, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000
	{  22, 0x11a03000, 0xfdffffff }, // mov:6:0x13A03000
	{  23, 0x01a03001, 0xfdffffff }, // mov:6:0x03A03001
	{  24, 0xe1560000, 0xfdffffff }, // cmp:7:0xE3560000
	{  26, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  27, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFBC6DD
	{  29, 0xe59fc030, 0xfdffffff }, // ldr:4:0xE59FC030
	{  30, 0xe59fe024, 0xfdffffff }, // ldr:4:0xE59FE024
	{  31, 0xe1a01e2d, 0xfdffffff }, // mov:6:0xE3A01E2D
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_DisplayImagePhysicalScreen_1[] = {
	{   1, 0xe59f2198, 0xfdffffff }, // ldr:4:0xE59F2198
	{   2, 0xe1a04001, 0xfdffffff }, // mov:6:0xE3A04001
	{   3, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   4, 0xe04dd010, 0xfdffffff }, // sub:6:0xE24DD010
	{   5, 0xe1a08004, 0xfdffffff }, // mov:6:0xE1A08004
	{   6, 0xe1560002, 0xfdffffff }, // cmp:7:0xE1560002
	{   7, 0xe1a05003, 0xfdffffff }, // mov:6:0xE1A05003
	{   8, 0xe59d7034, 0xfdffffff }, // ldr:4:0xE59D7034
	{   9, 0xe1a09004, 0xfdffffff }, // mov:6:0xE1A09004
	{  10, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE3A0B000
	{  11, 0xe1a0a008, 0xfdffffff }, // mov:6:0xE1A0A008
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000D
	{  13, 0x8a000000, 0xff000000 }, // b, bl:3:0x8A000005
	{  14, 0xe1a03541, 0xfdffffff }, // mov:6:0xE3A03541
	{  15, 0xe0833aaf, 0xfdffffff }, // add:6:0xE2833AAF
	{  16, 0xe0833eaa, 0xfdffffff }, // add:6:0xE2833EAA
	{  17, 0xe1560003, 0xfdffffff }, // cmp:7:0xE1560003
	{  18, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  19, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000D
	{  20, 0xe59f3150, 0xfdffffff }, // ldr:4:0xE59F3150
	{  21, 0xe1560003, 0xfdffffff }, // cmp:7:0xE1560003
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009
	{  24, 0xe59f3144, 0xfdffffff }, // ldr:4:0xE59F3144
	{  25, 0xe583b000, 0xfdffffff }, // str:4:0xE583B000
	{  26, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009
	{  27, 0xe59f3138, 0xfdffffff }, // ldr:4:0xE59F3138
	{  28, 0xe5838000, 0xfdffffff }, // str:4:0xE5838000
	{  29, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000006
	{  30, 0xe59f212c, 0xfdffffff }, // ldr:4:0xE59F212C
	{  31, 0xe1a03002, 0xfdffffff }, // mov:6:0xE3A03002
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_ExecuteEventProcedure_1[] = {
	{   2, 0xe59f3088, 0xfdffffff }, // ldr:4:0xE59F3088
	{   3, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   4, 0xe59fc084, 0xfdffffff }, // ldr:4:0xE59FC084
	{   5, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{   6, 0xe59d1010, 0xfdffffff }, // ldr:4:0xE59D1010
	{   7, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200D
	{   8, 0xe58dc000, 0xfdffffff }, // str:4:0xE58DC000
	{   9, 0xe08d5014, 0xfdffffff }, // add:6:0xE28D5014
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE7D
	{  11, 0xe59f406c, 0xfdffffff }, // ldr:4:0xE59F406C
	{  12, 0xe1500019, 0xfdffffff }, // cmp:7:0xE3500019
	{  13, 0xe59f1068, 0xfdffffff }, // ldr:4:0xE59F1068
	{  14, 0xe59f2068, 0xfdffffff }, // ldr:4:0xE59F2068
	{  15, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005
	{  17, 0xe59d3010, 0xfdffffff }, // ldr:4:0xE59D3010
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0ACBD0
	{  19, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  20, 0xe59f3054, 0xfdffffff }, // ldr:4:0xE59F3054
	{  21, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  22, 0xe593f000, 0xfdffffff }, // ldr:4:0xE593F000
	{  23, 0xe59f304c, 0xfdffffff }, // ldr:4:0xE59F304C
	{  24, 0xe59d1010, 0xfdffffff }, // ldr:4:0xE59D1010
	{  25, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  26, 0xe59f2044, 0xfdffffff }, // ldr:4:0xE59F2044
	{  27, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  28, 0xe592f000, 0xfdffffff }, // ldr:4:0xE592F000
	{  29, 0xe59d3000, 0xfdffffff }, // ldr:4:0xE59D3000
	{  30, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  31, 0xe5931000, 0xfdffffff }, // ldr:4:0xE5931000
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_GetPropertyCase_1[] = {
	{   1, 0xe59f3064, 0xfdffffff }, // ldr:4:0xE59F3064
	{   2, 0xe593c000, 0xfdffffff }, // ldr:4:0xE593C000
	{   3, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{   4, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   5, 0xe1a01e11, 0xfdffffff }, // mov:6:0xE3A01E11
	{   6, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{   7, 0xe59f5050, 0xfdffffff }, // ldr:4:0xE59F5050
	{   8, 0xe59f0050, 0xfdffffff }, // ldr:4:0xE59F0050
	{   9, 0xe0811001, 0xfdffffff }, // add:6:0xE2811001
	{  10, 0xe1a04002, 0xfdffffff }, // mov:6:0xE1A04002
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFBE3C
	{  13, 0xe5953000, 0xfdffffff }, // ldr:4:0xE5953000
	{  14, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  15, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF29C
	{  17, 0xe1a03004, 0xfdffffff }, // mov:6:0xE1A03004
	{  18, 0xe1a01007, 0xfdffffff }, // mov:6:0xE1A01007
	{  19, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  20, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFC3
	{  22, 0xe5953000, 0xfdffffff }, // ldr:4:0xE5953000
	{  23, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  24, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF30D
	{ -1, -1, -1 },
	/* 25/26 */
};

static FuncSig func_sig_SetPropertyCase_1[] = {
	{   1, 0xe59f306c, 0xfdffffff }, // ldr:4:0xE59F306C
	{   2, 0xe593c000, 0xfdffffff }, // ldr:4:0xE593C000
	{   3, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   4, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   5, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   6, 0xe59f705c, 0xfdffffff }, // ldr:4:0xE59F705C
	{   7, 0xe59f005c, 0xfdffffff }, // ldr:4:0xE59F005C
	{   8, 0xe1a010e9, 0xfdffffff }, // mov:6:0xE3A010E9
	{   9, 0xe1a04002, 0xfdffffff }, // mov:6:0xE1A04002
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFBE84
	{  12, 0xe5973000, 0xfdffffff }, // ldr:4:0xE5973000
	{  13, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  14, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF2E4
	{  16, 0xe1a01006, 0xfdffffff }, // mov:6:0xE1A01006
	{  17, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  18, 0xe1a03004, 0xfdffffff }, // mov:6:0xE1A03004
	{  19, 0xe5970000, 0xfdffffff }, // ldr:4:0xE5970000
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF8A
	{  21, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  22, 0xe1a010ee, 0xfdffffff }, // mov:6:0xE3A010EE
	{  23, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{  24, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFBE76
	{  26, 0xe5973000, 0xfdffffff }, // ldr:4:0xE5973000
	{  27, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{ -1, -1, -1 },
	/* 27/29 */
};

static FuncSig func_sig_RefreshPhysicalScreen_1[] = {
	{   1, 0xe04dd010, 0xfdffffff }, // sub:6:0xE24DD010
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0002AA
	{   3, 0xe0105001, 0xfdffffff }, // and:6:0xE2105001
	{   4, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000022
	{   5, 0xe59f3090, 0xfdffffff }, // ldr:4:0xE59F3090
	{   6, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   7, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   8, 0xe59f0088, 0xfdffffff }, // ldr:4:0xE59F0088
	{   9, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  10, 0xe59f3084, 0xfdffffff }, // ldr:4:0xE59F3084
	{  11, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFAC5D4
	{  13, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000019
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA9C6A
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF476
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF113
	{  17, 0xe59f406c, 0xfdffffff }, // ldr:4:0xE59F406C
	{  18, 0xe59fe06c, 0xfdffffff }, // ldr:4:0xE59FE06C
	{  19, 0xe59f306c, 0xfdffffff }, // ldr:4:0xE59F306C
	{  20, 0xe59fc06c, 0xfdffffff }, // ldr:4:0xE59FC06C
	{  21, 0xe5931000, 0xfdffffff }, // ldr:4:0xE5931000
	{  22, 0xe59e2000, 0xfdffffff }, // ldr:4:0xE59E2000
	{  23, 0xe59c3000, 0xfdffffff }, // ldr:4:0xE59C3000
	{  24, 0xe594c000, 0xfdffffff }, // ldr:4:0xE594C000
	{  25, 0xe58d2008, 0xfdffffff }, // str:4:0xE58D2008
	{  26, 0xe58dc00c, 0xfdffffff }, // str:4:0xE58DC00C
	{  27, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  28, 0xe58d5000, 0xfdffffff }, // str:4:0xE58D5000
	{  29, 0xe58d5004, 0xfdffffff }, // str:4:0xE58D5004
	{  30, 0xe59fc048, 0xfdffffff }, // ldr:4:0xE59FC048
	{  31, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_IsStrobeChargeCompleted_1[] = {
	{   1, 0xe59f3060, 0xfdffffff }, // ldr:4:0xE59F3060
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE3A04000
	{   4, 0xe59f5058, 0xfdffffff }, // ldr:4:0xE59F5058
	{   5, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{   6, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{   7, 0xe1a01005, 0xfdffffff }, // mov:6:0xE3A01005
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFC9199
	{   9, 0xe1a01003, 0xfdffffff }, // mov:6:0xE3A01003
	{  10, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  11, 0xe1a02f7d, 0xfdffffff }, // mov:6:0xE3A02F7D
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFC8E9B
	{  13, 0xe1500004, 0xfdffffff }, // cmp:7:0xE1500004
	{  14, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000006
	{  16, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFC8F19
	{  18, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  19, 0xe1a01003, 0xfdffffff }, // mov:6:0xE3A01003
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFC8F02
	{  21, 0xe59d3000, 0xfdffffff }, // ldr:4:0xE59D3000
	{  22, 0xe0034001, 0xfdffffff }, // and:6:0xE2034001
	{  23, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  24, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  26, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_VbattGet_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF5BE
	{   2, 0xe59f3034, 0xfdffffff }, // ldr:4:0xE59F3034
	{   4, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   5, 0xe0622820, 0xfdffffff }, // rsb:6:0xE0622820
	{   6, 0xe0623182, 0xfdffffff }, // rsb:6:0xE0623182
	{   7, 0xe0833283, 0xfdffffff }, // add:6:0xE0833283
	{   8, 0xe0822103, 0xfdffffff }, // add:6:0xE0822103
	{   9, 0xe0622202, 0xfdffffff }, // rsb:6:0xE0622202
	{  10, 0xe59f3018, 0xfdffffff }, // ldr:4:0xE59F3018
	{  11, 0xe1a02202, 0xfdffffff }, // mov:6:0xE1A02202
	{  13, 0xe1a01fc2, 0xfdffffff }, // mov:6:0xE1A01FC2
	{  14, 0xe0800002, 0xfdffffff }, // add:6:0xE0800002
	{  15, 0xe0610740, 0xfdffffff }, // rsb:6:0xE0610740
	{  16, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  17, 0x00011480, 0xfdffffff }, // and:6:0x00011480
	{  20, 0xe59f50b8, 0xfdffffff }, // ldr:4:0xE59F50B8
	{  21, 0xe5954000, 0xfdffffff }, // ldr:4:0xE5954000
	{  22, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000
	{  23, 0xe59f00b0, 0xfdffffff }, // ldr:4:0xE59F00B0
	{  25, 0xe59f30ac, 0xfdffffff }, // ldr:4:0xE59F30AC
	{  26, 0xe59f20ac, 0xfdffffff }, // ldr:4:0xE59F20AC
	{  27, 0xe1a01004, 0xfdffffff }, // mov:6:0xE3A01004
	{  28, 0xe5831000, 0xfdffffff }, // str:4:0xE5831000
	{  29, 0xe5824000, 0xfdffffff }, // str:4:0xE5824000
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000FC
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF70B
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_GetZoomLensCurrentPosition_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE53
	{   2, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   3, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{   4, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{   5, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC6E
	{   7, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   8, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{   9, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  10, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  11, 0xe59f3008, 0xfdffffff }, // ldr:4:0xE59F3008
	{  12, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  13, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF6F766
	{  15, 0x000813d0, 0xfdffffff }, // and:6:0x000813D0
	{  17, 0xe59f4018, 0xfdffffff }, // ldr:4:0xE59F4018
	{  18, 0xe5943000, 0xfdffffff }, // ldr:4:0xE5943000
	{  19, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000D8
	{  22, 0xe1a03001, 0xfdffffff }, // mov:6:0xE3A03001
	{  23, 0xe5843000, 0xfdffffff }, // str:4:0xE5843000
	{  25, 0x0000aae4, 0xfdffffff }, // and:6:0x0000AAE4
	{  26, 0xe59f2010, 0xfdffffff }, // ldr:4:0xE59F2010
	{  27, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{  28, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  29, 0x11a03000, 0xfdffffff }, // mov:6:0x13A03000
	{  30, 0x15823000, 0xfdffffff }, // str:4:0x15823000
	{  31, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_GetZoomLensCurrentPoint_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCB8
	{   2, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   3, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{   4, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{   5, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE53
	{   7, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   8, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{   9, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  10, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC6E
	{  12, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{  13, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{  14, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  15, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  16, 0xe59f3008, 0xfdffffff }, // ldr:4:0xE59F3008
	{  17, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  18, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  19, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF6F766
	{  20, 0x000813d0, 0xfdffffff }, // and:6:0x000813D0
	{  22, 0xe59f4018, 0xfdffffff }, // ldr:4:0xE59F4018
	{  23, 0xe5943000, 0xfdffffff }, // ldr:4:0xE5943000
	{  24, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000D8
	{  27, 0xe1a03001, 0xfdffffff }, // mov:6:0xE3A03001
	{  28, 0xe5843000, 0xfdffffff }, // str:4:0xE5843000
	{  30, 0x0000aae4, 0xfdffffff }, // and:6:0x0000AAE4
	{  31, 0xe59f2010, 0xfdffffff }, // ldr:4:0xE59F2010
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_GetFocusLensSubjectDistance_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe59f3034, 0xfdffffff }, // ldr:4:0xE59F3034
	{   2, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   3, 0xe1a01f62, 0xfdffffff }, // mov:6:0xE3A01F62
	{   4, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   5, 0xe59f0028, 0xfdffffff }, // ldr:4:0xE59F0028
	{   6, 0xe0811003, 0xfdffffff }, // add:6:0xE2811003
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF674AE
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF1C0
	{  10, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{  11, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00004B
	{  13, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{  14, 0xe1a00820, 0xfdffffff }, // mov:6:0xE1A00820
	{  15, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  16, 0x0000abbc, 0xfdffffff }, // and:6:0x0000ABBC
	{  18, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  19, 0xe59f3054, 0xfdffffff }, // ldr:4:0xE59F3054
	{  20, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{  21, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{  22, 0xe1a01f66, 0xfdffffff }, // mov:6:0xE3A01F66
	{  23, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  24, 0xe59f0044, 0xfdffffff }, // ldr:4:0xE59F0044
	{  25, 0xe0811001, 0xfdffffff }, // add:6:0xE2811001
	{  26, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF6749B
	{  28, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  29, 0xe08d0002, 0xfdffffff }, // add:6:0xE28D0002
	{  30, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFAF0B
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_malloc_1[] = {
	{   0, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{   1, 0xe59f0070, 0xfdffffff }, // ldr:4:0xE59F0070
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFDF
	{   3, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{   4, 0xe59f0064, 0xfdffffff }, // ldr:4:0xE59F0064
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFE1E
	{   6, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   7, 0xe080000c, 0xfdffffff }, // add:6:0xE280000C
	{   8, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA003068
	{  10, 0x00110004, 0xfdffffff }, // and:6:0x00110004
	{  11, 0x0000eb7c, 0xfdffffff }, // and:6:0x0000EB7C
	{  12, 0x00580001, 0xfdffffff }, // sub:6:0x00580001
	{  13, 0x000a0754, 0xfdffffff }, // and:6:0x000A0754
	{  14, 0x0000eb64, 0xfdffffff }, // and:6:0x0000EB64
	{  16, 0x00110002, 0xfdffffff }, // and:6:0x00110002
	{  17, 0x0000e9ac, 0xfdffffff }, // and:6:0x0000E9AC
	{  18, 0x000a0318, 0xfdffffff }, // and:6:0x000A0318
	{  19, 0x00002732, 0xfdffffff }, // and:6:0x00002732
	{  20, 0x000a0260, 0xfdffffff }, // and:6:0x000A0260
	{  21, 0x10000100, 0xfdffffff }, // and:6:0x10000100
	{  22, 0x000a0244, 0xfdffffff }, // and:6:0x000A0244
	{  23, 0x0000eb74, 0xfdffffff }, // and:6:0x0000EB74
	{  24, 0x0000eb70, 0xfdffffff }, // and:6:0x0000EB70
	{  25, 0x000a0368, 0xfdffffff }, // and:6:0x000A0368
	{  26, 0x0000eb88, 0xfdffffff }, // and:6:0x0000EB88
	{  27, 0x00082ec0, 0xfdffffff }, // and:6:0x00082EC0
	{  31, 0x00082e08, 0xfdffffff }, // and:6:0x00082E08
	{ -1, -1, -1 },
	/* 28/32 */
};

static FuncSig func_sig_free_1[] = {
	{   0, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{   1, 0xe59f0064, 0xfdffffff }, // ldr:4:0xE59F0064
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFE1E
	{   3, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   4, 0xe080000c, 0xfdffffff }, // add:6:0xE280000C
	{   5, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   6, 0xea000000, 0xff000000 }, // b, bl:3:0xEA003068
	{   7, 0x00110004, 0xfdffffff }, // and:6:0x00110004
	{   8, 0x0000eb7c, 0xfdffffff }, // and:6:0x0000EB7C
	{   9, 0x00580001, 0xfdffffff }, // sub:6:0x00580001
	{  10, 0x000a0754, 0xfdffffff }, // and:6:0x000A0754
	{  11, 0x0000eb64, 0xfdffffff }, // and:6:0x0000EB64
	{  13, 0x00110002, 0xfdffffff }, // and:6:0x00110002
	{  14, 0x0000e9ac, 0xfdffffff }, // and:6:0x0000E9AC
	{  15, 0x000a0318, 0xfdffffff }, // and:6:0x000A0318
	{  16, 0x00002732, 0xfdffffff }, // and:6:0x00002732
	{  17, 0x000a0260, 0xfdffffff }, // and:6:0x000A0260
	{  18, 0x10000100, 0xfdffffff }, // and:6:0x10000100
	{  19, 0x000a0244, 0xfdffffff }, // and:6:0x000A0244
	{  20, 0x0000eb74, 0xfdffffff }, // and:6:0x0000EB74
	{  21, 0x0000eb70, 0xfdffffff }, // and:6:0x0000EB70
	{  22, 0x000a0368, 0xfdffffff }, // and:6:0x000A0368
	{  23, 0x0000eb88, 0xfdffffff }, // and:6:0x0000EB88
	{  24, 0x00082ec0, 0xfdffffff }, // and:6:0x00082EC0
	{  28, 0x00082e08, 0xfdffffff }, // and:6:0x00082E08
	{  29, 0x00002730, 0xfdffffff }, // and:6:0x00002730
	{  30, 0x000a02b4, 0xfdffffff }, // and:6:0x000A02B4
	{  31, 0x000a06ac, 0xfdffffff }, // and:6:0x000A06AC
	{ -1, -1, -1 },
	/* 28/32 */
};

static FuncSig func_sig_strcat_1[] = {
	{   0, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{   2, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   3, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFC
	{   4, 0xe0400001, 0xfdffffff }, // sub:6:0xE2400001
	{   6, 0xe013c0ff, 0xfdffffff }, // and:6:0xE213C0FF
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{   9, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{  10, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 8/32 */
};

static FuncSig func_sig_strchr_1[] = {
	{   0, 0xe00110ff, 0xfdffffff }, // and:6:0xE20110FF
	{   2, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE15C0001
	{   3, 0x01a0f00e, 0xfdffffff }, // mov:6:0x01A0F00E
	{   5, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9
	{   7, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   8, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 7/32 */
};

static FuncSig func_sig_opendir_1[] = {
	{   1, 0xe04dd048, 0xfdffffff }, // sub:6:0xE24DD048
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   3, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001196
	{   6, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   7, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000019
	{   9, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  10, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  12, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000D
	{  15, 0xe00cca0f, 0xfdffffff }, // and:6:0xE20CCA0F
	{  16, 0xe1a0c80c, 0xfdffffff }, // mov:6:0xE1A0C80C
	{  17, 0xe1a0c82c, 0xfdffffff }, // mov:6:0xE1A0C82C
	{  18, 0xe15c0901, 0xfdffffff }, // cmp:7:0xE35C0901
	{  19, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  20, 0xe1a00014, 0xfdffffff }, // mov:6:0xE3A00014
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0001DD
	{  22, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000004
	{  23, 0xe1a0006c, 0xfdffffff }, // mov:6:0xE3A0006C
	{  24, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001887
	{  26, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  27, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  28, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000FEC
	{  30, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  31, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000002
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_closedir_1[] = {
	{   1, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{   2, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001013
	{   5, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   6, 0x11a0000a, 0xfdffffff }, // mov:6:0x11A0000A
	{   7, 0x1b000000, 0xff000000 }, // b, bl:3:0x1B001C22
	{   8, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  10, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  11, 0xe1a01026, 0xfdffffff }, // mov:6:0xE3A01026
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00105A
	{  14, 0xe04dd048, 0xfdffffff }, // sub:6:0xE24DD048
	{  15, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  16, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001196
	{  19, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  20, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  21, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000019
	{  22, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  23, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  25, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  26, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000D
	{  28, 0xe00cca0f, 0xfdffffff }, // and:6:0xE20CCA0F
	{  29, 0xe1a0c80c, 0xfdffffff }, // mov:6:0xE1A0C80C
	{  30, 0xe1a0c82c, 0xfdffffff }, // mov:6:0xE1A0C82C
	{  31, 0xe15c0901, 0xfdffffff }, // cmp:7:0xE35C0901
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_readdir_1[] = {
	{   1, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   2, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{   3, 0xe1a01025, 0xfdffffff }, // mov:6:0xE3A01025
	{   4, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00106E
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   7, 0x11a00000, 0xfdffffff }, // mov:6:0x13A00000
	{   8, 0x008b0008, 0xfdffffff }, // add:6:0x028B0008
	{  10, 0xe1a0c000, 0xfdffffff }, // mov:6:0xE3A0C000
	{  11, 0xe580c004, 0xfdffffff }, // str:4:0xE580C004
	{  12, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 11/32 */
};

static FuncSig func_sig_rewinddir_1[] = {
	{   0, 0xe1a0c000, 0xfdffffff }, // mov:6:0xE3A0C000
	{   1, 0xe580c004, 0xfdffffff }, // str:4:0xE580C004
	{   2, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 3/32 */
};

static FuncSig func_sig_isalpha_1[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0003, 0xfdffffff }, // and:6:0xE20C0003
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 4/32 */
};

static FuncSig func_sig_isdigit_1[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0004, 0xfdffffff }, // and:6:0xE20C0004
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 4/32 */
};

static FuncSig func_sig_isspace_1[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0028, 0xfdffffff }, // and:6:0xE20C0028
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 4/32 */
};

static FuncSig func_sig_isupper_1[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0001, 0xfdffffff }, // and:6:0xE20C0001
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 4/32 */
};

static FuncSig func_sig_islower_1[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0002, 0xfdffffff }, // and:6:0xE20C0002
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 4/32 */
};

static FuncSig func_sig_ispunct_1[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0010, 0xfdffffff }, // and:6:0xE20C0010
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 4/32 */
};

static FuncSig func_sig_isxdigit_1[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0040, 0xfdffffff }, // and:6:0xE20C0040
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 4/32 */
};

static FuncSig func_sig_strncmp_1[] = {
	{   0, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   1, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{   2, 0x01a0f00e, 0xfdffffff }, // mov:6:0x01A0F00E
	{   5, 0xe15c0003, 0xfdffffff }, // cmp:7:0xE15C0003
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005
	{   8, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  10, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF6
	{  12, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  13, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 11/32 */
};

static FuncSig func_sig_strtol_1[] = {
	{   0, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   4, 0xe58d0028, 0xfdffffff }, // str:4:0xE58D0028
	{   5, 0xe58d102c, 0xfdffffff }, // str:4:0xE58D102C
	{   6, 0xe59f7180, 0xfdffffff }, // ldr:4:0xE59F7180
	{   7, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   8, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000
	{   9, 0xe5977000, 0xfdffffff }, // ldr:4:0xE5977000
	{  12, 0xe1130028, 0xfdffffff }, // tst:7:0xE3130028
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{  14, 0xe15b002d, 0xfdffffff }, // cmp:7:0xE35B002D
	{  15, 0x01a05001, 0xfdffffff }, // mov:6:0x03A05001
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  17, 0xe15b002b, 0xfdffffff }, // cmp:7:0xE35B002B
	{  19, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  21, 0xe1520010, 0xfdffffff }, // cmp:7:0xE3520010
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008
	{  23, 0xe15b0030, 0xfdffffff }, // cmp:7:0xE35B0030
	{  24, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000006
	{  26, 0xe15a0078, 0xfdffffff }, // cmp:7:0xE35A0078
	{  27, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  28, 0xe15a0058, 0xfdffffff }, // cmp:7:0xE35A0058
	{  30, 0x00899002, 0xfdffffff }, // add:6:0x02899002
	{  31, 0x01a06010, 0xfdffffff }, // mov:6:0x03A06010
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_rand_1[] = {
	{   0, 0xe59f002c, 0xfdffffff }, // ldr:4:0xE59F002C
	{   1, 0xe59f102c, 0xfdffffff }, // ldr:4:0xE59F102C
	{   2, 0xe59fc02c, 0xfdffffff }, // ldr:4:0xE59FC02C
	{   3, 0xe5903000, 0xfdffffff }, // ldr:4:0xE5903000
	{   5, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000
	{   6, 0xe59fc020, 0xfdffffff }, // ldr:4:0xE59FC020
	{   7, 0xe00c0821, 0xfdffffff }, // and:6:0xE00C0821
	{   8, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 8/32 */
};

static FuncSig func_sig_srand_1[] = {
	{   0, 0xe59fc008, 0xfdffffff }, // ldr:4:0xE59FC008
	{   1, 0xe58c0000, 0xfdffffff }, // str:4:0xE58C0000
	{   2, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   3, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 4/32 */
};

static FuncSig func_sig_stat_1[] = {
	{   1, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   3, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001171
	{   6, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{   9, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  10, 0xe1a0100a, 0xfdffffff }, // mov:6:0xE1A0100A
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFCB
	{  12, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  13, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000FD6
	{  17, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  18, 0xe1a0102e, 0xfdffffff }, // mov:6:0xE3A0102E
	{  19, 0xea000000, 0xff000000 }, // b, bl:3:0xEA001021
	{  21, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{  22, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  23, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00115D
	{  26, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  28, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{  29, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  30, 0xe1a0100a, 0xfdffffff }, // mov:6:0xE1A0100A
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_qsort_1[] = {
	{   0, 0xe1510001, 0xfdffffff }, // cmp:7:0xE3510001
	{   3, 0xe1510004, 0xfdffffff }, // cmp:7:0xE3510004
	{   4, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000001
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEF8
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEC7
	{   9, 0xe59f002c, 0xfdffffff }, // ldr:4:0xE59F002C
	{  10, 0xe59f102c, 0xfdffffff }, // ldr:4:0xE59F102C
	{  11, 0xe59fc02c, 0xfdffffff }, // ldr:4:0xE59FC02C
	{  12, 0xe5903000, 0xfdffffff }, // ldr:4:0xE5903000
	{  14, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000
	{  15, 0xe59fc020, 0xfdffffff }, // ldr:4:0xE59FC020
	{  16, 0xe00c0821, 0xfdffffff }, // and:6:0xE00C0821
	{  17, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 13/32 */
};

static FuncSig func_sig_localtime_1[] = {
	{   1, 0xe59fb010, 0xfdffffff }, // ldr:4:0xE59FB010
	{   2, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFD7
	{   4, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{   6, 0x0000f898, 0xfdffffff }, // and:6:0x0000F898 mul:11:0x0000F898
	{   7, 0x00082cec, 0xfdffffff }, // and:6:0x00082CEC
	{   9, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  10, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{  11, 0xe5910000, 0xfdffffff }, // ldr:4:0xE5910000
	{  12, 0xe1a0a002, 0xfdffffff }, // mov:6:0xE1A0A002
	{  13, 0xe1a01002, 0xfdffffff }, // mov:6:0xE1A01002
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE287
	{  15, 0xe5983000, 0xfdffffff }, // ldr:4:0xE5983000
	{  16, 0xe1a0100a, 0xfdffffff }, // mov:6:0xE1A0100A
	{  17, 0xe0800003, 0xfdffffff }, // add:6:0xE0800003
	{  18, 0xe5880000, 0xfdffffff }, // str:4:0xE5880000
	{  19, 0xe599b000, 0xfdffffff }, // ldr:4:0xE599B000
	{  20, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE280
	{  22, 0xe000009a, 0xfdffffff }, // and:6:0xE000009A mul:11:0xE000009A
	{  23, 0xe1a0100a, 0xfdffffff }, // mov:6:0xE1A0100A
	{  24, 0xe04bb000, 0xfdffffff }, // sub:6:0xE04BB000
	{  25, 0xe589b000, 0xfdffffff }, // str:4:0xE589B000
	{  26, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE27A
	{  28, 0xe000009a, 0xfdffffff }, // and:6:0xE000009A mul:11:0xE000009A
	{  29, 0xe04b0000, 0xfdffffff }, // sub:6:0xE04B0000
	{  30, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  31, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000005
	{ -1, -1, -1 },
	/* 32/32 */
};

static FuncSig func_sig_GetCurrentAvValue_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFB08A
	{   2, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   3, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{   4, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{   6, 0xe59f4028, 0xfdffffff }, // ldr:4:0xE59F4028
	{   7, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   8, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF679C8
	{  10, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{  11, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000006
	{  13, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{ -1, -1, -1 },
	/* 13/14 */
};

static FuncSig func_sig__pow_1[] = {
	{   0, 0xe04dd010, 0xfdffffff }, // sub:6:0xE24DD010
	{   2, 0xe04dd0e0, 0xfdffffff }, // sub:6:0xE24DD0E0
	{   3, 0xe1a0cf41, 0xfdffffff }, // mov:6:0xE3A0CF41
	{   4, 0xe08cc00d, 0xfdffffff }, // add:6:0xE08CC00D
	{   6, 0xe1a0cf43, 0xfdffffff }, // mov:6:0xE3A0CF43
	{   7, 0xe08cc00d, 0xfdffffff }, // add:6:0xE08CC00D
	{   9, 0xe59d0104, 0xfdffffff }, // ldr:4:0xE59D0104
	{  10, 0xe59d1108, 0xfdffffff }, // ldr:4:0xE59D1108
	{  11, 0xe08d2068, 0xfdffffff }, // add:6:0xE28D2068
	{  13, 0xe59dc06c, 0xfdffffff }, // ldr:4:0xE59DC06C
	{  14, 0xe59d010c, 0xfdffffff }, // ldr:4:0xE59D010C
	{  15, 0xe59d1110, 0xfdffffff }, // ldr:4:0xE59D1110
	{  16, 0xe58dc020, 0xfdffffff }, // str:4:0xE58DC020
	{  17, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{  18, 0xe08d2070, 0xfdffffff }, // add:6:0xE28D2070
	{  19, 0xe58d3014, 0xfdffffff }, // str:4:0xE58D3014
	{  21, 0xe59dc074, 0xfdffffff }, // ldr:4:0xE59DC074
	{  22, 0xe58dc010, 0xfdffffff }, // str:4:0xE58DC010
	{  23, 0xe59dc020, 0xfdffffff }, // ldr:4:0xE59DC020
	{  25, 0xe5920000, 0xfdffffff }, // ldr:4:0xE5920000
	{  26, 0xe00cc003, 0xfdffffff }, // and:6:0xE00CC003
	{  27, 0xe59d3010, 0xfdffffff }, // ldr:4:0xE59D3010
	{  28, 0xe58dc008, 0xfdffffff }, // str:4:0xE58DC008
	{  30, 0xe003c00c, 0xfdffffff }, // and:6:0xE003C00C
	{  31, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig__log_1[] = {
	{   1, 0xe04dd050, 0xfdffffff }, // sub:6:0xE24DD050
	{   2, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   3, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{   4, 0xe08d0018, 0xfdffffff }, // add:6:0xE28D0018
	{   6, 0xe59dc01c, 0xfdffffff }, // ldr:4:0xE59DC01C
	{   7, 0xe58dc008, 0xfdffffff }, // str:4:0xE58DC008
	{   8, 0xe59d3008, 0xfdffffff }, // ldr:4:0xE59D3008
	{   9, 0xe1a0c000, 0xfdffffff }, // mov:6:0xE3A0C000
	{  10, 0xe5901000, 0xfdffffff }, // ldr:4:0xE5901000
	{  11, 0xe1530601, 0xfdffffff }, // cmp:7:0xE3530601
	{  12, 0xe58dc010, 0xfdffffff }, // str:4:0xE58DC010
	{  13, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000017
	{  14, 0xe59d3008, 0xfdffffff }, // ldr:4:0xE59D3008
	{  16, 0xe0033002, 0xfdffffff }, // and:6:0xE0033002
	{  18, 0x059f160c, 0xfdffffff }, // ldr:4:0x059F160C
	{  19, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00017F
	{  21, 0xe59dc008, 0xfdffffff }, // ldr:4:0xE59DC008
	{  22, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  23, 0xb59f15fc, 0xfdffffff }, // ldr:4:0xB59F15FC
	{  24, 0xb1a00000, 0xfdffffff }, // mov:6:0xB3A00000
	{  25, 0xba000000, 0xff000000 }, // b, bl:3:0xBA00017A
	{  27, 0xe1a01009, 0xfdffffff }, // mov:6:0xE1A01009
	{  28, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  29, 0xe58dc010, 0xfdffffff }, // str:4:0xE58DC010
	{  30, 0xe59f35e4, 0xfdffffff }, // ldr:4:0xE59F35E4
	{  31, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig__log10_1[] = {
	{   1, 0xe04dd020, 0xfdffffff }, // sub:6:0xE24DD020
	{   2, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   3, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{   4, 0xe08db008, 0xfdffffff }, // add:6:0xE28DB008
	{   6, 0xe59da00c, 0xfdffffff }, // ldr:4:0xE59DA00C
	{   7, 0xe59b4000, 0xfdffffff }, // ldr:4:0xE59B4000
	{   8, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE3A0B000
	{   9, 0xe15a0601, 0xfdffffff }, // cmp:7:0xE35A0601
	{  10, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000014
	{  12, 0xe00ac00c, 0xfdffffff }, // and:6:0xE00AC00C
	{  14, 0x059f110c, 0xfdffffff }, // ldr:4:0x059F110C
	{  15, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00003F
	{  17, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{  18, 0xb59f1100, 0xfdffffff }, // ldr:4:0xB59F1100
	{  19, 0xb1a00000, 0xfdffffff }, // mov:6:0xB3A00000
	{  20, 0xba000000, 0xff000000 }, // b, bl:3:0xBA00003B
	{  22, 0xe1a01009, 0xfdffffff }, // mov:6:0xE1A01009
	{  23, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  24, 0xe59f30ec, 0xfdffffff }, // ldr:4:0xE59F30EC
	{  25, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001620
	{  27, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{  28, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  29, 0xe58d0018, 0xfdffffff }, // str:4:0xE58D0018
	{  30, 0xe58d101c, 0xfdffffff }, // str:4:0xE58D101C
	{  31, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig__sqrt_1[] = {
	{   1, 0xe1a0c470, 0xfdffffff }, // mov:6:0xE3A0C470
	{   3, 0xe111000c, 0xfdffffff }, // tst:7:0xE111000C
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000044
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000064
	{   7, 0xe1110480, 0xfdffffff }, // tst:7:0xE3110480
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000066
	{   9, 0xe1a0ca21, 0xfdffffff }, // mov:6:0xE1A0CA21
	{  12, 0xe08cc0fd, 0xfdffffff }, // add:6:0xE28CC0FD
	{  13, 0xe1b0c0ac, 0xfdffffff }, // mov:6:0xE1B0C0AC
	{  14, 0xe08ccf60, 0xfdffffff }, // add:6:0xE28CCF60
	{  15, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000001
	{  16, 0xe1b00080, 0xfdffffff }, // mov:6:0xE1B00080
	{  18, 0xe1a01501, 0xfdffffff }, // mov:6:0xE1A01501
	{  20, 0xe1a00500, 0xfdffffff }, // mov:6:0xE1A00500
	{  21, 0xe1a02440, 0xfdffffff }, // mov:6:0xE3A02440
	{  22, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{  23, 0xe0411440, 0xfdffffff }, // sub:6:0xE2411440
	{  24, 0xe1a0e540, 0xfdffffff }, // mov:6:0xE3A0E540
	{  25, 0xe0514002, 0xfdffffff }, // sub:6:0xE0514002
	{  26, 0x2054400e, 0xfdffffff }, // sub:6:0x2054400E
	{  27, 0x21a01004, 0xfdffffff }, // mov:6:0x21A01004
	{  28, 0x2082208e, 0xfdffffff }, // add:6:0x2082208E
	{  29, 0xe1b00080, 0xfdffffff }, // mov:6:0xE1B00080
	{  31, 0xe1b0e0ae, 0xfdffffff }, // mov:6:0xE1B0E0AE
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_strncpy_1[] = {
	{   0, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   2, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   3, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000C
	{   5, 0xe013c0ff, 0xfdffffff }, // and:6:0xE213C0FF
	{   7, 0x00422001, 0xfdffffff }, // sub:6:0x02422001
	{   8, 0x01a01000, 0xfdffffff }, // mov:6:0x03A01000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  10, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF7
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000003
	{  14, 0xe0422001, 0xfdffffff }, // sub:6:0xE2422001
	{  15, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{  18, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{  21, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000007
	{  23, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{  25, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{  26, 0x0a000000, 0xff000000 }, // b, bl:3:0x0AFFFFF8
	{  27, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE15A0000
	{  28, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFA
	{  29, 0xe0420001, 0xfdffffff }, // sub:6:0xE2420001
	{  30, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000000
	{  31, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_strrchr_1[] = {
	{   0, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{   1, 0xe00110ff, 0xfdffffff }, // and:6:0xE20110FF
	{   3, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE15C0001
	{   4, 0x01a02000, 0xfdffffff }, // mov:6:0x01A02000
	{   6, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9
	{   8, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{   9, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 8/32 */
};

static FuncSig func_sig_tolower_1[] = {
	{   0, 0xe040c041, 0xfdffffff }, // sub:6:0xE240C041
	{   1, 0xe15c0019, 0xfdffffff }, // cmp:7:0xE35C0019
	{   2, 0x90800020, 0xfdffffff }, // add:6:0x92800020
	{   3, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 4/32 */
};

static FuncSig func_sig_toupper_1[] = {
	{   0, 0xe040c061, 0xfdffffff }, // sub:6:0xE240C061
	{   1, 0xe15c0019, 0xfdffffff }, // cmp:7:0xE35C0019
	{   2, 0x90400020, 0xfdffffff }, // sub:6:0x92400020
	{   3, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 4/32 */
};

static FuncSig func_sig_SetParameterData_1[] = {
	{   1, 0xe59f30c4, 0xfdffffff }, // ldr:4:0xE59F30C4
	{   2, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{   3, 0xe593c000, 0xfdffffff }, // ldr:4:0xE593C000
	{   4, 0xe1a02802, 0xfdffffff }, // mov:6:0xE1A02802
	{   5, 0xe1a03800, 0xfdffffff }, // mov:6:0xE1A03800
	{   6, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{   7, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   8, 0xe1a01fe5, 0xfdffffff }, // mov:6:0xE3A01FE5
	{   9, 0xe59f70a8, 0xfdffffff }, // ldr:4:0xE59F70A8
	{  10, 0xe59f00a8, 0xfdffffff }, // ldr:4:0xE59F00A8
	{  11, 0xe0811001, 0xfdffffff }, // add:6:0xE2811001
	{  12, 0xe1a04843, 0xfdffffff }, // mov:6:0xE1A04843
	{  13, 0xe1a05842, 0xfdffffff }, // mov:6:0xE1A05842
	{  14, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFAD61C
	{  16, 0xe1a02804, 0xfdffffff }, // mov:6:0xE1A02804
	{  17, 0xe1a03822, 0xfdffffff }, // mov:6:0xE1A03822
	{  19, 0xe1a01fe5, 0xfdffffff }, // mov:6:0xE3A01FE5
	{  20, 0xe1a04804, 0xfdffffff }, // mov:6:0xE1A04804
	{  21, 0xe1120101, 0xfdffffff }, // tst:7:0xE3120101
	{  22, 0xe59f0078, 0xfdffffff }, // ldr:4:0xE59F0078
	{  23, 0xe0811001, 0xfdffffff }, // add:6:0xE2811001
	{  24, 0xe1a04824, 0xfdffffff }, // mov:6:0xE1A04824
	{  25, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFAD611
	{  27, 0xe1a01fe5, 0xfdffffff }, // mov:6:0xE3A01FE5
	{  28, 0xe154005d, 0xfdffffff }, // cmp:7:0xE354005D
	{  29, 0xe59f005c, 0xfdffffff }, // ldr:4:0xE59F005C
	{  30, 0xe0811001, 0xfdffffff }, // add:6:0xE2811001
	{  31, 0x9a000000, 0xff000000 }, // b, bl:3:0x9A000000
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_GetParameterData_1[] = {
	{   1, 0xe59f30a8, 0xfdffffff }, // ldr:4:0xE59F30A8
	{   2, 0xe593c000, 0xfdffffff }, // ldr:4:0xE593C000
	{   3, 0xe1a02802, 0xfdffffff }, // mov:6:0xE1A02802
	{   4, 0xe1a03800, 0xfdffffff }, // mov:6:0xE1A03800
	{   5, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{   6, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   7, 0xe1a01fe7, 0xfdffffff }, // mov:6:0xE3A01FE7
	{   8, 0xe59f7090, 0xfdffffff }, // ldr:4:0xE59F7090
	{   9, 0xe59f0090, 0xfdffffff }, // ldr:4:0xE59F0090
	{  10, 0xe0811003, 0xfdffffff }, // add:6:0xE2811003
	{  11, 0xe1a04843, 0xfdffffff }, // mov:6:0xE1A04843
	{  12, 0xe1a05842, 0xfdffffff }, // mov:6:0xE1A05842
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFAD5E5
	{  15, 0xe1a02804, 0xfdffffff }, // mov:6:0xE1A02804
	{  16, 0xe1a03822, 0xfdffffff }, // mov:6:0xE1A03822
	{  18, 0xe1a01fe7, 0xfdffffff }, // mov:6:0xE3A01FE7
	{  19, 0xe1a04804, 0xfdffffff }, // mov:6:0xE1A04804
	{  20, 0xe1120101, 0xfdffffff }, // tst:7:0xE3120101
	{  21, 0xe59f0060, 0xfdffffff }, // ldr:4:0xE59F0060
	{  22, 0xe0811003, 0xfdffffff }, // add:6:0xE2811003
	{  23, 0xe1a04824, 0xfdffffff }, // mov:6:0xE1A04824
	{  24, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFAD5DA
	{  26, 0xe1a01fe7, 0xfdffffff }, // mov:6:0xE3A01FE7
	{  27, 0xe154005d, 0xfdffffff }, // cmp:7:0xE354005D
	{  28, 0xe59f0044, 0xfdffffff }, // ldr:4:0xE59F0044
	{  29, 0xe0811003, 0xfdffffff }, // add:6:0xE2811003
	{  30, 0x9a000000, 0xff000000 }, // b, bl:3:0x9A000000
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFAD5D4
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_rename_1[] = {
	{   0, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   2, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   3, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{   4, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{   7, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{   9, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF04A
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000E
	{  13, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  14, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFED
	{  16, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  17, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  19, 0xba000000, 0xff000000 }, // b, bl:3:0xBA000007
	{  20, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  21, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{  22, 0xe1a0100a, 0xfdffffff }, // mov:6:0xE3A0100A
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEA4
	{  24, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  25, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE51
	{  27, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  30, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{  31, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_chdir_1[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   3, 0xe58d0000, 0xfdffffff }, // str:4:0xE58D0000
	{   4, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0002B4
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000010
	{   9, 0xe59dc000, 0xfdffffff }, // ldr:4:0xE59DC000
	{  10, 0xe15c000b, 0xfdffffff }, // cmp:7:0xE15C000B
	{  11, 0x059fb28c, 0xfdffffff }, // ldr:4:0x059FB28C
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  13, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE624
	{  15, 0xe1500c01, 0xfdffffff }, // cmp:7:0xE3500C01
	{  16, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000004
	{  17, 0xe59fb278, 0xfdffffff }, // ldr:4:0xE59FB278
	{  18, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF024
	{  21, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000003
	{  22, 0xe59f0250, 0xfdffffff }, // ldr:4:0xE59F0250
	{  23, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE5C1
	{  25, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  26, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  28, 0xe59f1238, 0xfdffffff }, // ldr:4:0xE59F1238
	{  29, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFE5BC
	{  30, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFE0
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_time_1[] = {
	{   1, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{   2, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{   3, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   4, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000209
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{   8, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   9, 0x159dc000, 0xfdffffff }, // ldr:4:0x159DC000
	{  10, 0x158ac000, 0xfdffffff }, // str:4:0x158AC000
	{  11, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000000
	{  14, 0xe08dd008, 0xfdffffff }, // add:6:0xE28DD008
	{  17, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{  18, 0xe59fb418, 0xfdffffff }, // ldr:4:0xE59FB418
	{  19, 0xe59bb000, 0xfdffffff }, // ldr:4:0xE59BB000
	{  20, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  23, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  24, 0xe1a0f00b, 0xfdffffff }, // mov:6:0xE1A0F00B
	{  25, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  26, 0xe08dd008, 0xfdffffff }, // add:6:0xE28DD008
	{  27, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  30, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{  31, 0xe59fb3e8, 0xfdffffff }, // ldr:4:0xE59FB3E8
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_utime_1[] = {
	{   1, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   3, 0xe59f2034, 0xfdffffff }, // ldr:4:0xE59F2034
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00114C
	{   6, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000007
	{   9, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  10, 0xe1a0200a, 0xfdffffff }, // mov:6:0xE1A0200A
	{  11, 0xe1a0102c, 0xfdffffff }, // mov:6:0xE3A0102C
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001003
	{  13, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  14, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000FB0
	{  16, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  18, 0x000001b6, 0xfdffffff }, // and:6:0x000001B6
	{  20, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  21, 0xe1a00032, 0xfdffffff }, // mov:6:0xE3A00032
	{  22, 0xe1a01004, 0xfdffffff }, // mov:6:0xE3A01004
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00183F
	{  24, 0xe59fc5d0, 0xfdffffff }, // ldr:4:0xE59FC5D0
	{  25, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  26, 0xe58c0000, 0xfdffffff }, // str:4:0xE58C0000
	{  28, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000010
	{  29, 0xe59f05c0, 0xfdffffff }, // ldr:4:0xE59F05C0
	{  30, 0xe1a03032, 0xfdffffff }, // mov:6:0xE3A03032
	{  31, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_iosDevAdd_1[] = {
	{   1, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{   2, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   3, 0xe1a09002, 0xfdffffff }, // mov:6:0xE1A09002
	{   4, 0xe1a00001, 0xfdffffff }, // mov:6:0xE1A00001
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFC3
	{   6, 0xe1b01000, 0xfdffffff }, // mov:6:0xE1B01000
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008
	{   8, 0xe590000c, 0xfdffffff }, // ldr:4:0xE590000C
	{   9, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE292
	{  11, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  12, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  13, 0xe59f036c, 0xfdffffff }, // ldr:4:0xE59F036C
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFED51
	{  16, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000011
	{  17, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE348
	{  19, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000772
	{  21, 0xe1b01000, 0xfdffffff }, // mov:6:0xE1B01000
	{  23, 0xe58a100c, 0xfdffffff }, // str:4:0xE58A100C
	{  25, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008
	{  26, 0xe1a00001, 0xfdffffff }, // mov:6:0xE1A00001
	{  27, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE2E5
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF6B
	{  30, 0xe59f02f8, 0xfdffffff }, // ldr:4:0xE59F02F8
	{  31, 0xe1a0100a, 0xfdffffff }, // mov:6:0xE1A0100A
	{ -1, -1, -1 },
	/* 28/32 */
};

static FuncSig func_sig_iosDrvInstall_1[] = {
	{   1, 0xe59d8024, 0xfdffffff }, // ldr:4:0xE59D8024
	{   2, 0xe59d9028, 0xfdffffff }, // ldr:4:0xE59D9028
	{   3, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE3A0B000
	{   4, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{   5, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{   6, 0xe1a05002, 0xfdffffff }, // mov:6:0xE1A05002
	{   7, 0xe1a04003, 0xfdffffff }, // mov:6:0xE1A04003
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFECF
	{   9, 0xe59f00bc, 0xfdffffff }, // ldr:4:0xE59F00BC
	{  10, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{  11, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001
	{  12, 0xda000000, 0xff000000 }, // b, bl:3:0xDA00000D
	{  13, 0xe59fc08c, 0xfdffffff }, // ldr:4:0xE59FC08C
	{  14, 0xe040a001, 0xfdffffff }, // sub:6:0xE240A001
	{  15, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  16, 0xe08c1020, 0xfdffffff }, // add:6:0xE28C1020
	{  17, 0xe591c01c, 0xfdffffff }, // ldr:4:0xE591C01C
	{  18, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  19, 0x01a0b001, 0xfdffffff }, // mov:6:0x01A0B001
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  21, 0xe05aa001, 0xfdffffff }, // sub:6:0xE25AA001
	{  22, 0xe0811020, 0xfdffffff }, // add:6:0xE2811020
	{  23, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF8
	{  24, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  25, 0xe040a00a, 0xfdffffff }, // sub:6:0xE040A00A
	{  26, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  27, 0xe59f008c, 0xfdffffff }, // ldr:4:0xE59F008C
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFEC92
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEBD
	{  31, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000B
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_Unmount_FileSystem_1[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe1a0600d, 0xfdffffff }, // mov:6:0xE1A0600D
	{   3, 0xe59f1044, 0xfdffffff }, // ldr:4:0xE59F1044
	{   4, 0xe1a02002, 0xfdffffff }, // mov:6:0xE3A02002
	{   5, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0967C9
	{   7, 0xe59fc038, 0xfdffffff }, // ldr:4:0xE59FC038
	{   8, 0xe59fe038, 0xfdffffff }, // ldr:4:0xE59FE038
	{   9, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{  10, 0xe59f4034, 0xfdffffff }, // ldr:4:0xE59F4034
	{  11, 0xe58e3000, 0xfdffffff }, // str:4:0xE58E3000
	{  12, 0xe0835041, 0xfdffffff }, // add:6:0xE2835041
	{  13, 0xe08c1054, 0xfdffffff }, // add:6:0xE28C1054
	{  15, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  16, 0xe5843000, 0xfdffffff }, // str:4:0xE5843000
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0006AD
	{  19, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  21, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 18/32 */
};

static FuncSig func_sig_Mount_FileSystem_1[] = {
	{   1, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000
	{   2, 0xe59f6064, 0xfdffffff }, // ldr:4:0xE59F6064
	{   3, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE88
	{   5, 0xe5960038, 0xfdffffff }, // ldr:4:0xE5960038
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC42
	{   7, 0xe0501000, 0xfdffffff }, // sub:6:0xE2501000
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   9, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005
	{  10, 0xe59f3048, 0xfdffffff }, // ldr:4:0xE59F3048
	{  11, 0xe59f2048, 0xfdffffff }, // ldr:4:0xE59F2048
	{  12, 0xe5831000, 0xfdffffff }, // str:4:0xE5831000
	{  13, 0xe59f3044, 0xfdffffff }, // ldr:4:0xE59F3044
	{  14, 0xe5821000, 0xfdffffff }, // str:4:0xE5821000
	{  15, 0xe5831000, 0xfdffffff }, // str:4:0xE5831000
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE90
	{  17, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF58
	{  19, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  20, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF77
	{  22, 0xe0044000, 0xfdffffff }, // and:6:0xE0044000
	{  23, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{  24, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  25, 0xe596103c, 0xfdffffff }, // ldr:4:0xE596103C
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFD0
	{  27, 0xe5860040, 0xfdffffff }, // str:4:0xE5860040
	{  29, 0x0002e008, 0xfdffffff }, // and:6:0x0002E008
	{  30, 0x00002830, 0xfdffffff }, // and:6:0x00002830
	{  31, 0x00002828, 0xfdffffff }, // and:6:0x00002828
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_UpdateMBROnFlash_1[] = {
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   2, 0xe1a09002, 0xfdffffff }, // mov:6:0xE1A09002
	{   3, 0xe1a07001, 0xfdffffff }, // mov:6:0xE1A07001
	{   4, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{   5, 0xe1a01c02, 0xfdffffff }, // mov:6:0xE3A01C02
	{   6, 0xe1a00003, 0xfdffffff }, // mov:6:0xE3A00003
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFE9AFB
	{   8, 0xe59f5074, 0xfdffffff }, // ldr:4:0xE59F5074
	{   9, 0xe0843084, 0xfdffffff }, // add:6:0xE0843084
	{  10, 0xe0644183, 0xfdffffff }, // rsb:6:0xE0644183
	{  11, 0xe1a04104, 0xfdffffff }, // mov:6:0xE1A04104
	{  12, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  13, 0xe0858038, 0xfdffffff }, // add:6:0xE2858038
	{  14, 0xe085a044, 0xfdffffff }, // add:6:0xE285A044
	{  15, 0xe085c04c, 0xfdffffff }, // add:6:0xE285C04C
	{  16, 0xe1a03006, 0xfdffffff }, // mov:6:0xE1A03006
	{  17, 0xe59a1004, 0xfdffffff }, // ldr:4:0xE79A1004
	{  18, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001
	{  19, 0xe5980004, 0xfdffffff }, // ldr:4:0xE7980004
	{  20, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  21, 0xe59cf004, 0xfdffffff }, // ldr:4:0xE79CF004
	{  22, 0xe1a00009, 0xfdffffff }, // mov:6:0xE1A00009
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB09685A
	{  24, 0xe0867007, 0xfdffffff }, // add:6:0xE0867007
	{  25, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{  26, 0xe1a01009, 0xfdffffff }, // mov:6:0xE1A01009
	{  27, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB09687F
	{  29, 0xe0855050, 0xfdffffff }, // add:6:0xE2855050
	{  30, 0xe5980004, 0xfdffffff }, // ldr:4:0xE7980004
	{  31, 0xe59a1004, 0xfdffffff }, // ldr:4:0xE79A1004
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_vsprintf_1[] = {
	{   0, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   1, 0xe1a0c002, 0xfdffffff }, // mov:6:0xE1A0C002
	{   3, 0xe58d0004, 0xfdffffff }, // str:4:0xE58D0004
	{   4, 0xe59f2ba8, 0xfdffffff }, // ldr:4:0xE59F2BA8
	{   5, 0xe1a00001, 0xfdffffff }, // mov:6:0xE1A00001
	{   6, 0xe08d3004, 0xfdffffff }, // add:6:0xE28D3004
	{   7, 0xe1a0100c, 0xfdffffff }, // mov:6:0xE1A0100C
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC68
	{   9, 0xe59dc004, 0xfdffffff }, // ldr:4:0xE59DC004
	{  10, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{  11, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{  14, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  15, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 13/32 */
};

static FuncSig func_sig_Close_1[] = {
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097DD0
	{   3, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   4, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00024D
	{   6, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   9, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  10, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097EC2
	{  12, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000282
	{  15, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{  16, 0xe1a0600d, 0xfdffffff }, // mov:6:0xE1A0600D
	{  17, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  18, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFB8
	{  21, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFCF
	{  23, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  25, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  26, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  28, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_Open_1[] = {
	{   1, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   2, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097F6A
	{   4, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{   5, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{   6, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00022B
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  11, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097DD0
	{  13, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  14, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00024D
	{  16, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  19, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  20, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097EC2
	{  22, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  23, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000282
	{  25, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{  26, 0xe1a0600d, 0xfdffffff }, // mov:6:0xE1A0600D
	{  27, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  28, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  29, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFB8
	{  31, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_Read_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA097DC3
	{   4, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097DDC
	{   6, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   7, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000216
	{   9, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  12, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  13, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097F32
	{  15, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{  16, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  17, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00027A
	{  19, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  21, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  22, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEA097DE7
	{  25, 0xe04dd048, 0xfdffffff }, // sub:6:0xE24DD048
	{  26, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{  27, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB096DAB
	{  29, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  31, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_Write_1[] = {
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097DDC
	{   3, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   4, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000216
	{   6, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   9, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  10, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097F32
	{  12, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{  13, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  14, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00027A
	{  16, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  18, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  19, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  20, 0xea000000, 0xff000000 }, // b, bl:3:0xEA097DE7
	{  22, 0xe04dd048, 0xfdffffff }, // sub:6:0xE24DD048
	{  23, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{  24, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB096DAB
	{  26, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  28, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008
	{  31, 0xe59dc014, 0xfdffffff }, // ldr:4:0xE59DC014
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_Remove_1[] = {
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097EC2
	{   4, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   5, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000282
	{   7, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{   8, 0xe1a0600d, 0xfdffffff }, // mov:6:0xE1A0600D
	{   9, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  10, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFB8
	{  13, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFCF
	{  15, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  17, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  18, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  20, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 18/32 */
};

static FuncSig func_sig_GetCurrentTargetDistance_1[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFCC4A
	{   2, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   3, 0xe1a00820, 0xfdffffff }, // mov:6:0xE1A00820
	{   4, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{   6, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   7, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{   8, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   9, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{  10, 0xe08d0002, 0xfdffffff }, // add:6:0xE28D0002
	{  11, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFCD7E
	{  19, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  21, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 14/32 */
};

static FuncSig func_sig_strpbrk_1[] = {
	{   0, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{   3, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000007
	{   5, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   7, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0AFFFFF8
	{   9, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE15A0000
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFA
	{  11, 0xe0420001, 0xfdffffff }, // sub:6:0xE2420001
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000000
	{  13, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  15, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  16, 0xe00110ff, 0xfdffffff }, // and:6:0xE20110FF
	{  18, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE15C0001
	{  19, 0x01a02000, 0xfdffffff }, // mov:6:0x01A02000
	{  21, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9
	{  23, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{  24, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 19/32 */
};

static FuncSig func_sig_AllocateUncacheableMemory_1[] = {
	{   1, 0xe0804040, 0xfdffffff }, // add:6:0xE2804040
	{   2, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF48C
	{   4, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{   5, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{   6, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{   8, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0ACADF
	{  11, 0xe0800020, 0xfdffffff }, // add:6:0xE2800020
	{  13, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  14, 0xe0400020, 0xfdffffff }, // sub:6:0xE2400020
	{  15, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  17, 0x049df004, 0xfdffffff }, // ldr:4:0x049DF004
	{  18, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  19, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFF47F
	{  22, 0x00000064, 0xfdffffff }, // and:6:0x00000064
	{  24, 0x00632e65, 0xfdffffff }, // rsb:6:0x00632E65
	{  26, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFE3
	{  28, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  29, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  30, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{  31, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{ -1, -1, -1 },
	/* 23/32 */
};

static FuncSig func_sig_FreeUncacheableMemory_1[] = {
	{   0, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   1, 0xe0400020, 0xfdffffff }, // sub:6:0xE2400020
	{   2, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   4, 0x049df004, 0xfdffffff }, // ldr:4:0x049DF004
	{   5, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   6, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFF47F
	{   9, 0x00000064, 0xfdffffff }, // and:6:0x00000064
	{  11, 0x00632e65, 0xfdffffff }, // rsb:6:0x00632E65
	{  13, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFE3
	{  15, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  16, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  17, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{  18, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0AD45E
	{  20, 0xe59f0010, 0xfdffffff }, // ldr:4:0xE59F0010
	{  21, 0xe1a01041, 0xfdffffff }, // mov:6:0xE3A01041
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC59
	{  23, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  29, 0x00007061, 0xfdffffff }, // and:6:0x00007061
	{  31, 0xe0505000, 0xfdffffff }, // sub:6:0xE2505000
	{ -1, -1, -1 },
	/* 21/32 */
};

static FuncSig func_sig_LockMainPower_1[] = {
	{   1, 0xe59f3088, 0xfdffffff }, // ldr:4:0xE59F3088
	{   2, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   3, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   4, 0xe59f6080, 0xfdffffff }, // ldr:4:0xE59F6080
	{   5, 0xe59f5080, 0xfdffffff }, // ldr:4:0xE59F5080
	{   6, 0xe1a04000, 0xfdffffff }, // mov:6:0xE3A04000
	{   7, 0xe59f007c, 0xfdffffff }, // ldr:4:0xE59F007C
	{   8, 0xe1a010b1, 0xfdffffff }, // mov:6:0xE3A010B1
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFAEAF0
	{  11, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  12, 0xe5960000, 0xfdffffff }, // ldr:4:0xE5960000
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFB24D9
	{  14, 0xe59f2064, 0xfdffffff }, // ldr:4:0xE59F2064
	{  15, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{  16, 0xe0833001, 0xfdffffff }, // add:6:0xE2833001
	{  17, 0xe1530001, 0xfdffffff }, // cmp:7:0xE3530001
	{  18, 0xe59f1058, 0xfdffffff }, // ldr:4:0xE59F1058
	{  19, 0xe5823000, 0xfdffffff }, // str:4:0xE5823000
	{  20, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001
	{  21, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  22, 0xe591f000, 0xfdffffff }, // ldr:4:0xE591F000
	{  23, 0xe59fc048, 0xfdffffff }, // ldr:4:0xE59FC048
	{  24, 0xe59c3000, 0xfdffffff }, // ldr:4:0xE59C3000
	{  25, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001
	{  26, 0xe59f1040, 0xfdffffff }, // ldr:4:0xE59F1040
	{  27, 0xe1530002, 0xfdffffff }, // cmp:7:0xE1530002
	{  28, 0xe5812000, 0xfdffffff }, // str:4:0xE5812000
	{  29, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  30, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  31, 0xe58c4000, 0xfdffffff }, // str:4:0xE58C4000
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_UnlockMainPower_1[] = {
	{   1, 0xe59f30d0, 0xfdffffff }, // ldr:4:0xE59F30D0
	{   2, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   3, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   4, 0xe59f50c8, 0xfdffffff }, // ldr:4:0xE59F50C8
	{   5, 0xe59f40c8, 0xfdffffff }, // ldr:4:0xE59F40C8
	{   6, 0xe59f00c8, 0xfdffffff }, // ldr:4:0xE59F00C8
	{   7, 0xe1a010c5, 0xfdffffff }, // mov:6:0xE3A010C5
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFAEAC4
	{  10, 0xe5943000, 0xfdffffff }, // ldr:4:0xE5943000
	{  11, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  12, 0xe1530001, 0xfdffffff }, // cmp:7:0xE1530001
	{  14, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFB24AA
	{  16, 0xe5943000, 0xfdffffff }, // ldr:4:0xE5943000
	{  17, 0xe0432001, 0xfdffffff }, // sub:6:0xE2432001
	{  18, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  19, 0xe59f1098, 0xfdffffff }, // ldr:4:0xE59F1098
	{  20, 0xe5842000, 0xfdffffff }, // str:4:0xE5842000
	{  21, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  22, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  24, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFB24CB
	{  25, 0xe59f3084, 0xfdffffff }, // ldr:4:0xE59F3084
	{  26, 0xe5832000, 0xfdffffff }, // str:4:0xE5832000
	{  27, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  28, 0xe591f000, 0xfdffffff }, // ldr:4:0xE591F000
	{  29, 0xe59f3078, 0xfdffffff }, // ldr:4:0xE59F3078
	{  30, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{  31, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_MoveZoomLensWithPoint_1[] = {
	{   1, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{   3, 0xe08d0004, 0xfdffffff }, // add:6:0xE28D0004
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF6C6EF
	{   5, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   6, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{   7, 0xe59f1050, 0xfdffffff }, // ldr:4:0xE59F1050
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFB74
	{   9, 0xe59f304c, 0xfdffffff }, // ldr:4:0xE59F304C
	{  10, 0xe1a01c27, 0xfdffffff }, // mov:6:0xE3A01C27
	{  11, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  12, 0xe0811010, 0xfdffffff }, // add:6:0xE2811010
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF6F73A
	{  14, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  15, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000D
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF6C6E3
	{  17, 0xe1140001, 0xfdffffff }, // tst:7:0xE3140001
	{  18, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF91F
	{  21, 0xe1a00a20, 0xfdffffff }, // mov:6:0xE1A00A20
	{  22, 0xe1a00a00, 0xfdffffff }, // mov:6:0xE1A00A00
	{  23, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  24, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  26, 0xe08dd008, 0xfdffffff }, // add:6:0xE28DD008
	{  28, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_MoveFocusLensToDistance_1[] = {
	{   1, 0xe59f5030, 0xfdffffff }, // ldr:4:0xE59F5030
	{   2, 0xe5904000, 0xfdffffff }, // ldr:4:0xE5904000
	{   3, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   4, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF6703E
	{   6, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   7, 0xe59f101c, 0xfdffffff }, // ldr:4:0xE59F101C
	{   8, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000006
	{  10, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  11, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  12, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF66FC6
	{  15, 0x0000b22c, 0xfdffffff }, // and:6:0x0000B22C
	{  18, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{  19, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{  20, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFCAB3
	{  22, 0xe1a01800, 0xfdffffff }, // mov:6:0xE1A01800
	{  23, 0xe1a01821, 0xfdffffff }, // mov:6:0xE1A01821
	{  24, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  25, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  26, 0xe1a03006, 0xfdffffff }, // mov:6:0xE1A03006
	{  28, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFFF
	{  30, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_Fclose_Fut_1[] = {
	{   1, 0xe0506000, 0xfdffffff }, // sub:6:0xE2506000
	{   2, 0xe04dd054, 0xfdffffff }, // sub:6:0xE24DD054
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000030
	{   5, 0xe0864020, 0xfdffffff }, // add:6:0xE2864020
	{   6, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB098097
	{   8, 0xe1500020, 0xfdffffff }, // cmp:7:0xE3500020
	{   9, 0xd08d5030, 0xfdffffff }, // add:6:0xD28D5030
	{  10, 0xd1a08005, 0xfdffffff }, // mov:6:0xD1A08005
	{  11, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000003
	{  12, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFEAFDD
	{  14, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  15, 0xe08d8030, 0xfdffffff }, // add:6:0xE28D8030
	{  16, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  17, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB098033
	{  19, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  20, 0xe5964008, 0xfdffffff }, // ldr:4:0xE5964008
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCC7
	{  22, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{  23, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000EEA
	{  25, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001239
	{  27, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000
	{  28, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  29, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000D
	{  30, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000EE3
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_Fopen_Fut_1[] = {
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   2, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCE8
	{   4, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   5, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000F0B
	{   7, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{   8, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001220
	{  10, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  11, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCEA
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  16, 0xe0506000, 0xfdffffff }, // sub:6:0xE2506000
	{  17, 0xe04dd054, 0xfdffffff }, // sub:6:0xE24DD054
	{  19, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000030
	{  20, 0xe0864020, 0xfdffffff }, // add:6:0xE2864020
	{  21, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB098097
	{  23, 0xe1500020, 0xfdffffff }, // cmp:7:0xE3500020
	{  24, 0xd08d5030, 0xfdffffff }, // add:6:0xD28D5030
	{  25, 0xd1a08005, 0xfdffffff }, // mov:6:0xD1A08005
	{  26, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000003
	{  27, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFEAFDD
	{  29, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  30, 0xe08d8030, 0xfdffffff }, // add:6:0xE28D8030
	{  31, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{ -1, -1, -1 },
	/* 28/32 */
};

static FuncSig func_sig_Fread_Fut_1[] = {
	{   1, 0xe0537000, 0xfdffffff }, // sub:6:0xE2537000
	{   2, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   3, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   4, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{   5, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC9B
	{   9, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  10, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  11, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  12, 0xe1a03007, 0xfdffffff }, // mov:6:0xE1A03007
	{  13, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001228
	{  15, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  16, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC9D
	{  18, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  21, 0xe0537000, 0xfdffffff }, // sub:6:0xE2537000
	{  22, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  23, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{  24, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{  25, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC87
	{  29, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  30, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  31, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_Fseek_Fut_1[] = {
	{   1, 0xe0507000, 0xfdffffff }, // sub:6:0xE2507000
	{   2, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{   3, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   4, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC62
	{   8, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{   9, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  10, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  11, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0012C8
	{  13, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  14, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC65
	{  16, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  19, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  20, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC52
	{  24, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  25, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0012CE
	{  27, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  28, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC57
	{  30, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_Fwrite_Fut_1[] = {
	{   1, 0xe0537000, 0xfdffffff }, // sub:6:0xE2537000
	{   2, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   3, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   4, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{   5, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC87
	{   9, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  10, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  11, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  12, 0xe1a03007, 0xfdffffff }, // mov:6:0xE1A03007
	{  13, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001264
	{  15, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  16, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC89
	{  18, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  21, 0xe0524000, 0xfdffffff }, // sub:6:0xE2524000
	{  22, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  23, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{  24, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020
	{  25, 0x01a00004, 0xfdffffff }, // mov:6:0x01A00004
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC74
	{  28, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{  29, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{  30, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  31, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_SetAutoShutdownTime_1[] = {
	{   1, 0xe59f30d4, 0xfdffffff }, // ldr:4:0xE59F30D4
	{   2, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   3, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   4, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   5, 0xe59f80c8, 0xfdffffff }, // ldr:4:0xE59F80C8
	{   6, 0xe59f70c8, 0xfdffffff }, // ldr:4:0xE59F70C8
	{   7, 0xe59fa0c8, 0xfdffffff }, // ldr:4:0xE59FA0C8
	{   8, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000
	{   9, 0xe59f60c4, 0xfdffffff }, // ldr:4:0xE59F60C4
	{  10, 0xe1a01098, 0xfdffffff }, // mov:6:0xE3A01098
	{  11, 0xe59f00c0, 0xfdffffff }, // ldr:4:0xE59F00C0
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFAEB2F
	{  14, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  15, 0xe5980000, 0xfdffffff }, // ldr:4:0xE5980000
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFB2518
	{  17, 0xe5972000, 0xfdffffff }, // ldr:4:0xE5972000
	{  18, 0xe0643284, 0xfdffffff }, // rsb:6:0xE0643284
	{  19, 0xe0843103, 0xfdffffff }, // add:6:0xE0843103
	{  20, 0xe1a03183, 0xfdffffff }, // mov:6:0xE1A03183
	{  21, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{  22, 0xe5863000, 0xfdffffff }, // str:4:0xE5863000
	{  23, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  24, 0xe59a0000, 0xfdffffff }, // ldr:4:0xE59A0000
	{  25, 0xe5875000, 0xfdffffff }, // str:4:0xE5875000
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE315
	{  27, 0xe58a5000, 0xfdffffff }, // str:4:0xE58A5000
	{  28, 0xe5965000, 0xfdffffff }, // ldr:4:0xE5965000
	{  29, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{  30, 0xe1a06001, 0xfdffffff }, // mov:6:0xE3A06001
	{  31, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_PutInNdFilter_1[] = {
	{   1, 0xe59f4028, 0xfdffffff }, // ldr:4:0xE59F4028
	{   2, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   3, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF678C5
	{   5, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{   6, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000006
	{   8, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{   9, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  10, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF6784E
	{  13, 0x0000b0bc, 0xfdffffff }, // and:6:0x0000B0BC
	{  15, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  16, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFBA05
	{  19, 0xe59f4028, 0xfdffffff }, // ldr:4:0xE59F4028
	{  20, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  21, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF678B3
	{  23, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{  24, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000006
	{  26, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{  27, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  28, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  30, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF6783C
	{  31, 0x0000b0bc, 0xfdffffff }, // and:6:0x0000B0BC
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_PutOutNdFilter_1[] = {
	{   1, 0xe59f4028, 0xfdffffff }, // ldr:4:0xE59F4028
	{   2, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   3, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF678B3
	{   5, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{   6, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000006
	{   8, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{   9, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  10, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF6783C
	{  13, 0x0000b0bc, 0xfdffffff }, // and:6:0x0000B0BC
	{  15, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  16, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFB9FA
	{  24, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  28, 0x00000072, 0xfdffffff }, // and:6:0x00000072
	{ -1, -1, -1 },
	/* 17/32 */
};

static FuncSig func_sig_UnsetZoomForMovie_1[] = {
	{   1, 0xe1a00060, 0xfdffffff }, // mov:6:0xE3A00060
	{   2, 0xe1a04000, 0xfdffffff }, // mov:6:0xE3A04000
	{   3, 0xe59f1034, 0xfdffffff }, // ldr:4:0xE59F1034
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA1830
	{   5, 0xe59f2030, 0xfdffffff }, // ldr:4:0xE59F2030
	{   6, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{   7, 0xe1530004, 0xfdffffff }, // cmp:7:0xE1530004
	{   9, 0xe5824000, 0xfdffffff }, // str:4:0xE5824000
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00002F
	{  11, 0xe59f201c, 0xfdffffff }, // ldr:4:0xE59F201C
	{  12, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{  13, 0xe1530004, 0xfdffffff }, // cmp:7:0xE1530004
	{  15, 0xe5824000, 0xfdffffff }, // str:4:0xE5824000
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFCD1
	{  19, 0x00007ff8, 0xfdffffff }, // and:6:0x00007FF8
	{  20, 0x00007ff4, 0xfdffffff }, // and:6:0x00007FF4
	{  21, 0xe59f3004, 0xfdffffff }, // ldr:4:0xE59F3004
	{  22, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  23, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 19/32 */
};

static FuncSig func_sig_Fgets_Fut_1[] = {
	{   1, 0xe0524000, 0xfdffffff }, // sub:6:0xE2524000
	{   2, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   3, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   4, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020
	{   5, 0x01a00004, 0xfdffffff }, // mov:6:0x01A00004
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC74
	{   8, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{   9, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{  10, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  11, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001291
	{  13, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  14, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC77
	{  16, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{ -1, -1, -1 },
	/* 15/18 */
};

static FuncSig func_sig_Feof_Fut_1[] = {
	{   1, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{   2, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC52
	{   6, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   7, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0012CE
	{   9, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  10, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC57
	{  12, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{ -1, -1, -1 },
	/* 10/14 */
};

static FuncSig func_sig_Fflush_Fut_1[] = {
	{   1, 0xe0505000, 0xfdffffff }, // sub:6:0xE2505000
	{   2, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018
	{   3, 0xe0854020, 0xfdffffff }, // add:6:0xE2854020
	{   4, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000014
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC42
	{   8, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   9, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0012C4
	{  11, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  12, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000E62
	{  14, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  15, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000CA7
	{  17, 0xe59d3004, 0xfdffffff }, // ldr:4:0xE59D3004
	{  18, 0xe1130010, 0xfdffffff }, // tst:7:0xE3130010
	{  20, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  21, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000002
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000D9A
	{  23, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000E26
	{  25, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC3A
	{  27, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  28, 0xe08dd018, 0xfdffffff }, // add:6:0xE28DD018
	{  30, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_strftime_1[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe59fc018, 0xfdffffff }, // ldr:4:0xE59FC018
	{   3, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   4, 0xe58dc000, 0xfdffffff }, // str:4:0xE58DC000
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFAA
	{   6, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{ -1, -1, -1 },
	/* 6/8 */
};

static FuncSig func_sig_mktime_1[] = {
	{   1, 0xe04dd01c, 0xfdffffff }, // sub:6:0xE24DD01C
	{   2, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFB0
	{   4, 0xe59b9000, 0xfdffffff }, // ldr:4:0xE59B9000
	{   5, 0xe59bc004, 0xfdffffff }, // ldr:4:0xE59BC004
	{   6, 0xe1a0303c, 0xfdffffff }, // mov:6:0xE3A0303C
	{   7, 0xe59b0014, 0xfdffffff }, // ldr:4:0xE59B0014
	{   8, 0xe59b1010, 0xfdffffff }, // ldr:4:0xE59B1010
	{   9, 0xe59b200c, 0xfdffffff }, // ldr:4:0xE59B200C
	{  11, 0xe59bc008, 0xfdffffff }, // ldr:4:0xE59BC008
	{  12, 0xe1a03ee1, 0xfdffffff }, // mov:6:0xE3A03EE1
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEDA
	{  15, 0xe0401001, 0xfdffffff }, // sub:6:0xE2401001
	{  16, 0xe59ba014, 0xfdffffff }, // ldr:4:0xE59BA014
	{  17, 0xe58b101c, 0xfdffffff }, // str:4:0xE58B101C
	{  18, 0xe59fc094, 0xfdffffff }, // ldr:4:0xE59FC094
	{  19, 0xe59f3094, 0xfdffffff }, // ldr:4:0xE59F3094
	{  20, 0xe08ac00c, 0xfdffffff }, // add:6:0xE08AC00C
	{  21, 0xe15c0003, 0xfdffffff }, // cmp:7:0xE15C0003
	{  23, 0xba000000, 0xff000000 }, // b, bl:3:0xBA00001D
	{  24, 0xe04a0046, 0xfdffffff }, // sub:6:0xE24A0046
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEC2
	{  26, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  27, 0xe0800004, 0xfdffffff }, // add:6:0xE2800004
	{  28, 0xe1a01007, 0xfdffffff }, // mov:6:0xE3A01007
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB006FD7
	{  30, 0xe58b0018, 0xfdffffff }, // str:4:0xE58B0018
	{  31, 0xe59f3068, 0xfdffffff }, // ldr:4:0xE59F3068
	{ -1, -1, -1 },
	/* 28/32 */
};

static FuncSig func_sig_RenameFile_Fut_1[] = {
	{   1, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   2, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD49
	{   4, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   5, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD4D
	{   7, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEE2
	{  10, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  11, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD4B
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  16, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{  17, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD3A
	{  19, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  20, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  21, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000DA4
	{  23, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  24, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD3E
	{  26, 0xe0144001, 0xfdffffff }, // and:6:0xE2144001
	{  27, 0xe1a00342, 0xfdffffff }, // mov:6:0xE3A00342
	{  28, 0xe0800505, 0xfdffffff }, // add:6:0xE2800505
	{  30, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_DeleteFile_Fut_1[] = {
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD2A
	{   3, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   4, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   5, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEEE
	{   7, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD2E
	{  10, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{ -1, -1, -1 },
	/* 10/12 */
};

static FuncSig func_sig_MakeDirectory_Fut_1[] = {
	{   1, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   2, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD06
	{   4, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   5, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD0A
	{   7, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEE6
	{  10, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  11, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFD08
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  16, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCF8
	{  18, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  19, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEFF
	{  21, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  22, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCFD
	{  24, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  26, 0xe59f3004, 0xfdffffff }, // ldr:4:0xE59F3004
	{  27, 0xe5930100, 0xfdffffff }, // ldr:4:0xE7930100
	{  28, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_errnoOfTaskGet_1[] = {
	{   1, 0xe1b0b000, 0xfdffffff }, // mov:6:0xE1B0B000
	{   2, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0056EB
	{   4, 0xe150000b, 0xfdffffff }, // cmp:7:0xE150000B
	{   5, 0x059f0070, 0xfdffffff }, // ldr:4:0x059F0070
	{   6, 0x05900000, 0xfdffffff }, // ldr:4:0x05900000
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{   8, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB005702
	{  10, 0xe1b0b000, 0xfdffffff }, // mov:6:0xE1B0B000
	{  12, 0x159b0084, 0xfdffffff }, // ldr:4:0x159B0084
	{  14, 0xe59fc04c, 0xfdffffff }, // ldr:4:0xE59FC04C
	{  15, 0xe58c0000, 0xfdffffff }, // str:4:0xE58C0000
	{  16, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  17, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 15/32 */
};

static FuncSig func_sig_iosDevFind_1[] = {
	{   1, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{   2, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFE2
	{   4, 0xe1b0b000, 0xfdffffff }, // mov:6:0xE1B0B000
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   6, 0xe590000c, 0xfdffffff }, // ldr:4:0xE590000C
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE370
	{   8, 0xe08aa000, 0xfdffffff }, // add:6:0xE08AA000
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000002
	{  10, 0xe59f03e4, 0xfdffffff }, // ldr:4:0xE59F03E4
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFDA
	{  12, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  13, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  14, 0xe589a000, 0xfdffffff }, // str:4:0xE589A000
	{  15, 0x059f03d4, 0xfdffffff }, // ldr:4:0x059F03D4
	{  16, 0x0b000000, 0xff000000 }, // b, bl:3:0x0BFFED6C
	{  17, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  20, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF90
	{  22, 0xe59f038c, 0xfdffffff }, // ldr:4:0xE59F038C
	{  23, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB005358
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF8F
	{  26, 0xe59b000c, 0xfdffffff }, // ldr:4:0xE59B000C
	{  28, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00078A
	{  30, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  31, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_TurnOnBackLight_1[] = {
	{   0, 0xe59f000c, 0xfdffffff }, // ldr:4:0xE59F000C
	{   1, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF9CD1C
	{   3, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   4, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDFD0D
	{   7, 0x4066664f, 0xfdffffff }, // rsb:6:0x4266664F
	{  10, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  11, 0xe59f000c, 0xfdffffff }, // ldr:4:0xE59F000C
	{  12, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF9CD11
	{  14, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  15, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDFD3B
	{  20, 0x61536c61, 0xfdffffff }, // cmp:7:0x63536C61
	{  22, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  23, 0xe59f000c, 0xfdffffff }, // ldr:4:0xE59F000C
	{  24, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF9CD05
	{  26, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  27, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDF05F
	{  30, 0x5066664f, 0xfdffffff }, // rsb:6:0x5066664F
	{ -1, -1, -1 },
	/* 20/32 */
};

static FuncSig func_sig_TurnOffBackLight_1[] = {
	{   0, 0xe59f000c, 0xfdffffff }, // ldr:4:0xE59F000C
	{   1, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF9CD11
	{   3, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   4, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDFD3B
	{   9, 0x61536c61, 0xfdffffff }, // cmp:7:0x63536C61
	{  11, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  12, 0xe59f000c, 0xfdffffff }, // ldr:4:0xE59F000C
	{  13, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF9CD05
	{  15, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  16, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDF05F
	{  19, 0x5066664f, 0xfdffffff }, // rsb:6:0x5066664F
	{  23, 0x0000006e, 0xfdffffff }, // and:6:0x0000006E
	{  24, 0xe59f000c, 0xfdffffff }, // ldr:4:0xE59F000C
	{  25, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF9CCF9
	{  27, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  28, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDF067
	{ -1, -1, -1 },
	/* 19/32 */
};

static FuncSig func_sig_GetSystemTime_2[] = {
	{   1, 0xe59f6030, 0xfdffffff }, // ldr:4:0xE59F6030
	{   2, 0xe5965000, 0xfdffffff }, // ldr:4:0xE5965000
	{   3, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{   4, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   5, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017
	{   6, 0x11a03000, 0xfdffffff }, // mov:6:0x13A03000
	{   7, 0x15843000, 0xfdffffff }, // str:4:0x15843000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002E01
	{  10, 0xe5963008, 0xfdffffff }, // ldr:4:0xE5963008
	{  11, 0xe5843000, 0xfdffffff }, // str:4:0xE5843000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002E01
	{  13, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  15, 0x00001d14, 0xfdffffff }, // and:6:0x00001D14
	{  17, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  18, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002
	{  19, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{  20, 0xe1a08003, 0xfdffffff }, // mov:6:0xE1A08003
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002DF5
	{  22, 0xe085e014, 0xfdffffff }, // add:6:0xE285E014
	{  23, 0xe59e2004, 0xfdffffff }, // ldr:4:0xE59E2004
	{  24, 0xe085c014, 0xfdffffff }, // add:6:0xE285C014
	{  25, 0xe152000c, 0xfdffffff }, // cmp:7:0xE152000C
	{  26, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  27, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000002
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002DF1
	{  29, 0xe1a00005, 0xfdffffff }, // mov:6:0xE3A00005
	{  31, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_GetPropertyCase_2[] = {
	{   1, 0xe59f3064, 0xfdffffff }, // ldr:4:0xE59F3064
	{   2, 0xe593c000, 0xfdffffff }, // ldr:4:0xE593C000
	{   3, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{   4, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   5, 0xe1a01e13, 0xfdffffff }, // mov:6:0xE3A01E13
	{   6, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{   7, 0xe59f5050, 0xfdffffff }, // ldr:4:0xE59F5050
	{   8, 0xe59f0050, 0xfdffffff }, // ldr:4:0xE59F0050
	{   9, 0xe0811001, 0xfdffffff }, // add:6:0xE2811001
	{  10, 0xe1a04002, 0xfdffffff }, // mov:6:0xE1A04002
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFBBB5
	{  13, 0xe5953000, 0xfdffffff }, // ldr:4:0xE5953000
	{  14, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  15, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF1A6
	{  17, 0xe1a03004, 0xfdffffff }, // mov:6:0xE1A03004
	{  18, 0xe1a01007, 0xfdffffff }, // mov:6:0xE1A01007
	{  19, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  20, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFB8
	{  22, 0xe5953000, 0xfdffffff }, // ldr:4:0xE5953000
	{  23, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  24, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF217
	{  26, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  28, 0x00001f28, 0xfdffffff }, // and:6:0x00001F28
	{  29, 0x00001f30, 0xfdffffff }, // and:6:0x00001F30
	{ -1, -1, -1 },
	/* 28/32 */
};

static FuncSig func_sig_SetPropertyCase_2[] = {
	{   1, 0xe59f3074, 0xfdffffff }, // ldr:4:0xE59F3074
	{   2, 0xe593c000, 0xfdffffff }, // ldr:4:0xE593C000
	{   3, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   4, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   5, 0xe1a01f41, 0xfdffffff }, // mov:6:0xE3A01F41
	{   6, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   7, 0xe59f7060, 0xfdffffff }, // ldr:4:0xE59F7060
	{   8, 0xe59f0060, 0xfdffffff }, // ldr:4:0xE59F0060
	{   9, 0xe0811001, 0xfdffffff }, // add:6:0xE2811001
	{  10, 0xe1a04002, 0xfdffffff }, // mov:6:0xE1A04002
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFBC09
	{  13, 0xe5973000, 0xfdffffff }, // ldr:4:0xE5973000
	{  14, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  15, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF1FA
	{  17, 0xe1a01006, 0xfdffffff }, // mov:6:0xE1A01006
	{  18, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  19, 0xe1a03004, 0xfdffffff }, // mov:6:0xE1A03004
	{  20, 0xe5970000, 0xfdffffff }, // ldr:4:0xE5970000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF7A
	{  22, 0xe1a01f42, 0xfdffffff }, // mov:6:0xE3A01F42
	{  23, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  24, 0xe0811002, 0xfdffffff }, // add:6:0xE2811002
	{  25, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{  26, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFBBFA
	{  28, 0xe5973000, 0xfdffffff }, // ldr:4:0xE5973000
	{  29, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  31, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFF265
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_RefreshPhysicalScreen_2[] = {
	{   1, 0xe04dd010, 0xfdffffff }, // sub:6:0xE24DD010
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0002AB
	{   3, 0xe0105001, 0xfdffffff }, // and:6:0xE2105001
	{   4, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000023
	{   5, 0xe59f3094, 0xfdffffff }, // ldr:4:0xE59F3094
	{   6, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   7, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   8, 0xe59f108c, 0xfdffffff }, // ldr:4:0xE59F108C
	{   9, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  11, 0xe59f3084, 0xfdffffff }, // ldr:4:0xE59F3084
	{  12, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA2853
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000019
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA021B
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF499
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF136
	{  18, 0xe59f406c, 0xfdffffff }, // ldr:4:0xE59F406C
	{  19, 0xe59fe06c, 0xfdffffff }, // ldr:4:0xE59FE06C
	{  20, 0xe59f306c, 0xfdffffff }, // ldr:4:0xE59F306C
	{  21, 0xe59fc06c, 0xfdffffff }, // ldr:4:0xE59FC06C
	{  22, 0xe5931000, 0xfdffffff }, // ldr:4:0xE5931000
	{  23, 0xe59e2000, 0xfdffffff }, // ldr:4:0xE59E2000
	{  24, 0xe59c3000, 0xfdffffff }, // ldr:4:0xE59C3000
	{  25, 0xe594c000, 0xfdffffff }, // ldr:4:0xE594C000
	{  26, 0xe58d2008, 0xfdffffff }, // str:4:0xE58D2008
	{  27, 0xe58dc00c, 0xfdffffff }, // str:4:0xE58DC00C
	{  28, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  29, 0xe58d5000, 0xfdffffff }, // str:4:0xE58D5000
	{  30, 0xe58d5004, 0xfdffffff }, // str:4:0xE58D5004
	{  31, 0xe59fc048, 0xfdffffff }, // ldr:4:0xE59FC048
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_DisplayImagePhysicalScreen_2[] = {
	{   1, 0xe59f2198, 0xfdffffff }, // ldr:4:0xE59F2198
	{   2, 0xe1a04001, 0xfdffffff }, // mov:6:0xE3A04001
	{   3, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   4, 0xe04dd010, 0xfdffffff }, // sub:6:0xE24DD010
	{   5, 0xe1a08004, 0xfdffffff }, // mov:6:0xE1A08004
	{   6, 0xe1560002, 0xfdffffff }, // cmp:7:0xE1560002
	{   7, 0xe1a05003, 0xfdffffff }, // mov:6:0xE1A05003
	{   8, 0xe59d7034, 0xfdffffff }, // ldr:4:0xE59D7034
	{   9, 0xe1a09004, 0xfdffffff }, // mov:6:0xE1A09004
	{  10, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE3A0B000
	{  11, 0xe1a0a008, 0xfdffffff }, // mov:6:0xE1A0A008
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000D
	{  13, 0x8a000000, 0xff000000 }, // b, bl:3:0x8A000005
	{  14, 0xe1a03541, 0xfdffffff }, // mov:6:0xE3A03541
	{  15, 0xe083380b, 0xfdffffff }, // add:6:0xE283380B
	{  16, 0xe0833e72, 0xfdffffff }, // add:6:0xE2833E72
	{  17, 0xe1560003, 0xfdffffff }, // cmp:7:0xE1560003
	{  18, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  19, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000D
	{  20, 0xe59f3150, 0xfdffffff }, // ldr:4:0xE59F3150
	{  21, 0xe1560003, 0xfdffffff }, // cmp:7:0xE1560003
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009
	{  24, 0xe59f3144, 0xfdffffff }, // ldr:4:0xE59F3144
	{  25, 0xe583b000, 0xfdffffff }, // str:4:0xE583B000
	{  26, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009
	{  27, 0xe59f3138, 0xfdffffff }, // ldr:4:0xE59F3138
	{  28, 0xe5838000, 0xfdffffff }, // str:4:0xE5838000
	{  29, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000006
	{  30, 0xe59f212c, 0xfdffffff }, // ldr:4:0xE59F212C
	{  31, 0xe1a03002, 0xfdffffff }, // mov:6:0xE3A03002
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_VbattGet_2[] = {
	{   0, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002
	{   1, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF5F5
	{   3, 0xe59f3014, 0xfdffffff }, // ldr:4:0xE59F3014
	{   5, 0xe0620000, 0xfdffffff }, // rsb:6:0xE0620000
	{   6, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   7, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{   8, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFEE3
	{  10, 0x0000e8e0, 0xfdffffff }, // and:6:0x0000E8E0
	{  11, 0x706d6554, 0xfdffffff }, // rsb:6:0x706D6554
	{  13, 0x0000006b, 0xfdffffff }, // and:6:0x0000006B
	{  15, 0xe59f2124, 0xfdffffff }, // ldr:4:0xE59F2124
	{  16, 0xe04dd010, 0xfdffffff }, // sub:6:0xE24DD010
	{  17, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{  18, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  19, 0xe59f7118, 0xfdffffff }, // ldr:4:0xE59F7118
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000041
	{  21, 0xe5975000, 0xfdffffff }, // ldr:4:0xE5975000
	{  22, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{  23, 0xe59f610c, 0xfdffffff }, // ldr:4:0xE59F610C
	{  24, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00003D
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF3FA
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF445
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF41E
	{  28, 0xe1a00005, 0xfdffffff }, // mov:6:0xE3A00005
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF5DA
	{  30, 0xe59f30f4, 0xfdffffff }, // ldr:4:0xE59F30F4
	{  31, 0xe08d4004, 0xfdffffff }, // add:6:0xE28D4004
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_GetZoomLensCurrentPosition_2[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE4B
	{   2, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   3, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{   4, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{   5, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC27
	{   7, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   8, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{   9, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  10, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  11, 0xe59f3008, 0xfdffffff }, // ldr:4:0xE59F3008
	{  12, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  13, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF607FC
	{  15, 0x0007c954, 0xfdffffff }, // and:6:0x0007C954
	{  17, 0xe59f4018, 0xfdffffff }, // ldr:4:0xE59F4018
	{  18, 0xe5943000, 0xfdffffff }, // ldr:4:0xE5943000
	{  19, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000FB
	{  22, 0xe1a03001, 0xfdffffff }, // mov:6:0xE3A03001
	{  23, 0xe5843000, 0xfdffffff }, // str:4:0xE5843000
	{  25, 0x00009ad4, 0xfdffffff }, // and:6:0x00009AD4
	{  26, 0xe59f2010, 0xfdffffff }, // ldr:4:0xE59F2010
	{  27, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{  28, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  29, 0x11a03000, 0xfdffffff }, // mov:6:0x13A03000
	{  30, 0x15823000, 0xfdffffff }, // str:4:0x15823000
	{  31, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_GetZoomLensCurrentPoint_2[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC6F
	{   2, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   3, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{   4, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{   5, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE4B
	{   7, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   8, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{   9, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  10, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC27
	{  12, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{  13, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{  14, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  15, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  16, 0xe59f3008, 0xfdffffff }, // ldr:4:0xE59F3008
	{  17, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  18, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  19, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF607FC
	{  20, 0x0007c954, 0xfdffffff }, // and:6:0x0007C954
	{  22, 0xe59f4018, 0xfdffffff }, // ldr:4:0xE59F4018
	{  23, 0xe5943000, 0xfdffffff }, // ldr:4:0xE5943000
	{  24, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0000FB
	{  27, 0xe1a03001, 0xfdffffff }, // mov:6:0xE3A03001
	{  28, 0xe5843000, 0xfdffffff }, // str:4:0xE5843000
	{  30, 0x00009ad4, 0xfdffffff }, // and:6:0x00009AD4
	{  31, 0xe59f2010, 0xfdffffff }, // ldr:4:0xE59F2010
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_GetFocusLensSubjectDistance_2[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe59f3034, 0xfdffffff }, // ldr:4:0xE59F3034
	{   2, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   3, 0xe1a01d06, 0xfdffffff }, // mov:6:0xE3A01D06
	{   4, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   5, 0xe59f0028, 0xfdffffff }, // ldr:4:0xE59F0028
	{   6, 0xe0811003, 0xfdffffff }, // add:6:0xE2811003
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF58365
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF1C0
	{  10, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{  11, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00004D
	{  13, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{  14, 0xe1a00820, 0xfdffffff }, // mov:6:0xE1A00820
	{  15, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  16, 0x00009ba4, 0xfdffffff }, // and:6:0x00009BA4
	{  18, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  19, 0xe59f3054, 0xfdffffff }, // ldr:4:0xE59F3054
	{  20, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{  21, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{  22, 0xe1a01e19, 0xfdffffff }, // mov:6:0xE3A01E19
	{  23, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  24, 0xe59f0044, 0xfdffffff }, // ldr:4:0xE59F0044
	{  25, 0xe0811001, 0xfdffffff }, // add:6:0xE2811001
	{  26, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF58352
	{  28, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  29, 0xe08d0002, 0xfdffffff }, // add:6:0xE28D0002
	{  30, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFAEAC
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_malloc_2[] = {
	{   0, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{   1, 0xe59f0070, 0xfdffffff }, // ldr:4:0xE59F0070
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFDF
	{   3, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{   4, 0xe59f0064, 0xfdffffff }, // ldr:4:0xE59F0064
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFE1E
	{   6, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   7, 0xe080000c, 0xfdffffff }, // add:6:0xE280000C
	{   8, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA002C61
	{  10, 0x00110004, 0xfdffffff }, // and:6:0x00110004
	{  11, 0x0000c12c, 0xfdffffff }, // and:6:0x0000C12C
	{  12, 0x00580001, 0xfdffffff }, // sub:6:0x00580001
	{  13, 0x0009f594, 0xfdffffff }, // and:6:0x0009F594 mul:11:0x0009F594
	{  14, 0x0000c114, 0xfdffffff }, // and:6:0x0000C114
	{  16, 0x00110002, 0xfdffffff }, // and:6:0x00110002
	{  17, 0x0000bf64, 0xfdffffff }, // and:6:0x0000BF64
	{  18, 0x0009f158, 0xfdffffff }, // and:6:0x0009F158
	{  19, 0x00002732, 0xfdffffff }, // and:6:0x00002732
	{  20, 0x0009f0a0, 0xfdffffff }, // and:6:0x0009F0A0
	{  21, 0x10000100, 0xfdffffff }, // and:6:0x10000100
	{  22, 0x0009f084, 0xfdffffff }, // and:6:0x0009F084
	{  23, 0x0000c124, 0xfdffffff }, // and:6:0x0000C124
	{  24, 0x0000c120, 0xfdffffff }, // and:6:0x0000C120
	{  25, 0x0009f1a8, 0xfdffffff }, // and:6:0x0009F1A8
	{  26, 0x0000c138, 0xfdffffff }, // and:6:0x0000C138
	{  27, 0x00081dd8, 0xfdffffff }, // and:6:0x00081DD8
	{  31, 0x00081d20, 0xfdffffff }, // and:6:0x00081D20
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_free_2[] = {
	{   0, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{   1, 0xe59f0064, 0xfdffffff }, // ldr:4:0xE59F0064
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFE1E
	{   3, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   4, 0xe080000c, 0xfdffffff }, // add:6:0xE280000C
	{   5, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   6, 0xea000000, 0xff000000 }, // b, bl:3:0xEA002C61
	{   7, 0x00110004, 0xfdffffff }, // and:6:0x00110004
	{   8, 0x0000c12c, 0xfdffffff }, // and:6:0x0000C12C
	{   9, 0x00580001, 0xfdffffff }, // sub:6:0x00580001
	{  10, 0x0009f594, 0xfdffffff }, // and:6:0x0009F594 mul:11:0x0009F594
	{  11, 0x0000c114, 0xfdffffff }, // and:6:0x0000C114
	{  13, 0x00110002, 0xfdffffff }, // and:6:0x00110002
	{  14, 0x0000bf64, 0xfdffffff }, // and:6:0x0000BF64
	{  15, 0x0009f158, 0xfdffffff }, // and:6:0x0009F158
	{  16, 0x00002732, 0xfdffffff }, // and:6:0x00002732
	{  17, 0x0009f0a0, 0xfdffffff }, // and:6:0x0009F0A0
	{  18, 0x10000100, 0xfdffffff }, // and:6:0x10000100
	{  19, 0x0009f084, 0xfdffffff }, // and:6:0x0009F084
	{  20, 0x0000c124, 0xfdffffff }, // and:6:0x0000C124
	{  21, 0x0000c120, 0xfdffffff }, // and:6:0x0000C120
	{  22, 0x0009f1a8, 0xfdffffff }, // and:6:0x0009F1A8
	{  23, 0x0000c138, 0xfdffffff }, // and:6:0x0000C138
	{  24, 0x00081dd8, 0xfdffffff }, // and:6:0x00081DD8
	{  28, 0x00081d20, 0xfdffffff }, // and:6:0x00081D20
	{  29, 0x00002730, 0xfdffffff }, // and:6:0x00002730
	{  30, 0x0009f0f4, 0xfdffffff }, // and:6:0x0009F0F4
	{  31, 0x0009f4ec, 0xfdffffff }, // and:6:0x0009F4EC
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_AllocateMemory_2[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0BFC00
	{   3, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   4, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0BFC00
	{   8, 0x00000064, 0xfdffffff }, // and:6:0x00000064
	{  11, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  13, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  15, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  16, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  17, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{  18, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0BEC38
	{  20, 0xe59f0010, 0xfdffffff }, // ldr:4:0xE59F0010
	{  21, 0xe1a0104d, 0xfdffffff }, // mov:6:0xE3A0104D
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00087A
	{  23, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  27, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  28, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  29, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0BF980
	{  30, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  31, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_FreeMemory_2[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0BFC00
	{   5, 0x00000064, 0xfdffffff }, // and:6:0x00000064
	{   8, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  10, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  12, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  13, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  14, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0BEC38
	{  17, 0xe59f0010, 0xfdffffff }, // ldr:4:0xE59F0010
	{  18, 0xe1a0104d, 0xfdffffff }, // mov:6:0xE3A0104D
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00087A
	{  20, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  24, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  25, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  26, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0BF980
	{  27, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  28, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  29, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0BFBC5
	{  30, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  31, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_CreatePhysicalVram_2[] = {
	{   1, 0xe59fc0a0, 0xfdffffff }, // ldr:4:0xE59FC0A0
	{   2, 0xe59ce000, 0xfdffffff }, // ldr:4:0xE59CE000
	{   3, 0xe15e0001, 0xfdffffff }, // cmp:7:0xE35E0001
	{   4, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{   5, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   6, 0xe59f0090, 0xfdffffff }, // ldr:4:0xE59F0090
	{   7, 0xe1a010d4, 0xfdffffff }, // mov:6:0xE3A010D4
	{   8, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   9, 0xe1a04003, 0xfdffffff }, // mov:6:0xE1A04003
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFB2FDD
	{  12, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{  13, 0x11a03000, 0xfdffffff }, // mov:6:0x13A03000
	{  14, 0x01a03001, 0xfdffffff }, // mov:6:0x03A03001
	{  15, 0xe1570000, 0xfdffffff }, // cmp:7:0xE3570000
	{  17, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  18, 0xe59f0060, 0xfdffffff }, // ldr:4:0xE59F0060
	{  19, 0xe1a010d7, 0xfdffffff }, // mov:6:0xE3A010D7
	{  20, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000006
	{  21, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000
	{  22, 0x11a03000, 0xfdffffff }, // mov:6:0x13A03000
	{  23, 0x01a03001, 0xfdffffff }, // mov:6:0x03A03001
	{  24, 0xe1560000, 0xfdffffff }, // cmp:7:0xE3560000
	{  26, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  27, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFB2FCC
	{  29, 0xe1a03201, 0xfdffffff }, // mov:6:0xE3A03201
	{  30, 0xe0833836, 0xfdffffff }, // add:6:0xE2833836
	{  31, 0xe59fe028, 0xfdffffff }, // ldr:4:0xE59FE028
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_PhySw_testgpio_2[] = {
	{   1, 0xe59f3068, 0xfdffffff }, // ldr:4:0xE59F3068
	{   2, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   3, 0xe1a03800, 0xfdffffff }, // mov:6:0xE1A03800
	{   4, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   5, 0xe1a010b7, 0xfdffffff }, // mov:6:0xE3A010B7
	{   6, 0xe59f0058, 0xfdffffff }, // ldr:4:0xE59F0058
	{   7, 0xe1a04843, 0xfdffffff }, // mov:6:0xE1A04843
	{   8, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFAD0B
	{  11, 0xe1a02822, 0xfdffffff }, // mov:6:0xE3A02822
	{  12, 0xe1a03804, 0xfdffffff }, // mov:6:0xE1A03804
	{  13, 0xe0822a03, 0xfdffffff }, // add:6:0xE2822A03
	{  14, 0xe1b03823, 0xfdffffff }, // mov:6:0xE1B03823
	{  15, 0xe0822173, 0xfdffffff }, // add:6:0xE2822173
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{  17, 0xe1a02822, 0xfdffffff }, // mov:6:0xE3A02822
	{  18, 0xe0822a03, 0xfdffffff }, // add:6:0xE2822A03
	{  19, 0xe1530001, 0xfdffffff }, // cmp:7:0xE3530001
	{  20, 0xe0822193, 0xfdffffff }, // add:6:0xE2822193
	{  21, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{  22, 0xe1a010c8, 0xfdffffff }, // mov:6:0xE3A010C8
	{  23, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001
	{  24, 0xe5925000, 0xfdffffff }, // ldr:4:0xE5925000
	{  25, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000000
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFACFB
	{  27, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  29, 0x00001fc4, 0xfdffffff }, // and:6:0x00001FC4
	{  31, 0xe59f1044, 0xfdffffff }, // ldr:4:0xE59F1044
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_rand_2[] = {
	{   0, 0xe59f002c, 0xfdffffff }, // ldr:4:0xE59F002C
	{   1, 0xe59f102c, 0xfdffffff }, // ldr:4:0xE59F102C
	{   2, 0xe59fc02c, 0xfdffffff }, // ldr:4:0xE59FC02C
	{   3, 0xe5903000, 0xfdffffff }, // ldr:4:0xE5903000
	{   5, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000
	{   6, 0xe59fc020, 0xfdffffff }, // ldr:4:0xE59FC020
	{   7, 0xe00c0821, 0xfdffffff }, // and:6:0xE00C0821
	{   8, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 8/32 */
};

static FuncSig func_sig_srand_2[] = {
	{   0, 0xe59fc008, 0xfdffffff }, // ldr:4:0xE59FC008
	{   1, 0xe58c0000, 0xfdffffff }, // str:4:0xE58C0000
	{   2, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   3, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 4/32 */
};

static FuncSig func_sig_IsStrobeChargeCompleted_2[] = {
	{   1, 0xe59f3060, 0xfdffffff }, // ldr:4:0xE59F3060
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE3A04000
	{   4, 0xe59f5058, 0xfdffffff }, // ldr:4:0xE59F5058
	{   5, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{   6, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{   7, 0xe1a01004, 0xfdffffff }, // mov:6:0xE3A01004
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFBFC7B
	{   9, 0xe1a01003, 0xfdffffff }, // mov:6:0xE3A01003
	{  10, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  11, 0xe1a02f7d, 0xfdffffff }, // mov:6:0xE3A02F7D
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFBF9A3
	{  13, 0xe1500004, 0xfdffffff }, // cmp:7:0xE1500004
	{  14, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000006
	{  16, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFBFA21
	{  18, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  19, 0xe1a01003, 0xfdffffff }, // mov:6:0xE3A01003
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFBFA0A
	{  21, 0xe59d3000, 0xfdffffff }, // ldr:4:0xE59D3000
	{  22, 0xe0034001, 0xfdffffff }, // and:6:0xE2034001
	{  23, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  24, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  26, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_GetCurrentAvValue_2[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFF9781
	{   2, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{   3, 0xe1a00840, 0xfdffffff }, // mov:6:0xE1A00840
	{   4, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{   6, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   7, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   8, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   9, 0xe08d0002, 0xfdffffff }, // add:6:0xE28D0002
	{  10, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFF97C6
	{  12, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  13, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFCF
	{  16, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{ -1, -1, -1 },
	/* 15/18 */
};

static FuncSig func_sig__pow_2[] = {
	{   0, 0xe04dd010, 0xfdffffff }, // sub:6:0xE24DD010
	{   2, 0xe04dd0e0, 0xfdffffff }, // sub:6:0xE24DD0E0
	{   3, 0xe1a0cf41, 0xfdffffff }, // mov:6:0xE3A0CF41
	{   4, 0xe08cc00d, 0xfdffffff }, // add:6:0xE08CC00D
	{   6, 0xe1a0cf43, 0xfdffffff }, // mov:6:0xE3A0CF43
	{   7, 0xe08cc00d, 0xfdffffff }, // add:6:0xE08CC00D
	{   9, 0xe59d0104, 0xfdffffff }, // ldr:4:0xE59D0104
	{  10, 0xe59d1108, 0xfdffffff }, // ldr:4:0xE59D1108
	{  11, 0xe08d2068, 0xfdffffff }, // add:6:0xE28D2068
	{  13, 0xe59dc06c, 0xfdffffff }, // ldr:4:0xE59DC06C
	{  14, 0xe59d010c, 0xfdffffff }, // ldr:4:0xE59D010C
	{  15, 0xe59d1110, 0xfdffffff }, // ldr:4:0xE59D1110
	{  16, 0xe58dc020, 0xfdffffff }, // str:4:0xE58DC020
	{  17, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{  18, 0xe08d2070, 0xfdffffff }, // add:6:0xE28D2070
	{  19, 0xe58d3014, 0xfdffffff }, // str:4:0xE58D3014
	{  21, 0xe59dc074, 0xfdffffff }, // ldr:4:0xE59DC074
	{  22, 0xe58dc010, 0xfdffffff }, // str:4:0xE58DC010
	{  23, 0xe59dc020, 0xfdffffff }, // ldr:4:0xE59DC020
	{  25, 0xe5920000, 0xfdffffff }, // ldr:4:0xE5920000
	{  26, 0xe00cc003, 0xfdffffff }, // and:6:0xE00CC003
	{  27, 0xe59d3010, 0xfdffffff }, // ldr:4:0xE59D3010
	{  28, 0xe58dc008, 0xfdffffff }, // str:4:0xE58DC008
	{  30, 0xe003c00c, 0xfdffffff }, // and:6:0xE003C00C
	{  31, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig__log_2[] = {
	{   1, 0xe04dd050, 0xfdffffff }, // sub:6:0xE24DD050
	{   2, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   3, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{   4, 0xe08d0018, 0xfdffffff }, // add:6:0xE28D0018
	{   6, 0xe59dc01c, 0xfdffffff }, // ldr:4:0xE59DC01C
	{   7, 0xe58dc008, 0xfdffffff }, // str:4:0xE58DC008
	{   8, 0xe59d3008, 0xfdffffff }, // ldr:4:0xE59D3008
	{   9, 0xe1a0c000, 0xfdffffff }, // mov:6:0xE3A0C000
	{  10, 0xe5901000, 0xfdffffff }, // ldr:4:0xE5901000
	{  11, 0xe1530601, 0xfdffffff }, // cmp:7:0xE3530601
	{  12, 0xe58dc010, 0xfdffffff }, // str:4:0xE58DC010
	{  13, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000017
	{  14, 0xe59d3008, 0xfdffffff }, // ldr:4:0xE59D3008
	{  16, 0xe0033002, 0xfdffffff }, // and:6:0xE0033002
	{  18, 0x059f160c, 0xfdffffff }, // ldr:4:0x059F160C
	{  19, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00017F
	{  21, 0xe59dc008, 0xfdffffff }, // ldr:4:0xE59DC008
	{  22, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  23, 0xb59f15fc, 0xfdffffff }, // ldr:4:0xB59F15FC
	{  24, 0xb1a00000, 0xfdffffff }, // mov:6:0xB3A00000
	{  25, 0xba000000, 0xff000000 }, // b, bl:3:0xBA00017A
	{  27, 0xe1a01009, 0xfdffffff }, // mov:6:0xE1A01009
	{  28, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  29, 0xe58dc010, 0xfdffffff }, // str:4:0xE58DC010
	{  30, 0xe59f35e4, 0xfdffffff }, // ldr:4:0xE59F35E4
	{  31, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig__log10_2[] = {
	{   1, 0xe04dd020, 0xfdffffff }, // sub:6:0xE24DD020
	{   2, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   3, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{   4, 0xe08db008, 0xfdffffff }, // add:6:0xE28DB008
	{   6, 0xe59da00c, 0xfdffffff }, // ldr:4:0xE59DA00C
	{   7, 0xe59b4000, 0xfdffffff }, // ldr:4:0xE59B4000
	{   8, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE3A0B000
	{   9, 0xe15a0601, 0xfdffffff }, // cmp:7:0xE35A0601
	{  10, 0xaa000000, 0xff000000 }, // b, bl:3:0xAA000014
	{  12, 0xe00ac00c, 0xfdffffff }, // and:6:0xE00AC00C
	{  14, 0x059f110c, 0xfdffffff }, // ldr:4:0x059F110C
	{  15, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00003F
	{  17, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{  18, 0xb59f1100, 0xfdffffff }, // ldr:4:0xB59F1100
	{  19, 0xb1a00000, 0xfdffffff }, // mov:6:0xB3A00000
	{  20, 0xba000000, 0xff000000 }, // b, bl:3:0xBA00003B
	{  22, 0xe1a01009, 0xfdffffff }, // mov:6:0xE1A01009
	{  23, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  24, 0xe59f30ec, 0xfdffffff }, // ldr:4:0xE59F30EC
	{  25, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000C28
	{  27, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{  28, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  29, 0xe58d0018, 0xfdffffff }, // str:4:0xE58D0018
	{  30, 0xe58d101c, 0xfdffffff }, // str:4:0xE58D101C
	{  31, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig__sqrt_2[] = {
	{   1, 0xe1a0c470, 0xfdffffff }, // mov:6:0xE3A0C470
	{   3, 0xe111000c, 0xfdffffff }, // tst:7:0xE111000C
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000044
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000064
	{   7, 0xe1110480, 0xfdffffff }, // tst:7:0xE3110480
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000066
	{   9, 0xe1a0ca21, 0xfdffffff }, // mov:6:0xE1A0CA21
	{  12, 0xe08cc0fd, 0xfdffffff }, // add:6:0xE28CC0FD
	{  13, 0xe1b0c0ac, 0xfdffffff }, // mov:6:0xE1B0C0AC
	{  14, 0xe08ccf60, 0xfdffffff }, // add:6:0xE28CCF60
	{  15, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000001
	{  16, 0xe1b00080, 0xfdffffff }, // mov:6:0xE1B00080
	{  18, 0xe1a01501, 0xfdffffff }, // mov:6:0xE1A01501
	{  20, 0xe1a00500, 0xfdffffff }, // mov:6:0xE1A00500
	{  21, 0xe1a02440, 0xfdffffff }, // mov:6:0xE3A02440
	{  22, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{  23, 0xe0411440, 0xfdffffff }, // sub:6:0xE2411440
	{  24, 0xe1a0e540, 0xfdffffff }, // mov:6:0xE3A0E540
	{  25, 0xe0514002, 0xfdffffff }, // sub:6:0xE0514002
	{  26, 0x2054400e, 0xfdffffff }, // sub:6:0x2054400E
	{  27, 0x21a01004, 0xfdffffff }, // mov:6:0x21A01004
	{  28, 0x2082208e, 0xfdffffff }, // add:6:0x2082208E
	{  29, 0xe1b00080, 0xfdffffff }, // mov:6:0xE1B00080
	{  31, 0xe1b0e0ae, 0xfdffffff }, // mov:6:0xE1B0E0AE
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_strncpy_2[] = {
	{   0, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   2, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   3, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000C
	{   5, 0xe013c0ff, 0xfdffffff }, // and:6:0xE213C0FF
	{   7, 0x00422001, 0xfdffffff }, // sub:6:0x02422001
	{   8, 0x01a01000, 0xfdffffff }, // mov:6:0x03A01000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  10, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF7
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000003
	{  14, 0xe0422001, 0xfdffffff }, // sub:6:0xE2422001
	{  15, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{  18, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{  21, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000007
	{  23, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{  25, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{  26, 0x0a000000, 0xff000000 }, // b, bl:3:0x0AFFFFF8
	{  27, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE15A0000
	{  28, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFA
	{  29, 0xe0420001, 0xfdffffff }, // sub:6:0xE2420001
	{  30, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000000
	{  31, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_strrchr_2[] = {
	{   0, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{   1, 0xe00110ff, 0xfdffffff }, // and:6:0xE20110FF
	{   3, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE15C0001
	{   4, 0x01a02000, 0xfdffffff }, // mov:6:0x01A02000
	{   6, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9
	{   8, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{   9, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 8/32 */
};

static FuncSig func_sig_SetParameterData_2[] = {
	{   1, 0xe59f30c4, 0xfdffffff }, // ldr:4:0xE59F30C4
	{   2, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{   3, 0xe593c000, 0xfdffffff }, // ldr:4:0xE593C000
	{   4, 0xe1a02802, 0xfdffffff }, // mov:6:0xE1A02802
	{   5, 0xe1a03800, 0xfdffffff }, // mov:6:0xE1A03800
	{   6, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{   7, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   8, 0xe1a01e41, 0xfdffffff }, // mov:6:0xE3A01E41
	{   9, 0xe59f70a8, 0xfdffffff }, // ldr:4:0xE59F70A8
	{  10, 0xe59f00a8, 0xfdffffff }, // ldr:4:0xE59F00A8
	{  11, 0xe0811002, 0xfdffffff }, // add:6:0xE2811002
	{  12, 0xe1a04843, 0xfdffffff }, // mov:6:0xE1A04843
	{  13, 0xe1a05842, 0xfdffffff }, // mov:6:0xE1A05842
	{  14, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA3741
	{  16, 0xe1a02804, 0xfdffffff }, // mov:6:0xE1A02804
	{  17, 0xe1a03822, 0xfdffffff }, // mov:6:0xE1A03822
	{  19, 0xe1a01e41, 0xfdffffff }, // mov:6:0xE3A01E41
	{  20, 0xe1a04804, 0xfdffffff }, // mov:6:0xE1A04804
	{  21, 0xe1120101, 0xfdffffff }, // tst:7:0xE3120101
	{  22, 0xe59f0078, 0xfdffffff }, // ldr:4:0xE59F0078
	{  23, 0xe0811002, 0xfdffffff }, // add:6:0xE2811002
	{  24, 0xe1a04824, 0xfdffffff }, // mov:6:0xE1A04824
	{  25, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA3736
	{  27, 0xe1a01e41, 0xfdffffff }, // mov:6:0xE3A01E41
	{  28, 0xe154006d, 0xfdffffff }, // cmp:7:0xE354006D
	{  29, 0xe59f005c, 0xfdffffff }, // ldr:4:0xE59F005C
	{  30, 0xe0811002, 0xfdffffff }, // add:6:0xE2811002
	{  31, 0x9a000000, 0xff000000 }, // b, bl:3:0x9A000000
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_GetParameterData_2[] = {
	{   1, 0xe59f30a8, 0xfdffffff }, // ldr:4:0xE59F30A8
	{   2, 0xe593c000, 0xfdffffff }, // ldr:4:0xE593C000
	{   3, 0xe1a02802, 0xfdffffff }, // mov:6:0xE1A02802
	{   4, 0xe1a03800, 0xfdffffff }, // mov:6:0xE1A03800
	{   5, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{   6, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   7, 0xe1a01e41, 0xfdffffff }, // mov:6:0xE3A01E41
	{   8, 0xe59f7090, 0xfdffffff }, // ldr:4:0xE59F7090
	{   9, 0xe59f0090, 0xfdffffff }, // ldr:4:0xE59F0090
	{  10, 0xe081100c, 0xfdffffff }, // add:6:0xE281100C
	{  11, 0xe1a04843, 0xfdffffff }, // mov:6:0xE1A04843
	{  12, 0xe1a05842, 0xfdffffff }, // mov:6:0xE1A05842
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA370A
	{  15, 0xe1a02804, 0xfdffffff }, // mov:6:0xE1A02804
	{  16, 0xe1a03822, 0xfdffffff }, // mov:6:0xE1A03822
	{  18, 0xe1a01e41, 0xfdffffff }, // mov:6:0xE3A01E41
	{  19, 0xe1a04804, 0xfdffffff }, // mov:6:0xE1A04804
	{  20, 0xe1120101, 0xfdffffff }, // tst:7:0xE3120101
	{  21, 0xe59f0060, 0xfdffffff }, // ldr:4:0xE59F0060
	{  22, 0xe081100c, 0xfdffffff }, // add:6:0xE281100C
	{  23, 0xe1a04824, 0xfdffffff }, // mov:6:0xE1A04824
	{  24, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA36FF
	{  26, 0xe1a01e41, 0xfdffffff }, // mov:6:0xE3A01E41
	{  27, 0xe154006d, 0xfdffffff }, // cmp:7:0xE354006D
	{  28, 0xe59f0044, 0xfdffffff }, // ldr:4:0xE59F0044
	{  29, 0xe081100c, 0xfdffffff }, // add:6:0xE281100C
	{  30, 0x9a000000, 0xff000000 }, // b, bl:3:0x9A000000
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA36F9
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_rename_2[] = {
	{   0, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   2, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   3, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{   4, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{   7, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{   9, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF584
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000E
	{  13, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  14, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFED
	{  16, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  17, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  19, 0xba000000, 0xff000000 }, // b, bl:3:0xBA000007
	{  20, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  21, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{  22, 0xe1a0100a, 0xfdffffff }, // mov:6:0xE3A0100A
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEA4
	{  24, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  25, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE51
	{  27, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  30, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{  31, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_chdir_2[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   3, 0xe58d0000, 0xfdffffff }, // str:4:0xE58D0000
	{   4, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0002B4
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000010
	{   9, 0xe59dc000, 0xfdffffff }, // ldr:4:0xE59DC000
	{  10, 0xe15c000b, 0xfdffffff }, // cmp:7:0xE15C000B
	{  11, 0x059fb28c, 0xfdffffff }, // ldr:4:0x059FB28C
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  13, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFEB5E
	{  15, 0xe1500c01, 0xfdffffff }, // cmp:7:0xE3500C01
	{  16, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A000004
	{  17, 0xe59fb278, 0xfdffffff }, // ldr:4:0xE59FB278
	{  18, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF55E
	{  21, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000003
	{  22, 0xe59f0250, 0xfdffffff }, // ldr:4:0xE59F0250
	{  23, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFEAFB
	{  25, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  26, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  28, 0xe59f1238, 0xfdffffff }, // ldr:4:0xE59F1238
	{  29, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFEAF6
	{  30, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFE0
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_time_2[] = {
	{   1, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{   2, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{   3, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   4, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000209
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{   8, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   9, 0x159dc000, 0xfdffffff }, // ldr:4:0x159DC000
	{  10, 0x158ac000, 0xfdffffff }, // str:4:0x158AC000
	{  11, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000000
	{  14, 0xe08dd008, 0xfdffffff }, // add:6:0xE28DD008
	{  17, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{  18, 0xe59fb418, 0xfdffffff }, // ldr:4:0xE59FB418
	{  19, 0xe59bb000, 0xfdffffff }, // ldr:4:0xE59BB000
	{  20, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  23, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  24, 0xe1a0f00b, 0xfdffffff }, // mov:6:0xE1A0F00B
	{  25, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  26, 0xe08dd008, 0xfdffffff }, // add:6:0xE28DD008
	{  27, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  30, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{  31, 0xe59fb3e8, 0xfdffffff }, // ldr:4:0xE59FB3E8
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_utime_2[] = {
	{   1, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   3, 0xe59f2034, 0xfdffffff }, // ldr:4:0xE59F2034
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000C12
	{   6, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000007
	{   9, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  10, 0xe1a0200a, 0xfdffffff }, // mov:6:0xE1A0200A
	{  11, 0xe1a0102c, 0xfdffffff }, // mov:6:0xE3A0102C
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000AC9
	{  13, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  14, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000A76
	{  16, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  18, 0x000001b6, 0xfdffffff }, // and:6:0x000001B6
	{  20, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  21, 0xe1a00032, 0xfdffffff }, // mov:6:0xE3A00032
	{  22, 0xe1a01004, 0xfdffffff }, // mov:6:0xE3A01004
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001305
	{  24, 0xe59fc5d0, 0xfdffffff }, // ldr:4:0xE59FC5D0
	{  25, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  26, 0xe58c0000, 0xfdffffff }, // str:4:0xE58C0000
	{  28, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000010
	{  29, 0xe59f05c0, 0xfdffffff }, // ldr:4:0xE59F05C0
	{  30, 0xe1a03032, 0xfdffffff }, // mov:6:0xE3A03032
	{  31, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_Mount_FileSystem_2[] = {
	{   1, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000
	{   2, 0xe59f6064, 0xfdffffff }, // ldr:4:0xE59F6064
	{   3, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE74
	{   5, 0xe5960038, 0xfdffffff }, // ldr:4:0xE5960038
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC22
	{   7, 0xe0501000, 0xfdffffff }, // sub:6:0xE2501000
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   9, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005
	{  10, 0xe59f3048, 0xfdffffff }, // ldr:4:0xE59F3048
	{  11, 0xe59f2048, 0xfdffffff }, // ldr:4:0xE59F2048
	{  12, 0xe5831000, 0xfdffffff }, // str:4:0xE5831000
	{  13, 0xe59f3044, 0xfdffffff }, // ldr:4:0xE59F3044
	{  14, 0xe5821000, 0xfdffffff }, // str:4:0xE5821000
	{  15, 0xe5831000, 0xfdffffff }, // str:4:0xE5831000
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE7C
	{  17, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF44
	{  19, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  20, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF63
	{  22, 0xe0044000, 0xfdffffff }, // and:6:0xE0044000
	{  23, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{  24, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  25, 0xe596103c, 0xfdffffff }, // ldr:4:0xE596103C
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFD0
	{  27, 0xe5860040, 0xfdffffff }, // str:4:0xE5860040
	{  29, 0x0002c4a8, 0xfdffffff }, // and:6:0x0002C4A8
	{  30, 0x00002750, 0xfdffffff }, // and:6:0x00002750
	{  31, 0x00002748, 0xfdffffff }, // and:6:0x00002748
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_LockMainPower_2[] = {
	{   1, 0xe59f3074, 0xfdffffff }, // ldr:4:0xE59F3074
	{   2, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   3, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   4, 0xe59f406c, 0xfdffffff }, // ldr:4:0xE59F406C
	{   5, 0xe59f006c, 0xfdffffff }, // ldr:4:0xE59F006C
	{   6, 0xe1a010bf, 0xfdffffff }, // mov:6:0xE3A010BF
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA4B62
	{   9, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{  10, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA86AA
	{  12, 0xe59f2054, 0xfdffffff }, // ldr:4:0xE59F2054
	{  13, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{  14, 0xe0833001, 0xfdffffff }, // add:6:0xE2833001
	{  15, 0xe1530001, 0xfdffffff }, // cmp:7:0xE3530001
	{  16, 0xe5823000, 0xfdffffff }, // str:4:0xE5823000
	{  17, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF11
	{  19, 0xe59f003c, 0xfdffffff }, // ldr:4:0xE59F003C
	{  20, 0xe5903000, 0xfdffffff }, // ldr:4:0xE5903000
	{  21, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001
	{  22, 0xe59f1034, 0xfdffffff }, // ldr:4:0xE59F1034
	{  23, 0xe1530002, 0xfdffffff }, // cmp:7:0xE1530002
	{  24, 0xe5812000, 0xfdffffff }, // str:4:0xE5812000
	{  25, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000002
	{  26, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{  27, 0xe5803000, 0xfdffffff }, // str:4:0xE5803000
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEBA
	{  29, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{  31, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFA86C0
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_UnlockMainPower_2[] = {
	{   1, 0xe59f30c8, 0xfdffffff }, // ldr:4:0xE59F30C8
	{   2, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   3, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   4, 0xe59f50c0, 0xfdffffff }, // ldr:4:0xE59F50C0
	{   5, 0xe59f40c0, 0xfdffffff }, // ldr:4:0xE59F40C0
	{   6, 0xe59f00c0, 0xfdffffff }, // ldr:4:0xE59F00C0
	{   7, 0xe1a010d2, 0xfdffffff }, // mov:6:0xE3A010D2
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA4B3B
	{  10, 0xe5943000, 0xfdffffff }, // ldr:4:0xE5943000
	{  11, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  12, 0xe1530001, 0xfdffffff }, // cmp:7:0xE1530001
	{  14, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA8680
	{  16, 0xe5943000, 0xfdffffff }, // ldr:4:0xE5943000
	{  17, 0xe0432001, 0xfdffffff }, // sub:6:0xE2432001
	{  18, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  19, 0xe5842000, 0xfdffffff }, // str:4:0xE5842000
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  21, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFA86A2
	{  24, 0xe59f307c, 0xfdffffff }, // ldr:4:0xE59F307C
	{  25, 0xe5832000, 0xfdffffff }, // str:4:0xE5832000
	{  26, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEEA
	{  27, 0xe59f3074, 0xfdffffff }, // ldr:4:0xE59F3074
	{  28, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{  29, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  30, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000011
	{  31, 0xe59fc068, 0xfdffffff }, // ldr:4:0xE59FC068
	{ -1, -1, -1 },
	/* 29/32 */
};

static FuncSig func_sig_MoveZoomLensWithPoint_2[] = {
	{   1, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{   3, 0xe08d0004, 0xfdffffff }, // add:6:0xE28D0004
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF5D5F4
	{   5, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   6, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{   7, 0xe59f1050, 0xfdffffff }, // ldr:4:0xE59F1050
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFB1B
	{   9, 0xe59f304c, 0xfdffffff }, // ldr:4:0xE59F304C
	{  10, 0xe1a01c27, 0xfdffffff }, // mov:6:0xE3A01C27
	{  11, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  12, 0xe0811010, 0xfdffffff }, // add:6:0xE2811010
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF607D0
	{  14, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  15, 0xe1a0000d, 0xfdffffff }, // mov:6:0xE1A0000D
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF5D5E8
	{  17, 0xe1140001, 0xfdffffff }, // tst:7:0xE3140001
	{  18, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF886
	{  21, 0xe1a00a20, 0xfdffffff }, // mov:6:0xE1A00A20
	{  22, 0xe1a00a00, 0xfdffffff }, // mov:6:0xE1A00A00
	{  23, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  24, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  26, 0xe08dd008, 0xfdffffff }, // add:6:0xE28DD008
	{  28, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_MoveFocusLensToDistance_2[] = {
	{   1, 0xe59f5030, 0xfdffffff }, // ldr:4:0xE59F5030
	{   2, 0xe5904000, 0xfdffffff }, // ldr:4:0xE5904000
	{   3, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   4, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF567AD
	{   6, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   7, 0xe59f101c, 0xfdffffff }, // ldr:4:0xE59F101C
	{   8, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000006
	{  10, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  11, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  12, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF56735
	{  15, 0x0000a2e0, 0xfdffffff }, // and:6:0x0000A2E0
	{  17, 0xe1a03002, 0xfdffffff }, // mov:6:0xE1A03002
	{  18, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  19, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  20, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  21, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  22, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFFF
	{  24, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{  26, 0xe1a05801, 0xfdffffff }, // mov:6:0xE1A05801
	{  28, 0xe052e000, 0xfdffffff }, // sub:6:0xE252E000
	{  29, 0xe1a00800, 0xfdffffff }, // mov:6:0xE1A00800
	{  30, 0xe1a0c86c, 0xfdffffff }, // mov:6:0xE1A0C86C
	{  31, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_GetFocusLensSubjectDistanceFromLens_2[] = {
	{   1, 0xe59f3070, 0xfdffffff }, // ldr:4:0xE59F3070
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   4, 0xe1a01f8a, 0xfdffffff }, // mov:6:0xE3A01F8A
	{   5, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   6, 0xe0811002, 0xfdffffff }, // add:6:0xE2811002
	{   7, 0xe59f005c, 0xfdffffff }, // ldr:4:0xE59F005C
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF581F7
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE87
	{  11, 0xe1a03800, 0xfdffffff }, // mov:6:0xE1A03800
	{  13, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  14, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  15, 0xe08d0002, 0xfdffffff }, // add:6:0xE28D0002
	{  16, 0xe1a04823, 0xfdffffff }, // mov:6:0xE1A04823
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFAD4C
	{  19, 0xe59f3030, 0xfdffffff }, // ldr:4:0xE59F3030
	{  21, 0xe5931000, 0xfdffffff }, // ldr:4:0xE5931000
	{  22, 0xe1a02082, 0xfdffffff }, // mov:6:0xE1A02082
	{  23, 0xe0811fa9, 0xfdffffff }, // add:6:0xE2811FA9
	{  25, 0xe0633004, 0xfdffffff }, // rsb:6:0xE0633004
	{  26, 0xe1a03803, 0xfdffffff }, // mov:6:0xE1A03803
	{  27, 0xe1a00823, 0xfdffffff }, // mov:6:0xE1A00823
	{  28, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  30, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_SetAutoShutdownTime_2[] = {
	{   1, 0xe59f30c8, 0xfdffffff }, // ldr:4:0xE59F30C8
	{   2, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   3, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   4, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   5, 0xe59f60bc, 0xfdffffff }, // ldr:4:0xE59F60BC
	{   6, 0xe59f50bc, 0xfdffffff }, // ldr:4:0xE59F50BC
	{   7, 0xe59f70bc, 0xfdffffff }, // ldr:4:0xE59F70BC
	{   8, 0xe1a010a7, 0xfdffffff }, // mov:6:0xE3A010A7
	{   9, 0xe59f00b8, 0xfdffffff }, // ldr:4:0xE59F00B8
	{  10, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA4B9E
	{  12, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  13, 0xe5960000, 0xfdffffff }, // ldr:4:0xE5960000
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA86E6
	{  15, 0xe5952000, 0xfdffffff }, // ldr:4:0xE5952000
	{  16, 0xe0643284, 0xfdffffff }, // rsb:6:0xE0643284
	{  17, 0xe0843103, 0xfdffffff }, // add:6:0xE0843103
	{  18, 0xe1a03183, 0xfdffffff }, // mov:6:0xE1A03183
	{  19, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{  20, 0xe5873000, 0xfdffffff }, // str:4:0xE5873000
	{  21, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000002
	{  22, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{  23, 0xe5853000, 0xfdffffff }, // str:4:0xE5853000
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEFD
	{  25, 0xe597e000, 0xfdffffff }, // ldr:4:0xE597E000
	{  26, 0xe15e0000, 0xfdffffff }, // cmp:7:0xE35E0000
	{  27, 0xe1a04001, 0xfdffffff }, // mov:6:0xE3A04001
	{  28, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  29, 0xe59f306c, 0xfdffffff }, // ldr:4:0xE59F306C
	{  30, 0xe5960000, 0xfdffffff }, // ldr:4:0xE5960000
	{  31, 0xe583e000, 0xfdffffff }, // str:4:0xE583E000
	{ -1, -1, -1 },
	/* 31/32 */
};

static FuncSig func_sig_PutInNdFilter_2[] = {
	{   1, 0xe59f4028, 0xfdffffff }, // ldr:4:0xE59F4028
	{   2, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   3, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF5706D
	{   5, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{   6, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000006
	{   8, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{   9, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  10, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF56FF6
	{  13, 0x0000a168, 0xfdffffff }, // and:6:0x0000A168
	{  15, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  16, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFEDE
	{  19, 0xe59f4028, 0xfdffffff }, // ldr:4:0xE59F4028
	{  20, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  21, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF5705B
	{  23, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{  24, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000006
	{  26, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{  27, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  28, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  30, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF56FE4
	{  31, 0x0000a168, 0xfdffffff }, // and:6:0x0000A168
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_PutOutNdFilter_2[] = {
	{   1, 0xe59f4028, 0xfdffffff }, // ldr:4:0xE59F4028
	{   2, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   3, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF5705B
	{   5, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{   6, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000006
	{   8, 0xe5940000, 0xfdffffff }, // ldr:4:0xE5940000
	{   9, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  10, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEAF56FE4
	{  13, 0x0000a168, 0xfdffffff }, // and:6:0x0000A168
	{  15, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  16, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFEBE
	{  24, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  28, 0x00000072, 0xfdffffff }, // and:6:0x00000072
	{ -1, -1, -1 },
	/* 17/32 */
};

static FuncSig func_sig_TurnOnBackLight_2[] = {
	{   0, 0xe59f1010, 0xfdffffff }, // ldr:4:0xE59F1010
	{   1, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020
	{   2, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF929AA
	{   4, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDEB6B
	{   8, 0x4066664f, 0xfdffffff }, // rsb:6:0x4266664F
	{  11, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  12, 0xe59f1010, 0xfdffffff }, // ldr:4:0xE59F1010
	{  13, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020
	{  14, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF9299E
	{  16, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDEB7A
	{  22, 0x61536c61, 0xfdffffff }, // cmp:7:0x63536C61
	{  24, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  25, 0xe59f1010, 0xfdffffff }, // ldr:4:0xE59F1010
	{  26, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020
	{  27, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF92991
	{  29, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  30, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDDFEA
	{ -1, -1, -1 },
	/* 22/32 */
};

static FuncSig func_sig_TurnOffBackLight_2[] = {
	{   0, 0xe59f1010, 0xfdffffff }, // ldr:4:0xE59F1010
	{   1, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020
	{   2, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF9299E
	{   4, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDEB7A
	{  10, 0x61536c61, 0xfdffffff }, // cmp:7:0x63536C61
	{  12, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  13, 0xe59f1010, 0xfdffffff }, // ldr:4:0xE59F1010
	{  14, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020
	{  15, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF92991
	{  17, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  18, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDDFEA
	{  21, 0x5066664f, 0xfdffffff }, // rsb:6:0x5066664F
	{  25, 0x0000006e, 0xfdffffff }, // and:6:0x0000006E
	{  26, 0xe59f1010, 0xfdffffff }, // ldr:4:0xE59F1010
	{  27, 0xe1a00020, 0xfdffffff }, // mov:6:0xE3A00020
	{  28, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF92984
	{  30, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  31, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFDDFF1
	{ -1, -1, -1 },
	/* 22/32 */
};

static FuncSig func_sig_Fclose_Fut_3[] = {
	{   1, 0xe0506000, 0xfdffffff }, // sub:6:0xE2506000
	{   2, 0xe04dd03c, 0xfdffffff }, // sub:6:0xE24DD03C
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000026
	{   5, 0xe0864020, 0xfdffffff }, // add:6:0xE2864020
	{   6, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA3FB2
	{   8, 0xe1500020, 0xfdffffff }, // cmp:7:0xE3500020
	{   9, 0xd08d5018, 0xfdffffff }, // add:6:0xD28D5018
	{  10, 0xd1a08005, 0xfdffffff }, // mov:6:0xD1A08005
	{  11, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000003
	{  12, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF6FED5
	{  14, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  15, 0xe08d8018, 0xfdffffff }, // add:6:0xE28D8018
	{  16, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  17, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA3F4E
	{  19, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  20, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  21, 0xe5964008, 0xfdffffff }, // ldr:4:0xE5964008
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC4A
	{  23, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{  24, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC75
	{  26, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001D5E
	{  28, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000
	{  29, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  30, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  31, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{ -1, -1, -1 },
	/* 30/32 */
};

static FuncSig func_sig_Fopen_Fut_3[] = {
	{   1, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   2, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC6C
	{   5, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   6, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC97
	{   8, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{   9, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001D46
	{  11, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  12, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC72
	{  14, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  17, 0xe0506000, 0xfdffffff }, // sub:6:0xE2506000
	{  18, 0xe04dd03c, 0xfdffffff }, // sub:6:0xE24DD03C
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000026
	{  21, 0xe0864020, 0xfdffffff }, // add:6:0xE2864020
	{  22, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA3FB2
	{  24, 0xe1500020, 0xfdffffff }, // cmp:7:0xE3500020
	{  25, 0xd08d5018, 0xfdffffff }, // add:6:0xD28D5018
	{  26, 0xd1a08005, 0xfdffffff }, // mov:6:0xD1A08005
	{  27, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000003
	{  28, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBF6FED5
	{  30, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  31, 0xe08d8018, 0xfdffffff }, // add:6:0xE28D8018
	{ -1, -1, -1 },
	/* 28/32 */
};

static FuncSig func_sig_Fread_Fut_3[] = {
	{   1, 0xe0537000, 0xfdffffff }, // sub:6:0xE2537000
	{   2, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   3, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   4, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{   5, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   6, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC28
	{  10, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  11, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  12, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  13, 0xe1a03007, 0xfdffffff }, // mov:6:0xE1A03007
	{  14, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001D57
	{  16, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  17, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC2E
	{  19, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  22, 0xe0537000, 0xfdffffff }, // sub:6:0xE2537000
	{  23, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  24, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{  25, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{  26, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  27, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC13
	{  31, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_Fseek_Fut_3[] = {
	{   1, 0xe0507000, 0xfdffffff }, // sub:6:0xE2507000
	{   2, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   3, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{   4, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   5, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBEC
	{   9, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  10, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  11, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  12, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001DF4
	{  14, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  15, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBF3
	{  17, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  20, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  21, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  22, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBDB
	{  26, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  27, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001DF9
	{  29, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  30, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  31, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBE4
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_Fwrite_Fut_3[] = {
	{   1, 0xe0537000, 0xfdffffff }, // sub:6:0xE2537000
	{   2, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   3, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   4, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{   5, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   6, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC13
	{  10, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  11, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  12, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  13, 0xe1a03007, 0xfdffffff }, // mov:6:0xE1A03007
	{  14, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001D92
	{  16, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  17, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC19
	{  19, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  22, 0xe0524000, 0xfdffffff }, // sub:6:0xE2524000
	{  23, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  24, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{  25, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020
	{  26, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  27, 0x01a00004, 0xfdffffff }, // mov:6:0x01A00004
	{  29, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBFF
	{  30, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{  31, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_GetFocusLensSubjectDistanceFromLens_3[] = {
	{   1, 0xe59f306c, 0xfdffffff }, // ldr:4:0xE59F306C
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   4, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   5, 0xe1a01f95, 0xfdffffff }, // mov:6:0xE3A01F95
	{   6, 0xe59f005c, 0xfdffffff }, // ldr:4:0xE59F005C
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0161C2
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEB8
	{  10, 0xe1a03800, 0xfdffffff }, // mov:6:0xE1A03800
	{  12, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  13, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  14, 0xe08d0002, 0xfdffffff }, // add:6:0xE28D0002
	{  15, 0xe1a04823, 0xfdffffff }, // mov:6:0xE1A04823
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB004F52
	{  18, 0xe59f3030, 0xfdffffff }, // ldr:4:0xE59F3030
	{  20, 0xe5931000, 0xfdffffff }, // ldr:4:0xE5931000
	{  21, 0xe1a02082, 0xfdffffff }, // mov:6:0xE1A02082
	{  22, 0xe0811f79, 0xfdffffff }, // add:6:0xE2811F79
	{  24, 0xe0633004, 0xfdffffff }, // rsb:6:0xE0633004
	{  25, 0xe1a03803, 0xfdffffff }, // mov:6:0xE1A03803
	{  26, 0xe1a00823, 0xfdffffff }, // mov:6:0xE1A00823
	{  27, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  29, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_Fgets_Fut_3[] = {
	{   1, 0xe0524000, 0xfdffffff }, // sub:6:0xE2524000
	{   2, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   3, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   4, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020
	{   5, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   6, 0x01a00004, 0xfdffffff }, // mov:6:0x01A00004
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBFF
	{   9, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{  10, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{  11, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  12, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001DBE
	{  14, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  15, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC06
	{  17, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  20, 0xe0507000, 0xfdffffff }, // sub:6:0xE2507000
	{  21, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{  22, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{  23, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  24, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBEC
	{  28, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  29, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  30, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  31, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007
	{ -1, -1, -1 },
	/* 26/32 */
};

static FuncSig func_sig_Feof_Fut_3[] = {
	{   1, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{   2, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   3, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBDB
	{   7, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   8, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001DF9
	{  10, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  11, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBE4
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  16, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  17, 0xe0846020, 0xfdffffff }, // add:6:0xE2846020
	{  18, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  19, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBCB
	{  23, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  24, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001DEF
	{  26, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  27, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  28, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBFD
	{  29, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  30, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBD2
	{  31, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{ -1, -1, -1 },
	/* 25/32 */
};

static FuncSig func_sig_Fflush_Fut_3[] = {
	{   1, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{   2, 0xe0846020, 0xfdffffff }, // add:6:0xE2846020
	{   3, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   4, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBCB
	{   8, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   9, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001DEF
	{  11, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  12, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBFD
	{  14, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBD2
	{  16, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  19, 0xe4905004, 0xfdffffff }, // ldr:4:0xE4905004
	{  20, 0xe4906004, 0xfdffffff }, // ldr:4:0xE4906004
	{  21, 0xe5904000, 0xfdffffff }, // ldr:4:0xE5904000
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001E71
	{  23, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  24, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{  25, 0xe1a03006, 0xfdffffff }, // mov:6:0xE1A03006
	{  26, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  28, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFEBD
	{  31, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{ -1, -1, -1 },
	/* 24/32 */
};

static FuncSig func_sig_MakeDirectory_Fut_3[] = {
	{   1, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{   2, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC8C
	{   5, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   6, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC94
	{   8, 0xe1a01006, 0xfdffffff }, // mov:6:0xE1A01006
	{   9, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEB0
	{  11, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  12, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC92
	{  14, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  16, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  18, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC7D
	{  20, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  21, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEBA
	{  23, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  24, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  25, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC86
	{  26, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  28, 0xe59f3004, 0xfdffffff }, // ldr:4:0xE59F3004
	{  29, 0xe5930100, 0xfdffffff }, // ldr:4:0xE7930100
	{  30, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 27/32 */
};

static FuncSig func_sig_RenameFile_Fut_3[] = {
	{   1, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{   2, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCE3
	{   5, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   6, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCEB
	{   8, 0xe1a01006, 0xfdffffff }, // mov:6:0xE1A01006
	{   9, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFEC1
	{  11, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  12, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCE9
	{  14, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  17, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{  18, 0xe1a01002, 0xfdffffff }, // mov:6:0xE1A01002
	{  19, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCD3
	{  21, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  22, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  23, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  24, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCEE
	{  25, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  26, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  27, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCDB
	{  28, 0xe0144001, 0xfdffffff }, // and:6:0xE2144001
	{  29, 0xe1a00342, 0xfdffffff }, // mov:6:0xE3A00342
	{  30, 0xe0800505, 0xfdffffff }, // add:6:0xE2800505
	{ -1, -1, -1 },
	/* 28/32 */
};

static FuncSig func_sig_Remove_3[] = {
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA40E6
	{   4, 0xe0505000, 0xfdffffff }, // sub:6:0xE2505000
	{   5, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0002AA
	{   8, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{   9, 0xe1a0400d, 0xfdffffff }, // mov:6:0xE1A0400D
	{  10, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFB9
	{  12, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFD0
	{  14, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  16, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  17, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  19, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 17/32 */
};

FuncsList func_list[] = {
	{ "AllocateMemory", func_sig_AllocateMemory_1 },
	{ "AllocateMemory", func_sig_AllocateMemory_2 },
	{ "AllocateUncacheableMemory", func_sig_AllocateUncacheableMemory_1 },
	{ "Close", func_sig_Close_1 },
	{ "CreatePhysicalVram", func_sig_CreatePhysicalVram_1 },
	{ "CreatePhysicalVram", func_sig_CreatePhysicalVram_2 },
	{ "CreateTask", func_sig_CreateTask_1 },
	{ "CreateTaskStrict", func_sig_CreateTaskStrict_1 },
	{ "DeleteFile_Fut", func_sig_DeleteFile_Fut_1 },
	{ "DisableDispatch", func_sig_DisableDispatch_1 },
	{ "DisplayImagePhysicalScreen", func_sig_DisplayImagePhysicalScreen_1 },
	{ "DisplayImagePhysicalScreen", func_sig_DisplayImagePhysicalScreen_2 },
	{ "EnableDispatch", func_sig_EnableDispatch_1 },
	{ "ExecuteEventProcedure", func_sig_ExecuteEventProcedure_1 },
	{ "ExitTask", func_sig_ExitTask_1 },
	{ "Fclose_Fut", func_sig_Fclose_Fut_1 },
	{ "Fclose_Fut", func_sig_Fclose_Fut_3 },
	{ "Feof_Fut", func_sig_Feof_Fut_1 },
	{ "Feof_Fut", func_sig_Feof_Fut_3 },
	{ "Fflush_Fut", func_sig_Fflush_Fut_1 },
	{ "Fflush_Fut", func_sig_Fflush_Fut_3 },
	{ "Fgets_Fut", func_sig_Fgets_Fut_1 },
	{ "Fgets_Fut", func_sig_Fgets_Fut_3 },
	{ "Fopen_Fut", func_sig_Fopen_Fut_1 },
	{ "Fopen_Fut", func_sig_Fopen_Fut_3 },
	{ "Fread_Fut", func_sig_Fread_Fut_1 },
	{ "Fread_Fut", func_sig_Fread_Fut_3 },
	{ "FreeMemory", func_sig_FreeMemory_1 },
	{ "FreeMemory", func_sig_FreeMemory_2 },
	{ "FreeUncacheableMemory", func_sig_FreeUncacheableMemory_1 },
	{ "Fseek_Fut", func_sig_Fseek_Fut_1 },
	{ "Fseek_Fut", func_sig_Fseek_Fut_3 },
	{ "Fwrite_Fut", func_sig_Fwrite_Fut_1 },
	{ "Fwrite_Fut", func_sig_Fwrite_Fut_3 },
	{ "GetCurrentAvValue", func_sig_GetCurrentAvValue_1 },
	{ "GetCurrentAvValue", func_sig_GetCurrentAvValue_2 },
	{ "GetCurrentTargetDistance", func_sig_GetCurrentTargetDistance_1 },
	{ "GetFocusLensSubjectDistance", func_sig_GetFocusLensSubjectDistance_1 },
	{ "GetFocusLensSubjectDistance", func_sig_GetFocusLensSubjectDistance_2 },
	{ "GetFocusLensSubjectDistanceFromLens", func_sig_GetFocusLensSubjectDistanceFromLens_2 },
	{ "GetFocusLensSubjectDistanceFromLens", func_sig_GetFocusLensSubjectDistanceFromLens_3 },
	{ "GetParameterData", func_sig_GetParameterData_1 },
	{ "GetParameterData", func_sig_GetParameterData_2 },
	{ "GetPropertyCase", func_sig_GetPropertyCase_1 },
	{ "GetPropertyCase", func_sig_GetPropertyCase_2 },
	{ "GetSystemTime", func_sig_GetSystemTime_1 },
	{ "GetSystemTime", func_sig_GetSystemTime_2 },
	{ "GetZoomLensCurrentPoint", func_sig_GetZoomLensCurrentPoint_1 },
	{ "GetZoomLensCurrentPoint", func_sig_GetZoomLensCurrentPoint_2 },
	{ "GetZoomLensCurrentPosition", func_sig_GetZoomLensCurrentPosition_1 },
	{ "GetZoomLensCurrentPosition", func_sig_GetZoomLensCurrentPosition_2 },
	{ "IsStrobeChargeCompleted", func_sig_IsStrobeChargeCompleted_1 },
	{ "IsStrobeChargeCompleted", func_sig_IsStrobeChargeCompleted_2 },
	{ "LockMainPower", func_sig_LockMainPower_1 },
	{ "LockMainPower", func_sig_LockMainPower_2 },
	{ "MakeDirectory", func_sig_MakeDirectory_1 },
	{ "MakeDirectory_Fut", func_sig_MakeDirectory_Fut_1 },
	{ "MakeDirectory_Fut", func_sig_MakeDirectory_Fut_3 },
	{ "Mount_FileSystem", func_sig_Mount_FileSystem_1 },
	{ "Mount_FileSystem", func_sig_Mount_FileSystem_2 },
	{ "MoveFocusLensToDistance", func_sig_MoveFocusLensToDistance_1 },
	{ "MoveFocusLensToDistance", func_sig_MoveFocusLensToDistance_2 },
	{ "MoveZoomLensWithPoint", func_sig_MoveZoomLensWithPoint_1 },
	{ "MoveZoomLensWithPoint", func_sig_MoveZoomLensWithPoint_2 },
	{ "Open", func_sig_Open_1 },
	{ "PhySw_testgpio", func_sig_PhySw_testgpio_1 },
	{ "PhySw_testgpio", func_sig_PhySw_testgpio_2 },
	{ "ProtectFile", func_sig_ProtectFile_1 },
	{ "PutInNdFilter", func_sig_PutInNdFilter_1 },
	{ "PutInNdFilter", func_sig_PutInNdFilter_2 },
	{ "PutOutNdFilter", func_sig_PutOutNdFilter_1 },
	{ "PutOutNdFilter", func_sig_PutOutNdFilter_2 },
	{ "Read", func_sig_Read_1 },
	{ "RefreshPhysicalScreen", func_sig_RefreshPhysicalScreen_1 },
	{ "RefreshPhysicalScreen", func_sig_RefreshPhysicalScreen_2 },
	{ "Remove", func_sig_Remove_1 },
	{ "Remove", func_sig_Remove_3 },
	{ "RenameFile_Fut", func_sig_RenameFile_Fut_1 },
	{ "RenameFile_Fut", func_sig_RenameFile_Fut_3 },
	{ "SetAutoShutdownTime", func_sig_SetAutoShutdownTime_1 },
	{ "SetAutoShutdownTime", func_sig_SetAutoShutdownTime_2 },
	{ "SetParameterData", func_sig_SetParameterData_1 },
	{ "SetParameterData", func_sig_SetParameterData_2 },
	{ "SetPropertyCase", func_sig_SetPropertyCase_1 },
	{ "SetPropertyCase", func_sig_SetPropertyCase_2 },
	{ "SleepTask", func_sig_SleepTask_1 },
	{ "TakeSemaphore", func_sig_TakeSemaphore_1 },
	{ "TurnOffBackLight", func_sig_TurnOffBackLight_1 },
	{ "TurnOffBackLight", func_sig_TurnOffBackLight_2 },
	{ "TurnOnBackLight", func_sig_TurnOnBackLight_1 },
	{ "TurnOnBackLight", func_sig_TurnOnBackLight_2 },
	{ "UnlockMainPower", func_sig_UnlockMainPower_1 },
	{ "UnlockMainPower", func_sig_UnlockMainPower_2 },
	{ "Unmount_FileSystem", func_sig_Unmount_FileSystem_1 },
	{ "UnsetZoomForMovie", func_sig_UnsetZoomForMovie_1 },
	{ "UpdateMBROnFlash", func_sig_UpdateMBROnFlash_1 },
	{ "VbattGet", func_sig_VbattGet_1 },
	{ "VbattGet", func_sig_VbattGet_2 },
	{ "Write", func_sig_Write_1 },
	{ "_log", func_sig__log_1 },
	{ "_log", func_sig__log_2 },
	{ "_log10", func_sig__log10_1 },
	{ "_log10", func_sig__log10_2 },
	{ "_pow", func_sig__pow_1 },
	{ "_pow", func_sig__pow_2 },
	{ "_sqrt", func_sig__sqrt_1 },
	{ "_sqrt", func_sig__sqrt_2 },
	{ "chdir", func_sig_chdir_1 },
	{ "chdir", func_sig_chdir_2 },
	{ "close", func_sig_close_1 },
	{ "closedir", func_sig_closedir_1 },
	{ "errnoOfTaskGet", func_sig_errnoOfTaskGet_1 },
	{ "free", func_sig_free_1 },
	{ "free", func_sig_free_2 },
	{ "ints_disable", func_sig_ints_disable_1 },
	{ "ints_enable", func_sig_ints_enable_1 },
	{ "ioctl", func_sig_ioctl_1 },
	{ "iosDevAdd", func_sig_iosDevAdd_1 },
	{ "iosDevFind", func_sig_iosDevFind_1 },
	{ "iosDrvInstall", func_sig_iosDrvInstall_1 },
	{ "isalpha", func_sig_isalpha_1 },
	{ "isdigit", func_sig_isdigit_1 },
	{ "islower", func_sig_islower_1 },
	{ "ispunct", func_sig_ispunct_1 },
	{ "isspace", func_sig_isspace_1 },
	{ "isupper", func_sig_isupper_1 },
	{ "isxdigit", func_sig_isxdigit_1 },
	{ "kbd_p1_f", func_sig_kbd_p1_f_1 },
	{ "kbd_p1_f_cont", func_sig_kbd_p1_f_cont_1 },
	{ "kbd_p2_f", func_sig_kbd_p2_f_1 },
	{ "kbd_pwr_off", func_sig_kbd_pwr_off_1 },
	{ "kbd_pwr_on", func_sig_kbd_pwr_on_1 },
	{ "kbd_read_keys_r2", func_sig_kbd_read_keys_r2_1 },
	{ "localtime", func_sig_localtime_1 },
	{ "lseek", func_sig_lseek_1 },
	{ "malloc", func_sig_malloc_1 },
	{ "malloc", func_sig_malloc_2 },
	{ "memchr", func_sig_memchr_1 },
	{ "memcmp", func_sig_memcmp_1 },
	{ "memcpy", func_sig_memcpy_1 },
	{ "memset", func_sig_memset_1 },
	{ "mkdir", func_sig_mkdir_1 },
	{ "mktime", func_sig_mktime_1 },
	{ "open", func_sig_open_1 },
	{ "opendir", func_sig_opendir_1 },
	{ "qsort", func_sig_qsort_1 },
	{ "rand", func_sig_rand_1 },
	{ "rand", func_sig_rand_2 },
	{ "read", func_sig_read_1 },
	{ "readdir", func_sig_readdir_1 },
	{ "rename", func_sig_rename_1 },
	{ "rename", func_sig_rename_2 },
	{ "rewinddir", func_sig_rewinddir_1 },
	{ "srand", func_sig_srand_1 },
	{ "srand", func_sig_srand_2 },
	{ "stat", func_sig_stat_1 },
	{ "strcat", func_sig_strcat_1 },
	{ "strchr", func_sig_strchr_1 },
	{ "strcmp", func_sig_strcmp_1 },
	{ "strcpy", func_sig_strcpy_1 },
	{ "strftime", func_sig_strftime_1 },
	{ "strlen", func_sig_strlen_1 },
	{ "strncmp", func_sig_strncmp_1 },
	{ "strncpy", func_sig_strncpy_1 },
	{ "strncpy", func_sig_strncpy_2 },
	{ "strpbrk", func_sig_strpbrk_1 },
	{ "strrchr", func_sig_strrchr_1 },
	{ "strrchr", func_sig_strrchr_2 },
	{ "strtol", func_sig_strtol_1 },
	{ "taskCreateHookAdd", func_sig_taskCreateHookAdd_1 },
	{ "taskDeleteHookAdd", func_sig_taskDeleteHookAdd_1 },
	{ "taskIdListGet", func_sig_taskIdListGet_1 },
	{ "taskLock", func_sig_taskLock_1 },
	{ "taskName", func_sig_taskName_1 },
	{ "taskResume", func_sig_taskResume_1 },
	{ "taskSuspend", func_sig_taskSuspend_1 },
	{ "taskUnlock", func_sig_taskUnlock_1 },
	{ "time", func_sig_time_1 },
	{ "time", func_sig_time_2 },
	{ "tolower", func_sig_tolower_1 },
	{ "toupper", func_sig_toupper_1 },
	{ "utime", func_sig_utime_1 },
	{ "utime", func_sig_utime_2 },
	{ "vsprintf", func_sig_vsprintf_1 },
	{ "write", func_sig_write_1 },
	{ NULL }
};
