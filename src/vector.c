#include "fbgc.h"


void init_static_fbgc_vector(struct fbgc_vector * vector, size_t cap, size_t block_size){
	vector->content = (uint8_t*)fbgc_malloc(fbgc_round_to_closest_power_of_two(cap)*block_size);
	vector->block_size = block_size;
	vector->size = 0;
}

struct fbgc_vector * new_fbgc_vector(size_t cap, size_t block_size){
	struct fbgc_vector * vector =  (struct fbgc_vector *) fbgc_malloc(sizeof(struct fbgc_vector));
	init_static_fbgc_vector(vector,cap,block_size);
	return vector;
}

size_t capacity_fbgc_vector(const struct fbgc_vector * vector){
	return capacity_fbgc_raw_memory(vector->content,vector->block_size);
}

inline size_t size_fbgc_vector(const struct fbgc_vector * vector){
	return vector->size;
}

inline bool is_full_fbgc_vector(const struct fbgc_vector * vector){
	return vector->size == capacity_fbgc_vector(vector);
}

inline bool is_empty_fbgc_vector(const struct fbgc_vector * vector){
	return vector->size == 0;
}

inline void * front_fbgc_vector(const struct fbgc_vector * vector){
	return vector->content;
}

inline void * back_fbgc_vector(const struct fbgc_vector * vector){
	if(vector->size)
		return vector->content+(vector->size*vector->block_size-1);
	return NULL;
}

void * at_fbgc_vector(const struct fbgc_vector * vector, size_t index){
	return vector->content + (index*vector->block_size);
}

void push_back_fbgc_vector(struct fbgc_vector * vector, const void * item){
	
	//	Check the capacity, if there is enough space push back the obj
	if(is_full_fbgc_vector(vector)){
		//request change for the capacity of the vector
		vector->content = fbgc_realloc(vector->content,(capacity_fbgc_vector(vector) <<1) * vector->block_size );
	}
	memcpy(at_fbgc_vector(vector,vector->size), item, vector->block_size);
	++vector->size;
}

void pop_back_fbgc_vector(struct fbgc_vector * vector){
	assert(vector->size);
	--vector->size;
}


void * get_item_fbgc_vector(const struct fbgc_vector * vector, int index){
	index = (index < 0) * vector->size +  index;
	assert( index < vector->size && index >= 0 );
	return at_fbgc_vector(vector,index);
}

void set_item_fbgc_vector(const struct fbgc_vector * vector, int index, const void * item){
	index = (index < 0) * vector->size +  index;
	assert( index < vector->size && index >= 0 );
	memcpy(at_fbgc_vector(vector,index), item, vector->block_size);
}

void insert_fbgc_vector(struct fbgc_vector * vector,size_t index_start,  const void * item, size_t item_len){
	//Can we do it without allocation new mem ?
	if((vector->size + item_len) > capacity_fbgc_vector(vector)){
		size_t cap = fbgc_round_to_closest_power_of_two(vector->size+item_len);
		vector->content = fbgc_realloc(vector->content,cap*vector->block_size );
	}
	//So we can just shift the data from reverse!
	//How many data that we need to shift ? 

	if(vector->size < index_start) vector->size = index_start;
	//TODO
	//There should be an efficient way to copy all the data by just calling one or two memcpy
	if(vector->size > 0){
		for(size_t i = vector->size-1; i >= index_start; --i){
			uint8_t * pold = at_fbgc_vector(vector,i);
			uint8_t * pshifted = pold + (vector->block_size * item_len);
			memcpy(pshifted,pold,vector->block_size);
		}
	}
	//insert the remaining
	memcpy(at_fbgc_vector(vector,index_start),item,item_len*vector->block_size);

	vector->size += item_len;
}


void test_vector(){
	double arr[] = {3,4,5,6,7};
	struct fbgc_vector * v = new_fbgc_vector(0,sizeof(double));
	push_back_fbgc_vector(v,arr);
	push_back_fbgc_vector(v,arr+2);
	push_back_fbgc_vector(v,arr+3);
	push_back_fbgc_vector(v,arr+4);

	printf("Vector capacity %ld\n",capacity_fbgc_vector(v) );
	
	for (int i = 0; i < size_fbgc_vector(v); ++i){
		double * d = (double *) get_item_fbgc_vector(v,i);
		printf("[%d] = %g\n",i,*d);
	}

	for (int i = -1; i > -size_fbgc_vector(v); --i){
		double * d = (double *) get_item_fbgc_vector(v,i);
		printf("[%d] = %g\n",i,*d);
	}

	pop_back_fbgc_vector(v);
	pop_back_fbgc_vector(v);
	pop_back_fbgc_vector(v);
	pop_back_fbgc_vector(v);

	printf("Pop test, must contain no data\n");
	for (int i = 0; i < size_fbgc_vector(v); ++i){
		double * d = (double *) get_item_fbgc_vector(v,i);
		printf("[%d] = %g\n",i,*d);
	}


	printf("Insertion test zero size vector\n");
	insert_fbgc_vector(v,0,arr,5);

	for (int i = 0; i < size_fbgc_vector(v); ++i){
		double * d = (double *) get_item_fbgc_vector(v,i);
		printf("[%d] = %g\n",i,*d);
	}

	printf("Insertion test at index 1\n");
	double new_data[] = {8,10,13};
	insert_fbgc_vector(v,1,new_data,3);	

	for (int i = 0; i < size_fbgc_vector(v); ++i){
		double * d = (double *) get_item_fbgc_vector(v,i);
		printf("[%d] = %g\n",i,*d);
	}
}

// void fbgc_vector_swap_with_another_vector(struct fbgc_vector * vector,struct fbgc_vector * vector2 ){
// 	struct fbgc_vector temp;
// 	memcpy(&temp,vector,sizeof(struct fbgc_vector));
// 	memcpy(vector,vector2,sizeof(struct fbgc_vector));
// 	memcpy(vector2,&temp,sizeof(struct fbgc_vector));
// }