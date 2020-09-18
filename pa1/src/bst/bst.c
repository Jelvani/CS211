/* CS 211 PA1: bst
 * Created for: aj654
 */

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *getparent(struct node *head, struct node *buffer)
{
    struct node* temp = NULL;

    temp= head;
    while (1)
    {
        if (temp->left == buffer || temp->right == buffer)
        {
            return temp;
        }
        if (temp->data < buffer->data)
        {
            temp = temp->right;
        }
        else if (temp->data > buffer->data)
        {
            temp = temp->left;
        }
    }
}
void printtree(struct node *head, struct node *buffer)
{ //prints tree
    if (buffer == NULL)
    {
        return;
    }
    else
    {
        printf("(");
        printtree(head, buffer->left);
        printf("%d", buffer->data);
        printtree(head, buffer->right);
        printf(")");
    }
}
struct node *searchtree(int num, struct node *head, struct node *buffer)
{ //returns pointer to node searched for
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        while (1)
        {

            if (buffer == NULL)
            {

                return NULL;
            }
            if (buffer->data == num)
            {

                return buffer;
            }
            else if (buffer->data > num)
            {
                buffer = buffer->left;
            }
            else if (buffer->data < num)
            {
                buffer = buffer->right;
            }
        }
    }
    return NULL;
}
int main(int argc, char **argv)
{

    char cmd;
    struct node *head = NULL;
    struct node *buffer = NULL;
    struct node *temp = NULL;
    struct node *temp2 = NULL;
    int num;
    int stop;
    while (1)
    {
        stop = scanf("%c", &cmd);
        if (cmd != 'p')
        {
            stop = scanf("%d", &num);
        }

        if (stop == EOF)
        {
            return EXIT_SUCCESS;
        }
        buffer = head;
        if (cmd == 'i')
        { //insert into tree
            if (head == NULL)
            {
                head = (struct node *)malloc(sizeof(struct node));
                head->data = num;
                head->left = NULL;
                head->right = NULL;
                buffer = head;
                printf("inserted\n");
            }
            else
            {
                buffer = head;
                while (1)
                {
                    if (num < buffer->data)
                    {
                        if (buffer->left == NULL)
                        {
                            buffer->left = (struct node *)malloc(sizeof(struct node));
                            buffer->left->data = num;
                            buffer->left->right = NULL;
                            buffer->left->left = NULL;
                            printf("inserted\n");
                            break;
                        }
                        else
                        {
                            buffer = buffer->left;
                        }
                    }
                    else if (num > buffer->data)
                    {
                        if (buffer->right == NULL)
                        {
                            buffer->right = (struct node *)malloc(sizeof(struct node));
                            buffer->right->data = num;
                            buffer->right->right = NULL;
                            buffer->right->left = NULL;
                            printf("inserted\n");
                            break;
                        }
                        else
                        {
                            buffer = buffer->right;
                        }
                    }
                    else
                    {
                        printf("not inserted\n");
                        break;
                    }
                }
            }
        }
        else if (cmd == 's')
        { //search tree
            buffer = searchtree(num, head, buffer);
            if (buffer == NULL)
            {
                printf("absent\n");
            }
            else
            {
                printf("present\n");
            }
        }
        else if (cmd == 'p')
        { //print tree
            buffer = head;
            if (buffer == NULL)
            {
                printf("\n");
            }
            else
            {
                printtree(head, buffer);
                printf("\n");
            }
        }
        else if (cmd == 'd')
        { //delete node from tree
            buffer = head;

            buffer = searchtree(num, head, buffer);
            if (buffer == NULL)
            {
                printf("absent\n");
            }
            else if (buffer->left == NULL && buffer->right == NULL)
            { //if node being deleted has no children
                if (buffer == head)
                {
                    free(head);
                    head = NULL;
                    printf("deleted\n");
                }
                else
                {

                    temp = getparent(head, buffer);
                    buffer = searchtree(num, head, buffer);
                    if (temp->right == buffer)
                    {
                        temp->right = NULL;
                    }
                    else
                    {
                        temp->left = NULL;
                    }
                    printf("deleted\n");
                    free(buffer);
                    buffer = NULL;
                }
                buffer = head;
            }
            else if (buffer->left == NULL || buffer->right == NULL)
            {

				
				if(buffer!=head){
                temp = getparent(head, buffer);
                }
                buffer = searchtree(num, head, buffer);
				
                if(buffer==head){
                    if(buffer->right==NULL){
                        temp = head->left;
                    }else{
                        temp = head->right;
                    }
                    printf("deleted\n");
                    free(head);
                    head = temp;
                }
                else if (temp->left == buffer)
                {
                    if (buffer->right == NULL)
                    {

                        temp->left = buffer->left;
                        free(buffer);
                        printf("deleted\n");
                    }
                    else
                    {
                        temp->left = buffer->right;
                        free(buffer);
                        printf("deleted\n");
                    }
                }
                else if(temp->right==buffer)
                {
                    if (buffer->right == NULL)
                    {

                        temp->right = buffer->left;
                        free(buffer);
                        printf("deleted\n");
                    }
                    else
                    {
                        temp->right = buffer->right;
                        free(buffer);
                        printf("deleted\n");
                    }
                }
            }else{
            
            	
            	buffer = searchtree(num,head,buffer);
            	temp2=buffer;
            	
            	temp2 = temp2->left;
            	while(temp2->right!=NULL){//makes temp2 node that must replace buffer
            	temp2=temp2->right;
            	}
            	
            	
            	
            	temp = getparent(head,temp2);
            	
            	buffer->data = temp2->data;
            	if(temp->right==temp2){
            	temp->right=NULL;
            	}else{
            	temp->left=NULL;
            	}
            	free(temp2);
            	printf("deleted\n");
            }
        }
    }
    return EXIT_SUCCESS;
}
