#include "OverheatStand.h"

double OverheatStand::doTest(std::shared_ptr<Engine> _engine, double _initTempC)
{
	if (!_engine)
		return -1.0;		// It would be better to use std::optional

	_engine->restart(_initTempC);

	while (_engine->currentEngineTempC() < _engine->overheatTempC())
		_engine->doProgress(1.0e-4);

	return _engine->currentTimeSec();
}