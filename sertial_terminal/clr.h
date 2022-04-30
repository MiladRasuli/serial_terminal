#ifndef I4A392267_0985_4642_9613_FF22E1743AE0 
#define I4A392267_0985_4642_9613_FF22E1743AE0
#include "native.h"
#include <boost/asio/serial_port.hpp>
#include <boost/asio/serial_port_base.hpp>

namespace clr {

	int32_t my_pow(int32_t, int32_t);
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
		boost::asio::io_context* cntx;
	public:
		serial(uint32_t bud, System::String^ port_name);
		void write(System::String^ message);
		~serial() {};
	};
}
#endif /* !I4A392267_0985_4642_9613_FF22E1743AE0 */