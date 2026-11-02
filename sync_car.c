#include <pthread.h>

struct station {
    int esperando;
    int vagas;
    int embarcando;

    pthread_mutex_t mutex;

    pthread_cond_t pode_embarcar;
    pthread_cond_t embarque_concluido;
};