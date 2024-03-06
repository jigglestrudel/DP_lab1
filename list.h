typedef struct node_t node_t;

typedef struct node_t{
    node_t* prev;
    node_t* next;
    void* content;
}node_t;

typedef struct {
    node_t* head;
    node_t* tail;
    unsigned int size;
}list_t;

node_t* f_node_constructor(void* content);
void f_node_destructor(node_t* node);

// should the list require the content destructor
list_t* f_list_constructor(); 
void f_list_destructor(list_t*);



void f_list_insert(list_t* list, void* content, unsigned int index);
void f_list_insert_front(list_t* list, void* content);
void f_list_insert_back(list_t* list, void* content);
void f_list_insert_after(list_t* list, void* content, node_t* node);
void f_list_insert_before(list_t* list, void* content, node_t* node);

void f_list_remove(list_t* list, node_t* node);