// EngineTester.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <future>
#include <chrono>
#include <memory>
#include "Engines/ICEngine.h"
#include "Stands/OverheatStand.h"

using namespace std;

template<typename R>
void waitForReady(std::future<R> const& f)
{
	int iter = 0;
	vector<char> progress{ '|', '/', '-', '\\' };				/// TODO: it would be better to use constexpr
	while (f.wait_for(250ms) != future_status::ready) {
		cout << "\rWaiting for result... " << progress[iter++ % progress.size()];
	}
	cout << endl;
}


int main(int _argc, char* _argv[])
{
	std::shared_ptr<Engine> engine(new ICEngine(10, { {0, 20}, {75, 75}, {150, 100}, {200, 105}, {250, 75}, {300, 0} }, 110.0, 0.01, 0.0001, 0.1));

	auto f = std::async(launch::async, &OverheatStand::doTest, engine, 20.0);

	waitForReady(f);

	try {
		cout << "Result = " << f.get() << endl;
	}
	catch (const exception& e) {

		std::cout << "Caught exception: " << e.what() << endl;
	}

	return EXIT_SUCCESS;
}

