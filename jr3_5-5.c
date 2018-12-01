
#include <stdlib.h>
#include <stdio.h>

typedef char elementtype;
struct node{
  elementtype element;
  struct node *next;
};
typedef struct node* list;
list initlist(){
  list l = (list)malloc(sizeof(struct node));
  l->next = NULL;
  return l;
}
void print_char_list(list l){
  while(l->next!=NULL){
    printf("%c",l->next->element);
    l=l->next;
  }
  printf("\n");
}
void insert(list l,elementtype e){
  list L = initlist();
  L->next = l->next;
  L->element = e;
  l->next = L;
}
void delete(list l){
  list L = l->next;
  l->next=l->next->next;
  free(L);
}
int main(){
  int i;
  char c,buf[128];
  list l = initlist(),p=l;
  fgets(buf,sizeof(buf),stdin);
  for(i=0;(c = buf[i])!='\n';++i){
    insert(p,c);
    p=p->next;
  }
  p=l;
  list bffirst[2]={NULL,NULL},bfend[2]={NULL,NULL};//0->前 1->後
  list nakafirst=NULL,nakaend=NULL,tmp1,tmp2;
  int flag=0;
  while(p->next!=NULL){
    char elem=p->next->element;
    if(elem=='['||elem=='('){
      flag=1;
      tmp1=p;
      tmp2=p->next;
    }else if(elem==')'||elem==']'){
      int bf=(elem==')')?0:1;
      flag=0;
      tmp1->next=p->next->next;
      if(bffirst[bf]==NULL){
        bffirst[bf]=tmp2;
      }else{
        bfend[bf]->next=tmp2;
      }
      bfend[bf]=p->next;
      p=l;
      continue;
    }else{
      if(flag==0){
        if(nakafirst==NULL){nakafirst=p->next;}
        nakaend=p->next;
      }
    }
    p=p->next;
  }
  list tugi=l;
  if(bffirst[0]!=NULL){
    l->next=bffirst[0];
    tugi=bfend[0];
    bfend[0]->next=NULL;
  }
  if(nakafirst!=NULL){
    tugi->next=nakafirst;
    tugi=nakaend;
    nakaend->next=NULL;
  }
  if(bffirst[1]!=NULL){
    tugi->next=bffirst[1];
    bfend[1]->next=NULL;
  }
  p=l;
  while(p->next!=NULL){
    char e=p->next->element;
    if(e=='['||e=='('||e==')'||e==']'){
      delete(p);
    }else{p=p->next;}
  }
  print_char_list(l);
}