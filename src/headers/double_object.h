#ifndef FBGC_DOUBLE_OBJECTH
#define FBGC_DOUBLE_OBJECTH

#ifdef __cplusplus
extern "C" {
#endif

struct fbgc_double_object{
    struct fbgc_object base;
    double content;
};
#define cast_fbgc_object_as_double(x)(((struct fbgc_double_object*) x))



struct fbgc_object * new_fbgc_double_object(double);
struct fbgc_object * new_fbgc_double_object_from_str(const char *);
struct fbgc_object * new_fbgc_double_object_from_substr(const char *,const char *);

struct
fbgc_object * add_fbgc_double_object(struct fbgc_object * a,struct fbgc_object * b);
struct
fbgc_object * subtract_fbgc_double_object(struct fbgc_object * a,struct fbgc_object * b);
struct
fbgc_object * multiply_fbgc_double_object(struct fbgc_object * a,struct fbgc_object * b);
struct
fbgc_object * divide_fbgc_double_object(struct fbgc_object * a,struct fbgc_object * b);



void print_fbgc_double_object(struct fbgc_object *);
void free_fbgc_double_object(struct fbgc_object * );


#ifdef  __cplusplus
}
#endif

#endif

//for db array

/*
struct 
fbgc_object * add_fbgc_double_object (struct fbgc_object *obj, double inc_content){
    struct fbgc_double_object *dbo = (struct fbgc_double_object*) obj;
    if(obj == NULL){
        dbo =  (struct fbgc_double_object*) malloc(sizeof(struct fbgc_double_object));
        dbo->base.type = DOUBLE;
        dbo->base.next = NULL;
        dbo->content = NULL;   
        dbo->size = 0;
    }

    dbo->content = (double*) realloc(dbo->content,sizeof(double) * ++dbo->size);
    *(dbo->content+dbo->size-1) = inc_content;
    return (struct fbgc_object*) dbo;
}*/
