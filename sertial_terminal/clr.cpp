#include "clr.h"
#include <msclr/marshal_cppstd.h>
namespace clr {

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
	void serial::rec_callback(char* msg, uint32_t len)
	{
		System::String^ msg_str = gcnew System::String(msg);
		if (rec_func)
			rec_func(msg_str, len);
	}
	serial::serial(uint32_t bud, System::String^ port_name)
	{
		msclr::interop::marshal_context str;
		std::string com = str.marshal_as<std::string>(port_name);
		//cntx = new boost::asio::io_context();
		//ser = new native::serial(*cntx, bud, com);
		ser = new native::serial(bud, com);
	}
	void serial::write(System::String^ message)
	{
		msclr::interop::marshal_context str;
		std::string msg = str.marshal_as<std::string>(message);
		ser->write(msg);
	}
	void serial::on_receive(recive_callback^ f)
	{
		rec_func = f;
		auto handler = gcnew proxy_recive_Handeler(this, &serial::rec_callback);
		System::Runtime::InteropServices::GCHandle::Alloc(handler);
		auto ip = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(handler);

		ser->on_recevie(static_cast<native::serial::rec_func>(ip.ToPointer()));

	}
}

