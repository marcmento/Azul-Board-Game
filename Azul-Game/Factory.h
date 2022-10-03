
#ifndef COSC_ASSIGN_TWO_BST
#define COSC_ASSIGN_TWO_BST

#include <memory>

#define TILES_IN_FACTORY 4

class BST_Node {
public:

   BST_Node(int value);
   ~BST_Node();

   // Converts colour enum to letter
   std::string convertCol(int num);
   int value;

   std::shared_ptr<BST_Node> left;
   std::shared_ptr<BST_Node> right;
};

class BST {
public:

   BST();
   ~BST();

   // Clears binary search tree
   void clear();

   // Checks if BST is empty
   bool isEmpty();
   
   // contract: don't modify the data given
   bool contains(const int data) const;
   // Checks for multiple tiles in tree
   int multiple(const int data) const;

   int multiple(std::shared_ptr<BST_Node> node, const int data, int returnValue) const;

   // contract: don't modify the data given
   void add(const int data);

   // Do a Depth First Search of the BST
   void dfs() const;

private:
   std::shared_ptr<BST_Node> root;

   bool contains(std::shared_ptr<BST_Node> node, 
                 const int data) const;

   std::shared_ptr<BST_Node> add(std::shared_ptr<BST_Node> node, 
                                 const int data);

   void dfs(std::shared_ptr<BST_Node> node) const;
};

#endif // COSC_ASSIGN_TWO_BST
