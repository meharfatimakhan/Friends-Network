#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class nodeFriend//node for linkedListFriends
{
private:
	friend class linkedQueueFriend;
	friend class friendsApp;
	friend class linkedIterator;
	friend class linkedListFriends;
	friend class user;

	int data;
	nodeFriend *next;

public:
	nodeFriend(int d) //parameterized constructor
	{
		data = d;
		next = nullptr;
	}
};

class linkedQueueFriend
{
private:
	friend class friendApp;

	nodeFriend *queueFront;
	nodeFriend *queueRear;

public:
	linkedQueueFriend() //default constructor
	{
		queueFront = nullptr;
		queueRear = nullptr;
	}

	nodeFriend* getFront() //returns the first element in queue
	{
		if (queueFront != nullptr)
			return queueFront;
	}

	nodeFriend* getRear() //returns the last element present in queue
	{
		if (queueRear != nullptr)
			return queueRear;
	}

	bool isEmptyQueue() const
	{
		return (queueFront == nullptr);
	}

	bool isFullQueue()
	{
		nodeFriend *newNode;
		try
		{
			newNode = new nodeFriend(0);
			delete newNode;
			return false;
		}
		catch (std::bad_alloc exception)
		{
			return true;
		}
	}
	void enQueue(const int& newElement)//adds a new element at the the rear of queue
	{
		nodeFriend *newNode = new nodeFriend(0);//initializing newNode to 0
		newNode->data = newElement;
		newNode->next = nullptr;
		if (queueFront == nullptr)//if front is not null, newElement would be first element in queue
		{
			queueFront = newNode;
			queueRear = newNode;
		}
		else
		{
			queueRear->next = newNode;//if not empty, the inserts newElement at rear
			queueRear = queueRear->next;
		}
	}

	void deQueue() //deletes an element from the front of the queue
	{
		nodeFriend *temp;
		if (!isEmptyQueue())
		{
			temp = queueFront;
			queueFront = queueFront->next;
			delete temp;
			if (queueFront == nullptr)
				queueRear = nullptr;
		}
		else
			cout << "Cannot remove from an empty queue.\n";
	}

	~linkedQueueFriend()//destructor
	{
		nodeFriend *temp;
		while (queueFront != nullptr)//deletes until front is not null
		{
			temp = queueFront;
			queueFront = queueFront->next;
			delete temp;
		}
	}
};

class linkedListFriends
{
private:
	friend class user;
	friend class nodeUser;
	friend class linkedListUsers;
	friend class friendsApp;
	
	nodeFriend *head;

public:
	linkedListFriends() //default constructor
	{
		head = nullptr;
	}

	void insertFriend(int Data) //inserts new data in linkedlist
	{
		nodeFriend* newNode = new nodeFriend(Data);
		if (head == 0)//if linkedList is empty
		{
			head = newNode;
		}
		else
		{
			if (Data < head->data) //if new data is less than already present data in head, then make head = newNode
			{
				newNode->next = head;
				head = newNode;
			}
			else
			{
				nodeFriend* current = head;
				while (current->next != 0 && current->next->data < Data)//while current is not null & while current's next's data is not less than new data
				{
					current = current->next;
				}
				newNode->next = current->next;
				current->next = newNode;
			}
		}
	}

	nodeFriend* searchFriend(int Data)//searches for an element in linkedList
	{
		if (head)
		{
			nodeFriend* current = head;
			while (current != 0 && current->data < Data)//while new data is not more than current's data
			{
				current = current->next;
			}
			if (current != 0 && current->data == Data)//if current's data is more than newdata and it's equal to newdata
			{
				cout << current->data;
				return current;
			}
			else
			{
				cout << Data << " is not a friend of user.\n";
				return 0;
			}
		}
	}

	nodeFriend* getHead()//returns head if it's not equal to null
	{
		if (head!=nullptr)
		{
			nodeFriend* temp = head;
			return temp;	
		}
		return 0;
	}

	~linkedListFriends()//destructor
	{
		head = nullptr;
	}
}; 

class user
{
public:
	friend class linkedListUsers;

	int iD;
	string firstName;
	string lastName;
	linkedListFriends friendList;

	//default constructor
	user()
	{
		iD = 0;
		firstName = "0";
		lastName = "0";
	}

	friend ostream& operator<<(ostream& out, const user &userData)//console output operator
	{
		out << "USER INFORMATION:\n";
		out << "ID: " <<userData.iD << "\nName: " << userData.firstName << " ";
		out << userData.lastName << "\nFriend List: \n"; 
		return out;
	}
};

class nodeUser//node for linkedListUsers
{
private:
	friend class friendsApp;
	friend class linkedListUsers;
	friend class user;

	user data;
	nodeUser *next;

public:
	nodeUser(user d)//defualt constructor
	{
		data = d;
		next = nullptr;
	}
};

class linkedListUsers
{
private:
	friend class linkedListFriends;

	nodeUser *head;

public:
	linkedListUsers()//default constructor
	{
		head = nullptr;
	}

	void insertUser(user Data)//inserts new data in linkedlist
	{
		nodeUser* newNode = new nodeUser(Data);
		if (head == 0)//if linkedList is empty
		{
			head = newNode;
		}
		else
		{
			if (Data.iD < head->data.iD)//if new data is less than already present data in head, then make head = newNode
			{
				newNode->next = head;
				head = newNode;
			}
			else
			{
				nodeUser* current = head;
				while (current->next != 0 && current->next->data.iD < Data.iD)//while current is not null & while current's next's data is not less than new data
				{
					current = current->next;
				}
				newNode->next = current->next;
				current->next = newNode;
			}
		}
	}

	nodeUser* searchAndPrintUser(int Data)//searches for user with the Id that matches Data
	{
		if (head)
		{
			nodeUser* temp = head;
			while (temp != 0 && temp->data.iD < Data)
			{
				temp = temp->next;
			}
			if (temp != 0 && temp->data.iD == Data)//if user's id matches data, the user is found and it prints user
			{
				cout << temp->data;
				return temp;
			}
			else
			{
				cout << "User ID does not exist.\n";
				return 0;
			}
		}
	}

	nodeUser* getInfo(int Data)//this performs the same operation as search, it is just a getter, has no printing purpose
	{
		if (head)
		{
			nodeUser* temp = head;
			while (temp != 0 && temp->data.iD < Data)
			{
				temp = temp->next;
			}
			if (temp != 0 && temp->data.iD == Data)
			{
				return temp;
			}
			else
			{
				return 0;
			}
		}
	}

	void searchFriendUser(int Data)//this searches for the friend of user in friendList
	{
		if (head)
		{
			nodeUser* temp = head;
			while (temp != 0 && temp->data.iD < Data)
			{
				temp = temp->next;
			}
			if (temp != 0 && temp->data.iD == Data)//if friend is found in user friendList, then prints friend's info
			{
				cout << temp->data.iD<<" "<< temp->data.firstName <<" "<< temp->data.lastName;
				cout << endl;
			    return; 
			}
			else
			{
				cout << "No friends in friend list.\n";
				return;
			}
		}
	}

	~linkedListUsers()//destructor
	{
		nodeUser* nodeToDelete = nullptr;
		while (head != nullptr)	//If linked list is not empty
		{
			nodeToDelete = head;
			head = head->next;
			delete nodeToDelete;
		}
	}
};

class friendsApp:public user//user is made public for ease of access
{
private:
	linkedListUsers userList;

public:
	void readfromFile()//reads all data from file and stores user's data in userList and user's friend's in friendList
	{
		ifstream read;
		read.open("UsersList.txt");
		while (!read.eof())//reads till end of file
		{
			int ID=0;
			user appUser;
			read >> appUser.iD;//reads user's id
			getline(read, appUser.firstName, ' ');//reads first name till it finds a space
			getline(read, appUser.lastName, '\t');//reads last name till it finds a tab
			while (ID != -1)
			{
			    read >> ID;//reads friend's id
				if (ID == -1)//when id is -1, it will skip insertion and 
					goto here;
				appUser.friendList.insertFriend(ID);//this will insert friends in friendlist until id is not -1
			}
			here: userList.insertUser(appUser);//inserts user's data in userlist
		}
		read.close();
	}

	void setup()
	{
		cout << "FRIENDS NETWORK\n\n";
		int option;
		cout << "Enter user ID for information: ";
		cin >> option;
		nodeUser *userNode = userList.searchAndPrintUser(option);//searches and prints data of selected user
		user ourUser = userNode->data;//copies the data present in userNode in app
		nodeUser *temporary = userNode;//creates a duplicate of userNode, needed later on
		
		nodeFriend *friendTemp = new nodeFriend(option);//this will gives us the userId of whose friendList we have to traverse
		friendTemp = ourUser.friendList.getHead();//returns the first friend present in user's friendlist

		if (friendTemp == nullptr)
			userList.searchFriendUser(0);
		else
		{
			while (friendTemp != nullptr)//prints friendlist by traversing through the friendlist
			{
				userList.searchFriendUser(friendTemp->data);//prints the name of friends present in friendlist by taking their user ids
				friendTemp = friendTemp->next;
			}
		}

		cout << "\nSuggested Friends: \n";

		delete friendTemp; //deallocates memory for friendTemp
		linkedQueueFriend queue;//creates an object of linkedQueue type

		friendTemp = new nodeFriend(option);//reallocates friendTemp to the selected userID
		friendTemp = ourUser.friendList.getHead();//gives first friend of the selected userId
		if (friendTemp != nullptr)
		{
			nodeFriend* friendVariable = new nodeFriend(friendTemp->data);//copies first friend  information in friendVar

			user ourUserCheck = ourUser;//this will be needed later
			userNode = userList.getInfo(friendVariable->data);//this gives info the first friend
			ourUser = userNode->data;//stores data of the selected user in ourUser

			while (friendTemp != nullptr)
			{
				friendVariable = new nodeFriend(friendTemp->data);
				friendVariable = ourUser.friendList.getHead();//gives us first friend of user 'friendTemp->data'
				while (friendVariable != nullptr)
				{
					bool flag1 = false;
					bool flag2 = false;
					if (friendVariable->data != option)//if not the selected user
					{
						nodeFriend *temp = new nodeFriend(temporary->data.iD);
						temp = ourUserCheck.friendList.getHead();//to check friends of selected friend
						while (temp != nullptr)//if not already friends
						{
							if (temp->data == friendVariable->data)//if true then skip and don't add in queue and skip
							{
								flag1 = true;
								goto skip;
							}
							temp = temp->next;
						}
						if (!queue.isEmptyQueue())//if queue is not empty
						{
							nodeFriend* current;
							current = queue.getFront();//stores value present at queue's front
							while (current != nullptr)
							{
								if (friendVariable->data == current->data)//if friend is already present in queue then, dont enqueue and skip
								{
									flag2 = true;
									goto skip;
								}
								current = current->next;
							}
						}
						if (!flag1 && !flag2)//if both flags are false, then enqueue
						{
							queue.enQueue(friendVariable->data);
							userList.searchFriendUser(friendVariable->data);//searches and prints friend's name
						}
					}
				skip: friendVariable = friendVariable->next;//gives next friend of user
				}
				friendTemp = friendTemp->next;//this processes next friend (of our selected user) 
			//	userNode = userNode->next;
				if (friendTemp!=nullptr)	
					userNode = userList.getInfo(friendTemp->data);//this gives info the first friend
				ourUser = userNode->data;//stores data of next friend
			}

			delete friendVariable;
			nodeFriend* queueElement = queue.getFront();//this will store first element present in queue, will need in loop
			friendVariable = queue.getFront();//stores queue's front  

			while (queueElement != queue.getRear())//works until our queue's front traverses to rear
			{
				nodeUser * traceUser = userList.getInfo(queueElement->data);//gives first element present in queue
				ourUser = traceUser->data;//stores this value in ourUser
				friendVariable = ourUser.friendList.getHead();//gives first friend of the element present in queue
				while (friendVariable != nullptr)
				{
					bool flag1 = false;
					bool flag2 = false;
					if (friendVariable->data != option)//if not the selected user
					{
						nodeFriend *temp = new nodeFriend(temporary->data.iD);
						temp = ourUserCheck.friendList.getHead();//to check friends of selected friend
						while (temp != nullptr)//if not already friends
						{
							if (temp->data == friendVariable->data)
							{
								flag1 = true;//if true then skip and don't add in queue and skip
								goto skip1;
							}
							temp = temp->next;
						}
						if (!queue.isEmptyQueue())//if queue is not empty
						{
							nodeFriend* current = queue.getFront();//stores value present at queue's front
							while (current != nullptr)
							{
								if (friendVariable->data == current->data)//if friend is already present in queue then, dont enqueue and skip
								{
									flag2 = true;
									goto skip1;
								}
								current = current->next;
							}
						}
						if (!flag1 && !flag2)//if both flags are false, then enqueue
						{
							queue.enQueue(friendVariable->data);
							userList.searchFriendUser(friendVariable->data);//searches and prints friend's name
						}
					}
				skip1: friendVariable = friendVariable->next;//gives next friend of user
				}
				queueElement = queueElement->next;//gives next element of queue which we will be processed in the above while loop
			}
		}
		if (queue.isEmptyQueue())//if queue is empty then, it means that no friend suggestions are available
		{
			cout << "No friend suggestions available.\n";
		}
	}

	void continueProgram()//function will call setup function until 0 is not pressed
	{
		int option = 1;
		do
		{
			setup();

			cout << "\nPress 1 to continue and any other NUMBER to end: ";
			cin >> option;
			cout << "\n";
		} while (option==1);
		exit(EXIT_FAILURE);//exit
	}
};

void main()
{
	friendsApp object;
	object.readfromFile();
	object.continueProgram();

	system("pause");
}