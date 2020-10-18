#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Instruction.h"
#include <llvm/IR/DebugLoc.h>
#include <llvm/IR/DebugInfoMetadata.h>

#include <string>

using namespace llvm;

namespace {

  struct SkeletonPass : public FunctionPass {
    static char ID;
    SkeletonPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {

      LLVMContext& context = F.getContext();
      auto logFunc = F.getParent()->getOrInsertFunction(
        "logdiv", Type::getVoidTy(context), Type::getInt32Ty(context)
      );

      bool ret = false;

      for (auto& B : F)
      {
        for (auto& I : B)
        {
          if (auto* op = dyn_cast<BinaryOperator>(&I)) {

            IRBuilder<> builder(op);

            if (op->getOpcode() == Instruction::FDiv) {

              const DebugLoc &debugInfo = I.getDebugLoc();

              std::string info = "Floating Point DIV at line ";
              errs() << info << debugInfo.getLine() << "\n";

              auto* left = ConstantInt::get(Type::getInt32Ty(context), 0);
              auto* right = ConstantInt::get(Type::getInt32Ty(context), debugInfo.getLine());
              auto* val = builder.CreateAdd(left, right, "linnum");

              builder.SetInsertPoint(&B, ++builder.GetInsertPoint());

              Value* args = {val};
              builder.CreateCall(logFunc, args);

              ret = true;
            }

            // Value* lhs = op->getOperand(0);
            // Value* rhs = op->getOperand(1);
            // Value* mul = builder.CreateMul(lhs, rhs);

            // for (auto& use : op->uses()) {

            //   User* user = use.getUser();
            //   user->setOperand(use.getOperandNo(), mul);
            // }

          }
        }
      }

      return ret;
    }
  };
}

char SkeletonPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new SkeletonPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerSkeletonPass);
