//12 May 2021 - Mark Zhang - Binary Search Tree - Creates a binary search tree from an array of integers taken from a file or manual entry by user
//user can create a tree, modify the tree by adding and deleting nodes, search the tree for an integer, and print the tree

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

//each node in a binary tree can be connected to up to 2 other nodes, represented in this node struct

struct node{
    int data;
    node* left = NULL;
    node* right = NULL;
};

//function declarations

void addToTree(node* root, node* newNode);
void printTree(node* root, int spacing);
bool searchTree(node* root, int a);
node* del(node* root, int a);

int main(){
    int* array = new int[100];
    bool inputRegistered = false;
    for(int i = 0; i < 100; i++){
        array[i] = 0;
    }
    while(inputRegistered == false){ //takes initial input from file or user input
        cout << "Welcome to binary search tree: enter [file] for file input or [console] for manual input, or [quit] the program" << endl;
        char* input = new char[10];
        cin.getline(input, 10);
        if(strcmp(input, "file") == 0){
            cout << "please enter file name" << endl;
            string fileName;
            cin >> fileName;
            fstream file;
            int temp = 0;;
            int index = 0;
            file.open(fileName, ios::in);
            while(file >> temp){
                array[index] = temp;
                index++;
            }
            inputRegistered = true;
        }
        else if(strcmp(input, "console") == 0){
            char* temp = new char[500];
            cout << "enter integers separated with spaces" << endl;
            cin.getline(temp, 500);
            char* token = strtok(temp, " ");
            int index = 0;
            while(token != NULL){
                array[index] = atoi(token);
                token = strtok(NULL, " ");
                index++;
            }
            inputRegistered = true;
        }
        else if(strcmp(input, "quit") == 0){
            exit(0);
        }
        else{
            cout << "command not recognized" << endl;
        }
    }
    node* root = new node;
    root->data = array[0];
    int i = 1;
    while(array[i] != 0){
        node* temp = new node;
        temp->data = array[i];
        addToTree(root, temp);
        i++;
    }
    cout << "tree created from input\n " << endl;
    cin.clear();
    cin.ignore(9999, '\n');

    while(1){ //contains the interface that lets the user modify and print the tree by calling functions
        cout << "enter a command to modify the tree: [add], [delete], [search]; display the tree: [print]; or [quit] the program" << endl;
        char* input = new char[10];
        cin.clear();
        cin.getline(input, 10);
        if(strcmp(input, "quit") == 0){
            cout << "quitting..." << endl;
            break;
        }
        if(strcmp(input, "add") == 0){
            int newNumber = 0;
            cout << "enter integer value you would like to add" << endl;
            cin.clear();
            cin >> newNumber;
            cin.ignore(9999, '\n');
            node* temp = new node();
            temp->data = newNumber;
            addToTree(root, temp);
            cout << newNumber << " added to the tree\n" << endl;
        }
        else if(strcmp(input, "delete") == 0){
            int n = 0;
            cout << "enter integer value you would like delete" << endl;
            cin.clear();
            cin >> n;
            cin.ignore(9999, '\n');
            root = del(root, n);
        }
        else if(strcmp(input, "search") == 0){
            int n = 0;
            cout << "enter integer value you would like to search for" << endl;
            cin.clear();
            cin >> n;
            cin.ignore(9999, '\n');
            if(searchTree(root, n)){
                cout << n << " is in the tree\n" << endl;
            }
            else{
                cout << n << " was not found in the tree" << endl;
            }
        }
        else if(strcmp(input, "print") == 0){
            cout << "\nPRINTOUT OF BINARY TREE -- NOTE: root is the leftmost value, top is right, bottom is left\n" << endl;
            printTree(root, 0);
            cout << '\n'<< endl;
        }
        else{
            cout << "command not recognized" << endl;
        }
    }
    return 0;
}

//function adds a node to the tree
void addToTree(node* root, node* n){ 
    node* traverse = new node;
    traverse = root;
    while(1){ //traverses the tree until it reaches the end of the appropriate branch and adds the new node
        if(n->data >= traverse->data){
            if(traverse->right == NULL){
                traverse->right = n;
                return;
            }
            else{
                traverse = traverse->right;
            }
        }
        else if(n->data < traverse->data){
            if(traverse->left == NULL){
                traverse->left = n;
                return;
            }
            else{
                traverse = traverse->left;
            }
        }
    }
}

//recursively prints the tree
void printTree(node* root, int spacing){
    if(root == NULL){
        return;
    }
    spacing += 7;
    printTree(root->right, spacing);
    cout << endl;
    for(int i = 7; i < spacing; i++){
        cout << " ";
    }
    cout << root->data << '\n';
    printTree(root->left, spacing);
}

//searches the tree to see if a value exists in the tree by traversing it based on the value being searched for
//if the end of a branch is reached and the value is still not found, it can
//be concluded that the value is not in the tree 
bool searchTree(node* root, int a){
    node* traverse = new node;
    traverse = root;
    while(1){
        if(a > traverse->data){
            if(traverse->right == NULL){
                return false;
            }
            traverse = traverse->right;
        }
        else if(a < traverse->data){
            if(traverse->left == NULL){
                return false;
            }
            traverse = traverse->left;
        }
        else if(traverse->data == a){
            return true;
        }
    }
}

//function that deletes the first node with the given integer value
node* del(node* root, int a){
    node* traverse = new node;
    node* prev = traverse;
    bool isLeftofPrev = false;
    //the function first searches the tree to confirm that the value exists
    if(searchTree(root, a) != true){
        cout << a << " was not found in the tree and therefore cannot be deleted" << endl; 
        return root;
    }
    //the function must account for a number of cases
    //the first case is that the node the user is trying to delete is the root
    //in this case, make the node to the right of root the new root and add the node to the left of root
    //if root has no right child, make its left child the new node
    if(root->data == a){
        node* newRoot = new node;
        if(root->right != NULL){
            newRoot = root->right;
            addToTree(newRoot, root->left);
        }
        else if(root->left != NULL){
            newRoot = root->left;
        }
        delete root;
        return newRoot;
    }
    traverse = root;
    //if root is not the node to be deleted, traverse the tree until the node with the given value is found
    while(traverse->data != a){
        if(a > traverse->data){
            prev = traverse;
            isLeftofPrev = false;
            traverse = traverse->right;
        }
        else if(a < traverse->data){
            prev = traverse;
            isLeftofPrev = true;
            traverse = traverse->left;
        }
    }
    //Another case: the node to be deleted is not the root and has 2 children
    //in this case, delete the node and add its children back into the table
    if(traverse->left != NULL && traverse->right != NULL){
        if(isLeftofPrev == true){
            prev->left = NULL;
        }
        else{
            prev->right = NULL;
        }
        node* left = traverse->left;
        node* right = traverse->right;
        delete traverse;
        addToTree(root, left);
        addToTree(root, right);
        cout << "deleted node had 2 children" << endl;
    }
    //2 cases for a node that has 1 child since it could either be the left or right child
    //if the node to be deleted has only a single child, put that child in its place and delete the node
    else if(traverse->left != NULL && traverse->right == NULL){
        if(isLeftofPrev == true){
            prev->left = traverse->left;
        }
        else{
            prev->right = traverse->left;
        }
        delete traverse;
        cout << "deleted node had 1 child" << endl;
    }
    else if(traverse->right != NULL && traverse->left== NULL){
        if(isLeftofPrev == true){
            prev->left = traverse->right;
        }
        else{
            prev->right = traverse->right;
        }
        delete traverse;
        cout << "deleted node had 1 child" << endl;
    }
    //if the node has no children, meaning it is the end of the branch, set the node pointer stored in the previous node to NULL
    //then delete the node
    else{
        if(isLeftofPrev == true){
            prev->left = NULL;
        }
        else{
            prev->right = NULL;
        }
        delete traverse;
        cout << "deleted node had no children" << endl;
    }
    return root;
}