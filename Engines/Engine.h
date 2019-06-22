#pragma once

class Engine {
public:
	Engine() {}
	virtual ~Engine() {}

	virtual double currentEngineTempC() const = 0;				// ������� ����������� ���������
	virtual double currentTimeSec() const = 0;					// ������� ����� ������ ���������
	virtual double overheatTempC() const = 0;					// ����������� ���������
	virtual void restart(double _initTempC) = 0;				// ���� ���������
	virtual void doProgress(double _timestepS) = 0;				// ������ ��� �� �������.
																// TODO 1: ������, ������ ������������ ��������� ����� �������, ������������ ��� �� �������
																// TODO 2: ������������ std::chrono
};