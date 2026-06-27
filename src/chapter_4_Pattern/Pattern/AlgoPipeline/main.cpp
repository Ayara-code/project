#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
#include "parseAlgoJson.h"
#include "AlgoInterface.h"
#include "AlgoPipeline.h"

REGISTER_ALGORITHM(CannyEdgeDetector, "CannyEdgeDetector")
REGISTER_ALGORITHM(SIFTFeatureExtractor, "SIFTFeatureExtractor")
REGISTER_ALGORITHM(HoughLineDetector, "HoughLineDetector")
REGISTER_ALGORITHM(ORBFeatureExtractor, "ORBFeatureExtractor")

int main()
{
	std::cout << "Hello world!\n";

	std::ifstream file("C:/Users/ASUS/Desktop/pipeline1.json");
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open file.");
	}

	// 使用字符串流读取整个文件
	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string strJson = buffer.str();
	std::cout << strJson << std::endl;

	// 反序列化
	auto algos = parseAlgoJson::getInstance().parseFromJson(strJson);
	auto pipeline = AlgorithmPipeline("pipeline", std::move(algos));

	cv::Mat src, dst;
	pipeline.process(src, dst);

	return 0;
}