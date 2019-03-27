#include<iostream>
using namespace std;
class Node{
	public:
		//store data
		int data;
		//children
		Node *parent;
		Node *left;
		Node *right;
		Node(int value){
			data = value;
			parent = NULL;
			left = NULL;
			right = NULL;	
	}
};
class BiST{
	public:
		Node *root;
		BiST(){
			root = NULL;
		}
		void insert(int value){
			insertHelper(root,value);
		}
		void insertHelper(Node * current, int value){
			//Base case if current is NULL, insert there.
			if(current == NULL){
				current = new Node(value); 
				if (root == NULL) root = current;	
				return;
			}
			 
			/*if (root == NULL){
				root = new Node(value);
			}*/ 
			//Else compare the current data with value
			else if(value <  current->data){
				//If value <current data  ->move left and call insert
				//if left is NULL,insert it.
				if(current->left == NULL)	{
					current->left = new Node(value);
					current->left->parent = current;
				}
				//else move left and call insert
				else insertHelper(current->left , value);
			}
			else{
				//else move right and call insert
				if (current->right == NULL) {
					current->right = new Node(value);
					current->right->parent = current;
				}
				else insertHelper(current->right,value);
			}			
		}
			
		void display(){
			display2(root);
			cout<<endl;
		}
		
		void display2(Node *current){
			//Base condition
			if (current == NULL) return;
			//Display left
			display2(current->left);
			//display current
			cout<<current->data<<" , ";
			//display right
			display2(current->right);
		}
		//searching the node with the given value
		Node * search1(Node * current,int value){
			//if not present or present return current
			if (current == NULL || current->data == value) return current;
			//searching left and right node
			else if(value<current->data){
				return search1(current->left,value);
			}
			else return search1(current->right,value);
		}
		//not found or found
		bool search(int value){
			//if found the node with the given value
			if(search1(root,value)!=NULL) {
				cout<<"found"<<endl;
				return 1;
			}
			//if not
			else {
				cout<<"Not found"<<endl;return 0;	
			}
		}
		//find min
		int find_min(int value){
			//search for a branch
				Node *current = search1(root,value);
			//take the min of that branch
			    Node *min = find_min1(current);
			    cout<<endl;
			    return min->data;
		}
		Node *find_min1(Node *current){
			//find min the recursion
			if(current->left == NULL ){
				return current;	
			}
			else if(current == NULL){
			    return NULL;
			}
			//recursion carried to left
			else return find_min1(current->left);
		}
		

		
		
		//NExt class - Friday
		//int height();
		void deleteNode(int value){
			//search deleting nodee
			Node *current = search1(root,value);
			if(current == NULL){
			    return;
			}
			else{
				//replacing the values
			    if(current->left == NULL){ 
				    replace_at_parent1(current->right,current);
			    }
    			else if(current->right == NULL){ 
    				replace_at_parent1(current->left,current);
    			}
    			else{ 
    			    Node *temp = find_min1(current->right);
    			    if(current == root){
    	                current->data = temp->data;
    	                replace_at_parent1(NULL,temp);
    				    delete temp;
    			    }
    			    else{
    				    replace_at_parent1(temp,current);
    				    temp->parent = current->parent;
    				    temp->left = current->left;
    				    delete temp;
    			    }
    			}
			}
			
		}
		
		void replace_at_parent(int value1,int value2){
			Node *rep = search1(root,value2);
			Node *current = search1(root,value1);
			replace_at_parent1(current,rep);
		}
		void replace_at_parent1(Node *current,Node *rep){
			if(rep == root){
				root = current;	
			}
			else if(current == root){
				return;
			}
			else{
				if(rep->data > rep->parent->data){
				    if(current == NULL){
			            rep->parent->right = NULL;
			        }
			        else{
			            rep->parent->right = current;
    					if(current->data > current->parent->data){
    						current->parent->right = NULL;
    					}
    					else current->parent->left = NULL;
    					current->parent = rep->parent;
			        }
					
				}
				else{
				    if(current == NULL){
			            rep->parent->left = NULL;
			        }
			        else{
			     	rep->parent->left = current;
					if(current->data>current->parent->data){
						current->parent->right = NULL;
					}
					else current->parent->left = NULL;
					current->parent = rep->parent;       
			        }
				
				}
			}
			print2DUtil(root,0);
		}     
		void print2DUtil(Node *root, int space){
			// Base case  
			if (root == NULL)  
			    return;  
			// Increase distance between levels  
			space += 5;  
			// Process right child first  
			print2DUtil(root->right, space);  

			// Print current node after space  
			// count  
			cout<<endl;  
			for (int i = 5; i < space; i++)  
			    	cout<<" ";  
				cout<<root->data<<"\n";  

			// Process left child  
			print2DUtil(root->left, space);  
			}  

			// Wrapper over print2DUtil()  
		void print2D(){  
		        cout << "******************************" << endl;
		        // Pass initial space count as 0  
		        print2DUtil(root, 0);  
		        cout << "******************************" << endl;
                }
		int count(){
			return count2(root);			
		}
		int count2(Node *current){
			if(current == NULL){
				return 0;
			}
			else{
				return count2(current->left) + 1 + count2(current->right);
			}
		}
		int rangeSearch(int k1,int k2){
			return rangeSearch1(root,k1,k2);
		}
		int rangeSearch1(Node*current,int k1,int k2){
			if (current==NULL) return 0; 
			if (current->data == k2 && current->data == k1){ 
				cout<<current->data<<","<<endl;
				return 1;
			}	
			if (current->data <= k2 && current->data >= k1){ 
				cout<<current->data<<",";
				return 1 + rangeSearch1(current->left, k1, k2) + rangeSearch1(current->right, k1, k2); 
			} 
			else if (current->data < k2){ 
				return rangeSearch1(current->right, k1, k2); 
			} 
			
			else {
				cout<<"\n"<<"The range of the given interval is ";
				return rangeSearch1(current->left, k1, k2); 
			}
			
		}
	
};
int main(){
	BiST t1;
	t1.insert(5);
	t1.insert(7);
	t1.insert(6);
	t1.insert(2);
	t1.insert(3);
	t1.insert(1);
	t1.insert(8);
	t1.insert(4);
	t1.insert(9);
	t1.insert(0);	
	t1.print2D();
	cout<<"No of nodes in the binary tree are "<<t1.count()<<endl;
	cout<<t1.rangeSearch(3,8)<<"\n";
	
}
