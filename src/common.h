#ifndef COMMON_H
#define COMMON_H

/* MACROs and VARIABLEs -----------------------------------------------------*/

#define POP_SIZE 15
#define DEBUG {printf(RED "\t(%d) DEBUG at FILE: %s LINE:%d" RESET "\n", getpid(), __FILE__, __LINE__);}
#define PRINT_ERROR if (errno) {fprintf(stderr, RED "\t%s:%d: PID=%5d: Error %d (%s)"RESET"\n", \
                      __FILE__,    __LINE__, getpid(), errno, strerror(errno));}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/* Colors for Command Line */
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

/* Path to the configuration file */
#define CONF_PATH "src/opt.conf"

#if defined(__linux__)
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short  *array;
        #if defined(__linux__)
            struct seminfo* __buf;
        #endif
    };
#endif

#define KEY_CHILDREN_SEMAPHORE ftok("src/manager.c",1)
#define KEY_MESSAGE_QUEUE ftok("src/manager.c",2)
#define KEY_SHARED_MEMORY ftok("src/manager.c",3)
#define KEY_MESSAGE_QUEUE_PARENT ftok("src/manager.c",4)
#define KEY_MESSAGE_QUEUE_ANSWER ftok("src/manager.c",5)

/* IPCs ids*/
int id_children_semaphore;
int id_shared_memory;
int id_message_queue;
int id_message_queue_parent;
int id_message_queue_answer;

struct shared_memory {
    int marks[POP_SIZE][6]; /* pid, group_id, group_num, ade_mark, so_mark
                               and pref_group */
};

struct shared_memory * shm_pointer; // Pointer to shared memory area

// List
typedef struct _node* list;

struct _node {
    int student;
    int voto_ade;
    int group_num;
    int pref_gruppo;
    list nxt;
};

// Mark_list
typedef struct _node_mark* mark_list;

struct _node_mark {
    int mark;
    mark_list nxt;
};

// Messages Types
struct my_msg{
    long mtype;
    char ask;
    int ade_voto;
    int student_id;
    int pref_gruppo;
} costrutto,costrutto3;

struct my_msg2{
    long mtype;
    int sender;
    int student_msg;
    int ade_mark_msg;
    int pref_gruppo_msg;
    int group_id_msg;
    int group_num_msg;
} costrutto2;

/* Config settings */
int sim_time;
int dev_preference_2;
int dev_preference_3;
int dev_preference_4;
int nof_invites;
int max_reject;

/* Vector of kids PIDs */
pid_t population[POP_SIZE];

/* FUNCTIONS ----------------------------------------------------------------*/

/* manager.c */
void set_shared_data();
void parent_handle_signal();
void compute_mark(int number_marks);

/* student.c */
void read_invites(list l);
void child_handle_signal();
void init_student_parameters();
void init_ipc_id();

/* utility.c - Functions grouped by category*/

void start_timer();

int random_between(pid_t seed, int min, int max);
int compute_preference(int pref_2,int pref_3,int pref_4);

void init_message_queue(int key_msg_queue);
void init_children_semaphore (int key_sem);
int initSemAvailable(int semId, int semNum);
int request_resource(int id_sem, int sem_num);
int relase_resource(int id_sem, int sem_num);
void init_shared_memory(int key_shmem);
void deallocate_IPCs();
void read_conf(char * config_path);

list create_node (int i,int voto, int p);
list insert_head(list l, int i,int voto,int p);
list insert_tail(list l,int i,int voto, int p);
list remove_head (list l);
list remove_tail (list l);
int contains(list l, int stud);
void print_list (list l);

mark_list create_node_mark (int m);
mark_list insert_tail_mark(mark_list l,int m);
int contains_mark(mark_list l, int m);

#endif // COMMON_H
