#ifndef FBGC_CSTRUCT_OBJECTH
#define FBGC_CSTRUCT_OBJECTH

#ifdef __cplusplus
extern "C" {
#endif


struct fbgc_cstruct_object{
    struct fbgc_object base;
    const struct fbgc_object_property_holder * properties;
    void * cstruct; // defined in C 
};



#define cast_fbgc_object_as_cstruct(x)( (struct fbgc_cstruct_object *) x)

#define sizeof_fbgc_cstruct_object(x) (sizeof(struct fbgc_cstruct_object) )



struct fbgc_object * new_fbgc_cstruct_object(size_t bsz,const struct fbgc_object_property_holder * );

struct fbgc_object * get_set_fbgc_cstruct_object_member(struct fbgc_object * o, const char * str, struct fbgc_object * rhs);


#ifdef  __cplusplus
}
#endif

#endif
