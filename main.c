#include <stdio.h>
#include<stdlib.h>
struct Node{
    int key;
    struct Node* left;
    struct Node* right;
};

typedef struct Node* Tree;

struct Node* create_tree(int key);
void delete_tree(struct Node* node);
void insert_node(Tree* root,Tree node);
Tree extract_max(Tree root);
void delete_node(Tree* root,int key);
void search_pre(Tree root);
void search_pre_with_depth(Tree root,int depth);
void search_middle(Tree root);
void search_post(Tree root);

//-----------max--------------
int max_(int a,int b){
	return a>b?a:b;
}
//----------avg---------------
//----------var---------------
//----------factorial---------
int factorial(int n){
	if (n<=1) return 1;
	return n*factorial(n-1);
}

//-----順列の生成--------------
//順列から番号の生成
int ind(int* num,int n){
	int ind = 0;
	for(int i = 0;i < n;i++){
		ind *= (n-i);
		for(int j = i+1;j<n;j++){
			if(num[i]>num[j]) ind++;
		}
	}
	return ind;
}

void clear(int *array,int n){
	for(int i = 0;i<n;i++) array[i] = 0;
}
//-------------二分木の作成------------------------
Tree create_tree(int key){
    Tree new_ = (struct Node*)malloc(sizeof(struct Node));

    new_->key = key;
    new_->left = NULL;
    new_->right = NULL;

    return new_;
}

//node以下のすべてのnodeを削除
void delete_tree(Tree node){
    if(node != NULL){
        delete_tree(node->left);
        delete_tree(node->right);
        free(node);
    }
}

int count_children(Tree root){
	if (root == NULL) return 1;
	else return count_children(root->left) + count_children(root->right);
}

int calculate_hight(Tree root){
	if(root == NULL) return 0;
	return max_(calculate_hight(root->left),calculate_hight(root->right))+1;
}

//左小さい 右大きい ポインタのポインタになる　注意
void insert_node(Tree* root,Tree node){
    if(*root == NULL) {
		*root = node;
		return;
	}
    if(node->key <= (*root)->key) insert_node(&((*root)->left),node);
    else insert_node(&((*root)->right),node); 
}
//作らなくてもいいか
void insert_node_as_AVl(Tree* root,Tree node){

}
//必要ないかも
void revalance_as_AVL(Tree* root,Tree node){
}

Tree extract_max(Tree root){
	if(root->right == NULL) return root; 
	else return extract_max(root->right);
}

Tree extract_min(Tree root){
	if(root->left == NULL) return root;
	else return extract_min(root->left);
}

void delete_node(Tree* root,int key){
    if(*root == NULL) return;
	if((*root)->key < key) delete_node(&((*root)->left),key);  
	else if((*root)->key > key) delete_node(&(*root)->left,key);
    else{
		/*if ((*root)->left == NULL && (*root)->right == NULL){
			free(*root);
			root = NULL;
		}*/
		//じつはこれだけでよかったね
		if((*root)->left == NULL){
			*root = (*root)->right;
			free(*root);
			root = NULL;
		}
		else{
			Tree left_tree_max = extract_max((*root)->left);
			Tree tmp = left_tree_max->left;
			left_tree_max->left = (*root)->left;
			left_tree_max->right = (*root)->right;
			free(*root);//release例では*rootを別に取ってあるのでfreeと*root=maxの行が入れ替わっている。
			*root = left_tree_max;
			((*root)->left)->right = tmp;
		}
	}
}

void search_pre(Tree root){
	if (root == NULL) return;
	printf("key:%d\n",root->key);
	search_pre(root->left);
	search_pre(root->right);
}

void search_pre_with_depth(Tree root,int depth){
	if (root == NULL) return;
	printf("key:%d d:%d\n",root->key,depth);
	search_pre_with_depth(root->left,depth+1);
	search_pre_with_depth(root->right,depth+1);
}

void get_key_record(Tree root,int* list,int* num){
	if (root == NULL) return;
	list[*num] = root->key;
	++*num;
	get_key_record(root->left,list,num);
	get_key_record(root->right,list,num);
}

void search_middle(Tree root){
	if (root == NULL) return;
	search_middle(root->left);
	printf("key:%d\n",root->key);
	search_middle(root->right);
}

void search_post(Tree root){
	if (root == NULL) return;
	search_post(root->left);
	search_post(root->right);
	printf("key:%d\n",root->key);
}

void print_tree(Tree root){
	
}

//全探索による順列の生成
void calculate_permutation(int** list,int* nums,int* seen,int seed,int n,int depth){
	seen[seed] = 1;
	nums[depth] = seed;
	for(int i = 1;i <= n;i++){
		if(seen[i] == 0){
			calculate_permutation(list,nums,seen,i,n,depth+1);
			seen[i] = 0;
		}
	}
	if(depth == n-1) for(int i = 0;i<n;i++) list[ind(nums,n)][i] = nums[i];
	
}

int** get_permutation_list(int n){
	int* seen = (int*)calloc(sizeof(int),(n+1));
	int* nums = (int*)calloc(sizeof(int),(n+1));

	int** list = (int**)malloc(sizeof(int*)*factorial(n));
	for(int i = 0;i<factorial(n);i++) list[i] = (int*)malloc(sizeof(int)*n);

	for(int i = 1;i<=n;calculate_permutation(list,nums,seen,i,n,0),clear(seen,n+1),i++);

	return list;	
}

/*void get_different_trees(int n){
	int* seen = (int*)calloc(sizeof(int),n+1);
	int* nums = (int*)calloc(sizeof(int),n+1);
	int depth = 0;

	for(int i = 1;i<=n;i++){;
	seen[i] = 1;
	nums[depth] = i;
	for(int i = 1;i <= n;i++){
		if(seen[i] == 0){
			permutation(nums,seen,i,n,depth+1);
			seen[i] = 0;
		}
	}
	if(depth == n-1)
	{
		printf("%d:",ind(nums,4));
		Tree root = create_tree(nums[0]);
		Tree* root_p = &root;
		for(int i = 0;i<n;i++) printf("%d ",nums[i]);
		putchar('\n');
		for(int i = 1;i<n;i++){
			insert_node(root_p,create_tree(nums[i]));
		}
		search_pre_with_depth(root,0);
		printf("hight:%d\n",calculate_hight(root));
		printf("\n");
		delete_tree(root);
	}
	clear(seen,n+1);
	}
}*/
void get_different_trees(int n){
	int fact = factorial(n);
	int** list = get_permutation_list(n);
	
	Tree* result = (Tree*)malloc(sizeof(Tree)*fact);
	for(int i = 0;i<fact;i++) result[i] = NULL;

	for(int i = 0;i<fact;i++){
		Tree root = create_tree(list[i][0]);
		Tree* root_p = &root;
		int* nums = (int*)calloc(sizeof(int),n);
		int node_num = 0;

		for(int j = 1;j<n;j++) insert_node(root_p,create_tree(list[i][j]));

		get_key_record(root,nums,&node_num);
		for(int j = 0;j<n;j++) printf("%d:",nums[j]);
		printf("[%d]",ind(nums,n));
		putchar('\n');
		
		for(int j = 0;j<n;j++) printf("%d,",list[i][j]);
		printf("[%d]",ind(list[i],n));
		putchar('\n');


		//printf("hight:%d\n",calculate_hight(root));
		printf("\n");		
	}


	for(int i = 0;i<fact;i++) free(list[i]);
	free(list);
	//return result;
}


int main(){
	get_different_trees(4);
	/*Tree n44 = create_tree(44);
	Tree n12 = create_tree(12);
	Tree n55 = create_tree(55);
	Tree n6 = create_tree(6);
	Tree n42 = create_tree(42);
	Tree n67 = create_tree(67);
	Tree n14 = create_tree(14);
	Tree n18 = create_tree(18);
	Tree* root = &n44;

	insert_node(root,n12);
	insert_node(root,n55);
	insert_node(root,n6);
	insert_node(root,n42);
	insert_node(root,n67);
	insert_node(root,n14);
	insert_node(root,n18);
	search_pre(n44);

	delete_node(root,44);
	putchar('\n');
	search_pre(n42);*/
	
	/*int seen[LIM+1];
	clear(seen,LIM+1);
	int nums[LIM+1];
	clear(nums,LIM+1);
	int n = 4;


	for(int i = 1;i<=n;calculate_permutation(res,nums,seen,i,n,0),clear(seen,LIM+1),i++);
	
	for(int i = 0;i<24;putchar('\n'),i++) for(int j = 0;j<4;j++) printf("%d ",res[i][j]);*/


}