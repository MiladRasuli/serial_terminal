#ifndef I94F86423_FD0A_4E1B_8609_2C4DBE865375 
#define I94F86423_FD0A_4E1B_8609_2C4DBE865375


#include <iostream>
#include <string>
#include <boost/asio/io_service.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind.hpp>
//#include <boost/thread.hpp>
#include <thread>

namespace native
{
    int32_t my_pow(int32_t a, int32_t n);
    class math {
    public:
        auto print_pow(int32_t a, int32_t n) -> void;
        auto print_message(std::string msg) -> void;
        auto print_avrage(std::vector<int32_t> numb)-> void;
        math() = default;
        ~math() = default;
    private:
        std::vector<int32_t> number{};
    };

    using rcv_callback_type = void(__stdcall*)(char*, uint32_t);
    using err_callback_type = void(__stdcall*)(const char*);
    class Serial {

    private:
        char read_msg_[512];
        boost::asio::io_service io_;
        boost::asio::serial_port ser;
        std::thread thread_{};
        std::string com{};
        uint32_t baud{ 9600 };
        rcv_callback_type rcv_function = [](char*, uint32_t) -> void {};
        err_callback_type err_function = [](const char*) -> void {};
        void handler(const boost::system::error_code& error, size_t bytes_transferred)
        {
            if (errno) {

                err_function(error.message().data());
                return;
            }
            read_some();
            read_msg_[bytes_transferred] = 0;
            rcv_function(read_msg_, bytes_transferred);
        }
        void read_some()
        {
            ser.async_read_some(boost::asio::buffer(read_msg_, 512),
                boost::bind(&Serial::handler,
                    this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
    public:
        ~Serial()
        {
            if (ser.is_open())
                ser.close();
            exit(0);
        }

        Serial(const std::string dev_name, uint32_t baud_rate) :
            io_{}, ser(io_), com{ dev_name }, baud{ baud_rate }
        {
            /*
                  port.set_option( boost::asio::serial_port_base::parity() );	// default none
                  port.set_option( boost::asio::serial_port_base::character_size( 8 ) );
                  port.set_option( boost::asio::serial_port_base::stop_bits() );	// default one
            */
            read_some();

            // run the IO service as a separate thread, so the main thread can do others
            std::thread t([this] {io_.run(); });
            t.detach();
        }
        auto start() -> int32_t {
            try
            {
                ser.open(com);
                ser.set_option(boost::asio::serial_port_base::baud_rate(baud));
            }
            catch (const std::exception& err)
            {

                err_function(err.what());
                return 0;
            }
            return 1;
        }
        auto stop() -> int32_t {
            try
            {
                rcv_function = [](auto, auto)->void {};
                err_function = [](auto)->void {};
                ser.cancel();
                ser.close();
            }
            catch (const std::exception& err)
            {
                err_function(err.what());
                return 0;
            }
            return 1;
        }
        void write(std::string msg)
        {
            ser.write_some(boost::asio::buffer(msg, msg.length()));
        }
        auto on_receive(rcv_callback_type&& cb) ->void {
            rcv_function = std::move(cb);
        }
        auto on_error(err_callback_type&& cb) ->void {
            err_function = std::move(cb);
        }
    };


};

#endif /* !I94F86423_FD0A_4E1B_8609_2C4DBE865375 */