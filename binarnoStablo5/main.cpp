#include <iostream>
#include <math.h>
#include <queue>
typedef struct Node{
    Node* left;
    Node* right;
    int val;
}Node;

void dodaj(Node*& head, int val){
    Node* novi = new Node;
    novi->left = nullptr;
    novi->right = nullptr;
    novi->val = val;

    if(head == nullptr)
    {
        head = novi;
        return;
    }

    Node* temp = head;
    Node* prev = nullptr;

    while(temp != nullptr){
        prev = temp;
        if(val < temp->val)
            temp = temp->left;
        else
            temp = temp->right;
        //else return;
    }

    if(val < prev->val)
        prev->left = novi;
    else prev->right = novi;
}

void inOrder(Node* head){
    if(head == nullptr)
        return;
    inOrder(head->left);
    std::cout<<head->val<<" ";
    inOrder(head->right);
}

void cvoroviNaNivou(Node* head, int lvl){
    if(head == nullptr)
        return;
    if(lvl == 0){
        std::cout<< head->val << " ";
        return;
    }
    cvoroviNaNivou(head->left,lvl-1);
    cvoroviNaNivou(head->right,lvl-1);
}

int visinaStabla(Node* head){
    if(head == nullptr)
        return 0;
    if(visinaStabla(head->left) > visinaStabla(head->right))
        return 1+visinaStabla(head->left);
    else return 1+visinaStabla(head->right);
}

void stampaNivoe(Node* head){
    int visina = visinaStabla(head);

    for(int i = 0; i < visina; i++){
        cvoroviNaNivou(head,i);
        std::cout<<std::endl;
    }
}

int prebroj(Node* head){
    if(head == nullptr)
        return 0;
    if(head->left == nullptr || head->right == nullptr)
        return 0;
    if(head->val % 2 == head->left->val % 2 &&
        head->val % 2 == head->right->val % 2)
            return 1 + prebroj(head->left) + prebroj(head->right);
    else return prebroj(head->left) + prebroj(head->right);
}

int suma1(Node* head){
    if(head == nullptr)
        return 0;
    if(head->left == nullptr && head->right == nullptr)
        return 0;
    int val= 0;
    if(head->left != nullptr)
        val = head->left->val;
    if(head->right != nullptr)
        val+=head->right->val;
    if(head->val > val){
        return head->val + suma1(head->left) + suma1(head->right);
    }
    else return suma1(head->left) + suma1(head->right);
}

int suma2(Node* head,int lvl){
    if(head == nullptr)
        return 0;
    if(lvl == 0){
        if(head->val % 2 == 0)
            return head->val;
        else return -1*head->val;
    }
    else return suma2(head->left,lvl-1) + suma2(head->right,lvl-1);
}

bool simetricnoStablo(Node* leftt,Node* rightt){
    if(leftt == nullptr && rightt == nullptr)
        return true;
    if(leftt == nullptr && rightt != nullptr)
        return false;
    if(leftt != nullptr && rightt == nullptr)
        return false;
    if(leftt->val != rightt->val)
        return false;
    return simetricnoStablo(leftt->left,rightt->right) && simetricnoStablo(leftt->right,rightt->left);
}

bool balansiranoStablo(Node* head){
    if(head == nullptr)
        return true;
    if(abs(visinaStabla(head->left) - visinaStabla(head->right)) > 1)
            return false;
    else return balansiranoStablo(head->left) && balansiranoStablo(head->right);
}

void inorderQueue(Node* head,std::queue<int>& red){
    if(head== nullptr)
        return;
    inorderQueue(head->left,red);
    red.push(head->val);
    inorderQueue(head->right,red);
}

bool validnoStablo(Node* head){
    std::queue<int> red;
    inorderQueue(head,red);

    if(red.empty())
        return true;

    int temp = red.front();
    red.pop();
    while(!red.empty()){
        if(temp > red.front())
            return false;

        temp = red.front();
        red.pop();
    }
    return true;

}

int main()
{
    Node* head = nullptr;
    dodaj(head,25);
    dodaj(head,20);
    dodaj(head,36);
    dodaj(head,10);
    dodaj(head,22);
    dodaj(head,30);
    dodaj(head,40);
    dodaj(head,5);
    dodaj(head,12);
    dodaj(head,28);
    dodaj(head,38);
    dodaj(head,48);

    stampaNivoe(head);

    //inOrder(head);

    //std::cout<<prebroj(head)<<std::endl;
   // std::cout<<suma1(head);
    //std::cout<<suma2(head,2);

    //std::cout<<simetricnoStablo(head->left,head->right);
    std::cout<<validnoStablo(head);
    return 0;
}
