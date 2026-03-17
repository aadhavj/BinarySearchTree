#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
using namespace std;


struct Node {
	int data;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

void printTree(Node* root, int depth);
void addNode(Node* &root, Node* &newNode);
bool doesExist(Node* current, int value);
void deleteNode(Node* current, int value);
void eraseNodeFromParent(Node* current);
void replaceNode(Node* current, Node* replacingNode);
Node* returnSuccessor(Node* original);


int main(){
	
	//Basic var instantiation
	string command;
	Node* root = nullptr;
	bool runProgram = true;


	while (runProgram){
		cout << "\nEnter Command(DELETE, SEARCH, ADD, PRINT, ADDF, QUIT): ";
		cin >> command;
		
		//Command recognition
		if (command == "DELETE"){
			int value;
			cout << "What value do you want to delete?: ";
			cin >> value;
			if (doesExist(root, value)){
				deleteNode(root, value);
			}
			else{
				cout << "Cannot delete value that does not exist" << endl;
			}
		}
		else if (command == "ADD"){

			//Get value
			int value;
			cout << "Value: ";
			cin >> value;

			//Create node
			Node* addMe = new Node();
			addMe->data = value;

			//Push to tree
			addNode(root, addMe);
		}
		else if (command == "ADDF"){
			//Adds file
			string fileName;
			cout << "Please enter filename: " << endl;
			cin >> fileName;
			
			ifstream numFile(fileName);

			if (!numFile) {
				cout << "Invalid file name." << endl;
			}
			else{
				int number;
				while (numFile >> number) {
					Node* addMe = new Node();
					addMe->data = number;
					addNode(root, addMe);
				}
				numFile.close();
			}

		}
		else if (command == "PRINT"){
			printTree(root, 0);
		}
		else if (command == "SEARCH"){
			//Searches if provided value in list
			int value;
			cout << "Value you are searching for?: " << endl;
			cin >> value;
			if (doesExist(root, value)){
				cout << "Node with that value exists." << endl;
			}
			else{
				cout << "Node with that value dosen't exist" << endl;
			}
		}
		else if (command == "QUIT"){
			//Exits search tree
			runProgram = false;
		}
		else{
			cout << "Command not recognized" << endl;
		}
	}

	return 0;
}
void printTree(Node* current, int depth){
	Node* left = current->left;
	Node* right = current->right;
	if (right != nullptr){
		printTree(right,depth+1);
	}
	for (int i = 0;i< depth;i++){
		cout << "\t";
	}
	if (current != nullptr){
		cout << current->data << endl;
	}
	if (left != nullptr){
		printTree(left, depth+1);
	}
}

void addNode(Node* &root, Node* &newNode){
	if (root == nullptr){
		root = newNode;
	}
	else{
		Node* current = root;
		if (newNode->data <= current->data){
			if (current->left == nullptr){
				current->left = newNode;
				newNode->parent = current;
			}
			else{
				addNode(current->left, newNode);
			}
		}
		else{
			if (current->right == nullptr){
				current->right = newNode;
				newNode->parent = current;
			}
			else{
				addNode(current->right, newNode);
			}
		}
	}
}
bool doesExist(Node* current, int value){
	if (current->data == value){
		return true;
	}
	else{
		if (value < current->data){
			if (current->left == nullptr){
				return false;
			}
			else{
				return doesExist(current->left, value);
			}
		}
		else{
			if (current->right == nullptr){
				return false;
			}
			else{
				return doesExist(current->right, value);
			}
		}
	}
}

void deleteNode(Node* current, int value){
	if (current->data == value){
		//No child case
		if (current->left == nullptr && current->right == nullptr){
			eraseNodeFromParent(current);
		}
		//One child cases
		else if (current->right == nullptr){
			Node* newCurrent = current->left;
			newCurrent->parent = current->parent;
			replaceNode(current, newCurrent);
		}
		else if (current->left == nullptr){
			Node* newCurrent = current->right;
			newCurrent->parent = current->parent;
			replaceNode(current, newCurrent);
		}
		//Two child case
		else{
			//Get successor
			Node* newCurrent = returnSuccessor(current);

			//Set successor's parent to not recognize child
			eraseNodeFromParent(newCurrent);

			//If there are right nodes of successor, make the right node take successor's place
			if (newCurrent->right != nullptr){
				replaceNode(newCurrent, newCurrent->right);
				newCurrent->right->parent = newCurrent->parent;
				newCurrent->right = nullptr;
			}

			//Put successor into place of current in tree
			newCurrent->parent = current->parent;
			newCurrent->left = current->left;
			newCurrent->left->parent = newCurrent;
			if (current->right != nullptr){
				newCurrent->right = current->right;
				newCurrent->right->parent = newCurrent;
			}
			else{
				//cout << "successor is direct right of deleted value.";
				newCurrent->right = nullptr;
				//cout << newCurrent->parent->data; //<< " " << newCurrent->left->data << " " << newCurrent->right->data << endl;
			}
			replaceNode(current,newCurrent);
		}
		//delete current;
	}
	else{
		if (value <= current->data){
			deleteNode(current->left, value);
		}
		else{
			deleteNode(current->right, value);
		}
	}
	
}
void eraseNodeFromParent(Node* current){
	if (current->data <= current->parent->data){
		current->parent->left = nullptr;
	}
	else{
		current->parent->right = nullptr;
	}
}
void replaceNode(Node* current, Node* replacingNode){
	if (current->data <= current->parent->data){
		current->parent->left = replacingNode;
	}
	else{
		current->parent->right = replacingNode;
	}
}
Node* returnSuccessor(Node* original){
	Node* current = original->right;
	while (current->left != nullptr){
		current = current->left;
	}
	return current;
}
