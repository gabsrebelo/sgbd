/*****B+ Tree*****/
//TODO funcao que le do arquivo de dados
    //subir 819 ids de registros para a mem
    //inserir eles na arvore
    //se for folha aponta para o byte correspondente no arquivo de dados
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<climits>
#include "../data_types/bloco.h"
#include "../data_types/registro.h"
using namespace std;
#define FILENAME "files/hash.bin"
int MAX = 4; //tamanho de cada no
class BPTree;
class Node
{
	bool IS_LEAF;
	int *key, size;
	Node** ptr;
	friend class BPTree;
public:
	Node();
};
class BPTree
{
	Node *root;
	void insertInternal(int,Node*,Node*);
	Node* findParent(Node*,Node*);
public:
	BPTree();
	void search(int);
	void insert(int);
	void display(Node*);
	Node* getRoot();
	void cleanUp(Node*);
    void readFile();
	~BPTree();
};
//give command line argument to load a tree from log
//to create a fresh tree, do not give any command line argument
int main(int argc, char* argv[])
{
	
    BPTree bpt;
    /*
	int x;

    while(true){
        cin>>x;
        if(x == -1)
            bpt.display(bpt.getRoot());
        else
            bpt.insert(x);
    }
    */		
	bpt.readFile();
	return 0;
}
Node::Node()
{
	//alocacao dinamica de memoria
	key = new int[MAX];
	ptr = new Node*[MAX+1];
}
BPTree::BPTree()
{
	root = NULL;
}
void BPTree::search(int x)
{
	//search logic
	if(root==NULL)
	{
		//empty
		cout<<"Tree empty\n";
	}
	else
	{
		Node* cursor = root;
		//in the following while loop, cursor will will travel to the leaf node possibly consisting the key
		while(cursor->IS_LEAF == false)
		{
			for(int i = 0; i < cursor->size; i++)
			{
				if(x < cursor->key[i])
				{
					cursor = cursor->ptr[i];
					break;
				}
				if(i == cursor->size - 1)
				{
					cursor = cursor->ptr[i+1];
					break;
				}
			}
		}
		//in the following for loop, we search for the key if it exists
		for(int i = 0; i < cursor->size; i++)
		{
			if(cursor->key[i] == x)
			{
				cout<<"Found\n";
				return;
			}
		}
		cout<<"Not found\n";
	}
}
void BPTree::insert(int x)
{
	if(root==NULL)
	{
		root = new Node;
		root->key[0] = x;
		root->IS_LEAF = true;
		root->size = 1;
		cout<<"Created root\nInserted "<<x<<" successfully\n";
	}
	else
	{
		Node* cursor = root;
		Node* parent;
        //ir ate o no folha
		while(cursor->IS_LEAF == false)
		{
			parent = cursor;
			for(int i = 0; i < cursor->size; i++)
			{
				if(x < cursor->key[i])
				{
					cursor = cursor->ptr[i];
					break;
				}
				if(i == cursor->size - 1)
				{
					cursor = cursor->ptr[i+1];
					break;
				}
			}
		}
        //aqui o cursor esta no nó folha onde deve ser inserido a chave
		if(cursor->size < MAX)
		{
            //se o no não estiver cheio, encontra a posicao correta
			int i = 0;
			while(x > cursor->key[i] && i < cursor->size) i++;
			//make space for new key
			for(int j = cursor->size;j > i; j--)
			{
				cursor->key[j] = cursor->key[j-1];
			}
			cursor->key[i] = x;
			cursor->size++;
			cursor->ptr[cursor->size] = cursor->ptr[cursor->size-1];
			cursor->ptr[cursor->size-1] = NULL;
			cout<<"Inserted "<<x<<" successfully\n";
		}
		else
		{
			cout<<"Inserted "<<x<<" successfully\n";
			cout<<"Overflow in leaf node!\nSplitting leaf node\n";
			//overflow e cria nova folha
			Node* newLeaf = new Node;
            //cria um nó virtual e insere x nele
			int virtualNode[MAX+1];
			for(int i = 0; i < MAX; i++)
			{
				virtualNode[i] = cursor->key[i];
			}
			int i = 0, j;
			while(x > virtualNode[i] && i < MAX) i++;
			//espaço para a nova chave
			for(int j = MAX+1;j > i; j--)
			{
				virtualNode[j] = virtualNode[j-1];
			}
			virtualNode[i] = x; 
			newLeaf->IS_LEAF = true;
			//separa em duas folhas
			cursor->size = (MAX+1)/2;
			newLeaf->size = MAX+1-(MAX+1)/2;
			//cursor aponta para a nova folha
			cursor->ptr[cursor->size] = newLeaf;
			newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
			cursor->ptr[MAX] = NULL;
            //coloca elementos nas novas folhas
			for(i = 0; i < cursor->size; i++)
			{
				cursor->key[i] = virtualNode[i];
			}
			for(i = 0, j = cursor->size; i < newLeaf->size; i++, j++)
			{
				newLeaf->key[i] = virtualNode[j];
			}
			//modifica o pai
			if(cursor == root)
			{
				//se cursor ja for uma raiz, entao cria uma nova raiz
				Node* newRoot = new Node;
				newRoot->key[0] = newLeaf->key[0];
				newRoot->ptr[0] = cursor;
				newRoot->ptr[1] = newLeaf;
				newRoot->IS_LEAF = false;
				newRoot->size = 1;
				root = newRoot;
				cout<<"Created new root\n";
			}
			else
			{
				//insere no nó pai
				insertInternal(newLeaf->key[0],parent,newLeaf);
			}
		}
	}
}
void BPTree::insertInternal(int x, Node* cursor, Node* child)
{
	if(cursor->size < MAX)
	{
        //se nao estiver cheio, encontrar a posicao correta da chave
		int i = 0;
		while(x > cursor->key[i] && i < cursor->size) i++;
        //espaço para a nova chave
		for(int j = cursor->size;j > i; j--)
		{
			cursor->key[j] = cursor->key[j-1];
		}
        //espaço para o novo ponteiro
		for(int j = cursor->size+1; j > i+1; j--)
		{
			cursor->ptr[j] = cursor->ptr[j-1];
		}
		cursor->key[i] = x;
		cursor->size++;
		cursor->ptr[i+1] = child;
		cout<<"Inserted key in an Internal node successfully\n";
	}
	else
	{
		cout<<"Inserted key in an Internal node successfully\n";
		cout<<"Overflow in internal node!\nSplitting internal node\n";
        //se overflow, entao cria um novo nó interno
		Node* newInternal = new Node;
        //cria nó interno virtual
		int virtualKey[MAX+1];
		Node* virtualPtr[MAX+2];
		for(int i = 0; i < MAX; i++)
		{
			virtualKey[i] = cursor->key[i];
		}
		for(int i = 0; i < MAX+1; i++)
		{
			virtualPtr[i] = cursor->ptr[i];
		}
		int i = 0, j;
		while(x > virtualKey[i] && i < MAX) i++;
		for(int j = MAX+1;j > i; j--)
		{
			virtualKey[j] = virtualKey[j-1];
		}
		virtualKey[i] = x; 
		for(int j = MAX+2;j > i+1; j--)
		{
			virtualPtr[j] = virtualPtr[j-1];
		}
		virtualPtr[i+1] = child; 
		newInternal->IS_LEAF = false;
		cursor->size = (MAX+1)/2;
		newInternal->size = MAX-(MAX+1)/2;
		for(i = 0, j = cursor->size+1; i < newInternal->size; i++, j++)
		{
			newInternal->key[i] = virtualKey[j];
		}
		for(i = 0, j = cursor->size+1; i < newInternal->size+1; i++, j++)
		{
			newInternal->ptr[i] = virtualPtr[j];
		}
		// m = cursor->key[cursor->size]
		if(cursor == root)
		{
			Node* newRoot = new Node;
			newRoot->key[0] = cursor->key[cursor->size];
			newRoot->ptr[0] = cursor;
			newRoot->ptr[1] = newInternal;
			newRoot->IS_LEAF = false;
			newRoot->size = 1;
			root = newRoot;
			cout<<"Created new root\n";
		}
		else
		{
			insertInternal(cursor->key[cursor->size] ,findParent(root,cursor) ,cursor);
		}
	}
}
Node* BPTree::findParent(Node* cursor, Node* child)
{
	Node* parent;
	if(cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF)
	{
		return NULL;
	}
	for(int i = 0; i < cursor->size+1; i++)
	{
		if(cursor->ptr[i] == child)
		{
			parent = cursor;
			return parent;
		}
		else
		{
			parent = findParent(cursor->ptr[i],child);
		}
	}
	return parent;
}

void BPTree::display(Node* cursor)
{
	//depth first display
	if(cursor!=NULL)
	{
		for(int i = 0; i < cursor->size; i++)
		{   
            cout<<cursor->key[i]<<" ";
		}
		cout<<"\n";
		if(cursor->IS_LEAF != true)
		{
			for(int i = 0; i < cursor->size+1; i++)
			{
				display(cursor->ptr[i]);
			}
		}
	}
}
Node* BPTree::getRoot()
{
	return root;
}
void BPTree::cleanUp(Node* cursor)
{
	if(cursor!=NULL)
	{
		if(cursor->IS_LEAF != true)
		{
			for(int i = 0; i < cursor->size+1; i++)
			{
				cleanUp(cursor->ptr[i]);
			}
		}
		for(int i = 0; i < cursor->size; i++)
		{
			cout<<"Deleted key from memory: "<<cursor->key[i]<<"\n";
		}
		delete[] cursor->key;
		delete[] cursor->ptr;
		delete cursor;
	}
}
BPTree::~BPTree()
{
	//calling cleanUp routine
	cleanUp(root);
}

void BPTree::readFile(){
    ifstream file_obj;
    file_obj.open(FILENAME, ios::in);
    Bloco bloco;
    Registro reg[2];
    BPTree bpt;

    while (!file_obj.eof()) { 
        //le um bloco do arquivo de dados e insere os registros na arvore
        file_obj.read((char*)&bloco, sizeof(bloco));
        for(int i=0; i<2; i++){
            reg[i]= bloco.registros[i];
            bpt.insert(reg[i].id);
        }        
    }
    //bpt.display(bpt.getRoot());
}