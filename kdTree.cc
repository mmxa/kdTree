#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


template<typename T>
struct kdTreeNode{
    kdTreeNode(){
        left = NULL;
        right = NULL;
        parent = NULL;
    }
    kdTreeNode(kdTreeNode* root){
        left = NULL;
        right = NULL;
        parent = root;
    }
    kdTreeNode(kdTreeNode* root, kdTreeNode* left_node, kdTreeNode* right_node){
        left = left_node;
        right = right_node;
        parent = root;
    }
    kdTreeNode(const vector<T>& data):data(data){
        left = NULL;
        right = NULL;
        parent = NULL;
    }
    kdTreeNode<T>* left;
    kdTreeNode<T>* right;
    kdTreeNode<T>* parent;
    int split;
    vector<T> data;
    vector<T> range;
    ~kdTreeNode(){
        cout << "node destory"<<endl;
    }
};

template<typename T>
class kdTree{
public:
    kdTree(const vector<vector<T>>& arr){
        data_base = arr;
        //initialize_kdTree(arr);
        if (data_base.empty()){
            root = NULL;
            return;
        }
        k = data_base[0].size(); //get dimension of database
        int right = data_base.size();
        root = split_arr(0, right, -1, NULL);
    }

    ~kdTree() {
        visit = [](kdTreeNode<T>* node){delete node;};
        postOrder(root);
    }

    kdTreeNode<T>* split_arr(int left, int right, int dim, kdTreeNode<T>* parent) {
        if (left >= right) {
            return NULL;
        }
        int cur_dim  = (dim%k) + 1;       // choose dimension one by one
        auto fun = [cur_dim](vector<T> a, vector<T> b){return a[cur_dim]<b[cur_dim];};
        sort(data_base.begin()+left, data_base.begin()+right, fun);
        int mid = (left+right) / 2;
        //vector<T> cur_data = data_base[mid];
        kdTreeNode<T>* cur_node = new kdTreeNode<T>(data_base[mid]);
        cur_node->split = cur_dim;
        cur_node->parent = parent;
        cur_node->left = split_arr(left, mid, cur_dim, cur_node);
        cur_node->right = split_arr(mid+1, right, cur_dim, cur_node);
        return cur_node;
    }

    void split_arr(vector<vector<T>> arr, kdTreeNode<T>* parent) {
        if(arr.size() == 0){
            return;
        }
        float nums = arr.size();
        int max_split = 0;
        float max_square_var = 0;
        for(int i=0; i < k; i++) {
            float mean_val = 0;
            float square_val = 0;
            for(int j=0; j<arr.size(); j++){
                mean_val += arr[j][k];
                square_val += arr[j][k]*arr[j][k];
            }
            float temp_square_var = square_val/nums - mean_val*mean_val/nums/nums;
            if (temp_square_var > max_square_var){
                max_split = i;
                max_square_var = temp_square_var;
            }
        }
        auto fun = [max_split](vector<T> a, vector<T> b){return a[max_split]<b[max_split];};
        sort(arr.begin(), arr.end(), fun);
        int mid = nums / 2;
        parent->data = arr[mid];
        parent->split = max_split;
        if(nums <= 1){
            return;
        }
        parent->left = new kdTreeNode<T>(parent);
        vector<vector<T>>left(arr.begin(),arr.begin()+mid);
        split_arr(left, parent->left);
        if (nums==2) {
            return;
        }
        parent->right = new kdTreeNode<T>(parent);
        vector<vector<T>>right(arr.begin()+mid+1,arr.end());
        parent->right = new kdTreeNode<T>(parent);
        split_arr(right, parent->right);
    }   

    void initialize_kdTree(vector<vector<T>> arr){
        if (arr.empty()) {
            root = NULL;
            return;
        }
        k = arr[0].size();  //get k dimension
        root = new kdTreeNode<T>();
        split_arr(arr, root);
    }

    void inOrder(kdTreeNode<T>* node) {
        if (node == NULL){
            return;
        }
        inOrder(node->left);
        visit(node);
        inOrder(node->right);
    }
    void preOrder(kdTreeNode<T>* node) {
        if (node == NULL){
            return;
        }
        visit(node);
        preOrder(node->left);
        preOrder(node->right);
    }
    void postOrder(kdTreeNode<T>* node) {
        if (node == NULL){
            return;
        }
        postOrder(node->left);
        postOrder(node->right);
        visit(node);
    }
    void inOrder_visit(void(*func_pointer)(kdTreeNode<T>*)) {
        visit = func_pointer;
        inOrder(root);
    }
    void preOrder_visit(void(*func_pointer)(kdTreeNode<T>*)) {
        visit = func_pointer;
        preOrder(root);
    }

private:
    vector<vector<T>> data_base;
    void (*visit)(kdTreeNode<T>*);
    kdTreeNode<T>* root;
    int k;
};

template<typename T>
void print_element(kdTreeNode<T>* elem) {
    for(int i=0; i<elem->data.size(); i++) {
        cout << elem->data[i] << "  ";
    }
    cout << endl;
}

int main(int argc, char** argv) {
    vector<vector<int>> nums;
    // for(int i=0; i<10; i++){
    //     vector<int> temp;
    //     for(int j=0; j<2; j++) {
    //         temp.push_back(i + j);
    //     }
    //     nums.push_back(temp);
    // }
    nums.push_back(vector<int>{2,3});
    nums.push_back(vector<int>{5,4});
    nums.push_back(vector<int>{4,7});
    nums.push_back(vector<int>{7,2});
    nums.push_back(vector<int>{9,6});
    nums.push_back(vector<int>{8,1});
    //nums.push_back(vector<int>{2,3});
    
    kdTree<int>* tree = new kdTree<int>(nums);
    tree->inOrder_visit(print_element<int>);
    cout << "-----"<<endl;
    tree->preOrder_visit(print_element<int>);
    delete tree;
}
