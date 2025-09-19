#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void have_2son(void); 
void have_3son(void); 

//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao inciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar

int main(int argc, char** argv) {

    // ....

    /*************************************************
     * Dicas:                                        *
     * 1. Leia as intruções antes do main().         *
     * 2. Faça os prints exatamente como solicitado. *
     * 3. Espere o término dos filhos                *
     *************************************************/

    pid_t pid0 = getpid();

    printf("I am all father: %d\n\n", getpid());

    have_2son();

    while (wait(NULL) >= 0 );
    
    if (getpid() != pid0)
    {
        printf("\nProcesso %d finalizado\n\n", getpid());
        return 0;
    }

    printf("Processo principal %d finalizado\n\n", getpid());    
    return 0;
}


void have_3son(){
    
    for (int i = 0; i < 3; i++)
    {
        if (fork() == 0)
        {
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            fflush(stdout);
            sleep(5);
            break;
        }
    }
}

void have_2son(){
    
    for (int i = 0; i < 2; i++)
    {
        if (fork() == 0)
        {
            printf( "Processo %d, filho de %d\n", getpid(), getppid());
            fflush(stdout);
            have_3son();
            break;
        }   
    }
}