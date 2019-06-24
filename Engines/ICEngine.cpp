#include "ICEngine.h"
#include <algorithm>
//#include <iostream>

// _MFunc must be sorter in asc order
ICEngine::ICEngine(double _I, std::list<std::pair<double, double>> _MFunc,
	double _overheatTempC, double _Hm, double _Hv, double _C) :
	Engine(), mI(_I), mMFunc(std::move(_MFunc)),
	mOverheatTempC(_overheatTempC), mHm(_Hm), mHv(_Hv), mC(_C),
	mEnvTempC(0.0), mEngineTempC(0.0), mTimeSec(0.0), mV(0.0), mM(0.0)
{
}

void ICEngine::restart(double _initTempC)
{
	mEngineTempC = mEnvTempC = _initTempC;
	mTimeSec = mV = 0.0;
	mM = getM(mV);

	// Comment it if you do not need
	/*{
		std::cout << "===== Engine Restart =====" << std::endl;
		std::cout << "\tEnv temp = " << mEnvTempC << " sec" << std::endl;
		std::cout << "\tEng temp = " << mEngineTempC << " C" << std::endl;
	}*/
}

// TODO: По идее, сюда должна передаваться схема расчета.
// Текущая линейная схема работает кооректно только на маленьких шагах по времени
void ICEngine::doProgress(std::chrono::microseconds _timestepS)
{
	// Comment it if you do not need
	/*{
		std::cout << "----- New Iteration -----" << std::endl;
		std::cout << "\tDuration = " << mTimeSec << " sec" << std::endl;
		std::cout << "\tEng temp = " << mEngineTempC << " C" << std::endl;
		std::cout << "\tV        = " << mV << " rad/s" << std::endl;
		std::cout << "\tM        = " << mM << " H * m" << std::endl;
		std::cout << "\tAcc      = " << mM / mI << " H * m" << std::endl;
	}*/

	double tsSec = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(_timestepS).count()) / 1.0e+6;

	double Vh = mM * mHm + mV * mV * mHv;
	double Vc = mC * (mEnvTempC - mEngineTempC);

	mEngineTempC += (Vh - Vc) * tsSec;

	mV += tsSec * (mM / mI);
	mM = getM(mV);

	mTimeSec += tsSec;
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