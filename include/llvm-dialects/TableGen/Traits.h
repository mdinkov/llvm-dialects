/*
 * Copyright (c) 2022 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cstdint>
#include <string>

#include "llvm/ADT/StringRef.h"

namespace llvm {
class Record;
}

namespace llvm_dialects {

class GenDialectsContext;

class Trait {
public:
  enum class Kind : uint8_t {
    LlvmAttributeTrait,
  };

  virtual ~Trait() = default;

  virtual void init(GenDialectsContext *context, llvm::Record *record);

  Kind getKind() const { return m_kind; }
  llvm::Record *getRecord() const { return m_record; }
  llvm::StringRef getName() const;

protected:
  Trait(Kind kind) : m_kind(kind) {}

private:
  const Kind m_kind;
  llvm::Record *m_record = nullptr;
};

class LlvmAttributeTrait : public Trait {
public:
  LlvmAttributeTrait() : Trait(Kind::LlvmAttributeTrait) {}

  void init(GenDialectsContext *context, llvm::Record *record) override;

  llvm::StringRef getLlvmEnum() const { return m_llvmEnum; }

  static bool classof(const Trait *t) {
    return t->getKind() == Kind::LlvmAttributeTrait;
  }

private:
  std::string m_llvmEnum;
};

} // namespace llvm_dialects
