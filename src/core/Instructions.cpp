//
// Created by matthew on 05/07/2020.
//

#include "Instructions.h"
#include "CPU.h"
#include "Bytes.h"

const instructionInfo CORE_INSTRUCTION_INFO[256] = {
        {1, 4, 0, "NOP"},
        {3, 12, 0, "LD BC,nn"},
        {1, 8, 0, "LD BC,A"},
        {1, 8, 0, "INC BC"},
        {1, 4, 0, "INC B"},
        {1, 4, 0, "DEC B"},
        {2, 8, 0, "LD B,n"},
        {1, 4, 0, "RLCA"},
        {3, 20, 0, "LD (nn),SP"},
        {1, 8, 0, "ADD HL,BC"},
        {1, 8, 0, "LD A,BC"},
        {1, 8, 0, "DEC BC"},
        {1, 4, 0, "INC C"},
        {1, 4, 0, "DEC C"},
        {2, 8, 0, "LD C,n"},
        {1, 4, 0, "RRCA"},
        {1, 0, 0, "STOP 0"},
        {3, 12, 0, "LD DE,nn"},
        {1, 8, 0, "LD (DE),A"},
        {1, 8, 0, "INC DE"},
        {1, 4, 0, "INC D"},
        {1, 4, 0, "DEC D"},
        {2, 8, 0, "LD D,n"},
        {1, 4, 0, "RLA"},
        {2, 12, 0, "JR n"},
        {1, 8, 0, "ADD HL,DE"},
        {1, 8, 0, "LD A,(DE)"},
        {1, 8, 0, "DEC DE"},
        {1, 4, 0, "INC E"},
        {1, 4, 0, "DEC E"},
        {2, 8, 0, "LD E,n"},
        {1, 4, 0, "RRA"},
        {2, 12, 8, "JR NZ,n"},
        {3, 12, 0, "LD HL,nn"},
        {1, 8, 0, "LD (HL+),A"},
        {1, 8, 0, "INC HL"},
        {1, 4, 0, "INC H"},
        {1, 4, 0, "DEC H"},
        {2, 8, 0, "LD H,n"},
        {1, 4, 0, "DAA"},
        {2, 12, 8, "JR Z,n"},
        {1, 8, 0, "ADD HL,HL"},
        {1, 8, 0, "LD A,(HL+)"},
        {1, 8, 0, "DEC HL"},
        {1, 4, 0, "INC L"},
        {1, 4, 0, "DEC L"},
        {2, 8, 0, "LD L,n"},
        {1, 4, 0, "CPL"},
        {2, 12, 8, "JR NC,n"},
        {3, 12, 0, "LD SP,nn"},
        {1, 8, 0, "LD (HL-),A"},
        {1, 8, 0, "INC SP"},
        {1, 12, 0, "INC (HL)"},
        {1, 12, 0, "DEC (HL)"},
        {2, 12, 0, "LD (HL),n"},
        {1, 4, 0, "SCF"},
        {2, 12, 8, "JR C,n"},
        {1, 8, 0, "ADD HL,SP"},
        {1, 8, 0, "LD A,(HL-)"},
        {1, 8, 0, "DEC SP"},
        {1, 4, 0, "INC A"},
        {1, 4, 0, "DEC A"},
        {2, 8, 0, "LD A,n"},
        {1, 4, 0, "CCF"},
        {1, 4, 0, "LD B,B"},
        {1, 4, 0, "LD B,C"},
        {1, 4, 0, "LD B,D"},
        {1, 4, 0, "LD B,E"},
        {1, 4, 0, "LD B,H"},
        {1, 4, 0, "LD B,L"},
        {1, 8, 0, "LD B,(HL)"},
        {1, 4, 0, "LD B,A"},
        {1, 4, 0, "LD C,B"},
        {1, 4, 0, "LD C,C"},
        {1, 4, 0, "LD C,D"},
        {1, 4, 0, "LD C,E"},
        {1, 4, 0, "LD C,H"},
        {1, 4, 0, "LD C,L"},
        {1, 8, 0, "LD C,(HL)"},
        {1, 4, 0, "LD C,A"},
        {1, 4, 0, "LD D,B"},
        {1, 4, 0, "LD D,C"},
        {1, 4, 0, "LD D,D"},
        {1, 4, 0, "LD D,E"},
        {1, 4, 0, "LD D,H"},
        {1, 4, 0, "LD D,L"},
        {1, 8, 0, "LD D,(HL)"},
        {1, 4, 0, "LD D,A"},
        {1, 4, 0, "LD E,B"},
        {1, 4, 0, "LD E,C"},
        {1, 4, 0, "LD E,D"},
        {1, 4, 0, "LD E,E"},
        {1, 4, 0, "LD E,H"},
        {1, 4, 0, "LD E,L"},
        {1, 8, 0, "LD E,(HL)"},
        {1, 4, 0, "LD E,A"},
        {1, 4, 0, "LD H,B"},
        {1, 4, 0, "LD H,C"},
        {1, 4, 0, "LD H,D"},
        {1, 4, 0, "LD H,E"},
        {1, 4, 0, "LD H,H"},
        {1, 4, 0, "LD H,L"},
        {1, 8, 0, "LD H,(HL)"},
        {1, 4, 0, "LD H,A"},
        {1, 4, 0, "LD L,B"},
        {1, 4, 0, "LD L,C"},
        {1, 4, 0, "LD L,D"},
        {1, 4, 0, "LD L,E"},
        {1, 4, 0, "LD L,H"},
        {1, 4, 0, "LD L,L"},
        {1, 8, 0, "LD L,(HL)"},
        {1, 4, 0, "LD L,A"},
        {1, 8, 0, "LD (HL),B"},
        {1, 8, 0, "LD (HL),C"},
        {1, 8, 0, "LD (HL),D"},
        {1, 8, 0, "LD (HL),E"},
        {1, 8, 0, "LD (HL),H"},
        {1, 8, 0, "LD (HL),L"},
        {1, 0, 0, "HALT"},
        {1, 8, 0, "LD (HL),A"},
        {1, 4, 0, "LD A,B"},
        {1, 4, 0, "LD A,C"},
        {1, 4, 0, "LD A,D"},
        {1, 4, 0, "LD A,E"},
        {1, 4, 0, "LD A,H"},
        {1, 4, 0, "LD A,L"},
        {1, 8, 0, "LD A,(HL)"},
        {1, 4, 0, "LD A,A"},
        {1, 4, 0, "ADD A,B"},
        {1, 4, 0, "ADD A,C"},
        {1, 4, 0, "ADD A,D"},
        {1, 4, 0, "ADD A,E"},
        {1, 4, 0, "ADD A,H"},
        {1, 4, 0, "ADD A,L"},
        {1, 8, 0, "ADD A,(HL)"},
        {1, 4, 0, "ADD A,A"},
        {1, 4, 0, "ADC A,B"},
        {1, 4, 0, "ADC A,C"},
        {1, 4, 0, "ADC A,D"},
        {1, 4, 0, "ADC A,E"},
        {1, 4, 0, "ADC A,H"},
        {1, 4, 0, "ADC A,L"},
        {1, 8, 0, "ADC A,(HL)"},
        {1, 4, 0, "ADC A,A"},
        {1, 4, 0, "SUB B"},
        {1, 4, 0, "SUB C"},
        {1, 4, 0, "SUB D"},
        {1, 4, 0, "SUB E"},
        {1, 4, 0, "SUB H"},
        {1, 4, 0, "SUB L"},
        {1, 8, 0, "SUB (HL)"},
        {1, 4, 0, "SUB A"},
        {1, 4, 0, "SBC A,B"},
        {1, 4, 0, "SBC A,C"},
        {1, 4, 0, "SBC A,D"},
        {1, 4, 0, "SBC A,E"},
        {1, 4, 0, "SBC A,H"},
        {1, 4, 0, "SBC A,L"},
        {1, 8, 0, "SBC A,(HL)"},
        {1, 4, 0, "SBC A,A"},
        {1, 4, 0, "AND B"},
        {1, 4, 0, "AND C"},
        {1, 4, 0, "AND D"},
        {1, 4, 0, "AND E"},
        {1, 4, 0, "AND H"},
        {1, 4, 0, "AND L"},
        {1, 8, 0, "AND (HL)"},
        {1, 4, 0, "AND A"},
        {1, 4, 0, "XOR B"},
        {1, 4, 0, "XOR C"},
        {1, 4, 0, "XOR D"},
        {1, 4, 0, "XOR E"},
        {1, 4, 0, "XOR H"},
        {1, 4, 0, "XOR L"},
        {1, 8, 0, "XOR (HL)"},
        {1, 4, 0, "XOR A"},
        {1, 4, 0, "OR B"},
        {1, 4, 0, "OR C"},
        {1, 4, 0, "OR D"},
        {1, 4, 0, "OR E"},
        {1, 4, 0, "OR H"},
        {1, 4, 0, "OR L"},
        {1, 8, 0, "OR (HL)"},
        {1, 4, 0, "OR A"},
        {1, 4, 0, "CP B"},
        {1, 4, 0, "CP C"},
        {1, 4, 0, "CP D"},
        {1, 4, 0, "CP E"},
        {1, 4, 0, "CP H"},
        {1, 4, 0, "CP L"},
        {1, 8, 0, "CP (HL)"},
        {1, 4, 0, "CP A"},
        {1, 20, 8, "RET NZ"},
        {1, 12, 0, "POP BC"},
        {3, 16, 12, "JP NZ,nn"},
        {3, 16, 0, "JP nn"},
        {3, 24, 12, "CALL NZ,nn"},
        {1, 16, 0, "PUSH BC"},
        {2, 8, 0, "ADD A,n"},
        {1, 16, 0, "RST 00H"},
        {1, 20, 8, "RET Z"},
        {1, 16, 0, "RET"},
        {3, 16, 12, "JP Z,nn"},
        {3, 0, 0, "JP Z,nn"},
        {3, 24, 12, "CALL Z,nn"},
        {3, 24, 0, "CALL nn"},
        {2, 8, 0, "ADC A,n"},
        {1, 16, 0, "RST 08H"},
        {1, 20, 8, "RET NC"},
        {1, 12, 0, "POP DE"},
        {3, 16, 12, "JP NC,nn"},
        {0, 0, 0, "NO INSTRUCTION"},
        {3, 24, 12, "CALL NC,nn"},
        {1, 16, 0, "PUSH DE"},
        {2, 8, 0, "SUB n"},
        {1, 16, 0, "RST 10H"},
        {1, 20, 8, "RET C"},
        {1, 16, 0, "RETI"},
        {3, 16, 12, "JP C,nn"},
        {0, 0, 0, "NO INSTRUCTION"},
        {3, 24, 12, "CALL C,nn"},
        {0, 0, 0, "NO INSTRUCTION"},
        {2, 8, 0, "SBC A,n"},
        {1, 16, 0, "RST 18H"},
        {2, 12, 0, "LDH (n),A"},
        {1, 12, 0, "POP HL"},
        {1, 8, 0, "LD (C),A"},
        {0, 0, 0, "NO INSTRUCTION"},
        {0, 0, 0, "NO INSTRUCTION"},
        {1, 16, 0, "PUSH HL"},
        {2, 8, 0, "AND n"},
        {1, 16, 0, "RST 20H"},
        {2, 16, 0, "ADD SP,n"},
        {1, 4, 0, "JP (HL)"},
        {3, 16, 0, "LD (nn),A"},
        {0, 0, 0, "NO INSTRUCTION"},
        {0, 0, 0, "NO INSTRUCTION"},
        {0, 0, 0, "NO INSTRUCTION"},
        {2, 8, 0, "XOR n"},
        {1, 16, 0, "RST 28H"},
        {2, 12, 0, "LDH A,(n)"},
        {1, 12, 0, "POP AF"},
        {1, 8, 0, "LD A,(C)"},
        {1, 4, 0, "DI"},
        {0, 0, 0, "NO INSTRUCTION"},
        {1, 16, 0, "PUSH AF"},
        {2, 8, 0, "OR n"},
        {1, 16, 0, "RST 30H"},
        {2, 12, 0, "LD HL,SP+n"},
        {1, 8, 0, "LD SP,HL"},
        {3, 16, 0, "LD A,(nn)"},
        {1, 4, 0, "EI"},
        {0, 0, 0, "NO INSTRUCTION"},
        {0, 0, 0, "NO INSTRUCTION"},
        {2, 8, 0, "CP n"},
        {1, 16, 0, "RST 38H"}
};

const instructionInfo CB_INSTRUCTION_INFO[256] = {
        {2, 8, 0, "NOP"},
        {2, 8, 0, "LD BC,nn"},
        {2, 8, 0, "LD BC,A"},
        {2, 8, 0, "INC BC"},
        {2, 8, 0, "INC B"},
        {2, 8, 0, "DEC B"},
        {2, 16, 0, "LD B,n"},
        {2, 8, 0, "RLCA"},
        {2, 8, 0, "LD (nn),SP"},
        {2, 8, 0, "ADD HL,BC"},
        {2, 8, 0, "LD A,BC"},
        {2, 8, 0, "DEC BC"},
        {2, 8, 0, "INC C"},
        {2, 8, 0, "DEC C"},
        {2, 16, 0, "LD C,n"},
        {2, 8, 0, "RRCA"},
        {2, 8, 0, "STOP 0"},
        {2, 8, 0, "LD DE,nn"},
        {2, 8, 0, "LD (DE),A"},
        {2, 8, 0, "INC DE"},
        {2, 8, 0, "INC D"},
        {2, 8, 0, "DEC D"},
        {2, 16, 0, "LD D,n"},
        {2, 8, 0, "RLA"},
        {2, 8, 0, "JR n"},
        {2, 8, 0, "ADD HL,DE"},
        {2, 8, 0, "LD A,(DE)"},
        {2, 8, 0, "DEC DE"},
        {2, 8, 0, "INC E"},
        {2, 8, 0, "DEC E"},
        {2, 16, 0, "LD E,n"},
        {2, 8, 0, "RRA"},
        {2, 8, 0, "JR NZ,n"},
        {2, 8, 0, "LD HL,nn"},
        {2, 8, 0, "LD (HL+),A"},
        {2, 8, 0, "INC HL"},
        {2, 8, 0, "INC H"},
        {2, 8, 0, "DEC H"},
        {2, 16, 0, "LD H,n"},
        {2, 8, 0, "DAA"},
        {2, 8, 0, "JR Z,n"},
        {2, 8, 0, "ADD HL,HL"},
        {2, 8, 0, "LD A,(HL+)"},
        {2, 8, 0, "DEC HL"},
        {2, 8, 0, "INC L"},
        {2, 8, 0, "DEC L"},
        {2, 16, 0, "LD L,n"},
        {2, 8, 0, "CPL"},
        {2, 8, 0, "JR NC,n"},
        {2, 8, 0, "LD SP,nn"},
        {2, 8, 0, "LD (HL-),A"},
        {2, 8, 0, "INC SP"},
        {2, 8, 0, "INC (HL)"},
        {2, 8, 0, "DEC (HL)"},
        {2, 16, 0, "LD (HL),n"},
        {2, 8, 0, "SCF"},
        {2, 8, 0, "JR C,n"},
        {2, 8, 0, "ADD HL,SP"},
        {2, 8, 0, "LD A,(HL-)"},
        {2, 8, 0, "DEC SP"},
        {2, 8, 0, "INC A"},
        {2, 8, 0, "DEC A"},
        {2, 16, 0, "LD A,n"},
        {2, 8, 0, "CCF"},
        {2, 8, 0, "LD B,B"},
        {2, 8, 0, "LD B,C"},
        {2, 8, 0, "LD B,D"},
        {2, 8, 0, "LD B,E"},
        {2, 8, 0, "LD B,H"},
        {2, 8, 0, "LD B,L"},
        {2, 12, 0, "LD B,(HL)"},
        {2, 8, 0, "LD B,A"},
        {2, 8, 0, "LD C,B"},
        {2, 8, 0, "LD C,C"},
        {2, 8, 0, "LD C,D"},
        {2, 8, 0, "LD C,E"},
        {2, 8, 0, "LD C,H"},
        {2, 8, 0, "LD C,L"},
        {2, 12, 0, "LD C,(HL)"},
        {2, 8, 0, "LD C,A"},
        {2, 8, 0, "LD D,B"},
        {2, 8, 0, "LD D,C"},
        {2, 8, 0, "LD D,D"},
        {2, 8, 0, "LD D,E"},
        {2, 8, 0, "LD D,H"},
        {2, 8, 0, "LD D,L"},
        {2, 12, 0, "LD D,(HL)"},
        {2, 8, 0, "LD D,A"},
        {2, 8, 0, "LD E,B"},
        {2, 8, 0, "LD E,C"},
        {2, 8, 0, "LD E,D"},
        {2, 8, 0, "LD E,E"},
        {2, 8, 0, "LD E,H"},
        {2, 8, 0, "LD E,L"},
        {2, 12, 0, "LD E,(HL)"},
        {2, 8, 0, "LD E,A"},
        {2, 8, 0, "LD H,B"},
        {2, 8, 0, "LD H,C"},
        {2, 8, 0, "LD H,D"},
        {2, 8, 0, "LD H,E"},
        {2, 8, 0, "LD H,H"},
        {2, 8, 0, "LD H,L"},
        {2, 12, 0, "LD H,(HL)"},
        {2, 8, 0, "LD H,A"},
        {2, 8, 0, "LD L,B"},
        {2, 8, 0, "LD L,C"},
        {2, 8, 0, "LD L,D"},
        {2, 8, 0, "LD L,E"},
        {2, 8, 0, "LD L,H"},
        {2, 8, 0, "LD L,L"},
        {2, 12, 0, "LD L,(HL)"},
        {2, 8, 0, "LD L,A"},
        {2, 8, 0, "LD (HL),B"},
        {2, 8, 0, "LD (HL),C"},
        {2, 8, 0, "LD (HL),D"},
        {2, 8, 0, "LD (HL),E"},
        {2, 8, 0, "LD (HL),H"},
        {2, 8, 0, "LD (HL),L"},
        {2, 12, 0, "HALT"},
        {2, 8, 0, "LD (HL),A"},
        {2, 8, 0, "LD A,B"},
        {2, 8, 0, "LD A,C"},
        {2, 8, 0, "LD A,D"},
        {2, 8, 0, "LD A,E"},
        {2, 8, 0, "LD A,H"},
        {2, 8, 0, "LD A,L"},
        {2, 12, 0, "LD A,(HL)"},
        {2, 8, 0, "LD A,A"},
        {2, 8, 0, "ADD A,B"},
        {2, 8, 0, "ADD A,C"},
        {2, 8, 0, "ADD A,D"},
        {2, 8, 0, "ADD A,E"},
        {2, 8, 0, "ADD A,H"},
        {2, 8, 0, "ADD A,L"},
        {2, 16, 0, "ADD A,(HL)"},
        {2, 8, 0, "ADD A,A"},
        {2, 8, 0, "ADC A,B"},
        {2, 8, 0, "ADC A,C"},
        {2, 8, 0, "ADC A,D"},
        {2, 8, 0, "ADC A,E"},
        {2, 8, 0, "ADC A,H"},
        {2, 8, 0, "ADC A,L"},
        {2, 16, 0, "ADC A,(HL)"},
        {2, 8, 0, "ADC A,A"},
        {2, 8, 0, "SUB B"},
        {2, 8, 0, "SUB C"},
        {2, 8, 0, "SUB D"},
        {2, 8, 0, "SUB E"},
        {2, 8, 0, "SUB H"},
        {2, 8, 0, "SUB L"},
        {2, 16, 0, "SUB (HL)"},
        {2, 8, 0, "SUB A"},
        {2, 8, 0, "SBC A,B"},
        {2, 8, 0, "SBC A,C"},
        {2, 8, 0, "SBC A,D"},
        {2, 8, 0, "SBC A,E"},
        {2, 8, 0, "SBC A,H"},
        {2, 8, 0, "SBC A,L"},
        {2, 16, 0, "SBC A,(HL)"},
        {2, 8, 0, "SBC A,A"},
        {2, 8, 0, "AND B"},
        {2, 8, 0, "AND C"},
        {2, 8, 0, "AND D"},
        {2, 8, 0, "AND E"},
        {2, 8, 0, "AND H"},
        {2, 8, 0, "AND L"},
        {2, 16, 0, "AND (HL)"},
        {2, 8, 0, "AND A"},
        {2, 8, 0, "XOR B"},
        {2, 8, 0, "XOR C"},
        {2, 8, 0, "XOR D"},
        {2, 8, 0, "XOR E"},
        {2, 8, 0, "XOR H"},
        {2, 8, 0, "XOR L"},
        {2, 16, 0, "XOR (HL)"},
        {2, 8, 0, "XOR A"},
        {2, 8, 0, "OR B"},
        {2, 8, 0, "OR C"},
        {2, 8, 0, "OR D"},
        {2, 8, 0, "OR E"},
        {2, 8, 0, "OR H"},
        {2, 8, 0, "OR L"},
        {2, 16, 0, "OR (HL)"},
        {2, 8, 0, "OR A"},
        {2, 8, 0, "CP B"},
        {2, 8, 0, "CP C"},
        {2, 8, 0, "CP D"},
        {2, 8, 0, "CP E"},
        {2, 8, 0, "CP H"},
        {2, 8, 0, "CP L"},
        {2, 16, 0, "CP (HL)"},
        {2, 8, 0, "CP A"},
        {2, 8, 0, "RET NZ"},
        {2, 8, 0, "POP BC"},
        {2, 8, 0, "JP NZ,nn"},
        {2, 8, 0, "JP nn"},
        {2, 8, 0, "CALL NZ,nn"},
        {2, 8, 0, "PUSH BC"},
        {2, 16, 0, "ADD A,n"},
        {2, 8, 0, "RST 00H"},
        {2, 8, 0, "RET Z"},
        {2, 8, 0, "RET"},
        {2, 8, 0, "JP Z,nn"},
        {2, 8, 0, "CB"},
        {2, 8, 0, "CALL Z,nn"},
        {2, 8, 0, "CALL nn"},
        {2, 16, 0, "ADC A,n"},
        {2, 8, 0, "RST 08H"},
        {2, 8, 0, "RET NC"},
        {2, 8, 0, "POP DE"},
        {2, 8, 0, "JP NC,nn"},
        {2, 8, 0, "NO INSTRUCTION"},
        {2, 8, 0, "CALL NC,nn"},
        {2, 8, 0, "PUSH DE"},
        {2, 16, 0, "SUB n"},
        {2, 8, 0, "RST 10H"},
        {2, 8, 0, "RET C"},
        {2, 8, 0, "RETI"},
        {2, 8, 0, "JP C,nn"},
        {2, 8, 0, "NO INSTRUCTION"},
        {2, 8, 0, "CALL C,nn"},
        {2, 8, 0, "NO INSTRUCTION"},
        {2, 16, 0, "SBC A,n"},
        {2, 8, 0, "RST 18H"},
        {2, 8, 0, "LDH (n),A"},
        {2, 8, 0, "POP HL"},
        {2, 8, 0, "LD (C),A"},
        {2, 8, 0, "NO INSTRUCTION"},
        {2, 8, 0, "NO INSTRUCTION"},
        {2, 8, 0, "PUSH HL"},
        {2, 16, 0, "AND n"},
        {2, 8, 0, "RST 20H"},
        {2, 8, 0, "ADD SP,n"},
        {2, 8, 0, "JP (HL)"},
        {2, 8, 0, "LD (nn),A"},
        {2, 8, 0, "NO INSTRUCTION"},
        {2, 8, 0, "NO INSTRUCTION"},
        {2, 8, 0, "NO INSTRUCTION"},
        {2, 16, 0, "XOR n"},
        {2, 8, 0, "RST 28H"},
        {2, 8, 0, "LDH A,(n)"},
        {2, 8, 0, "POP AF"},
        {2, 8, 0, "LD A,(C)"},
        {2, 8, 0, "DI"},
        {2, 8, 0, "NO INSTRUCTION"},
        {2, 8, 0, "PUSH AF"},
        {2, 16, 0, "OR n"},
        {2, 8, 0, "RST 30H"},
        {2, 8, 0, "LD HL,SP+n"},
        {2, 8, 0, "LD SP,HL"},
        {2, 8, 0, "LD A,(nn)"},
        {2, 8, 0, "EI"},
        {2, 8, 0, "NO INSTRUCTION"},
        {2, 8, 0, "NO INSTRUCTION"},
        {2, 16, 0, "CP n"},
        {2, 8, 0, "RST 38H"}
};

static void rotate_right_r8(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    bool lsb = Bytes::getBit_8(value, 0);
    bool carry = cpu->flag_c;
    uint8 new_value = value >> 1;
    
    if (carry) {
        new_value = new_value | 128;
    }

    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = false;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = lsb;
}

static void rotate_right_r8_cb(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    bool lsb = Bytes::getBit_8(value, 0);
    bool carry = cpu->flag_c;
    uint8 new_value = value >> 1;

    if (carry) {
        new_value = new_value | 128;
    }

    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = lsb;
}

static void rotate_right_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    bool lsb = Bytes::getBit_8(value, 0);
    bool carry = cpu->flag_c;
    uint8 new_value = value >> 1;

    if (carry) {
        new_value = new_value | 128;
    }

    memory->set_8(address, new_value & 0xFF);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = lsb;
}

static void load_increment_r16_r8(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint8 value = cpu->get_8(cpuRegister_2);
    uint16 address = cpu->get_16(cpuRegister_1);
    memory->set_8(address, value);
    cpu->set_16(cpuRegister_1, Bytes::wrappingAdd_16(address, 1));
}

static void load_increment_r8_ar16(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint16 address = cpu->get_16(cpuRegister_2);
    uint8 value = memory->get_8(address);
    cpu->set_8(cpuRegister_1, value);
    cpu->set_16(cpuRegister_2, Bytes::wrappingAdd_16(address, 1));
}

static void load_decrement_r8_ar16(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint16 address = cpu->get_16(cpuRegister_2);
    uint8 value = memory->get_8(address);
    cpu->set_8(cpuRegister_1, value);
    cpu->set_16(cpuRegister_2, Bytes::wrappingSub_16(address, 1));
}

static void decimal_r8(CPU* cpu, Register cpuRegister) {
    uint16 value = cpu->get_8(cpuRegister);

    if (!cpu->flag_n) {
        if (cpu->flag_h || (value & 0x0F) > 0x9) {
            value += 0x6;
        }
        if (cpu->flag_c || value > 0x9F) {
            value += 0x60;
        }
    } else {
        if (cpu->flag_h) {
            value -= 0x6;
            if (!cpu->flag_c) {
                value &= 0xFF;
            }
        }
        if (cpu->flag_c) {
            value -= 0x60;
        }
    }

    cpu->flag_h = false;

    if (value > 0xFF) {
        cpu->flag_c = true;
    }

    value &= 0xFF;

    cpu->flag_z = value == 0;

    cpu->set_8(cpuRegister, value);
}

static void complement_r8(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    uint8 new_value = value ^ 0xFF;
    cpu->set_8(cpuRegister, new_value);

    cpu->flag_n = true;
    cpu->flag_h = true;
}

static void load_sp_n16(CPU* cpu, uint16 value) {
    cpu->sp = value;
}

static void swap_r8(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    uint8 upper = Bytes::split_8_upper(value);
    uint8 lower = Bytes::split_8_lower(value);
    uint8 new_value = Bytes::join_4(lower, upper);
    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = false;
}

static void swap_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    uint8 upper = Bytes::split_8_upper(value);
    uint8 lower = Bytes::split_8_lower(value);
    uint8 new_value = Bytes::join_4(lower, upper);
    memory->set_8(address, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = false;
}

static void shift_left_r8(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    bool hsb = Bytes::getBit_8(value, 7);
    uint8 new_value = (value << 1) & 0xFF;
    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = hsb;
}

static void shift_left_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    bool hsb = Bytes::getBit_8(value, 7);
    uint8 new_value = (value << 1) & 0xFF;
    memory->set_8(address, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = hsb;
}

static void shift_right_r8(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    bool lsb = Bytes::getBit_8(value, 0);
    uint8 new_value = value >> 1;
    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = lsb;
}

static void shift_right_weird_r8(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    bool msb = Bytes::getBit_8(value, 7);
    bool lsb = Bytes::getBit_8(value, 0);
    uint8 new_value = value >> 1;

    if (msb) {
        new_value = Bytes::setBit_8(new_value, 7);
    }

    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = lsb;
}

static void shift_right_weird_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    bool msb = Bytes::getBit_8(value, 7);
    bool lsb = Bytes::getBit_8(value, 0);
    uint8 new_value = value >> 1;

    if (msb) {
        new_value = Bytes::setBit_8(new_value, 7);
    }

    memory->set_8(address, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = lsb;
}

static void shift_right_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    bool lsb = Bytes::getBit_8(value, 0);
    uint8 new_value = value >> 1;
    memory->set_8(address, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = lsb;
}

static void bit_8(CPU* cpu, uint8 value, uint8 bit) {
    bool set = Bytes::getBit_8(value, bit);

    cpu->flag_z = !set;
    cpu->flag_n = false;
    cpu->flag_h = true;
}

static void bit_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister, uint8 bit) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    bit_8(cpu, value, bit);
}

static void bit_r8(CPU* cpu, Register cpuRegister, uint8 bit) {
    uint8 value = cpu->get_8(cpuRegister);
    bit_8(cpu, value, bit);
}

static void reset_r8(CPU* cpu, Register cpuRegister, uint8 bit) {
    uint8 value = cpu->get_8(cpuRegister);
    uint8 new_value = Bytes::clearBit_8(value, bit);
    cpu->set_8(cpuRegister, new_value);
}

static void reset_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister, uint8 bit) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    uint8 new_value = Bytes::clearBit_8(value, bit);
    memory->set_8(address, new_value);
}

static void set_r8(CPU* cpu, Register cpuRegister, uint8 bit) {
    uint8 value = cpu->get_8(cpuRegister);
    uint8 new_value = Bytes::setBit_8(value, bit);
    cpu->set_8(cpuRegister, new_value);
}

static void set_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister, uint8 bit) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    uint8 new_value = Bytes::setBit_8(value, bit);
    memory->set_8(address, new_value);
}

static void increment_sp(CPU* cpu) {
    cpu->sp = Bytes::wrappingAdd_16(cpu->sp, 1);
}

static void set_carry(CPU* cpu) {
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = true;
}

static void rotate_left_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    bool carry = cpu->flag_c;
    bool msb = Bytes::getBit_8(value, 7);
    uint8 new_value = ((value) << 1) & 0xFF;

    if (carry) {
        new_value = new_value + 0x1;
    }

    memory->set_8(address, new_value & 0xFF);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = msb;
}

static void rotate_left_r8(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    bool carry = cpu->flag_c;
    bool msb = Bytes::getBit_8(value, 7);
    uint8 new_value = ((value) << 1) & 0xFF;

    if (carry) {
        new_value = new_value + 0x1;
    }

    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = false;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = msb;
}

static void rotate_left_r8_cb(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    bool carry = cpu->flag_c;
    bool msb = Bytes::getBit_8(value, 7);
    uint8 new_value = ((value) << 1) & 0xFF;

    if (carry) {
        new_value = new_value + 0x1;
    }

    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = msb;
}

static void rotate_left_carry_r8(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    bool msb = Bytes::getBit_8(value, 7);
    uint8 new_value = Bytes::rotateLeft_8(value, 1);

    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = false;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = msb;
}

static void rotate_left_carry_r8_cb(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    bool msb = Bytes::getBit_8(value, 7);
    uint8 new_value = Bytes::rotateLeft_8(value, 1);

    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = msb;
}

static void rotate_left_carry_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    bool msb = Bytes::getBit_8(value, 7);
    uint8 new_value = Bytes::rotateLeft_8(value, 1);

    memory->set_8(address, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = msb;
}

static void rotate_right_carry_r8(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    bool lsb = Bytes::getBit_8(value, 0);
    uint8 new_value = Bytes::rotateRight_8(value, 1);

    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = false;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = lsb;
}

static void rotate_right_carry_r8_cb(CPU* cpu, Register cpuRegister) {
    uint8 value = cpu->get_8(cpuRegister);
    bool lsb = Bytes::getBit_8(value, 0);
    uint8 new_value = Bytes::rotateRight_8(value, 1);

    cpu->set_8(cpuRegister, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = lsb;
}

static void rotate_right_carry_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    bool lsb = Bytes::getBit_8(value, 0);
    uint8 new_value = Bytes::rotateRight_8(value,1 );

    memory->set_8(address, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = lsb;
}

static void disable_interrupts(CPU* cpu) {
    cpu->interruptsEnabled = false;
}

static void enable_interrupts(CPU* cpu) {
    cpu->interruptsEnabled = true;
}

static void load_r16_sp_n8(CPU* cpu, Register cpuRegister, uint8 value) {
    int16 signed_value = Bytes::toSigned_8(value);
    uint16 new_value = Bytes::wrappingSub_16(Bytes::wrappingAdd_16(cpu->sp, signed_value), 0);
    cpu->set_16(cpuRegister, new_value);

    cpu->flag_z = false;
    cpu->flag_n = false;
    cpu->flag_h =  Bytes::isHalfCarryAdd_8((cpu->sp & 0xFF), value);
    cpu->flag_c = Bytes::isCarryAdd_8((cpu->sp & 0xFF), value);
}

static void load_r8_ar8(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint8 value = memory->get_8(0xFF00 + cpu->get_8(cpuRegister_2));
    cpu->set_8(cpuRegister_1, value);
}

static void load_n16_sp(CPU* cpu, MemoryHook* memory, uint16 arg_16) {
    memory->set_16(arg_16, cpu->sp);
}

static void jump_n16(CPU* cpu, uint16 value) {
    cpu->pc = value;
}

static void jump_ar16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    jump_n16(cpu, address);
}

static void add_sp_n8(CPU* cpu, uint8 value) {
    int8 signed_value = Bytes::toSigned_8(value);
    uint16 new_value = Bytes::wrappingSub_16(Bytes::wrappingAdd_16(cpu->sp, signed_value), 0);
    uint8 old_value = cpu->sp;
    cpu->sp = new_value;

    cpu->flag_z = false;
    cpu->flag_n = false;
    cpu->flag_h =  Bytes::isHalfCarryAdd_8((old_value & 0xFF), value);
    cpu->flag_c = Bytes::isCarryAdd_8((old_value & 0xFF), value);
}

static uint8 and_(CPU* cpu, uint8 value_1, uint8 value_2)  {
    uint8 result = value_1 & value_2;

    cpu->flag_z = result == 0;
    cpu->flag_n = false;
    cpu->flag_h = true;
    cpu->flag_c = false;

    return result;
}

static uint16 add_16(CPU* cpu, uint16 value_1, uint16 value_2) {
    uint16 result = Bytes::wrappingAdd_16(value_1, value_2);

    cpu->flag_n = false;
    cpu->flag_h = Bytes::isHalfCarryAdd_16(value_1, value_2);
    cpu->flag_c = Bytes::isCarryAdd_16(value_1, value_2);

    return result;
}

static void and_r8_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint16 address = cpu->get_16(cpuRegister_2);
    uint8 value_2 = memory->get_8(address);
    uint8 value_1 = cpu->get_8(cpuRegister_1);
    uint8 result = and_(cpu, value_1, value_2);
    cpu->set_8(cpuRegister_1, result);
}

static uint8 sub(CPU* cpu, uint8 value_1, uint8 value_2) {
    uint8 result = Bytes::wrappingSub_8(value_1, value_2);

    cpu->flag_z = result == 0;
    cpu->flag_n = true;
    cpu->flag_h = Bytes::isHalfCarrySub_8(value_1, value_2);
    cpu->flag_c = value_1 < value_2;

    return result;
}

static void sub_r8_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint16 address = cpu->get_16(cpuRegister_2);
    uint8 value = memory->get_8(address);
    uint8 register_value_1 = cpu->get_8(cpuRegister_1);
    uint8 result = sub(cpu, register_value_1, value);

    cpu->set_8(cpuRegister_1, result);
}

static uint8 add(CPU* cpu, uint8 value_1, uint8 value_2) {
    uint8 result = Bytes::wrappingAdd_8(value_1, value_2);

    cpu->flag_z = result == 0;
    cpu->flag_n = false;
    cpu->flag_h = Bytes::isHalfCarryAdd_8(value_1, value_2);
    cpu->flag_c = Bytes::isCarryAdd_8(value_1, value_2);

    return result;
}

static void add_r8_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint16 address = cpu->get_16(cpuRegister_2);
    uint8 value = memory->get_8(address);
    uint8 register_value_1 = cpu->get_8(cpuRegister_1);
    uint8 result = add(cpu, register_value_1, value);

    cpu->set_8(cpuRegister_1, result);
}

static void add_r16_r16(CPU* cpu, Register cpuRegister_1, Register cpuRegister_2) {
    uint16 register_value_1 = cpu->get_16(cpuRegister_1);
    uint16 register_value_2 = cpu->get_16(cpuRegister_2);
    uint16 result = add_16(cpu, register_value_1, register_value_2);

    cpu->set_16(cpuRegister_1, result);
}

static void decrement_sp(CPU* cpu) {
    cpu->sp = Bytes::wrappingSub_16(cpu->sp, 1);
}

static void add_r16_sp(CPU* cpu, Register cpuRegister) {
    uint16 value_1 = cpu->get_16(cpuRegister);
    uint16 value_2 = cpu->sp;
    uint16 result = add_16(cpu, value_1, value_2);

    cpu->set_16(cpuRegister, result);
}

static void return_(CPU* cpu, MemoryHook* memory) {
    uint8 lower = memory->get_8(cpu->sp);
    uint8 upper = memory->get_8(cpu->sp + 1);
    uint16 address = Bytes::join_8(upper, lower);
    cpu->sp += 2;
    jump_n16(cpu, address);
}

static void return_enable_interrupts(CPU* cpu, MemoryHook* memory) {
    return_(cpu, memory);
    enable_interrupts(cpu);
}

static bool return_carry(CPU* cpu, MemoryHook* memory) {
    if (cpu->flag_c) {
        return_(cpu, memory);
        return true;
    }

    return false;
}

static bool return_not_carry(CPU* cpu, MemoryHook* memory) {
    if (!cpu->flag_c) {
        return_(cpu, memory);
        return true;
    }

    return false;
}

static bool return_zero(CPU* cpu, MemoryHook* memory) {
    if (cpu->flag_z) {
        return_(cpu, memory);
        return true;
    }

    return false;
}

static bool return_not_zero(CPU* cpu, MemoryHook* memory) {
    if (!cpu->flag_z) {
        return_(cpu, memory);
        return true;
    }

    return false;
}

static void halt(CPU* cpu) {
    cpu->halt = true;
}

static void stop(CPU* cpu) {
    if(cpu->swapSpeed) {
        cpu->currentSpeed = cpu->currentSpeed == 1 ? 2 : 1;
        cpu->swapSpeed = false;
    }
}

static void toggle_carry(CPU* cpu) {
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = !cpu->flag_c;
}

static void not_used() {
    throw std::invalid_argument("Reached invalid instruction.");
}

// Stack

static void push_n16(CPU* cpu, MemoryHook* memory, uint16 value) {
    memory->set_8(cpu->sp - 1, Bytes::split_16_upper(value));
    memory->set_8(cpu->sp - 2, Bytes::split_16_lower(value));
    cpu->sp -= 2;
}

static void push_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 register_value = cpu->get_16(cpuRegister);
    push_n16(cpu, memory, register_value);
}

static void pop_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint8 lower = memory->get_8(cpu->sp);
    uint8 upper = memory->get_8(cpu->sp + 1);
    uint16 value = Bytes::join_8(upper, lower);

    cpu->set_16(cpuRegister, value);
    cpu->sp += 2;
}

static void restart_n8(CPU* cpu, MemoryHook* memory, uint8 value) {
    uint16 next_instruction = cpu->pc;
    push_n16(cpu, memory, next_instruction);
    jump_n16(cpu, value);
}

void Instructions::call(CPU* cpu, MemoryHook* memory, uint16 value) {
    uint16 next_instruction = cpu->pc;
    push_n16(cpu, memory, next_instruction);
    jump_n16(cpu, value);
}

static bool call_carry_n16(CPU* cpu, MemoryHook* memory, uint16 value) {
    if (cpu->flag_c) {
        Instructions::call(cpu, memory, value);
        return true;
    }

    return false;
}

static bool call_not_carry_n16(CPU* cpu, MemoryHook* memory, uint16 value) {
    if (!cpu->flag_c) {
        Instructions::call(cpu, memory, value);
        return true;
    }

    return false;
}

static bool call_not_zero_n16(CPU* cpu, MemoryHook* memory, uint16 value) {
    if (!cpu->flag_z) {
        Instructions::call(cpu, memory, value);
        return true;
    }

    return false;
}

static bool call_zero_n16(CPU* cpu, MemoryHook* memory, uint16 value) {
    if (cpu->flag_z) {
        Instructions::call(cpu, memory, value);
        return true;
    }

    return false;
}

// Loads

static void load_r8_an8(CPU* cpu, MemoryHook* memory, Register cpuRegister, uint8 value) {
    uint8 new_value = memory->get_8(0xFF00 + value);
    cpu->set_8(cpuRegister, new_value);
}

static void load_r8_r8(CPU* cpu, Register cpuRegister_1, Register cpuRegister_2) {
    uint8 value = cpu->get_8(cpuRegister_2);
    cpu->set_8(cpuRegister_1, value);
}

static void load_r8_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint16 address = cpu->get_16(cpuRegister_2);
    uint8 value = memory->get_8(address);
    cpu->set_8(cpuRegister_1, value);
}

static void load_r8_n8(CPU* cpu, Register cpuRegister, uint8 value) {
    cpu->set_8(cpuRegister, value);
}

static void load_r8_n16(CPU* cpu, MemoryHook* memory, Register cpuRegister, uint16 value) {
    uint8 new_value = memory->get_8(value);
    cpu->set_8(cpuRegister, new_value);
}

static void load_r16_r8(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint16 address = cpu->get_16(cpuRegister_1);
    uint8 value = cpu->get_8(cpuRegister_2);
    memory->set_8(address, value);
}

static void load_r16_n16(CPU* cpu, Register cpuRegister, uint16 value) {
    cpu->set_16(cpuRegister, value);
}

static void load_n16_r8(CPU* cpu, MemoryHook* memory, uint16 address, Register cpuRegister) {
    uint8 register_value = cpu->get_8(cpuRegister);
    memory->set_8(address, register_value);
}

static void load_high_n8_a(CPU* cpu, MemoryHook* memory, uint8 value) {
    uint16 address = 0xFF00 + value;
    uint8 register_value = cpu->get_8(A);
    memory->set_8(address, register_value);
}

static void load_decrement_hl_a(CPU* cpu, MemoryHook* memory) {
    uint8 value = cpu->get_8(A);
    uint16 address = cpu->get_16(HL);
    memory->set_8(address, value);
    cpu->set_16(HL, address - 1);
}

static void load_sp_r16(CPU* cpu, Register cpuRegister) {
    uint16 register_value = cpu->get_16(cpuRegister);
    cpu->sp = register_value;
}

static void load_r16_n8(CPU* cpu, MemoryHook* memory, Register cpuRegister, uint8 value) {
    uint16 address = cpu->get_16(cpuRegister);
    memory->set_8(address, value);
}

static void load_ar8_r8(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint8 value = cpu->get_8(cpuRegister_2);
    uint16 address = 0xFF00 + cpu->get_8(cpuRegister_1);
    memory->set_8(address, value);
}

// Math

static void increment_r8(CPU* cpu, Register cpuRegister) {
    uint8 register_value = cpu->get_8(cpuRegister);
    uint8 value = Bytes::wrappingAdd_8(register_value, 1);
    cpu->set_8(cpuRegister, value);

    cpu->flag_z = value == 0;
    cpu->flag_n = false;
    cpu->flag_h = Bytes::isHalfCarryAdd_8(register_value, 1);
}

static void increment_ar16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    uint8 new_value = Bytes::wrappingAdd_8(value, 1);
    memory->set_8(address, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = false;
    cpu->flag_h = Bytes::isHalfCarryAdd_8(value, 1);
}

static void decrement_ar16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    uint8 new_value = Bytes::wrappingSub_8(value, 1);
    memory->set_8(address, new_value);

    cpu->flag_z = new_value == 0;
    cpu->flag_n = true;
    cpu->flag_h = Bytes::isHalfCarrySub_8(value, 1);
}

static void increment_r16(CPU* cpu, Register cpuRegister) {
    uint16 register_value = cpu->get_16(cpuRegister);
    cpu->set_16(cpuRegister, Bytes::wrappingAdd_16(register_value, 1));
}

static void decrement_r16(CPU* cpu, Register cpuRegister) {
    uint16 register_value = cpu->get_16(cpuRegister);
    uint16 newValue = Bytes::wrappingSub_16(register_value, 1);
    cpu->set_16(cpuRegister, newValue);
}

static void add_carry_r8_n8(CPU* cpu, Register cpuRegister, uint8 value) {
    uint8 carry_value =  cpu->flag_c ? 1 : 0 ;
    uint8 register_value = cpu->get_8(cpuRegister);
    uint8 result = Bytes::wrappingAdd_8(Bytes::wrappingAdd_8(register_value, value), carry_value);

    cpu->flag_z = result == 0;
    cpu->flag_n = false;
    cpu->flag_h = Bytes::isHalfCarryAdd_8_three(register_value, value, carry_value);
    cpu->flag_c = Bytes::isCarryAdd_8_three(register_value, value, carry_value);

    cpu->set_8(cpuRegister, result);
}


static void sub_carry_r8_n8(CPU* cpu, Register cpuRegister, uint8 value) {
    uint8 carry_value = cpu->flag_c ? 1 : 0;
    uint8 register_value = cpu->get_8(cpuRegister);
    uint8 result = Bytes::wrappingSub_8(Bytes::wrappingSub_8(register_value, value), carry_value);

    cpu->flag_z = result == 0;
    cpu->flag_n = true;
    cpu->flag_h = Bytes::isHalfCarrySub_8_three(register_value, value, carry_value);
    cpu->flag_c = Bytes::isCarrySub_8_three(register_value, value, carry_value);

    cpu->set_8(cpuRegister, result);
}

static void add_cary_r8_r8(CPU* cpu, Register cpuRegister_1, Register cpuRegister_2) {
    uint8 register_value_2 = cpu->get_8(cpuRegister_2);
    add_carry_r8_n8(cpu, cpuRegister_1, register_value_2);
}

static void add_carry_r8_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint16 address = cpu->get_16(cpuRegister_2);
    uint8 value = memory->get_8(address);
    add_carry_r8_n8(cpu, cpuRegister_1, value);
}

static void sub_carry_r8_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister_1, Register cpuRegister_2) {
    uint16 address = cpu->get_16(cpuRegister_2);
    uint8 value = memory->get_8(address);
    sub_carry_r8_n8(cpu, cpuRegister_1, value);
}

static void add_r8_r8(CPU* cpu, Register cpuRegister_1, Register cpuRegister_2) {
    uint8 register_value_1 = cpu->get_8(cpuRegister_1);
    uint8 register_value_2 = cpu->get_8(cpuRegister_2);
    uint8 result = add(cpu, register_value_1, register_value_2);

    cpu->set_8(cpuRegister_1, result);
}

static void add_r8_n8(CPU* cpu, Register cpuRegister, uint8 value) {
    uint8 register_value = cpu->get_8(cpuRegister);
    uint8 result = add(cpu, register_value, value);

    cpu->set_8(cpuRegister, result);
}

static void sub_carry_r8_r8(CPU* cpu, Register cpuRegister_1, Register cpuRegister_2) {
    uint8 register_value_2 = cpu->get_8(cpuRegister_2);
    sub_carry_r8_n8(cpu, cpuRegister_1, register_value_2);
}

static void sub_r8_r8(CPU* cpu, Register cpuRegister_1, Register cpuRegister_2) {
    uint8 register_value_1 = cpu->get_8(cpuRegister_1);
    uint8 register_value_2 = cpu->get_8(cpuRegister_2);
    uint8 result = sub(cpu, register_value_1, register_value_2);

    cpu->set_8(cpuRegister_1, result);
}

static void sub_r8_n8(CPU* cpu, Register cpuRegister, uint8 value) {
    uint8 register_value = cpu->get_8(cpuRegister);
    uint8 result = sub(cpu, register_value, value);

    cpu->set_8(cpuRegister, result);
}

static void compare_n8(CPU* cpu, uint8 value) {
    uint8 register_value = cpu->get_8(A);
    sub(cpu, register_value, value);
}

static void compare_r8(CPU* cpu, Register cpuRegister) {
    uint8 register_value = cpu->get_8(cpuRegister);
    compare_n8(cpu, register_value);
}

static void compare_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    compare_n8(cpu, value);
}

static void xor_8(CPU* cpu, uint8 value) {
    uint8 result = value ^ cpu->get_8(A);
    cpu->set_8(A, result);

    cpu->flag_z = result == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = false;
}

static void xor_r8_n8(CPU* cpu, Register cpuRegister, uint8 value) {
    xor_8(cpu, value);
}

static void xor_r8(CPU* cpu, Register cpuRegister) {
    uint8 register_value = cpu->get_8(cpuRegister);
    xor_8(cpu, register_value);
}

static uint8 or_8(CPU* cpu, uint8 value_1, uint8 value_2)  {
    uint8 result = value_1 | value_2;

    cpu->flag_z = result == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = false;

    return result;
}

static void or_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint8 register_value = cpu->get_8(A);
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    uint8 result = or_8(cpu, register_value, value);
    cpu->set_8(A, result);
}

static void xor_r16(CPU* cpu, MemoryHook* memory, Register cpuRegister) {
    uint16 address = cpu->get_16(cpuRegister);
    uint8 value = memory->get_8(address);
    xor_8(cpu, value);
}

static void and_r8_r8(CPU* cpu, Register cpuRegister_1, Register cpuRegister_2) {
    uint8 register_value_1 = cpu->get_8(cpuRegister_1);
    uint8 register_value_2 = cpu->get_8(cpuRegister_2);
    uint8 result = and_(cpu, register_value_1, register_value_2);
    cpu->set_8(cpuRegister_1, result);
}

static void and_r8_n8(CPU* cpu, Register cpuRegister, uint8 value) {
    uint8 register_value = cpu->get_8(cpuRegister);
    uint8 result = and_(cpu, register_value, value);
    cpu->set_8(cpuRegister, result);
}

static void or_r8_n8(CPU* cpu, Register cpuRegister, uint8 value) {
    uint8 register_value_1 = cpu->get_8(cpuRegister);
    uint8 result = register_value_1 | value;
    cpu->set_8(cpuRegister, result);

    cpu->flag_z = result == 0;
    cpu->flag_n = false;
    cpu->flag_h = false;
    cpu->flag_c = false;
}

static void or_r8(CPU* cpu, Register cpuRegister) {
    uint8 register_value_1 = cpu->get_8(A);
    uint8 register_value_2 = cpu->get_8(cpuRegister);
    uint8 result = or_8(cpu, register_value_1, register_value_2);
    cpu->set_8(A, result);
}

static void decrement_r8(CPU* cpu, Register cpuRegister) {
    uint8 register_value = cpu->get_8(cpuRegister);
    uint8 value = Bytes::wrappingSub_8(register_value, 1);
    cpu->set_8(cpuRegister, value);

    cpu->flag_z = value == 0;
    cpu->flag_n = true;
    cpu->flag_h = Bytes::isHalfCarrySub_8(register_value, 1);
}

// Jumps

static bool jump_carry_n16(CPU* cpu, uint16 value) {
    if (cpu->flag_c) {
        jump_n16(cpu, value);
        return true;
    }

    return false;
}

static bool jump_not_carry_n16(CPU* cpu, uint16 value) {
    if (!cpu->flag_c) {
        jump_n16(cpu, value);
        return true;
    }

    return false;
}

static bool jump_not_zero_n16(CPU* cpu, uint16 value) {
    if (!cpu->flag_z) {
        jump_n16(cpu, value);
        return true;
    }

    return false;
}

static bool jump_zero_n16(CPU* cpu, uint16 value) {
    if (cpu->flag_z) {
        jump_n16(cpu, value);
        return true;
    }

    return false;
}

static void jump_right_n8(CPU* cpu, uint8 value) {
    int8 signed_value = Bytes::toSigned_8(value);
    uint16 new_pc = cpu->pc + signed_value;
    cpu->pc = new_pc;
}

static bool jump_right_not_zero_n8(CPU* cpu, uint8 value) {
    if (cpu->flag_z == false) {
        jump_right_n8(cpu, value);
        return true;
    }

    return false;
}

static bool jump_right_zero_r8(CPU* cpu, uint8 value) {
    if (cpu->flag_z) {
        jump_right_n8(cpu, value);
        return true;
    }

    return false;
}

static bool jump_right_not_carry_n8(CPU* cpu, uint8 value) {
    if (!cpu->flag_c) {
        jump_right_n8(cpu, value);
        return true;
    }

    return false;
}

static bool jump_right_carry_n8(CPU* cpu, uint8 value) {
    if (cpu->flag_c == true) {
        jump_right_n8(cpu, value);
        return true;
    }

    return false;
}

static bool run_cb(uint8 index, CPU *cpu, MemoryHook *memory) {
    switch(index) {

        case 0x00:
            rotate_left_carry_r8_cb(cpu, B);
            return true;

        case 0x01:
            rotate_left_carry_r8_cb(cpu, C);
            return true;

        case 0x02:
            rotate_left_carry_r8_cb(cpu, D);
            return true;

        case 0x03:
            rotate_left_carry_r8_cb(cpu, E);
            return true;

        case 0x04:
            rotate_left_carry_r8_cb(cpu, H);
            return true;

        case 0x05:
            rotate_left_carry_r8_cb(cpu, L);
            return true;

        case 0x06:
            rotate_left_carry_r16(cpu, memory, HL);
            return true;

        case 0x07:
            rotate_left_carry_r8_cb(cpu, A);
            return true;

        case 0x08:
            rotate_right_carry_r8_cb(cpu, B);
            return true;

        case 0x09:
            rotate_right_carry_r8_cb(cpu, C);
            return true;

        case 0x0a:
            rotate_right_carry_r8_cb(cpu, D);
            return true;

        case 0x0b:
            rotate_right_carry_r8_cb(cpu, E);
            return true;

        case 0x0c:
            rotate_right_carry_r8_cb(cpu, H);
            return true;

        case 0x0d:
            rotate_right_carry_r8_cb(cpu, L);
            return true;

        case 0x0e:
            rotate_right_carry_r16(cpu, memory, HL);
            return true;

        case 0x0f:
            rotate_right_carry_r8_cb(cpu, A);
            return true;

        case 0x10:
            rotate_left_r8_cb(cpu, B);
            return true;

        case 0x11:
            rotate_left_r8_cb(cpu, C);
            return true;

        case 0x12:
            rotate_left_r8_cb(cpu, D);
            return true;

        case 0x13:
            rotate_left_r8_cb(cpu, E);
            return true;

        case 0x14:
            rotate_left_r8_cb(cpu, H);
            return true;

        case 0x15:
            rotate_left_r8_cb(cpu, L);
            return true;

        case 0x16:
            rotate_left_r16(cpu, memory, HL);
            return true;

        case 0x17:
            rotate_left_r8_cb(cpu, A);
            return true;

        case 0x18:
            rotate_right_r8_cb(cpu, B);
            return true;

        case 0x19:
            rotate_right_r8_cb(cpu, C);
            return true;

        case 0x1a:
            rotate_right_r8_cb(cpu, D);
            return true;

        case 0x1b:
            rotate_right_r8_cb(cpu, E);
            return true;

        case 0x1c:
            rotate_right_r8_cb(cpu, H);
            return true;

        case 0x1d:
            rotate_right_r8_cb(cpu, L);
            return true;

        case 0x1e:
            rotate_right_r16(cpu, memory, HL);
            return true;

        case 0x1f:
            rotate_right_r8_cb(cpu, A);
            return true;

        case 0x20:
            shift_left_r8(cpu, B);
            return true;

        case 0x21:
            shift_left_r8(cpu, C);
            return true;

        case 0x22:
            shift_left_r8(cpu, D);
            return true;

        case 0x23:
            shift_left_r8(cpu, E);
            return true;

        case 0x24:
            shift_left_r8(cpu, H);
            return true;

        case 0x25:
            shift_left_r8(cpu, L);
            return true;

        case 0x26:
            shift_left_r16(cpu, memory, HL);
            return true;

        case 0x27:
            shift_left_r8(cpu, A);
            return true;

        case 0x28:
            shift_right_weird_r8(cpu, B);
            return true;

        case 0x29:
            shift_right_weird_r8(cpu, C);
            return true;

        case 0x2a:
            shift_right_weird_r8(cpu, D);
            return true;

        case 0x2b:
            shift_right_weird_r8(cpu, E);
            return true;

        case 0x2c:
            shift_right_weird_r8(cpu, H);
            return true;

        case 0x2d:
            shift_right_weird_r8(cpu, L);
            return true;

        case 0x2e:
            shift_right_weird_r16(cpu, memory, HL);
            return true;

        case 0x2f:
            shift_right_weird_r8(cpu, A);
            return true;

        case 0x30:
            swap_r8(cpu, B);
            return true;

        case 0x31:
            swap_r8(cpu, C);
            return true;

        case 0x32:
            swap_r8(cpu, D);
            return true;

        case 0x33:
            swap_r8(cpu, E);
            return true;

        case 0x34:
            swap_r8(cpu, H);
            return true;

        case 0x35:
            swap_r8(cpu, L);
            return true;

        case 0x36:
            swap_r16(cpu, memory, HL);
            return true;

        case 0x37:
            swap_r8(cpu, A);
            return true;

        case 0x38:
            shift_right_r8(cpu, B);
            return true;

        case 0x39:
            shift_right_r8(cpu, C);
            return true;

        case 0x3a:
            shift_right_r8(cpu, D);
            return true;

        case 0x3b:
            shift_right_r8(cpu, E);
            return true;

        case 0x3c:
            shift_right_r8(cpu, H);
            return true;

        case 0x3d:
            shift_right_r8(cpu, L);
            return true;

        case 0x3e:
            shift_right_r16(cpu, memory, HL);
            return true;

        case 0x3f:
            shift_right_r8(cpu, A);
            return true;

        case 0x40:
            bit_r8(cpu, B, 0);
            return true;

        case 0x41:
            bit_r8(cpu, C, 0);
            return true;

        case 0x42:
            bit_r8(cpu, D, 0);
            return true;

        case 0x43:
            bit_r8(cpu, E, 0);
            return true;

        case 0x44:
            bit_r8(cpu, H, 0);
            return true;

        case 0x45:
            bit_r8(cpu, L, 0);
            return true;

        case 0x46:
            bit_r16(cpu, memory, HL, 0);
            return true;

        case 0x47:
            bit_r8(cpu, A, 0);
            return true;

        case 0x48:
            bit_r8(cpu, B, 1);
            return true;

        case 0x49:
            bit_r8(cpu, C, 1);
            return true;

        case 0x4a:
            bit_r8(cpu, D, 1);
            return true;

        case 0x4b:
            bit_r8(cpu, E, 1);
            return true;

        case 0x4c:
            bit_r8(cpu, H, 1);
            return true;

        case 0x4d:
            bit_r8(cpu, L, 1);
            return true;

        case 0x4e:
            bit_r16(cpu, memory, HL, 1);
            return true;

        case 0x4f:
            bit_r8(cpu, A, 1);
            return true;

        case 0x50:
            bit_r8(cpu, B, 2);
            return true;

        case 0x51:
            bit_r8(cpu, C, 2);
            return true;

        case 0x52:
            bit_r8(cpu, D, 2);
            return true;

        case 0x53:
            bit_r8(cpu, E, 2);
            return true;

        case 0x54:
            bit_r8(cpu, H, 2);
            return true;

        case 0x55:
            bit_r8(cpu, L, 2);
            return true;

        case 0x56:
            bit_r16(cpu, memory, HL, 2);
            return true;

        case 0x57:
            bit_r8(cpu, A, 2);
            return true;

        case 0x58:
            bit_r8(cpu, B, 3);
            return true;

        case 0x59:
            bit_r8(cpu, C, 3);
            return true;

        case 0x5a:
            bit_r8(cpu, D, 3);
            return true;

        case 0x5b:
            bit_r8(cpu, E, 3);
            return true;

        case 0x5c:
            bit_r8(cpu, H, 3);
            return true;

        case 0x5d:
            bit_r8(cpu, L, 3);
            return true;

        case 0x5e:
            bit_r16(cpu, memory, HL, 3);
            return true;

        case 0x5f:
            bit_r8(cpu, A, 3);
            return true;

        case 0x60:
            bit_r8(cpu, B, 4);
            return true;

        case 0x61:
            bit_r8(cpu, C, 4);
            return true;

        case 0x62:
            bit_r8(cpu, D, 4);
            return true;

        case 0x63:
            bit_r8(cpu, E, 4);
            return true;

        case 0x64:
            bit_r8(cpu, H, 4);
            return true;

        case 0x65:
            bit_r8(cpu, L, 4);
            return true;

        case 0x66:
            bit_r16(cpu, memory, HL, 4);
            return true;

        case 0x67:
            bit_r8(cpu, A, 4);
            return true;

        case 0x68:
            bit_r8(cpu, B, 5);
            return true;

        case 0x69:
            bit_r8(cpu, C, 5);
            return true;

        case 0x6a:
            bit_r8(cpu, D, 5);
            return true;

        case 0x6b:
            bit_r8(cpu, E, 5);
            return true;

        case 0x6c:
            bit_r8(cpu, H, 5);
            return true;

        case 0x6d:
            bit_r8(cpu, L, 5);
            return true;

        case 0x6e:
            bit_r16(cpu, memory, HL, 5);
            return true;

        case 0x6f:
            bit_r8(cpu, A, 5);
            return true;

        case 0x70:
            bit_r8(cpu, B, 6);
            return true;

        case 0x71:
            bit_r8(cpu, C, 6);
            return true;

        case 0x72:
            bit_r8(cpu, D, 6);
            return true;

        case 0x73:
            bit_r8(cpu, E, 6);
            return true;

        case 0x74:
            bit_r8(cpu, H, 6);
            return true;

        case 0x75:
            bit_r8(cpu, L, 6);
            return true;

        case 0x76:
            bit_r16(cpu, memory, HL, 6);
            return true;

        case 0x77:
            bit_r8(cpu, A, 6);
            return true;

        case 0x78:
            bit_r8(cpu, B, 7);
            return true;

        case 0x79:
            bit_r8(cpu, C, 7);
            return true;

        case 0x7a:
            bit_r8(cpu, D, 7);
            return true;

        case 0x7b:
            bit_r8(cpu, E, 7);
            return true;

        case 0x7c:
            bit_r8(cpu, H, 7);
            return true;

        case 0x7d:
            bit_r8(cpu, L, 7);
            return true;

        case 0x7e:
            bit_r16(cpu, memory, HL, 7);
            return true;

        case 0x7f:
            bit_r8(cpu, A, 7);
            return true;

        case 0x80:
            reset_r8(cpu, B, 0);
            return true;

        case 0x81:
            reset_r8(cpu, C, 0);
            return true;

        case 0x82:
            reset_r8(cpu, D, 0);
            return true;

        case 0x83:
            reset_r8(cpu, E, 0);
            return true;

        case 0x84:
            reset_r8(cpu, H, 0);
            return true;

        case 0x85:
            reset_r8(cpu, L, 0);
            return true;

        case 0x86:
            reset_r16(cpu, memory, HL, 0);
            return true;

        case 0x87:
            reset_r8(cpu, A, 0);
            return true;

        case 0x88:
            reset_r8(cpu, B, 1);
            return true;

        case 0x89:
            reset_r8(cpu, C, 1);
            return true;

        case 0x8a:
            reset_r8(cpu, D, 1);
            return true;

        case 0x8b:
            reset_r8(cpu, E, 1);
            return true;

        case 0x8c:
            reset_r8(cpu, H, 1);
            return true;

        case 0x8d:
            reset_r8(cpu, L, 1);
            return true;

        case 0x8e:
            reset_r16(cpu, memory, HL, 1);
            return true;

        case 0x8f:
            reset_r8(cpu, A, 1);
            return true;

        case 0x90:
            reset_r8(cpu, B, 2);
            return true;

        case 0x91:
            reset_r8(cpu, C, 2);
            return true;

        case 0x92:
            reset_r8(cpu, D, 2);
            return true;

        case 0x93:
            reset_r8(cpu, E, 2);
            return true;

        case 0x94:
            reset_r8(cpu, H, 2);
            return true;

        case 0x95:
            reset_r8(cpu, L, 2);
            return true;

        case 0x96:
            reset_r16(cpu, memory, HL, 2);
            return true;

        case 0x97:
            reset_r8(cpu, A, 2);
            return true;

        case 0x98:
            reset_r8(cpu, B, 3);
            return true;

        case 0x99:
            reset_r8(cpu, C, 3);
            return true;

        case 0x9a:
            reset_r8(cpu, D, 3);
            return true;

        case 0x9b:
            reset_r8(cpu, E, 3);
            return true;

        case 0x9c:
            reset_r8(cpu, H, 3);
            return true;

        case 0x9d:
            reset_r8(cpu, L, 3);
            return true;

        case 0x9e:
            reset_r16(cpu, memory, HL, 3);
            return true;

        case 0x9f:
            reset_r8(cpu, A, 3);
            return true;

        case 0xa0:
            reset_r8(cpu, B, 4);
            return true;

        case 0xa1:
            reset_r8(cpu, C, 4);
            return true;

        case 0xa2:
            reset_r8(cpu, D, 4);
            return true;

        case 0xa3:
            reset_r8(cpu, E, 4);
            return true;

        case 0xa4:
            reset_r8(cpu, H, 4);
            return true;

        case 0xa5:
            reset_r8(cpu, L, 4);
            return true;

        case 0xa6:
            reset_r16(cpu, memory, HL, 4);
            return true;

        case 0xa7:
            reset_r8(cpu, A, 4);
            return true;

        case 0xa8:
            reset_r8(cpu, B, 5);
            return true;

        case 0xa9:
            reset_r8(cpu, C, 5);
            return true;

        case 0xaa:
            reset_r8(cpu, D, 5);
            return true;

        case 0xab:
            reset_r8(cpu, E, 5);
            return true;

        case 0xac:
            reset_r8(cpu, H, 5);
            return true;

        case 0xad:
            reset_r8(cpu, L, 5);
            return true;

        case 0xae:
            reset_r16(cpu, memory, HL, 5);
            return true;

        case 0xaf:
            reset_r8(cpu, A, 5);
            return true;

        case 0xb0:
            reset_r8(cpu, B, 6);
            return true;

        case 0xb1:
            reset_r8(cpu, C, 6);
            return true;

        case 0xb2:
            reset_r8(cpu, D, 6);
            return true;

        case 0xb3:
            reset_r8(cpu, E, 6);
            return true;

        case 0xb4:
            reset_r8(cpu, H, 6);
            return true;

        case 0xb5:
            reset_r8(cpu, L, 6);
            return true;

        case 0xb6:
            reset_r16(cpu, memory, HL, 6);
            return true;

        case 0xb7:
            reset_r8(cpu, A, 6);
            return true;

        case 0xb8:
            reset_r8(cpu, B, 7);
            return true;

        case 0xb9:
            reset_r8(cpu, C, 7);
            return true;

        case 0xba:
            reset_r8(cpu, D, 7);
            return true;

        case 0xbb:
            reset_r8(cpu, E, 7);
            return true;

        case 0xbc:
            reset_r8(cpu, H, 7);
            return true;

        case 0xbd:
            reset_r8(cpu, L, 7);
            return true;

        case 0xbe:
            reset_r16(cpu, memory, HL, 7);
            return true;

        case 0xbf:
            reset_r8(cpu, A, 7);
            return true;

        case 0xc0:
            set_r8(cpu, B, 0);
            return true;

        case 0xc1:
            set_r8(cpu, C, 0);
            return true;

        case 0xc2:
            set_r8(cpu, D, 0);
            return true;

        case 0xc3:
            set_r8(cpu, E, 0);
            return true;

        case 0xc4:
            set_r8(cpu, H, 0);
            return true;

        case 0xc5:
            set_r8(cpu, L, 0);
            return true;

        case 0xc6:
            set_r16(cpu, memory, HL, 0);
            return true;

        case 0xc7:
            set_r8(cpu, A, 0);
            return true;

        case 0xc8:
            set_r8(cpu, B, 1);
            return true;

        case 0xc9:
            set_r8(cpu, C, 1);
            return true;

        case 0xca:
            set_r8(cpu, D, 1);
            return true;

        case 0xcb:
            set_r8(cpu, E, 1);
            return true;

        case 0xcc:
            set_r8(cpu, H, 1);
            return true;

        case 0xcd:
            set_r8(cpu, L, 1);
            return true;

        case 0xce:
            set_r16(cpu, memory, HL, 1);
            return true;

        case 0xcf:
            set_r8(cpu, A, 1);
            return true;

        case 0xd0:
            set_r8(cpu, B, 2);
            return true;

        case 0xd1:
            set_r8(cpu, C, 2);
            return true;

        case 0xd2:
            set_r8(cpu, D, 2);
            return true;

        case 0xd3:
            set_r8(cpu, E, 2);
            return true;

        case 0xd4:
            set_r8(cpu, H, 2);
            return true;

        case 0xd5:
            set_r8(cpu, L, 2);
            return true;

        case 0xd6:
            set_r16(cpu, memory, HL, 2);
            return true;

        case 0xd7:
            set_r8(cpu, A, 2);
            return true;

        case 0xd8:
            set_r8(cpu, B, 3);
            return true;

        case 0xd9:
            set_r8(cpu, C, 3);
            return true;

        case 0xda:
            set_r8(cpu, D, 3);
            return true;

        case 0xdb:
            set_r8(cpu, E, 3);
            return true;

        case 0xdc:
            set_r8(cpu, H, 3);
            return true;

        case 0xdd:
            set_r8(cpu, L, 3);
            return true;

        case 0xde:
            set_r16(cpu, memory, HL, 3);
            return true;

        case 0xdf:
            set_r8(cpu, A, 3);
            return true;

        case 0xe0:
            set_r8(cpu, B, 4);
            return true;

        case 0xe1:
            set_r8(cpu, C, 4);
            return true;

        case 0xe2:
            set_r8(cpu, D, 4);
            return true;

        case 0xe3:
            set_r8(cpu, E, 4);
            return true;

        case 0xe4:
            set_r8(cpu, H, 4);
            return true;

        case 0xe5:
            set_r8(cpu, L, 4);
            return true;

        case 0xe6:
            set_r16(cpu, memory, HL, 4);
            return true;

        case 0xe7:
            set_r8(cpu, A, 4);
            return true;

        case 0xe8:
            set_r8(cpu, B, 5);
            return true;

        case 0xe9:
            set_r8(cpu, C, 5);
            return true;

        case 0xea:
            set_r8(cpu, D, 5);
            return true;

        case 0xeb:
            set_r8(cpu, E, 5);
            return true;

        case 0xec:
            set_r8(cpu, H, 5);
            return true;

        case 0xed:
            set_r8(cpu, L, 5);
            return true;

        case 0xee:
            set_r16(cpu, memory, HL, 5);
            return true;

        case 0xef:
            set_r8(cpu, A, 5);
            return true;

        case 0xf0:
            set_r8(cpu, B, 6);
            return true;

        case 0xf1:
            set_r8(cpu, C, 6);
            return true;

        case 0xf2:
            set_r8(cpu, D, 6);
            return true;

        case 0xf3:
            set_r8(cpu, E, 6);
            return true;

        case 0xf4:
            set_r8(cpu, H, 6);
            return true;

        case 0xf5:
            set_r8(cpu, L, 6);
            return true;

        case 0xf6:
            set_r16(cpu, memory, HL, 6);
            return true;

        case 0xf7:
            set_r8(cpu, A, 6);
            return true;

        case 0xf8:
            set_r8(cpu, B, 7);
            return true;

        case 0xf9:
            set_r8(cpu, C, 7);
            return true;

        case 0xfa:
            set_r8(cpu, D, 7);
            return true;

        case 0xfb:
            set_r8(cpu, E, 7);
            return true;

        case 0xfc:
            set_r8(cpu, H, 7);
            return true;

        case 0xfd:
            set_r8(cpu, L, 7);
            return true;

        case 0xfe:
            set_r16(cpu, memory, HL, 7);
            return true;

        case 0xff:
            set_r8(cpu, A, 7);
            return true;

        default:
            throw std::invalid_argument("Invalid CB instruction.");
    }
}

instructionInfo Instructions::getInfo(uint8 index, uint8 arg) {
    return index == 0xCB ? CB_INSTRUCTION_INFO[arg] : CORE_INSTRUCTION_INFO[index];
}

bool Instructions::run(uint8 index, CPU *cpu, MemoryHook *memory, uint8 arg_8, uint16 arg_16) {
    switch(index) {
        case 0x00:
            return true;
        case 0x01:   load_r16_n16(cpu, BC, arg_16); return true;
        case 0x02:   load_r16_r8(cpu, memory, BC, A); return true;
        case 0x03:   increment_r16(cpu, BC); return true;
        case 0x04:   increment_r8(cpu, B); return true;
        case 0x05:   decrement_r8(cpu, B); return true;
        case 0x06:   load_r8_n8(cpu, B, arg_8); return true;
        case 0x07:   rotate_left_carry_r8(cpu, A); return true;
        case 0x08:   load_n16_sp(cpu, memory, arg_16); return true;
        case 0x09:   add_r16_r16(cpu, HL, BC); return true;
        case 0x0a:   load_r8_r16(cpu, memory, A, BC); return true;
        case 0x0b:   decrement_r16(cpu, BC); return true;
        case 0x0c:   increment_r8(cpu, C); return true;
        case 0x0d:   decrement_r8(cpu, C); return true;
        case 0x0e:   load_r8_n8(cpu, C, arg_8); return true;
        case 0x0f:   rotate_right_carry_r8(cpu, A); return true;
        case 0x10:   stop(cpu); return true;
        case 0x11:   load_r16_n16(cpu, DE, arg_16); return true;
        case 0x12:   load_r16_r8(cpu, memory, DE, A); return true;
        case 0x13:   increment_r16(cpu, DE); return true;
        case 0x14:   increment_r8(cpu, D); return true;
        case 0x15:   decrement_r8(cpu, D); return true;
        case 0x16:   load_r8_n8(cpu, D, arg_8); return true;
        case 0x17:   rotate_left_r8(cpu, A); return true;
        case 0x18:   jump_right_n8(cpu, arg_8); return true;
        case 0x19:   add_r16_r16(cpu, HL, DE); return true;
        case 0x1a:   load_r8_r16(cpu, memory, A, DE); return true;
        case 0x1b:   decrement_r16(cpu, DE); return true;
        case 0x1c:   increment_r8(cpu, E); return true;
        case 0x1d:   decrement_r8(cpu, E); return true;
        case 0x1e:   load_r8_n8(cpu, E, arg_8); return true;
        case 0x1f:   rotate_right_r8(cpu, A); return true;
        case 0x20:   return jump_right_not_zero_n8(cpu, arg_8);
        case 0x21:   load_r16_n16(cpu, HL, arg_16); return true;
        case 0x22:   load_increment_r16_r8(cpu, memory, HL, A); return true;
        case 0x23:   increment_r16(cpu, HL); return true;
        case 0x24:   increment_r8(cpu, H); return true;
        case 0x25:   decrement_r8(cpu, H); return true;
        case 0x26:   load_r8_n8(cpu, H, arg_8); return true;
        case 0x27:   decimal_r8(cpu, A); return true;
        case 0x28:   return jump_right_zero_r8(cpu, arg_8);
        case 0x29:   add_r16_r16(cpu, HL, HL); return true;
        case 0x2a:   load_increment_r8_ar16(cpu, memory, A, HL); return true;
        case 0x2b:   decrement_r16(cpu, HL); return true;
        case 0x2c:   increment_r8(cpu, L); return true;
        case 0x2d:   decrement_r8(cpu, L); return true;
        case 0x2e:   load_r8_n8(cpu, L, arg_8); return true;
        case 0x2f:   complement_r8(cpu, A); return true;
        case 0x30:   return jump_right_not_carry_n8(cpu, arg_8);
        case 0x31:   load_sp_n16(cpu, arg_16); return true;
        case 0x32:   load_decrement_hl_a(cpu, memory); return true;
        case 0x33:   increment_sp(cpu); return true;
        case 0x34:   increment_ar16(cpu, memory, HL); return true;
        case 0x35:   decrement_ar16(cpu, memory, HL); return true;
        case 0x36:   load_r16_n8(cpu, memory, HL, arg_8); return true;
        case 0x37:   set_carry(cpu); return true;
        case 0x38:   return jump_right_carry_n8(cpu, arg_8);
        case 0x39:   add_r16_sp(cpu, HL); return true;
        case 0x3a:   load_decrement_r8_ar16(cpu, memory, A, HL); return true;
        case 0x3b:   decrement_sp(cpu); return true;
        case 0x3c:   increment_r8(cpu, A); return true;
        case 0x3d:   decrement_r8(cpu, A); return true;
        case 0x3e:   load_r8_n8(cpu, A, arg_8); return true;
        case 0x3f:   toggle_carry(cpu); return true;
        case 0x40:   load_r8_r8(cpu, B, B); return true;  // 0x40
        case 0x41:   load_r8_r8(cpu, B, C); return true;  // 0x41
        case 0x42:   load_r8_r8(cpu, B, D); return true;  // 0x42
        case 0x43:   load_r8_r8(cpu, B, E); return true;  // 0x43
        case 0x44:   load_r8_r8(cpu, B, H); return true;  // 0x44
        case 0x45:   load_r8_r8(cpu, B, L); return true;  // 0x45
        case 0x46:   load_r8_r16(cpu, memory, B, HL); return true;
        case 0x47:   load_r8_r8(cpu, B, A); return true;
        case 0x48:   load_r8_r8(cpu, C, B); return true;  // 0x48
        case 0x49:   load_r8_r8(cpu, C, C); return true;  // 0x49
        case 0x4a:   load_r8_r8(cpu, C, D); return true;  // 0x4A
        case 0x4b:   load_r8_r8(cpu, C, E); return true;  // 0x4B
        case 0x4c:   load_r8_r8(cpu, C, H); return true;  // 0x4C
        case 0x4d:   load_r8_r8(cpu, C, L); return true;  // 0x4D
        case 0x4e:   load_r8_r16(cpu, memory, C, HL); return true;
        case 0x4f:   load_r8_r8(cpu, C, A); return true;
        case 0x50:   load_r8_r8(cpu, D, B); return true;  // 0x50
        case 0x51:   load_r8_r8(cpu, D, C); return true;  // 0x51
        case 0x52:   load_r8_r8(cpu, D, D); return true;  // 0x52
        case 0x53:   load_r8_r8(cpu, D, E); return true;  // 0x53
        case 0x54:   load_r8_r8(cpu, D, H); return true;  // 0x54
        case 0x55:   load_r8_r8(cpu, D, L); return true;  // 0x55
        case 0x56:   load_r8_r16(cpu, memory, D, HL); return true;
        case 0x57:   load_r8_r8(cpu, D, A); return true;
        case 0x58:   load_r8_r8(cpu, E, B); return true;  // 0x58
        case 0x59:   load_r8_r8(cpu, E, C); return true;  // 0x59
        case 0x5a:   load_r8_r8(cpu, E, D); return true;  // 0x5A
        case 0x5b:   load_r8_r8(cpu, E, E); return true;  // 0x5B
        case 0x5c:   load_r8_r8(cpu, E, H); return true;  // 0x5C
        case 0x5d:   load_r8_r8(cpu, E, L); return true;  // 0x5D
        case 0x5e:   load_r8_r16(cpu, memory, E, HL); return true;
        case 0x5f:   load_r8_r8(cpu, E, A); return true;
        case 0x60:   load_r8_r8(cpu, H, B); return true;  // 0x60
        case 0x61:   load_r8_r8(cpu, H, C); return true;  // 0x61
        case 0x62:   load_r8_r8(cpu, H, D); return true;  // 0x62
        case 0x63:   load_r8_r8(cpu, H, E); return true;  // 0x63
        case 0x64:   load_r8_r8(cpu, H, H); return true;  // 0x64
        case 0x65:   load_r8_r8(cpu, H, L); return true;  // 0x65
        case 0x66:   load_r8_r16(cpu, memory, H, HL); return true;
        case 0x67:   load_r8_r8(cpu, H, A); return true;
        case 0x68:   load_r8_r8(cpu, L, B); return true;  // 0x68
        case 0x69:   load_r8_r8(cpu, L, C); return true;  // 0x69
        case 0x6a:   load_r8_r8(cpu, L, D); return true;  // 0x6A
        case 0x6b:   load_r8_r8(cpu, L, E); return true;  // 0x6B
        case 0x6c:   load_r8_r8(cpu, L, H); return true;  // 0x6C
        case 0x6d:   load_r8_r8(cpu, L, L); return true;  // 0x6D
        case 0x6e:   load_r8_r16(cpu, memory, L, HL); return true;
        case 0x6f:   load_r8_r8(cpu, L, A); return true;
        case 0x70:   load_r16_r8(cpu, memory, HL, B); return true;
        case 0x71:   load_r16_r8(cpu, memory, HL, C); return true;
        case 0x72:   load_r16_r8(cpu, memory, HL, D); return true;
        case 0x73:   load_r16_r8(cpu, memory, HL, E); return true;
        case 0x74:   load_r16_r8(cpu, memory, HL, H); return true;
        case 0x75:   load_r16_r8(cpu, memory, HL, L); return true;
        case 0x76:   halt(cpu); return true;
        case 0x77:   load_r16_r8(cpu, memory, HL, A); return true;
        case 0x78:   load_r8_r8(cpu, A, B); return true;  // 0x78
        case 0x79:   load_r8_r8(cpu, A, C); return true;  // 0x79
        case 0x7a:   load_r8_r8(cpu, A, D); return true;  // 0x7A
        case 0x7b:   load_r8_r8(cpu, A, E); return true;  // 0x7B
        case 0x7c:   load_r8_r8(cpu, A, H); return true;  // 0x7C
        case 0x7d:   load_r8_r8(cpu, A, L); return true;  // 0x7D
        case 0x7e:   load_r8_r16(cpu, memory, A, HL); return true;
        case 0x7f:   load_r8_r8(cpu, A, A); return true;  // 0x7F
        case 0x80:   add_r8_r8(cpu, A, B); return true;
        case 0x81:   add_r8_r8(cpu, A, C); return true;
        case 0x82:   add_r8_r8(cpu, A, D); return true;
        case 0x83:   add_r8_r8(cpu, A, E); return true;
        case 0x84:   add_r8_r8(cpu, A, H); return true;
        case 0x85:   add_r8_r8(cpu, A, L); return true;
        case 0x86:   add_r8_r16(cpu, memory, A, HL); return true;
        case 0x87:   add_r8_r8(cpu, A, A); return true;
        case 0x88:   add_cary_r8_r8(cpu, A, B); return true;
        case 0x89:   add_cary_r8_r8(cpu, A, C); return true;
        case 0x8a:   add_cary_r8_r8(cpu, A, D); return true;
        case 0x8b:   add_cary_r8_r8(cpu, A, E); return true;
        case 0x8c:   add_cary_r8_r8(cpu, A, H); return true;
        case 0x8d:   add_cary_r8_r8(cpu, A, L); return true;
        case 0x8e:   add_carry_r8_r16(cpu, memory, A, HL); return true;
        case 0x8f:   add_cary_r8_r8(cpu, A, A); return true;
        case 0x90:   sub_r8_r8(cpu, A, B); return true;
        case 0x91:   sub_r8_r8(cpu, A, C); return true;
        case 0x92:   sub_r8_r8(cpu, A, D); return true;
        case 0x93:   sub_r8_r8(cpu, A, E); return true;
        case 0x94:   sub_r8_r8(cpu, A, H); return true;
        case 0x95:   sub_r8_r8(cpu, A, L); return true;
        case 0x96:   sub_r8_r16(cpu, memory, A, HL); return true;
        case 0x97:   sub_r8_r8(cpu, A, A); return true;
        case 0x98:   sub_carry_r8_r8(cpu, A, B); return true;
        case 0x99:   sub_carry_r8_r8(cpu, A, C); return true;
        case 0x9a:   sub_carry_r8_r8(cpu, A, D); return true;
        case 0x9b:   sub_carry_r8_r8(cpu, A, E); return true;
        case 0x9c:   sub_carry_r8_r8(cpu, A, H); return true;
        case 0x9d:   sub_carry_r8_r8(cpu, A, L); return true;
        case 0x9e:   sub_carry_r8_r16(cpu, memory, A, HL); return true;
        case 0x9f:   sub_carry_r8_r8(cpu, A, A); return true;
        case 0xa0:   and_r8_r8(cpu, A, B); return true;
        case 0xa1:   and_r8_r8(cpu, A, C); return true;
        case 0xa2:   and_r8_r8(cpu, A, D); return true;
        case 0xa3:   and_r8_r8(cpu, A, E); return true;
        case 0xa4:   and_r8_r8(cpu, A, H); return true;
        case 0xa5:   and_r8_r8(cpu, A, L); return true;
        case 0xa6:   and_r8_r16(cpu, memory, A, HL); return true;
        case 0xa7:   and_r8_r8(cpu, A, A); return true;
        case 0xa8:   xor_r8(cpu, B); return true;
        case 0xa9:   xor_r8(cpu, C); return true;
        case 0xaa:   xor_r8(cpu, D); return true;
        case 0xab:   xor_r8(cpu, E); return true;
        case 0xac:   xor_r8(cpu, H); return true;
        case 0xad:   xor_r8(cpu, L); return true;
        case 0xae:   xor_r16(cpu, memory, HL); return true;
        case 0xaf:   xor_r8(cpu, A); return true;
        case 0xb0:   or_r8(cpu, B); return true;
        case 0xb1:   or_r8(cpu, C); return true;
        case 0xb2:   or_r8(cpu, D); return true;
        case 0xb3:   or_r8(cpu, E); return true;
        case 0xb4:   or_r8(cpu, H); return true;
        case 0xb5:   or_r8(cpu, L); return true;
        case 0xb6:   or_r16(cpu, memory, HL); return true;
        case 0xb7:   or_r8(cpu, A); return true;
        case 0xb8:   compare_r8(cpu, B); return true;
        case 0xb9:   compare_r8(cpu, C); return true;
        case 0xba:   compare_r8(cpu, D); return true;
        case 0xbb:   compare_r8(cpu, E); return true;
        case 0xbc:   compare_r8(cpu, H); return true;
        case 0xbd:   compare_r8(cpu, L); return true;
        case 0xbe:   compare_r16(cpu, memory, HL); return true;
        case 0xbf:   compare_r8(cpu, A); return true;
        case 0xc0:   return return_not_zero(cpu, memory);
        case 0xc1:   pop_r16(cpu, memory, BC); return true;
        case 0xc2:   return jump_not_zero_n16(cpu, arg_16);
        case 0xc3:   jump_n16(cpu, arg_16); return true;
        case 0xc4:   return call_not_zero_n16(cpu, memory, arg_16);
        case 0xc5:   push_r16(cpu, memory, BC); return true;
        case 0xc6:   add_r8_n8(cpu, A, arg_8); return true;
        case 0xc7:   restart_n8(cpu, memory, 0x00); return true;
        case 0xc8:   return return_zero(cpu, memory);
        case 0xc9:   return_(cpu, memory); return true;
        case 0xca:   return jump_zero_n16(cpu, arg_16);
        case 0xcb:   return run_cb(arg_8, cpu, memory);
        case 0xcc:   return call_zero_n16(cpu, memory, arg_16);
        case 0xcd:   call(cpu, memory, arg_16); return true;
        case 0xce:   add_carry_r8_n8(cpu, A, arg_8); return true;
        case 0xcf:   restart_n8(cpu, memory, 0x08); return true;
        case 0xd0:   return return_not_carry(cpu, memory);
        case 0xd1:   pop_r16(cpu, memory, DE); return true;
        case 0xd2:   return jump_not_carry_n16(cpu, arg_16);
        case 0xd3:   not_used(); return true;
        case 0xd4:   return call_not_carry_n16(cpu, memory, arg_16);
        case 0xd5:   push_r16(cpu, memory, DE); return true;
        case 0xd6:   sub_r8_n8(cpu, A, arg_8); return true;
        case 0xd7:   restart_n8(cpu, memory, 0x10); return true;
        case 0xd8:   return return_carry(cpu, memory);
        case 0xd9:   return_enable_interrupts(cpu, memory); return true;
        case 0xda:   return jump_carry_n16(cpu, arg_16);
        case 0xdb:   not_used(); return true;
        case 0xdc:
            return call_carry_n16(cpu, memory, arg_16);


        case 0xdd:
            not_used();
            return true;

        case 0xde:
            sub_carry_r8_n8(cpu, A, arg_8);
            return true;

        case 0xdf:
            restart_n8(cpu, memory, 0x18);
            return true;

        case 0xe0:
            load_high_n8_a(cpu, memory, arg_8);
            return true;

        case 0xe1:
            pop_r16(cpu, memory, HL);
            return true;

        case 0xe2:
            load_ar8_r8(cpu, memory, C, A);
            return true;

        case 0xe3:
            not_used();
            return true;

        case 0xe4:
            not_used();
            return true;

        case 0xe5:
            push_r16(cpu, memory, HL);
            return true;

        case 0xe6:
            and_r8_n8(cpu, A, arg_8);
            return true;

        case 0xe7:
            restart_n8(cpu, memory, 0x20);
            return true;

        case 0xe8:
            add_sp_n8(cpu, arg_8);
            return true;

        case 0xe9:
            jump_ar16(cpu, memory, HL);
            return true;

        case 0xea:
            load_n16_r8(cpu, memory, arg_16, A);
            return true;

        case 0xeb:
            not_used();
            return true;

        case 0xec:
            not_used();
            return true;

        case 0xed:
            not_used();
            return true;

        case 0xee:
            xor_r8_n8(cpu, A, arg_8);
            return true;

        case 0xef:
            restart_n8(cpu, memory, 0x28);
            return true;

        case 0xf0:
            load_r8_an8(cpu, memory, A, arg_8);
            return true;

        case 0xf1:
            pop_r16(cpu, memory, AF);
            return true;

        case 0xf2:
            load_r8_ar8(cpu, memory, A, C);
            return true;

        case 0xf3:
            disable_interrupts(cpu);
            return true;

        case 0xf4:
            not_used();
            return true;

        case 0xf5:
            push_r16(cpu, memory, AF);
            return true;

        case 0xf6:
            or_r8_n8(cpu, A, arg_8);
            return true;

        case 0xf7:
            restart_n8(cpu, memory, 0x30);
            return true;

        case 0xf8:
            load_r16_sp_n8(cpu, HL, arg_8);
            return true;

        case 0xf9:
            load_sp_r16(cpu, HL);
            return true;

        case 0xfa:
            load_r8_n16(cpu, memory, A, arg_16);
            return true;

        case 0xfb:
            enable_interrupts(cpu);
            return true;

        case 0xfc:
            not_used();
            return true;

        case 0xfd:
            not_used();
            return true;

        case 0xfe:
            compare_n8(cpu, arg_8);
            return true;

        case 0xff:
            restart_n8(cpu, memory, 0x38);
            return true;
        
        default:
            throw std::invalid_argument("Invalid instruction.");
    }
}
