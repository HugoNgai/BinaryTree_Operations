#include<iostream>
#include<vector>
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
void CreateBitree(Bitree *t)								//仅仅通过前序遍历创建二叉树，'#'表示子树为空
{
	char ch;
	scanf("%c",&ch);
	//cin.get(ch);
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

//获取叶子结点数
int CountLeaves(Bitree t)
{
	static int count=0;						//定义静态变量
	if(t!=NULL)  
    {  
        count=CountLeaves(t->lchild);  
        if((t->lchild==NULL)&&(t->rchild==NULL))  
            count=count+1;  
        count=CountLeaves(t->rchild);  
    }  
    return count;  
}

//寻找某结点并保存其路径
int FindPath(Bitree t,char p,vector<Bitree> *path)
{											//path[Max]用于储存路径
	Bitnode node[Max];						//用于储存结点
	int i=0;

	(*path).push_back(t);
	node[i]=*t;								//t为指针，*t表示取该结构型指针的整个结构数据
	if (!t)
		return 0;

	while (i>=0)
	{
		while ((*path)[i]->data==p||node[i].lchild)
		{
			if ((*path)[i]->data==p)
				return 1;
			else
			{
				(*path).push_back(node[i].lchild);
				node[i+1]=*node[i].lchild;
				node[i].lchild = NULL;				//清除该结点值,下次不再重复遍历
				i++;
			}
		}

		if (node[i].rchild)
		{
			(*path).push_back(node[i].rchild);
			node[i+1]=*node[i].rchild;
			node[i].rchild = NULL;					//清除该结点值，下次不再重复遍历
			i++;
		}
		else
		{
			(*path).pop_back();
			i--;
		}
	}
	
	if (i<0)
		return NULL;
	
}	

//寻找两结点的共同祖先
Bitree ancestor(Bitree t,char p,char q)
{
	vector<Bitree> path1,path2;
	vector <Bitree> ::iterator it;
	FindPath(t,p,&path1);
	FindPath(t,q,&path2);
	int k=0;
	
	if (path1.empty() || path2.empty())
	{
		cout << "Can't find the path!";
		return NULL;
	}
		
	cout << "p's path:";
	for (it=path1.begin();it!=path1.end(); it++)
		cout << (*it)->data;

	cout << endl;
	cout << "q's path:";
	for (it = path2.begin();it!=path2.end(); it++)
		cout << (*it)->data;
	cout << endl;

	if (!(path1.empty())&&(!(path2.empty())))
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

//通过前序遍历和中序遍历序列创建二叉树(递归)
Bitree Creat(char *pre, char *in, int nNode)
{
	char ch;
	int i, lenL, lenR;

	ch = pre[0];
	Bitree Bt = (Bitree)malloc(sizeof(Bitnode));
	Bt->data = ch;
	Bt->lchild = NULL;
	Bt->rchild = NULL;

	if (nNode == 0)
		return NULL;

	for (i = 0; i < nNode&&in[i] != ch; i++);

	lenL = i;
	lenR = nNode - i - 1;

	if (lenL > 0)
		Bt->lchild = Creat(&(pre[1]), &(in[0]), lenL);
	if (lenR > 0)
		Bt->rchild = Creat(&(pre[lenL + 1]), &(in[lenL + 1]), lenR);
	return Bt;
}

int main(void)
{
	Bitree T,temp;
	char e,p,q;
	vector<char> Pre;
	vector<char> In;
	//vector<char>::iterator it;
	char pre, in;
	T = NULL;
	cout<<"Please input the preorder binary tree:"<<endl;	
	while ((pre=getchar())!='\n')
		Pre.push_back(pre);
	cout << "Then input the inorder binary tree:" << endl;
	while ((in = getchar()) != '\n')
		In.push_back(in);
	
	/*cout << "p's path:";
	for (it = Pre.begin(); it != Pre.end(); it++)
		cout << (*it);

	cout << endl;
	cout << "q's path:";
	for (it = In.begin(); it != In.end(); it++)
		cout << (*it);
	cout << endl;*/

	int nNode = Pre.size();
	/*cout << "Please input the binary tree:" << endl;
	CreateBitree(&T);*/
	T = Creat(&Pre[0], &In[0],nNode);
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
	cout << endl;
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
