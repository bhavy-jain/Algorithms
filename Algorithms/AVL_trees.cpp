//AVL trees are self balancing binary trees capable of performing insertion,deletion and other such opertions in O(log(n))
#include<bits/stdc++.h>
using namespace std;
struct Node 
{
    int data,height,count;
    Node *left,*right;
};
int height(Node *root)
{
    if(root==NULL)
    return 0;
    return root->height;
}
int count(Node *root)
{
    if(root==NULL)
    return 0;
    return root->count;
}
int f(Node *root)
{
    if(root==NULL)
    return 0;
    return height(root->left)-height(root->right);
}
void inorder(Node *root)
{
    if(root==NULL)
        return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}
int k_element(Node *root,int k)
{
    if(root==NULL||k<=0)
        return -1;
    if(count(root->left)==k-1)
        return root->data;
    else if(count(root->left)>=k)
        return k_element(root->left,k);
    else
        return k_element(root->right,k-(1+count(root->left)));
}
int index(Node *root,int k)
{
    if(root==NULL)
        return -1;
    if(k==root->data)
        return count(root->left)+1;
    else if(k<root->data)
        return index(root->left,k);
    else
        return 1+count(root->left)+index(root->right,k);
}
Node* lrotate(Node *x)
{
    Node *y=x->right;
    Node *T2=y->left;
    y->left=x;
    x->right=T2;
    x->height=1+max(height(x->left),height(x->right));
    y->height=1+max(height(y->left),height(y->right));
    x->count=1+count(x->left)+count(x->right);
    y->count=1+count(y->left)+count(y->right);
    return y;
}
Node* rrotate(Node *y)
{
    Node *x=y->left;
    Node *T2=x->right;
    x->right=y;
    y->left=T2;
    y->height=1+max(height(y->left),height(y->right));
    x->height=1+max(height(x->left),height(x->right));
    y->count=1+count(y->left)+count(y->right);
    x->count=1+count(x->left)+count(x->right);
    return x;
}
Node* insert( Node* root, int data)
{
    if(root==NULL)
    {
        Node *p=new Node;
        p->data=data;
        p->left=NULL;
        p->right=NULL;
        p->height=1;
        p->count=1;
        return p;
    }
    if(root->data<data)
    root->right=insert(root->right,data);
    else if(root->data>data)
        root->left=insert(root->left,data);
    else
        return root;
    root->height=1+max(height(root->left),height(root->right));
    root->count=1+count(root->left)+count(root->right);
    int g=f(root);
    if(g>1&&data<root->left->data)
    return rrotate(root);
    else if(g<-1&&data>root->right->data)
    return lrotate(root);
    else if(g>1&&data>root->left->data)
    {
        root->left=lrotate(root->left);
        return rrotate(root);
    }
    else if(g<-1&&data<root->right->data)
    {
        root->right=rrotate(root->right);
        return lrotate(root);
    }
    return root;
}
Node* deleteroot(Node* root, int data)
{
    if(root==NULL)
    return NULL;
    if(root->data<data)
        root->right=deleteroot(root->right,data);
    else if(root->data>data)
        root->left=deleteroot(root->left,data);
    else
    {
        if(root->left==NULL&&root->right==NULL)
        return NULL;
        else if(root->left==NULL)
            return root->right;
        else if(root->right==NULL)
            return root->left;
        else
        {
            Node *p=root->right;
            while(p->left)
            p=p->left;
            root->data=p->data;
            root->right=deleteroot(root->right,root->data);
        }
    }
    root->height=1+max(height(root->left),height(root->right));
    root->count=1+count(root->left)+count(root->right);
    int g=f(root);
    if(g>1&&f(root->left)>=0)
    return rrotate(root);
    else if(g<-1&&f(root->right)<=0)
    return lrotate(root);
    else if(g>1&&f(root->left)<0)
    {
        root->left=lrotate(root->left);
        return rrotate(root);
    }
    else if(g<-1&&f(root->right)>0)
    {
        root->right=rrotate(root->right);
        return lrotate(root);
    }
    return root;
}
int main()
{
    Node* root=NULL;
    root=insert(root,5);
    root=insert(root,4);
    root=insert(root,8);
    root=insert(root,12);
    root=insert(root,18);
    root=insert(root,1);
    root=insert(root,9);
    root=deleteroot(root,5);
    root=deleteroot(root,1);
    inorder(root);
    cout<<"\n";
    cout<<k_element(root,4)<<"\n";
    cout<<index(root,12)<<"\n";
}
