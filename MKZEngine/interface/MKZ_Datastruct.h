#ifndef __MKZ_DATASTRUCT_IMPORTED__
#define __MKZ_DATASTRUCT_IMPORTED__

typedef struct MKZ_linkedList MKZ_linkedList;


struct MKZ_linkedList{

	void * object;
	int type_id;
	int object_id;
	MKZ_linkedList * ll;
};


typedef MKZ_linkedList MKZ_stack;

void MKZ_DATASTRUCT_linkedList_add(MKZ_linkedList ** ll , void * object, int type_id , int obj_id);
void MKZ_DATASTRUCT_linkedList_get(MKZ_linkedList * ll , int obj_id , void ** p , int * type_id);
void MKZ_DATASTRUCT_linkedList_remove(MKZ_linkedList ** ll , int obj_id,void (*free_tool)(void * freend , int type_id));
void MKZ_DATASTRUCT_free_linkedList(MKZ_linkedList * ll, void (*free_tool)(void * freend , int type_id));

void MKZ_DATASTRUCT_stack_push(MKZ_stack ** st, void * obj , int type_id);
void MKZ_DATASTRUCT_stack_pop(MKZ_stack** st, void ** obj, int * type_id);
void MKZ_DATASTRUCT_stack_peek(MKZ_stack* st, void ** obj, int * type_id);

#endif
