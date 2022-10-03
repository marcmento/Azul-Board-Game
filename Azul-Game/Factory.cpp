#include "Factory.h"

#include <iostream>
#include <string>

BST_Node::BST_Node(int value) :
   value(value),
   left(nullptr),
   right(nullptr)
{

}

BST_Node::~BST_Node() {
   left = nullptr;
   right = nullptr;
}

std::string BST_Node::convertCol(int num){
    std::string returnval;
    if(num == 0){
      returnval = "R ";
   } else if (num == 1){
      returnval = "Y ";
   } else if (num == 2){
      returnval = "B ";
   } else if (num == 3){
      returnval = "L ";
   } else if (num == 4){
      returnval = "U ";
   } else if (num == 5){
      returnval = "F ";
   } else if (num == 6){
      returnval = ". ";
   } else if (num == 7){
      returnval = "  ";
   } else if (num == 8){
      returnval = "O ";
   }
   return returnval;
}

BST::BST() {
   root = nullptr;
}

BST::~BST() {
}

void BST::clear() {
   root = nullptr;
}

bool BST::isEmpty(){
    bool returnval = false;
    if(root == nullptr){
        returnval = true;
    }
    return returnval;
}

bool BST::contains(const int data) const {
   return contains(root, data);
}

bool BST::contains(std::shared_ptr<BST_Node> node, 
                   const int data) const {
   bool returnValue = false;

   if (node == nullptr) {
      returnValue = false;
   } else if (data == node->value) {
      returnValue = true;
   } else {
      // recursive case
      // check which side of the tree to search in
      if (data < node->value) {
         // go left
         returnValue = contains(node->left, data);
      } else {
         // go right
         returnValue = contains(node->right, data);
      }
   }

   return returnValue;
}

int BST::multiple(const int data) const {
   int returnValue = 0;
   return multiple(root, data, returnValue);
}

int BST::multiple(std::shared_ptr<BST_Node> node, const int data, int returnValue) const {
   if (node != nullptr) {
      if (data == node->value) {
         returnValue++;
      }
      // recursive case
      // check which side of the tree to search in
      if (data < node->value) {
         // go left
         returnValue = multiple(node->left, data, returnValue);
      } else {
         // go right
         returnValue = multiple(node->right, data, returnValue);
      }
   }
   return returnValue;
}

void BST::add(const int data) {
   root = add(root, data);
}

std::shared_ptr<BST_Node> BST::add(std::shared_ptr<BST_Node> node, 
                                   const int data) {

   // Please start here VSCODE
   std::shared_ptr<BST_Node> returnNode;

   if (node == nullptr) {
      // base case
      returnNode = std::make_shared<BST_Node>(data);
   } else {
      // recursive case
      // check which side of the tree to add the data to
      if (data < node->value) {
         // go left
         std::shared_ptr<BST_Node> subtree = add(node->left, data);
         node->left = subtree;
         returnNode = node;
      } else {
         // go right
         std::shared_ptr<BST_Node> subtree = add(node->right, data);
         node->right = subtree;
         returnNode = node;
      }
   }

   return returnNode;
}

void BST::dfs() const {
   dfs(root);
}

void BST::dfs(std::shared_ptr<BST_Node> node) const {
   // print out all node in the BST
   // go left
   if (node != nullptr) {
      dfs(node->left);

      // do me
      std::cout<< node->convertCol(node->value);

      // go right
      dfs(node->right);
   }
   
}