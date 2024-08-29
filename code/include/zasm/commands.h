#pragma once

#include <string_view>

#include "zasm/config.h"

namespace zasm::commands {

// 0000'0000
// └┬┴──┬──┘
//  │   └ Command ID (up to 64)
//  └ Arguments count (up to 3)

enum command_type : std::uint8_t {
	none = 0x00,

	commands_0_parameters_begin = none,
		interrupt,                       // int
		call_return,                     // ret
		leave,                           // lve
	commands_0_parameters_end,


	commands_1_parameters_begin = 0x40,
		push,                            // psh [address]
		push_literal,                    // psh literal

		pop,                             // pop literal

		increment,                       // inc [address] or +++
		decrement,                       // dec [address] or ---

		jump,                            // jmp [address]
		jump_equal,                      // jeq [address] or j==  // jump if r0 == 0
		jump_not_equal,                  // jne [address] or j!=  // jump if r0 != 0
		jump_less,                       // jls [address] or j<<  // jump if r0 <  0
		jump_less_equal,                 // jle [address] or j<=  // jump if r0 <= 0
		jump_greater,                    // jgr [address] or j>>  // jump if r0 >  0
		jump_greater_equal,              // jge [address] or j>=  // jump if r0 >= 0

		invert,                          // inv [address]
	commands_1_parameters_end,

	commands_2_parameters_begin = 0x80,
		compare,                         // cmp [address] [address]
		compare_address_literal,         // cmp [address] literal

		move,                            // mov [address] [address]
		move_literal,                    // mov [address] literal

		swap,                            // swp [address] [address]

		sum,                             // sum [address] [address]
		sum_literal,                     // sum [address] literal
		subtract,                        // sub [address] [address]
		subtract_literal,                // sub [address] literal
		multiply,                        // mul [address] [address]
		multiply_literal,                // mul [address] literal
		divide,                          // div [address] [address]
		divide_literal,                  // div [address] literal
		divide_module,                   // mod [address] [address]
		divide_module_literal,           // mod [address] literal

		bin_and,                         // and [address] [address]
		bin_and_literal,                 // and [address] literal

		bin_or,                          // or [address] [address]
		bin_or_literal,                  // or [address] literal

		bin_nand,                        // nan [address] [address]
		bin_nand_literal,                // nan [address] literal

		bin_xor,                         // xor [address] [address]
		bin_xor_literal,                 // xor [address] literal

		bin_shift,                       // sft [address] literal
		bin_rotate,                      // rot [address] literal
	commands_2_parameters_end,

	commands_3_parameters_begin = 0xC0,
	commands_3_parameters_end,
};

#pragma push(pack, 1)
struct command {
	uint8_t parameters : 2;
	command_type type  : 6;
};
#pragma pop(pack)

template<std::int32_t N>
[[nodiscard]] constexpr bool is_parameters_count(const command_type cmd) noexcept;
[[nodiscard]] constexpr bool is_command(const command_type cmd) noexcept;
[[nodiscard]] constexpr std::int32_t parameters_count(const command_type cmd) noexcept;


[[nodiscard]] constexpr std::string_view to_string(const command_type cmd) noexcept;
[[nodiscard]] constexpr command_type from_string(const std::string_view cmd) noexcept;
[[nodiscard]] constexpr std::string_view description(const command_type cmd) noexcept;

#include "zasm/commands.inl"

} // namespace zasm::commands
