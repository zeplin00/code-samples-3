#include <iostream>
#include <vector>

using namespace std;

typedef struct node {
  int key;
  struct node *l;
  struct node *r;
  struct node *p;
} node;

typedef node *NODEPTR;

NODEPTR bst_min(NODEPTR root)
{
  if (!root) return root;

  while (root->l) { root = root->l; }

  return root; 

}

NODEPTR bst_max(NODEPTR root)
{
  if (!root) return root;

  while (root->r) { root = root->r; }

  return root; 

}

NODEPTR bst_successor(NODEPTR n)
{
  if (!n) return NULL;

  if (n->r) return bst_min(n->r);

  NODEPTR p = n->p; 

  while (p && (n == p->r)) {
    n = p;
    p = p->p;
  }

  return p;
  
}

NODEPTR bst_predecessor(NODEPTR n)
{
  if (!n) return NULL;

  if (n->l) return bst_max(n->l);

  NODEPTR p = n->p; 

  while (p && (n == p->l)) {
    n = p;
    p = p->p;
  }

  return p;
  
}

void transplant(NODEPTR &root, NODEPTR &u, NODEPTR &v)
{
  if (u->p == NULL) root = v;
  else if (u == u->p->l) {
    // u is the left child
    //
    u->p->l = v;
  } else if (u == u->p->r) {
    // u is the right child
    //
    u->p->r = v;
  }

  if (v) v->p = u->p;

  return;

}

void bst_delete(NODEPTR &root, NODEPTR n)
{
  if (!root || !n) return;

  if (!n->l) {
    // No left subtree
    //
    transplant(root, n, n->r); 
  } else if (!n->r) {
    // No right subtree
    //
    transplant(root, n, n->l); 

  } else {
    // Both subtrees exist
    //
    NODEPTR y = bst_min(n->r);

    // y has to be in the right subtree of n
    // y cannot have a left child.
    //
    if (y->p != n) {
      // y is not n's child
      //
      transplant(root, y, y->r);
      y->r = n->r;
      y->r->p = y;
    }

    transplant(root, n, y);
    y->l= n->l;
    y->l->p = y;

  }


  return;
}

NODEPTR bst_find(NODEPTR root, int key)
{
  if (!root || (root->key == key) ) return root;

  if (key > root->key) return bst_find(root->r, key);  
  else return bst_find(root->l, key);

}

void bst_inorder(NODEPTR root)
{
  if (!root) return;

  bst_inorder(root->r);

  cout << "In-Order key = " << root->key << endl;

  bst_inorder(root->l);

  return;
}

void bst_insert(NODEPTR &root, int key)
{
   // Create a new node
   //
   node *n = new node;

   n->key = key;

   n->l = n->r = n->p = NULL;

   NODEPTR st = root;
   NODEPTR y = st;

   while (st != NULL) {

     y = st;

     if (key < st->key) st=st->l; else st=st->r;
   }

   n->p = y;

   if (!y) root = n; 
   else if (key < y->key) y->l = n;
   else y->r = n;

   return; 
}

int main()
{
  NODEPTR bst_root = NULL;

  vector<int> elements = {100, 200, 50, 3, 5, 4, 5, 7, 8, 9};

  for(auto &x : elements) {
    cout << "Adding " << x << endl;
    bst_insert(bst_root, x);  
  }

  NODEPTR del1 = bst_find(bst_root, 100);
  NODEPTR del2 = bst_find(bst_root, 200);

  bst_delete(bst_root, del1);
  bst_delete(bst_root, del2);

  bst_inorder(bst_root);

  return 0;
}
