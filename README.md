
# LLVM Loop Unroll Optimization Pass

## 🛠️ Overview

This project demonstrates how to build and use a custom **LLVM optimization pass** to perform **loop unrolling** on LLVM Intermediate Representation (IR). The custom pass is implemented as a shared library plugin and can be loaded using the `opt` tool from LLVM.

Loop unrolling is a classic compiler optimization that reduces loop overhead and potentially improves performance by executing multiple iterations of a loop in a single iteration.

---

## 📁 Project Structure

```
llvm-loop-optimizer/
├── build/                      # Contains compiled plugin DLL and output files
├── include/                    # Header files (if any)
├── src/                        # Source code for custom pass
│   └── LoopUnrollPass.cpp      # Implementation of loop unroll pass
├── test/                       # Test case files
│   └── test.cpp                # Source file with loops to optimize
├── CMakeLists.txt              # CMake configuration
└── README.md                   # Project documentation
```

---

## ⚙️ Requirements

- LLVM (version 12 or newer recommended)
- CMake
- Clang / opt (from LLVM)
- MSYS2/MinGW (on Windows)
- C++ compiler

---

## 🧰 Building the Plugin

1. **Clone this repository**:

```bash
git clone https://github.com/yourusername/llvm-loop-optimizer.git
cd llvm-loop-optimizer
```

2. **Create a build directory**:

```bash
mkdir build && cd build
```

3. **Configure the build using CMake**:

```bash
cmake ..
```

4. **Build the plugin**:

```bash
cmake --build .
```

After successful build, the plugin shared library (`libLoopUnrollPass.dll` on Windows or `.so` on Linux) will be located in the `build/` directory.

---

## 🧪 Running the Optimization

### Step 1: Compile the Test File to LLVM IR

From the project root:

```bash
clang++ -S -emit-llvm ./test/test.cpp -o test.ll
```

This generates `test.ll` — the LLVM IR of your C++ file.

---

### Step 2: Apply the Loop Unroll Pass

```bash
opt -load-pass-plugin ./libLoopUnrollPass.dll -passes=loop-unroll -S test.ll -o optimized.ll
```

- `-load-pass-plugin`: Loads your custom pass.
- `-passes=loop-unroll`: Applies your custom pass.
- `-S`: Outputs human-readable LLVM IR.
- `optimized.ll`: The transformed IR file.

---

## 🧾 Expected Output

- **Before**: `test.ll` contains loop structures, `br` instructions, and PHI nodes.
- **After**: `optimized.ll` should contain **duplicated loop bodies**, **fewer branches**, and possibly **flattened control flow**.

If `optimized.ll` is unreadable (binary), you may have missed the `-S` flag. Add it to get IR output in text format.

---

## 🔍 Sample Input (test.cpp)

```cpp
void loop_example() {
    int arr[4] = {1, 2, 3, 4};
    for (int i = 0; i < 4; ++i) {
        arr[i] = arr[i] + 1;
    }
}
```

---

## 🧠 Tips for Effective Optimization

- Prefer loops with **constant bounds**.
- Use `#pragma clang loop unroll(full)` for aggressive unrolling.
- Use `-O1` or `-O2` while compiling for cleaner IR.
- Avoid complex loops or nested control flows while testing your plugin initially.

---

## 🐛 Troubleshooting

### Problem: `Plugin entry point not found`

**Cause**: Plugin is missing the correct registration mechanism (like `PassPluginLibraryInfo`).

**Fix**: Make sure your `LoopUnrollPass.cpp` includes:

```cpp
extern "C" ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "LoopUnrollPass", "v0.1",
        [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "loop-unroll") {
                        FPM.addPass(LoopUnrollPass());
                        return true;
                    }
                    return false;
                });
        }
    };
}
```

---

## 📚 References

- [LLVM Passes Documentation](https://llvm.org/docs/WritingAnLLVMPass.html)
- [Writing New Passes in LLVM (official)](https://llvm.org/docs/NewPassManager.html)
- [Loop Unrolling - LLVM Analysis](https://llvm.org/docs/LoopUnroll.html)

---

## 📃 License

This project is open-source under the [MIT License](LICENSE).

---

## 👨‍💻 Author

**Your Name**  
[GitHub](https://github.com/yourusername)
