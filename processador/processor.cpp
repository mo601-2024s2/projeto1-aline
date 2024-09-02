#include <iostream>
#include <string>
#include <vector>
#include "fetch.hpp"
#include "execute.hpp"

int main(int argc, char** argv) {
    FetchStage fetch_stage;
    decodeInstruction decode_instr;
    executeInstruction execute_instr;
    std::string asm_file = fetch_stage.readAssemblyFile(argv[1]);
    std::string asm_instructions = fetch_stage.getMainInstructions(asm_file);
    decode_instr.instr_info = decode_instr.parseInstruction(asm_instructions);
    if (execute_instr.execution(decode_instr.instr_info)) {
        std::cout << "Execution failed" << std::endl;
        return 1;
    }
    return 0;
}