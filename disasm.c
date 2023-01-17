#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

int g_bHex = 1;
int g_bRegisterAliases = 0;

#define MAX_BUFFER 1024

//
static const char *regs[] = {"r0", "r1", "r2", "r3", "r4", "r5", "lr", "sp"};
static const char *ops[] = { "add", "addi", "nand", "lui", "sw", "lw", "beq", "jalr" };
//
typedef struct
{
	unsigned unused : 13;
	unsigned opcode : 3;
} Inst_type;

//
typedef struct
{
	unsigned regc : 3;
	unsigned unused : 4;
	unsigned regb : 3;
	unsigned rega : 3;
	unsigned opcode : 3;
} RRR_type;

//
typedef struct
{
	int imm7 : 7;
	unsigned regb : 3;
	unsigned rega : 3;
	unsigned opcode : 3;
} RRI_type;

//
typedef struct
{
	int imm10 : 10;
	unsigned rega : 3;
	unsigned opcode : 3;
} RI_type;

//
void usage()
{
	printf("\nusage: disasm filename\n\n");
	exit(0);
}

//
void diasm(int addr, unsigned short val)
{
	unsigned opcode = val >> 13;
	RRR_type *rrr = (RRR_type*)&val;
	RRI_type *rri = (RRI_type*)&val;
	RI_type *ri = (RI_type*)&val;
//	Inst_type *inst = (Inst_type*)&val;

	switch (opcode)
	{
	case 0:
	case 2:
		printf("%04X\t%04X\t%s\t%s, %s, %s\n", addr, val, ops[opcode], regs[rrr->rega], regs[rrr->regb], regs[rrr->regc]);
		break;

	case 1:
	case 4:
	case 5:
		printf("%04X\t%04X\t%s\t%s, %s, $%02x\t# decimal %d\n", addr, val, ops[opcode], regs[rri->rega], regs[rri->regb], rri->imm7, rri->imm7);
		break;

	case 6:
		printf("%04X\t%04X\t%s\t%s, %s, %d\t# dest addr %04x\n", addr, val, ops[opcode], regs[rri->rega], regs[rri->regb], rri->imm7, addr + 1 + rri->imm7);
		break;

	case 3:
		printf("%04X\t%04X\t%s\t%s, $%02x\t\t# decimal %d\n", addr, val, ops[opcode], regs[ri->rega], ri->imm10, ri->imm10);
		break;

	case 7:
		printf("%04X\t%04X\t%s\t%s, %s\n", addr, val, ops[opcode], regs[rri->rega], regs[rri->regb]);
		break;

	default:
		printf("%04X\t%04X\t%s\t%04X\n", addr, val, "dw", val);
	}
}

//
void decode(FILE *f)
{
	char buf[MAX_BUFFER];
	char *s;
	int num;
	int addr = 0;

	// read a line
	while (fgets(buf, MAX_BUFFER - 1, f)) {
		// tokenize the line
		s = strtok(buf, "\t ");

		while (s) {
			if (g_bHex)
			{
				// parse hex numbers
				if (isxdigit(s[0])) {
					num = strtol(s, NULL, 16);
					diasm(addr, num);
				}
			}
			else
			{
				// parse decimal numbers
				if (isdigit(s[0])) {
					num = atoi(s);
					diasm(addr, num);
				}
			}

			addr++;
			s = strtok(NULL, "\t ");
		}
	}
}

//
int main(int argc, char *argv[])
{
	if (argc < 2)
		usage();

	FILE *f = fopen(argv[1], "rt");

	printf(
		"\nRiSC-16 processor disassembler\n\n"
		"addr\tinst\tdisassembly\n"
		"----\t----\t-----------\n"
	);

	decode(f);
	
	fclose(f);

	return 0;
}