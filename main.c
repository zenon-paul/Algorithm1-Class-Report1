#include <stdio.h>
#include<stdlib.h>
struct Node{
    int key;
    struct Node* left;
    struct Node* right;
};

typedef struct Node* Tree;

typedef struct list{
	int* list;
	int size;
	int len;
}List;

typedef struct tree_list{
	Tree* list;
	int size;
	int len;
}TreeList;

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

int min_(int a,int b){
	return a<b?a:b;
}
//----------avg---------------
//----------var---------------
//----------factorial---------
int factorial(int n){
	if (n<=1) return 1;
	return n*factorial(n-1);
}

//-------------list----------------
List* create_list(int lim){
	List* new_ = (List*)malloc(sizeof(List));
	new_->list = (int*)calloc(sizeof(int),lim);
	new_->size = lim;
	new_->len = 0;
	return new_;
}

void delete_list(List* list){
	free(list->list);
	free(list);
}

int push_back_list(List* list,int num){
	if(list->size == list->len) return 0;
	list->list[list->len] = num;
	list->len += 1;
	return 1;
}

void print_list(List list){
	for(int i = 0;i<min_(list.size,list.len);i++)printf("%d ",list.list[i]);
	putchar('\n');
}
//-------------tree list----------------
TreeList* create_treelist(int lim){
	TreeList* new_ = (TreeList*)malloc(sizeof(TreeList));
	new_->list = (Tree*)calloc(sizeof(Tree),lim);
	new_->size = lim;
	new_->len = 0;
	return new_;
}

void delete_treelist(TreeList* list){
	free(list->list);
	free(list);
}

int push_back_treelist(TreeList* list,Tree tree){
	if(list->size == list->len) return 0;
	list->list[list->len] = tree;
	list->len += 1;
	return 1;
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

void get_key_record_(Tree root,List* list){
	if (root == NULL) return;
	push_back_list(list,root->key);
	get_key_record_(root->left,list);
	get_key_record_(root->right,list);
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
Tree* get_different_trees(int n){
	int fact = factorial(n);
	int** list = get_permutation_list(n);
	int different_tree_num = 0;
	
	Tree* result = (Tree*)malloc(sizeof(Tree)*(fact+1));//番兵を一つ残すため
	for(int i = 0;i<fact+1;i++) result[i] = NULL;

	for(int i = 0;i<fact;i++){
		Tree current = create_tree(list[i][0]);
		Tree* current_p = &current;
		int current_id  = 0;
		int* keyrecord = (int*)calloc(sizeof(int),n);
		int* keyrecord2 = (int*)calloc(sizeof(int),n);
		int node_num = 0;

		for(int j = 1;j<n;j++) insert_node(current_p,create_tree(list[i][j]));

		get_key_record(current,keyrecord,&node_num);
		current_id = ind(keyrecord,n);
		for(int j = 0;j<n;j++) printf("%d:",keyrecord[j]);
		printf("[%d],node%d",current_id,node_num);
		putchar('\n');
		
		for(int j = 0;j<n;j++) printf("%d,",list[i][j]);
		printf("[%d]",ind(list[i],n));
		putchar('\n');
		//putchar('\n');
		

		printf("-----\n");

		for(int j = 0;j<=different_tree_num;j++){
			int node_num2 = 0;
			if(result[j] == NULL){
				result[different_tree_num++] = current;
				printf("s");
				break;
			}
			
			get_key_record(result[j],keyrecord2,&node_num2);
			int result_j_id = ind(keyrecord2,n);
			printf("j:%d{%d %d}node%d\n",j,current_id,result_j_id,node_num2);
			for(int k = 0;k<node_num2;k++) printf("%d ",keyrecord2[k]);
			putchar('\n');
			putchar('#');
			search_pre_with_depth(result[j],0);
			//for(int j = 0;j<n;j++) printf("%d:",keyrecord2[j]);
			putchar('\n');


			if(current_id == result_j_id){//採用しないのでcurrentはdelete
				printf("n");
				delete_tree(current);
				break;
			}			
		}

		printf("-----\n");
		free(keyrecord2);
		free(keyrecord);

		//printf("hight:%d\n",calculate_hight(root));
	}

	for(int i = 0;i<fact;i++) free(list[i]);
	free(list);

	Tree* tmp = NULL;
	while((tmp = (Tree*)realloc(result,sizeof(Tree)*(different_tree_num+1))) == NULL);
	result = tmp;
	tmp = NULL;

	return result;
}

Tree* get_different_trees_(int n){
	int fact = factorial(n);
	int** list = get_permutation_list(n);
	int different_tree_num = 0;
	
	Tree* result = (Tree*)malloc(sizeof(Tree)*(fact+1));//番兵を一つ残すため
	for(int i = 0;i<fact+1;i++) result[i] = NULL;

	for(int i = 0;i<fact;i++){
		Tree current = create_tree(list[i][0]);
		Tree* current_p = &current;
		int current_id  = 0;
		List* keyrecord = create_list(n);

		for(int j = 1;j<n;j++) insert_node(current_p,create_tree(list[i][j]));

		get_key_record_(current,keyrecord);
		current_id = ind(keyrecord->list,keyrecord->len);
		for(int j = 0;j<keyrecord->len;j++) printf("%d:",keyrecord->list[j]);
		printf("[%d],node%d",current_id,keyrecord->len);
		putchar('\n');
		
		for(int j = 0;j<n;j++) printf("%d,",list[i][j]);
		printf("[%d]",ind(list[i],n));
		putchar('\n');
		//putchar('\n');
		

		printf("-----\n");

		for(int j = 0;j<=different_tree_num;j++){
			if(result[j] == NULL){
				result[different_tree_num++] = current;
				break;
			}
			List* keyrecord2 = create_list(n);
			get_key_record_(result[j],keyrecord2);
			int result_j_id = ind(keyrecord2->list,keyrecord2->len);
			//print_list(*keyrecord2);
			delete_list(keyrecord2);
			printf("{%d:%d:%d\n",j,result_j_id,keyrecord2->len);
			if(current_id == result_j_id){
				delete_tree(current);
				break;				
			}
		}

		printf("-----\n");
		delete_list(keyrecord);


		//printf("hight:%d\n",calculate_hight(root));
	}

	for(int i = 0;i<fact;i++) free(list[i]);
	free(list);

	Tree* tmp = NULL;
	while((tmp = (Tree*)realloc(result,sizeof(Tree)*(different_tree_num+1))) == NULL);
	result = tmp;
	tmp = NULL;
	printf("$%d\n",different_tree_num);




	return result;
}


int main(){
	/*Tree current = create_tree(1);
	Tree* current_p = &current;
	for(int j = 4;j>1;j--) insert_node(current_p,create_tree(j));

	List* list = create_list(4);
	get_key_record_(current,list);
	print_list(*list);*/
	int n = 4;
	Tree* result = get_different_trees_(n);

	for(int i = 0;result[i] != NULL;i++){
		printf("[%d\n",i);
		search_pre_with_depth(result[i],0);
		putchar('\n');
	}
	/*Tree root;
	
	for(int i = 0;i<14;i++){
		List* keyrecord = create_list(n);
		get_key_record_(root,keyrecord);
		for(int j = 0;j<n;j++) printf("%d:",keyrecord->list[j]);
		printf("[%d]",ind(keyrecord->list,n));
		putchar('\n');
		delete_list(keyrecord);
	}*/
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