
template<std::int32_t N>
constexpr bool is_parameters_count(const command_type cmd) noexcept {
	if constexpr (N == 0) {
		return cmd > commands_0_parameters_begin & cmd < commands_0_parameters_end;
	} else if constexpr (N == 1) {
		return cmd > commands_1_parameters_begin & cmd < commands_1_parameters_end;
	} else if constexpr (N == 2) {
		return cmd > commands_2_parameters_begin & cmd < commands_2_parameters_end;
	} else {
		return false;
	}
}

constexpr bool is_command(const command_type cmd) noexcept {
	return (cmd > commands_0_parameters_begin & cmd < commands_0_parameters_end)
	|      (cmd > commands_1_parameters_begin & cmd < commands_1_parameters_end)
	|      (cmd > commands_2_parameters_begin & cmd < commands_2_parameters_end);
}

constexpr std::int32_t parameters_count(const command_type cmd) noexcept {
	return static_cast<std::int32_t>(0xFC & (cmd >> 6));
}

constexpr std::string_view to_string(const command_type cmd) noexcept {
	if (is_parameters_count<0>()) {
		switch (cmd) {
			case interrupt:   return "int";
			case call_return: return "ret";
			case leave:       return "lve";
			default: break;
		}
	}

	if (is_parameters_count<1>(cmd)) {
		switch (cmd) {
			case push:               return "psh";
			case push_literal:       return "psh";
			case pop:                return "pop";
			case increment:          return "inc";
			case decrement:          return "dec";
			case jump:               return "jmp";
			case jump_equal:         return "jeq";
			case jump_not_equal:     return "jne";
			case jump_less:          return "jls";
			case jump_less_equal:    return "jle";
			case jump_greater:       return "jgr";
			case jump_greater_equal: return "jge";
			case invert:             return "inv";

			default: break;
		}
	}

	if (is_parameters_count<2>(cmd)) {
		switch (cmd) {
			case compare:                 return "cmp";
			case compare_address_literal: return "cmp";
			case move:                    return "mov";
			case move_literal:            return "mov";
			case swap:                    return "swp";
			case sum:                     return "sum";
			case sum_literal:             return "sum";
			case subtract:                return "sub";
			case subtract_literal:        return "sub";
			case multiply:                return "mul";
			case multiply_literal:        return "mul";
			case divide:                  return "div";
			case divide_literal:          return "div";
			case divide_module:           return "mod";
			case divide_module_literal:   return "mod";
			case bin_and:                 return "and";
			case bin_and_literal:         return "and";
			case bin_or:                  return "or";
			case bin_or_literal:          return "or";
			case bin_nand:                return "nan";
			case bin_nand_literal:        return "nan";
			case bin_xor:                 return "xor";
			case bin_xor_literal:         return "xor";
			case bin_shift:               return "sft";
			case bin_rotate:              return "rot";

			default: break;
		}
	}

	return {};
}

constexpr command_type from_string(const std::string_view cmd) noexcept {
	if (std::size(cmd) > 3) return command_type::none;
	if (cmd == "+++") return increment;
	if (cmd == "---") return decrement;

	switch (cmd[0]) {
		case 'c':
			if (cmd[1] == 'm' & cmd[2] == 'p') return compare;
			break;
		case 'd':
			if (cmd[1] == 'e' & cmd[2] == 'c') return decrement;
			if (cmd[1] == 'i' & cmd[2] == 'v') return divide;
			break;
		case 'i':
			if (cmd[1] == 'n' & cmd[2] == 'c') return increment;
			if (cmd[1] == 'n' & cmd[2] == 'v') return invert;
			if (cmd[1] == 'n' & cmd[2] == 't') return interrupt;
			break;
		case 'j':
			if (cmd[1] == 'm' & cmd[2] == 'p') return jump;
			if (cmd[1] == 'e' & cmd[2] == 'q') return jump_equal;
			if (cmd[1] == 'n' & cmd[2] == 'e') return jump_not_equal;
			if (cmd[1] == 'l' & cmd[2] == 's') return jump_less;
			if (cmd[1] == 'l' & cmd[2] == 'e') return jump_less_equal;
			if (cmd[1] == 'g' & cmd[2] == 's') return jump_greater;
			if (cmd[1] == 'g' & cmd[2] == 'e') return jump_greater_equal;

			// Aliases
			if (cmd[1] == '=' & cmd[2] == '=') return jump_equal;
			if (cmd[1] == '!' & cmd[2] == '=') return jump_not_equal;
			if (cmd[1] == '<' & cmd[2] == '<') return jump_less;
			if (cmd[1] == '<' & cmd[2] == '=') return jump_less_equal;
			if (cmd[1] == '>' & cmd[2] == '>') return jump_greater;
			if (cmd[1] == '>' & cmd[2] == '=') return jump_greater_equal;

			break;
		case 'l':
			if (cmd[1] == 'v' & cmd[2] == 'e') return leave;
			break;
		case 'm':
			if (cmd[1] == 'o' & cmd[2] == 'v') return move;
			if (cmd[1] == 'u' & cmd[2] == 'l') return multiply;
			if (cmd[1] == 'o' & cmd[2] == 'd') return divide_module;
			break;
		case 'n':
			if (cmd[1] == 'a' & cmd[2] == 'n') return bin_nand;
			break;
		case 'o':
			if (cmd[1] == 'r') return bin_or;
			break;
		case 'p':
			if (cmd[1] == 'o' & cmd[2] == 'p') return pop;
			break;
		case 'r':
			if (cmd[1] == 'e' & cmd[2] == 't') return call_return;
			if (cmd[1] == '0' & cmd[2] == 't') return bin_rotate;
			break;
		case 's':
			if (cmd[1] == 'u' & cmd[2] == 'b') return substract;
			if (cmd[1] == 'u' & cmd[2] == 'm') return sum;
			if (cmd[1] == 'f' & cmd[2] == 't') return bit_shift;
			break;

		default: break;
	}

	return command_type::none;
}

constexpr std::string_view description(const command_type cmd) noexcept {
	switch (cmd) {
		case interrupt: return
			"Syntax: `int`\n"
			"Interrupt the execution. When it called, the process will be interrupted."
			;
		case call_return: return
			"Syntax: `ret`\n"
			"Take the top value from the stack and interpret it as the address to jump, then pop stack."
			;
		case leave: return
			"Syntax: `lve`\n"
			"Leave the current stack frame. Unrolls the stack till the first pushed value (aka address).\n"
			"Usually placed just before the `ret` command."
			;
		case push: return
			"Syntax: `psh [address]`\n"
			"Push a value under the given address to the stack."
			;
		case push_literal: return
			"Syntax: `psh literal`\n"
			"Push the literal to the stack. Actually just `sub [rsp] literal`."
			;
		case pop: return
			"Syntax: `pop literal`\n"
			"Pop <literal> count of bytes from the stack. Actually just `sum [rsp] literal`."
			;
		case increment: return
			"Syntax: `inc [address]` or `+++ [address]`\n"
			"Increments a value under the given address."
			;
		case decrement: return
			"Syntax: `dec [address]` or `--- [address]`"
			"Decrements a value under the given address."
			;
		case jump: return
			"Syntax: `jmp [address]`\n"
			"Jump to the given address. Actually sets the `[rpc]` register, aka program counter."
			;
		case jump_equal: return
			"Syntax: `jeq [address]` or `j== [address]`\n"
			"Jump to the given address if the r0 register is 0`."
			;
		case jump_not_equal: return
			"Syntax: `jne [address]` or `j!= [address]`\n"
			"Jump to the given address if the r0 register isn't 0`."
			;
		case jump_less: return
			"Syntax: `jls [address]` or `j<< [address]`\n"
			"Jump to the given address if the r0 register is less than 0`."
			;
		case jump_less_equal: return
			"Syntax: `jle [address]` or `j<= [address]`\n"
			"Jump to the given address if the r0 register is less or equal to 0`."
			;
		case jump_greater: return
			"Syntax: `jgr [address]` or `j>> [address]`\n"
			"Jump to the given address if the r0 register is greater than 0`."
			;
		case jump_greater_equal: return
			"Syntax: `jge [address]` or `j>= [address]`\n"
			"Jump to the given address if the r0 register is greater or equal to 0`."
			;
		case invert: return
			"Syntax: `inv [address]`\n"
			"Invert bytes of a value under the given address."
			;

#define COMPARE_DESCRIPTION \
	"If left value is greater than right, the r0 contains of positive value,\n" \
	"If left value is less than right, the r0 contains of negative value," \
	"otherwise the r0 register is 0.\n" \
	"It's actually just a `mov [r0] [address1]` and `sub [r0] [address2]`, but faster"

		case compare: return
			"Syntax: `cmp [address] [address]`\n"
			"Compare values from the given addresses and set the r0 register.\n"
			COMPARE_DESCRIPTION
			;
		case compare_address_literal: return
			"Syntax: `cmp [address] literal`\n"
			"Compare a value from the given address with a literal and set the r0 register.\n"
			COMPARE_DESCRIPTION
			;

#undef COMPARE_DESCRIPTION

		case move: return
			"Syntax: `mov [address] [address]`\n"
			"Copy the value from the right placed address to the left one."
			;
		case move_literal: return
			"Syntax: `mov [address] literal`\n"
			"Copy the right placed literal to the left address."
			;
		case swap: return
			"Syntax: `swp [address] [address]`\n"
			"Swap the values of the given addresses."
			;
		case sum: return
			"Syntax: `sum [address] [address]`\n"
			"Increase the value of the first address by the value of the second."
			;
		case sum_literal: return
			"Syntax: `sum [address] literal`\n"
			"Increase the value of the first address by the given literal."
			;
		case subtract: return
			"Syntax: `sub [address] [address]`\n"
			"Decrease the value of the first address by the value of the second."
			;
		case subtract_literal: return
			"Syntax: `sub [address] literal`\n"
			"Decrease the value of the first address by the given literal."
			;
		case multiply: return
			"Syntax: `mul [address] [address]`\n"
			"Store the multiplication result of values under the given addresses to the first address."
			;
		case multiply_literal: return
			"Syntax: `mul [address] literal`\n"
			"Increase the value under the given address by multiplying on a literal."
			;
		case divide: return
			"Syntax: `div [address] [address]`\n"
			"Divide the values under the given addresses and store the result to the first address."
			;
		case divide_literal: return
			"Syntax: `div [address] literal`\n"
			"Store the integral division result of the value under the address and the given literal"
			"to the first address."
			;
		case divide_module: return
			"Syntax: `mod [address] [address]`\n"
			"Store the module of the division of the value under the addresses to the first one."
			;
		case divide_module_literal: return
			"Syntax: `mod [address] literal`\n"
			"Store the module of the division of the value under the address and the given literal"
			"to the first address."
			;
		case bin_and: return
			"Syntax: `and [address] [address]`\n"
			"Binary `and` operation for each bit of values under the given addresses "
			"and store the result to the first one."
			;
		case bin_and_literal: return
			"Syntax: `and [address] literal`\n"
			"Binary `and` operation for each bit of value under the given address and literal "
			"and store the result to the address."
			;
		case bin_or: return
			"Syntax: `or [address] [address]`\n"
			"Binary `or` operation for each bit of values under the given addresses "
			"and store the result to the first one."
			;
		case bin_or_literal: return
			"Syntax: `or [address] literal`\n"
			"Binary `or` operation for each bit of value under the given address and literal "
			"and store the result to the address."
			;
		case bin_nand: return
			"Syntax: `nan [address] [address]`\n"
			"Binary `nand` operation for each bit of values under the given addresses "
			"and store the result to the first one."
			;
		case bin_nand_literal: return
			"Syntax: `nan [address] literal`\n"
			"Binary `nand` operation for each bit of value under the given address and literal "
			"and store the result to the address."
			;
		case bin_xor: return
			"Syntax: `xor [address] [address]`\n"
			"Binary `xor` operation for each bit of values under the given addresses "
			"and store the result to the first one."
			;
		case bin_xor_literal: return
			"Syntax: `xor [address] literal`\n"
			"Binary `xor` operation for each bit of value under the given address and literal "
			"and store the result to the address."
			;
		case bin_shift: return
			"Syntax: `sft [address] literal`\n"
			"Shift the bits of the value under the given address to the bits count, which is in literal.\n"
			"Positive literal shift bits to the left, and negative otherwise."
			;
		case bin_rotate: return
			"Syntax: `rot [address] literal`\n"
			"Rotate the bits of the value under the given address to the bits count, which is in literal.\n"
			"Positive literal shift bits to the left, and negative otherwise."
			;
	}
}
