#pragma once

class Engine {
public:
	Engine() {}
	virtual ~Engine() {}

	virtual double currentTempC() const = 0;					/// ������� �����������
	virtual double currentTimeSec() const = 0;					/// ������� ����� ������ ���������
	virtual void start(double _init_temp_c) = 0;				/// ���� ���������
	virtual void doProgress(double _timestep_ms) = 0;			/// ������ ��� �� �������
};