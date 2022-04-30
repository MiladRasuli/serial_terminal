#include "clr.h"
#include <msclr/marshal_cppstd.h>
namespace managed {

	int32_t my_pow(int32_t a, int32_t n)
	{
		return native::my_pow(a, n);
	}
	math::math() :mth{ new native::math } {}

	void math::print_pow(int32_t a, int32_t n) {
		mth->print_pow(a, n);
	}
	void math::print_message(System::String^ message) {
		msclr::interop::marshal_context str;
		mth->print_message(str.marshal_as<std::string>(message));
		System::Console::Write("Hello World from C++/CLR\n");
	}
	serial::serial(uint32_t bud, System::String^ port_name)
	{
		msclr::interop::marshal_context str;
		std::string com = str.marshal_as<std::string>(port_name);
		cntx = new boost::asio::io_context();
		ser = new native::serial(*cntx, bud, com);
	}
	void serial::write(System::String^ message)
	{
		msclr::interop::marshal_context str;
		std::string msg = str.marshal_as<std::string>(message);
		ser->write(msg);
	}
}

