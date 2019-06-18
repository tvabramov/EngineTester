#pragma once

class Engine {
public:
	Engine() {}
	virtual ~Engine() {}

	virtual double currentTempC() const = 0;					/// Текущая температура
	virtual double currentTimeSec() const = 0;					/// Текущее время работы двигателя
	virtual void start(double _init_temp_c) = 0;				/// Пуск двигателя
	virtual void doProgress(double _timestep_ms) = 0;			/// Делаем шаг по времени
};