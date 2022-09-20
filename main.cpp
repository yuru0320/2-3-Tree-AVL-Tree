// DS ex.2 0405
// �� 16 �� ��T�G�A 10827234 �^�ۺ� &&�@10827242 ��౯�

#include <iostream> 	// cout, endl
#include <fstream> 		// open, is_open, close, ignore
#include <string.h>
#include <vector> 		// vector, push_back
#include <cstdlib> 		// system, atoi
#define PTR_NUM 3
#define KEY_NUM PTR_NUM-1
using namespace std;

struct File {
public:
	string rawLine; 	// raw data of one record
	int index; 		// ex: [1] 256
	string school;		// �ǮզW�� 
	string department;	// ��t�W��
	string dayOrNight;	// ��]�O 
	string level;		// �ŧO 
	int stdNum;			// number of student
};

typedef struct schoolN {
	string schoolName;
	vector<int> vIndex;	// �Ӧs�@�ӥH�W ��ƪ�index 
							// ����n�L��ƪ��ɭԦA���index �L�X������
} schoolN;

typedef struct twoTheeTreeNodes {
	twoTheeTreeNodes* parent;
	schoolN data[KEY_NUM];			// 2 * key
	// twoTheeTreeNodes * link[PTR_NUM] ;
	twoTheeTreeNodes* left = NULL; 	// 3 * ptr
	twoTheeTreeNodes* mid = NULL;
	twoTheeTreeNodes* right = NULL;
	twoTheeTreeNodes* temp = NULL;
}tttNodes;

typedef struct bT {
	schoolN slot;	// a pair of (record id,
	tttNodes* link; // a pointer to a child on the right
}blockType;

struct node  {
	vector<int> index;
	vector<string> department;
    node *left;
	node *right;
	node *parent;
} ;

class twoThreeTree {
public:
	vector<schoolN> vSort;
	tttNodes* root;
	tttNodes* cur;
	void insertNode(schoolN* newSlot);	// �̧ǱN��ƴ��J 2-3�� 
	tttNodes* createNode(tttNodes* left, tttNodes* right, tttNodes* parent, schoolN* newSlot);	// �y 
	void findLeaf(string school);		// ��� Leaf ����m 
	void bubbleSort();
	void splitLeaf(schoolN* newSlot, blockType& blockUp);
	tttNodes* createRoot(tttNodes* leftChild, tttNodes* rightChild, schoolN* blockUpSlot);
	void insertNonleaf(blockType blockUp);
	void splitNonleaf(blockType& blockUp);
	void print(vector<File>& vTemp);		// �L�X���G 
};

typedef node* nodeptr;
class AVLTree {
	public:
		void AVL();
		nodeptr head = NULL;
		nodeptr t = NULL;
		nodeptr temp = NULL;
		bool BF( nodeptr ); 
		int height(nodeptr);
        int rotate_A ;
        int rotate_B  ;
        nodeptr LL( nodeptr );
        nodeptr LR( nodeptr );
        nodeptr RR( nodeptr );
        nodeptr RL( nodeptr );
};

string gNum;	// �s�ɮ׼Ʀr eg.101,102,103..... 
char buffer[200];	// �sŪ�i�ɮת� "�@��" ��� 

bool readFile(vector<File>& temp, int file);	// �B�zŪ�� 
int processingNum(char Num[]); // �B�z�����o�� "1,234" ���F�F �ন��ƨæ^��
void seperateData(vector<File>& temp);

// **************************************************************************** 
// *****************       Build a 2-3 Tree & AVL Tree      *******************           
// **************************************************************************** 

int main(void) {
	int command = 0; 			// user command
	int cc = 0, i = 0, j = 0;
	vector<File> vData_1; 		// vData_1 ����input file �����(���|��ʥL)
	twoThreeTree TTTItem;
	AVLTree AVLItem;
  	bool m1 = false;
	do {
		cout << endl << "*** Search Tree Utilities **";
		cout << endl << "* 0. QUIT                  *";
		cout << endl << "* 1. Build 2-3 tree        *";
		cout << endl << "* 2. Build AVL tree        *";
		cout << endl << "* 3. Unavailable           *";
		cout << endl << "****************************";
		cout << endl << "Input a choice(0, 1, 2, 3): ";
		cin >> command; // get a command

		/* ��l�� */	TTTItem.vSort.clear(), cc = 0;

		switch (command) {
		case 1:
			vData_1.clear();
			if (readFile(vData_1, 1)) { 	// read records from a file				
				cc = vData_1.size();
				seperateData(vData_1);		// �N�@����Ƥ��ΥX�� 
				TTTItem.cur = NULL;
				TTTItem.root = NULL;

				/* code */

				for (i = 0; i < vData_1.size(); i++) {
					TTTItem.cur = TTTItem.root;
					schoolN* temp = new schoolN();
					temp->schoolName = vData_1[i].school;
					temp->vIndex.push_back(vData_1[i].index);
					TTTItem.insertNode(temp);
				} // end for()

				TTTItem.print(vData_1);

			} // end if
			m1 = true;
			break;

		case 2:
			if(!m1) {
    			cout << "### Choose 1 first. ###\n";
    			break;
			}
			else{
				m1=false;
				int i = 0, j = 0;
				bool finishInsert = false; 
				bool rotate = false;
				AVLItem.head =NULL;
				AVLItem.t =NULL;
				AVLItem.temp =NULL;
				while( i < vData_1.size() ) {
					if( AVLItem.head == NULL ) { //�Ū�TREE 
						AVLItem.t = new node;
        				AVLItem.t->department.push_back(vData_1[i].department);
        				AVLItem.t->index.push_back(vData_1[i].index);
						AVLItem.head = AVLItem.t; //���Y�w�� (������)
						AVLItem.t->parent = NULL;
						AVLItem.t->right = NULL;
						AVLItem.t->left = NULL;
					}
					else{
						finishInsert = false;
						bool same = false; 
						AVLItem.t = AVLItem.head;
						while( !finishInsert ){
							if( AVLItem.t->department[0] > vData_1[i].department  && AVLItem.t->left == NULL) { // AVLItem.t->department bigger 
								//push leftTree	
								AVLItem.t->left= new node;
            					AVLItem.t->left->department.push_back(vData_1[i].department);
            					AVLItem.t->left->index.push_back(vData_1[i].index);
            					AVLItem.temp = AVLItem.t;
            					AVLItem.t = AVLItem.t->left;
            					AVLItem.t->parent = AVLItem.temp;
								AVLItem.t->right = NULL;
								AVLItem.t->left = NULL;
								finishInsert = true;
							}
							else if(AVLItem.t->department[0] < vData_1[i].department &&  AVLItem.t->right == NULL ) {
								AVLItem.t->right = new node;
            					AVLItem.t->right->department.push_back(vData_1[i].department);
            					AVLItem.t->right->index.push_back(vData_1[i].index);
            					AVLItem.temp = AVLItem.t;
            					AVLItem.t = AVLItem.t->right;
            					AVLItem.t->parent = AVLItem.temp;
								AVLItem.t->right = NULL;
								AVLItem.t->left = NULL;
								finishInsert = true;
							}
							else if( AVLItem.t->department[0] == vData_1[i].department  ) {
								AVLItem.t->department.push_back(vData_1[i].department);
            					AVLItem.t->index.push_back(vData_1[i].index);
            					finishInsert = true;
            					same = true;
							}
							else if( AVLItem.t->department[0] > vData_1[i].department && AVLItem.t->left != NULL ){
								AVLItem.t = AVLItem.t->left;
							}
							else if( AVLItem.t->department[0] < vData_1[i].department && AVLItem.t->right != NULL ){
								AVLItem.t = AVLItem.t->right;
							}
							if( finishInsert&& !same ){
								while( !rotate ){
									if( AVLItem.t->parent->parent== NULL) {
										rotate = true;
									}
									else {
										rotate = AVLItem.BF(AVLItem.t->parent);
										AVLItem.t = AVLItem.t->parent; 
									}
									if(rotate) break;
								}
								rotate = false; 
							}
							
						}//while
						
					}//else
					i++;
				}//while

			} // end if
			i=0;
			i = AVLItem.height(AVLItem.head);
			cout << "Tree height = "<<i<<endl;
  			i=0;
  			j = 1;
  			while( i <AVLItem.head->department.size()){
  				cout <<j<<": "<<"["<<AVLItem.head->index[i]<<"] "<< vData_1[AVLItem.head->index[i]-1].school
				     <<", "<<vData_1[AVLItem.head->index[i]-1].department<<", "
				     <<vData_1[AVLItem.head->index[i]-1].dayOrNight<<", "<<vData_1[AVLItem.head->index[i]-1].level
					 <<", "<<vData_1[AVLItem.head->index[i]-1].stdNum<<endl;
  				i++;
  				j++;
			}
			break;

		case 3:

			break;

		case 0: cout << "Quit the program !" << endl; break;
		default: cout << endl << "Command does not exist!" << endl;
		} // end switch( command )

	} while (command != 0);

	system("pause");
	return 0;
} // end main()

// ====================��MAIN()��====================

bool readFile(vector<File>& temp, int option) { // read records from a file
	string fileName = "";
	fstream input;
	int cc = 0;
	while (1) {
		cout << endl << "Input a file number ([0] Quit): ";
		cin >> gNum;

		if ( gNum == "0" ) // quit
			return false;
		if (option == 1)
			fileName = "input";
		fileName = fileName + gNum;
		fileName = fileName + ".txt";
		input.open(fileName.c_str(), ios::in);

		if (!input) { // �䤣���ɮ�!
			if (option == 1)
				cout << endl << "### input" << gNum << ".txt does not exist! ###" << endl;
		} // if
		else {
			for (int i = 0; i < 3; i++) // Ū���e�T�� 
				input.getline(buffer, sizeof(buffer), '\n'); // �H'\n' �_�y
			while (!input.eof()) {	// �٨SŪ�� 
				File* file = new File();
				temp.push_back(*file); 	// �Ф@�ӷs��File���� �ë���s��vector�᭱ 
				input.getline(buffer, sizeof(buffer), '\n'); // Ū��� �s��buffer  �H'\n' �_�y
				temp[cc].rawLine = buffer; 	// �Nbufer �ƻs�� File ����rawLine
				 // �Ω�p��vector���@���h�֭ӪF�� 

				if (temp[cc].rawLine.length() == 0)
					temp.pop_back();
				cc++;
			} // while() �N��Ʀs�Jvector�� 

			input.close();
			return true;
		} // else 
	} // while

	return false; // return �᭫�s��Jcommand 
} // readInputFile() 

int processingNum(char Num[]) { // �B�z�����o�� "1,234" ���F�F �ন��ƨæ^�� 
	int temp = 0;
	for (int i = 0; i < strlen(Num); i++) {
		if (Num[i] >= '0' && '9' >= Num[i]) 	// ���Ʀr 
			temp = temp * 10 + Num[i] - '0'; 	// ascii code 0 == 48	
	} // for()

	return temp;
} // processingNum()

void seperateData(vector<File>& temp) {
	int index = 0, option = 1;
	char data[200];
	char buff[10] = "";		// �s index
	char aLine[200] = "";

	for (int j = 0; j < temp.size(); j++) {
		index = 0;
		option = 1;
		//strcpy_s( aLine , temp[j].rawLine.c_str() ); // �N�r���ন�r���}�C ��K���θ�� 
		strcpy( aLine, temp[j].rawLine.c_str() ) ; // �N�r���ন�r���}�C ��K���θ�� 
		for (int i = 0; i < sizeof(aLine); i++) { //�N�}�C���Φ��r��}�C
			if (aLine[i] == '\t') {               //�H�Ů�@�����j��

				// �sdata
				switch (option) {
				case 2: // �ǮզW��
					temp[j].school = data;
					break;
				case 4: // ��t�W��
					temp[j].department = data;
					break;
				case 5: // ��]
					temp[j].dayOrNight = data;
					break;
				case 6: // �ŧO 
					temp[j].level = data;
					break;

				case 7: // �ǥͼ� 
					temp[j].stdNum = processingNum(data); // �N�}�C���r���B�z���Ʀr
					temp[j].index = j + 1;
					break;
				default: break;
				} // switch()

				for (int d = 0; d < 200; d++)
					data[d] = '\0';

				option++;
				index = 0;
				continue;
			} // end if()

			data[index++] = aLine[i];  //�N���Φn���r����K�Ʋո� 

		} // end 2for()

		for (int z = 0; z < 200; z++)
			aLine[z] = '\0';
	} // end 1for()

	return;
} // seperateData()

void twoThreeTree::insertNode(schoolN* temp) {
	int keySize = -1;

	if (root == NULL) { // root ==NULL �N root ���V�@�� node 
		root = twoThreeTree::createNode(NULL, NULL, NULL, temp); // �y�s�`�I �ó]�wroot 
	} // if ()
	else {
		twoThreeTree::findLeaf(temp->schoolName);
		blockType blockUp; // a data block received from a split
		// insert

		//cout << cur ->data[0].schoolName ;
		if (cur->data[1].schoolName == "") {	// 2 node
			if (cur->data[0].schoolName.compare(temp->schoolName) == 0) {	// �P�զW
				cur->data[0].vIndex.push_back(temp->vIndex[0]);
			} // if()
			else { // �զW���P ����j�p�� �����s�i�`�I INsertLeaf

				if (temp->schoolName.compare(cur->data[0].schoolName) < 0) { // �n�s�J�r����p
					cur->data[1].vIndex.assign(cur->data[0].vIndex.begin(), cur->data[0].vIndex.end()); // �N�쥻����Ʋ���ĤG�Ӧ�m 
					cur->data[0].vIndex.clear();
					cur->data[1].schoolName = cur->data[0].schoolName;
					cur->data[0].schoolName = temp->schoolName;	// �s�J���
					cur->data[0].vIndex.push_back(temp->vIndex[0]);
				} // if	
				else {
					cur->data[1].schoolName = temp->schoolName;	// �s�J���
					cur->data[1].vIndex.push_back(temp->vIndex[0]);
				} // else
			} // else

		} // if

		else {	// 3 node  
			if (cur->data[0].schoolName.compare(temp->schoolName) == 0) {	// �P�զW
				cur->data[0].vIndex.push_back(temp->vIndex[0]);
				return;
			} // if()
			else if (cur->data[1].schoolName.compare(temp->schoolName) == 0) {	// �P�զW
				cur->data[1].vIndex.push_back(temp->vIndex[0]);
				return;
			} // if()

			else { // splitLeaf
				twoThreeTree::splitLeaf(temp, blockUp);

				if (cur->parent == NULL) {
					root = twoThreeTree::createRoot(cur, blockUp.link, &blockUp.slot);
				} // if
				else {
					do {
						cur = cur->parent;
						if (cur->data[1].vIndex.size() == 0) { // at least one (rightmost) unused slot
							twoThreeTree::insertNonleaf(blockUp); 	// add a slot into a non leaf
							break; 	// finish the
						} // if
						else {
							twoThreeTree::splitNonleaf(blockUp); // split a non leaf for an insertion
							if (cur->parent == NULL) {
								root = twoThreeTree::createRoot(cur, blockUp.link, &blockUp.slot);
								break;
							} // if()
						} // else

					} while (true);

				} // else
			} // else
		} // else
	} // else

	//cout << cur->data.at(0) << endl ;
}	// twoThreeTree::insertNode( char school[] )

tttNodes* twoThreeTree::createNode(tttNodes* left, tttNodes* right, tttNodes* parent, schoolN* newSlot) {
	// intput: left child, right child, parent, a new record kept as a slot
	// output: a new created node or NULL
	tttNodes* newNode = NULL;

	try {
		newNode = new tttNodes;// create a new node
		newNode->data[0].schoolName = newSlot->schoolName; // put the record into the 1st slot
		newNode->data[1].schoolName = "";
		newNode->data[0].vIndex = newSlot->vIndex;
		newNode->data[1].vIndex.clear();
		newNode->parent = parent;	// set up a link to the parent
		newNode->left = left;		// set up the leftmost link
		newNode->mid = NULL;		// clear up the middle link
		newNode->right = right;	// set up the rightmost link
		newNode->temp = NULL;		// clear up the temp link
	} // end try
	catch (std::bad_alloc& ba) { // unable to allocate space
		std::cerr << endl << "bad_alloc caught: " << ba.what() << endl;
	} // end catch

	return newNode; // pass a pointer to the new created node
} // end createNode

void twoThreeTree::findLeaf(string school) {
	tttNodes* temp = root ;
	tttNodes* pre = temp ;

	while ( temp != NULL ) { // have not found leaf
		if (temp->data[1].schoolName == "") {	// 2 node

			if (temp->data[0].schoolName.compare(school) == 0) {	// �P�զW
				pre = temp;
				break;
			} // if
			else if (temp->data[0].schoolName.compare(school) > 0) { // �s��Ƹ��p �����l�𨫳X 
				pre = temp;
				temp = temp->left;
			} // else if
			else {
				pre = temp;
				temp = temp->right;
			} // else
		} // if

		else {
			if (temp->data[0].schoolName.compare(school) == 0) {
				pre = temp;
				break;
			} // if
			else if (temp->data[1].schoolName.compare(school) == 0) {
				pre = temp;
				break;
			} // else if
			else if (temp->data[0].schoolName.compare(school) > 0) { // �s��Ƹ��p �����l�𨫳X 
				pre = temp;
				temp = temp->left;
			} // else if
			else if (temp->data[0].schoolName.compare(school) < 0 &&
					 temp->data[1].schoolName.compare(school) > 0) {
				// �s��ƮզW ����key�j &&  ���kkey�p �������l�𨫳X
				pre = temp;
				temp = temp->mid;
			} // else if
			else {
				pre = temp;
				temp = temp->right;
			} // else
		} // else
	} // while()

	cur = pre; // �X�j��N�� ��� LEAF 
	return;
} // twoThreeTree::findLeaf()

void twoThreeTree::splitLeaf(schoolN* newSlot, blockType& blockUp) {
	vSort.clear();
	vSort.push_back(cur->data[0]);
	vSort.push_back(cur->data[1]);
	vSort.push_back(*newSlot);

	twoThreeTree::bubbleSort();
	cur->data[0] = vSort[0];			// set��`�I 
	cur->data[1].schoolName = "";
	cur->data[1].vIndex.clear(); 	// clear data[1] 

	blockUp.link = twoThreeTree::createNode(NULL, NULL, cur->parent, &vSort[2]); // �b�k�s�y�@�� sibling�`�I 

	blockUp.slot.schoolName = vSort[1].schoolName; // block to move upwards
	blockUp.slot.vIndex = vSort[1].vIndex;
} // splitLeaf()

tttNodes* twoThreeTree::createRoot(tttNodes* leftChild, tttNodes* rightChild, schoolN* blockUpSlot) {
	tttNodes* newRoot = createNode(leftChild, rightChild, NULL, blockUpSlot);

	leftChild->parent = newRoot; 	// set their parent as the new root
	rightChild->parent = newRoot;

	return newRoot;
} // createRoot()

void twoThreeTree::insertNonleaf(blockType blockUp) {

	if (blockUp.slot.schoolName.compare(cur->data[0].schoolName) > 0) { // �nsplit�I�bright
		cur->data[1].schoolName = blockUp.slot.schoolName;	// set blockUp data into right slot 
		cur->data[1].vIndex = blockUp.slot.vIndex;
		cur->mid = cur->right;		// link mid ptr to ���p���`�I( �쥻right�ҫ� 
		cur->right = blockUp.link; 	// �N�kptr �s�W���j���`�I( blockUp�� 
	} // if
	else { // �nsplit�I�bleft
		cur->data[1].schoolName = cur->data[0].schoolName;	// blockUp data �p��쥻�������� 
		cur->data[1].vIndex = cur->data[0].vIndex;			// �N��Ʋ���k�� 
		cur->data[0].schoolName = blockUp.slot.schoolName;	// set blockUp data into right slot 
		cur->data[0].vIndex = blockUp.slot.vIndex;
		cur->mid = blockUp.link; // link mid ptr to split slot
	} // else

}  // insertNonleaf()

void twoThreeTree::splitNonleaf(blockType& blockUp) {
	blockType blockUpTemp = blockUp;
	vSort.clear();
	vSort.push_back(cur->data[0]);
	vSort.push_back(cur->data[1]);
	vSort.push_back(blockUpTemp.slot);
	twoThreeTree::bubbleSort();

	if (blockUpTemp.slot.schoolName.compare(cur->data[1].schoolName) > 0) { // �nsplit�I�bright
		cur->temp = blockUpTemp.link; //�̤j���`�I

	} // if
	else if (blockUpTemp.slot.schoolName.compare(cur->data[1].schoolName) < 0 &&
		blockUpTemp.slot.schoolName.compare(cur->data[0].schoolName) > 0) { // split�I�b mid 
		cur->temp = cur->right;
		cur->right = blockUpTemp.link; // �˼ƲĤG�j���`�I  	
	} // else if 
	else { // �nsplit�I�bleft
		cur->temp = cur->right;
		cur->right = cur->mid;
		cur->mid = blockUpTemp.link; // �˼ƲĤT�j���`�I  	
	} // else

	blockUp.link = twoThreeTree::createNode(cur->right, cur->temp, cur->parent, &vSort[2]); // �b�k�s�y�@�� sibling�`�I 
	cur->temp->parent = blockUp.link;
	cur->right->parent = blockUp.link;

	cur->data[0] = vSort[0];			// set��`�I 
	cur->data[1].schoolName = "";
	cur->data[1].vIndex.clear(); 	// clear data[1] 

	blockUp.slot.schoolName = vSort[1].schoolName; // block to move upwards
	blockUp.slot.vIndex = vSort[1].vIndex;
	
	cur->right = cur->mid;
	cur->mid = NULL;
	cur->temp = NULL;

} // splitNonleaf()

void twoThreeTree::bubbleSort() {
	schoolN temp;
	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 3; j++) {
			if (vSort.at(i).schoolName.compare(vSort.at(j).schoolName) > 0) { // �� compare ���i��strcmp 
				temp = vSort.at(i);
				vSort.at(i) = vSort.at(j);
				vSort.at(j) = temp;
			} // if() 
		} // for2
	} // for1

	return;
} // twoThreeTree::bubbleSort()


void twoThreeTree::print(vector<File>& vTemp) {
	//int keySize = root->data.size() ;
	vector<File> vPrint;
	int tempIndex = -1, i = 0, count = 1, height = 0;
	tttNodes* tempPtr = root;
	while (tempPtr != NULL) {
		height++;
		tempPtr = tempPtr->left;
	} // while
		
	cout << "Tree height = " << height << endl;

	for (i = 0; i < root->data[0].vIndex.size(); i++) {
		tempIndex = root->data[0].vIndex[i] - 1;
		vPrint.push_back(vTemp[tempIndex]);
	} // for

	if (root->data[1].schoolName != "") {
		for (i = 0; i < root->data[1].vIndex.size(); i++) {
			tempIndex = root->data[1].vIndex[i] - 1;
			vPrint.push_back(vTemp[tempIndex]);
		} // for
	} // if()

	File temp;
	for ( i = 0; i < vPrint.size(); i++) {
		for (int j = i + 1; j < vPrint.size(); j++) {
			if (vPrint.at(i).index > vPrint[j].index ) { // �� compare ���i��strcmp 
				temp = vPrint.at(i);
				vPrint.at(i) = vPrint.at(j);
				vPrint.at(j) = temp;
			} // if() 
		} // for2
	} // for1

	 // ��X�̷ӧǸ��ƪ����
	for (i = 0; i < vPrint.size(); i++) {
		cout << count << ": " << "[" << vPrint[i].index << "] " << vPrint[i].school << ", "
			<< vPrint[i].department << ", " << vPrint[i].dayOrNight << ", "
			<< vPrint[i].level << ", " << vPrint[i].stdNum << endl;
		count++;
	} // for
} // twoThreeTree::print()


int AVLTree::height(nodeptr node){
	int l = 0;
	int r = 0;
	if(node->left == NULL && node->right == NULL) return 1 ;
	if(node->left != NULL) l = height(node->left);
	if(node->right != NULL ) r = height(node->right);
	if(l >= r) return l+1;
	else return r+1;
}

bool AVLTree::BF( nodeptr t ){
    rotate_A = 0 ;
    rotate_B = 0 ;
	nodeptr leftnode;
	nodeptr rightnode;
	nodeptr temp;
	nodeptr y = NULL;
	bool stop = false;
	int l = 0;
	int r = 0;
	if( t->left == NULL ) l =0;
	else {
		leftnode = t->left;
		l = height( leftnode );
	}
	if( t->right == NULL ) r =0;
	else {
		rightnode = t->right;
		r = height( rightnode );
	}
	
	rotate_B = l - r ;
	if( t->parent == NULL){ //second times
		return true;
	}
	else{
		if( t->parent->left == NULL ) l =0;
		else {
			leftnode = t->parent->left;
			l = height( leftnode );
		}
		
		if( t->parent->right == NULL ) r =0;
		else {
			rightnode = t->parent->right;
			r = height( rightnode );
		}
	}
	rotate_A = l - r ;
	if( (rotate_A == 2 ) && (rotate_B == +1 || rotate_B == 0 ) ) { // LL
		if( t->parent->parent!=NULL && t->parent->parent->right == t->parent ){
			temp = t->parent->parent;
			temp->right = LL( t->parent );
	    }
		else if( t->parent->parent!=NULL && t->parent->parent->left == t->parent) {
			temp = t->parent->parent;
			temp->left = LL( t->parent );
		}
		else temp = LL( t->parent );
		return true;
	}
	else if( (rotate_A == -2 ) && (rotate_B == -1 || rotate_B == 0 ) ) { // RR
		if( t->parent->parent!=NULL && t->parent->parent->right == t->parent ){
			temp = t->parent->parent;
			temp->right = RR( t->parent );
		
		}
		else if( t->parent->parent!=NULL && t->parent->parent->left == t->parent) {
			temp = t->parent->parent;
			temp->left = RR( t->parent );
		}
		else temp = RR( t->parent );
		return true;
	}
	else if( (rotate_A == 2 ) && (rotate_B == -1 ) ) { // LR=RR->LL
		y = t->parent;
		bool Isleft = false;
		if( t->parent == head && t->parent->left == t ){
			Isleft = true;
		}
		else if(t->parent->parent->left == t->parent) {
			Isleft = true;
		}
		y->left = RR( t );
		if(y!=head){
			temp = y->parent;
			if(Isleft) temp->left = LL( y );
			else temp->right = LL( y ); 
		}
		else temp = LL(y);
		return true;
	}
	else if( (rotate_A == -2 ) && (rotate_B == 1  ) ) { // RL=ll->RR
		bool Isleft = false;
		if( t->parent == head && t->parent->left == t ){
			Isleft = true;
		}
		else if(t->parent->parent->left== t->parent) Isleft = true;
		y = t->parent;
		y->right = LL( t );	
		if(y!=head){
			temp = y->parent;
			if(Isleft) temp->left = RR( y );
			else temp->right = RR( y ); 
		}
		else temp = LL(y);
		return true;
	}
	else if( t->parent == head ) return true;
	else return false;
}
    			
nodeptr AVLTree::LL( nodeptr t ){
	nodeptr tmp ;
	bool Ishead = false;
	if(t->parent!=NULL) tmp = t->parent;
	if(t->parent == NULL ) {
		Ishead = true;
        tmp = NULL ;
	}
	nodeptr y = t->left;
	t->left = y->right;
	if(t->left != NULL){
		t->left->parent=t;
	}
	y->right = t ;
	y->right->parent = y;
    y->parent = tmp;
	if( Ishead ){
		head = y;
		y->parent = NULL;
	}
	return y;
}
nodeptr AVLTree::RR( nodeptr t ){
	nodeptr tmp ;
	tmp = t;
	if(t->parent!=NULL) tmp = t->parent;
	bool Ishead = false;
	if(t->parent == NULL ) {
		Ishead = true;
		tmp = NULL;
	}
	nodeptr y = t->right;
	t->right = y->left;
	if(t->right != NULL){
		t->right->parent = t;
	}
	y->left = t ;
	y->left->parent = y;
	y->parent = tmp;
	if(Ishead ){
		head = y;
		y->parent = NULL;
	}
	return y;
}
    			
