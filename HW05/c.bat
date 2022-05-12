cls
del *.o
del *.disass
del *.srec
del *.ihex
del *.rom

riscv64-unknown-elf-g++ -c -mabi=ilp32 -march=rv32im boot.s -g -o boot.o
riscv64-unknown-elf-g++ -c -mabi=ilp32 -march=rv32im -DUSE_MYSTDLIB -DTIME -DRISCV -g stdlib.cpp -o stdlib.o
riscv64-unknown-elf-g++ -c -mabi=ilp32 -march=rv32im -DUSE_MYSTDLIB -DTIME -DRISCV -g HW05.cpp -o HW05.o
riscv64-unknown-elf-ld -nostdlib -T rv32im.ls boot.o stdlib.o HW05.o -o HW05.elf
riscv64-unknown-elf-objcopy -O binary HW05.elf HW05.bin
riscv64-unknown-elf-objcopy -O srec HW05.elf HW05.srec
riscv64-unknown-elf-objcopy -O ihex HW05.elf HW05.ihex
riscv64-unknown-elf-objcopy -R rom HW05.elf HW05.rom
riscv64-unknown-elf-objdump -D HW05.elf > HW05.disass




