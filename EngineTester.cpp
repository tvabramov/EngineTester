#include <iostream>
#include <future>
#include <chrono>
#include <memory>
#include "Engines/ICEngine.h"
#include "Stands/OverheatStand.h"

using namespace std;

template<class R, class Rep, class Period>
bool waitForReady(const future<R> &_f, const std::chrono::duration<Rep, Period>& _timeout)							// TODO: max time duration
{
	auto startTime = chrono::system_clock::now();

	int iter = 0;
	vector<char> progress{ '|', '/', '-', '\\' };				// TODO: it would be better to use constexpr
	while (_f.wait_for(250ms) != future_status::ready) {

		cout << "\rWaiting for result... " << progress[iter++ % progress.size()];
		
		if ((chrono::system_clock::now() - startTime) > _timeout) {

			cout << endl;
			return false;
		}
	}

	cout << endl;
	return true;
}


int main()
{
	double envTemp;
	cout << "Enter ambient temperature: ";
	cin >> envTemp;

	shared_ptr<Engine> engine(new ICEngine(10, { {0.0, 20.0}, {75.0, 75.0}, {150.0, 100.0}, {200.0, 105.0}, {250.0, 75.0}, {300.0, 0.0} }, 110.0, 0.01, 0.0001, 0.1));

	auto f = async(launch::async, &OverheatStand::doTest, engine, envTemp, 100us);

	if (waitForReady(f, 10s)) {

		try {
			cout << "Overheating time = " << f.get() << " sec" << endl;
		}
		catch (const exception& e) {

			cout << "Caught exception: " << e.what() << endl;
		}
	}
	else {

		cout << "Waiting time is over" << endl;
	}

	return EXIT_SUCCESS;
}

