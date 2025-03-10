#include<stdio.h>
int n,q[10],front=-1,rear=-1;
struct proc
{
    int no,at,bt,ct,tat,wt,rt,completed;
};
void enqueue(int i)
{
    if(rear==10)
        printf("Overflow");
    rear++;
    q[rear]=i;
    if(front==-1)
        front=0;
}
int dequeue()
{
    if(front==-1)
        printf("Underflow");
    int temp=q[front];
    if(front==rear)
        front=rear=-1;
    else
        front++;
    return temp;
}
int isInQueue(int i)
{
    int k;
    for(k=front;k<=rear;k++)
    {
        if(q[k]==i)
            return 1;
    }
    return 0;
}
struct proc read(int i)
{
    struct proc p;
    printf("\nProcess No: %d\n",i);
    p.no=i;
    printf("Enter Arrival Time: ");
    scanf("%d",&p.at);
    printf("Enter Burst Time: ");
    scanf("%d",&p.bt);
    p.rt=p.bt;
    p.completed=0;
    return p;
}
void main()
{
    int i,j,tq,time=0,remaining;
    float avgtat=0,avgwt=0;
    struct proc p[10],temp;
    printf("<--Round Robin Scheduling Algorithm-->\n");
    printf("Enter Number of Processes: ");
    scanf("%d",&n);
    printf("Enter Time Quantum: ");
    scanf("%d",&tq);
    for(int i=0;i<n;i++)
        p[i]=read(i+1);
    for(int i=0;i<n-1;i++)
        for(j=0;j<n-i-1;j++)    
            if(p[j].at>p[j+1].at)
            {
            temp=p[j];
            p[j]=p[j+1];
            p[j+1]=temp;
            }
    remaining=n;
    enqueue(0);
    printf("\nQueue: ");
    for(time=p[0].at;remaining!=0;)
    {   
        i=dequeue();
        if(p[i].rt<=tq)
        {
            time+=p[i].rt;
            p[i].rt=0;
            p[i].completed=1;
            remaining--;
            printf("-> P%d",p[i].no);
            p[i].ct=time;
            p[i].tat=p[i].ct-p[i].at;
            avgtat+=p[i].tat;
            p[i].wt=p[i].tat-p[i].bt;
            avgwt+=p[i].wt;
            for(j=0;j<n;j++)
                if(p[j].at<=time && p[j].completed!=1&& isInQueue(j)!=1)
                    enqueue(j);
        }
        else
        {
            time+=tq;
            p[i].rt-=tq;
            printf("-> P%d",p[i].no);
            for(j=0;j<n;j++)
                if(p[j].at<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
                    enqueue(j);
            enqueue(i);
        }
    }
    printf("\n\nProcess\t\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++)
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n",p[i].no,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    avgtat/=n,avgwt/=n;
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f",avgtat,avgwt);
}

_______________________________________________________________________________________________________________________
OUTPUT:

<--Round Robin Scheduling Algorithm-->
Enter Number of Processes: 5
Enter Time Quantum: 3

Process No: 1
Enter Arrival Time: 0
Enter Burst Time: 8

Process No: 2
Enter Arrival Time: 5
Enter Burst Time: 2

Process No: 3
Enter Arrival Time: 1
Enter Burst Time: 7

Process No: 4
Enter Arrival Time: 6
Enter Burst Time: 3

Process No: 5
Enter Arrival Time: 8
Enter Burst Time: 5

Queue: -> P1-> P3-> P1-> P2-> P4-> P3-> P5-> P1-> P3-> P5

Process         AT      BT      CT      TAT     WT
P1              0       8       22      22      14
P3              1       7       23      22      15
P2              5       2       11      6       4
P4              6       3       14      8       5
P5              8       5       25      17      12

Average TurnAroundTime=15.000000
Average WaitingTime=10.000000
