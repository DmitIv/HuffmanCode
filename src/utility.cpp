//
// Created by dmitri on 07.03.2020.
//

#include "QueueConnectionHandler.h"

#include <cstdio>
#include <cstdlib>
#include <cstdarg>


unsigned long long operator""_passive(unsigned long long value) { return value; }
unsigned long long operator""_durable(unsigned long long value) { return value; }
unsigned long long operator""_internal(unsigned long long value) { return value; }
unsigned long long operator""_exclusive(unsigned long long value) { return value; }
unsigned long long operator""_autodelete(unsigned long long value) { return value; }

namespace UTILITY {
    void die(const char *fmt, ...) {
        va_list ap;
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        va_end(ap);
        fprintf(stderr, "\n");
        exit(1);
    }

    void die_on_amqp_error(amqp_rpc_reply_t x, char const *context) {
        switch (x.reply_type) {
            case AMQP_RESPONSE_NORMAL:
                return;

            case AMQP_RESPONSE_NONE:
                fprintf(stderr, "%s: missing RPC reply type!\n", context);
                break;

            case AMQP_RESPONSE_LIBRARY_EXCEPTION:
                fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x.library_error));
                break;

            case AMQP_RESPONSE_SERVER_EXCEPTION:
                switch (x.reply.id) {
                    case AMQP_CONNECTION_CLOSE_METHOD: {
                        amqp_connection_close_t *m =
                                (amqp_connection_close_t *)x.reply.decoded;
                        fprintf(stderr, "%s: server connection error %uh, message: %.*s\n",
                                context, m->reply_code, (int)m->reply_text.len,
                                (char *)m->reply_text.bytes);
                        break;
                    }
                    case AMQP_CHANNEL_CLOSE_METHOD: {
                        amqp_channel_close_t *m = (amqp_channel_close_t *)x.reply.decoded;
                        fprintf(stderr, "%s: server channel error %uh, message: %.*s\n",
                                context, m->reply_code, (int)m->reply_text.len,
                                (char *)m->reply_text.bytes);
                        break;
                    }
                    default:
                        fprintf(stderr, "%s: unknown server error, method id 0x%08X\n",
                                context, x.reply.id);
                        break;
                }
                break;
        }

        exit(1);
    }
}