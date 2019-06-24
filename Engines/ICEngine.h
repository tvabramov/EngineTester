#pragma once

#include "Engine.h"
#include <list>

class ICEngine : public Engine
{
public:
	ICEngine(double _I, std::list<std::pair<double, double>> _M,
		double _overheatTempC, double _Hm, double _Hv, double _C);
	~ICEngine() {}

	virtual double currentEngineTempC() const override { return mEngineTempC; }
	virtual double currentTimeSec() const override { return mTimeSec; }
	virtual double overheatTempC() const override { return mOverheatTempC; }

	virtual void restart(double _initTempC) override;
	virtual void doProgress(std::chrono::microseconds _timestepS) override;

private:
	// Статические характеристики
	double mI;											// Момент инерции, кг * м2
	std::list<std::pair<double, double>> mMFunc;		// Зависимость M (крутящего момента Н * м) от скорости вращения коленвала V (рад/с)
	double mOverheatTempC;								// Температура перегрева
	double mHm;											// Коэффициент зависимости скорости нагрева от куртящего момента (C/(Н * м * с))
	double mHv;											// Коэффициент зависимости скорости нагрева от скорости коленвала (C * с/ рад2)
	double mC;											// Коэффициент зависимости скорости охлаждения от температуры двигателя и окр среды (1 / с)
	// Текущие параметры
	double mEnvTempC;									// Температура окружающей среды
	double mEngineTempC;								// Текущая температура двигателя
	double mTimeSec;									// Время с момента старта
	double mV;											// Текущая скорость вращения коленвала
	//double mM;										// Текущий крутящий момент
	double getM(double _V) const;						// Расчет крутящего момента по mM
};
