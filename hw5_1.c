#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 100

typedef struct node * tree_pointer;
struct node {
   int data;
   tree_pointer left_child, right_child;
};

void insert(tree_pointer *node,int num);
void del(tree_pointer *ptr, int key);
void levelOrder(tree_pointer ptr);
tree_pointer modifiedSearch(tree_pointer tree,int key);
void addq(tree_pointer ptr);
tree_pointer deleteq();

int rear=-1;
int front=-1;
int count=1;
tree_pointer queue[Max];
tree_pointer rootnum;
int number=0;

int main(){
  char input[8];
  int i,data;
  tree_pointer root = NULL;
    
  do{
    scanf("%s",&input);
    if(input[0]>=48&&input[0]<=57){
      data= 0;
      for(i=0;i<strlen(input);i++) data=data*10+input[i]-48;
      insert(&root,data);
      number=number+1;
    }
  }while(input[0]!='D'&&input[0]!='E');
      
  while(1){
  	  scanf("%s",&input);
	  if(input[0]=='E') {
	   break;
      }
	  data=0;
	  for(i=0;i<strlen(input);i++) data=data*10+input[i]-48;
	  del(&root,data);
	  number=number-1;
  }
 
  levelOrder(root);
  
  system("pause");
  return 0;
}


void insert(tree_pointer *node,int num){
  tree_pointer ptr;
  tree_pointer temp = modifiedSearch(*node,num);
  
  while(count==1){
    rootnum=malloc(sizeof(*rootnum));
    rootnum->data=num;
	rootnum->left_child=rootnum->right_child=rootnum;
    count++;
  }
	
  ptr=malloc(sizeof(*ptr));
  ptr->data=num;
  ptr->left_child=ptr->right_child=rootnum;
	
  if(*node)
    if(num<temp->data)
      temp->left_child = ptr;
	else
	  temp->right_child = ptr;
	else
	  *node = ptr;
}

tree_pointer modifiedSearch(tree_pointer tree,int key){
  tree_pointer lastNode;
  if(!tree) return NULL;
  while (tree!=rootnum){
    if(key == tree->data){
      printf("Repeat num!\n");
      return NULL;
    }
    lastNode = tree;
	if(key < tree->data)
	  tree = tree->left_child;
	else tree = tree->right_child;
  }
  return lastNode;
}

void levelOrder(tree_pointer ptr){
  addq(ptr);
  while(number>0){
    ptr=deleteq();
    if(ptr){
      if(front==0){
	    printf("%d",ptr->data);
	    number=number-1;
      }
      else if(ptr==rootnum&&front!=0)
        printf(",X");
      else{
        printf(",%d",ptr->data);
        number=number-1;
      }
    
      if(ptr->left_child)
        addq(ptr->left_child);
	  if(ptr->right_child)
	    addq(ptr->right_child);
    }
    
  }  
}

void del(tree_pointer *ptr, int key){
  tree_pointer temp = *ptr, pre, next, prenext;
  int direction, found=0;
  while ((temp != NULL) && found==0){
     
    if (temp -> data == key)
      found = 1;
    else if (key > temp ->data){ 
	  pre=temp; 
	  temp=temp->right_child;
      direction=1;
	}
    else{ 
	  pre=temp; 
	  temp=temp->left_child;
      direction = 0;}
    }
    
  if(!found){
  printf("Not on the tree!\n");
  return;
  }
  
  else{
    if(temp->right_child==rootnum && temp->left_child==rootnum){
      if(temp==*ptr)
        *ptr=NULL;
      else{
	    if(direction==1)
		  pre->right_child=rootnum;
		else
		  pre->left_child=rootnum;
      }
	}
	if(temp->right_child!=rootnum && temp->left_child==rootnum){
	  if(temp==*ptr)
	    *ptr=(*ptr)->right_child;
	  else{
	    if(direction==1)
		  pre->right_child=temp->right_child;
		else
		  pre->left_child=temp->right_child;
	  }
	}
	if(temp->right_child==rootnum && temp->left_child!=rootnum){
	  if(temp==*ptr)
	    *ptr=(*ptr)->left_child;
	  else{
	    if(direction==1)
		  pre->right_child=temp->left_child;
		else
		  pre->left_child=temp->left_child;
	  }
	}
	if(temp->right_child!=rootnum && temp->left_child!=rootnum){
      next = temp->left_child;
      if(next->right_child == rootnum){ 
        next->right_child = temp->right_child;
      if (temp == *ptr)
	    *ptr = next;
      else if (direction == 1)
        pre->right_child = next;
      else pre->left_child = next;
      }
      else{ 
        while (next->right_child != rootnum){ 
	      prenext = next;
          next = next->right_child;
        }
        prenext->right_child = rootnum;
        next->left_child = temp->left_child;
        next->right_child = temp->right_child;
        if (temp == *ptr)
          *ptr = next;
        else if (direction == 1)
          pre->right_child = next;
        else pre->left_child = next;
      }
	}
  }
  free(temp);
  return;
}

void addq(tree_pointer ptr){

  queue[++rear]=ptr;
}

tree_pointer deleteq(){
  if(rear==front)  return NULL;
  else  return queue[++front];
}
