#ifndef I4A392267_0985_4642_9613_FF22E1743AE0 
#define I4A392267_0985_4642_9613_FF22E1743AE0

#include "native.h"
#include <boost/asio/serial_port.hpp>
#include <boost/asio/serial_port_base.hpp>

namespace clr {

	int32_t my_pow(int32_t, int32_t);
	//managed delegate data type

	public ref class math
	{
		native::math* mth;
	public:
		void print_pow(int32_t, int32_t);
		void print_message(System::String^);
		//void print_avrage()
		math();
		~math() {};
	};

	public delegate void r_callback(System::String^ str, uint32_t len);
	public delegate void error_callback(System::String^ str);

	public ref class serial
	{
		native::Serial* ser;
		//this function are called as callback in native side
		void rcv_callback(char*,uint32_t);
		void err_callback(const char*);
		//this below delegate comes from .net(managed) side
		r_callback^ rcv_func{};
		error_callback^ err_func{};
		//this below delegate is for converting argumants to managed args.
		delegate void proxy_recive_Handeler(char*, uint32_t);
		delegate void proxy_error_Handeler(const char*);
		
	public:
		serial(uint32_t bud, System::String^ port_name);
		void write(System::String^ message);
		void on_receive(r_callback^ f);
		void on_error(error_callback^ err_code);
		System::Boolean start();
		System::Boolean stop();
		~serial() {};
	};
}
#endif // !I4A392267_0985_4642_9613_FF22E1743AE0 
