#include <stdio.h>
#include <stdlib.h>

int capacity;

typedef struct
{
    int n;
    int **adj;
} Graf;

typedef struct
{
    int head,tail;
    int size;
    int *v;
} queue;

//1
void enqueue(queue *coada,int givenkey)
{
    if(coada->size==capacity)
        return;
    else
    {
        coada->v[coada->tail]=givenkey;
        coada->size++;
        coada->tail++;
        if(coada->tail==capacity)
            coada->tail=0;
    }
}

//2
int dequeue(queue *coada)
{
    if(coada->size==0)
        return 0;
    else
    {
        int val=coada->v[coada->head];
        coada->size--;
        coada->head++;
        if(coada->head==capacity)
            coada->head=0;
        return val;
    }
}

//3
void bfs(Graf g,int s)
{
    queue coada;
    coada.head=0;
    coada.tail=0;
    coada.size=0;
    enqueue(&coada,s);
    int *vizitat;
    vizitat=(int*)calloc(g.n+1,sizeof(int));
    //int vizitat[g.n+1];
    //for(int i=0;i<=g.n;i++)
    // vizitat[i]=0;
    vizitat[s]=1;
    while(coada.size!=0)
    {
        int val=dequeue(&coada);
        printf("%d ",val);
        for(int i=1; i<=g.n; i++)
            if(vizitat[i]==0&&g.adj[val][i]==1)
            {
                enqueue(&coada,i);
                vizitat[i]=1;
            }
    }
}

int main()
{
    FILE *f=fopen("grafBFSvect.txt","r");
    if(f==NULL)
        return 0;
    Graf g;
    fscanf(f,"%d",&g.n);
    capacity=g.n;
    g.adj=(int**)calloc(g.n+1,sizeof(int*));
    for(int i=0; i<=g.n; i++)
        g.adj[i]=(int*)calloc(g.n+1,sizeof(int));
    int x,y;
    while(fscanf(f,"%d %d",&x,&y)==2)
    {
        g.adj[x][y]=1;
    }
    bfs(g,1);
    return 0;
}
