#include <sstream>
#include <stdint.h>
#include "fetch.hpp"

std::string FetchStage::readAssemblyFile(std::string filename) {
    std::stringstream asm_file_output;
    std::string read_asm_file;
    std::ifstream asm_file(filename);
    while (getline(asm_file, read_asm_file)) {
        asm_file_output << read_asm_file << "\n";
    }
    asm_file.close();
    return asm_file_output.str();
}

std::string FetchStage::getMainInstructions(std::string asm_file) {
    std::stringstream instructions;
    size_t start = asm_file.find("<_start>:");
    uint64_t end = asm_file.find("Disassembly of section .comment:");
    uint64_t end1 = asm_file.find("Disassembly of section .rodata:");

    if (end1 < end) {
        end = end1;
    }
    start -= 9;
    for (size_t i = start; i < end; i++) {
        instructions << asm_file[i];
    }
    instructions << "\n";
    return instructions.str();
}