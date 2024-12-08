#include <stdio.h>
#include<stdlib.h>
#include"list.h"
#include"binary_tree.h"
#include"utility.h"

int main(){
	int n = 4;
	Tree* result = get_different_trees(n);

	for(int i = 0;result[i] != NULL;i++){
		printf("[%d\n",i);
		search_pre_with_depth(result[i],0);
		putchar('\n');
	}

}