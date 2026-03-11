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

void addNode(Node* &root, Node* &newNode);
bool doesExist(Node* current, int value);
void deleteNode(Node* &current, int value);
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
				cout << "somethin" << endl;
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
			cout << root->data << " " << root->left->data << " " << root->right->data << endl;
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

void deleteNode(Node* &current, int value){
	if (current->data == value){
		//delete
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
Node* returnSuccessor(Node* original){
	Node* current = original->right;
	while (current->left != nullptr){
		current = current->left;
	}
	return current;
}
