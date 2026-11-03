#include <pthread.h>

struct station {
    int esperando;
    int vagas;
    int embarcando;

    pthread_mutex_t mutex;

    pthread_cond_t pode_embarcar;
    pthread_cond_t embarque_concluido;
};

void station_init(struct station *station){
    station->esperando = 0;
    station->vagas = 0;
    station->embarcando = 0;

    pthread_mutex_init(&station->mutex, NULL);

    pthread_cond_init(&station->pode_embarcar, NULL);
    pthread_cond_init(&station->embarque_concluido, NULL);
}