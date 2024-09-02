#include <iostream>
#include <iomanip>
#include <cstdint>
#include <bits/stdc++.h>
#include "decode.hpp"
class logInstruction {
    public:
        void logInstrExecution(uint32_t pc, std::map<uint32_t, decodeInstruction::instrInfo> instr_info, std::map<std::string, uint32_t>);
};
