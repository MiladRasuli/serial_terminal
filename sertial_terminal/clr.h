#ifndef I4A392267_0985_4642_9613_FF22E1743AE0 
#define I4A392267_0985_4642_9613_FF22E1743AE0
#include "native.h"
#include <boost/asio/serial_port.hpp>
#include <boost/asio/serial_port_base.hpp>

namespace clr {

	int32_t my_pow(int32_t, int32_t);
	/*managed delegate data type*/
	public delegate void recive_callback(System::String^, uint32_t);
	public ref class math
	{
		native::math* mth;
	public:
		void print_pow(int32_t, int32_t);
		void print_message(System::String^);
		math();
		~math() {};
	};

	public ref class serial
	{
		native::serial* ser;
		//boost::asio::io_context* cntx;
		/*this function are called as callback in native side*/
		void rec_callback(char*, uint32_t);
		/*this below delegate comes from .net(managed) side*/
		recive_callback^ rec_func{};
		/*this below delegate is for converting argumants to managed args.*/
		delegate void proxy_recive_Handeler(char*, uint32_t);
	public:
		serial(uint32_t bud, System::String^ port_name);
		void write(System::String^ message);
		void on_receive(recive_callback^ f);

		~serial() {};
	};
}
#endif /* !I4A392267_0985_4642_9613_FF22E1743AE0 */