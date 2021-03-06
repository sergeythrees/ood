#include <iostream>
#include <functional>
#include <memory>
#include <cassert>
#include <vector>

using namespace std;
namespace Dance
{
	void Valse()
	{
		cout << "I'm dancing valse!!" << endl;
	}

	void Minuet()
	{
		cout << "I'm dancing minuet!!" << endl;
	}

	void NoWay()
	{
	}
}

namespace Fly
{
	function<void()> MakeFlyWithWingsBehavior()
	{
		size_t flightNumber = 0;
		return [flightNumber]() mutable
		{
			++flightNumber;
			cout << "I'm flying with wings for the " << flightNumber << " time" << endl;
		};
	}

	auto NoWay = []() {};
}

namespace Quack
{
	auto Quack = []()
	{
		cout << "Quack Quack!!!" << endl;
	};
	auto Squeak = []()
	{
		cout << "Squeek!!!" << endl;
	};
	auto Mute = []()
	{
	};
}

class Duck
{
public:
	Duck(const function<void()>& flyBehavior, const function<void()>& quackBehavior, const function<void()>& danceBehavior)
		: m_quackBehavior(quackBehavior),
		m_danceBehavior(danceBehavior)
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(flyBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	virtual void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(const function<void()>& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = flyBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() {};
private:
	function<void()> m_flyBehavior;
	function<void()> m_quackBehavior;
	function<void()> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(Fly::MakeFlyWithWingsBehavior(), Quack::Quack, Dance::Valse)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(Fly::MakeFlyWithWingsBehavior(), Quack::Quack, Dance::Minuet)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DeckoyDuck : public Duck
{
public:
	DeckoyDuck()
		: Duck(Fly::NoWay, Quack::Mute, Dance::NoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm deckoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(Fly::NoWay, Quack::Quack, Dance::NoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(Fly::NoWay, Quack::Quack, Dance::NoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck & duck)
{
	duck.Quack();
	DrawDuck(duck);
	duck.Dance();
	for (size_t i = 0; i < 5; ++i)
	{
		duck.Fly();
	}
}


void main()
{
	MallardDuck mallarDuck;
	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);
	DeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);
	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);	
	modelDuck.SetFlyBehavior(Fly::MakeFlyWithWingsBehavior());
	PlayWithDuck(modelDuck);
}