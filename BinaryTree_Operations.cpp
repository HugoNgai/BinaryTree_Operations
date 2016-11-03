#include<iostream>
#include<stdio.h>
#define Max 100
using namespace std;

typedef struct Bit
{
	char data;
	struct Bit *lchild,*rchild;
}Bitnode,*Bitree;



//前序遍历 递归
void Preorder(Bitree t)
{
	if (t)
	{
		cout<<t->data;
		Preorder(t->lchild);
		Preorder(t->rchild);
	}
}

//前序遍历 非递归
void Preorder2(Bitree t)
{
	Bitree Stack[Max];
	int top=0;
	Bitnode *p = NULL;
	p=t;

	while (p||top!=0)
	{
		while (p)
		{
			cout<<p->data;
			Stack[top++]=p;
			p=p->lchild;
		}

		if (top!=0)
		{
			p=Stack[--top];
			p=p->rchild;
		}
	}
}

//中序遍历 递归
void Inorder(Bitree t)
{
	if (t)
	{
		Inorder(t->lchild);
		cout<<t->data;
		Inorder(t->rchild);
	}
}

//中序遍历 非递归
void Inorder2(Bitree t)
{
	Bitree Stack[Max];
	int top=0;
	Bitnode *p=NULL;
	p=t;

	while (p||top!=0)
	{
		while (p)
		{
			Stack[top++]=p;
			p=p->lchild;
		}
		if (top!=0)
		{
			p=Stack[--top];
			cout<<p->data;
			p=p->rchild;
		}
	}
}

//后序遍历 递归
void Postorder(Bitree t)
{
	if (t)
	{
		Postorder(t->lchild);
		Postorder(t->rchild);
		cout<<t->data;
	}
}

//后序遍历 非递归
void Postorder2(Bitree t)
{
	Bitree Stack[Max];
	int top=0;
	Bitnode *p=NULL,*q=NULL;
	p=t;

	while (p||top!=0)
	{
		while (p)
		{
			Stack[top++]=p;
			p=p->lchild;
		}
		if (top!=0)
		{
			p=Stack[top-1];
			if (p->rchild==NULL||p->rchild==q)					//p的右子树为空或已访问过
			{
				cout<<p->data;
				q=p;
				p=NULL;
				top--;
			}
			else
				p=p->rchild;
		}
	}
}

//层次遍历
void Levelorder(Bitree t)
{
	Bitree Q[Max];
	int front=0,rear=0;
	Bitree p=t;
	if (t)
		Q[rear++]=t;
	while (front!=rear)
	{
		p=Q[front++];
		cout<<p->data;

		if (p->lchild)
			Q[rear++]=p->lchild;
		if (p->rchild)
			Q[rear++]=p->rchild;
	}
}

//初始化
void CreateBitree(Bitree *t)
{
	char ch;
	scanf("%c",&ch);

	if (ch=='#')
		*t=NULL;
	else
	{
		*t=(Bitree )malloc(sizeof(Bitnode));
		if (!(*t))
			exit(-1);
		(*t)->data=ch;
		CreateBitree(&(*t)->lchild);
		CreateBitree(&(*t)->rchild);
	}
}

//销毁二叉树
void destroy(Bitree *t)
{
	if (*t)
	{
		if ((*t)->lchild)
			destroy(&(*t)->lchild);
		if ((*t)->rchild)
			destroy(&(*t)->rchild);
		free(*t);
		*t=NULL;
	}
}

//二叉树的插入
int insertChild(Bitree p,Bitree c,int LR)
{
	if (LR==0)										//插入左子树
	{
		if (!p)
		{
			c->rchild=p->lchild;					//将p的左子树作为c的右子树
			p->lchild=c;							//将c作为p的左子树
			return 1;
		}
	return 0;
	}

	if (LR==1)										//插入右子树
	{
		if (!p)
		{
			c->lchild=p->rchild;					//将p的右子树作为c的左子树
			p->rchild=c;							//将c作为p的右子树
			return 1;
		}
		return 0;
	}
}

//二叉树的删除
int DeleteChild(Bitree p,int LR)
{
	if (LR==0)										//删除左子树
	{
		if (!p)
		{
			DeleteChild(p->lchild,LR);
			return 1;
		}
		return 0;
	}

	if (LR==1)										//删除右子树
	{
		if (!p)
		{
			DeleteChild(p->rchild,LR);
			return 1;
		}
		return 0;
	}
}

//查找二叉树


Bitree Search(Bitree T,char e)						//队列查找
{
	Bitnode *p = NULL;
	Bitree Q[Max];									//定义一个队列，用于存放二叉树中结点的指针
	int front=0,rear=0;

	if (T)
	{
		Q[rear]=T;
		rear++;

		while (front!=rear)
		{
			p=Q[front];
			front++;
			if (p->data==e)
				return p;
			if (p->lchild)
			{
				Q[rear]=p->lchild;
				rear++;
			}
			if (p->rchild)
			{
				Q[rear]=p->rchild;
				rear++;
			}
			
		}
	}
	return p;
}

//返回e的左子树的值
char LeftChild(Bitree T,char e)
{
	Bitnode *p=NULL;
	if (T)
	{
		p=Search(T,e);
		if (p&&p->lchild)
			return p->lchild->data;
	}
	return 0;
}

//返回e的右子树的值
char RightChild(Bitree T,char e)
{
	Bitnode *p=NULL;
	if (T)
	{
		p=Search(T,e);
		if (p&&p->rchild)
			return p->rchild->data;
	}
	return 0;
}

//获取树深度
int Getheight(Bitree t)
{	
	if (t==NULL)
		return 0;
	int lh=Getheight(t->lchild);
	int rh=Getheight(t->rchild);

	return lh>rh?lh+1:rh+1;
}

//获取子叶数
int CountLeaves(Bitree t)
{
	if (t==NULL)
		return 0;
	int L=CountLeaves(t->lchild);
	int R=CountLeaves(t->rchild);
	if (L+R==0)
		return 1;
	else
		return L+R;
}

//寻找某结点并保存其路径
int FindPath(Bitree t,char p,Bitree path[Max])
{											//path[Max]用于储存路径
	Bitnode node[Max];						//用于储存结点
	int i=0;

	path[i]=t;
	node[i]=*t;								//t为指针，*t表示取该结构型指针的整个结构数据
	if (!t)
		return 0;

	while (i>=0)
	{
		while (path[i]->data==p||node[i].lchild)
		{
			if (path[i]->data==p)
				return 1;
			else
			{
				path[i+1]=node[i].lchild;
				node[i+1]=*node[i].lchild;
				node[i].lchild = NULL;				//清除该结点值,下次不再重复遍历
				i++;
			}
		}

		if (node[i].rchild)
		{
			path[i+1]=node[i].rchild;
			node[i+1]=*node[i].rchild;
			node[i].rchild = NULL;					//清除该结点值，下次不再重复遍历
			i++;
		}
		else
		{
			path[i] = NULL;
			i--;
		}
	}
	if (i<0)
		return NULL;
}	

//寻找两结点的共同祖先
Bitree ancestor(Bitree t,char p,char q)
{
	Bitree path1[Max],path2[Max];
	FindPath(t,p,path1);
	FindPath(t,q,path2);
	int k=0;

	if (path1&&path2)
	{
		if (path1[k]->data!=p&&path2[k]->data!=q)
		{
			while(path1[k]->data==path2[k]->data)
				k++;
			return path1[k-1];
		}
	}
	return NULL;
}

int main(void)
{
	Bitree T,temp;
	char e,p,q;
	T=NULL;
	cout<<"Please input the binary tree,# to quit:"<<endl;
	CreateBitree(&T);
	cout<<"Binary Tree's Preorder:"<<endl;
	cout<<"Recursion："<<endl;
	Preorder(T);
	cout << endl;
	cout<<"Non recursion:"<<endl;
	Preorder2(T);
	cout << endl;
	cout<<"Binary Tree's Inorder:"<<endl;
	cout<<"Recursion："<<endl;
	Inorder(T);
	cout << endl;
	cout<<"Non recursion:"<<endl;
	Inorder2(T);
	cout << endl;
	cout<<"Binary Tree's Postorder:"<<endl;
	cout<<"Recursion："<<endl;
	Postorder(T);
	cout << endl;
	cout<<"Non recursion:"<<endl;
	Postorder2(T);
	cout << endl;
	cout<<"Binary Tree's Levelorder:"<<endl;
	Levelorder(T);
	cout<<"The height of Binary Tree:";
	cout << Getheight(T) << endl;
	cout<<"The leaves of Binary Tree:";
	cout << CountLeaves(T) << endl;

	cout<<"Please input the node p and q,then I will find their nearest ancestor: ";
	cin>>p;
	cin>>q;
	temp=ancestor(T,p,q);
	cout << "Their ancestor is:" << temp->data << endl;

	cout<<"Please input the element you want to search in the Binary Tree:";
	cin>>e;
	cout<<"It's LeftChild is:"<<endl;
	cout<<LeftChild(T,e)<<endl;
	cout<<"It's RightChild is:"<<endl;
	cout<<RightChild(T,e)<<endl;
	

	destroy(&T);
}
