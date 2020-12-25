//===-- AMDGPUMCTargetDesc.h - AMDGPU Target Descriptions -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
/// \file
/// Provides AMDGPU specific target descriptions.
//
//===----------------------------------------------------------------------===//
//

#ifndef LLVM_LIB_TARGET_AMDGPU_MCTARGETDESC_AMDGPUMCTARGETDESC_H
#define LLVM_LIB_TARGET_AMDGPU_MCTARGETDESC_AMDGPUMCTARGETDESC_H

#include <memory>

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class StringRef;
class Target;
class Triple;
class raw_pwrite_stream;

enum AMDGPUDwarfFlavour { Wave64 = 0, Wave32 = 1 };

MCRegisterInfo *createGCNMCRegisterInfo(AMDGPUDwarfFlavour DwarfFlavour);

MCCodeEmitter *createR600MCCodeEmitter(const MCInstrInfo &MCII,
                                       const MCRegisterInfo &MRI,
                                       MCContext &Ctx);
MCInstrInfo *createR600MCInstrInfo();

MCCodeEmitter *createSIMCCodeEmitter(const MCInstrInfo &MCII,
                                     const MCRegisterInfo &MRI,
                                     MCContext &Ctx);

MCAsmBackend *createAMDGPUAsmBackend(const Target &T,
                                     const MCSubtargetInfo &STI,
                                     const MCRegisterInfo &MRI,
                                     const MCTargetOptions &Options);

std::unique_ptr<MCObjectTargetWriter>
createAMDGPUELFObjectWriter(bool Is64Bit, uint8_t OSABI,
                            bool HasRelocationAddend, uint8_t ABIVersion);
} // End llvm namespace

#define GET_REGINFO_ENUM
#include "AMDGPUGenRegisterInfo.inc"

#define GET_REGINFO_ENUM
#include "R600GenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_OPERAND_ENUM
#define GET_INSTRINFO_SCHED_ENUM
#include "AMDGPUGenInstrInfo.inc"

#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_OPERAND_ENUM
#define GET_INSTRINFO_SCHED_ENUM
#include "R600GenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "AMDGPUGenSubtargetInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "R600GenSubtargetInfo.inc"

#endif
