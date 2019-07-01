#include <string>
#include <iostream>
#include <vector>

enum state { Out_Of_Poptarts, No_Credit, Has_Credit, Dispenses_Poptart };  // creates an enum called state with a list of parameters inside
enum stateParameter { No_Of_Poptarts, Credit, Cost_Of_Poptart};// creates an enum called stateParameter with a list of parameters inside

using namespace std;

class StateContext; // because code in c++ reads from top to bottom I've put this there to tell the classes that needs use of variables from a different class lower than it that its there just lower
class Poptart_Dispenser; // because code in c++ reads from top to bottom I've put this there to tell the classes that needs use of variables from a different class lower than it that its there just lower

class State // creates a class called state
{
protected: // creates an area of this class thats protected from being accessed by other classes 

	StateContext* CurrentContext; // creates a pointer object of StateContext class called CurrentContext

public: // creates an area of this class that's public which allows child classes access to these variables/functions

	State(StateContext* Context) // creates a constructor for class State called State which takes a StateContext pointer called Context as its parameter 
	{
		CurrentContext = Context; // Says the CurrentContext equals Context
	}
	virtual ~State(void) {} // creates a virtual deconstructor for class State  - Virtual means it allows a derived class to override it
	virtual void transition(void) {} // creates a virtual function called Transition   - Virtual means it allows a derived class to override it
};

class StateContext // creates a class called StateContext
{
protected: // creates an area of this class thats protected from being accessed by other classes 

	State* CurrentState = nullptr; // instantiate a pointer object of class State and sets it to nullptr 
	int stateIndex = 0; // creates a variable called stateIndex and sets the value to 0
	vector<State*> availableStates; // Creates a vector of class State pointer called availableStates
	vector<int> stateParameters; // Creates a Vector int called stateParameters

public: // creates an area of this class that's public which allows child classes access to these variables/functions
	virtual ~StateContext(void); // creates a virtual deconstructor for StateContext   - Virtual means it allows a derived class to override it
	virtual void setState(state newState); // creates a Virtual void function called setState which takes a enum called State as a parameter   - Virtual means it allows a derived class to override it
	virtual int getStateIndex(void); // creates a virtual int function called getStateIndex 
	virtual void setStateParam(stateParameter SP, int value); // creates a virtual void setStateParam which takes two parameters one being a parameter from the enum stateParameter and a int value
	virtual int getStateParam(stateParameter SP); // creates a virtual int getStateParam which takes a enum stateParameter as a parameter 
};

class Transition // creates a class called Transition
{
public:// creates an area of this class that's public which allows child classes access to these variables/functions
	virtual bool insertMoney(int) { cout << "Error!" << endl; return false; } // creates a virtual bool function called insetMoney which takes an int Parameter and couts "error" as a message creates a new line then returns false
	virtual bool makeSelection(int) { cout << "Error!" << endl; return false; } // creates a virtual bool function called makeSelection which takes an int Parameter and couts "error" as a message creates a new line then returns false
	virtual bool moneyRejected(void) { cout << "Error!" << endl; return false; } // creates a virtual bool function called moneyRejected which takes an int Parameter and couts "error" as a message creates a new line then returns false
	virtual bool addPoptart(int) { cout << "Error!" << endl; return false; } // creates a virtual bool function called addPoptart which takes an int Parameter and couts "error" as a message creates a new line then returns false
	virtual bool dispense(void) { cout << "Error!" << endl; return false; } // creates a virtual bool function called dispense which takes an int Parameter and couts "error" as a message creates a new line then returns false
};

class PoptartState : public State, public Transition // creates a class called PoptartState which is a child class of State and Transition which means it can access the functions/variables in the public area's of those classes
{
public:  // creates an area of this class that's public which allows child classes access to these variables/functions
	PoptartState(StateContext* Context) : State(Context) {} // creates a constructor for PoptartState which takes two parameters a StateContext pointer called Context and a State object called Context
};

class HasCredit : public PoptartState // creates a class called HasCredit which is a child class of PoptartState
{
public: // creates an area of this class that's public which allows child classes access to these variables/functions
	HasCredit(StateContext* Context) : PoptartState(Context) {} // creates a constructor for HasCredit which takes two parameters a StateContext pointer called Context and a State object called Context
	bool insertMoney(int money); // creates a cool function called insertMoney which takes a int parameter
	bool makeSelection(int option);// creates a cool function called makeSelection which takes a int parameter
	bool moneyRejected(void); // creates a bool function called moneyRejected 
	bool addPoptart(int number);// creates a cool function called addPoptart which takes a int parameter
	bool dispense(void); // creates a bool function called dispense
};

class Product // creates a class called Product
{
protected: // creates an area of this class thats protected from being accessed by other classes 
	string product_description; // creates a string variable called product_description
	int itemCost = 0; // creates a int variable called itemCost and sets the value to 0
public: // creates an area of this class that's public which allows child classes access to these variables/functions
	virtual int cost(void); // creates a virtual int function called Cost
	virtual string description(void); // creates a virtual string function called description
};
class Poptart_Dispenser : public StateContext, public Transition // creates a class called Poptart_Dispenser which is a child class of StateContext and Transition
{
	friend class DispensesPoptart; // creates a Friend class link to DispensesPoptart which allows it to directly access public and private variables/functions from this class
	friend class HasCredit; // creates a Friend class link to HasCredit which allows it to directly access public and private variables/functions from this class

private: // creates an area of this class thats private from being accessed by other classes 
	PoptartState* PoptartCurrentState = nullptr; // instantiates a object from a PoptartState class pointer called PoptartCurrentState and sets it to nullptr
	bool itemDispensed = false; //indicates whether a product is there to be retrieved
	Product* DispensedItem = nullptr; // instantiates a object from a Product class pointer called DispensedItem and sets it to nullptr
	bool itemRetrieved = false; //indicates whether a product has been retrieved
public:// creates an area of this class that's public which allows child classes access to these variables/functions
	Poptart_Dispenser(int inventory_count); // creates a constructor for Poptart_Dispenser which takes a int parameter
	~Poptart_Dispenser(void); // creates a deconstructor for Poptart_Dispenser
	bool insertMoney(int money); // creates a bool function called insetMoney which takes an int parameter
	bool makeSelection(int option); // creates a bool function called makeSelection which takes an int parameter
	bool moneyRejected(void); // creates a bool function called moneyRejected
	bool addPoptart(int number); // creates a bool function called addPoptart which takes an int parameter
	bool dispense(void); // creates a bool function called dispense
	Product* getProduct(void); // creates a Product pointer function called getProduct
	virtual void setStateParam(stateParameter SP, int value); // creates a virtual void setStateParam which takes two parameters one being a parameter from the enum stateParameter and a int value
	virtual int getStateParam(stateParameter SP); // creates a virtual int getStateParam which takes a enum stateParameter as a parameter 
};

StateContext::~StateContext(void)
{
	for (int i = 0; i < this->availableStates.size(); i++) delete this->availableStates[i]; // creates a for loop that loops through all of the datapoints inside availableStates and deletes them all 1 by 1
	this->availableStates.clear(); // removes all the elements from the vector leaving the container with a size of 0
	this->stateParameters.clear(); // removes all the elements fromt he vector leaving the container which a size of 0
}

void StateContext::setState(state newState)
{
	this->CurrentState = availableStates[newState]; // sets the CurrentState to whatever Parameter newState is inside availableStates vector
	this->stateIndex = newState; // sets the stateIndex to whatever is inside newState
	this->CurrentState->transition(); // CurrentState called transition function 
}

int StateContext::getStateIndex(void)
{
	return this->stateIndex; // returns the current stateIndex
}

void StateContext::setStateParam(stateParameter SP, int value)
{
	this->stateParameters[SP] = value; // takes the stateParameter that was sent inside SP and sets a value to it that was sent inside value 
}

int StateContext::getStateParam(stateParameter SP)
{
	return this->stateParameters[SP]; // returns the state thats inside SP from stateParameters
}

class OutOfPoptart : public PoptartState // creates a class OutOfPoptat which is a child class of PoptartState
{
public: // creates an area of this class that's public which allows child classes access to these variables/functions
	OutOfPoptart(StateContext* Context) : PoptartState(Context) {} // creates a constructor for OutOfPoptart which takes two parameters a StateContext pointer called Context and a State object called Context
	bool insertMoney(int money); // creates a bool function called insetMoney which takes an int parameter
	bool makeSelection(int option); // creates a bool function called makeSelection which takes an int parameter
	bool moneyRejected(void); // creates a bool function called moneyRejected
	bool addPoptart(int number); // creates a bool function called addPoptart which takes an int parameter
	bool dispense(void); // creates a bool function called dispense
};

bool OutOfPoptart::insertMoney(int money)
{
	cout << "Error, No Poptarts are left!" << endl; // if function is called inside this state send a error message 
	this->moneyRejected(); // calls the function moneyRejected to eject the money 
	return false; // return false
}

bool OutOfPoptart::makeSelection(int option)
{
	cout << "Error, No Poptarts are left, selection not made!" << endl; // if function is called inside this state send a error message 
	return false; // return false
}

bool OutOfPoptart::moneyRejected(void)
{
	cout << "Ejecting!" << endl; // Ejecting the money from the machine
	return false; // return false
}

bool OutOfPoptart::addPoptart(int number)
{
	this->CurrentContext->setStateParam(No_Of_Poptarts, number); // updates the number inside No_Of_Poptarts to the value that was passed through in number
	this->CurrentContext->setState(No_Credit); // changes the state to No_Credit
	return true; // return true because adding poptarts was successful
}

bool OutOfPoptart::dispense(void)
{
	cout << "Error, No Poptarts are left, nothing to dispense!" << endl; // if function is called inside this state send a error message 
	return false; // returns false
}

class NoCredit : public PoptartState // Creates a class called NoCredit that is a child call of PoptartState
{
public:  // creates an area of this class that's public which allows child classes access to these variables/functions
	NoCredit(StateContext* Context) : PoptartState(Context) {} // creates a constructor for OutOfPoptart which takes two parameters a StateContext pointer called Context and a State object called Context
	bool insertMoney(int money); // creates a bool function called insetMoney which takes an int parameter
	bool makeSelection(int option); // creates a bool function called makeSelection which takes an int parameter
	bool moneyRejected(void); // creates a bool function called moneyRejected
	bool addPoptart(int number); // creates a bool function called addPoptart which takes an int parameter
	bool dispense(void); // creates a bool function called dispense
};

bool NoCredit::insertMoney(int money)
{
	cout << "You inserted: " << money << endl; // sends a message to say how much you have entered
	money = money + this->CurrentContext->getStateParam(Credit); // updates how much money you have by checking if you have already put in a previous amount
	this->CurrentContext->setStateParam(Credit, money); // updates the credit to the latest amount of money you have put in the machine
	cout << "Total: " << money << endl; // outputs the total amount of money that is currently in the machine
	this->CurrentContext->setState(Has_Credit); // keeps the state in Has_Credit
	return true; // return true because inserting money was successful

}

bool NoCredit::makeSelection(int option)
{
	cout << "No selection should be made at this stage" << endl; // if function is called inside this state send a error message 
	return false; // returns false
}

bool NoCredit::moneyRejected(void)
{
	cout << "Error, Money rejected, rejecting!" << endl; // if function is called inside this state send a error message 
	return false; // returns false
}

bool NoCredit::addPoptart(int number)
{
	cout << "Error, out of poptarts" << endl; // if function is called inside this state send a error message 
	return false; // returns false
}

bool NoCredit::dispense(void)
{
	cout << "Error, no Poptarts have been selected yet" << endl; // if function is called inside this state send a error message 
	return false; // returns false
}
bool HasCredit::insertMoney(int money)
{
	cout << "You inserted: " << money << endl; // sends a message to say how much you have entered
	money = money + this->CurrentContext->getStateParam(Credit); // updates how much money you have by checking if you have already put in a previous amount
	this->CurrentContext->setStateParam(Credit, money); // updates the credit to the latest amount of money you have put in the machine
	cout << "Total: " << money << endl; // outputs the total amount of money that is currently in the machine
	return true; // return true because insert money was successful
}

bool HasCredit::moneyRejected(void)
{
	cout << "Ejecting" << endl; // send a message ejecting the money
	this->CurrentContext->setState(No_Credit); // Sends the current state back to No_Credit
	return true; // return true because rejecting the money was successful
}

bool HasCredit::addPoptart(int number)
{
	cout << "Error, out of Poptarts"; // if function is called inside this state sends a error message 
	return false; // returns false
}

bool HasCredit::dispense(void)
{
	cout << "Error, shoudl not be in here" << endl; // if function is called inside this state sends a error message 
	return false; // returns false
}
class DispensesPoptart : public PoptartState // creates a class called DispensesPoptart which is a child called of PoptartState
{
public:  // creates an area of this class that's public which allows child classes access to these variables/functions
	DispensesPoptart(StateContext* Context) : PoptartState(Context) {} // creates a constructor for OutOfPoptart which takes two parameters a StateContext pointer called Context and a State object called Context
	bool insertMoney(int money); // creates a bool function called insetMoney which takes an int parameter
	bool makeSelection(int option); // creates a bool function called makeSelection which takes an int parameter
	bool moneyRejected(void); // creates a bool function called moneyRejected
	bool addPoptart(int number); // creates a bool function called addPoptart which takes an int parameter
	bool dispense(void); // creates a bool function called dispense
};
bool DispensesPoptart::insertMoney(int money)
{
	cout << "Error, no money can be inserted" << endl; // if function is called inside this state sends a error message 
	return false; // returns false
}

bool DispensesPoptart::makeSelection(int option)
{
	cout << "Error, should not be in here" << endl; // if function is called inside this state sends a error message 
	return false; // returns false
}

bool DispensesPoptart::moneyRejected(void)
{
	cout << "Error, rejecting" << endl; // if function is called inside this state sends a error message 
	return false; // returns false
}

bool DispensesPoptart::addPoptart(int number)
{
	cout << "Error, should not be in here" << endl; // if function is called inside this state sends a error message 
	return false; // returns false
}

bool DispensesPoptart::dispense(void)
{
	((Poptart_Dispenser*)(this->CurrentContext))->itemDispensed = true; // changes the itemDispensed bool in Poptart_dispenses to true
	if (this->CurrentContext->getStateParam(Credit) > 0 && this->CurrentContext->getStateParam(No_Of_Poptarts) > 0) // checks to see if Credit is greater than 0 and the number inside No_Of_Poptarts is greater than 0
	{
		this->CurrentContext->setState(Has_Credit); // if the above statement is correct changes the current state to Has_Credit
	}
	else if (this->CurrentContext->getStateParam(Credit) == 0 && this->CurrentContext->getStateParam(No_Of_Poptarts) > 0) // checks to see if Credit is equal to 0 and if No_Of_Poptart is greater than 0
	{
		
		this->CurrentContext->setState(No_Credit); // if the above statement is correct changes the current state to No_Credit
	}
	else if (this->CurrentContext->getStateParam(No_Of_Poptarts) == 0) // checks to see if the No_Of_Poptarts equal 0
	{
		
		this->CurrentContext->setState(Out_Of_Poptarts); // if the above statement is correct changes the current State to Out_Of_Poptarts
	}

	return true; // return true because one of the above stats was successful 
}

int Product::cost(void) // creates the function Cost for class Product
{
	return this->itemCost; // returns the value inside itemCost
}
string Product::description(void) // creates the function description for class Product
{
	return this->product_description;// returns the string inside product_description
}

class Poptart : public Product
{
public:
	Poptart(void);
};
Poptart::Poptart(void) // creates the constructor for class Poptart
{
	itemCost = 0; // Uses the variable that was created in the adult class Product and sets the value to 0
	product_description = "";// Uses the string variable that was created in the adult class Product and sets the value to nothing
}

class Plain : public Poptart // creates a call called Plain which is a child of Poptart
{
public:
	Plain(void) // creates a constructor for Plain
	{
		product_description = "Plain Poptart"; // adds test to the string variable Product_description
		itemCost = 100; // changes the value inside itemCost
	}
};

class Spicy : public Poptart // creates a call called Spicy which is a child of Poptart
{
public:
	Spicy(void) // creates a constructor for Spicy
	{
		product_description = "Spicy"; // adds test to the string variable Product_description
		itemCost = 150; // changes the value inside itemCost
	}
};

class Chocolate : public Poptart // creates a call called Chocolate which is a child of Poptart
{
public:
	Chocolate(void) // creates a constructor for Chocolate
	{
		product_description = "Chocolately Goodness"; // adds test to the string variable Product_description
		itemCost = 200; // changes the value inside itemCost
	}
};

class Cocounut : public Poptart // creates a call called Cocounut which is a child of Poptart
{
public:
	Cocounut(void) // creates a constructor for Cocounut
	{
		product_description = "Cocounutty"; // adds test to the string variable Product_description
		itemCost = 200; // changes the value inside itemCost
	}
};

class Fruity : public Poptart // creates a call called Fruity which is a child of Poptart
{
public:
	Fruity(void) // creates a constructor for Fruity
	{
		product_description = "Fruity Tooty"; // adds test to the string variable Product_description
		itemCost = 200; // changes the value inside itemCost
	}
};
bool HasCredit::makeSelection(int option)
{
	
	int itemCost = 0; // declaring a variable called ItemCost
	switch (option) // Picks the case depending on the value that gets passed to Option
	{
	case 1:
		((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Plain; // calls the DispnsedItem from the Poptart_dispenser state and calls a poptart base called "plain" 
		break;
	case 2:
		((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Spicy; // calls the DispnsedItem from the Poptart_dispenser state and calls a poptart base called "spicy" 
		break;
	case 4:
		((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Chocolate; // calls the DispnsedItem from the Poptart_dispenser state and calls a poptart base called "chocolate" 
		break;
	case 8:
		((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Cocounut; // calls the DispnsedItem from the Poptart_dispenser state and calls a poptart base called "Cocounut" 
		break;
	case 16:
		((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Fruity; // calls the DispnsedItem from the Poptart_dispenser state and calls a poptart base called "Fruity" 
		break;
	default:
		cout << "error";
		break;
	}
	if (this->CurrentContext->getStateParam(Credit) >= ((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem->cost()) // checks to see if the value that is inside credit is more than the cost of the item that they chose by calling the function that will return the product's itemCost
	{
		
		this->CurrentContext->setStateParam(Credit, (this->CurrentContext->getStateParam(Credit) - this->CurrentContext->getStateParam(Cost_Of_Poptart))); // Sets the value inside Credit by calling the GetStateParam with Cost_Of_Poptart as the variable sent so when entering that function it'll execute a piece of code in there that returns the cost of the Poptart product and then minusing it by getting the the value that is currently already inside Credit
		cout << "You now have: " << this->CurrentContext->getStateParam(Credit); // sends out a message updating how much money the person has left after buying the poptart they chose 
		this->CurrentContext->setState(Dispenses_Poptart); // changes the current state to Dispenses_Poptart
	}
	else
		cout << "you don't have enough money"; // if the user didn't have enough money for the product they bought send the message they didn't have enough money to the screen
	

	
	cout << endl;
	return true; // return true because chosing an item was successful
}


Poptart_Dispenser::Poptart_Dispenser(int inventory_counter)
{
	this->availableStates.push_back(new OutOfPoptart(this)); // creates a object of OutOfPoptart and puts it inside a Vector 
	this->availableStates.push_back(new NoCredit(this)); // creates a object of NoCredit and puts it inside a Vector 
	this->availableStates.push_back(new HasCredit(this)); // creates a object of HasCredit and puts it inside a Vector 
	this->availableStates.push_back(new DispensesPoptart(this)); // creates a object of DispensesPoptart and puts it inside a Vector 
	this->stateParameters.push_back(0); // Creates a vector position for a StateParameter 
	this->stateParameters.push_back(0); // Creates a vector position for a StateParameter 
	this->stateParameters.push_back(0); // Creates a vector position for a StateParameter 

	this->setState(Out_Of_Poptarts); // changes the state to Out_Of_Poptarts 
	if (inventory_counter > 0) // checks to see if the value that was passed through Inventory_counter is more than 0
	{
		this->addPoptart(inventory_counter); // if the above statement is true, call the add poptart function and send the value thats inside Inventory_Counter to that function
	}
}

Poptart_Dispenser::~Poptart_Dispenser(void)
{
	if (!this->itemRetrieved) // checks for itemRetrieved if there execute the following code inside the if statement
	{
		delete this->DispensedItem; // deletes DispensedItem
	}
}

bool Poptart_Dispenser::insertMoney(int money)
{
	PoptartCurrentState = (PoptartState*) this->CurrentState; // PoptartCurrentState = the CurrentState inside PoptartState  
	return this->PoptartCurrentState->insertMoney(money); // return PoptartCurrentState calling the function inside the new state insertMoney with the value that is inside the parameter money
}

bool Poptart_Dispenser::makeSelection(int option)
{
	PoptartCurrentState = (PoptartState*) this->CurrentState; // PoptartCurrentState = the CurrentState inside PoptartState  
	return this->PoptartCurrentState->makeSelection(option); // return PoptartCurrentState calling the function inside the new state makeSelection with the value that is inside the parameter option
}

bool Poptart_Dispenser::moneyRejected(void)
{
	PoptartCurrentState = (PoptartState*) this->CurrentState; // PoptartCurrentState = the CurrentState inside PoptartState  
	return this->PoptartCurrentState->moneyRejected(); // return PoptartCurrentState calling the function inside the new state makeRejected
}

bool Poptart_Dispenser::addPoptart(int number)
{
	PoptartCurrentState = (PoptartState*) this->CurrentState; // PoptartCurrentState = the CurrentState inside PoptartState  
	return this->PoptartCurrentState->addPoptart(number);// return PoptartCurrentState calling the function inside the new state addPoptart with the value that is inside the parameter number
}

bool Poptart_Dispenser::dispense(void)
{
	PoptartCurrentState = (PoptartState*) this->CurrentState; // PoptartCurrentState = the CurrentState inside PoptartState  
	return this->PoptartCurrentState->dispense(); // return PoptartCurrentState calling the function inside the new state dispense
}

Product* Poptart_Dispenser::getProduct(void)
{
	if (this->itemDispensed) // checks for itemDispensed is its there execute the folowing code inside the if statement
	{
		this->itemDispensed = false; // changes the value of itemDispensed to false
		this->itemRetrieved = true; // changes the value of itemRetrieved to True
		return this->DispensedItem; // returns DispensedItem 
	}

	return nullptr; // if it didn't successfully go inside the if statement return nullptr
}

void Poptart_Dispenser::setStateParam(stateParameter SP, int value)
{
	if (SP == Cost_Of_Poptart) return; // checks to see if the value inside SP equals Cost_Of_Poptart
	this->stateParameters[SP] = value; // if it does go to stateParameter find the parameter that equals SP once you've done that give that Paramter the value that is inside value and return it
}

int Poptart_Dispenser::getStateParam(stateParameter SP)
{
	if (SP == Cost_Of_Poptart) // checks to see if SP is equal to Cost_Of_Poptart
	{
		if (DispensedItem == nullptr) return 0; // checks to see if DispensedItem equals nullptr if it is return nothing
		return DispensedItem->cost(); // if its not return DispensedItem calling the function cost
	}
	return this->stateParameters[SP]; // go to stateParameter find the parameter that equals SP and return it.
}

int main()
{
	Poptart_Dispenser test = Poptart_Dispenser(3);
	test.insertMoney(500);
	test.makeSelection(16);

	system("pause");
	return 0;
}