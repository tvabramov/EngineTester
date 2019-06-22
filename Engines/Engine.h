#pragma once

class Engine {
public:
	Engine() {}
	virtual ~Engine() {}

	virtual double currentEngineTempC() const = 0;				// Текущая температура двигателя
	virtual double currentTimeSec() const = 0;					// Текущее время работы двигателя
	virtual double overheatTempC() const = 0;					// Температура перегрева
	virtual void restart(double _initTempC) = 0;				// Пуск двигателя
	virtual void doProgress(double _timestepS) = 0;				// Делаем шаг по времени.
																// TODO 1: вообще, должна передаваться некоторая схема расчета, регулирующая шаг по времени
																// TODO 2: использовать std::chrono
};