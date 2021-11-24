struct Tree{
    int num;
    Tree *left, *right;
};
Tree *create(int *arr, int size){
    Tree *tree = new Tree;
    tree->num = arr[0];
}