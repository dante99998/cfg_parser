#include "string.h"
#include "stdlib.h"
#include "assert.h"
#include "stdbool.h"

#include "cfg_table.h"


int calchash(unsigned char *str)
{
    /*
        this algorithm (k=33) was first reported by dan bernstein many years ago in comp.lang.c. 
        another version of this algorithm (now favored by bernstein) uses xor: hash(i) = hash(i - 1) * 33 ^ str[i];
        the magic of number 33 (why it works better than many other constants, prime or not) has never been adequately explained.
    */
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % HASH_RANGE;
}

Cfg_table* cfgtable_create(){
    Cfg_table* cfg_table = (Cfg_table*)malloc(sizeof(Cfg_table)); 
    assert(cfg_table != NULL);
    memset(cfg_table, 0, sizeof(Cfg_table));
    return cfg_table;
}

void cfgtable_delete(Cfg_table* cfg_table){
    assert(cfg_table != NULL);

    int i;
    for(i = 0; i < cfg_table->scnt; i++){
        free(cfg_table->svals[i]);
        // free(cfg_table->svals[i], cfg_table->svals_sizes[i]); // for TDA free
    }

    free(cfg_table);
    // free(cfg_table, sizeof(Cfg_table));
}

int cfgtable_geti(Cfg_table* cfg_table, it_str key){
    assert(cfg_table != NULL);
    int i, hash = calchash(key);
    int ret_val = 0;
    for(i = 0; i < cfg_table->icnt; i++){
        if(hash == cfg_table->ihashes[i]){
            ret_val = cfg_table->ivals[i];
            break;
        }
    }
    return ret_val;
}

float cfgtable_getf(Cfg_table* cfg_table, it_str key){
    assert(cfg_table != NULL);
    int   i, hash = calchash(key);
    float ret_val = 0.f;
    for(i = 0; i < cfg_table->fcnt; i++){
        if(hash == cfg_table->fhashes[i]){
            ret_val = cfg_table->fvals[i];
            break;
        }
    }
    return ret_val;
}

it_str cfgtable_gets(Cfg_table* cfg_table, it_str key){
    assert(cfg_table != NULL);
    int    i, hash = calchash(key);
    it_str ret_val = NULL;
    for(i = 0; i < cfg_table->scnt; i++){
        if(hash == cfg_table->shashes[i]){
            ret_val = cfg_table->svals[i];
            break;
        }
    }
    return ret_val;
}
