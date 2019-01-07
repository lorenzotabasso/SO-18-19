#include "common.h"

int print_error(int en){
    fprintf(stderr,"Error #%03d: %s\n", en, strerror(en));
    return en;
}

void init_msg_queue(){
    msg_queue_id = msgget(IPC_PRIVATE, 0400 | 0200);
    if (msg_queue_id == -1) {
        print_error(errno);
    }
    printf("Created message queue with ID: %d\n", msg_queue_id);
}

void deallocate_IPCs(){
    if (msgctl(msg_queue_id, IPC_RMID, NULL) == -1){
        print_error(errno);
    }
//    if (semctl(semaforoPalla, 0, IPC_RMID) == -1){
//        Error();
//    }
//    if (semctl(setSemaforiSquadre, 1, IPC_RMID) == -1){
//        Error();
//    }
//    if (shmctl(idshm, IPC_RMID, NULL) == -1) {
//        Error();
//    }
    printf ("IPCs deallocated successfully.\n");
}