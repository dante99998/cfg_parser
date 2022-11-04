#ifndef CFG_TABLE_H
#define CFG_TABLE_H

typedef unsigned char* it_str;

#define CFG_MAX    (100)
#define HASH_RANGE (5000)
#define LINE_MAX   (256)
#define LEX_MAX    (50)

typedef struct {
    int      ivals[CFG_MAX];         int icnt;
    float    fvals[CFG_MAX];         int fcnt;
    it_str   svals[CFG_MAX];         int scnt;
    int      svals_sizes[CFG_MAX];

    int      ihashes[CFG_MAX];
    int      fhashes[CFG_MAX];
    int      shashes[CFG_MAX];

} Cfg_table;

Cfg_table* cfgtable_create();
void       cfgtable_delete(Cfg_table* cfg_table);
int        calchash(unsigned char *str);
int        cfgtable_geti(Cfg_table* cfg_table, it_str key);
float      cfgtable_getf(Cfg_table* cfg_table, it_str key);
it_str     cfgtable_gets(Cfg_table* cfg_table, it_str key);

#endif // CFG_TABLE_H