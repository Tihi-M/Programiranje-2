#include <iostream>

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
        else if (val > temp->val)
            temp = temp->right;
        else return;
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

    //inOrder(head);
    stampaNivoe(head);
    //std::cout<<prebroj(head)<<std::endl;
    std::cout<<suma1(head);
    return 0;
}
