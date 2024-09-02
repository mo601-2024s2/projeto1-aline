#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>
#include <string.h>
#include <bits/stdc++.h>
#include <algorithm> 
#include <cctype>
#include "registers.hpp"

class decodeInstruction {
    public:
        struct instrInfo {
            std::string pc;
            std::string instr;
            std::string rd;
            std::string rs1;
            std::string rs2;
            std::string imm;
            std::string mnemonic;    
        };

        std::map<uint32_t, instrInfo> instr_info;
        // std::vector<instrInfo> instr_info;
        std::map<uint32_t, instrInfo> parseInstruction(std::string asm_instructions);

    private:
        const uint32_t RD_MASK = 0xF80;
        const uint32_t RS1_MASK = 0xF8000;
        const uint32_t RS2_MASK = 0x1F00000;
        const uint32_t OPC_MASK = 0x7F;

};