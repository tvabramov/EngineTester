#pragma once

#include <memory>
#include <chrono>
#include "../Engines/Engine.h"

class OverheatStand {

public:
	static double doTest(std::shared_ptr<Engine> _engine, double _initTempC, std::chrono::microseconds _timeStep);

private:
	OverheatStand() {};
	virtual ~OverheatStand() {}
};