//
// Created by dmitri on 06.03.2020.
//

#ifndef HUFFMANCODE_QUEUECONNECTIONHANDLER_H
#define HUFFMANCODE_QUEUECONNECTIONHANDLER_H

#include <amqp.h>
#include <amqp_tcp_socket.h>

#include <memory>
#include <string>
#include <cctype>

unsigned long long operator "" _passive(unsigned long long value);
unsigned long long operator "" _durable(unsigned long long value);
unsigned long long operator "" _autodelete(unsigned long long value);
unsigned long long operator "" _internal(unsigned long long value);
unsigned long long operator "" _exclusive(unsigned long long value);

namespace UTILITY {
    struct Address {
        std::string hostname;
        std::size_t port;
    };

    const std::size_t MAX_FRAME_SIZE = 131072;
    const std::string DEFAULT_EXCHANGE = "amq.direct";
    const std::string DEFAULT_EXCHANGE_TYPE = "direct";
    const std::string DEFAULT_LOGIN = "guest";
    const std::string DEFAULT_PASSWORD = "guest";
    const std::string DEFAULT_BINDING_KEY = "queue";

    void die(const char *fmt, ...);
    void die_on_amqp_error(amqp_rpc_reply_t x, char const *context);
}

namespace AMQP {
    using Socket = amqp_socket_t*;

    class ConnectionBuilder;
    class ConnectionHandler {
        friend class ConnectionBuilder;
    private:
        amqp_connection_state_t conn_;
        Socket socket_;
        UTILITY::Address address_;
        int socket_status_;
        int channel_num_;
        amqp_bytes_t queue_name_;

    public:
        int GetSocketStatus() const;

        ConnectionHandler(const ConnectionHandler&) = delete;
        ConnectionHandler& operator=(const ConnectionHandler&) = delete;

        ConnectionHandler(ConnectionHandler&&) = default;
        ConnectionHandler& operator=(ConnectionHandler&&) = default;
    private:
        ConnectionHandler(UTILITY::Address address, Socket socket, amqp_connection_state_t conn,
                int socket_status, amqp_bytes_t queue_name, int channel_num);

    };

    class ConnectionBuilder {
    private:
        amqp_connection_state_t conn;
        Socket socket;
        UTILITY::Address address;
        int socket_status;
        std::string vhost;
        size_t chanel_max;
        size_t frame_max;
        size_t heartbeat;
        amqp_sasl_method_enum sasl_method;
        std::string login;
        std::string password;
        int channel_num;
        std::string exchange;
        std::string exchange_type;
        uint16_t exchange_declare_flags;
        uint16_t queue_declare_flags;
        std::string bindingKey;
        amqp_bytes_t queue_name;
    public:
        ConnectionBuilder();
        ConnectionBuilder& SetHostname(std::string host);
        ConnectionBuilder& SetPort(std::size_t port);
        ConnectionBuilder& SetVhost(std::string vHost);
        ConnectionBuilder& SetChannelMax(std::size_t cmax);
        ConnectionBuilder& SetFrameMax(std::size_t fmax);
        ConnectionBuilder& SetHeartbeat(std::size_t h);
        ConnectionBuilder& SetSASLMethod(amqp_sasl_method_enum method);
        ConnectionBuilder& SetLogin(std::string l);
        ConnectionBuilder& SetPassword(std::string p);
        ConnectionBuilder& SetChannelNum(std::size_t n);
        ConnectionBuilder& SetExchange(std::string exch);
        ConnectionBuilder& SetExchangeType(std::string exch_t);
        ConnectionBuilder& SetExchangeFlags(uint16_t p, uint16_t d, uint16_t ad, uint16_t i);
        ConnectionBuilder& SetQueueFlags(uint16_t p, uint16_t d, uint16_t e, uint16_t ad);
        ConnectionBuilder& SetBindingKey(std::string binding_key);
        ConnectionHandler Build();
    };
}

#endif //HUFFMANCODE_QUEUECONNECTIONHANDLER_H