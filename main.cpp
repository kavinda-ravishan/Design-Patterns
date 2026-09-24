#include "Singleton.hpp"
#include "Iterator.hpp"
#include "Factory.hpp"
#include "Builder.hpp"
#include "Observer.hpp"
#include "Strategy.hpp"

int main(const int argc, const char* argv[]) {

	TestSingleton();
	TestIterator();
	TestFactory();
	TestBuilder();
	TestObserver();
	TestStrategy();

	return 0;
}
