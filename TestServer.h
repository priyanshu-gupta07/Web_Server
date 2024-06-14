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
            void launch();
    };
}