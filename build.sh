echo *****************Build Kimia OS********************
#remove last
rm -f kernel.bin
rm -fr obj/*.*
rm -fr boot/obj/*.*
#export options
export kimia_gcc_options='-m32 -I ./include -ffreestanding -Wall -c' 
#-O2  -std=c99 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
 #-Wall -Wextra -Werror 
export kimia_nasm_options='-f elf32'
export bootloader_nasm_options='-f bin'
#------------------------------------
echo =================BOOTLOADER compile .asm files=================
cd boot/x86
nasm $bootloader_nasm_options boot1.asm -o ../obj/bootload1.bin
nasm $bootloader_nasm_options boot2.asm -o ../obj/BOOT2.BIN
cd ../..
#------------------------------------
echo ======================BOOTLOADER linker========================
#------------------------------------
echo ===================KERNEL compile .asm files===================
#[#[----------------------------kernel/x86/arch]
nasm kernel/arch/x86/boot.asm -o obj/boot.o $kimia_nasm_options
nasm kernel/arch/x86/gdt.asm -o obj/gdt.o $kimia_nasm_options
nasm kernel/arch/x86/interrupt.asm -o obj/interrupt.o $kimia_nasm_options
#nasm kernel/arch/x86/ports.asm -o obj/ports.o $kimia_nasm_options
#------------------------------------
echo ===================KERNEL compile .c files=====================
#[#[----------------------------kernel]
gcc $kimia_gcc_options kernel/main.c -o obj/main.o 
gcc $kimia_gcc_options kernel/debug_display.c -o obj/debug_display.o
#[#[----------------------------kernel/x86/arch]
gcc $kimia_gcc_options kernel/arch/x86/cpu.c -o obj/cpu.o 
#gcc $kimia_gcc_options kernel/arch/x86/ports.c -o obj/ports_c.o 
gcc $kimia_gcc_options kernel/arch/x86/descriptor_tables.c -o obj/descriptor_tables.o 
gcc $kimia_gcc_options kernel/arch/x86/timer.c -o obj/timer.o 
gcc $kimia_gcc_options kernel/arch/x86/cpu.c -o obj/cpu.o 
gcc $kimia_gcc_options kernel/arch/x86/cpu.c -o obj/cpu.o 
gcc $kimia_gcc_options kernel/arch/x86/panic.c -o obj/panic.o 
gcc $kimia_gcc_options kernel/arch/x86/ports.c -o obj/ports.o 
#[----------------------------kernel/memory]
gcc $kimia_gcc_options kernel/memory/mm.c -o obj/mm.o
#[----------------------------kernel/lib]
gcc $kimia_gcc_options kernel/lib/string.c -o obj/string.o 
gcc $kimia_gcc_options kernel/lib/mem.c -o obj/mem.o
#[----------------------------drivers/keyboard]
rm -f obj/keyb/*.o
mkdir obj/keyb
gcc $kimia_gcc_options drivers/keyboard/keyboard.c -o obj/keyb/keyboard.o 

#------------------------------------
echo =========================KERNEL linker=========================
cd obj
ld -m elf_i386 -static -T ../link.ld -o ../kernel.bin *.o keyb/*.o
cd ..
#------------------------------------
echo ======================KIMIA_OS image files========================
#rm -f kimia_os.flp 
#rm -f kimia_os.iso
#dd if=/dev/zero of=kimia_os.img count=1 bs=1M
#mkfs.vfat ./kimia_os.img

#dd status=noxfer conv=noerror if=boot/obj/bootload1.bin of=kimia_os.img  bs=512 count=1
#dd status=noxfer conv=noerror seek=1 if=kernel.bin of=kimia_os.img 
#dd status=noxfer conv=noerror seek=1 if=boot/obj/BOOT2.BIN of=kimia_os.flp 

#mkdir tmp-dir
#su
#mkfs.vfat kimia_os.flp
#mount -o loop -t vfat kimia_os.flp tmp-dir
#cp boot/obj/BOOT2.BIN tmp-dir
#cp kernel.bin tmp-dir
#umount tmp-dir
#rm -rf tmp-dir
#mkisofs -quiet -V 'KIMIA' -input-charset iso8859-1 -o kimia_os.iso -b kimia_os.flp ./
#------------------------------------
#echo =====================run KERNEL with qemu=====================
#cd ..
qemu-system-x86_64 -kernel kernel.bin
#------------------------------------
#echo =====================run KIMIA OS with qemu====================
#qemu-system-x86_64 kimia_os.img  #kimia_os.img


echo **************************!DONE!*******************************
