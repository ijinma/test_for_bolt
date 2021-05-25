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
# gcc -Wl,-q -fuse-ld=gold test.c -o test
```

### run perf and bolt:
```
# perf record -F 3999 -e cycles:u -o perf.data ./test

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
PERF2BOLT: processing basic events (without LBR)...
PERF2BOLT: read 301440 samples
PERF2BOLT: out of range samples recorded in unknown regions: 6 (0.0%)
PERF2BOLT: wrote 84 objects and 0 memory objects to perf.fdata
# llvm-bolt test -o test.bolt -data=perf.fdata -reorder-blocks=cache+ -reorder-functions=hfsort+ -split-functions=3 -split-all-cold -split-eh -dyno-stats -v=3
BOLT-INFO: Target architecture: aarch64
BOLT-INFO: BOLT version: bfa0ca9934fda54949958c8e1bc330d0d95c31d8
BOLT-INFO: first alloc address is 0x400000
BOLT-INFO: creating new program header table at address 0x600000, offset 0x200000
BOLT-INFO: enabling relocation mode
BOLT-INFO: disabling -align-macro-fusion on non-x86 platform
BOLT-INFO: setting size of function _init/1(*3) to 20 (was 0)
BOLT-INFO: setting size of function _start(*2) to 60 (was 0)
BOLT-INFO: setting size of function _fini/1(*3) to 16 (was 0)
BOLT-INFO: pre-processing profile using branch profile reader
BOLT-INFO: operating with basic samples profiling data (no LBR).
BOLT-INFO: normalizing samples by instruction count.
BOLT-INFO: Starting pass: print-stats
BOLT-INFO: 2 out of 12 functions in the binary (16.7%) have non-empty execution profile
BOLT-INFO: Finished pass: print-stats
BOLT-INFO: Starting pass: validate-internal-calls
BOLT-INFO: Finished pass: validate-internal-calls
BOLT-INFO: Starting pass: strip-rep-ret
BOLT-INFO: Finished pass: strip-rep-ret
BOLT-INFO: Starting pass: veneer-elimination
BOLT-INFO: Finished pass: veneer-elimination
BOLT-INFO: Starting pass: indirect-call-promotion
BOLT-INFO: Finished pass: indirect-call-promotion
BOLT-INFO: Starting pass: inlining
BOLT-INFO: Finished pass: inlining
BOLT-INFO: Starting pass: PLT call optimization
BOLT-INFO: Finished pass: PLT call optimization
BOLT-INFO: Starting pass: reorder-blocks
BOLT-INFO: basic block reordering modified layout of 2 (16.67%) functions
BOLT-INFO: Finished pass: reorder-blocks
BOLT-INFO: Starting pass: eliminate-unreachable
BOLT-INFO: UCE removed 0 blocks and 0 bytes of code.
BOLT-INFO: Finished pass: eliminate-unreachable
BOLT-INFO: Starting pass: split-functions
BOLT-INFO: Finished pass: split-functions
BOLT-INFO: Starting pass: loop-inversion-opt
BOLT-INFO: 0 Functions were reordered by LoopInversionPass
BOLT-INFO: Finished pass: loop-inversion-opt
BOLT-INFO: Starting pass: fix-branches
BOLT-INFO: Finished pass: fix-branches
BOLT-INFO: Starting pass: reorder-functions
BOLT-INFO: buildCallGraph: 2 nodes, 2 callsites (0 recursive), density = 0.250000, 1 callsites not processed, 0 callsites with invalid profile, used perf data for 0 stale functions.
BOLT-INFO: hfsort+ reduced the number of chains from 2 to 1
BOLT-INFO: Function reordering page layout
BOLT-INFO: ============== page 0 ==============
BOLT-INFO: -------- density = 4.382 (1928 / 440) --------
BOLT-INFO: hot func BubbleSort (360)
BOLT-INFO: start =    360 : avgCallDist = 0 : BubbleSort
BOLT-INFO: Function reordering stats
BOLT-INFO:  Number of hot functions: 1
BOLT-INFO:  Number of clusters: 1
BOLT-INFO:  Final average call distance = 0.0 (0 / 0)
BOLT-INFO:  Total Calls = 0
BOLT-INFO: Finished pass: reorder-functions
BOLT-INFO: Starting pass: print dyno-stats after optimizations
BOLT-INFO: program-wide dynostats after all optimizations before SCTC and FOP:

             5379594 : executed forward branches
             2146353 : taken forward branches
             2291537 : executed backward branches
             1904094 : taken backward branches
             3924400 : executed unconditional branches
                1928 : all function calls
                   0 : indirect calls
                   0 : PLT calls
           301433955 : executed instructions
            87745425 : executed load instructions
                   0 : executed store instructions
                   0 : taken jump table branches
                   0 : taken unknown indirect branches
            11595531 : total branches
             7974847 : taken branches
             3620684 : non-taken conditional branches
             4050447 : taken conditional branches
             7671131 : all conditional branches
                   0 : linker-inserted veneer calls

             6859665 : executed forward branches (+27.5%)
              750234 : taken forward branches (-65.0%)
              811466 : executed backward branches (-64.6%)
             2146785 : taken backward branches (+12.7%)
             3963117 : executed unconditional branches (+1.0%)
                1928 : all function calls (=)
                   0 : indirect calls (=)
                   0 : PLT calls (=)
           301474268 : executed instructions (+0.0%)
            87745425 : executed load instructions (=)
                   0 : executed store instructions (=)
                   0 : taken jump table branches (=)
                   0 : taken unknown indirect branches (=)
            11634248 : total branches (+0.3%)
             6860136 : taken branches (-14.0%)
             4774112 : non-taken conditional branches (+31.9%)
             2897019 : taken conditional branches (-28.5%)
             7671131 : all conditional branches (=)
                   0 : linker-inserted veneer calls (=)

BOLT-INFO: Finished pass: print dyno-stats after optimizations
BOLT-INFO: Starting pass: simplify-conditional-tail-calls
BOLT-INFO: Finished pass: simplify-conditional-tail-calls
BOLT-INFO: Starting pass: peepholes
BOLT-INFO: Finished pass: peepholes
BOLT-INFO: Starting pass: aligner
BOLT-INFO: Finished pass: aligner
BOLT-INFO: Starting pass: reorder-data
BOLT-INFO: Finished pass: reorder-data
BOLT-INFO: Starting pass: finalize-functions
BOLT-INFO: Finished pass: finalize-functions
BOLT-INFO: Starting pass: frame-optimizer
BOLT-INFO: Finished pass: frame-optimizer
BOLT-INFO: Starting pass: alloc-combiner
BOLT-INFO: Finished pass: alloc-combiner
BOLT-INFO: Starting pass: retpoline-insertion
BOLT-INFO: Finished pass: retpoline-insertion
BOLT-INFO: Starting pass: assign-sections
BOLT-INFO: Finished pass: assign-sections
BOLT-INFO: Starting pass: patch-entries
BOLT-INFO: Finished pass: patch-entries
BOLT-INFO: Starting pass: long-jmp
BOLT-INFO: Starting stub-insertion pass
BOLT-INFO: Inserted 0 stubs in the hot area and 0 stubs in the cold area. Shared 0 times, iterated 1 times.
BOLT-INFO: Finished pass: long-jmp
BOLT-INFO: Starting pass: inst-lowering
BOLT-INFO: Finished pass: inst-lowering
BOLT-INFO: Starting pass: lower-annotations
BOLT-INFO: Finished pass: lower-annotations
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
 #7 0x0000000001b38dd4 llvm::install_bad_alloc_error_handler(void (*)(void*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, bool), void*) /home/majin/install/tools/bolt/BOLT/llvm/lib/Support/ErrorHandling.cpp:130:0
 #8 0x0000000001b38c60 llvm::report_fatal_error(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, bool) /home/majin/install/tools/bolt/BOLT/llvm/lib/Support/ErrorHandling.cpp:86:0
 #9 0x00000000025dff60 llvm::RuntimeDyldELF::resolveAArch64Relocation(llvm::SectionEntry const&, unsigned long, unsigned long, unsigned int, long) /home/majin/install/tools/bolt/BOLT/llvm/lib/ExecutionEngine/RuntimeDyld/RuntimeDyldELF.cpp:400:0
#10 0x00000000025e2400 llvm::RuntimeDyldELF::resolveRelocation(llvm::SectionEntry const&, unsigned long, unsigned long, unsigned int, long, unsigned long, unsigned int) /home/majin/install/tools/bolt/BOLT/llvm/lib/ExecutionEngine/RuntimeDyld/RuntimeDyldELF.cpp:1014:0
#11 0x00000000025e22e8 llvm::RuntimeDyldELF::resolveRelocation(llvm::RelocationEntry const&, unsigned long) /home/majin/install/tools/bolt/BOLT/llvm/lib/ExecutionEngine/RuntimeDyld/RuntimeDyldELF.cpp:996:0
#12 0x00000000025c2db8 llvm::RuntimeDyldImpl::resolveRelocationList(llvm::SmallVector<llvm::RelocationEntry, 64u> const&, unsigned long) /home/majin/install/tools/bolt/BOLT/llvm/lib/ExecutionEngine/RuntimeDyld/RuntimeDyld.cpp:1090:0
#13 0x00000000025c31c8 llvm::RuntimeDyldImpl::applyExternalSymbolRelocations(llvm::StringMap<llvm::JITEvaluatedSymbol, llvm::MallocAllocator>) /home/majin/install/tools/bolt/BOLT/llvm/lib/ExecutionEngine/RuntimeDyld/RuntimeDyld.cpp:1096:0
#14 0x00000000025c363c llvm::RuntimeDyldImpl::resolveExternalSymbols() /home/majin/install/tools/bolt/BOLT/llvm/lib/ExecutionEngine/RuntimeDyld/RuntimeDyld.cpp:1196:0
#15 0x00000000025beab0 llvm::RuntimeDyldImpl::resolveRelocations() /home/majin/install/tools/bolt/BOLT/llvm/lib/ExecutionEngine/RuntimeDyld/RuntimeDyld.cpp:131:0
#16 0x00000000025c447c llvm::RuntimeDyld::resolveRelocations() /home/majin/install/tools/bolt/BOLT/llvm/lib/ExecutionEngine/RuntimeDyld/RuntimeDyld.cpp:1373:0
#17 0x00000000025c4568 llvm::RuntimeDyld::finalizeWithMemoryManagerLocking() /home/majin/install/tools/bolt/BOLT/llvm/lib/ExecutionEngine/RuntimeDyld/RuntimeDyld.cpp:1392:0
#18 0x00000000005e3d2c llvm::bolt::RewriteInstance::emitAndLink() /home/majin/install/tools/bolt/BOLT/bolt/src/RewriteInstance.cpp:3051:0
#19 0x00000000005d8284 llvm::bolt::RewriteInstance::run() /home/majin/install/tools/bolt/BOLT/bolt/src/RewriteInstance.cpp:820:0
#20 0x000000000040b064 main /home/majin/install/tools/bolt/BOLT/bolt/src/llvm-bolt.cpp:302:0
#21 0x0000fffbecf33f60 __libc_start_main (/lib64/libc.so.6+0x23f60)
#22 0x0000000000409ea4 _start (/home/majin/install/tools/bolt/build/bin/llvm-bolt+0x409ea4)
PLEASE submit a bug report to https://bugs.llvm.org/ and include the crash backtrace.
Stack dump:
0.      Program arguments: llvm-bolt test -o test.bolt -data=perf.fdata -reorder-blocks=cache+ -reorder-functions=hfsort+ -split-functions=3 -split-all-cold -split-eh -dyno-stats -v=3
Segmentation fault (core dumped)
```