#include <iostream>
#include <string.h>
using namespace std;

struct Node
{
    char name[5];
    int start;
    int duration;
    Node *nxt,*bfr;
};

struct NodeSimple
{
    char name[5];
    int start;
    int duration;
    NodeSimple *nxt;
};

void AddElementCircularList(Node *&first ,Node *&last,NodeSimple *element)
{
    Node * el = new Node;
    strcpy(el->name,element->name);
    el->start = element->start;
    el->duration = element->duration;
    el->nxt = el->bfr = el;
    if (first == NULL)
    {
        first = last = el;
    }
    else
    {
        Node *list = first;
        while(list->nxt != first)
            list = list->nxt;
        list->nxt = el;
        last = list->nxt;
        last->bfr = list;
        last->nxt = first;
        first->bfr = last;
    }
}

void AddElementSimpleList(NodeSimple *&first,char *name,int start,int duration)
{
    NodeSimple *el = new NodeSimple;
    strcpy(el->name,name);
    el->start = start;
    el->duration = duration;
    el->nxt = NULL;
    if(first == NULL)
        first = el;
    else
    {
        NodeSimple *list = first;
        while(list->nxt != NULL)
            list = list->nxt;
        list->nxt = el;
    }
}

void Show(Node *el,int current_time)
{
    Node *element = new Node;
    element = el;
    cout <<current_time<<":\t";
    if(el != NULL)
        do
        {
            if(el->start <= current_time)
                cout << el->name << "[" << el->duration << "] ";
            el = el->nxt;
        }while(element != el);
    cout<<endl<<"\t";
}

void RemoveElement(Node *el)
{
    el->bfr->nxt = el->nxt;
    el->nxt->bfr = el->bfr;
    delete el;
}
int TotalTime(NodeSimple *el)
{
    int timp_t=0;
    while(el!=NULL)
    {
        timp_t+=el->duration;
        el=el->nxt;
    }
    return timp_t;
}
int main()
{
    Node *first = new Node;
    Node *last = new Node;
    first = last = NULL;

    int T,time_passed=0,current_time = 0,total_time,nr;
    cout<<"Enter quantic time: ";
    cin>>T;
    cout<<"Enter number of processes: ";
    cin>>nr;

    NodeSimple *element = new NodeSimple;
    element = element->nxt = NULL;
    cout<<"Enter processes(In order of start time):\nName Start Duration"<<endl;
    for(int i=0;i<nr;i++)
    {
        char name[5];
        int start,duration;
        cin>>name;
        cin>>start;
        cin>>duration;
        AddElementSimpleList(element,name,start,duration);
    }
    cout<<endl;
    char aux[5];

    total_time =TotalTime(element);

    while(current_time < total_time)
    {
        if(element != NULL && element->start == current_time)
        {
            AddElementCircularList(first,last,element);
            Show(first,current_time);
            cout<<"Process "<<element->name<<" enters."<<endl;
            element = element->nxt;
        }
        if(first->duration == 0)
        {
            if(first == first->nxt)
            {
                strcpy(aux,first->name);
                first = NULL;
                Show(first,current_time);
                time_passed = 0;
                cout<<"Process "<<aux<<" was executed completely."<<endl;
            }
            else
            {
                strcpy(aux,first->name);
                RemoveElement(first);
                first = first->nxt;
                Show(first,current_time);
                time_passed = 0;
                cout<<"Process "<<aux<<" was executed completely."<<endl;
            }
        }
        if(time_passed == T)
        {
            first = first->nxt;
            Show(first,current_time);
            time_passed = 0;
            cout<<"Process "<<first->bfr->name<<" was executed for "<<T<<"ms."<<endl;
        }
        current_time++;
        time_passed++;
        first->duration--;
    }
    cout<<total_time<<":\t"<<"All processes finished."<<endl;

    return 0;
}
