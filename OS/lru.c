#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#include<string.h>

struct process_info{
	int frame_no;
	bool valid;
	int last_access_time;
};

bool ispagepresent(struct process_info PT[],int page){
	if(PT[page].valid==1){
		return true;
	}
	return false;
}

void updatepagetable(struct process_info PT[],int page,int frame_no,int status,int access_time){
	PT[page].valid=status;
	if(status==1){
		PT[page].last_access_time=access_time;
		PT[page].frame_no=frame_no;
	}
}

void printframe(int frames[],int n){
	for(int i=0;i<n;i++){
		printf("%d  ",frames[i]);
	}
	printf("\n");
}

int searchlrupage(struct process_info PT[],int frames[],int n){
	int min=INT_MAX;
	int index;
	for(int i=0;i<n;i++){
		if(PT[frames[i]].last_access_time<min){
			min=PT[frames[i]].last_access_time;
			index=i;
		}
	}
	return index;
}

int main()
{
	int n,no_of_frames,current=0,page_fault=0;
	bool flag=false;
	printf("Enter number of process: \n");
	scanf("%d",&n);
	int reference_string[n];
	printf("Enter Reference String: \n");
	for(int i=0;i<n;i++){
		scanf("%d",&reference_string[i]);
	}
	printf("Enter number of Frames: \n");
	scanf("%d",&no_of_frames);
	int frames[no_of_frames];
	struct process_info PT[50];
	memset(frames,-1,no_of_frames*sizeof(int));
	for(int i=0;i<50;i++){
		PT[i].valid=0;
	}
	printf("Pages inside Frame at Different Time\n");
	for(int i=0;i<n;i++){
		if(!(ispagepresent(PT,reference_string[i]))){
			page_fault++;
			if(flag==false && current<no_of_frames){
				frames[current]=reference_string[i];
				printframe(frames,no_of_frames);
				updatepagetable(PT,reference_string[i],current,1,i);
				current+=1;
				if(current==no_of_frames){
					flag=true;
				}
			}else{
				int LRU_index;
				LRU_index=searchlrupage(PT,frames,no_of_frames);
				updatepagetable(PT,frames[LRU_index],-1,0,i);
				frames[LRU_index]=reference_string[i];
				printframe(frames,no_of_frames);
				updatepagetable(PT,reference_string[i],LRU_index,1,i);
			}
		}
		PT[reference_string[i]].last_access_time=i;
	}
	printf("Page Fault: %d\n",page_fault);
	printf("Hit Ratio: %0.2f\n",(float)(n-page_fault)/n);
}