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
Node* doesExist(Node* current, int value);
void deleteNode(Node* &root, int value);
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
			if (doesExist(root, value) != nullptr){
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
			if (root != nullptr){
				printTree(root, 0);
			}
		}
		else if (command == "SEARCH"){
			//Searches if provided value in list
			int value;
			cout << "Value you are searching for?: " << endl;
			cin >> value;
			if (root != nullptr && doesExist(root, value) != nullptr){
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
Node* doesExist(Node* current, int value){
	if (current->data == value){
		return current;
	}
	else{
		if (value < current->data){
			if (current->left == nullptr){
				return nullptr;
			}
			else{
				return doesExist(current->left, value);
			}
		}
		else{
			if (current->right == nullptr){
				return nullptr;
			}
			else{
				return doesExist(current->right, value);
			}
		}
	}
}

void deleteNode(Node* &root, int value){
	Node* deleteMe = doesExist(root,value);
	if (deleteMe != nullptr){
		//No child case
		if (deleteMe->left == nullptr && deleteMe->right == nullptr){
			if (deleteMe->parent != nullptr){
				replaceNode(deleteMe, nullptr);
			}
			else{
				root = nullptr;
			}
		}
		//One child cases
		else if (deleteMe->right == nullptr){
			Node* successor = deleteMe->left;
			successor->parent = deleteMe->parent;
			if (successor->parent != nullptr){
				replaceNode(deleteMe, successor);
			}
			else{
				root = successor;
			}
		}
		else if (deleteMe->left == nullptr){
			Node* successor = deleteMe->right;
			successor->parent = deleteMe->parent;
			if (successor->parent != nullptr){
				replaceNode(deleteMe, successor);
			}
			else{
				root = successor;
			}
		}
		//Two child case
		else{
			//Get successor
			Node* successor = returnSuccessor(deleteMe);

			//Set successor's parent to not recognize child
			//eraseNodeFromParent(successor);
			replaceNode(successor, nullptr);

			//If there are right nodes of successor, make the right node take successor's place
			if (successor->right != nullptr){
				replaceNode(successor, successor->right);
				successor->right->parent = successor->parent;
				successor->right = nullptr;
			}

			//Put successor into place of current in tree
			successor->parent = deleteMe->parent;
			successor->left = deleteMe->left;
			successor->left->parent = successor;
			if (deleteMe->right != nullptr){
				successor->right = deleteMe->right;
				successor->right->parent = successor;
			}
			else{
				//cout << "successor is direct right of deleted value.";
				successor->right = nullptr;
				//cout << newCurrent->parent->data; //<< " " << newCurrent->left->data << " " << newCurrent->right->data << endl;
			}
			if (successor->parent != nullptr){
				replaceNode(deleteMe,successor);
			}
			else{
				root = successor;
			}
		}
		delete deleteMe;
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
