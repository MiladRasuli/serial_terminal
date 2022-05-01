#ifndef I94F86423_FD0A_4E1B_8609_2C4DBE865375 
#define I94F86423_FD0A_4E1B_8609_2C4DBE865375
#include <iostream>
#include <string>
#include<boost/asio/serial_port_base.hpp>
#include<boost/asio/serial_port.hpp>
#include <thread>
#include <functional>

namespace native
{
    int32_t my_pow(int32_t a, int32_t n);
    class math {
    public:
        auto print_pow(int32_t a, int32_t n) -> void;
        auto print_message(std::string msg) -> void;

        math() = default;
        ~math() = default;
    };

    class serial {

    public:
        using rec_func = void(__stdcall*)(char *,uint32_t);
        //using rec_func = std::function<void(char* data, uint32_t lenght)>;
        //using rec_func = std::function<void(std::string)>;
        serial(boost::asio::io_context& cntx, uint32_t bud, std::string port_name)
        {
            port = std::make_unique<boost::asio::serial_port>(cntx, port_name);
            port->set_option(boost::asio::serial_port_base::baud_rate(bud));
            port->async_read_some(
                boost::asio::buffer(ser_buf.data(), ser_buf.size()),
                std::bind(&serial::resiv_handle, this, std::placeholders::_1, std::placeholders::_2));
            std::thread([&] {cntx.run(); }).detach();
        }
        ~serial()
        {
            port->close();
        }

        void write(std::string message) {
            port->async_write_some(boost::asio::buffer(message.data(), message.length()),
                std::bind(&serial::send_handle, this, std::placeholders::_1, std::placeholders::_2, message.length()));
        }
        auto operator[](unsigned index) -> char
        {
            return ser_buf[index];
        }

        void on_recevie(rec_func receive_callback) {
            receive_ = receive_callback;
        }
    private:
        std::unique_ptr<boost::asio::serial_port> port;
        std::array<char, 1000> ser_buf;
        rec_func receive_ = nullptr;
        auto resiv_handle(const boost::system::error_code& err, std::size_t res_size) -> void
        {

            if (receive_ == nullptr) return;
            receive_(ser_buf.data(), res_size);

            port->async_read_some(
                boost::asio::buffer(ser_buf.data(), ser_buf.size()),
                std::bind(&serial::resiv_handle, this, std::placeholders::_1, std::placeholders::_2));
        }
        void send_handle(const boost::system::error_code& error_code, std::size_t bytes_transferred, std::size_t actual_bytes) {
            /* Call the error_callback if an error is generated. */
            if (error_code || actual_bytes != bytes_transferred) {
                //error_callback_(error_code.message());
            }
        }
    };
};

#endif /* !I94F86423_FD0A_4E1B_8609_2C4DBE865375 */