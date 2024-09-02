#include <iostream>

#define NUM_REGS 32

class registerBank {
    public:
        enum regsID {
            ZERO = 0, // HARD WIRED ZERO
            RA = 1, // RETURN_ADDRESS
            SP = 2, // STACK_POINTER
            GP = 3, // GLOBAL_POINTER
            TP = 4, // THREAD_POINTER
            T0 = 5, // TEMPORARY
            T1 = 6, // TEMPORARY
            T2 = 7, // TEMPORARY
            S0_FP = 8, // SAVED_REGISTER/FRAME_POINTER
            S1 = 9, // SAVED_REGISTER
            A0 = 10, // FUNCTION ARGUMENT/RETURN_VALUE
            A1 = 11, // FUNCTION ARGUMENT/RETURN_VALUE
            A2 = 12, //FUNCTION_ARGUMENT
            A3 = 13, //FUNCTION_ARGUMENT
            A4 = 14, //FUNCTION_ARGUMENT
            A5 = 15, //FUNCTION_ARGUMENT
            A6 = 16, //FUNCTION_ARGUMENT
            A7 = 17, //FUNCTION_ARGUMENT
            S2 = 18, // SAVED_REGISTER
            S3 = 19, // SAVED_REGISTER
            S4 = 20, // SAVED_REGISTER
            S5 = 21, // SAVED_REGISTER
            S6 = 22, // SAVED_REGISTER
            S7 = 23, // SAVED_REGISTER
            S8 = 24, // SAVED_REGISTER
            S9 = 25, // SAVED_REGISTER
            S10 = 26, // SAVED_REGISTER
            S11 = 27, // SAVED_REGISTER
            T3 = 28, //TEMPORARY
            T4 = 29, //TEMPORARY
            T5 = 30, //TEMPORARY
            T6 = 31 //TEMPORARY
        };
        uint32_t PC;

        struct registers
        {
            uint32_t reg;
            bool valid;
        };

        std::map<std::string, uint32_t> bank;
    // void write_register(uint32_t data, register regs_bank);
    // uint32_t read_register(uint32_t reg);
};