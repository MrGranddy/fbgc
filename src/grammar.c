#include "fbgc.h"

//MATRIX_BEGIN
//Autogenerated by helper/grammar_gen2.py
uint8_t left_matrix[89][15] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{2,0,0,2,2,2,0,0,2,0,2,2,2,2,0},
{2,0,0,2,2,2,0,0,2,0,2,2,2,2,0},
{2,0,0,2,2,2,0,0,2,0,2,2,2,2,0},
{2,0,0,2,2,2,0,0,2,0,2,2,2,2,0},
{2,0,0,2,2,2,0,0,2,0,2,2,2,2,0},
{2,0,0,2,2,2,0,0,2,0,2,2,2,2,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{3,0,0,3,3,3,0,0,3,0,3,3,3,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{3,0,0,3,3,3,0,0,3,0,3,3,3,3,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{14,0,0,0,0,14,0,0,14,0,14,0,0,0,0},
{14,0,0,0,0,14,0,0,14,0,14,0,0,0,0},
{14,0,0,0,0,0,0,14,0,0,0,0,0,0,0},
{14,0,0,0,0,0,0,14,0,0,0,0,0,0,0},
{14,0,0,0,0,0,0,14,0,0,0,0,0,0,0},
{14,0,0,0,0,0,0,14,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{14,0,0,0,0,0,0,14,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{11,0,11,11,11,11,0,0,11,0,11,11,11,11,11},
{0,8,8,0,0,0,0,8,0,8,2,0,0,0,0},
{12,0,12,12,12,12,0,12,12,0,12,12,12,0,0},
{0,15,15,0,0,0,0,15,0,15,0,2,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,9,9,0,0,0,0,9,0,0,0,0,0,0,9},
{0,0,4,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,0,0,0,0,1,0,1,0,0,0,0,1},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{-5,4,4,-5,-5,-5,0,4,-5,0,-5,-5,0,0,4},
{-5,4,4,-5,-5,-5,0,4,-5,0,-5,-5,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{-13,4,4,-13,-13,-13,0,4,-13,0,-13,-13,0,-13,4},
{0,4,4,0,0,0,0,4,0,0,0,0,0,0,4},
{5,0,0,5,5,0,0,0,0,0,0,0,0,0,0},
{5,0,0,5,5,0,0,0,0,0,0,0,0,0,0},
{5,0,0,5,5,0,0,0,0,0,0,0,0,0,0},
{5,0,0,5,5,0,0,0,0,0,0,0,0,0,0},
{0,0,6,0,0,0,0,6,0,0,0,0,0,0,6},
{0,0,6,0,0,0,0,6,0,0,0,0,0,0,6},
{0,0,6,0,0,0,0,6,0,0,0,0,0,0,6},
{0,0,6,0,0,0,0,6,0,0,0,0,0,0,6},
{0,0,6,0,0,0,0,6,0,0,0,0,0,0,6},
{0,0,6,0,0,0,0,6,0,0,0,0,0,0,6},
{0,0,6,0,0,0,0,6,0,0,0,0,0,0,6},
{0,0,6,0,0,0,0,6,0,0,0,0,0,0,6},
{0,0,6,0,0,0,0,6,0,0,0,0,0,0,6},
{0,0,6,0,0,0,0,6,0,0,0,0,0,0,6},
{0,0,6,0,0,0,0,6,0,0,0,0,0,0,6},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
uint8_t right_matrix[89][15] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,8,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,2,3,4,5,6,7,8,9,10,11,12,13,14,3},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,8,0,0,0,0,0,8,0,0,0,0,0,0,0},
{0,8,0,0,0,0,0,8,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,8,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,8,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,8,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,8,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,8,0,0,0,0,0,0,0},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,10,10,0,0,0,0,10,0,0,0,0,0,0,10},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{0,8,8,0,0,0,0,8,0,8,0,0,0,0,8},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,8,8,0,0,0,0,8,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
//MATRIX_END


//Close everything if we are not gonna debug
#ifndef GRAMMAR_DEBUG
#define _info(s,...)
#define _info_green(s,...)
#define _warning(s,...)
#define _print(s,...)
#define _cprint(c,s,...)
#define _debug(s,...)
#define _print_object(s,obj)
#define _println_object(s,obj)
#define _obj2str(obj)
#define _gm2str(gm) 
#endif


uint8_t gm_seek_left(struct fbgc_grammar * gm, struct fbgc_ll_base * obj){

	#define gm_left (gm->top)

	_warning("Grammar LEFT:[%s],Obj:[%s]\n",_gm2str(gm_left),_obj2str(obj));


	int8_t new_left = left_matrix[get_fbgc_object_type(obj)][gm_left-1];
	
	if(new_left < 0){

		new_left = -new_left;	

		_print("Grammar gm_left(%s) has a special function definition",_gm2str(gm_left));
		
		switch(get_fbgc_object_type(obj)){
			case PLUS:
			{
				obj->type = UPLUS;
				break;
			}
			case MINUS:
			{
				obj->type = UMINUS;
				break;
			}
			case PIPE:
			{
				obj->type = LEN;
				break;
			}
			default:
			{
				new_left = GM_ERROR;
				break;
			}	
		}
	}
	
	if(new_left == GM_ERROR){
		_cprint(100,"Unexpected grammar! LEFT:(%s), OBJ:(%s)\n",_gm2str(gm_left),_obj2str(obj));
	}

	gm_left = new_left;

	return (new_left == GM_ERROR) ? _FBGC_SYNTAX_ERROR : _FBGC_NO_ERROR;

	#undef gm_left
}
uint8_t gm_seek_right(struct fbgc_grammar * gm, struct fbgc_ll_base * obj){

	#define gm_right (gm->top)
	
	_warning("Grammar Obj:[%s],RIGHT:[%s]\n",_obj2str(obj),_gm2str(gm_right));

	int8_t new_right = right_matrix[get_fbgc_object_type(obj)][gm_right-1];

	if(new_right == GM_ERROR){
		_cprint(100,"Unexpected grammar! Obj:(%s) RIGHT:(%s)\n",_obj2str(obj),_gm2str(gm_right));
	}
	
	gm_right = new_right;
	return (new_right == GM_ERROR) ? _FBGC_SYNTAX_ERROR : _FBGC_NO_ERROR;

	#undef gm_right
}
