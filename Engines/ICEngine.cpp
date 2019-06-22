#include "ICEngine.h"
#include <algorithm>

// _MFunc must be sorter in asc order
ICEngine::ICEngine(double _I, std::list<std::pair<double, double>> _MFunc,
	double _overheatTempC, double _Hm, double _Hv, double _C) :
	Engine(), mI(_I), mMFunc(std::move(_MFunc)),
	mOverheatTempC(_overheatTempC), mHm(_Hm), mHv(_Hv), mC(_C),
	mEnvTemp(0.0), mEngineTempC(0.0), mTimeSec(0.0), mV(0.0), mM(0.0)
{
}

void ICEngine::restart(double _initTempC)
{
	mEngineTempC = mEnvTemp = _initTempC;
	mTimeSec = mV = 0.0;
	mM = getM(mV);
}

// TODO: По идее, сюда должна передаваться схема расчета.
// Текущая линейная схема работает кооректно только на маленьких шагах по времени
void ICEngine::doProgress(double _timestepS)
{
	if (_timestepS <= 0.0)
		return;

	double Vh = mM * mHm + mV * mV * mHv;
	double Vc = mC * (mEnvTemp - mEngineTempC);

	mEngineTempC += (Vh - Vc) * _timestepS;

	mV += _timestepS * (mM / mI);
	mM = getM(mV);

	mTimeSec += _timestepS;
}

double ICEngine::getM(double _V) const
{
	if (mMFunc.empty())
		return 0.0;					// TODO: maybe throw exc
	
	auto it_right = std::upper_bound(mMFunc.begin(), mMFunc.end(), std::make_pair(_V, 0.0),
		[](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });

	if (it_right == mMFunc.begin())
		return it_right->second;				// Const extrapolation
	
	if (it_right == mMFunc.end())
		return (--it_right)->second;			// Const extrapolation

	auto it_left = std::prev(it_right);

	double l = (_V - it_left->first) / (it_right->first - it_left->first);

	return (1.0 - l) * it_left->second + l * it_right->second;
}