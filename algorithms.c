#include "algorithms.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void array_create(struct array *self) {
  self->data = calloc(sizeof(int),5);
  self->capacity = 5;
  self->size =0;
}

void array_create_from(struct array *self, const int *other, size_t size) {
  self->data = calloc(sizeof(int),size);
  self->capacity = size;
  self->size =size;
  for(size_t i = 0; i<size ; ++i){
    self->data[i]= other[i];
  }
}

void array_destroy(struct array *self) {
  free(self->data);
  self=NULL;
}

bool array_empty(const struct array *self) {

  return(self->size ==0);
}

size_t array_size(const struct array *self) {

  return self->size;
}

bool array_equals(const struct array *self, const int *content, size_t size) {
  if(self->size !=size){
    return false ;
  }
  for(size_t i = 0;i<size; i++){
    if(self->data[i]!= content[i]){
      return false;
    }
  }
  return true;
}

void grow ( struct array *self){
  size_t capacity = self->capacity *2;
  int *data = calloc(sizeof(int), capacity);
  memcpy(data,self->data,self->size*sizeof(int));
  free(self->data);
  self->data = data;
  self->capacity= capacity;
}
void array_push_back(struct array *self, int value) {
  if(self->size +1 >=self->capacity ){
    grow (self);
  }
  self->data[self->size]= value;
  self->size =self->size +1;
  
}

void array_pop_back(struct array *self) {
  if(self->size>0){
   self->size --; 
  }
}

void decal_droite(struct array *self,size_t index){
  
  size_t taille = self->size ++;
  if(self->size  >=self->capacity ){
    grow (self);
  }
  for(size_t i =taille ;i>index; i--){
    self->data[i]= self->data[i-1];

  }
  
  
}
void array_insert(struct array *self, int value, size_t index) {
  decal_droite(self,index);
  self->data[index]= value;
  
}

void array_remove(struct array *self, size_t index) {
  if(index > self->size-1){
    return;
  } 
  
  self->size = self->size-1;

  for(size_t i =index ; i<=self->size-1; i++){
    self->data[i]= self->data[i+1];
  }
}

int array_get(const struct array *self, size_t index) {
  if(index > self->size-1){
    return 0;
  }
  return self->data[index];
}

void array_set(struct array *self, size_t index, int value) {
  if(index < self->size){
    self->data[index] =value ;
  }
}
void afficher_array (const struct array *self){
  for(size_t i =0; i<self->size;++i){
    printf("%d, ", self->data[i]);
  }
  printf("\n");
}
size_t array_search(const struct array *self, int value) {

  
  for(size_t i= 0 ; i<self->size;i++){
    if(self->data[i]==value){
      return i;
    }
  }
  return self->size;
  
}


size_t array_search_sorted(const struct array *self, int value) {
  size_t i = 0;
  if(self->data[0] > value || self->data[self->size-1] < value){
    return self->size;
  }

  while (self->data[i]<= value){
    if (self->data[i]== value){
      return i;
    }
    i++;
  }
  return self->size;


}

bool array_is_sorted(const struct array *self) {
  if(self->size ==0){
    return true;
  }
  for (size_t i=0; i< self->size-1; ++i){
    if (self->data[i]> self->data[i+1]){
      return false;
    }
  }
  return true;
}


static void array_swap (struct array *self,ptrdiff_t  k, ptrdiff_t l ){
  int temp = self->data[k];
  self->data[k] = self->data[l] ;
  self->data[l] =temp;
}

ptrdiff_t array_partition(struct array *self, ptrdiff_t i, ptrdiff_t j) {
  ptrdiff_t pivot_index = i;
  const int pivot = self->data[pivot_index];
  array_swap(self,pivot_index, j);
  ptrdiff_t l = i;
  for (ptrdiff_t k=i;k<j;++k){
    if(self->data[k]<pivot){
      array_swap(self,k,l);
      ++l;
    }
  }
  array_swap(self, l, j);
  return l;
}
static void array_quick_sort_partial(struct array *self,ptrdiff_t i, ptrdiff_t j) {
  if(i<j){
    ptrdiff_t p = array_partition(self,i,j);
    array_quick_sort_partial(self, i, p-1);
    array_quick_sort_partial(self, p+1, j);
    
  }
}
void array_quick_sort(struct array *self) {
  array_quick_sort_partial(self, 0, self->size-1);
}




void heapify(struct array *self, int n, int i)
{
  int largest = i; // Initialize largest as root
  int l = 2 * i + 1; // left = 2*i + 1
  int r = 2 * i + 2; // right = 2*i + 2

  // If left child is larger than root
  if (l < n && self->data[l] > self->data[largest])
      largest = l;

  // If right child is larger than largest so far
  if (r < n && self->data[r] > self->data[largest])
      largest = r;

  // If largest is not root
  if (largest != i) {
     array_swap(self,i,largest);

      // Recursively heapify the affected sub-tree
      heapify(self, n, largest);
  }
}
void array_heap_sort(struct array *self) {
    
  size_t n = self->size;
  // Build heap (rearrange array)
  for (int i = n / 2 - 1; i >= 0; i--)
      heapify(self, n, i);

  // One by one extract an element from heap
  for (int i = n - 1; i > 0; i--) {
      // Move current root to end
      array_swap(self,0,i);

      // call max heapify on the reduced heap
      heapify(self, i, 0);
  }
  
}


bool isHeap(const struct array *self, int i, int n)
{
  // If a leaf node
  if (i >= (n) / 2)
    return true;

  if (self->data[i] >= self->data[2 * i + 1] &&  self->data[i] >= self->data[2 * i + 2] && 
  isHeap(self, 2 * i + 2, n)&& isHeap(self, 2 * i + 1, n)){
    return true;
  }
  return false;
}
bool array_is_heap(const struct array *self) {
  return isHeap(self,0,self->size);
}

void array_heap_add(struct array *self, int value) {
  size_t i = self->size;
  array_push_back(self,value);
  while(i>0){
    size_t j = (i-1)/2;
    if(self->data[i]<self->data[j]){
      break;
    }
    array_swap(self,i,j);
    i=j;
  }

}

int array_heap_top(const struct array *self) {
  return self->data[0];
}

void array_heap_remove_top(struct array *self) {
  self->data[0] = self->data[self->size-1];
  self->size--;
  size_t i =0;
  while (i<(self->size)/2){ //self->size+1
    size_t lt = 2*i+1;
    size_t rt = 2*i+2 ;
    if(self->data[i]> self->data[lt] && self->data[i]> self->data[rt]){
      break;
    }
    size_t j = (self->data[lt]>self->data[rt]) ? lt : rt;
    array_swap(self,i,j);
    i=j;
  }
}

/*
 * list
 */

void list_create(struct list *self) {
  
  self->first=NULL;
}

void list_create_from(struct list *self, const int *other, size_t size) {
   struct list_node *node = malloc (sizeof(struct list_node));
  node->data = other[0];
  self->first= node;
  struct list_node *curr1 =  self-> first;
  //curr1 = node;
  for(size_t i = 1; i< size; ++i){
    struct list_node *node1 = malloc (sizeof(struct list_node));
    node1->data = other[i];
    curr1->next = node1;
    curr1=curr1-> next;
  } 
  curr1->next =NULL;
}

void list_destroy(struct list *self) {
  if(list_empty(self)){
    return;
  }
  struct list_node *curr = self-> first;
  struct list_node *curr1 = curr-> next;
  while(curr != NULL && curr1 !=NULL){
    free(curr);
    curr= curr1;
    curr1=curr1->next;
  }
  free(curr);
  self->first =NULL;
  //free(curr1);
}

bool list_empty(const struct list *self) {

  return (self->first ==NULL);
}

size_t list_size(const struct list *self) {
  if (self->first==NULL){
    return 0;
  }
  struct list_node *curr = self->first;
  size_t res= 0;
  while(curr !=NULL){
    res++;
    curr = curr->next;

  }
  return res;
}

bool list_equals(const struct list *self, const int *data, size_t size) {
  if(list_size(self)!=size){
    return false;
  }
  struct list_node *curr = self->first;
  size_t i = 0;
  while (curr !=NULL){
    if (curr->data != data[i]){
      return false;
    }
    curr = curr->next;
    i++;
  }
  return true;
}

void list_push_front(struct list *self, int value) {
  
  struct list_node *node = malloc(sizeof(struct list_node));
  node->data = value;
  node->next = self->first;
  self->first = node;

}

void afficher_list (struct list *self){
  struct list_node *curr = self->first;
  while (curr!= NULL){
    printf ("%d, ", curr->data);
    curr = curr->next;
  }
  printf("\n");
}
void list_pop_front(struct list *self) {
  if(self->first ==NULL){
    return;
  }
  struct list_node *curr = self->first;
  self->first= curr->next;
  free(curr);
}

void list_push_back(struct list *self, int value) {
  struct list_node *node= malloc(sizeof(struct list_node));
   
  node ->data =value;
  node->next = NULL;
  if(self->first == NULL){
    self->first = node;
    
    return;
  }
  struct list_node *curr= self->first; 
  while (curr!=NULL && curr->next !=NULL){
    curr= curr->next;
  }
  curr->next = node;

}

void list_pop_back(struct list *self) {
  if(self->first ==NULL){
    return;
  }
  if(self->first->next ==NULL){
    free(self->first);
    self->first=NULL;
    return;
  }
  struct list_node *curr= self->first;
  while (curr!=NULL && curr->next->next !=NULL){
    curr= curr->next;
  }

  free(curr->next);
  curr->next = NULL;

}


void list_insert(struct list *self, int value, size_t index) {
  
  struct list_node *curr = self->first;
  struct list_node *curr1 = curr->next;
  if(index== 0){
    list_push_front(self,value);
    return;
  }
  struct list_node *node = malloc(sizeof(struct list_node));
  node->data = value;
  node->next =NULL;
  size_t i = 1;
  while (i<index && curr->next !=NULL){
    curr= curr1;
    curr1= curr1->next;
    ++i;
  }
  if(curr1== NULL){
    curr->next = node;
  }else{
    node->next = curr1;
    curr->next = node;
  }
}


void list_remove(struct list *self, size_t index) {
   struct list_node *curr = self->first;
  struct list_node *curr1 = curr->next;
  if(self->first == NULL){
    return;
  }
  if(index ==0){
    self->first = curr1;
    free (curr);
    return;
  }
  size_t i = 1;
 
  while(i<index && curr->next != NULL){
    curr = curr1;
    curr1= curr1->next;
    ++i;

  }
  if(curr1==NULL){
    return;
  }
  curr ->next = curr1->next;
  free(curr1);
  
}

int list_get(const struct list *self, size_t index) {

  if(self->first == NULL ){
    return 0;
  }
  size_t i = 0;
 struct list_node *curr = self->first;
  while(i<index && curr != NULL){
    curr = curr->next;
    ++i;

  }
  if(curr==NULL ){
    return 0;
  }
  return curr->data;
  
}

void list_set(struct list *self, size_t index, int value) {
  if(self->first==NULL){
    return;
  }
  if(index==0){
    self->first->data=value;
    return;
  }
  struct list_node *curr = self->first ;
  size_t i = 1;
  while(curr!= NULL && i<=index ){
    curr= curr->next;
    ++i;
  }
  if(curr==NULL){
    return;
  }
  curr->data =value;
}

size_t list_search(const struct list *self, int value) {
  if(self->first==NULL){
    return 0;
  }
  struct list_node *curr = self->first ;
  size_t i =0;
  while (curr!=NULL)
  {
    if(curr->data == value){
      return i;
    }
    curr= curr->next;
    ++i;
  }
  return i;
  
}

bool list_is_sorted(const struct list *self) {
   if(self->first==NULL){
    return true;
  }
  if(self->first->next==NULL){
    return true;
  }
  struct list_node *curr = self->first ;
  struct list_node *curr1 = curr->next ;
  while(curr1!=NULL){
    if (curr->data >curr1->data)
    {
      return false;
    }
    curr = curr->next;
    curr1=curr1->next;
    
  }
  return true;
}

void list_split(struct list *self, struct list *out1, struct list *out2) {
  struct list_node *curr = self->first ;
  size_t i=0;
  while(curr!=NULL){
    if(i%2 ==0){
      list_push_front(out1,curr->data);
      curr=curr->next;
    }else{
      list_push_front(out2,curr->data);
      curr=curr->next;
    }
    ++i;
  }
  list_destroy(self);
}

void list_merge(struct list *self, struct list *in1, struct list *in2) {
  
  if(in1->first==NULL){
    self->first= in2->first;
    in2->first =NULL;
    return;
  }
  if(in2->first==NULL){
    self->first= in1->first;
    in1->first =NULL;
    return;
  }
  if(in1->first==NULL&&in2->first==NULL){
    return;
  }
  
  struct list_node *curr1 = in1->first ;
  struct list_node *curr2 = in2->first ;
  if(curr1->data<curr2->data){
    self->first = curr1;
    curr1=curr1->next;
  }else{
    self->first = curr2;
    curr2=curr2->next;
  }
  
  struct list_node *res = self->first;
  while (curr1!=NULL &&curr2 !=NULL){
    if(curr1->data<curr2->data){
      res->next = curr1;
      res=res->next;
      curr1=curr1->next;
    }else{
      res->next= curr2;
      res=res->next;
      curr2=curr2->next;
    }
  }

  if(curr1 ==NULL){
    while(curr2!=NULL){
      res->next= curr2;
      res=res->next;
      curr2=curr2->next;
    }
  }else {
    while(curr1!=NULL){
      res->next = curr1;
      res=res->next;
      curr1=curr1->next;
    }
  }
  in1->first=NULL;
  in2->first=NULL;
  


}

void list_merge_sort(struct list *self) {
  if(self->first ==NULL ||self->first->next==NULL){
    return;
  }
  struct list one;
  list_create(&one);
  struct list two;
  list_create(&two);
  list_split(self, &one, &two);
  list_merge_sort(&one);
  list_merge_sort(&two);
  list_merge(self,&one,&two);

}


/*
 * tree
 */

void tree_create(struct tree *self) {
  self->root=NULL;
}

void tree_destroy_partial (struct tree_node *node){
  if(node == NULL){
    return;
  }
  tree_destroy_partial(node->left);
  tree_destroy_partial(node->right);
  free(node);

}

void tree_destroy(struct tree *self) {

  tree_destroy_partial (self->root);  
  self->root=NULL;

}


bool tree_contains_partial (const struct tree_node *node, int value){
  if(node==NULL){
    return false;
  }
  if (value<node->data){
    return tree_contains_partial(node->left,value);
  }
  if (value>node->data){
    return tree_contains_partial(node->right,value);
  }
  return true;
}

bool tree_contains(const struct tree *self, int value) {
  return tree_contains_partial(self->root,value);
}



struct tree_node* tree_insert_partial (struct tree_node *node,int value){

  if(node ==NULL){
    struct tree_node *tree = malloc(sizeof (struct tree_node));
    tree->left=tree->right=NULL;
    tree->data = value;
    return tree;
  }

  if(value < node->data){
   node->left = tree_insert_partial(node->left,value);
   return node;
  }

  if(value > node->data){
    node->right = tree_insert_partial(node->right,value);
    return node;
  }
  return node;  

}

bool tree_insert(struct tree *self, int value) {
  if(tree_contains(self,value)){
    return false;
  }
  self->root = tree_insert_partial(self->root,value);
  return true;
}



struct tree_node* minValueNode(struct tree_node* node)
{
  struct tree_node* current = node;

  /* loop down to find the leftmost leaf */
  while (current && current->left != NULL)
    current = current->left;

  return current;
}


struct tree_node* deleteNode(struct tree_node* root, int key)
{
  // base case
  if (root == NULL)
    return root;

  
  if (key < root->data)
    root->left = deleteNode(root->left, key);

  
  else if (key > root->data)
      root->right = deleteNode(root->right, key);

  
  else {
    // node with only one child or no child
    if (root->left == NULL) {
      struct tree_node* temp = root->right;
      free(root);
      return temp;
    }
    else if (root->right == NULL) {
      struct tree_node* temp = root->left;
      free(root);
      return temp;
    }
    struct tree_node* temp = minValueNode(root->right);

    root->data = temp->data;
    root->right = deleteNode(root->right, temp->data);
  }
  return root;
}




bool tree_remove(struct tree *self, int value) {
  if(!tree_contains(self,value)){
    return false;
  }

  self->root = deleteNode(self->root,value);
  return true;
}
  

bool tree_empty(const struct tree *self) {
  return self->root==NULL;
}

size_t max (size_t a, size_t b){
  return (a<=b)? b : a;
}

size_t tree_size_partial (const struct tree_node *node){
  
  if(node== NULL){
    return 0;
  }
  
  return tree_size_partial(node->left)+1  +tree_size_partial(node->right);
}

size_t tree_size(const struct tree *self) {
  return tree_size_partial(self->root);  
  
}

size_t tree_height_partial (const struct tree_node *node){
  if(node== NULL){
    return 0;
  }
  size_t hg = tree_height_partial(node->left);
  size_t hd = tree_height_partial(node->right);
  return 1 + max(hg,hd);
}

size_t tree_height(const struct tree *self) {
  return tree_height_partial(self->root);
}


void tree_walk_pre_order_partial (const struct tree_node *node , tree_func_t func, void *user_data){
  if (node == NULL) {
    return; 
  }
     /* first print data of node */
  func (node->data,user_data);   
  
     /* then recur on left sutree */
  tree_walk_pre_order_partial(node->left,func,user_data);   
  
     /* now recur on right subtree */
  tree_walk_pre_order_partial(node->right,func,user_data);
}



void tree_walk_pre_order(const struct tree *self, tree_func_t func, void *user_data)  {
  tree_walk_pre_order_partial(self->root,func,user_data);
}

void tree_walk_in_order_partial(const struct tree_node *node, tree_func_t func, void *user_data) {

  if (node == NULL) 
    return; 

  tree_walk_in_order_partial(node->left,func,user_data);; 

  func(node->data,user_data);   

  tree_walk_in_order_partial(node->right,func,user_data); 

}
void tree_walk_in_order(const struct tree *self, tree_func_t func, void *user_data) {
  tree_walk_in_order_partial(self->root,func,user_data);
}

void tree_walk_post_order_partial(const struct tree_node *node, tree_func_t func, void *user_data) {

  if (node == NULL) 
    return; 

  // first recur on left subtree 
  tree_walk_post_order_partial(node->left,func,user_data); 

  // then recur on right subtree 
  tree_walk_post_order_partial(node->right,func,user_data); 

  // now deal with the node 
  func(node->data,user_data); 
}

void tree_walk_post_order(const struct tree *self, tree_func_t func, void *user_data) {
 tree_walk_post_order_partial(self->root,func,user_data);
}
