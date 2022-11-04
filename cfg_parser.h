#ifndef CFG_PARSER_H
#define CFG_PARSER_H

#include "cfg_table.h"
#include "stdbool.h"

typedef enum{
    SYNTAX   = 0,
    TYPE        ,
    COMMENT     ,
    EQTOKEN     ,
    BIG_INT     ,
    INV_FLOAT   ,

    OK      = 0xFFFF
} ERR_CODE;

ERR_CODE get_lex(const char* str_buff, char** pos, it_str lex_buf);
ERR_CODE check_int(const char* istr);
ERR_CODE save_value(const it_str type_lex, const it_str lval_lex, const it_str rval_lex, Cfg_table* cfg_table);
ERR_CODE find_eqtoken(const char* str_buff, char** pos);
bool     iscomment(const char* str_buff);
void     printerr(ERR_CODE errcode, int line);

Cfg_table* parse_cfg(const it_str filename);


#endif // CFG_PARSER_H
