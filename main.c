#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void a();
void b();
void c();
void d();
void e();


int main() {
    //a();
    b();
    //c();
    //e();
    //d();
    return 0;
}

void b() {
    printf("Parent process\n");
    a();
    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();
        switch (pid) {
            case -1:
                perror("fork error\n");
                exit(1);
            case 0:
                printf("Child process\n");
                a();
            default:
                wait(NULL);
        };
    }

}

void c() {
    pid_t id = getpid();
    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();
        switch (pid) {
            case -1:
                perror("fork error\n");
                exit(1);
            case 0:
                printf("Child process\n");
                a();
        };
    }
    if (id == getpid())return;
    sleep(10);
}

void e() {
    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();
        switch (pid) {
            case -1:
                perror("fork error\n");
                exit(1);
            case 0:
                printf("Child process\n");
                setpgid(0, 0);
                a();
            default:
                wait(NULL);
        };
    }

}
void d() {
    a();
    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();
        switch (pid) {
            case -1:
                perror("fork error\n");
                exit(1);
            case 0:
                printf("Child process\n");
                a();
            default:
                sleep(3-i);
        };
    }

}
void a() {
    printf("===================\n");
    uid_t uid = getuid();
    printf("uid %e\t", uid);
    gid_t gid = getgid();
    printf("gid %e\t", gid);
    pid_t pid = getpid();
    printf("pid %e\t", pid);
    pid_t ppid = getppid();
    printf("ppid %e\t", ppid);
    pid_t pgid = getpgid(pid);
    printf("pgid %e\n", pgid);
    printf("===================\n");
}