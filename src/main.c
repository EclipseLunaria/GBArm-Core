#include "core.h"
#include "cpu.h"
#include "repl.h"
int main(){
    CPU cpu;
    init_cpu(&cpu);
    run_repl_terminal();



    return 0;

}