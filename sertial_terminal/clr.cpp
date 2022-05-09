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
	
	void serial::rcv_callback(char*str, uint32_t len)
	{
		System::String^ msg = gcnew System::String(str);
		if (rcv_func)
		{
			rcv_func(msg, len);
		}
	}
	void serial::err_callback(const char* str)
	{
		System::String^ msg = gcnew System::String(str);
		if (err_func)
			err_func(msg);
	}
	serial::serial(uint32_t bud, System::String^ port_name)
	{
		msclr::interop::marshal_context str;
		std::string com = str.marshal_as<std::string>(port_name);
		ser = new native::Serial(com,bud);
	}
	System::Boolean serial::start()
	{
		return ser->start()?true:false;
	}
	System::Boolean serial::stop()
	{
		return ser->stop()?true:false;
	}
	void serial::write(System::String^ message)
	{
		msclr::interop::marshal_context str;
		std::string msg = str.marshal_as<std::string>(message);
		ser->write(msg);
	}
	void serial::on_receive(r_callback^ f)
	{
		rcv_func = f;
		auto handel = gcnew proxy_recive_Handeler(this, &serial::rcv_callback);
		System::Runtime::InteropServices::GCHandle::Alloc(handel);
		auto ip = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(handel);
		ser->on_receive(static_cast<native::rcv_callback_type>(ip.ToPointer()));
	}

	void serial::on_error(error_callback^ f)
	{
		err_func = f;
		auto handler = gcnew proxy_error_Handeler(this, &serial::err_callback);
		System::Runtime::InteropServices::GCHandle::Alloc(handler);
		auto ip = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(handler);
		ser->on_error(static_cast<native::err_callback_type>(ip.ToPointer()));
	}
}

