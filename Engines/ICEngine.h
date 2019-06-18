#pragma once

#include "Engine.h"

class ICEngine : public Engine
{
public:
	ICEngine() {}
	virtual ~ICEngine() {}

	virtual double currentTempC() const override;
	virtual double currentTimeSec() const override;
	virtual void start(double _init_temp_c) override;
	virtual void doProgress(double _timestep_ms) override;

private:
	double mTempC;
	double mTimeSec;
};
