# Chapter 7 --- Linking
### Object file - Three forms
+ relocatable object file
+ executable object file
+ shared object file

>To get a relocatable object file, with gcc we can use the command _**gcc -c xxx.c**_, then we can get a relocatable object file _**xxx.o**_, which is in elf64 in 64-bits linux system. And then to get an executable object file, with gcc we can use the command _**gcc -o prog a.o b.o c.o**_, then we can get an executable object file _**prog**_, which is the executable file in linux.

### Static linking
1. Symbol resolution
2. Relocation

### The ELF64 format
<center>ELF64</center>|<center>Descriptions</center>|
:---:|:--:|
ELF header| |
.text|To record the meachine code|
.rodata|To store the read only data|
.data|To store the global or static variables,<br>which is initialized but not zero|
.bss|To store the global or static variables,<br>which is defined but not initialized ,<br>or will be initialized to zero at runtime|
.symtab|To store the symbol infomarions|
.rel.text|A list of locations that are needed to be modified in _.text_ |
.rel.data|A list of locations that are needed to be modified in _.data_ |
.debug| |
.line| |
.strtab| |
Section header table| |

###### Relocation entries
```C
typedef struct{
  long offset;/* the place where to be modified */
  long type: 32,/* Relocation type */
       symbol: 32;/* the address where the referenced symbol are */
  long addend;/* bias */
} Elf64_Rela;
```
> ###### Type
+ R_X86_64_PC32
+ R_X86_64_32

### Symbol resolution
### Relocation
### Linking with static libraries
### Dynamic linking with shared libraries
### Loading and linking shared libraries from applications
### Position-independent code (PIC)
### Library interpositioning
#### 1. at compile time
#### 2. at link time
#### 3. at runtime
