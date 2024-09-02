ARCH=riscv
CROSS_COMPILER=riscv32-unknown-elf-gcc
PROJECT_PATH=$HOME/projeto1
ACSTONE_PATH=$PROJECT_PATH/test/ACStone
PROCESSOR_PATH=$PROJECT_PATH/processador

DISASM_EXT=.disasm
LOG_EXT=.log
ASM_FILENAME=*.riscv
DISASM_FILENAME=*.disasm

RESULTADO=$PROJECT_PATH/resultado

cd $ACSTONE_PATH

make clean
make build ARCH=${ARCH} CROSS_COMPILER=${CROSS_COMPILER}

for i in $ASM_FILENAME
do
    riscv32-unknown-elf-objdump --disassemble-all $i > ${i}${DISASM_EXT}
done
 
cd $PROCESSOR_PATH
make clean
make

cd $ACSTONE_PATH


if [ ! -d $RESULTADO ]; then
    mkdir $RESULTADO
fi

for i in ${DISASM_FILENAME}
do
    echo "Processing: $i"
    echo "Writing: ${i}${LOG_EXT}"
    ${PROCESSOR_PATH}/processor ${i} > ${i}${LOG_EXT}
    mv ${i}${LOG_EXT} $RESULTADO
done

