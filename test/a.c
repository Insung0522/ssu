#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum flags {false, true};

typedef struct date{
	int year;
	int month;
	int day;
}date;

typedef struct food{
	int flag;
	char name[30];
	union {
		int quantity;
		char amount[20];
	}remain;
	date store;
	date expiry;
}food;

typedef struct node{
	food item;
	struct node *next;
}node_t;

node_t *file_read(node_t *pnode);
node_t *file_write(node_t *pnode);
void list_print(node_t *pnode);
void exit_prog(node_t *pnode);

void main()
{
	enum flags err_flag;

	node_t *pnode;
	
	pnode = file_read(pnode);
	list_print(pnode);
	pnode = file_write(pnode);
	exit_prog(pnode);

}

node_t *file_read(node_t *pnode){
	FILE *fp = fopen("food.dat", "r");
	node_t *next_head = NULL;

	if(fp == NULL){
		printf("Failed to open file for read\n");
		return pnode;
	}
	
	while(!feof(fp)){
		pnode = (node_t*)malloc(sizeof(node_t));
	
		fscanf(fp,"%d", &pnode->item.flag);
		if(pnode->item.flag == false)//quantity
			fscanf(fp," name:%s remain:%d store:%d.%d.%d expiry:%d.%d.%d\n",
				pnode->item.name, &pnode->item.remain.quantity, 
				&pnode->item.store.year, &pnode->item.store.month, &pnode->item.store.day, 
				&pnode->item.expiry.year, &pnode->item.expiry.month, &pnode->item.expiry.day);
		else//amount
			fscanf(fp," name:%s remain:%s store:%d.%d.%d expiry:%d.%d.%d\n",
				pnode->item.name, pnode->item.remain.amount, 
				&pnode->item.store.year, &pnode->item.store.month, &pnode->item.store.day, 
				&pnode->item.expiry.year, &pnode->item.expiry.month, &pnode->item.expiry.day);
		
		pnode->next = next_head;
		next_head = pnode;
	}
	fclose(fp);
	return pnode;
}

node_t *file_write(node_t *pnode){
	FILE *fp = fopen("food.dat", "w");
	node_t *last_head;

	if(fp == NULL){
		printf("Failed to open file for write\n");
		return pnode;
	}
	last_head = pnode;//노드의 마지막 주소를 기억

	while(pnode != NULL){
		if(pnode->item.flag == false)//quantity
			fprintf(fp,"%d name:%s remain:%d store:%d.%d.%d expiry:%d.%d.%d\n",
				pnode->item.flag, pnode->item.name, pnode->item.remain.quantity, 
				pnode->item.store.year, pnode->item.store.month, pnode->item.store.day, 
				pnode->item.expiry.year, pnode->item.expiry.month, pnode->item.expiry.day);
		else//amount
			fprintf(fp,"%d name:%s remain:%s store:%d.%d.%d expiry:%d.%d.%d\n",
				pnode->item.flag, pnode->item.name, pnode->item.remain.amount, 
				pnode->item.store.year, pnode->item.store.month, pnode->item.store.day, 
				pnode->item.expiry.year, pnode->item.expiry.month, pnode->item.expiry.day);

		pnode = pnode->next;
	}
	pnode = last_head;
	
	fclose(fp);
	return pnode;
}

void list_print(node_t *pnode){
	node_t *last_head;
	last_head = pnode;

	while(pnode != NULL){
		printf(" name:%s remain:%s store:%d.%d.%d expiry:%d.%d.%d\n",
			pnode->item.name, pnode->item.remain.amount, 
			pnode->item.store.year, pnode->item.store.month, pnode->item.store.day, 
			pnode->item.expiry.year, pnode->item.expiry.month, pnode->item.expiry.day);
		pnode = pnode->next;
	}

	pnode = last_head;
}

void exit_prog(node_t *pnode){
	node_t *tmp;
	while(pnode != NULL){
		tmp = pnode;
		pnode = pnode->next;
		free(tmp);
	}
}
