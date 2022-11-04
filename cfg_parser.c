#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "assert.h"

#include "cfg_parser.h"


it_str err_list[] = {"Invalid syntax",
                     "Invalid type",
                     "Comment line should start with #",
                     "Equal sign should be each side gapped",
                     "Too big int",
                     "Invalid float"};

void printerr(ERR_CODE errcode, int line){
    printf("\nParsing error: ");
    printf("%s\n", err_list[errcode]);
    printf("Line: %i\n", line);
}

ERR_CODE get_lex(const char* str_buff, char** pos, it_str lex_buf){
    char ch;
    int i = 0;
    bool before = true;
    while(ch = *str_buff){
        if(i  >= LEX_MAX-1) {                                   return SYNTAX;  }
        if(ch == ' ' && before)  { str_buff++;                  continue;       }
        if((ch == '\0' || ch == '\n' || ch == '\r') && before){ return SYNTAX;  }
        if(ch == ' ' && !before) { lex_buf[i+1] = '\0' ;        break;          }
        if(ch == '=') {                                         return SYNTAX; }

        lex_buf[i] = ch;

        str_buff++; i++;
        before = false;
    }
    if(i == 0) return SYNTAX;

    *pos = str_buff; // save cur pos

    return OK;
}

ERR_CODE check_int(const char* istr){
    char ch;
    if(strlen(istr) > 9) { return BIG_INT; }
    while(ch = *istr){
        if(!isdigit(ch)){ return TYPE; }
        istr++;
    }
    return OK;
}

ERR_CODE check_float(const char* fstr){
    char ch;
    while(ch = *fstr){
        

        fstr++;
    }
}

ERR_CODE save_value(const it_str type_lex, const it_str lval_lex, const it_str rval_lex, Cfg_table* cfg_table){
    ERR_CODE retval = OK;
    if(!strcmp(type_lex, "int")){
        if((retval = check_int(rval_lex)) != OK) { return retval; }
        int i                 = cfg_table->icnt;
        cfg_table->ivals[i]   = atoi(rval_lex);
        cfg_table->ihashes[i] = calchash(lval_lex);
        cfg_table->icnt++;
    }else if (!strcmp(type_lex, "float"))
    {
        
    }else if(!strcmp(type_lex, "str")){

    }else{
        return TYPE;
    }

    return retval;
}

ERR_CODE find_eqtoken(const char* str_buff, char** pos){
    char ch;
    int i = 0;
    while(ch = *str_buff){
        if(i  >= LEX_MAX-1) {                       return SYNTAX; }
        if(ch == '\0' || ch == '\n' || ch == '\r'){ return SYNTAX; }
        if(ch == ' ')  { str_buff++;                continue;      }
        
        if(ch == '=') {
            if(*(str_buff - 1) == ' ' && *(str_buff + 1) == ' '){ 
                break;
            } 
            else{
                return EQTOKEN; 
            }
        }else{
            printf("line %i\n", __LINE__);
            return SYNTAX;
        }

        str_buff++; i++;
    }

    *pos = str_buff + 1; // save cur pos (jump over equial token)

    return OK;
}

bool iscomment(const char* str_buff){
    char ch; // cur character
    while(ch = *str_buff){
        if(ch == ' ') { str_buff++; continue; }
        if(ch == '#' || ch == '\0' || ch == '\n' || ch == '\r'){
            return true;
        } else{
            return false;
        }
        str_buff++;
    }
    return true; // empty line
}

Cfg_table* parse_cfg(const it_str filename){
    char str_buff[LINE_MAX] = { 0 };

    char type_lex[LEX_MAX] = { 0 };
    char lval_lex[LEX_MAX] = { 0 };
    char rval_lex[LEX_MAX] = { 0 };

    FILE* fp = fopen(filename, "r");
    assert(fp != NULL);

    Cfg_table* cfg_table = cfgtable_create();
    
    int i;
    for(i = 1; fgets(str_buff, LINE_MAX, fp) != NULL; i++){
        if(iscomment(str_buff)) continue;
        // printf("%s", str_buff);

        char * cur_pos = str_buff;
        
        ERR_CODE errcode = OK;
        if((errcode = get_lex(cur_pos, &cur_pos, type_lex)) == OK) { printf("type   is %s\n", type_lex) ;}
        else { printerr(errcode, i); exit(0); }
        memset(type_lex, 0, LEX_MAX);

        if((errcode = get_lex(cur_pos, &cur_pos, lval_lex)) == OK) { printf("lvalue is %s\n", lval_lex) ;}
        else { printerr(errcode, i); exit(0); }
        memset(lval_lex, 0, LEX_MAX);

        if((errcode = find_eqtoken(cur_pos, &cur_pos)) == OK) {      printf("Equial token has found\n"); }
        else{ printerr(errcode, i); exit(0); }

        if((errcode = get_lex(cur_pos, &cur_pos, rval_lex)) == OK) { printf("rvalue is %s\n", rval_lex) ;}
        else { printerr(errcode, i); exit(0); }
        memset(rval_lex, 0, LEX_MAX);

        if(!iscomment(cur_pos)){ printerr(SYNTAX, i); exit(0); }

        printf("\n");
    }

    fclose(fp);

    return cfg_table;
}
