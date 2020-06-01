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
    kdTreeNode<T>* left;
    kdTreeNode<T>* right;
    kdTreeNode<T>* parent;
    int split;
    vector<T> data;
    vector<T> range;
};

template<typename T>
class kdTree{
public:
    kdTree(){

    }
    void split_arr(vector<vector<T>> arr, kdTreeNode* parent) {
        if(arr.size() == 0){
            return;
        }
        float nums = arr.size();
        int max_split = 0;
        float max_square_var = 0
        for(int i=0; i<k; i++){
            float mean_val = 0;
            float square_val = 0;
            for(int j=0; j<arr.size(); j++){
                mean_val += arr[j][k];
                square_val += arr[j][k]*arr[j][k];
            }
            float temp_square_var = square_val/nums/nums - mean_val*mean_val/nums
            if (temp_square_var > max_square_var){
                max_split = k;
                max_square_var = temp_square_var;
            }
        }
        auto fun = [max_split](vector<T> a, vector<T> b){return a[max_split]<b[max_split]};
        sort(arr.begin(), arr.end(); fun);
        int mid = nums / 2;
        parent->data.assign(arr[mid].begin(), arr[mid].end());
        parent->split = max_split;
        parent->left = new kdTreeNode(parent);
        parent->right = new kdTreeNode(parent);
        vector<vector<T>>left(arr.begin(),arr.begin()+mid);
        vector<vector<T>>right(arr.begin()+mid+1,arr.end();
        split_arr(left, parent->left);
        split_arr(right, parent->right);
    }   
    void initialize_kdTree(vector<vector<T>> arr, kdTreeNode* parent){
        if (arr.empty()) {
            root = NULL;
            return;
        }
        k = arr[0].size();  //get k dimension
        
    }

private:
    kdTreeNode<T>* root;
    int k;

};