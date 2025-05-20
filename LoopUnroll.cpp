#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"

using namespace llvm;

namespace {
struct LoopUnrollPass : PassInfoMixin<LoopUnrollPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    // Your pass logic here
    return PreservedAnalyses::all();
  }
};
} // namespace

// This is the required entry point for the New Pass Manager
extern "C" ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION,        // API version (must be exact)
    "LoopUnrollPass",               // Plugin name
    "v0.1",                         // Plugin version
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
