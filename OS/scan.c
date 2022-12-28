#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int comparator(const void *a,const void *b){
	int x=*(int *)a;
	int y=*(int *)b;
	if(x<y){
		return -1;
	}else if(x>=y){
		return 1;
	}
}

int min(int request_queue[],int n){
	int min=INT_MAX;
	for(int i=0;i<n;i++){
		if(request_queue[i]<min){
			min=request_queue[i];
		}
	}
	return min;
}

int max(int request_queue[],int n){
	int max=INT_MIN;
	for(int i=0;i<n;i++){
		if(request_queue[i]>max){
			max=request_queue[i];
		}
	}
	return max;
}

int applyscanalgo(int total_cylinders,int request_queue[],int n,int initial_pos,int direction,int seek_seq[],int *seq_size){
	int total=0,j=0,k=0;
	int left[n+1],right[n+1];
	if(direction==0){
		if(initial_pos > min(request_queue,n)){
			right[j++]=total_cylinders-1;
		}
		right[j++]=initial_pos;
	}else if(direction==1){
		if(initial_pos < max(request_queue,n)){
			left[k++]=0;
		}
		left[k++]=initial_pos;
	}
	
	for(int i=0;i<n;i++){
		if(initial_pos < request_queue[i]){
			right[j++]=request_queue[i];
		}
		if(initial_pos > request_queue[i]){
			left[k++]=request_queue[i];
		}
	}
	
	qsort((void *)left,k,sizeof(int),comparator);
	qsort((void *)right,j,sizeof(int),comparator);
	
	int completed=2;
	while(completed--){
		if(direction==0){
			for(int i=0;i<j;i++){
				total+=abs(initial_pos - right[i]);
				initial_pos=right[i];
				seek_seq[*seq_size]=right[i];
				(*seq_size)++;
			}
			direction=1;
		}
		else if(direction==1){
			for(int i=k-1;i>=0;i--){
				total+=abs(initial_pos - left[i]);
				initial_pos=left[i];
				seek_seq[*seq_size]=left[i];
				(*seq_size)++;
			}
			direction=0;
		}
		
	}
	return total;
}

int main(){
	int total_cylinders,n,initial_pos,direction,total_head_movement=0;
	printf("Enter Total Cylinder in HDD: ");
	scanf("%d",&total_cylinders);
	printf("Enter Cylinders in Request Queue: ");
	scanf("%d",&n);
	int request_queue[n];
	int seek_seq[n+10];
	int seq_size=0;
	printf("Enter queue: ");
	for(int i=0;i<n;i++){	
		scanf("%d",&request_queue[i]);
	}
	printf("Enter initial pos: ");
	scanf("%d",&initial_pos);
	printf("Enter Direction: ");
	scanf("%d",&direction);
	if(initial_pos <0 || initial_pos>total_cylinders){
		printf("Wrong Initial Postion");
		exit(0);
	}
	total_head_movement=applyscanalgo(total_cylinders,request_queue,n,initial_pos,direction,seek_seq,&seq_size);
	printf("Total Head Movement: %d\n",total_head_movement);
	int i;
	for(i=0;i<seq_size-1;i++){
		printf(" %d -> ",seek_seq[i]);
	}
	printf(" %d ",seek_seq[i]);
	return 0;
}