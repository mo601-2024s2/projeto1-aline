#include "log.hpp"

void logInstruction::logInstrExecution(uint32_t pc, std::map<uint32_t, decodeInstruction::instrInfo> instr_info, std::map<std::string, uint32_t> regs) {
    std::cout << "PC=" << std::hex << std::setfill('0') << std::setw(8) << pc << " ";
    std::cout << "[" << instr_info[pc].instr << "] ";
    std::cout << "rd=" << std::left << std::setfill(' ') << std::setw(8) << regs[instr_info[pc].rd] << " ";
    std::cout << "rs1=" << std::left << std::setfill(' ') << std::setw(8) << regs[instr_info[pc].rs1] << " ";
    std::cout << "rs2=" << std::left << std::setfill(' ') << std::setw(8) << regs[instr_info[pc].rs2] << " ";
    std::cout << "imm=" << std::left << std::setfill(' ') << std::setw(8) << regs[instr_info[pc].imm] << " ";
    std::cout << std::left << std::setfill(' ') << std::setw(8) << instr_info[pc].mnemonic << " " << instr_info[pc].rd << " " << instr_info[pc].rs1 << " " << instr_info[pc].rs2 << " " << instr_info[pc].imm << std::endl;
}