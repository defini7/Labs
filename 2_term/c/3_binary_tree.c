#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N 16

typedef struct
{
    struct BinaryTree* left;
    struct BinaryTree* right;
    int value;
} BinaryTree;

void bt_push(BinaryTree** this, int value)
{
    if (this == NULL)
        return;

    if (*this == NULL)
    {
        *this = (BinaryTree*)malloc(sizeof(BinaryTree));

        assert(*this && "Buy more RAM!");

        (*this)->value = value;
        (*this)->left = NULL;
        (*this)->right = NULL;

        return;
    }
    
    if (value <= (*this)->value)
        bt_push(&(*this)->left, value);
    else
        bt_push(&(*this)->right, value);
}

void bt_traversal_preorder(BinaryTree* this)
{
    if (this == NULL)
        return;

    printf("%d ", this->value);

    bt_traversal_preorder(this->left);
    bt_traversal_preorder(this->right);
}

void bt_traversal_inorder(BinaryTree* this)
{
    if (this == NULL)
        return;

    bt_traversal_inorder(this->left);
    printf("%d ", this->value);
    bt_traversal_inorder(this->right);
}

void bt_traversal_postorder(BinaryTree* this)
{
    if (this == NULL)
        return;

    bt_traversal_postorder(this->left);
    bt_traversal_postorder(this->right);

    printf("%d ", this->value);
}

int main()
{
    BinaryTree* bt = NULL;

    printf("Input: ");

    for (int i = 0; i < N; i++)
    {
        int value = rand() % N;
        bt_push(&bt, value);
        printf("%d ", value);
    }

    printf("\nAfter preorder traversal: ");
    bt_traversal_preorder(bt);

    printf("\nAfter inorder traversal: ");
    bt_traversal_inorder(bt);

    printf("\nAfter postorder traversal: ");
    bt_traversal_postorder(bt);

    return 0;
}
