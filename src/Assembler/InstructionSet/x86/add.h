#pragma once

#include "EncodedInstruction.h"
#include "Registers.h"

struct EncodedInstruction add(struct Operand* operand1, struct Operand* operand2, struct Operand* operand3, struct Operand* operand4, bool lock);