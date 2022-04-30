#include "native.h"

namespace native {

	auto math::print_pow(int32_t a, int32_t n) -> void
	{
		int32_t result{};
		result = my_pow(a, n);
		std::cout << "the result is :" << result << "\n";
	}
	auto math::print_message(std::string msg) -> void
	{
		std::cout << msg << "\n";
	}
	int32_t my_pow(int32_t a, int32_t n)
	{
		int32_t result{ 1 };
		if (n < 0) n = -n;
		for (auto i{ 0 }; i < n; i++) {
			result *= a;
		}
		return result;
	}
}