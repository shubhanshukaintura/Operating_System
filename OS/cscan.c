#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//98 183 37 122 14 124 65 67


int seq=0;

int comparator(const void *a,const void *b){
	int x=*(int *)a;
	int y=*(int *)b;
	if(x<y){
		return -1;
	}else{
		return 1;
	}
}

int min(int request_queue[],int n){
	int min=INT_MAX;
	for(int i=0;i<n;i++){
		if(request_queue[i] < min){
			min=request_queue[i];
		}
	}
	return min;
}

int max(int request_queue[],int n){
	int max=INT_MIN;
	for(int i=0;i<n;i++){
		if(request_queue[i] > max){
			max=request_queue[i];
		}
	}
	return max;
}

int moveright(int left[],int right[],int j,int k,int request_queue[],int initial_pos,int direction,int seek_seq[],int total_cylinders){
	int total_head=0;
	for(int i=0;i<j;i++){
		total_head+= abs(initial_pos - right[i]);
		initial_pos = right[i];
		seek_seq[seq]=right[i];
		seq++;
	}
	k ? total_head+=(total_cylinders-1):0;
	initial_pos=0;
	for(int i=0;i<k;i++){
		total_head+= abs(initial_pos - left[i]);
		initial_pos = left[i];
		seek_seq[seq]=left[i];
		seq++;
	}
	return total_head;
}

int moveleft(int left[],int right[],int j,int k,int request_queue[],int initial_pos,int direction,int seek_seq[],int total_cylinders){
	int total_head=0;
	for(int i=k-1;i>=0;i--){
		total_head+= abs(initial_pos - left[i]);
		initial_pos = left[i];
		seek_seq[seq]=left[i];
		seq++;
	}
	j ? total_head+=(total_cylinders-1):0;
	initial_pos=total_cylinders-1;
	for(int i=j-1;i>=0;i--){
		total_head+= abs(initial_pos - right[i]);
		initial_pos = right[i];
		seek_seq[seq]=right[i];
		seq++;
	}
	return total_head;
}

int applycscanalgo(int total_cylinders,int n,int initial_pos,int direction,int request_queue[],int seek_seq[]){
	int total_head_movement=0,j=0,k=0;
	int left[n+1],right[n+1];
	if((initial_pos > min(request_queue,n)) && (initial_pos < max(request_queue,n))){
		left[k++]=0;
		right[j++]=total_cylinders-1;
	}
	
	if(direction==0){
		right[j++]=initial_pos;
	}
	else if(direction==1){
		left[k++]=initial_pos;
	}
	
	for(int i=0;i<n;i++){
		if(request_queue[i] > initial_pos){
			right[j++]=request_queue[i];
		}
		else if(request_queue[i] < initial_pos){
			left[k++]=request_queue[i];
		}
	}

	qsort((void *)left,k,sizeof(int),comparator);
	qsort((void *)right,j,sizeof(int),comparator);
	
	if(direction==0){
		total_head_movement+=moveright(left,right,j,k,request_queue,initial_pos,direction,seek_seq,total_cylinders);
	}
	else if(direction==1){
		total_head_movement+=moveleft(left,right,j,k,request_queue,initial_pos,direction,seek_seq,total_cylinders);
	}
	return total_head_movement;
}

int main(){
	int total_cylinders,n,initial_pos,direction,total_head_movement=0;
	printf("Enter Total Cylinders : ");
	scanf("%d",&total_cylinders);
	printf("Enter Number of cylinders in request queue : ");
	scanf("%d",&n);
	int request_queue[n];
	int seek_seq[n+10];
	printf("Enter Request Queue : ");
	for(int i=0;i<n;i++){
		scanf("%d",&request_queue[i]);
	}
	printf("Enter initial position : ");
	scanf("%d",&initial_pos);
	if(initial_pos < 0 || initial_pos > total_cylinders-1){
		printf("Invalid Initial Position");
		exit(0);
	}
	printf("Enter Direction : ");
	scanf("%d",&direction);
	total_head_movement+=applycscanalgo(total_cylinders,n,initial_pos,direction,request_queue,seek_seq);
	printf("Total Head movement : %d\n",total_head_movement);
	printf("Seek Sequence\n");
	int i;
	for(i=0;i<seq-1;i++){
		printf(" %d ->",seek_seq[i]);
	}
	printf("%d",seek_seq[i]);
	
}