#include "mu_test.h"
#include <vector>
#include <cassert>
#include "CommonTypes.h"
#include "IRunnable.h"
#include "Thread.h"
#include "WaitQueue.h"

using namespace advcpp;

class Cat{
public:
	Cat() {++n; m_id = s_id; ++s_id;}
	Cat(const Cat& x) {++n; m_id = x.m_id;}
	Cat& operator=(const Cat& x) {++n; m_id = x.m_id; return *this;}
	bool operator==(const Cat& x) {return (m_id == x.m_id);}
	~Cat() {--n;}
	
	int n; //num of cats
	static int s_id; //counter
	int m_id;
};
int Cat::s_id = 0;

template <typename T>
class Producer : public IRunnable
{
public:
	Producer(shared_ptr<WaitQueue<T> > spWq, int N)
	: m_spWq(spWq)
	, m_size(N)
	{
		if(spWq == 0) //if NULL
		{
			assert(false and "input param NULL.");
		}
	}
	
	virtual ~Producer() {}
	virtual void Run()
	{
		for(int i=0; i<m_size; ++i)
		{
			T* element = new T();
			m_spWq->Enqueue(*element);
			delete element;
		}
	}

private:
	shared_ptr<WaitQueue<T> > m_spWq;
	int m_size;
};

template <typename T>
class Consumer : public IRunnable
{
public:
	typedef std::tr1::shared_ptr<WaitQueue<T> > SP_WQ;
	typedef std::tr1::shared_ptr<std::vector<T> > SP_VEC;	
	Consumer(SP_WQ spWq, int N, SP_VEC spVec)
	: m_spWq(spWq)
	, m_size(N)
	, m_spVec(spVec)
	{
		if(spWq == 0)
		{
			assert(false and "input param NULL.");
		}
	}
	
	virtual ~Consumer() {}
	virtual void Run()
	{	
		for(int i=0; i<m_size; ++i)
		{
			T* element = new T();
			*element = m_spWq->Dequeue();
			m_spVec->push_back(*element);
			delete element;				
		}
	}
	virtual int Result() const {return 0;} 
private:
	SP_WQ m_spWq;
	int m_size;
	SP_VEC m_spVec;
};


UNIT(Test_one_thread)
	Cat::s_id = 0;
	int N = 10000;
	WaitQueue<Cat> wq;
	Cat cat;  //id starts in 1
	ASSERT_THAT(wq.IsEmpty() == true);
	ASSERT_EQUAL_INT(wq.Size(), 0);	
	//push N cats to queue
	for(int i=0; i<N; ++i)
	{
		wq.Enqueue(Cat());
	}
	ASSERT_THAT(wq.IsEmpty() == false);
	ASSERT_EQUAL_INT(wq.Size(), 10000);
	//pop cats
	for(int i=1; i<=N; ++i)
	{
		cat = wq.Dequeue();
		ASSERT_EQUAL_INT(cat.m_id, i);
	}
	ASSERT_EQUAL_INT(wq.IsEmpty(), 1);
END_UNIT


UNIT(Test_TwoProd_OneCons_Thread)
	Cat::s_id = 0; //reset static var;
	int size=100;
	
	shared_ptr<WaitQueue<Cat> > spWq(new WaitQueue<Cat>);
	shared_ptr<Producer<Cat> > a_spProd(new Producer<Cat>(spWq, size));
	shared_ptr<Producer<Cat> > b_spProd(new Producer<Cat>(spWq, size));
	Thread th1(a_spProd);
	Thread th2(b_spProd);	
	th1.Join();
	th2.Join();
	
	//create a shared ptr to vector that producers fill with cats
	shared_ptr<std::vector<Cat> > spVec(new std::vector<Cat>); 
	ASSERT_EQUAL_INT(spVec->size(), 0);
	ASSERT_EQUAL_INT(spWq->IsEmpty(), false);
	ASSERT_EQUAL_INT(spWq->Size(), 2*size);
	
	shared_ptr<Consumer<Cat> > spCons(new Consumer<Cat>(spWq, 2*size, spVec));
	Thread th3(spCons);
	th3.Join();
	
	ASSERT_EQUAL_INT(spWq->IsEmpty(), true);
	ASSERT_EQUAL_INT(spVec->empty(), false);
	ASSERT_EQUAL_INT(spVec->size(), 2*size);

	ASSERT_EQUAL_INT(spWq->Size(), 0);		
END_UNIT


UNIT(Test_nProd_mCons_Thread)
	Cat::s_id = 0; //reset static var;
	int size=10000;
	shared_ptr<WaitQueue<Cat> > spWq(new WaitQueue<Cat>);
	shared_ptr<std::vector<Cat> > spVec(new std::vector<Cat>); 
	
	//check all possible scenarios: bigger:smaller, same:same, smaller:bigger
	size_t numProds = 105;
	size_t numCons = 85;
	
	//vectors contain prod/cons threads in order to join later
	std::vector<shared_ptr<Thread> > thSpProdsVec; 
	//std::vector<shared_ptr<Thread> > thSpConsVec; 

	shared_ptr<Producer<Cat> > spProd(new Producer<Cat>(spWq, size));

	for(size_t i=0; i<numProds; ++i)
	{
		shared_ptr<Thread> spThP(new Thread(spProd)); //Run
		//spThP->Join();
		thSpProdsVec.push_back(spThP);
	}

	size_t consSize = (numProds*size)/numCons;
	size_t dSize = (numProds*size)%numCons;
	if(dSize != 0)
	{
		shared_ptr<Consumer<Cat> > spCons(new Consumer<Cat>(spWq, dSize+consSize, spVec));
		shared_ptr<Thread> spThC(new Thread(spCons));
		spThC->Join();
		--numCons;
	}

	shared_ptr<Consumer<Cat> > spCons(new Consumer<Cat>(spWq, consSize, spVec));
	for(size_t i=0; i<numCons; ++i)
	{
		shared_ptr<Thread> spThC(new Thread(spCons));
		spThC->Join();
		//thSpConsVec.push_back(spThC);
	}
		
	ASSERT_EQUAL_INT(thSpProdsVec.size(), numProds);
	//ASSERT_EQUAL_INT(thSpConsVec.size(), numCons);
	
	//Join Prods/Cons
	for(size_t i=0; i<thSpProdsVec.size(); ++i)
	{
		thSpProdsVec[i]->Join();
	}
	
	/*
	for(size_t j=0; j<thSpConsVec.size(); ++j)
	{
		thSpConsVec[j]->Join();
	}
	*/
	
	ASSERT_THAT(spWq->IsEmpty() == true);
	ASSERT_EQUAL_INT(spVec->size(), numProds*size);	
END_UNIT


TEST_SUITE(CPP_Unit_Test_waitableQueue!)
	TEST(Test_one_thread)
	TEST(Test_TwoProd_OneCons_Thread)
	TEST(Test_nProd_mCons_Thread)

END_SUITE



