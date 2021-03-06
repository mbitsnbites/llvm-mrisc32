//===-- MRISC32Subtarget.h - Define Subtarget for the MRISC32 -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the MRISC32 specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MRISC32_MRISC32SUBTARGET_H
#define LLVM_LIB_TARGET_MRISC32_MRISC32SUBTARGET_H

#include "MRISC32FrameLowering.h"
#include "MRISC32ISelLowering.h"
#include "MRISC32InstrInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include <string>

#define GET_SUBTARGETINFO_HEADER
#include "MRISC32GenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class MRISC32Subtarget : public MRISC32GenSubtargetInfo {
  Triple TargetTriple;
  virtual void anchor();
  bool UseSoftMulDiv;
  bool UseSoftFloat;

  MRISC32InstrInfo InstrInfo;
  MRISC32TargetLowering TLInfo;
  SelectionDAGTargetInfo TSInfo;
  MRISC32FrameLowering FrameLowering;

  /// Initializes using the passed in CPU and feature strings so that we can
  /// use initializer lists for subtarget initialization.
  MRISC32Subtarget &initializeSubtargetDependencies(StringRef CPU, StringRef FS);

public:
  MRISC32Subtarget(const Triple &TT, const std::string &CPU,
                   const std::string &FS, const TargetMachine &TM);

  // Parses features string setting specified subtarget options. The
  // definition of this function is auto-generated by tblgen.
  void ParseSubtargetFeatures(StringRef CPU, StringRef FS);

  // Overridden virtual methods.
  const MRISC32InstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const TargetFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
  const MRISC32RegisterInfo *getRegisterInfo() const override {
    return &InstrInfo.getRegisterInfo();
  }
  const MRISC32TargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const SelectionDAGTargetInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  }

  // Custom methods.
  bool useSoftMulDiv() const { return UseSoftMulDiv; }
  bool useSoftFloat() const { return UseSoftFloat; }
};

} // end namespace llvm

#endif
