#include "fbgc.h"

struct
fbgc_object * new_fbgc_str_object(const char * str_content){
    struct fbgc_str_object *stro =  (struct fbgc_str_object*) malloc(sizeof(struct fbgc_str_object));
    stro->base.type = STRING;
    stro->base.next = NULL;
    stro->content = (char *)(malloc(sizeof( char )*(strlen(str_content)+1))); 
    memcpy(stro->content,str_content,strlen(str_content)+1);
    stro->content[strlen(str_content)] = '\0';
    return (struct fbgc_object*) stro;
}


struct fbgc_object * new_fbgc_str_object_from_substr(const char * str1,const char * str2){
    
    struct fbgc_str_object *stro =  (struct fbgc_str_object*) malloc(sizeof(struct fbgc_str_object));
    stro->base.type = STRING;
    stro->base.next = NULL;
    stro->content = (char *)(malloc(sizeof( char )*(str2-str1+1))); 
    memcpy(stro->content,str1,(str2-str1));
    stro->content[str2-str1] = '\0';
    return (struct fbgc_object*) stro;    
}


void print_fbgc_str_object(struct fbgc_object * obj){
    cprintf(011,"%s",cast_fbgc_object_as_str(obj)->content);   
}

void free_fbgc_str_object(struct fbgc_object * obj){
    free(cast_fbgc_object_as_str(obj)->content);
    free(obj);
}
