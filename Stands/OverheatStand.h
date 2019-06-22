#pragma once

#include <memory>
#include "Engine.h"

class OverheatStand {

public:
	static double doTest(std::shared_ptr<Engine> _engine, double _initTempC);

private:
	OverheatStand() {};
	virtual ~OverheatStand() {}
};