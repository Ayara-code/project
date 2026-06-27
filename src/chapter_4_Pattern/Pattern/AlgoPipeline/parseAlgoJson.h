#pragma once
#include "AlgoInterface.h"
#include "AlgoFactory.h"
#include "json.hpp"
#include <vector>
using Algos = std::vector<std::unique_ptr<AlgorithmInterface>>;

class parseAlgoJson
{
public:
	static parseAlgoJson& getInstance()
	{
		static parseAlgoJson instance;
		return instance;
	}

	// 反序列化
	Algos parseFromJson(const std::string& jsonStr);
	// 序列化
	std::string parseToJson(const Algos& algos);

private:
	parseAlgoJson() = default;
};



