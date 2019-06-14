#pragma once
#include <stdbool.h>

#include "EncodedInstruction.h"
#include "Registers.h"

__attribute__((const)) struct EncodedInstruction aaa(struct Operand* operand1, struct Operand* operand2, struct Operand* operand3, struct Operand* operand4, struct x86_instruction_arguments* args);
