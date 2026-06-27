// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "AlgoInterface.h"
#include "AlgoFactory.h"

REGISTER_ALGORITHM(CannyEdgeDetector, "CannyEdgeDetector")
REGISTER_ALGORITHM(SIFTFeatureExtractor, "SIFTFeatureExtractor")
REGISTER_ALGORITHM(HoughLineDetector, "HoughLineDetector")
REGISTER_ALGORITHM(ORBFeatureExtractor, "ORBFeatureExtractor")

//namespace {
//    struct CannyEdgeDetetorRegistrar {
//        CannyEdgeDetetorRegistrar() {
//            AlgorithmFactory::getInstance().registerAlgorithm<CannyEdgeDetetor>("CannyEdgeDetetor");
//        }
//    } CannyEdgeDetetorRegistrarInstance;
//}
//
//namespace {
//    struct SIFTFeatureExtractorRegistrar {
//        SIFTFeatureExtractorRegistrar() {
//            AlgorithmFactory::getInstance().registerAlgorithm<SIFTFeatureExtractor>("SIFTFeatureExtractor");
//        }
//    } SIFTFeatureExtractorRegistrarInstance;
//}

int main()
{
	// 手动注册
	auto& factory = AlgorithmFactory::getInstance();

#ifdef Debug
	// 方式1：使用模板注册
	factory.registerAlgorithm<CannyEdgeDetetor>("Canny");

	// 方式2：使用通用注册
	factory.registerAlgorithm("HoughLineDetector", []()->std::unique_ptr<HoughLineDetector>
		{
			auto algo = std::make_unique<HoughLineDetector>();
			// 自定义创建逻辑
			return algo;
		});
#endif //  Debug

	
	// 演示工厂使用
	factory.printAvailableAlgorithms();	// 打印可用算法

	// 创建算法实例
	std::cout << "\nCreating algorithms:\n";

	// 使用宏注册的算法
	auto canny1 = factory.createAlgorithm("CannyEdgeDetetor");
	if (canny1)
	{
		std::cout << "Created: " << canny1->getName() << "\n";
		canny1->process(cv::Mat());
	}

	std::cout << "hello world" << std::endl;
}

