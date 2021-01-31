#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H
#include <thread>
#include <utility>
//------------------------------------------------------------------------------
class Thread {
    private:
        std::thread thread;
        
    public:
        /* Constructor */
        Thread();
        
        /* Destructor */
        virtual ~Thread();

        /* Deshabilito el contructor por copia y su operador. */
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;
        
        /* Habilito el constructor por movimiento y su operador. */
        Thread(Thread&& other);
        Thread& operator=(Thread&& other);
        
        /* Lanza la ejecuccion del thread que luego ejecuta el run(). */
        void start();

        /* Hace un join con el hilo de ejecuccion. */
        void join();

        /* Metodo sobre el cual se va a producir un override por 
        las clases hijas. */
        virtual void run() = 0;
};
#endif
