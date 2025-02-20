#include <iostream>

typedef struct Node{
    int val;
    Node* left;
    Node* right;
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

    Node* temp = head;
    Node* prev = nullptr;

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
    else if(val > prev->val)
        prev->right = novi;
    else return;
}

void preOrder(Node* head){
    if(head == nullptr)
        return;
    std::cout << head->val << " ";
    preOrder(head->left);
    preOrder(head->right);
}

void inOrder(Node* head){
    if(head == nullptr)
        return;
    inOrder(head->left);
    std::cout<< head->val << " ";
    inOrder(head->right);
}

void postOrder(Node* head){
    if(head == nullptr)
        return;
    postOrder(head->left);
    postOrder(head->right);
    std::cout<< head->val << " ";
}

bool nodeExists(Node* head,int val){
    if(head == nullptr)
        return false;
    if(head->val == val)
        return true;
    if(head->val > val)
        return nodeExists(head->left,val);
    else return nodeExists(head->right,val);
}

Node* minNode(Node* head){
    if(head == nullptr)
        return nullptr;
    if(head->left == nullptr)
        return head;
    else return minNode(head->left);
}

void brisi(Node*& head,int val){
    if(head==nullptr)
        return;

    else if(val < head->left)
        brisi(head->left,val);
    else if(val > head->right)
        brisi(head->right,val);
    else{
        if(head->left == nullptr && head->right == nullptr){
            delete head;
            head == nullptr;
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


int main()
{
    Node* head = nullptr;
    addNode(head,5);
    addNode(head,3);
    addNode(head,2);
    addNode(head,10);
    addNode(head,17);
    addNode(head,20);
    addNode(head,15);
    addNode(head,4);

    preOrder(head);
    std::cout<<std::endl;

    inOrder(head);
    std::cout<<std::endl;

    postOrder(head);
    std::cout<<std::endl;

    std::cout<< nodeExists(head,17)<<std::endl;
    std::cout<< minNode(head)->val <<std::endl;

    return 0;
}
