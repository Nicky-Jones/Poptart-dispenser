#include <iostream>
#include <string>
#include <vector>

using namespace std;
enum state { No_Credit, Has_Credit, Dispenses_Poptart, Out_Of_Poptart };
enum stateParameter { Credit, Cost_Of_Poptart, No_Of_Poptarts };

class StateContext;

class State
{
protected:
	StateContext* CurrentContext;

public:
	State(StateContext* Context)
	{
		CurrentContext = Context;
	}
	virtual ~State(void) {}
	virtual void transition(void){}
};

class StateContext
{
protected:
	State* CurrentState = nullptr;
	int stateIndex = 0;
	vector<State*> availableStates;
	vector<int> stateParameters;
public:
	virtual ~StateContext(void);
	virtual void setState(state newState);
	virtual int getStateIndex(void);
	virtual void setStateParam(stateParameter SP, int value);
	virtual int getStateParam(stateParameter SP);
};

StateContext::~StateContext(void)
{
	for (int i = 0; i < this->availableStates.size(); i++) delete this->availableStates[i];
	this->availableStates.clear();
	this->stateParameters.clear();
}

void StateContext::setState(state newState)
{
	this->CurrentState = availableStates[newState];
	this->stateIndex = newState;
	this->CurrentState->transition();
}

int StateContext::getStateIndex(void)
{
	return this->stateIndex;
}

void StateContext::setStateParam(stateParameter SP, int value)
{
	this->stateParameters[SP] = value;
}

int StateContext::getStateParam(stateParameter SP)
{
	return this->stateParameters[SP];
}

class Transition
{
public:
	virtual bool insertMoney(int) { cout << "Error!" << endl; return false; }
	virtual bool makeSelection(int) { cout << "Error!" << endl; return false; }
	virtual bool moneyRejected(void) { cout << "Error!" << endl; return false; }
	virtual bool addPoptart(int) { cout << "Error!" << endl; return false; }
	virtual bool dispense(void) { cout << "Error!" << endl; return false; }
};

class PoptartState : public State, public Transition
{
public:
	PoptartState(StateContext* Context) : State(Context){}
};

class OutOfPoptart : public PoptartState
{
public:
	OutOfPoptart(StateContext* Context) : PoptartState(Context){}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

bool OutOfPoptart::insertMoney(int money)
{
	return false;
}

bool OutOfPoptart::makeSelection(int option)
{
	return false;
}

bool OutOfPoptart::moneyRejected(void)
{
	return false;
}

bool OutOfPoptart::addPoptart(int number)
{
	return false;
}

bool OutOfPoptart::dispense(void)
{
	return false;
}

class NoCredit : public PoptartState
{
public:
	NoCredit(StateContext* Context) : PoptartState(Context){}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

bool NoCredit::insertMoney(int money)
{
	return false;
}

bool NoCredit::makeSelection(int option)
{
	return false;
}

bool NoCredit::moneyRejected(void)
{
	return false;
}

bool NoCredit::addPoptart(int number)
{
	return false;
}

bool NoCredit::dispense(void)
{
	return false;
}

class HasCredit : public PoptartState
{
public:
	HasCredit(StateContext* Context) : PoptartState(Context){}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

bool HasCredit::insertMoney(int money)
{
	return false;
}

bool HasCredit::makeSelection(int option)
{
	return false;
}

bool HasCredit::moneyRejected(void)
{

	return false;
}

bool HasCredit::addPoptart(int number)
{
	return false;
}

bool HasCredit::dispense(void)
{
	return false;
}
class DispensesPoptart : public PoptartState
{
public:
	DispensesPoptart(StateContext* Context) : PoptartState(Context){}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

bool DispensesPoptart::insertMoney(int money)
{
	return false;
}

bool DispensesPoptart::makeSelection(int option)
{
	return false;
}

bool DispensesPoptart::moneyRejected(void)
{
	return false;
}

bool DispensesPoptart::addPoptart(int number)
{
	return false;
}

bool DispensesPoptart::dispense(void)
{
	return false;
}

class Product
{
protected:
	string product_description;
	int itemCost = 0;
public:
	virtual int cost(void);
	virtual string description(void);
};

class Poptart : public Product
{
public:
	Poptart(void);
};

class Poptart_Dispenser : public StateContext, public Transition
{
	friend class DispensesPoptart;
	friend class HasCredit;
private:
	PoptartState* PoptartCurrentState = nullptr;
	bool itemDispensed = false;
	Product* DispensedItem = nullptr;
	bool itemRetrieved = false;
public:
	Poptart_Dispenser(int inventory_counter);
	~Poptart_Dispenser(void);
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
	Product* getProduct(void);
	virtual void setStateParam(stateParameter SP, int value);
	virtual int getStateParam(stateParameter SP);
};

Poptart_Dispenser::Poptart_Dispenser(int inventory_counter)
{
	this->availableStates.push_back(new OutOfPoptart(this));
	this->availableStates.push_back(new NoCredit(this));
	this->availableStates.push_back(new HasCredit(this));
	this->availableStates.push_back(new DispensesPoptart(this));
	this->availableStates.push_back(0);
	this->availableStates.push_back(0);

	this->setState(Out_Of_Poptart);
	if (inventory_counter > 0)
	{
		this->addPoptart(inventory_counter);
	}
}

Poptart_Dispenser::~Poptart_Dispenser(void)
{
	if (!this->itemRetrieved)
	{
		delete this->DispensedItem;
	}
}

bool Poptart_Dispenser::insertMoney(int money)
{
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->insertMoney(money);
}

bool Poptart_Dispenser::makeSelection(int option)
{
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->makeSelection(option);
}

bool Poptart_Dispenser::moneyRejected(void)
{
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->moneyRejected();
}

bool Poptart_Dispenser::addPoptart(int number)
{
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->addPoptart(number);
}

bool Poptart_Dispenser::dispense(void)
{
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->dispense();
}

Product* Poptart_Dispenser::getProduct(void)
{
	if (this->itemDispensed)
	{
		this->itemDispensed = false;
		this->itemRetrieved = true;
		return this->DispensedItem;
	}
	return nullptr;
}

void Poptart_Dispenser::setStateParam(stateParameter SP, int value)
{
	if (SP == Cost_Of_Poptart) return;
	this->stateParameters[SP] = value;
}

int Poptart_Dispenser::getStateParam(stateParameter SP)
{
	if (SP == Cost_Of_Poptart)
	{
		if (DispensedItem == nullptr) return 0;
		return DispensedItem->cost();
	}
	return this->stateParameters[SP];
}
int main()
{
	Poptart_Dispenser test = Poptart_Dispenser(5);
	//test.setState(Has_Credit);

	test.insertMoney(500);
	system("pause");
	return 0;
}