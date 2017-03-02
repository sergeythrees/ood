﻿#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

enum class CoffeeSize
{
	Single,
	Double
};

std::string ToString(const CoffeeSize& coffeeSize)
{
	switch (coffeeSize)
	{
	case CoffeeSize::Double :
		return "Double ";
	default:
		break;
	}
	return std::string();

}
// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(const CoffeeSize& coffeeSize = CoffeeSize::Single) 
		:CCoffee(ToString(coffeeSize) + "Capuccino") , 
		m_coffeeSize(coffeeSize)
	{}

	double GetCost() const override 
	{
		double cost = 80;
		switch (m_coffeeSize)
		{
		case CoffeeSize::Double:
			cost = 120;
		default:
			break;
		}
		return cost; 
	}
private:
	CoffeeSize m_coffeeSize;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(const CoffeeSize& coffeeSize = CoffeeSize::Single)
		:CCoffee(ToString(coffeeSize) + "Latte")
	{}

	double GetCost() const override 
	{
		double cost = 90;
		switch (m_coffeeSize)
		{
		case CoffeeSize::Double:
			cost = 130;
		default:
			break;
		}
		return cost;
	}
private:
	CoffeeSize m_coffeeSize;
};

// Чай
enum TeaVariete
{
	Black,
	Oolong,
	Green,
	White
};
std::string ToString(const TeaVariete& variete)
{
	switch (variete)
	{
	case TeaVariete::Oolong:
		return "Oolong";
	case TeaVariete::Black:
		return "Black";
	case TeaVariete::Green:
		return "Green";
	case TeaVariete::White:
		return "White";
	default:
		break;
	}
	return std::string();

}

class CTea : public CBeverage
{
public:
	CTea(const TeaVariete& teaVariete = TeaVariete::Black) 
		:CBeverage(ToString(teaVariete) + " Tea") 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake() 
		:CBeverage("Milkshake") 
	{}

	double GetCost() const override 
	{ 
		return 80; 
	}
};
