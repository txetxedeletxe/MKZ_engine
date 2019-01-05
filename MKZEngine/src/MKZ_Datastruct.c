#include "MKZ_Datastruct.h"
#include "MKZ_Definitions.h"
#include <stdlib.h>



void MKZ_DATASTRUCT_linkedList_add(MKZ_linkedList ** ll , void * object, int type_id , int obj_id){

	MKZ_linkedList * lln = (MKZ_linkedList * ) malloc(sizeof(MKZ_linkedList));
	lln->object = object;
	lln->type_id = type_id;
	lln->object_id = obj_id;
	lln->ll = *(ll);
	*(ll) = lln;
}

void MKZ_DATASTRUCT_linkedList_get(MKZ_linkedList * ll , int obj_id , void ** p , int * type_id){

	MKZ_linkedList * aux = ll;

	while (aux != 0){

		if (aux->object_id == obj_id){
			*(p) = aux->object;
			*(type_id) = aux->type_id;
			return;
		}

		aux = aux->ll;
	}

	*(p) = 0;
	*(type_id) = MKZ_GENERIC_ID_UNDEFINED;

}

void MKZ_DATASTRUCT_linkedList_remove(MKZ_linkedList ** ll , int obj_id ,void (*free_tool)(void * freend , int type_id)){

	MKZ_linkedList * aux = *(ll);

	if (aux->object_id == obj_id){

		if (free_tool != 0){
			free_tool(aux->object , aux->type_id);
		}

		*(ll) = aux->ll;
		free(aux);
		return;
	}


	MKZ_linkedList * aux_aux = aux;
	aux = aux->ll;

	while (aux != 0){

		if (aux->object_id == obj_id){

			if (free_tool != 0){
				free_tool(aux->object , aux->type_id);
			}

			aux_aux->ll = aux->ll;
			free(aux);
			return;
		}

		aux_aux = aux;
		aux = aux->ll;
	}
}

void MKZ_DATASTRUCT_free_linkedList(MKZ_linkedList * ll, void (*free_tool)(void * freend , int type_id)){

	if (ll != 0){
		MKZ_DATASTRUCT_free_linkedList(ll->ll,free_tool);
		if (free_tool != 0)
			free_tool(ll->object,ll->type_id);
		free(ll);
	}

}

void MKZ_DATASTRUCT_stack_push(MKZ_stack ** st, void * obj , int type_id){
	MKZ_DATASTRUCT_linkedList_add(st,obj,type_id,0);
}


void MKZ_DATASTRUCT_stack_pop(MKZ_stack** st, void ** obj, int * type_id){

	if (*(st) == 0){
		*(obj) = 0;
		*(type_id) = MKZ_GENERIC_ID_UNDEFINED;
	}
	else{
		*(obj) = (*(st))->object;
		*(type_id) = (*(st))->type_id;
		*(st) = (*(st))->ll;
	}
}

void MKZ_DATASTRUCT_stack_peek(MKZ_stack* st, void ** obj, int * type_id){

	if (st == 0){
		*(obj) = 0;
		*(type_id) = MKZ_GENERIC_ID_UNDEFINED;
	}
	else{
		*(obj) = st->object;
		*(type_id) = st->type_id;
	}

}
