#include <iostream>
#include <queue>
typedef struct Node{
    int val;
    Node* left;
    Node* right;
}Node;

void dodaj(Node*& head,int val){
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
        novi->left = nullptr;
        novi->right = nullptr;
        novi->val = val;

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
    std::cout<< head->val << " ";
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

int brojCvorova(Node* head){
    if(head == nullptr)
        return 0;
    return 1 + brojCvorova(head->left) + brojCvorova(head->right);
}

int visinaStabla(Node* head){
    if(head == nullptr)
        return 0;
    if(visinaStabla(head->left) > visinaStabla(head->right))
        return visinaStabla(head->left)+1;
    else return visinaStabla(head->right)+1;
}

void inOrderQueue(Node* head,std::queue<int>& red){
    if(head == nullptr)
        return;
    inOrderQueue(head->left,red);
    red.push(head->val);
    inOrderQueue(head->right,red);
}

bool validnoStablo(Node* head){
    std::queue<int> red;
    inOrderQueue(head,red);

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

void listovi(Node* head){
    if(head == nullptr)
        return;
    if(head->left == nullptr && head->right == nullptr)
    {
        std::cout<<head->val<< " ";
        return;
    }
    listovi(head->left);
    listovi(head->right);
}

bool identicnaStabla(Node* head1,Node* head2){
    if(head1 == nullptr && head2 == nullptr)
        return true;
    if(head1 == nullptr || head2 == nullptr)
        return false;
    if(head1->val != head2->val)
        return false;
    return identicnaStabla(head1->left,head2->left) && identicnaStabla(head1->right,head2->right);
}

int brListova(Node* head){
    if(head == nullptr)
        return 0;
    if(head->left == nullptr && head->right == nullptr)
        return 1;
    else return brListova(head->left) + brListova(head->right);
}

int brListovaBfs(Node* head){
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

bool listoviNaNivou(Node* head,int lvl){
    if(head == nullptr)
        return false;
    if(lvl == 0 && head->left == nullptr && head->right == nullptr){
        std::cout << head->val <<" ";
        return true;
    }
        return listoviNaNivou(head->left,lvl-1) || listoviNaNivou(head->right,lvl-1);

}

void listoviNajmanjaDubina(Node* head){
    int visina = visinaStabla(head);

    for(int i = 0; i < visina;i++){
        if(listoviNaNivou(head,i))
            break;
    }
}

void cvoroviDvaSina(Node* head){
    if(head == nullptr)
        return;
    if(head->left != nullptr && head->right != nullptr)
    {
        std::cout<<head->val << " ";
        //cvoroviDvaSina(head->left);
        //cvoroviDvaSina(head->right);

    }
    cvoroviDvaSina(head->left);
    cvoroviDvaSina(head->right);
}

void cvorNaNivou(Node* head,int lvl){
    if(head == nullptr)
        return;
    if(lvl == 0){
        std::cout<< head->val << " ";
        return;
    }
    cvorNaNivou(head->left,lvl-1);
    cvorNaNivou(head->right,lvl-1);
}

void cvoroviNajvecaDubina(Node* head){
    int nivo = visinaStabla(head)-1;
    cvorNaNivou(head,nivo);
    std::cout<<std::endl;
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
    //dodaj(head,27);



    //std::cout<<brojCvorova(head)<<std::endl;
    //std::cout<<visinaStabla(head);

    //std::cout<<validnoStablo(head);
    //listovi(head);
    //std::cout<<std::endl;
    //std::cout<<brListova(head)<<std::endl;
    //std::cout<<brListovaBfs(head)<<std::endl;
    //listoviNajmanjaDubina(head);
    //cvoroviDvaSina(head);
    cvoroviNajvecaDubina(head);
    return 0;
}
