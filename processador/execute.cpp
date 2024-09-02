#include "execute.hpp"

bool executeInstruction::execution(std::map<uint32_t, decodeInstruction::instrInfo> instr_info) {
    registerBank regs;
    logInstruction log;
    memoryController mem;
    executeInstruction::op_regs op_regs;
    
    regs.PC = instr_info.begin()->first;
    while (true) {
        auto curr_instr = instr_info[regs.PC];
        if (curr_instr.mnemonic == "lui") {
            regs.bank[curr_instr.rd] = (std::stoul(curr_instr.imm, nullptr, 10) << 12);
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "jal") {
            regs.bank[curr_instr.rd] = regs.PC + 4;
            regs.PC = std::stoul(curr_instr.imm, nullptr, 16);
        } else if (curr_instr.mnemonic == "ebreak") {
            std::cout << "End of execution." << std::endl;
            break;
        } else if (curr_instr.mnemonic == "add") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] + regs.bank[curr_instr.rs2];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "sub") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] - regs.bank[curr_instr.rs2];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "sw") {
            mem.memory[regs.bank[curr_instr.rs1] + std::stoul(curr_instr.imm, nullptr, 16)] = regs.bank[curr_instr.rs2];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "lw") {
            regs.bank[curr_instr.rd] = mem.memory[regs.bank[curr_instr.rs1] + std::stoul(curr_instr.imm, nullptr, 16)];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "jalr") {
            regs.bank[curr_instr.rd] = regs.PC + 4;
            regs.PC = std::stoul(curr_instr.rs1, nullptr, 16);
        } else if (curr_instr.mnemonic == "li") {
            regs.bank[curr_instr.rd] = std::stoul(curr_instr.imm, nullptr, 16);
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "mv") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "ret") {
            regs.PC = regs.bank[curr_instr.rs1];
        } else if (curr_instr.mnemonic == "addi") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] + std::stoul(curr_instr.imm, nullptr, 16);
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "lhu") {
            regs.bank[curr_instr.rd] = mem.memory[regs.bank[curr_instr.rs1] + std::stoul(curr_instr.imm, nullptr, 16)];
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rd] >> 16;
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "lbu") {
            regs.bank[curr_instr.rd] = mem.memory[regs.bank[curr_instr.rs1] + std::stoul(curr_instr.imm, nullptr, 16)];
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rd] >> 25;
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "lh") {
            regs.bank[curr_instr.rd] = mem.memory[regs.bank[curr_instr.rs1] + std::stoul(curr_instr.imm, nullptr, 16)];
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rd] >> 16;
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "lb") {
            regs.bank[curr_instr.rd] = mem.memory[regs.bank[curr_instr.rs1] + std::stoul(curr_instr.imm, nullptr, 16)];
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rd] >> 25;
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "sh") {
            mem.memory[regs.bank[curr_instr.rs1] + std::stoul(curr_instr.imm, nullptr, 16)] = regs.bank[curr_instr.rs2];
            mem.memory[regs.bank[curr_instr.rs1] + std::stoul(curr_instr.imm, nullptr, 16)] >>= 16;
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "sb") {
            mem.memory[regs.bank[curr_instr.rs1] + std::stoul(curr_instr.imm, nullptr, 16)] = regs.bank[curr_instr.rs2];
            mem.memory[regs.bank[curr_instr.rs1] + std::stoul(curr_instr.imm, nullptr, 16)] >>= 25;
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "mul") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] * regs.bank[curr_instr.rs2];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "mulhu") {
            regs.bank[curr_instr.rd] = static_cast<uint64_t>(regs.bank[curr_instr.rs1]) * static_cast<uint64_t>(regs.bank[curr_instr.rs2]) & 0xFFFFFFFF00000000;
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "or") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] | regs.bank[curr_instr.rs2];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "and") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] & regs.bank[curr_instr.rs2];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "xor") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] ^ regs.bank[curr_instr.rs2];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "rem") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] % regs.bank[curr_instr.rs2];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "divu") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] / regs.bank[curr_instr.rs2];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "div") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] / regs.bank[curr_instr.rs2];
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "bge") {
            if (regs.bank[curr_instr.rs1] >= regs.bank[curr_instr.rs2]) {
                regs.PC = std::stoul(curr_instr.imm, nullptr, 16);
            }
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "blt") {
            if (regs.bank[curr_instr.rs1] < regs.bank[curr_instr.rs2]) {
                regs.PC = std::stoul(curr_instr.imm, nullptr, 16);
            }
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "sll") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] << std::stoul(curr_instr.imm, nullptr, 16);
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "sltu") {
            if (regs.bank[curr_instr.rs1] < regs.bank[curr_instr.rs2]){
                regs.bank[curr_instr.rd] = 1;
            } else {
                regs.bank[curr_instr.rd] = 0;
            }
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "srl") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] >> std::stoul(curr_instr.imm, nullptr, 16);
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "sra") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] >> std::stoul(curr_instr.imm, nullptr, 16);
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "slt") {
            if (regs.bank[curr_instr.rs1] < regs.bank[curr_instr.rs2]){
                regs.bank[curr_instr.rd] = 1;
            } else {
                regs.bank[curr_instr.rd] = 0;
            }
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "bgeu") {
            if (regs.bank[curr_instr.rs1] <= regs.bank[curr_instr.rs2]) {
                regs.PC = std::stoul(curr_instr.imm, nullptr, 16);
            }
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "bne") {
            if (regs.bank[curr_instr.rs1] != regs.bank[curr_instr.rs2]) {
                regs.PC = std::stoul(curr_instr.imm, nullptr, 16);
            }
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "bltu") {
            if (regs.bank[curr_instr.rs1] > regs.bank[curr_instr.rs2]) {
                regs.PC = std::stoul(curr_instr.imm, nullptr, 16);
            }
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "beq") {
            if (regs.bank[curr_instr.rs1] == regs.bank[curr_instr.rs2]) {
                regs.PC = std::stoul(curr_instr.imm, nullptr, 16);
            }
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "andi") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] & std::stoul(curr_instr.imm, nullptr, 16);
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "xori") {
            regs.bank[curr_instr.rd] = regs.bank[curr_instr.rs1] ^ std::stoul(curr_instr.imm, nullptr, 16);
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "slti") {
            if (regs.bank[curr_instr.rs1] < std::stoul(curr_instr.imm, nullptr, 16)) {
                regs.bank[curr_instr.rd] = 1;
            } else {
                regs.bank[curr_instr.rd] = 0;
            }
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "sltiu") {
            if (regs.bank[curr_instr.rs1] < std::stoul(curr_instr.imm, nullptr, 16)) {
                regs.bank[curr_instr.rd] = 1;
            } else {
                regs.bank[curr_instr.rd] = 0;
            }
            regs.PC += 4;
        } else if (curr_instr.mnemonic == "nop") {
            
        } else if (!curr_instr.mnemonic.empty()) {
            std::cout << "Invalid instruction: " << curr_instr.mnemonic << std::endl;
            return true;
        }
        log.logInstrExecution(regs.PC, instr_info, regs.bank);
    }
    return false;
}