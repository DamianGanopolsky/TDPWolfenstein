#ifndef LOGIN_H
#define LOGIN_H

#include <atomic>
#include "../Common/thread.h"
#include "../Common/non_blocking_queue.h"
#include "../Common/socket.h"
#include "./connection_element.h"

class Login : public Thread {
   private:
    std::atomic_bool is_running;
    Socket peer;
    NonBlockingQueue<ConnectionElement*>& new_connections;
    std::string _receive();

   public:
        Login(Socket& peer, NonBlockingQueue<ConnectionElement*>& new_connections);
        ~Login();

        Login(const Login&) = delete;
        Login& operator=(const Login&) = delete;
        Login(Login&& other) = delete;
        Login& operator=(Login&& other) = delete;

        void run() override;
        bool isRunning() const;
        void stop();
};

#endif