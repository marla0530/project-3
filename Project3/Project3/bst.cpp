#include "bst.h"

//insert nodes into a bst
node* BST::insert(node* root, double& key, string& teamName) {
    
    if (root == NULL) {
        return new node(key, teamName);
    }

    //if node already exist within the tree push it into the vector on the nodes
    else if (root->powerlevel == key) {
        root->teams.push_back(teamName);
        return root;
    }


    //traverse left
    if (key < root->powerlevel) {
        root->left = insert(root->left, key, teamName);
    }

    
    //traverse right
    else {
        root->right = insert(root->right, key, teamName);

    }

    return root;
}


//return the kth largest number in the tree
void BST::kLargest(node* root, int& k) {
    if (root == NULL) {
        return;
    }

    //reverse inorder traversal
    kLargest(root->right, k);
 
    //when k = 0 we have found the targeted kth largest
    if (k <= 0) {
        return;
    }

    //if kth largest is within the vector push it to the ourtput and set k to 0 
    else if (k <= root->teams.size()) {
        

        result.push_back( make_pair(root->teams[k - 1],root->powerlevel));
        k = 0;
    }

    //decrease k by the number of teams in the vector
    else {

        k -= root->teams.size();
    }

    kLargest(root->left, k);
}

//call kLargest x times
void BST::topX(int x) {
    
    for (int i = 1; i < x+1; i++) {
        int temp = i;
        kLargest(root,temp);
        
    }
}

//return vector of data
vector<pair<string, double >> BST::getResult() {
    return result;
}