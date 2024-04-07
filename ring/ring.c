#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 10

int list[MAX],n,c;
// n is the number of processes
//c is the coordinator
// list is to say which process is alive

void display()
{
  int i;
  printf("\nProcesses-->");
  for(i=1;i<=n;i++)
    printf("\t %d",i);
  printf("\nAlive-->    ");
  for(i=1;i<=n;i++)
    printf("\t %d",list[i]);

  printf("\ncoordinator is::%d",c);
}
void ring()
{
  int msg[20],k,i;
  int choice,crash,activate,gid,flag,subcdr;
	// gid is generator id
  do
  {
      printf("\n1.Crash\n2.Activate\n3.Display\n4.Exit\nEnter You choice::");
      scanf("%d",&choice);
      switch(choice)
      {
        case 1:
          printf("\nEnter Process no. to Crash::");
          scanf("%d",&crash);
          if(list[crash])
            list[crash]=0;
          else
          {
            printf("\nProcess is already dead!!");
            break;
          }
          do
          {
            printf("\nEnter election generator id::");
            scanf("%d",&gid);
            if(gid==c)
            {
              printf("\nenter a valid generator id::");
            }
          }while(gid==crash);
          flag=0;
          k=1;
          if(crash==c)
          {
            msg[k++]=gid;
            for(i=(gid+1)%n;i!=gid;i=(i+1)%n)
            {
              if(list[i])
              {
                printf("\nmessage is sent to %d k =%d",i,k);
                msg[k++]=i;

              }
            }
            subcdr=0;
            for(i=1;i<k;i++)
            {
              printf("\nmsg::%d\n",msg[i]);
              if(subcdr<msg[i])
              {
                subcdr=msg[i];
              }
            }
            c=subcdr;
          }
          display();
          break;
        case 2:
          //activate
          printf("\nEnter Process no. to Activated::");
          scanf("%d",&activate);
          if(!list[activate])
            list[activate]=1;
            else
          {
            printf("\nProcess is alreaady alive!!");
            break;
          }				
          //
          if(activate==n)
          {
            c=n;
            break;
          }
          for(i=activate+1;i<=n;i++)
          {
            printf("\nmessage is sent from %d to %d",activate,i);
            if(list[i])
            {
              subcdr=i;
              printf("\nResponse is sent from %d to %d",i,activate);
              flag=1;
            }
          }
          if(flag==1)
          {
            c=subcdr;
          }
          else
          {
            c=activate;
          }


        display();
        break;
      case 3:
        display();
      break;
      case 4:
        break;
      }
  }while(choice!=4);

}
int main()
{
  int i,j;
  printf("\nEnter no. of process::");
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
    printf("\nEnter Process %d is Alive or not(0/1)::",i);
    scanf("%d",&list[i]);
    if(list[i])
      c=i;
  }
  display();
  printf("\nRING ALGORITHM\n");
  ring();
  return 0;
}
