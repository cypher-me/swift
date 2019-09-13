//===--- ParseableInterfaceSupport.h - swiftinterface files -----*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2019 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_FRONTEND_PARSEABLEINTERFACESUPPORT_H
#define SWIFT_FRONTEND_PARSEABLEINTERFACESUPPORT_H

#include "swift/Basic/LLVM.h"
#include "swift/Basic/Version.h"
#include "llvm/Support/Regex.h"

#define SWIFT_INTERFACE_FORMAT_VERSION_KEY "swift-interface-format-version"
#define SWIFT_COMPILER_VERSION_KEY "swift-compiler-version"
#define SWIFT_MODULE_FLAGS_KEY "swift-module-flags"

namespace swift {

class ModuleDecl;

/// Options for controlling the generation of the .swiftinterface output.
struct ParseableInterfaceOptions {
  /// Should we prefer printing TypeReprs when writing out types in a module
  /// interface, or should we fully-qualify them?
  bool PreserveTypesAsWritten = false;

  /// Copy of all the command-line flags passed at .swiftinterface
  /// generation time, re-applied to CompilerInvocation when reading
  /// back .swiftinterface and reconstructing .swiftmodule.
  std::string ParseableInterfaceFlags;
};

extern version::Version InterfaceFormatVersion;

llvm::Regex getSwiftInterfaceFormatVersionRegex();
llvm::Regex getSwiftInterfaceModuleFlagsRegex();

/// Emit a stable module interface for \p M, which can be used by a client
/// source file to import this module, subject to options given by \p Opts.
///
/// Unlike a serialized module, the textual format generated by
/// emitModuleInterface is intended to be stable across compiler versions while
/// still describing the full ABI of the module in question.
///
/// The initial plan for this format can be found at
/// https://forums.swift.org/t/plan-for-module-stability/14551/
///
/// \return true if an error occurred
///
/// \sa swift::serialize
bool emitParseableInterface(raw_ostream &out,
                            ParseableInterfaceOptions const &Opts,
                            ModuleDecl *M);

} // end namespace swift

#endif
