#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

struct station {
    int esperando;
    int vagas;
    int embarcando;

    pthread_mutex_t mutex;

    pthread_cond_t pode_embarcar;
    pthread_cond_t embarque_concluido;
};

void station_init(struct station *station);
void station_wait_for_car(struct station *station);
void station_on_board(struct station *station);
void station_load_car(struct station *station, int count);

#endif