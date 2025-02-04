#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

#define MAX_PROCESOS 10

int N, K, J;
int pids[MAX_PROCESOS]; // Arreglo para almacenar los PIDs de los procesos hijos

void handle_sigterm(int sig) {
    int num_azar = rand() % N;
    if (num_azar == J) {
        printf("Proceso %d (PID %d): ¡Me tocó el número maldito %d! Adiós.\n", getpid(), getpid(), J);
        exit(0); // Termina el proceso si el número es maldito
    } else {
        printf("Proceso %d (PID %d): Sobreviví esta ronda.\n", getpid(), getpid());
    }
}

void crear_hijos() {
    for (int i = 0; i < N; i++) {
        int pid = fork();
        if (pid == 0) { // Código del hijo
            srand(time(NULL) ^ (getpid() << 16)); // Semilla para el generador de números aleatorios
            signal(SIGTERM, handle_sigterm); // Asigna el manejador de SIGTERM
            while (1) pause(); // Espera señales
        } else if (pid > 0) { // Código del padre
            pids[i] = pid;
        } else {
            perror("Error en fork");
            exit(1);
        }
    }
}

void enviar_sigterm_a_hijos() {
    for (int i = 0; i < N; i++) {
        if (pids[i] != -1) {
            kill(pids[i], SIGTERM);
        }
        sleep(1); // Espera 1 segundo entre cada señal
    }
}

void juego() {
    for (int ronda = 1; ronda <= K; ronda++) {
        printf("\n--- Ronda %d ---\n", ronda);
        enviar_sigterm_a_hijos();
        int estado;
        for (int i = 0; i < N; i++) {
            int pid = waitpid(-1, &estado, WNOHANG);
            if (pid > 0) {
                printf("Hijo con PID %d ha sido eliminado.\n", pid);
                for (int j = 0; j < N; j++) {
                    if (pids[j] == pid) {
                        pids[j] = -1; // Marcamos este PID como eliminado
                        break;
                    }
                }
            }
        }
    }
}

void finalizar_hijos() {
    printf("\n--- Final del juego ---\n");
    for (int i = 0; i < N; i++) {
        if (pids[i] != -1) {
            printf("Hijo sobreviviente: %d (PID: %d)\n", i + 1, pids[i]);
            kill(pids[i], SIGKILL); // Termina a los hijos sobrevivientes
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s N K J\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    K = atoi(argv[2]);
    J = atoi(argv[3]);

    if (N <= 0 || N >= 10 || K <= 0 || J < 0 || J >= N) {
        fprintf(stderr, "Parámetros inválidos.\n");
        return 1;
    }

    printf("Iniciando el juego con %d procesos, %d rondas, y el número maldito es %d.\n", N, K, J);

    crear_hijos();
    juego();
    finalizar_hijos();

    return 0;
}
