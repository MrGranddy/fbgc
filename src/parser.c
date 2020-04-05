#include "fbgc.h"

//Close everything if we are not gonna debug
#ifndef PARSER_DEBUG
#define _info(s,...)
#define _info_green(s,...)
#define _warning(s,...)
#define _print(s,...)
#define _cprint(c,s,...)
#define _debug(s,...)
#define _print_object(s,obj)
#define _println_object(s,obj)
#define _obj2str(obj)
#define _ll2str(obj)
#define _gm2str(gm)
#endif


#ifdef PARSER_DEBUG
	#define _print_main_list()(_print_fbgc_ll(p.head,"Main"))
	#define _print_op_stack()(_print_fbgc_ll(p.op,"O"))
	#define _print_field_locals(x)(print_field_object_locals(x),cprintf(111,"\n"))
#else
	#define _print_main_list()
	#define _print_op_stack()
	#define _print_field_locals(x)
#endif


#define is_pushable_in_main(x)(!is_fbgc_PARA(x) && x != LEN)

#define is_constant_and_token(x,y)( ((x->type == CONSTANT && _cast_llbase_as_llconstant(x)->content->type == y)) )


#define RIGHT_ASSOC 0b10000000
#define LEFT_ASSOC 0	
const fbgc_token const precedence_table[] =
{
	RIGHT_ASSOC | 0,//IF
	4,//RETURN
	2,//NEWLINE
	RIGHT_ASSOC | 5,//LPARA
	16,//RPARA
	RIGHT_ASSOC | 5,//LBRACK
	16,//RBRACK
	RIGHT_ASSOC | 5,//LBRACE
	16,//RBRACE
	RIGHT_ASSOC | 18,//COMMA // it was 20 now we changed to make bigger than equal sign for x = 1,2,3 cases
	52,//DOT
	3,//SEMICOLON
	32,//COLON	
	42,//R_SHIFT
	42,//L_SHIFT
	RIGHT_ASSOC | 46,//STARSTAR
	RIGHT_ASSOC | 46,//SLASHSLASH
	44,//PLUS
	44,//MINUS
	46,//STAR
	46,//SLASH
	RIGHT_ASSOC | 46,//CARET
	46,//PERCENT
	40,//LO_EQ
	40,//GR_EQ
	38,//EQ_EQ
	38,//NOT_EQ
	40,//LOWER
	40,//GREATER
	34,//PIPE
	36,//AMPERSAND
	46,//EXCLAMATION
	RIGHT_ASSOC | 46,//TILDE	
	RIGHT_ASSOC | 48,//UPLUS
	RIGHT_ASSOC | 48,//UMINUS
	RIGHT_ASSOC | 17,//ASSIGN
	RIGHT_ASSOC | 17,//R_SHIFT_ASSIGN
	RIGHT_ASSOC | 17,//L_SHIFT_ASSIGN
	RIGHT_ASSOC | 17,//STARSTAR_ASSIGN
	RIGHT_ASSOC | 17,//SLASHSLASH_ASSIGN
	RIGHT_ASSOC | 17,//PLUS_ASSIGN
	RIGHT_ASSOC | 17,//MINUS_ASSIGN
	RIGHT_ASSOC | 17,//STAR_ASSIGN
	RIGHT_ASSOC | 17,//SLASH_ASSIGN
	RIGHT_ASSOC | 17,//CARET_ASSIGN
	RIGHT_ASSOC | 17,//PERCENT_ASSIGN
	RIGHT_ASSOC | 17,//ASSIGN_SUBSCRIPT
	47,//LEN
};

uint8_t compare_operators(fbgc_token stack_top, fbgc_token obj_type){
	


	_info("Object type comparison StackTop:[%s]>=Obj[%s]:",object_name_array[stack_top],object_name_array[obj_type]);
	
	// precedence outputs
	// stack_top >= obj_type => return 1;
	// stack_top < obj_type => return 0;

	uint8_t result = 0;
	if(stack_top == IDENTIFIER) 
		result = 1;
	//x=(1,2) requires low precedence!
	else if(obj_type == LBRACK || obj_type == LPARA) result =  0;

	else if(obj_type >= IF && obj_type <= LEN && stack_top >= IF && stack_top <= LEN ){
		//precedence of the operators have to change according to their positions
		//result = (operator_precedence(stack_top) >= operator_precedence(obj_type));
		stack_top = precedence_table[stack_top - IF];
		obj_type = precedence_table[obj_type - IF];
		result = (0x7F & stack_top) > (0x7F & obj_type); // is there another way to perform this calculation ?? 
		if(result == 0 && obj_type == stack_top){
			result = !(0x80 & obj_type); 
		}
	}


	_info("%d\n",result&&1);

	return result;
}


void handle_function_args(struct fbgc_ll_base * fun_holder,struct fbgc_ll_base * arg_end){
	//	arg_start is always next pt of fun_holder
	//	arg_start holds parsed arg expression beginning
	//	example: fun(x,y,z) will be parsed x,y,z
	//							  arg_start^   ^arg_end
	//	There could be default assignment situations, we need to handle assignemnt expr and other type of args
	//Variadic arguments
	//We define them by putting function call operator(), ex: fun(a,b,args())
	
	struct fbgc_object * fun_obj = _cast_llbase_as_llconstant(fun_holder)->content;
	struct fbgc_object * tp = _cast_llbase_as_llconstant(cast_fbgc_object_as_fun(fun_obj)->code)->content;
	cast_fbgc_object_as_fun(fun_obj)->no_arg = size_fbgc_tuple_object(tp); 
	_info("Arg no is %d\n",cast_fbgc_object_as_fun(fun_obj)->no_arg);

	//If arg no is just 1, arg end does not hold correctly
	if(cast_fbgc_object_as_fun(fun_obj)->no_arg == 1)
		arg_end = arg_end->next;

	//Validate the arguments are they normal ?
	struct fbgc_ll_base * iter = fun_holder; //args start is iter->next
	while(iter != arg_end){
		_println_object("iter :",iter);
		if(iter->next->type == IDENTIFIER || iter->next->type == COMMA) //this is ok just fun arg definition
			iter = iter->next;
		else if(iter->next->type == FUN_CALL){
			//this is variadic template, it must be the last arguments
			if(iter->next->next != arg_end){
				_FBGC_LOGE("Variadic argmust be the last arg!");
				assert(0);	
			}

			//Make it negative so we will understand that it has variadic template
			cast_fbgc_object_as_fun(fun_obj)->no_arg *= -1;

			arg_end = iter->next;
			
			if(arg_end->next->type == COMMA){
				arg_end = arg_end->next;
			}

			break;

		}
		else{
			cprintf(100,"Syntax error in function definition!\n");
			_print_object("Error:",iter->next);
			assert(0);
		}
	}

	fun_holder->next = arg_end->next;



	_info("Handling function args, # of args:%d\n",cast_fbgc_object_as_fun(fun_obj)->no_arg);	
}

void handle_before_paranthesis(struct parser_packet * p){
	_FBGC_LOGD(PARSER,"\n==================================\nStack top holder:%s\n",_ll2str(TOP_LL(p->op)));
	
	const fbgc_token top_type = TOP_LL(p->op)->type;

	uint8_t	state = 0;
	if(p->iter_prev->type == COMMA) state = 2;
	else if(p->gm != GM_ATOM) state = 1;

	if(top_type == FUN_CALL){
		
		_print("Function call template, p->iter_prev:%s\n",_ll2str(p->iter_prev));

		//state == 2, p->iter_prev is comma
		if(state == 2){
			p->iter_prev->type = FUN_CALL;
		}
		else{

			struct fbgc_ll_base * ito = _new_fbgc_ll_opcode_int(FUN_CALL,state==1);
			ito->next = p->iter_prev->next;
			p->iter_prev->next = ito;
			p->iter_prev = ito;
		}
		_cast_llbase_as_llopcode_int(p->iter_prev)->content += _cast_llbase_as_llopcode_int(TOP_LL(p->op))->content;

		//gm_seek_right(gm,TOP_LL(p->op));
		struct fbgc_ll_base * iter = p->iter_prev->next;
		//Insert top p->op to the list  
		//p->iter_prev->next = TOP_LL(p->op);
		POP_LL(p->op);
		//p->iter_prev = p->iter_prev->next;
		
		char put_pop_top = 0;

		if(!is_empty_fbgc_ll(p->op) )
			put_pop_top = 1;

		put_pop_top = 0;

		if(put_pop_top){
			p->iter_prev->next = _new_fbgc_ll_base(POP_TOP);
			p->iter_prev = p->iter_prev->next;			
		}

		p->iter_prev->next = iter;
	}
	else if(top_type == FUN_MAKE){

		_print("Stack top is FUN_MAKE, function make template!\n");
		struct fbgc_ll_base * fun_holder =  _cast_llbase_as_lljumper(TOP_LL(p->op))->content; 
		struct fbgc_object * fun_obj = _cast_llbase_as_llconstant(fun_holder)->content;

		//Is it possible this is not useful*
		if(cast_fbgc_object_as_fun(fun_obj)->no_arg < 65){
			_print("already created function,arg :%d\n",cast_fbgc_object_as_fun(fun_obj)->no_arg);
			return;
		}
		//fun_make content holds function object, parse the arguments
		//gm_seek_right(&p);

		_print("Function Arg Start:%s\n",_ll2str(fun_holder->next));
		_print_fbgc_ll_code(fun_holder->next,p->iter_prev);
		_print("Function Arg End:%s\n",_ll2str(p->iter_prev));

		handle_function_args(fun_holder,p->iter_prev);
		p->iter_prev = fun_holder;
	}
	else if(top_type == CLASS_MAKE){
		FBGC_LOGD(PARSER,"Stack top is CLASS_MAKE, making class template!");



		struct fbgc_ll_base * cls_holder =  _cast_llbase_as_lljumper(TOP_LL(p->op))->content; 
		struct fbgc_object * cls_obj = _cast_llbase_as_llconstant(cls_holder)->content;

		if(_cast_llbase_as_llconstant(TOP_LL(p->scope_list))->content == cls_obj)
			return;

		_print("Class Arg Start:%s\n",_ll2str(cls_holder->next));
		//_print_fbgc_ll_code(cls_holder->next,p->iter_prev);
		_print("Class Arg End:%s\n",_ll2str(p->iter_prev));
		_push_front_fbgc_ll(p->scope_list,_new_fbgc_ll_constant(cls_obj));

		struct fbgc_ll_base * iter = cls_holder;
		/*while(iter != p->iter_prev){
			if(iter->next->type == IDENTIFIER){
				iter = iter->next;
			}
			else assert(0);
		}*/

		//cls_holder->next = p->iter_prev->next;
		if(cls_holder->next->type == IDENTIFIER){
			cls_holder = cls_holder->next;
			//p->iter_prev = p->iter_prev->next;
			//p->gm = GM_NEWLINE;
		}
		cast_fbgc_object_as_class(cls_obj)->code = cls_holder;

		_print("Class code :%s\n",_ll2str(cast_fbgc_object_as_class(cls_obj)->code));


	}
	else if(top_type == FOR){

		if(_cast_llbase_as_lljumper(TOP_LL(p->op))->content->type == FOR_BEGIN)
			return;
		
		//XXgm_seek_right(gm,TOP_LL(p->op));

		_print("Stack top is FOR, for loop template!\n");
		_print("For loop content:%s\n",_ll2str(_cast_llbase_as_lljumper(TOP_LL(p->op))->content));
		_print("Iterator previous:%s\n",_ll2str(p->iter_prev));
		
		if(p->iter_prev->type != ASSIGN){
			//This makes sure we have for i = x type of loop definition
			return NULL;
		}

		struct fbgc_ll_base * d = _cast_llbase_as_lljumper(TOP_LL(p->op))->content;
		while(d->next != p->iter_prev)
			d = d->next;
		
		struct fbgc_ll_base * fb = _new_fbgc_ll_base(FOR_BEGIN);
		fb->next = d->next;
		d->next = fb;
		_cast_llbase_as_lljumper(TOP_LL(p->op))->content = fb;

	}	
	else if( (top_type == IF || top_type == ELIF || top_type == WHILE) && _cast_llbase_as_lljumper(TOP_LL(p->op))->content == NULL){
		_print("Stack top is %s, conditional template!\n",_ll2str(TOP_LL(p->op)));
		//XXgm_seek_right(gm,TOP_LL(p->op));
		_cast_llbase_as_lljumper(TOP_LL(p->op))->content = p->iter_prev;
		_warning("If shows %s\n",_ll2str(p->iter_prev->next));	
	}
	else if(p->iter_prev->type == COMMA || p->gm == GM_ATOM){
		
		if(state == 2){
			_debug("State number is 2, changing COMMA to BUILD_TUPLE\n");
			p->iter_prev->type = BUILD_TUPLE;
		} 
		else if(state == 0){
			_debug("State number is 0, creating new object BUILD_TUPLE with 0 size\n");
			struct fbgc_ll_base * ito = _new_fbgc_ll_opcode_int(BUILD_TUPLE,0);
			ito->next = p->iter_prev->next;
			p->iter_prev->next = ito;
			p->iter_prev = ito;
		}
		//If nothing than it's a tuple!

	}
	else{
		
		//Should we put an error or not ....?
		/*_println_object("iter prev :",p->iter_prev);
		_print_op_stack();
		assert(0);*/
	}

	_info("==================================\n");
}

void handle_before_brackets(struct parser_packet *p){
	_FBGC_LOGD(PARSER,"\n==================================\nStack top holder:%s\n",_ll2str(TOP_LL(p->op)));

	
	uint8_t	state = 0;
	if(p->iter_prev->type == COMMA) state = 2;
	else if(p->gm != GM_ATOM) state = 1;


	
	if(is_fbgc_ASSIGNMENT_OPERATOR(p->iter_prev->next->type)) return;
	
	if(TOP_LL(p->op)->type == IDENTIFIER || TOP_LL(p->op)->type == LOAD_SUBSCRIPT){	
		_info("Operator stack top load_local or global, this is a subscript call template!\n");

		struct fbgc_ll_base * iter = p->iter_prev->next;
		//Insert top op to the list  
		p->iter_prev->next = TOP_LL(p->op);
		POP_LL(p->op);
		p->iter_prev = p->iter_prev->next;
		p->iter_prev->next = iter;
	}
	else{
		if(state == 2) p->iter_prev->type = BUILD_MATRIX; 
		else {
			struct fbgc_ll_base * ito = _new_fbgc_ll_opcode_int(BUILD_MATRIX,state==1);
			ito->next = p->iter_prev->next;
			p->iter_prev->next = ito;
			p->iter_prev = ito;
		}		
	}
	
	_info("==================================\n");
}

uint8_t parser(struct fbgc_object ** field_obj, FILE * input_file){

	FBGC_LOGD(PARSER,"==========[PARSER]==========");

	struct parser_packet p = {
		.head = _cast_llbase_as_ll( cast_fbgc_object_as_field(*field_obj)->head ),
		.iter = p.head->base.next,
		.iter_prev = (struct fbgc_ll_base *)p.head, //note that p.iter_prev->next is p.iter, always this is the case!
		.op = _new_fbgc_ll(),
		.scope_list = _new_fbgc_ll(),
		.error_code = _FBGC_NO_ERROR,
		.gm = GM_NEWLINE,
	};
	
		
	_push_front_fbgc_ll(p.scope_list,_new_fbgc_ll_constant(*field_obj));
	#define current_scope _cast_llbase_as_llconstant(TOP_LL(p.scope_list))->content
	#define previous_scope _cast_llbase_as_llconstant(TOP_LL(p.scope_list)->next)->content


	char line[1000] = {0};
	int line_no = 0;

	for(int i = 0; fbgc_error(p.error_code,line_no) ; i++){
		if(p.iter == p.head->tail){
			if(fbgc_getline_from_file(line, sizeof(line), input_file)){
				++line_no;

				if(line[0] == '#' || line[0] == '\0' || line[0] == '\n') {
					--i;
					continue; //fast passing the comment
				}
				_debug("Processed line[%d]:{%s}\n",line_no,line);
				
				p.head->tail->next = p.iter_prev;
				regex_lexer(field_obj,line);
				p.iter = p.iter_prev->next;
			}
			else break;
		}
	

	_cprint(010,"----------[%d]{%s:",i,_ll2str(p.iter));  _cprint(010,"}----------\n");

	switch(p.iter->type){
	case CONSTANT:
	{

		if( (p.error_code = gm_seek_left(&p)) != _FBGC_NO_ERROR  ){ goto PARSER_ERROR_LABEL; }	
		p.iter_prev = p.iter;
		break;
	}
	case IDENTIFIER:{

		if( (p.error_code = gm_seek_left(&p)) != _FBGC_NO_ERROR  ){ goto PARSER_ERROR_LABEL; }

		_info("Current Scope for identifier:(%s)\n",_obj2str(current_scope));
		struct fbgc_object * cstr_obj = get_object_in_fbgc_tuple_object(fbgc_symbols,get_ll_identifier_loc(p.iter));
		_println_object("Symbol name as a cstring object:",cstr_obj);
			
		struct fbgc_object * cf = NULL;

		if(!is_empty_fbgc_ll(p.op) && TOP_LL(p.op)->type == DOT){
			//so this is just a member selection
			POP_LL(p.op); //pop the dot object
			//now get the name of instance
			struct fbgc_ll_base * cstr_holder = _new_fbgc_ll_constant(cstr_obj);
			p.iter_prev->next = cstr_holder;
			cstr_holder->next = p.iter->next;
			p.iter_prev = cstr_holder;
			set_id_flag_MEMBER(p.iter);
		}
		else if((cf = new_cfun_object_from_str(*field_obj,&cast_fbgc_object_as_cstr(cstr_obj)->content)) != NULL){
			//remove identifier object, put cfun object into list
			//cf->next = p.iter->next;
			//p.iter = cf;
			struct fbgc_ll_base * cfun_holder = _new_fbgc_ll_constant(cf);
			p.iter_prev->next =  cfun_holder;
			cfun_holder->next = p.iter->next;
			p.iter_prev = cfun_holder;
			break;	
		}
		else if(current_scope->type == FIELD || current_scope->type == CLASS){

			struct fbgc_object * local_array; 

			if(current_scope->type == FIELD) local_array = cast_fbgc_object_as_field(current_scope)->locals;
			else local_array = cast_fbgc_object_as_class(current_scope)->locals;

			struct fbgc_identifier * temp_id; 
			int where = -1;

			for(int i = 0; i<size_fbgc_array_object(local_array); i++){
				temp_id = (struct fbgc_identifier *) get_address_in_fbgc_array_object(local_array,i);
				if(temp_id->name == cstr_obj) {
					where = i;
					break;
				} 
			}

			if(where == -1) {
				_info("Creating a variable inside a field obj\n");
				
				struct fbgc_identifier id;		
				id.name = cstr_obj; id.content = NULL;
				local_array = push_back_fbgc_array_object(local_array,&id);
				where = size_fbgc_array_object(local_array)-1;

				if(current_scope->type == FIELD) cast_fbgc_object_as_field(current_scope)->locals = local_array;
				else cast_fbgc_object_as_class(current_scope)->locals = local_array;
				
				_info("Symbol is created @ [%d]\n",where);
			}
			else{
				_info_green("Symbol is already defined @ [%d]\n",where);
			}

			
			set_id_flag_GLOBAL(p.iter);

			_cast_fbgc_object_as_llidentifier(p.iter)->loc = where;
		}

		else if(current_scope->type == FUN){				
			struct fbgc_object * local_tuple = 
				_cast_llbase_as_llconstant(cast_fbgc_object_as_fun(current_scope)->code)->content;
			int where = index_fbgc_tuple_object(local_tuple,cstr_obj);
			set_id_flag_LOCAL(p.iter);

			if(where == -1) {
				_print("p.iter->next type(%s)\n",_ll2str(p.iter->next));

				//65 arg means func definition hasnt been done yet! So we are reading arguments
				if(p.iter->next->type == ASSIGN  || cast_fbgc_object_as_fun(current_scope)->no_arg == 65){
					_info("Id object is an argument of function or a new definition inside the function\n");

					local_tuple = push_back_fbgc_tuple_object(local_tuple,cstr_obj);
					where = size_fbgc_tuple_object(local_tuple)-1;
					_cast_llbase_as_llconstant(cast_fbgc_object_as_fun(current_scope)->code)->content = local_tuple;
					
					_println_object("Fun local tuple:",local_tuple);
				}
				else {
					_info("Searching ID object in global (class or field)\n");

					local_tuple = cast_fbgc_object_as_field(*field_obj)->locals;
					struct fbgc_identifier * temp_id; 
					for(int i = 0; i<size_fbgc_array_object(local_tuple); i++){
						temp_id = (struct fbgc_identifier *) get_address_in_fbgc_array_object(local_tuple,i);
						if(temp_id->name == cstr_obj) where = i; 
					}						
					
					if(where == -1){
						_info("Creating a variable inside a previous global\n");
						struct fbgc_object * local_array; 

						local_array = cast_fbgc_object_as_field(*field_obj)->locals;
						

						
						struct fbgc_identifier id;		
						id.name = cstr_obj; id.content = NULL;
						local_array = push_back_fbgc_array_object(local_array,&id);
						where = size_fbgc_array_object(local_array)-1;

						cast_fbgc_object_as_field(*field_obj)->locals = local_array;
						
					}
					_print("Id object is found @ [%d]",where);
					set_id_flag_GLOBAL(p.iter);
				}
			}
			
			
			set_ll_identifier_loc(p.iter,where);
		}

		p.iter_prev->next = p.iter->next;
		_push_front_fbgc_ll(p.op,p.iter);
		break;
	}
	case END:{
		p.error_code = gm_seek_left(&p);

		_info("Before handling END keyword\n");
		_print_main_list();
		_print_op_stack();

		p.iter_prev->next = p.iter->next;
		

		if(TOP_LL(p.op)->type == IF){
			//now insert if in its place,

			struct fbgc_ll_base * if_obj = TOP_LL(p.op);
			POP_LL(p.op);

			if_obj->next = _cast_llbase_as_lljumper(if_obj)->content->next;
			_cast_llbase_as_lljumper(if_obj)->content->next = if_obj;
			_cast_llbase_as_lljumper(if_obj)->content = p.iter_prev; //now assign where to jump

		}
		else if(TOP_LL(p.op)->type == ELIF){
			//now insert if in its place,
			struct fbgc_ll_base * if_obj = TOP_LL(p.op);
			POP_LL(p.op);

			if_obj->next = _cast_llbase_as_lljumper(if_obj)->content->next;
			_cast_llbase_as_lljumper(if_obj)->content->next = if_obj;
			_cast_llbase_as_lljumper(if_obj)->content = p.iter_prev;
		}
		else if(TOP_LL(p.op)->type == WHILE){
			//now insert while in its place,
			struct fbgc_ll_base * if_obj = TOP_LL(p.op);
			POP_LL(p.op);

			if_obj->next = _cast_llbase_as_lljumper(if_obj)->content->next;
			_cast_llbase_as_lljumper(if_obj)->content->next = if_obj;

			struct fbgc_ll_base * jump_obj = TOP_LL(p.op);
			POP_LL(p.op);

			jump_obj->next = p.iter_prev->next;
			p.iter_prev->next = jump_obj;
			p.iter_prev = jump_obj;
			
			_cast_llbase_as_lljumper(if_obj)->content = jump_obj;
		}
		else if(TOP_LL(p.op)->type == FOR){
			//now insert while in its place,
			struct fbgc_ll_base * if_obj = TOP_LL(p.op);
			POP_LL(p.op);

			if_obj->next = _cast_llbase_as_lljumper(if_obj)->content->next;
			_cast_llbase_as_lljumper(if_obj)->content->next = if_obj;

			struct fbgc_ll_base * jump_obj = TOP_LL(p.op);
			POP_LL(p.op);

			_cast_llbase_as_lljumper(jump_obj)->content = _cast_llbase_as_lljumper(if_obj)->content;	

			jump_obj->next = p.iter_prev->next;
			p.iter_prev->next = jump_obj;
			p.iter_prev = jump_obj;
			
			_cast_llbase_as_lljumper(if_obj)->content = jump_obj;
		}
		else if(TOP_LL(p.op)->type == FUN_MAKE){

			//Check the function is empty or not, we need to handle this
			assert(p.iter_prev->type != FUN);  // why do we have this

			//???
			struct fbgc_ll_base * fun_holder = _cast_llbase_as_lljumper(TOP_LL(p.op))->content;
			struct fbgc_object * fun_obj = _cast_llbase_as_llconstant(fun_holder)->content;
			
			struct fbgc_object * tp = _cast_llbase_as_llconstant(cast_fbgc_object_as_fun(fun_obj)->code)->content;
			cast_fbgc_object_as_fun(fun_obj)->no_locals = size_fbgc_tuple_object(tp); 
			cast_fbgc_object_as_fun(fun_obj)->code = fun_holder->next;

			//This is commented to just save the day..
			//if(p.iter_prev->type != RETURN){
				//add NIL object 
				p.iter_prev->next = _new_fbgc_ll_constant(__fbgc_nil);
				p.iter_prev = p.iter_prev->next;
				p.iter_prev->next = _new_fbgc_ll_base(RETURN);
				p.iter_prev = p.iter_prev->next;
			//}

			p.iter_prev->next = NULL; //last token in function code shows NULL
			p.iter_prev = fun_holder;

			POP_LL(p.op); //Remove fun_make
			p.iter_prev->next = p.iter->next;

			POP_LL(p.scope_list);
			//current_scope = *field_obj; //Go back to the previous scope
		}
		else if(TOP_LL(p.op)->type == CLASS_MAKE){

			struct fbgc_ll_base * cls_holder = _cast_llbase_as_lljumper(TOP_LL(p.op))->content;
			struct fbgc_object * cls_obj = _cast_llbase_as_llconstant(cls_holder)->content;
			int arg_no = 0;

			while(cls_holder != cast_fbgc_object_as_class(cls_obj)->code){
				cls_holder = cls_holder->next;
				arg_no++;
			}

			FBGC_LOGV(PARSER,"Class inheritance arg no:%d\n",arg_no);

			cls_holder = cast_fbgc_object_as_class(cls_obj)->code;

			cast_fbgc_object_as_class(cls_obj)->code = cast_fbgc_object_as_class(cls_obj)->code->next;


			p.iter_prev->next = _new_fbgc_ll_constant(cls_obj);
			p.iter_prev = p.iter_prev->next;
			p.iter_prev->next = _new_fbgc_ll_base(RETURN);
			p.iter_prev = p.iter_prev->next;

			p.iter_prev->next = NULL;
			POP_LL(p.op);
			POP_LL(p.scope_list);
			p.iter_prev = cls_holder; 
			p.iter_prev->next = _new_fbgc_ll_opcode_int(CLASS_CALL,arg_no);
			p.iter_prev = p.iter_prev->next;
			p.iter_prev->next = p.iter->next;

		}
		else if(TOP_LL(p.op)->type != JUMP){
			cprintf(100,"Found extra END keyword\n");
			p.error_code = _FBGC_SYNTAX_ERROR;
			goto PARSER_ERROR_LABEL;
		}

		while(TOP_LL(p.op) != NULL && TOP_LL(p.op)->type == JUMP){
			struct fbgc_ll_base * jump_obj = TOP_LL(p.op);
			POP_LL(p.op);

			jump_obj->next = _cast_llbase_as_lljumper(jump_obj)->content->next;
			_cast_llbase_as_lljumper(jump_obj)->content->next = jump_obj;

			_cast_llbase_as_lljumper(jump_obj)->content = p.iter_prev;	
		}

		//p.iter_prev->next = p.iter->next;

		_info("After handling END keyword\n");
		_print_main_list();
		_print_op_stack();

		break;			
	}
	case FUN_MAKE:{
		p.error_code = gm_seek_left(&p);
		struct fbgc_object * fun_obj = new_fbgc_fun_object();
		struct fbgc_ll_base * fun_holder = _new_fbgc_ll_constant(fun_obj);
		fun_holder->next = p.iter->next;
		p.iter_prev->next = fun_holder;
		p.iter_prev = fun_holder;
		_cast_llbase_as_lljumper(p.iter)->content = fun_holder;
		_push_front_fbgc_ll(p.op,p.iter);

		_push_front_fbgc_ll(p.scope_list,_new_fbgc_ll_constant(fun_obj));
		//current_scope = fun_obj;

		cast_fbgc_object_as_fun(fun_obj)->code = _new_fbgc_ll_constant(new_fbgc_tuple_object(0));
		break;		
	}
	case CLASS_MAKE:{
		
		
		p.error_code = gm_seek_left(&p);	
		struct fbgc_object * cls_obj = new_fbgc_class_object();
		struct fbgc_ll_base * cls_holder = _new_fbgc_ll_constant(cls_obj);
		cls_holder->next = p.iter->next;
		p.iter_prev->next = cls_holder;
		p.iter_prev = cls_holder;
		_cast_llbase_as_lljumper(p.iter)->content = cls_holder;
		_push_front_fbgc_ll(p.op,p.iter);
		
		//Moving this to handle paranthesis for
		//_push_front_fbgc_ll(p.scope_list,_new_fbgc_ll_constant(cls_obj));
		
		break;
	}	
	case ELIF:{
		//p.error_code = gm_seek_right(&p.gm,TOP_LL(p.op));
		//p.error_code = gm_seek_left(&p.gm,p.iter);	

		if(is_empty_fbgc_ll(p.op) && (TOP_LL(p.op)->type != IF || TOP_LL(p.op)->type != ELIF)){
			//We raise this error because we couldn't find any if before so it's not just a syntax error.
			//## Give proper error message
			p.error_code = _FBGC_SYNTAX_ERROR;
			goto PARSER_ERROR_LABEL;
		}

		//now insert if in its place,
		struct fbgc_ll_base * if_obj = TOP_LL(p.op);
		POP_LL(p.op);
		if_obj->next = _cast_llbase_as_lljumper(if_obj)->content->next;
		_cast_llbase_as_lljumper(if_obj)->content->next = if_obj;

		struct fbgc_ll_base * jump_obj = _new_fbgc_ll_jumper(JUMP);

		_cast_llbase_as_lljumper(jump_obj)->content = p.iter_prev;

		_cast_llbase_as_lljumper(if_obj)->content = jump_obj;

		_push_front_fbgc_ll(p.op,jump_obj);
		p.iter_prev->next = p.iter->next;	
		_push_front_fbgc_ll(p.op,p.iter);			

		break;
	}
	case ELSE:{

		//p.error_code = gm_seek_right(&p.gm,TOP_LL(p.op));
		//p.error_code = gm_seek_left(&p.gm,p.iter);	

		if(is_empty_fbgc_ll(p.op) || (TOP_LL(p.op)->type != IF && TOP_LL(p.op)->type != ELIF) ){
			cprintf(100,"Top type = %s\n",object_name_array[TOP_LL(p.op)->type]);
			p.error_code = _FBGC_SYNTAX_ERROR;
			goto PARSER_ERROR_LABEL;
		}

		//now insert if in its place,
		struct fbgc_ll_base * if_obj = TOP_LL(p.op);
		POP_LL(p.op);
		if_obj->next = _cast_llbase_as_lljumper(if_obj)->content->next;
		_cast_llbase_as_lljumper(if_obj)->content->next = if_obj;

		struct fbgc_ll_base * jump_obj = _new_fbgc_ll_jumper(JUMP);

		_cast_llbase_as_lljumper(jump_obj)->content = p.iter_prev;
		_push_front_fbgc_ll(p.op,jump_obj);

		_cast_llbase_as_lljumper(if_obj)->content = jump_obj;

		

		p.iter_prev->next = p.iter->next;				
		break;
	}
	case WHILE:{
		p.error_code = gm_seek_left(&p);	

		struct fbgc_ll_base * jump_obj = _new_fbgc_ll_jumper(JUMP);
		if(TOP_LL(p.op) != NULL && TOP_LL(p.op)->type == WHILE){
			//This is a branch optimization to solve an issue between two while loops
			//if we have a situation
			// while(a)
			//	while(b)
			//jump object of second while holds 'a' to jump because a->next is b
			//however, second while loop will be inserted between 'a' and 'b' so
			//it will jump to while in the interpreter
			//now we can directly put the jump branch at while object
			// new configuration will look like this, first jump object jumps to the next of while which is 'b'
			// a,while,b,while,jump,jump 
			//		   ^---------|   |
			// ^---------------------|

			_cast_llbase_as_lljumper(jump_obj)->content = TOP_LL(p.op);
		}
		else if(TOP_LL(p.op) != NULL && TOP_LL(p.op)->type == FOR){
			cprintf(111,"Why do we have this?\n");
			assert(0);
		}
		else
			_cast_llbase_as_lljumper(jump_obj)->content = p.iter_prev;

		_push_front_fbgc_ll(p.op,jump_obj);
		p.iter_prev->next = p.iter->next;	
		_push_front_fbgc_ll(p.op,p.iter);	
		//p.iter_prev->next = p.iter->next;	
		break;
	}
	case FOR:{
		p.error_code = gm_seek_left(&p);	

		_cast_llbase_as_lljumper(p.iter)->content = p.iter_prev;

		struct fbgc_ll_base * jump_obj = _new_fbgc_ll_jumper(JUMP);
		_cast_llbase_as_lljumper(jump_obj)->content = p.iter_prev;
		_push_front_fbgc_ll(p.op,jump_obj);
		p.iter_prev->next = p.iter->next;	
		_push_front_fbgc_ll(p.op,p.iter);				
		break;
	}			
	case BREAK:
	case CONT:{
		p.iter_prev = p.iter;
		p.error_code = gm_seek_left(&p);

		struct fbgc_ll_base * op_top = TOP_LL(p.op);

		for(;;){
			assert(!is_empty_fbgc_ll(p.op));

			if(op_top->type == WHILE || op_top->type == FOR){

				if(p.iter->type == CONT){
					assert(op_top->next->type == JUMP);
					//here we assumed there will be always jump object after while in the stack
					op_top = op_top->next;
				}

				_cast_llbase_as_lljumper(p.iter)->content = op_top;
				break;
			}
			op_top = op_top->next;
		}
		break;
	}
	case IF:
	case RETURN:
	case NEWLINE:
	case LPARA:
	case RPARA:
	case LBRACK:
	case RBRACK:
	//case LBRACE:
	//case RBRACE:
	case COMMA:
	case DOT:
	case SEMICOLON:
	case COLON:
	case RSHIFT:
	case LSHIFT:
	case STARSTAR:
	case SLASHSLASH:
	case PLUS:
	case MINUS:
	case STAR:
	case SLASH:
	case CARET:
	case PERCENT:
	case LOEQ:
	case GREQ:
	case EQEQ:
	case NOTEQ:
	case LOWER:
	case GREATER:
	case PIPE:
	case AMPERSAND:
	case EXCLAMATION:
	case TILDE:		
	case UPLUS:
	case UMINUS:{

		//take the p.op object from main list and connect previous one to the next one 
		//[H]->[2]->[+]->[3] => [H]->[2]->[3], now p.iter holds the operator, p.iter->next is [3] but we will change that too 
		//     p^	i^					
		p.iter_prev->next = p.iter->next;
		//struct fbgc_object * p.iterp2 = p.iter_prev;

		
		while( is_not_empty_fbgc_ll(p.op) && compare_operators(get_fbgc_object_type(TOP_LL(p.op)),p.iter->type) ){

			if( (p.error_code = gm_seek_right(&p)) != _FBGC_NO_ERROR ){
				goto PARSER_ERROR_LABEL;
			}

			
			if(is_pushable_in_main(get_fbgc_object_type(TOP_LL(p.op)))){
				//Insert top p.op to the list  
				p.iter_prev->next = TOP_LL(p.op);
				//Pop top from stack
				POP_LL(p.op);
				//connect list again
				p.iter_prev->next->next = p.iter->next; 
				//make the p.iter_prev proper
				p.iter_prev = p.iter_prev->next;
				
			}
			else{

				_warning("Top object is not pushable to main list\n");
				
				if(p.iter->type == SEMICOLON && get_fbgc_object_type(TOP_LL(p.op)) == LBRACK){
					
					#ifdef PARSER_DEBUG
					cprintf(110,"\tBRACK AND SEMICOLON\n");
					#endif
					break;
				}
				else if(p.iter->type == PIPE && get_fbgc_object_type(TOP_LL(p.op)) == LEN){
						
					p.iter->next = p.iter_prev->next;
					//eat the pipe insert the len
					p.iter_prev->next = TOP_LL(p.op);
					//Pop top from stack
					POP_LL(p.op);
					p.iter_prev = p.iter_prev->next;
					p.iter_prev->next = p.iter->next;

					break;
				}
				else if(get_fbgc_object_type(TOP_LL(p.op)) == LPARA){
					POP_LL(p.op);
					break;
				}
				else {
					cprintf(111,"Syntax Error :");
					cprintf(011,"Op Top :[%s], p.iter:[%s]\n",object_name_array[get_fbgc_object_type(TOP_LL(p.op))],object_name_array[p.iter->type]);
					assert(0);
					//goto END_OF_THE_PARSER;
				}
			}
			_info_green("Checking the operator stack, inside the while loop\n");
			_print_main_list();
			_print_op_stack();
			_print("[GM]:{%s}\n",_gm2str(p.gm));

		}
		
		/*
			print((1,2,3)) gibi durumlarda p.iter_prev:cfun ve stacktop:lpara olduğu için
			tuple kurmak yerine function call atıyor. Bu hatayı düzeltmek için grammarde ne olduğunu bilmek gerekir
			Bu tip durumların düzeltilmesi gerekli.
		*/		
		fbgc_grammar gm_prev = p.gm;

		if( (p.error_code = gm_seek_left(&p)) != _FBGC_NO_ERROR  ){ goto PARSER_ERROR_LABEL; }

		if(p.iter->type == LPARA){
			_warning("p.iter is LPARA, p.iter_prev %s\n",_ll2str(p.iter_prev));

			// && TOP_LL(p.op)->type != LPARA we need to put this to ensure tuple entries

			if((gm_prev == GM_ID || gm_prev == GM_MATRIX) && (p.iter_prev->type == IDENTIFIER || p.iter_prev->type == LOAD_SUBSCRIPT || is_constant_and_token(p.iter_prev,CFUN) )) {
						
				if(p.iter_prev->type == CONSTANT && _cast_llbase_as_llconstant(p.iter_prev)->content->type == CFUN){
					_warning("match!\n");
				}

				if(p.iter_prev->type == IDENTIFIER && is_id_flag_MEMBER(p.iter_prev)){
					set_id_flag_MEMBER_METHOD(p.iter_prev);
					_push_front_fbgc_ll(p.op,_new_fbgc_ll_opcode_int(FUN_CALL,1));
				}
				else _push_front_fbgc_ll(p.op,_new_fbgc_ll_opcode_int(FUN_CALL,0));
			}
			_push_front_fbgc_ll(p.op,p.iter);
		}
		else if(p.iter->type == LBRACK){
			_warning("p.iter is LBRACK, p.iter_prev %s\n",_ll2str(p.iter_prev));
			if(p.iter_prev->type == IDENTIFIER || p.iter_prev->type == FUN_CALL){
				_push_front_fbgc_ll(p.op,_new_fbgc_ll_base(LOAD_SUBSCRIPT));
			}
			_push_front_fbgc_ll(p.op,p.iter);
		}
		else if(p.iter->type == ROW ){
			;
		}
		else if(p.iter->type == COMMA){
			if(TOP_LL(p.op)->type == COMMA){
				_cast_llbase_as_llopcode_int(TOP_LL(p.op))->content++;
			}
			else {
				//Also insert a lpara object for tuple entries without paranthesis
				if(get_fbgc_object_type(TOP_LL(p.op)) != LPARA && get_fbgc_object_type(TOP_LL(p.op)) != LBRACK){
					_push_front_fbgc_ll(p.op,_new_fbgc_ll_base(LPARA));
				}

				_push_front_fbgc_ll(p.op, _new_fbgc_ll_opcode_int(COMMA,2));
			}
		}
		else if( p.iter->type == RBRACK){
			
			if(TOP_LL(p.op)->type == LBRACK){
				_pop_front_fbgc_ll(p.op);
			}
			else assert(0);
			handle_before_brackets(&p);
			if( p.error_code != _FBGC_NO_ERROR  ){ goto PARSER_ERROR_LABEL; }

					
		}
		else if(p.iter->type == SEMICOLON && get_fbgc_object_type(TOP_LL(p.op)) == LBRACK){
			if(p.iter_prev->type == COMMA) p.iter_prev->type = ROW; 
			else if(p.iter_prev->type != ROW){
				struct fbgc_ll_base * ito = _new_fbgc_ll_opcode_int(ROW,1);
				ito->next = p.iter_prev->next;
				p.iter_prev->next = ito;
				p.iter_prev = ito;
			}
		}
		else if(p.iter->type == RPARA || p.iter->type == NEWLINE || p.iter->type == SEMICOLON){

			_warning("%s out of while loop\n",_ll2str(p.iter));
			_warning("Grammar top %s\n",_gm2str(p.gm));


			if(p.iter->type == RPARA && TOP_LL(p.op)->type == LPARA) _pop_front_fbgc_ll(p.op);
			else if(p.iter->type == NEWLINE && TOP_LL(p.op)->type == LPARA) _pop_front_fbgc_ll(p.op);

			handle_before_paranthesis(&p);
			if( p.error_code != _FBGC_NO_ERROR  ){ goto PARSER_ERROR_LABEL; }


			if(p.iter->type == NEWLINE || p.iter->type == SEMICOLON) p.gm = GM_NEWLINE;

			if(p.iter_prev->type == BUILD_TUPLE){
				if(p.iter->type == NEWLINE && !is_empty_fbgc_ll(p.op)){
					//Now fool the loop and check newline state again,
					p.iter_prev->next = p.iter;
					p.iter = p.iter_prev;
					p.gm = GM_EXPRESSION;
				}
			}
		}
		else {
			_push_front_fbgc_ll(p.op,p.iter);
		}


		break;
	}
	case ASSIGN:
	case RSHIFT_ASSIGN:
	case LSHIFT_ASSIGN:
	case STARSTAR_ASSIGN:
	case SLASHSLASH_ASSIGN:
	case PLUS_ASSIGN:
	case MINUS_ASSIGN:
	case STAR_ASSIGN:
	case SLASH_ASSIGN:
	case CARET_ASSIGN:
	case PERCENT_ASSIGN:{

		if( (p.error_code = gm_seek_left(&p)) != _FBGC_NO_ERROR  ){ goto PARSER_ERROR_LABEL; }
		

		if(TOP_LL(p.op)->type != IDENTIFIER && TOP_LL(p.op)->type != LOAD_SUBSCRIPT){
			p.error_code = _FBGC_SYNTAX_ERROR;
			cprintf(100,"Assignment operator requires identifier before itself\n");
			goto PARSER_ERROR_LABEL;
		}
		
		//XXX remove this push itself thing
		//fbgc_assert(TOP_LL(p.op)->type == IDENTIFIER ,"Assignment to a non-identifier object, object type:%s\n",object_name_array[TOP_LL(p.op)->type]);
		//cprintf(111,"top->next = %s\n",object_name_array[TOP_LL(p.op)->next->type]);
		if(TOP_LL(p.op)->next->type == ASSIGN || TOP_LL(p.op)->next->type == LPARA || TOP_LL(p.op)->next->type == COMMA){
			
			_info_green("Opening push itself flag\n");

			if(TOP_LL(p.op)->next->next == NULL || TOP_LL(p.op)->next->next->type != FOR)
				set_id_flag_PUSH_ITSELF(TOP_LL(p.op));

			//this creates error when we use "for(i=smth)... end", it pushes p.iter object
		}

		p.iter_prev->next = p.iter->next;

		if(TOP_LL(p.op)->type == IDENTIFIER){
			_info("Stack top is [%x]ID<%d>\n",get_ll_identifier_flag(TOP_LL(p.op)),get_ll_identifier_loc(TOP_LL(p.op)));
			TOP_LL(p.op)->type = p.iter->type;				
		}
		else if(TOP_LL(p.op)->type == LOAD_SUBSCRIPT){
			_info("Stack top is load subscript, converting to assign\n");
			TOP_LL(p.op)->type = ASSIGN_SUBSCRIPT;
		}
		
		break;
	}
	default:{

		_warning("Undefined object type[%s] in parser\n",_ll2str(p.iter));
		assert(0);
	}
}

	p.iter = p.iter_prev->next;
	
	_print_main_list();
	_print_op_stack();
	_cprint(101,"[GM]:{%s}\n\n",_gm2str(p.gm));

	}
	//make the linked list connection proper
	p.head->tail->next = p.iter_prev;

	if(!is_empty_fbgc_ll(p.op)){
		//Check the stack and give proper error
		if(is_fbgc_FUNCTIONABLE(get_fbgc_object_type(TOP_LL(p.op)))){
			cprintf(100,"Missing <END> : <%s>\n",object_type_as_str(TOP_LL(p.op)));
			return 0;
		}

		cprintf(100,"Syntax error in line %d, Non-empty operator stack!\n",line_no);
		_print_fbgc_ll(p.op,"O");
		return 0;
	}

	_info_green("==================================\n");
	_print("Parser finished the job successfully\n");
	_println_object("Defined symbols in the parser:",fbgc_symbols);
	_print("Global field locals:"); _print_field_locals(*field_obj);
	_info_green("==================================\n\n");

	return 1;


	PARSER_ERROR_LABEL:
	fbgc_error(p.error_code,line_no);
		cprintf(100,"%s\n",line);
	return 0;

}