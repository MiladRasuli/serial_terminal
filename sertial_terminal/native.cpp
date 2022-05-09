#include "native.h"
#include <mutex>
namespace native {

	auto math::print_pow(int32_t a, int32_t n) -> void
	{
		int32_t result{};
		result = my_pow(a, n);
		std::cout << "the result of the pow function is :" << result << "\n";
	}
	auto math::print_message(std::string msg) -> void
	{
		std::cout << msg << "\n";
	}
	auto math::print_avrage(std::vector<int32_t> numb) -> void
	{
		int32_t sum{};
		int32_t n{};
		for (auto& i : numb)
		{
			sum += i;
			++n;
		}
		std::cout << "the sum is :" << (double)sum / n;
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