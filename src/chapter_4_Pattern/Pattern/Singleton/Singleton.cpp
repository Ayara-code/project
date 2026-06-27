// Singleton.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <map>
#include <mutex>

// 现代C++推荐
class MeyerSingleton
{
public:
    static MeyerSingleton& getInstance()
    {
        static MeyerSingleton instance; //全局只有一份 线程安全
        return instance;
    }
private:
    MeyerSingleton() = default;
};

class LazySingleton
{
public:
    static LazySingleton* getInstance()
    {
        if (instance == nullptr)    
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr)    // 第二次检查，确保线程安全
            {
                instance = new LazySingleton();
            }
        }
        return instance;
    }

private:
    static LazySingleton* instance; //内存中只有一个
    static std::mutex mutex;

    LazySingleton() = default;

};

class EagerSingleton {
private:
    static EagerSingleton instance;

    EagerSingleton() = default;

public:
    static EagerSingleton& getInstance() {
        return instance;
    }
};
// 静态成员初始化
EagerSingleton EagerSingleton::instance;

class camera {};

class CameraManager
{
public:
    static CameraManager* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new CameraManager(); //唯一类对象
        }
        return instance;
    }

    void init()
    {

    }

    // 业务方法
    void openCamera(std::string cameraId) {
        auto it = _cameraIdMap.find(cameraId);
        if (it != _cameraIdMap.end()) {
            // 找到了，使用 it->second 访问 camera 对象
            camera& cam = it->second;
            // 使用 cam...
            // 调用相机的打开接口
            std::cout << cameraId << "Camera open!" << std::endl;
        }
        else {
            // 没有找到
            std::cout << "Camera not found!" << std::endl;
        }
    }

private:
    static CameraManager* instance; //内存中只有一个
    std::map<std::string, camera> _cameraIdMap; //相机序列号-》相机对象

    // 私有构造函数，防止外部实例化
    CameraManager() {}

    // 防止拷贝和赋值
    CameraManager(const CameraManager&) = delete;
    CameraManager& operator=(const CameraManager&) = delete;
};
CameraManager* CameraManager::instance = nullptr;

int main()
{
    std::string id = "5555";
    CameraManager::getInstance()->openCamera(id);

    std::cout << "Hello World!\n";
}


