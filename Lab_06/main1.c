#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <graphics.h>
#define TRUE 1
#define FALSE 0
struct nodetype
{
int info;
struct nodetype *left,*right;
// struct nodetype *right;
};
typedef struct nodetype * NODEPTR;
NODEPTR ptree;

//Khoi tao cay
void Initialize(NODEPTR ptree)
{
ptree = NULL;
}


//Cap phat mot node cho cay
NODEPTR Newnode()
{
NODEPTR p;
p=(NODEPTR)malloc(sizeof(struct nodetype));
return (p);
}

//Kiem tra cay rong

int Empty(NODEPTR ptree)
{
return (ptree ==NULL) ? TRUE : FALSE;

}

NODEPTR Makenode(int x)
{
NODEPTR p;
p=Newnode();
p->info = x;
p->left = NULL;
p->right= NULL;
return p;
}


//Chen 1 node vao cay

void Insert_node(NODEPTR &ptree, int x)
{
if (ptree == NULL)
{
ptree=Newnode();
ptree->info = x;
ptree->left = NULL;
ptree->right= NULL;
}
else if (x == ptree->info)
{printf("Gia tri bi trung !!!");getch();}
else if (x < ptree->info)
Insert_node(ptree->left,x);
else Insert_node(ptree->right,x);

}

//Duyet cay

void NLR(NODEPTR ptree, int ind)
{
if (!Empty(ptree))
{
for (int i=1;i<= ind-4;i++) printf(" ");
if (ind > 0) printf("@----");
//ÀÄÄÄÄ");
printf("(%d)\n",ptree->info);
NLR(ptree->left,ind+4);
NLR(ptree->right,ind+4);
}
}

int con (int dis)
{
int con1 = ((1.0 * dis)/1.2);
return con1;
}



void NLR_Graph(NODEPTR ptree, int x, int y, int dis)
{
char *s;
if (!Empty(ptree))
{
circle(x,y,10);
itoa(ptree->info,s,10);
outtextxy(x-5, y-4,s);
if (ptree->left !=NULL)
line (x,y,x-con(dis), y+20);
if (ptree->right !=NULL)
line (x,y,x+con(dis), y+20);
NLR_Graph(ptree->left,x - con(dis), y + 20, con(dis));
NLR_Graph(ptree->right,x + con(dis), y + 20, con(dis));
}
}



void LNR(NODEPTR ptree)
{
if (!Empty(ptree))
{
LNR(ptree->left);
printf("%4d",ptree->info);
LNR(ptree->right);
}
}

void LRN(NODEPTR ptree)
{
if (!Empty(ptree))
{
LRN(ptree->left);
LRN(ptree->right);
printf("%4d",ptree->info);
}
}

void RNL(NODEPTR ptree)
{
if (!Empty(ptree))
{
RNL(ptree->right);
printf("%4d",ptree->info);
RNL(ptree->left);

}
}

int Hight(NODEPTR ptree)
{ int h=0;
if (ptree == NULL) h=0;
else
{
if(Hight(ptree->left) > Hight(ptree->right))
h = 1 + Hight(ptree->left);
else
h = 1 + Hight(ptree->right);
}
return h;
}

int Tleaf(NODEPTR ptree)
{ int T;
if (ptree == NULL) T = 0;
else if(ptree->left == NULL && ptree->right==NULL) T=1;
else T = Tleaf(ptree->left) + Tleaf(ptree->right);
return T;
}

int Tnode(NODEPTR ptree)
{ int T;
if (ptree==NULL) T=0;
else T=1 + Tnode(ptree->left) + Tnode(ptree->right);
return T;
}

int Max(NODEPTR ptree)
{
if (ptree ==NULL)
{ printf("Cay bi rong !!!");
exit (1);
}
else
while (ptree->right!=NULL)
ptree = ptree->right;
return ptree->info;
}

int Min(NODEPTR ptree)
{
if (ptree ==NULL)
{ printf("Cay bi rong !!!");
exit (1);
}
else
while (ptree->left!=NULL)
ptree = ptree->left;
return ptree->info;
}


NODEPTR search(NODEPTR ptree, int x)
{
NODEPTR p;
p = ptree;
while (p !=NULL)
{
if (x == p->info)
return (p);
else
if (x < p->info)
p=p->left;
else
p=p->right;
}
return (NULL);
}


//Tim node cha
NODEPTR search_father(NODEPTR ptree, int x)
{
NODEPTR p,cha,trai, phai;
p = ptree;
while (p !=NULL)
{
trai = p->left;
phai = p->right;
if (x == trai->info || x == phai->info)
return (p);
else
if (x < p->info)
p=p->left;
else
p=p->right;
}
return (NULL);
}


//Tim node the mang
void SearchStandFor(NODEPTR &r, NODEPTR &q)
{
if (r->right) SearchStandFor(r->right,q);
else
{
q->info = r->info;
q = r;
r = r->left;
}
}

void Remove_node(NODEPTR &ptree, int x)
{
NODEPTR p;
if(ptree == NULL)
printf("Node p khong co");
else
{
if (x < ptree->info) Remove_node(ptree->left,x);
else
if (x > ptree->info) Remove_node(ptree->right,x);
else
{
p = ptree;
if(p->right == NULL)
ptree = p->left;
else
if (p->left == NULL)
ptree = p->right;
else
if (ptree->left != NULL)
SearchStandFor(ptree->left,p);
else
SearchStandFor(ptree->right,p);
free(p);

}
}
}


void Del_tree(NODEPTR ptree)
{
if (ptree !=NULL)
{
Del_tree(ptree->left);
Del_tree(ptree->right);
free(ptree);
}
}

NODEPTR rotate_left(NODEPTR ptree)
{
}

NODEPTR rotate_right(NODEPTR ptree)
{
}


void main()
{
int n, i, x, menu;
NODEPTR timkiem, tm;
do
{
clrscr();
printf(" Menu");
printf("\n1.Them node cho cay");
printf("\n2.Duyet cay NLR");
printf("\n3.Duyet cay LNR");
printf("\n4.Duyet cay LRN");
printf("\n5.Chieu cao cua cay");
printf("\n6.Tong so node cua cay");
printf("\n7.Tong so node la cua cay");
printf("\n8.Tim kiem");
printf("\n9.Xoa node co gia tri x");
printf("\n10.Node max ");
printf("\n11.Node min ");
printf("\n12.So node ben trai ");
printf("\n13.So node ben phai ");
printf("\n14.Xoay trai cay");
printf("\n15.Xoay phai cay");
printf("\n16.Xoa cay");
printf("\n0.Thoat");
printf("\n\nChon menu thuc hien: ");
scanf("%d",&menu);

switch (menu)
{
case 1:{printf("Gia tri cua node:");
scanf("%d",&x);
Insert_node(ptree,x);
break;}
case 2:{printf("\nDuyet cay theo NLR :\n");
// NLR(ptree,4);
int mh=DETECT, gmode, errorcode;

initgraph(&mh, &gmode, "C:\\BORLANDC\\BGI");
errorcode = graphresult();
//printf("Gia tri man hinh: %d\n",mh);
if (errorcode != grOk)
{
printf("Graphics error: %s\n", grapherrormsg(errorcode));
printf("Press any key to halt:");
getch();
exit(1);
}
setbkcolor(GREEN);
setcolor(WHITE);

NLR_Graph(ptree, getmaxx() / 2, 10, getmaxx() / 6);
getch();
closegraph();
break;
}
case 3:{printf("\nDuyet cay theo LNR(tang dan):");
LNR(ptree);
printf("\nDuyet cay theo RNL(giam dan):");
RNL(ptree);
getch();
break;}
case 4:{printf("\nDuyet cay theo LRN :");
LRN(ptree);
getch();
break;}
case 5:{printf("\nChieu cao : %d",Hight(ptree));
getch();
break;}
case 6:{printf("\nTong so node : %d",Tnode(ptree));
getch();
break;}
case 7:{printf("\nTong so node leaf : %d",Tleaf(ptree));
getch();
break;}
case 8:{printf("\nNhap gia tri can tim : ");
scanf("%d",&x);
timkiem = search(ptree, x);
if (timkiem != NULL)
printf("Gia tri can tim: %d",timkiem->info);
else printf("Khong tim thay");
getch();
break;}
case 9:{printf("\nNhap gia tri can xoa : ");
scanf("%d",&x);
Remove_node(ptree, x);
getch();
break;}
case 10:{printf("\nMax = %d ",Max(ptree)); getch(); break;}
case 11:{printf("\nMin = %d ",Min(ptree)); getch(); break;}
case 12:{printf("\nSo node trai = %d ",Tnode(ptree->left)); getch(); break;}
case 13:{printf("\nSo node phai = %d ",Tnode(ptree->right)); getch(); break;}

case 0:break;
default : {printf("Chon menu sai!!!");getch();break;}
}
}
while (menu !=0);
}
