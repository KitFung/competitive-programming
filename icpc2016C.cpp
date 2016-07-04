#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

struct Node {
   int val;
   Node* left = NULL;
   Node* right = NULL;
   Node() {}
   Node(int z): val(z) {}
};

bool Equal(Node *a, Node *b) {
   if(a == NULL && b == NULL) return true;
   if ((a == NULL && b != NULL) || (a != NULL && b == NULL)) return false;
   return Equal(a->left, b->left) && Equal(a->right, b->right);
}

void Delete(Node* node) {
   if( node == NULL )
       return;
   Delete(node->left);
   Delete(node->right);
   node->left = NULL;
   node->right = NULL;
   delete node;
}

void Insert( Node* node, int value )
{
   if( node->val > value ) {
      if(node->left == NULL)
         node->left = new Node( value );
      else
         Insert( node->left, value );
   } else {
      if(node->right == NULL) {
         node->right = new Node( value );
      }
      else {
         Insert( node->right, value );
      }
   }
}


int main() {
   // freopen("input.txt", "r", stdin);
   int N, K, val;
   while(scanf("%d%d", &N, &K) != EOF) {
      vector<Node*> v;
      for(int n = 0; n < N; ++n) {
         scanf("%d", &val);

         Node *root = new Node(val);

         for(int k = 1; k < K; ++k) {
            scanf("%d", &val);
            Insert(root, val);
         }
         v.push_back(root);
      }


      vector<Node*> unique;
      for(int i = 0; i < v.size(); ++i) {
         bool repeated = false;
         for(int j = 0; j < unique.size(); ++j) {
            if(Equal(unique[j], v[i])) {
               repeated = true;
               break;
            }
         }
         if(!repeated) {
            unique.push_back(v[i]);
         }
      }

      printf("%d\n", unique.size());
      for(int i = 0; i < v.size(); ++i) {
         Delete(v[i]);
      }

      v.clear();
   }

}
