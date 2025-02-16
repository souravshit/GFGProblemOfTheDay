#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

// Function to serialize the tree into a vector<int>
vector<int> serialize(Node* root) {
    vector<int> result;
    if (!root) return result;
    
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        
        if (node) {
            result.push_back(node->data);
            q.push(node->left);
            q.push(node->right);
        } else {
            result.push_back(-1); // Representing NULL
        }
    }
    return result;
}

// Function to deserialize the vector<int> into a tree
Node* deSerialize(vector<int>& data) {
    if (data.empty()) return NULL;
    
    Node* root = new Node(data[0]);
    queue<Node*> q;
    q.push(root);
    int i = 1;
    
    while (!q.empty() && i < data.size()) {
        Node* node = q.front();
        q.pop();
        
        if (data[i] != -1) {
            node->left = new Node(data[i]);
            q.push(node->left);
        }
        i++;
        
        if (i < data.size() && data[i] != -1) {
            node->right = new Node(data[i]);
            q.push(node->right);
        }
        i++;
    }
    return root;
}

// Inorder traversal function for verification
void inorderTraversal(Node* root, vector<int>& result) {
    if (!root) return;
    inorderTraversal(root->left, result);
    result.push_back(root->data);
    inorderTraversal(root->right, result);
}

int main() {
    // Constructing a sample tree
    //        1
    //       / \
    //      2   3
    //         / \
    //        4   5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->right->left = new Node(4);
    root->right->right = new Node(5);
    
    vector<int> serializedTree = serialize(root);
    cout << "Serialized: ";
    for (int num : serializedTree) cout << num << " ";
    cout << endl;
    
    Node* deserializedRoot = deSerialize(serializedTree);
    vector<int> inorderResult;
    inorderTraversal(deserializedRoot, inorderResult);
    
    cout << "In-order Traversal of Deserialized Tree: ";
    for (int num : inorderResult) cout << num << " ";
    cout << endl;
    
    return 0;
}

