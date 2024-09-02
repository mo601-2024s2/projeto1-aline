#include "decode.hpp"

std::map<uint32_t, decodeInstruction::instrInfo> decodeInstruction::parseInstruction(std::string asm_instructions) {
    std::istringstream asm_string(asm_instructions);
    std::map<uint32_t, instrInfo> instructions_info;
    std::stringstream instr_str; 
    std::string instr_line;
    size_t pos, start, end;
    instrInfo instr_info;

    while(std::getline(asm_string, instr_line)) {
        if (instr_line.find(">:") != std::string::npos ||
            instr_line.length() == 0) {
            continue; 
        } else {
            pos = instr_line.find(":");
            start = pos - 5;
            end = pos;
            instr_str.str("");
            for (size_t i = start; i < end; i++) {
                instr_str << instr_line[i];
            }
            instr_info.pc = instr_str.str();
            // instr_info.pc = std::stoul(instr_str.str(), nullptr, 16);

            end++;
            while (instr_line[end] == ' ' || instr_line[end] == '\t') {
                end++;
            }

            start = end;
            end += 8;
            instr_str.str("");
            for (size_t i = start; i < end; i++) {
                instr_str << instr_line[i];
            }
            instr_info.instr = instr_str.str();
            // instr_info.instr = std::stoul(instr_str.str(), nullptr, 16);

            end++;
            while (instr_line[end] == ' ' || instr_line[end] == '\t') {
                end++;
            }

            instr_str.str("");
            while (instr_line[end] != ' ' && instr_line[end] != '\t' && !isdigit(instr_line[end]) && end != instr_line.length()) {
                instr_str << instr_line[end];
                end++;
            }
            instr_info.mnemonic = instr_str.str();

            end++;
            while (instr_line[end] == ' ' || instr_line[end] == '\t') {
                end++;
            }

            instr_str.str("");
            if (instr_info.mnemonic == "lui") {
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rs1 = "";
                instr_info.rs2 = "";
            } else if (instr_info.mnemonic == "mv") {
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && instr_line[end] != ',' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();
                instr_info.rs2 = "";
                instr_info.imm = "";
            } else if (instr_info.mnemonic == "li") {
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();

                end++;
                instr_str.str("");
                while (end != instr_line.length()){
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rs1 = "";
                instr_info.rs2 = "";
            } else if (instr_info.mnemonic == "lw" || 
                       instr_info.mnemonic == "lhu" || 
                       instr_info.mnemonic == "lh" || 
                       instr_info.mnemonic == "lbu" || 
                       instr_info.mnemonic == "lb") {
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != '(') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ')' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();
                instr_info.rs2 = "";
            } else if (instr_info.mnemonic == "sw" || 
                       instr_info.mnemonic == "sh" || 
                       instr_info.mnemonic == "sb") {
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs2 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != '(') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ')' ) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();
                instr_info.rd = "";
            } else if (instr_info.mnemonic == "jal") {
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rd = "ra";
                instr_info.rs1 = "";
                instr_info.rs2 = "";
            } else if (instr_info.mnemonic == "add" || 
                       instr_info.mnemonic == "mul" || 
                       instr_info.mnemonic == "mulhu" || 
                       instr_info.mnemonic == "or" || 
                       instr_info.mnemonic == "and" || 
                       instr_info.mnemonic == "sub" || 
                       instr_info.mnemonic == "xor" ||
                       instr_info.mnemonic == "rem" ||
                       instr_info.mnemonic == "divu" ||
                       instr_info.mnemonic == "div") {
                bool digit = false;
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    if (isalpha(instr_line[end])) {
                        digit = true;
                    }
                    end++;
                }
                if (digit) {
                    instr_info.rs2 = instr_str.str();
                    instr_info.imm = "";
                } else {
                    instr_info.imm = instr_str.str();
                    instr_info.mnemonic = "addi";
                    instr_info.rs2 = "";
                }

            } else if (instr_info.mnemonic == "bgez") {
                instr_info.mnemonic = "bge";
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rs2 = "0";
                instr_info.rd = "";
            } else if (instr_info.mnemonic == "blt") {
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs2 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rd = "";
            } else if (instr_info.mnemonic == "sll" || 
                       instr_info.mnemonic == "sltu" || 
                       instr_info.mnemonic == "srl" || 
                       instr_info.mnemonic == "sra" || 
                       instr_info.mnemonic == "slt") {
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs2 = instr_str.str();
                instr_info.imm = "";
            } else if (instr_info.mnemonic == "bgeu") {
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs2 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rd = "";
            } else if (instr_info.mnemonic == "bne" || 
                       instr_info.mnemonic == "bltu" || 
                       instr_info.mnemonic == "bge" || 
                       instr_info.mnemonic == "beq") {
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs2 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rd = "";
            } else if (instr_info.mnemonic == "j") {
                instr_info.mnemonic = "jal";
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rs1 = "";
                instr_info.rs2 = "";
                instr_info.rd = "0";
            } else if (instr_info.mnemonic == "zext.b") {
                instr_info.mnemonic = "andi";
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();
                instr_info.imm = "0xff";
                instr_info.rs2 = "";
            } else if (instr_info.mnemonic == "bnez") {
                instr_info.mnemonic = "bne";
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rs2 = "0";
                instr_info.rd = "";
            } else if (instr_info.mnemonic == "bgtz") {
                instr_info.mnemonic = "blt";
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs2 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rs1 = "0";
                instr_info.rd = "";
            } else if (instr_info.mnemonic == "beqz") {
                instr_info.mnemonic = "beq";
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rs2 = "0";
                instr_info.rd = "";
            } else if (instr_info.mnemonic == "bltz") {
                instr_info.mnemonic = "blt";
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rs2 = "0";
                instr_info.rd = "";
            } else if (instr_info.mnemonic == "not") {
                instr_info.mnemonic = "xori";
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();
                instr_info.imm = "-1";
                instr_info.rs2 = "";
            } else if (instr_info.mnemonic == "slti" || instr_info.mnemonic == "sltiu") {
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();

                end++;                
                instr_str.str("");
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();

                end++;
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rs2 = "";
            } else if (instr_info.mnemonic == "jr") {
                instr_info.mnemonic = "jalr";
                while (instr_line[end] != ' ' && instr_line[end] != '\t' && instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();
                instr_info.rd = "0";
                instr_info.imm = "0";
                instr_info.rs2 = "";
            } else if (instr_info.mnemonic == "neg") {
                instr_info.mnemonic = "sub";
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();
                
                end++;                
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs2 = instr_str.str();
                instr_info.rs1 = "0";
                instr_info.imm = "";
            } else if (instr_info.mnemonic == "seqz") {
                instr_info.mnemonic = "sltiu";
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();
                
                end++;                
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs1 = instr_str.str();
                instr_info.imm = "1";
                instr_info.rs2 = "";
            } else if (instr_info.mnemonic == "blez") {
                instr_info.mnemonic = "bge";
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs2 = instr_str.str();
                
                end++;                
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.imm = instr_str.str();
                instr_info.rs1 = "0";
                instr_info.rd = "";
            } else if (instr_info.mnemonic == "snez") {
                instr_info.mnemonic = "sltu";
                while (instr_line[end] != ',') {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rd = instr_str.str();
                
                end++;                
                instr_str.str("");
                while (instr_line[end] != ' ' && end != instr_line.length()) {
                    instr_str << instr_line[end];
                    end++;
                }
                instr_info.rs2 = instr_str.str();
                instr_info.imm = "";
                instr_info.rs2 = "0";
            } else if (instr_info.mnemonic == "ret") {
                instr_info.rs1 = "ra";
                instr_info.rd = "0";
                instr_info.imm = "0";
                instr_info.rs2 = "";
            }
            else {
                instr_info.rd = "";
                instr_info.rs1 = "";
                instr_info.rs2 = "";
                instr_info.imm = "";
            }
            instructions_info.insert({static_cast<uint32_t>(std::stoul(instr_info.pc, nullptr, 16)), instr_info});
        }
        instr_str.clear();
    }
    return instructions_info;
}