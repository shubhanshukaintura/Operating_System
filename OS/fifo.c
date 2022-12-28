#include<stdio.h>
#include<stdbool.h>
#include<string.h>

struct page_table{
	int frame_no;
	bool valid;
};

bool inpagetable(struct page_table PT[],int page){
	if(PT[page].valid==1){
		return true;
	}
	return false;
}

void printframe(int frame[],int no_of_frames){
	for(int i=0;i<no_of_frames;i++){
		printf("%d  ",frame[i]);
	}
	printf("\n");
}

void updatepagetable(struct page_table PT[],int page,int frame_no,int status){
	PT[page].valid=status;
	if(status==1){
		PT[page].frame_no=frame_no;
	}
}

int main()
{
	int n,no_of_frames,current=0,page_fault=0;
	bool flag=false;
	printf("Enter number of pages: ");
	scanf("%d",&n);
	struct page_table PT[50];
	int reference_string[n];
	printf("Enter Referece String\n");
	for(int i=0;i<n;i++){
		scanf("%d",&reference_string[i]);
	}
	printf("Enter no of frames: ");
	scanf("%d",&no_of_frames);
	int frame[no_of_frames];
	memset(frame,-1,no_of_frames*sizeof(int));
	for(int i=0;i<50;i++){
		PT[i].valid=0;
	}
	printf("Frames Values at different Time\n");
	for(int i=0;i<n;i++){
		if(!(inpagetable(PT,reference_string[i]))){
			page_fault++;
			if(flag==false && current<no_of_frames){
				frame[current]=reference_string[i];
				printframe(frame,no_of_frames);
				updatepagetable(PT,reference_string[i],current,1);
				current+=1;
				if(current==no_of_frames){
					current=0;
					flag=true;
				}
			}
			else{
				updatepagetable(PT,frame[current],-1,0);
				printframe(frame,no_of_frames);
				frame[current]=reference_string[i];
				updatepagetable(PT,reference_string[i],current,1);
				current=(current+1)%no_of_frames;
			}
		}
	}
	printf("Page Fault: %d\n",page_fault);
	printf("Hit Ratio: %0.2f\n",(float)(n-page_fault)/n);
}