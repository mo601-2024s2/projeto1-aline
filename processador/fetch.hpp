#include <iostream>
#include <fstream> 

class FetchStage {
    public:
        std::string readAssemblyFile(std::string filename);
        std::string getMainInstructions(std::string asm_file);
};
