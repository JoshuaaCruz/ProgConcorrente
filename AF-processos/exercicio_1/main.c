#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//       (pai)      
//         |        
//    +----+----+
//    |         |   
// filho_1   filho_2


// ~~~ printfs  ~~~
// pai (ao criar filho): "Processo pai criou %d\n"
//    pai (ao terminar): "Processo pai finalizado!\n"
//  filhos (ao iniciar): "Processo filho %d criado\n"

// Obs:
// - pai deve esperar pelos filhos antes de terminar!


int main(int argc, char** argv) {

    // ....

    /*************************************************
     * Dicas:                                        *
     * 1. Leia as intruções antes do main().         *
     * 2. Faça os prints exatamente como solicitado. *
     * 3. Espere o término dos filhos                *
     *************************************************/

    pid_t pid1 = fork(); //filho 1 criado



    pid_t pid2; 

    if (pid1 != 0) {
        pid2 = fork();
        if (pid2 != 0) {
            printf("Processo pai criou %d\n", pid1);
            printf("Processo pai criou %d\n", pid2);
        }
    }
    

	if (pid1 == 0 || pid2 == 0 ) {
        printf("Processo filho %d criado\n", getpid());
        return 0;
    }
        

      

    while (wait(NULL) >= 0);



    printf("Processo pai finalizado!\n");   
    return 0;
}
