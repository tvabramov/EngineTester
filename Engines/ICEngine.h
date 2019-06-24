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
	// ����������� ��������������
	double mI;											// ������ �������, �� * �2
	std::list<std::pair<double, double>> mMFunc;		// ����������� M (��������� ������� � * �) �� �������� �������� ��������� V (���/�)
	double mOverheatTempC;								// ����������� ���������
	double mHm;											// ����������� ����������� �������� ������� �� ��������� ������� (C/(� * � * �))
	double mHv;											// ����������� ����������� �������� ������� �� �������� ��������� (C * �/ ���2)
	double mC;											// ����������� ����������� �������� ���������� �� ����������� ��������� � ��� ����� (1 / �)
	// ������� ���������
	double mEnvTempC;									// ����������� ���������� �����
	double mEngineTempC;								// ������� ����������� ���������
	double mTimeSec;									// ����� � ������� ������
	double mV;											// ������� �������� �������� ���������
	//double mM;										// ������� �������� ������
	double getM(double _V) const;						// ������ ��������� ������� �� mM
};
