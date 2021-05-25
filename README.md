# test_for_bolt

## bolt_error_1:
```
# gcc -Wl,-q -fuse-ld=gold bolt_error_1/test_1.c -o test
```
```
# perf record -F 3999 -e cycles:u -o perf.data ./test
```
```
# perf2bolt -p perf.data -o perf.fdata test -nl
```
```
# llvm-bolt test -o test.bolt -data=perf.fdata -reorder-blocks=cache+ -reorder-functions=hfsort+ -split-functions=3 -split-all-cold -split-eh -dyno-stats -v=3
<unknown>:0: error: invalid fixup for 64-bit load/store instruction
<unknown>:0: error: invalid fixup for add (uimm12) instruction
BOLT-INFO: padding code to 0xa00000 to accommodate hot text
LLVM ERROR: Relocation type not implemented yet!
 #0 0x0000000001be786c llvm::sys::PrintStackTrace(llvm::raw_ostream&, int) /home/majin/install/tools/bolt/BOLT/llvm/lib/Support/Unix/Signals.inc:565:0
 #1 0x0000000001be7944 PrintStackTraceSignalHandler(void*) /home/majin/install/tools/bolt/BOLT/llvm/lib/Support/Unix/Signals.inc:632:0
 #2 0x0000000001be5b88 llvm::sys::RunSignalHandlers() /home/majin/install/tools/bolt/BOLT/llvm/lib/Support/Signals.cpp:76:0
 #3 0x0000000001be7248 SignalHandler(int) /home/majin/install/tools/bolt/BOLT/llvm/lib/Support/Unix/Signals.inc:407:0
 #4 0x0000fffbed4a0784 (linux-vdso.so.1+0x784)
 #5 0x0000fffbecf46660 raise (/lib64/libc.so.6+0x36660)
 #6 0x0000fffbecf47a0c abort (/lib64/libc.so.6+0x37a0c)
```

## bolt_error_2:
```
# gcc -Wl,-q -fuse-ld=gold -O2 bolt_error_2/test_2.c -o test
```
```
# perf record -F 3999 -e cycles:u -o perf.data ./test
```
```
# perf2bolt -p perf.data -o perf.fdata test -nl
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
