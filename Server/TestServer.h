#include "Simpleserver.h"

namespace HDE {
    class TestServer :public SimpleServer {
        private:
            char buffer[300000]={0};
            int newsocket;
        public:
            TestServer();
            void AcceptConnection();
            void handleConnection();
            void respondConnection();
            char* parse(char str[],const char symbol[]);
            char* parse_method(char str[],const char symbol[]);
            int send_message(int fd, char mssg[],char tot[]);
            char* find_token(char str[],const char symbol[],const char match[]);
            void launch();
    };
}