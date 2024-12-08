#include"binary_tree.h"
#include"list.h"
#include"utility.h"

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
/*//作らなくてもいいか
void insert_node_as_AVl(Tree* root,Tree node){

}
//必要ないかも
void revalance_as_AVL(Tree* root,Tree node){
}*/

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

void get_key_record(Tree root,List* list){
	if (root == NULL) return;
	push_back_list(list,root->key);
	get_key_record(root->left,list);
	get_key_record(root->right,list);
}

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
		List* keyrecord = create_list(n);

		for(int j = 1;j<n;j++) insert_node(current_p,create_tree(list[i][j]));

		get_key_record(current,keyrecord);
		current_id = permutation_num(keyrecord->list,keyrecord->len);
		for(int j = 0;j<keyrecord->len;j++) printf("%d:",keyrecord->list[j]);
		printf("[%d],node%d",current_id,keyrecord->len);
		putchar('\n');
		
		for(int j = 0;j<n;j++) printf("%d,",list[i][j]);
		printf("[%d]",permutation_num(list[i],n));
		putchar('\n');
		//putchar('\n');
		

		printf("-----\n");

		for(int j = 0;j<=different_tree_num;j++){
			if(result[j] == NULL){
				result[different_tree_num++] = current;
				break;
			}
			List* keyrecord2 = create_list(n);
			get_key_record(result[j],keyrecord2);
			int result_j_id = permutation_num(keyrecord2->list,keyrecord2->len);
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