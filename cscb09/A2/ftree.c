#include <stdio.h>
// Add your system includes here.
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#include "ftw.h"
#include "ftree.h"
#include "hash.h"

void walkkDir(char *root_dir)
{
	DIR *dir = opendir(root_dir);
    struct dirent *ent;
    struct stat sb;

    if (dir != NULL)
    {
	    chdir(root_dir);
	    while((ent = readdir(dir)) != NULL) 
	    {
	    	char * d_name = ent->d_name; 
	        lstat(d_name,&sb);
	        // if a directory
	        if(S_ISDIR(sb.st_mode)) 
	        {
	            // ignore current and parent folder, respectively
	            if(strcmp(".",d_name) == 0 || strcmp("..",d_name) == 0)
	                continue;
	            // make child	
	            // populate node field
s
	            printf("%s\n",d_name);
	            // one level deeper
	            walkkDir(d_name);
	        }
	        //if a file or link

	        else 
	        {
	        	// make sibling
	        	// populate node fields
	        	printf("%s\n",d_name);

	        }

	    }
	    // go back up and close completed directory
	    chdir("..");
	    closedir(dir);
	    
	}
	//check for error
	else
	{
		printf("error");
	}	
}

struct TreeNode* createNode(char *name)
{

	struct TreeNode* new_node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	new_node->contents = NULL;  //child
	new_node->next = NULL;      //siblilng
	new_node->hash = NULL; 
	new_node->permissions = 0;
	new_node->fname = name;
 
	return new_node;
};


/*
 * Returns the FTree rooted at the path fname.
 */
struct TreeNode *generate_ftree(const char *fname) {
    // Your implementation here.
	char root[512];
	strcpy(root, fname);
	
	// make root node

	// recurse through directory and make all child nodes
	walkkDir(root); 


	return NULL;

}


/*
 * Prints the TreeNodes encountered on a preorder traversal of an FTree.
 */
void print_ftree(struct TreeNode *root) {
    // Here's a trick for remembering what depth (in the tree) you're at
    // and printing 2 * that many spaces at the beginning of the line.
    static int depth = 0;
    printf("%*s", depth * 2, "");

    // Your implementation here.
    printf("yeboi");
}


