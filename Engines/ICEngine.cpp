#include "ICEngine.h"

ICEngine::ICEngine() :
	Engine()
{

}

double ICEngine::currentTempC() const
{
	return mTempC;
}

double ICEngine::currentTimeSec() const
{
	return mTimeSec;
}

void ICEngine::start(double _initTemp)
{
	mTimeSec = 0.0;
}

void ICEngine::doProgress(double _timestep_ms)
{
	if (_timestep_ms > 0.0)
		mTimeSec += _timestep_ms;
}