#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "log.hpp"
#include "memory.hpp"

class executeInstruction {
    public:
        bool execution(std::map<uint32_t, decodeInstruction::instrInfo> instr_info);

        struct op_regs {
            uint32_t rd;
            uint32_t rs1;
            uint32_t rs2;
            uint32_t imm;
        };
};