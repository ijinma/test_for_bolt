# test_for_bolt

### compile:

```
# gcc -v 
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_ WRAPPER=/home/lhl/workspace/gcc/gcc-install-9.3.0-base/libexec/gcc/aarch64-unknown-linux-gnu/9.3.0/lto-wrapper
Target: aarch64 unknown Linux GNU
Configured with: ../gcc-9.3.0/configuration --prefix=/home/lhl/workspace/gcc/gcc-install-9.3.0-base --enable languages = C, c++, objc, obj-c++
Thread model: POSIX
GCC version 9.3.0 (GCC)
```
```
# gcc -Wl,-q -fuse-ld=gold -O2 test.c -o test
```

### run perf and bolt:
```
# perf record -F 3999 -e cycles:u -o perf.data ./test
```

```
# perf2bolt -p perf.data -o perf.fdata test -nl
PERF2BOLT: Starting data aggregation job for perf.data
PERF2BOLT: spawning perf job to read events without LBR
PERF2BOLT: spawning perf job to read mem events
PERF2BOLT: spawning perf job to read process events
PERF2BOLT: spawning perf job to read task events
BOLT-INFO: Target architecture: aarch64
BOLT-INFO: BOLT version: bfa0ca9934fda54949958c8e1bc330d0d95c31d8
BOLT-INFO: first alloc address is 0x400000
BOLT-INFO: creating new program header table at address 0x600000, offset 0x200000
BOLT-INFO: enabling relocation mode
BOLT-INFO: disabling -align-macro-fusion on non-x86 platform
BOLT-INFO: enabling strict relocation mode for aggregation purposes
BOLT-INFO: pre-processing profile using perf data aggregator
BOLT-WARNING: build-id will not be checked because we could not read one from input binary
PERF2BOLT: waiting for perf mmap events collection to finish...
PERF2BOLT: parsing perf-script mmap events output
PERF2BOLT: waiting for perf task events collection to finish...
PERF2BOLT: parsing perf-script task events output
PERF2BOLT: input binary is associated with 1 PID(s)
PERF2BOLT: waiting for perf events collection to finish...
PERF2BOLT: parsing basic events (without LBR)...
perf2bolt: /home/majin/install/tools/bolt/BOLT/llvm/include/llvm/MC/MCInst.h:80: int64_t llvm::MCOperand::getImm() const: Assertion `isImm() && "This is not an immediate"' failed.
 #0 0x0000000001be786c llvm::sys::PrintStackTrace(llvm::raw_ostream&, int) /home/majin/install/tools/bolt/BOLT/llvm/lib/Support/Unix/Signals.inc:565:0
 #1 0x0000000001be7944 PrintStackTraceSignalHandler(void*) /home/majin/install/tools/bolt/BOLT/llvm/lib/Support/Unix/Signals.inc:632:0
 #2 0x0000000001be5b88 llvm::sys::RunSignalHandlers() /home/majin/install/tools/bolt/BOLT/llvm/lib/Support/Signals.cpp:76:0
 #3 0x0000000001be7248 SignalHandler(int) /home/majin/install/tools/bolt/BOLT/llvm/lib/Support/Unix/Signals.inc:407:0
 #4 0x0000fffcfbba0784 (linux-vdso.so.1+0x784)
 #5 0x0000fffcfb646660 raise (/lib64/libc.so.6+0x36660)
 #6 0x0000fffcfb647a0c abort (/lib64/libc.so.6+0x37a0c)
 #7 0x0000fffcfb63fb0c (/lib64/libc.so.6+0x2fb0c)
 #8 0x0000fffcfb63fb8c (/lib64/libc.so.6+0x2fb8c)
 #9 0x0000000000418d4c llvm::MCOperand::getImm() const /home/majin/install/tools/bolt/BOLT/llvm/include/llvm/MC/MCInst.h:80:0
#10 0x0000000001c0038c (anonymous namespace)::AArch64MCPlusBuilder::evaluateBranch(llvm::MCInst const&, unsigned long, unsigned long, unsigned long&) const /home/majin/install/tools/bolt/BOLT/bolt/src/Target/AArch64/AArch64MCPlusBuilder.cpp:399:0
#11 0x0000000000497f7c llvm::bolt::BinaryFunction::disassemble() /home/majin/install/tools/bolt/BOLT/bolt/src/BinaryFunction.cpp:1145:0
#12 0x00000000005e26a8 llvm::bolt::RewriteInstance::disassembleFunctions() /home/majin/install/tools/bolt/BOLT/bolt/src/RewriteInstance.cpp:2772:0
#13 0x00000000005d8238 llvm::bolt::RewriteInstance::run() /home/majin/install/tools/bolt/BOLT/bolt/src/RewriteInstance.cpp:805:0
#14 0x000000000040b064 main /home/majin/install/tools/bolt/BOLT/bolt/src/llvm-bolt.cpp:302:0
#15 0x0000fffcfb633f60 __libc_start_main (/lib64/libc.so.6+0x23f60)
#16 0x0000000000409ea4 _start (/home/majin/install/tools/bolt/build/bin/llvm-bolt+0x409ea4)
PLEASE submit a bug report to https://bugs.llvm.org/ and include the crash backtrace.
Stack dump:
0.      Program arguments: perf2bolt -p perf.data -o perf.fdata test -nl
Segmentation fault (core dumped)
```