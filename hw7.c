#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matrix[50][50];
int max;
int tree[50];
int edge[50][50];
int cost[100];
int tree_connect[50][50];
int minimal_edge_count;
int minimal_db=0;
void reset();
void calculate();
void sort();


int main(){
  char filename[20];
  FILE *fPtr;
  int i,j,print_count=0;
  
  printf("Please input the file name(need .txt followed): ");
  gets(filename);
  fPtr=fopen(filename,"r");
  
  if(!fPtr)  printf("Fail!");
   
  fscanf(fPtr,"%d",&max);
  
  reset();
  
  //把matrix用二維矩陣存起來 
  for(i=0;i<max;i++)
    for(j=0;j<max;j++)
      fscanf(fPtr,"%d",&matrix[i][j]);
      
  fclose(fPtr);
  
  calculate();
  sort();
  
  printf("Minimum cost of Spanning Tree edges in ascending order:\n");
  while(print_count<minimal_edge_count){
    for(i=0;i<max;i++){
      for(j=i;j<max;j++){
      	//如果edge[]為1代表有用edge連接,若matrix=cost代表該print 
        if(edge[i][j]==1&&matrix[i][j]==cost[print_count]){
          printf("(%d,%d) = %d\n",i,j,cost[print_count]);
          print_count++;
        }
      }
    }
  }
    
  return 0;
}

void reset(){
	
  int i,j;
  
  for(i=0;i<50;i++)
    for(j=0;j<50;j++){
      matrix[i][j]=0;
	  edge[i][j]=0;
	  tree[j]=0;
	  tree_connect[i][j]=0;
	  cost[j]=0;
    }
  
  minimal_edge_count=0;
  
}

void calculate(){
	
  int index,min_connect,tree_num=1,j,sub_tree,min_connect_target,min_connect_source;
  int source_tree,target_tree;
  int i,min_val,min_val_index;
  
  for(index=0;index<max;index++){
    if(tree[index]!=0)  continue;
    min_val=min_val_index=999;
    for(i=0;i<max;i++){
      //找出每一列最小的weight,代表找出每個vertix wieght最少的那一邊 
      if(matrix[i][index]>0&&matrix[i][index]<min_val){
        min_val=matrix[i][index];
        min_val_index=i;
      }
    }
    //如果選出的兩個vertix之中有edge做連結,那就在edge[][]的相對位置設為1 
    if(edge[min_val_index][index]==0){
      edge[min_val_index][index]=1;
      edge[index][min_val_index]=1;
      //minimal_edge_count為計算總共有多少個edge 
      minimal_edge_count++;
    }
    min_connect=min_val_index;

    //tree[]用存這個vertix是第幾個tree的,tree_num則來存有幾個tree 
    if(tree[min_connect]!=0)  tree[index]=tree[min_connect];
    
    if(tree[index]==0&&tree[min_connect]==0){
      tree[index]=tree_num;
      tree[min_connect]=tree_num;
      tree_num++;
    }
  }
  //sub_tree為總數 
  sub_tree=tree_num;

  tree_num=1;

  for(tree_num=1;tree_num<=sub_tree;tree_num++){
    source_tree=1;
    target_tree=1;
    min_connect=999;
    for(index=0;index<max;index++){
      if(tree[index]!=tree_num)  continue;
      for(j=0;j<max;j++){
      	//當vertix間有edge,但這兩個vertix分別在不同的tree中,而且這兩個tree還未相連,則將這兩個tree中weight最小的兩個vertix視為連接目標 
        if(matrix[j][index]>0&&matrix[j][index]<min_connect&&tree[j]!=tree[index]&&tree_connect[tree[j]][tree[index]]!=1){
          min_connect=matrix[j][index];
          min_connect_target=j;
          min_connect_source=index;
        }
      }
    }
    //若找到的這兩個連接目標在edge[][]中尚未連上,就把他們連起來,並且用tree_connect紀錄這兩個tree已經做連結 
    if(edge[min_connect_target][min_connect_source]==0){
      edge[min_connect_target][min_connect_source]=1;
      edge[min_connect_source][min_connect_target]=1;
      tree_connect[tree[min_connect_source]][tree[min_connect_target]]=1;
      tree_connect[tree[min_connect_target]][tree[min_connect_source]]=1;
      minimal_edge_count++;
    }
  }  
}

void sort(){
  int i,j,k,l,swap,cost_index;
  cost_index=0;
  //用cost這個一唯陣列來儲存每個edge的weight 
  for(i=0;i<max;i++){
    for(j=i;j<max;j++){
      if(edge[i][j]==1){
        cost[cost_index]=matrix[i][j];
        cost_index++;
      }
    }
  }
  //把cost中的依照大小排好 
  for(k=0;k<(cost_index-1);k++){
    for(l=0;l<cost_index-k-1;l++){
      if(cost[l] > cost[l+1]){
        swap=cost[l];
        cost[l]=cost[l+1];
        cost[l+1]=swap;
      }
    }
  }
}
