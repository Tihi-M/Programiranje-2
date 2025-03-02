#include <iostream>
#include <queue>

typedef struct Node{
    int val;
    Node* left;
    Node* right;
}Node;

void dodaj(Node*& head,int val){
    Node* novi = new Node;
    novi->left = nullptr;
    novi->right = nullptr;
    novi->val = val;

    if(head == nullptr){
        head = novi;
        return;
    }

    Node* temp = head;
    Node* prev = nullptr;

    while(temp != nullptr){
        prev=temp;
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

void dodajRec(Node*& head,int val){
    if(head == nullptr){
        Node* novi = new Node;
        novi->val = val;
        novi->left = nullptr;
        novi->right = nullptr;

        head = novi;
        return;
    }

    if(val < head->val)
        dodajRec(head->left,val);
    else if (val > head->val)
        dodajRec(head->right,val);
    else return;
}

void inOrder(Node* head){
    if(head == nullptr)
        return;
    inOrder(head->left);
    std::cout<<head->val<<" ";
    inOrder(head->right);
}

void preOrder(Node* head){
    if(head == nullptr)
        return;
    std::cout<<head->val<<" ";
    preOrder(head->left);
    preOrder(head->right);
}

void postOrder(Node* head){
    if(head == nullptr)
        return;
    postOrder(head->left);
    postOrder(head->right);
    std::cout<<head->val<<" ";
}

bool postojiCvor(Node* head,int val){
    if(head == nullptr)
        return false;
    if(val < head->val)
        return postojiCvor(head->left,val);
    else if(val > head->val)
        return postojiCvor(head->right,val);
    else return true;
}

Node* minNode(Node* head){
    if(head==nullptr)
        return nullptr;
    if(head->left==nullptr)
        return head;
    else return minNode(head->left);
}

void obrisi(Node*& head,int val){
    if(head == nullptr)
        return;
    if(val < head->val)
        obrisi(head->left,val);
    else if(val > head->val)
        obrisi(head->right,val);
    else{
        Node* temp = head;
        if(head->left == nullptr && head->right == nullptr){
            head=nullptr;
            delete temp;
        }
        else if(head->left == nullptr){
            head=head->right;
            delete temp;
        }
        else if(head->right == nullptr){
            head=head->left;
            delete temp;
        }
        else{
            Node* sled = minNode(head->right);
            head->val = sled->val;
            obrisi(head->right,sled->val);
        }
    }
}

int visinaStabla(Node* head){
    if(head == nullptr)
        return 0;
    if(visinaStabla(head->left) > visinaStabla(head->right))
        return visinaStabla(head->left)+1;
    else  return visinaStabla(head->right)+1;
}

bool identicnaStabla(Node* head1,Node* head2){
    if(head1 == nullptr && head2 == nullptr)
        return true;
    if(head1->val != head2->val)
        return false;
    return identicnaStabla(head1->left,head2->left) && identicnaStabla(head1->right,head2->right);
}

void stampaNivo(Node* head,int i){
    if(head == nullptr)
        return;

    if(i == 0){
        std::cout<<head->val<<" ";
        return;
    }

    stampaNivo(head->left,i-1);
    stampaNivo(head->right,i-1);
}

void stampaNivoe(Node* head){
    int visina = visinaStabla(head);

    for(int i = 0; i < visina;i++){
        stampaNivo(head,i);
        std::cout<<std::endl;
    }
}

void stampaNivoaBfs(Node* head){
    if(head == nullptr)
        return;

    std::queue<Node*> red;
    red.push(head);

    while(!red.empty()){
        Node* tren = red.front();

        std::cout<<tren->val<<" ";
        red.pop();

        if(tren->left != nullptr)
            red.push(tren->left);

        if(tren->right != nullptr)
            red.push(tren->right);
    }
}

int brListova(Node* head){
    if(head==nullptr)
        return 0;
    if(head->left == nullptr && head->right == nullptr)
        return 1;
    return brListova(head->left) + brListova(head->right);
}

int brListovaRec(Node* head){
    if(head == nullptr)
        return 0;

    std::queue<Node*> red;
    int cnt = 0;
    red.push(head);

    while(!red.empty()){
        Node* temp = red.front();
        red.pop();

        if(temp->left == nullptr && temp->right == nullptr)
            cnt++;
        if(temp->left != nullptr)
            red.push(temp->left);
        if(temp->right != nullptr)
            red.push(temp->right);
    }
    return cnt;
}

void inorderQueue(Node* head,std::queue<int>& red){
    if(head==nullptr)
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

    int tren = red.front();
    red.pop();
    while(!red.empty()){
        if(tren > red.front())
            return false;

        tren = red.front();
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
    dodajRec(head,5);
    dodaj(head,12);
    dodaj(head,28);
    dodaj(head,38);
    dodaj(head,48);



    //std::cout<<identicnaStabla(head,head1);

    //std::cout<< postojiCvor(head,48)<<std::endl;
    //std::cout<<minNode(head)->val<<std::endl;
    //obrisi(head,38);
    //inOrder(head);
    //std::cout<<std::endl;
    //std::cout<<visinaStabla(head)<<std::endl;

    //stampaNivoaBfs(head);
    //std::cout<<std::endl;
    //stampaNivoe(head);
    //std::cout<<brListova(head)<<std::endl;
    //std::cout<<brListovaRec(head)<<std::endl;
    //std::cout<<validnoStablo(head);
    return 0;
}
