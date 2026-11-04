#include <pthread.h>

struct station {
    int esperando;
    int vagas;
    int embarcando;

    pthread_mutex_t mutex;

    pthread_cond_t pode_embarcar;
    pthread_cond_t embarque_concluido;
};
void station_init(struct station *station)
{
    station->esperando = 0;
    station->vagas = 0;
    station->embarcando = 0;

    pthread_mutex_init(&station->mutex, NULL);

    pthread_cond_init(&station->pode_embarcar, NULL);
    pthread_cond_init(&station->embarque_concluido, NULL);
}

void station_wait_for_car(struct station *station)
{
    pthread_mutex_lock(&station->mutex);

    station->esperando++;

    while (station->vagas == 0) {
        pthread_cond_wait(
            &station->pode_embarcar,
            &station->mutex
        );
    }

    station->esperando--;
    station->vagas--;
    station->embarcando++;

    pthread_mutex_unlock(&station->mutex);
}

void station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->mutex);

    station->embarcando--;

    if (station->embarcando == 0 &&
        (station->vagas == 0 || station->esperando == 0)) {
        pthread_cond_signal(&station->embarque_concluido);
    }

    pthread_mutex_unlock(&station->mutex);
}

void station_load_car(struct station *station, int count)
{
    pthread_mutex_lock(&station->mutex);

    station->vagas = count;

    pthread_cond_broadcast(&station->pode_embarcar);

    while ((station->vagas > 0 && station->esperando > 0) ||
           station->embarcando > 0) {
        pthread_cond_wait(
            &station->embarque_concluido,
            &station->mutex
        );
    }

    station->vagas = 0;

    pthread_mutex_unlock(&station->mutex);
}