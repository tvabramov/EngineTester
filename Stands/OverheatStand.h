#pragma once

#include <memory>
#include "../Engines/Engine.h"		// TODO: include paths

class OverheatStand {

public:
	static double doTest(std::shared_ptr<Engine> _engine, double _initTempC);

private:
	OverheatStand() {};
	virtual ~OverheatStand() {}
};