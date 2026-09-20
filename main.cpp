#include "Singleton.hpp"
#include "Iterator.hpp"
#include "Factory.hpp"
#include "Builder.hpp"
#include "Observer.hpp"

int main(const int argc, const char* argv[]) {

	TestSingleton();
	TestIterator();
	TestFactory();
	TestBuilder();
	TestObserver();

	return 0;
}
