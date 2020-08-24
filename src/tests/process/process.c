#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  /* Ogni processo ha: codice, dati ,pila, pid
   * init è il processo padre di tutti
   * unico modo per creare un nuovo processo è duplicare quello esistente
   * tramite fork
   * dopo una fork padre e figlio sono identici eccetto per il pid e risorse
   * run-time il padre non può terminare se il figlio non termina il figlio
   * termina tramite exit
   */

  int pid = 0;
  pid = fork();

  if (pid < 0) {
    printf("Fork fallita!\n");
  } else if (pid != 0) {
    printf("%d Sono il padre %d con un figlio %d\n", pid, getpid(), pid);
    wait(NULL);
    printf("Figlio completato\n");
  } else {
    printf("%d Sono figlio %d del padre %d! \n", pid, getpid(), getppid());
    // execlp("/bin/ls", "ls", NULL);
  }

  exit(EXIT_SUCCESS);
}
