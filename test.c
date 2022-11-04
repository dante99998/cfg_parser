#include "cfg_parser.h"

int main(){

    Cfg_table* cfg_table = parse_cfg("test.txt");

    cfgtable_delete(cfg_table);

    return 0;
}