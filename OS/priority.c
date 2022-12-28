#include<stdio.h>
#include<stdbool.h>

struct process{
	int at,bt,priority,st,wt,tat,rt,ct;
}ps[100];

int main(){
	int curr_time=0,completed=0,cycle=0,idle=0;
	float atat=0,awt=0,art=0;
	bool is_completed[100]={false};
	int bt_remaining[100];
	int n;
	scanf("%d",&n);
	printf("Enter Arrival time, Burst time, Priority\n");
	for(int i=0;i<n;i++){
		scanf("%d%d%d",&ps[i].at,&ps[i].bt,&ps[i].priority);
		bt_remaining[i]=ps[i].bt;
	}
	while(completed!=n){
		int max_index=-1;
		int maximum=-1;
		for(int i=0;i<n;i++){
			if(ps[i].at<=curr_time && is_completed[i]==0){
				if(ps[i].priority>maximum){
					maximum=ps[i].priority;
					max_index=i;
				}
				if(ps[i].priority==maximum){
					if(ps[i].at < ps[max_index].at){	
						maximum=ps[i].priority;
						max_index=i;}
				}
			}
		}
		if(max_index==-1){
			curr_time++;
			idle++;
		}else
		{
			if(bt_remaining[max_index]==ps[max_index].bt){
				ps[max_index].st=curr_time;
			}
			bt_remaining[max_index]--;
			cycle++;
			curr_time++;
			if(bt_remaining[max_index]==0){
				ps[max_index].ct=curr_time;
				ps[max_index].tat=ps[max_index].ct-ps[max_index].at;
				ps[max_index].wt=ps[max_index].tat-ps[max_index].bt;
				ps[max_index].rt=ps[max_index].st-ps[max_index].at;
				atat+=ps[max_index].tat;
				awt+=ps[max_index].wt;
				art+=ps[max_index].rt;
				is_completed[max_index]=true;
				completed++;
			}
		}
	}
	printf("Process\tAt\tBt\tPT\tSt\tCt\tTAT\tWt\tRt\n");
	for(int i=0;i<n;i++){
	printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,ps[i].at,ps[i].bt,ps[i].priority,ps[i].st,ps[i].ct,ps[i].tat,ps[i].wt,ps[i].rt);
	}
	float through,cpu;
	through=n/(float)curr_time;
	cpu=((cycle-idle)/(float)cycle)*100;
	printf("%d  %d\n",n,curr_time);
	printf("Average TAT= %f\n",atat/n);
	printf("Average WT= %f\n",awt/n);
	printf("Average RT= %f\n",art/n);
	printf("Throughput = %.3f\n",through);
	printf("CPU Utilisation = %.3f\n",cpu);	
	
}