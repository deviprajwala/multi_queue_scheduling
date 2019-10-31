#include<stdio.h>

#define queue_size 5//here we are considering 3 queues each of size 5

int queue_1[queue_size];//queue with quantum 0 to 8
int queue_2[queue_size];//queue with quantum 8 to 16
int queue_3[queue_size];//queue with quantum greater than 16
int v1[5];
int v2[5];
int v3[5];

struct process
{
 char name[5];      //gives the name of the process
 int id;
 int estimated_execution_time;//estimated time taken by the process to complete its execution
 int actual_execution_time;//actual time taken by the process to complete its execution 
 int priority;// priority of the process
 float value;// this value specifies the average of estimated time and priority
 struct process *link;
};
typedef struct process *process;

process head;
process head1;
process head2;
process head3;

process get_process();
void get_pro(process head,int n);
void calculation(process head,int n);
void display_list(process head);
int insert_to_queue(char queue[queue_size],process head,int in,int greater,int less,process head_new,int v[5]);
void diplay(char queue[queue_size],int in,int out);

process get_process()
{
 process x;
 x=(process)malloc(sizeof(struct process));
 x->link=NULL;
 return x;
}


void get_pro(process head,int n)
{
 int i,t1,t2,p,id;
 char str[10];
 process temp,cur,prev;
// printf("Enter the process name and it's time\n");
 for(i=1;i<=n;i++)
 {
   temp=get_process();
   printf("Name:");
   scanf("%s",temp->name);
   printf("Id:");
   scanf("%d",&id);
   temp->id=i;
   printf("Estimated Time:");
   scanf("%d",&t1);
   temp->estimated_execution_time=t1;
   printf("Actual Time:");
   scanf("%d",&t2);
   temp->actual_execution_time=t2;
   printf("Priority:");
   scanf("%d",&p);
   temp->priority=p;
   if(head->link==NULL)
   {
      head->link=temp;
      
   }
   else
   {
     cur=head;
     prev=NULL;
     while(cur!=NULL)
     {
       prev=cur;
       cur=cur->link;
     }
     prev->link=temp;
   }
 }
}
void calculation(process head,int n)
{
  int a,b,avg;
  process cur;
  cur=head->link;
  while(cur!=NULL)
  {
   a=cur->estimated_execution_time;
   b=cur->priority;
   avg=(a+b)/2;// the average of time and priority is calulated and assigned to 'value' field
   cur->value=avg;
   cur=cur->link;
  }
}

void display_list(process head)// to display the data which has been entered
{
 int i;
 process cur;
 printf("The list of processes and thier time is\n");
 printf("\n_______________________________________________________________________\n");
 cur=head->link;
 printf("NAME    ID    ESTIMATED TIME   ACTUAL TIME   PRIORITY   VALUE\n");
 while(cur!=NULL)
 {
   printf("%s      ",cur->name);
   printf("%d      ",cur->id);
   printf("%d                 ",cur->estimated_execution_time);
   printf("%d               ",cur->actual_execution_time);
   printf("%d           ",cur->priority);
   printf("%f ",cur->value);
   printf("\n");
   cur=cur->link;
 }
 printf("\n_______________________________________________________________________\n");
}

int insert_to_queue(char queue[queue_size],process head,int in,int greater,int less,process head_new,int v[5])
{
 int x=0;
 process cur,cur_new,temp,prev_new;
 cur=head->link;
 while(cur!=NULL)
 {
   if(cur->estimated_execution_time<=greater&&cur->estimated_execution_time>less)//in the first queue the process with execution time greater than 0 less than 8 is inserted similarly greater than 8 less than 16 for queue_2 and greater than 16 for queue_3   
   {
     queue[in]=cur->id;
     in++;
     temp=get_process();//we maintain a linked list for each of the queue
     strcpy(temp->name,cur->name);
     temp->id=cur->id;
     temp->estimated_execution_time=cur->estimated_execution_time;
     temp->actual_execution_time=cur->actual_execution_time;
     temp->priority=cur->priority;
     temp->value=cur->value;
     v[x]=cur->value;
     x++;
   if(head_new->link==NULL)
   {
      head_new->link=temp;//if the head link is null
      
   }
   else
   {
     cur_new=head_new;
     prev_new=NULL;
     while(cur_new!=NULL)//finds the node which is suitable for insertion
     {
       prev_new=cur_new;
       cur_new=cur_new->link;
     }
     prev_new->link=temp;
   }
   }
   cur=cur->link;
 }
 return in-1; 
}

void diplay(char queue[queue_size],int in,int out)
{
 int c;
 c=in;
 while(c!=out)
 {
   printf("%d  ",queue[c]);
   c--;
 }
 printf("%d\n",queue[c]);
}

int execution(process head,int in,int v[5],int limit)
{
 int n,va,incremented=0;
 n=in;
 process cur;
 cur=head->link;
 int temp,i,j,key,k;
 for(i=0;i<=n;i++)
 {
  for(j=i+1;j<=n;j++)
  {
  if(v[i]>v[j]) // we arrange the values of each of the process in ascending order and they are executed in similar fashion
  {
   temp=v[i];
   v[i]=v[j];
   v[j]=temp;
  }
  }
 }
 for(i=0;i<=in;i++)
 {
  key=v[i];
  while(cur!=NULL)
  {
    if(cur->value==key)
    {
      printf("%s",cur->name);
      for(k=1;k<=cur->estimated_execution_time;k++)
      {
        printf("-");
      }
      if(cur->actual_execution_time>limit) //if the execution time is more than the actual time then we insert the process at the end of the next queue
      {
        incremented++;
        cur->actual_execution_time-=8;
        cur->estimated_execution_time-=8;
        va=(cur->actual_execution_time+cur->priority)/2;
        cur->value=va;
        if(limit==8)         
        {
          qu_excee(head2,queue_2[queue_size],v2[5],cur->actual_execution_time,cur->estimated_execution_time,cur->value,cur->name,cur->priority,cur->id);//to insert the process at the end of next queue
        }
        else if(limit==16)
        {
          qu_excee(head3,queue_3[queue_size],v3[5],cur->actual_execution_time,cur->estimated_execution_time,cur->value,cur->name,cur->priority,cur->id);//to insert the process at the end of next queue
        }
      } 
      printf(" ");
    }
   cur=cur->link;
  }
  cur=head->link;
 }
 printf("\n");
 return incremented;//the number of processes which are inserted into the next queue is returned
}

void qu_excee(process head,int queue[queue_size],int v[5],int a,int b,float c,char name,int d,int e)
{
 int i;
 process temp,cur,prev;
 temp=get_process();
     //strcpy(temp->name,name);
     temp->id=e;
     temp->estimated_execution_time=b;
     temp->actual_execution_time=a;
     temp->priority=d;
     temp->value=c;
     for(i=0;i<5;i++)
     {
      if(v[i]==0)
      {
       v[i]=cur->value;
       queue[i]=cur->id;//the process id is inserted to the queue
      }
     }
     cur=head;
     prev=NULL;
     while(cur!=NULL)
     {
       prev=cur;
       cur=cur->link;
     }
     prev->link=temp;
}
int main()
{
 int n,in_1=0,out_1=0,in_2=0,out_2=0,in_3=0,out_3=0,incremented;
 head=get_process();
 head1=get_process();
 head2=get_process();
 head3=get_process();
 printf("Enter the number of processes:\n");
 scanf("%d",&n);
 get_pro(head,n);
 calculation(head,n);
 display_list(head);
 printf("\nMULTIPLE QUEUE SHEDULING\n");
 in_1=insert_to_queue(queue_1,head,in_1,8,0,head1,v1);
 diplay(queue_1,in_1,out_1);
 printf("queue1 is completed\n");
 in_2=insert_to_queue(queue_2,head,in_2,16,8,head2,v2);
 diplay(queue_2,in_2,out_2);
 printf("queue2 is completed\n");
 in_3=insert_to_queue(queue_3,head,in_3,100,16,head3,v3);
 diplay(queue_3,in_3,out_3);
 printf("queue3 is completed\n");
 printf("\n_______________________________EXECUTION_______________________________\n");
 incremented=execution(head1,in_1,v1,8);
 in_2=incremented;
 incremented=execution(head2,in_2,v2,16);
 in_3=incremented;
 incremented=execution(head3,in_3,v3,100);
 return 0;
}

