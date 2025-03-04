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

void inOrder(Node* head){
    if(head == nullptr)
        return;
    inOrder(head->left);
    std::cout<< head->val << " ";
    inOrder(head->right);
}

void printLevel(Node* head,int lvl){
    if(head == nullptr)
        return;
    if(lvl == 0)
    {
        std::cout<< head->val << " ";
        return;
    }
    printLevel(head->left,lvl-1);
    printLevel(head->right,lvl-1);
}

int visinaStabla(Node* head){
    if(head == nullptr)
        return 0;
    if(visinaStabla(head->left) > visinaStabla(head->right))
        return visinaStabla(head->left)+1;
    else return visinaStabla(head->right)+1;
}

void printLevels(Node* head){
    int visina = visinaStabla(head);

    for(int i = 0; i < visina;i++){
        printLevel(head,i);
        std::cout<<std::endl;
    }
}

int levelWidth(Node* head, int lvl){
    if(head == nullptr)
        return 0;
    if(lvl == 0)
        return 1;
    else return levelWidth(head->left,lvl-1) + levelWidth(head->right,lvl-1);
}

int sirinaStabla(Node* head){
    int visina = visinaStabla(head);
    int maxWidth = 0;
    for(int i = 0; i < visina;i++){
        int temp = levelWidth(head,i);
        if(temp > maxWidth)
            maxWidth = temp;
    }
    return maxWidth;
}

int sirinaStablaOpt(Node* head){
    if(head==nullptr)
        return 0;

    int maxWidth = 0;

    std::queue<Node*> red;
    red.push(head);

    while(!red.empty()){
        int lvlSize = red.size();

        maxWidth = std::max(maxWidth,lvlSize);
        while(lvlSize>0){
            Node* temp = red.front();
            red.pop();

            if(temp->left !=nullptr)
                red.push(temp->left);
            if(temp->right != nullptr)
                red.push(temp->right);
            lvlSize--;
        }
    }

    return maxWidth;

}

void krajnjiCvoroviOpt(Node* head){
    if(head==nullptr)
        return;

    std::queue<Node*> red;
    red.push(head);

    while(!red.empty()){
        int lvlSize = red.size();
        //na pocetku je lijevi na kraju desni
        std::cout << red.front()->val << " " << red.back()->val << std::endl;

        while(lvlSize>0){
            Node* temp = red.front();
            red.pop();

            if(temp->left !=nullptr)
                red.push(temp->left);
            if(temp->right != nullptr)
                red.push(temp->right);
            lvlSize--;
        }
    }
}


bool sumaNaPutanji(Node* head,int s){
    if(head==nullptr)
        return false;
    if(head->left == nullptr && head->right == nullptr && head->val == s)
        return true;
    return sumaNaPutanji(head->left,s - head->val) || sumaNaPutanji(head->right,s - head->val );
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

    printLevels(head);

    //std::cout<<sirinaStabla(head)<<std::endl;
    //std::cout<<sirinaStablaOpt(head)<<std::endl;

    //krajnjiCvoroviOpt(head);
    //std::cout<<sumaNaPutanji(head,60);

    return 0;
}
