#include<stdio.h>
#include<stdbool.h>

struct process_info{
	int max[10];
	int allocated[10];
	int need[10];
};

int no_of_process,no_of_resources;

void input(struct process_info process[no_of_process],int available[no_of_resources]){
	for(int i=0;i<no_of_process;i++){
		printf("Enter Max Need P[%d]\n",i);
		for(int j=0;j<no_of_resources;j++){
			scanf("%d",&process[i].max[j]);
		}
		printf("Enter Allocated P[%d]\n",i);
		for(int j=0;j<no_of_resources;j++){
			scanf("%d",&process[i].allocated[j]);
			process[i].need[j]=process[i].max[j]-process[i].allocated[j];
		}
	}
	printf("Enter Total Resources\n");
	for(int j=0;j<no_of_resources;j++){
		scanf("%d",&available[j]);
	}
}

void showinfo(struct process_info process[no_of_process]){
	printf("Process\tMaximum\tAllocated\tNeed\n");
	for(int i=0;i<no_of_process;i++){
		printf("P%d\t",i);
		for(int j=0;j<no_of_resources;j++){
			printf("%d ",process[i].max[j]);
		}
		printf("\t");
		for(int j=0;j<no_of_resources;j++){
			printf("%d ",process[i].allocated[j]);
		}
		printf("\t");
		for(int j=0;j<no_of_resources;j++){
			printf("%d ",process[i].need[j]);
		}
		printf("\n");
	}
}

bool applysafesequence(struct process_info process[no_of_process],int available[no_of_resources],int safesequence[no_of_process]){
	int work[no_of_resources];
	bool completed[no_of_process];
	for(int i=0;i<no_of_resources;i++){
		work[i]=available[i];
	}
	for(int i=0;i<no_of_process;i++){
		completed[i]=false;
	}
	bool proceed=true;
	int k=0;
	while(proceed){
		proceed=false;
		for(int i=0;i<no_of_process;i++){
			bool flag=true;
			if(completed[i]==false){
				for(int j=0;j<no_of_resources;j++){
					if(work[j]>=process[i].need[j]){
						continue;
					}else{
						flag=false;
						break;
					}
				}
				if(flag==false){
					continue;
				}	
				for(int j=0;j<no_of_resources;j++){
					work[j]=work[j]+process[i].allocated[j];
				}
				completed[i]=true;
				safesequence[k++]=i;
				proceed=true;
			}
		}
	}
	int i;
	for(i=0;i<no_of_process&&completed[i]==true;i++){
		continue;
	}
	if(i==no_of_process){
		return true;
	}else{
		return false;
	}
}

bool issafestate(struct process_info process[no_of_process],int available[no_of_resources],int safesequence[no_of_process]){
	if(applysafesequence(process,available,safesequence)==true){
		return true;
	}
	return false;
}

int main()
{
	printf("Enter no of process\n");
	scanf("%d",&no_of_process);
	printf("Enter no of Resources\n");
	scanf("%d",&no_of_resources);
	int available[no_of_resources];
	int safesequence[no_of_process];
	struct process_info process[no_of_process];
	input(process,available);
	showinfo(process);
	if(issafestate(process,available,safesequence)){
		printf("System is in Safe State\n");
		printf("Safe Sequence Is: ");
		for(int i=0;i<no_of_process;i++){
			printf("%d ",safesequence[i]);
	}
	}else{
		printf("System is NOT in Safe State\n");
	}
	
}