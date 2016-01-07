#include <stdlib.h>
#include <stdio.h>
double factorial1(int a);
double factorial2(int a);
int main(){
int n,k;
double output1,output2;
while(1){
	printf("plaese input n: ");
	scanf ("%d",&n);
	printf("plaese input k: ");
	scanf ("%d",&k);
	while(k>n){
		printf("please re-input\n");
		printf("plaese input n: ");
		scanf ("%d",&n);
		printf("plaese input k: ");
		scanf ("%d",&k);
	}
	
	output1= factorial1(n)/ (factorial1(k)* factorial1(n-k));
	output2= factorial2(n)/ (factorial2(k)* factorial2(n-k));
	printf("the result: %.0f (recursive)\n",output1);
	printf("the result: %.0f (iterative)\n",output2);
	
	}
}

double factorial1(int a){
  if(a==0||a==1){
    return 1;
  }
  else{
    return a * factorial1(a - 1);
  }
}


double factorial2(int a){
double temp=1;
int i;

for(i=1;i<=a;i++){
  temp=temp*i;
}
return temp;
} 
 
