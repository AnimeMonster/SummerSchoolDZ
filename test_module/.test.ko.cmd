cmd_/home/student/test/test.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/student/test/test.ko /home/student/test/test.o /home/student/test/test.mod.o ;  true
