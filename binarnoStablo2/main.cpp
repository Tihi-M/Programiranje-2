#include <iostream>

typedef struct Node{
    int val;
    Node* right;
    Node* left;
}Node;

void addNode(Node*& head,int val){
    Node* novi = new Node;
    novi->val = val;
    novi->left = nullptr;
    novi->right = nullptr;

    if(head == nullptr){
        head = novi;
        return;
    }

    Node* prev = nullptr;
    Node* temp = head;

    while(temp != nullptr){
        prev = temp;
        if(val < temp->val)
            temp = temp->left;
        else if(val > temp->val)
            temp = temp->right;
        else return;
    }

    if(val < prev->val)
        prev->left = novi;
    else prev->right = novi;
}

void preOrder(Node* head){
    if(head == nullptr)
        return;
    std::cout<< head->val << " ";
    preOrder(head->left);
    preOrder(head->right);
}

void inOrder(Node* head){
    if(head == nullptr)
        return;
    inOrder(head->left);
    std::cout<< head->val<< " ";
    inOrder(head->right);
}

void postOrder(Node* head){
    if(head == nullptr)
        return;
    postOrder(head->left);
    postOrder(head->right);
    std::cout<< head->val << " ";
}

Node* minNode(Node* head){
    if(head == nullptr)
        return nullptr;
    if(head->left == nullptr)
        return head;
    else return minNode(head->left);
}

void brisi(Node*& head,int val){
    if(head == nullptr)
        return;

    if(val < head->val)
        brisi(head->left,val);
    else if(val > head->val)
        brisi(head->right,val);
    else{
        if(head->left == nullptr && head->right == nullptr){
            delete head;
            head==nullptr;
        }
        else if(head->left == nullptr){
            Node* temp = head;
            head = head->right;
            delete temp;
        }
        else if(head->right == nullptr){
            Node* temp = head;
            head = head->left;
            delete temp;
        }
        else{
            Node* sled = minNode(head->right);
            head->val = sled->val;
            brisi(head->right,sled->val);
        }
    }
}

int brojCvorova(Node* head){
    if(head == nullptr)
        return 0;

    return 1 + brojCvorova(head->left) + brojCvorova(head->right);
}

int main()
{
    Node* head = nullptr;
    addNode(head,10);
    addNode(head,7);
    addNode(head,15);
    addNode(head,5);
    addNode(head,4);
    addNode(head,9);
    addNode(head,8);
    addNode(head,17);
    addNode(head,20);
    addNode(head,27);

    inOrder(head);
    std::cout<<std::endl;
    brisi(head,17);

    inOrder(head);
    std::cout<<std::endl;

    std::cout << brojCvorova(head) << std::endl;
    return 0;
}
