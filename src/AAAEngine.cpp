#include <AAAEngine.h>
#include <iostream>
#include <filesystem>
#include <map>
#include <vector>

namespace fs = std::filesystem;

#if defined(_WIN32) || defined(__MINGW32__)
    #include <windows.h>
    using LibHandle = HMODULE;
    #define LoadLib(name) LoadLibrary(name)
    #define GetFunc GetProcAddress
    #define CloseLib FreeLibrary
#else
    #include <dlfcn.h>
    using LibHandle = void*;
    #define LoadLib(name) dlopen(name, RTLD_LAZY)
    #define GetFunc dlsym
    #define CloseLib dlclose
#endif


// Часть ScriptModule
using CreateScriptFunc = Script* (*)();

class ScriptModule
{
private:
    LibHandle handle = nullptr;
    Script* script = nullptr;
public:
    bool Load(const char* libPath)
    {
        handle = LoadLib(libPath);
        if (!handle) return false;

        auto createFunc = (CreateScriptFunc)GetFunc(handle, "CreateScript");
        if (!createFunc) return false;

        script = createFunc();
        return true;
    }

    void Start()
    {
        if (script)
        {
            script->Start();
        }
    }

    void Update()
    {
        if (script)
        {
            script->Update();
        }
    }

    ~ScriptModule() {
        delete script;
        if (handle) CloseLib(handle);
    }
};

std::map<std::string, std::string> availableScripts;

// 1. Ищем папки с именем "build_scripts"
std::vector<fs::path> FindScriptsFolders(const fs::path& root) {
    std::vector<fs::path> result;

    // Проверяем, существует ли директория и доступна ли она
    if (root.empty()) {
        std::cerr << "Ошибка: передан пустой путь.\n";
        return result;
    }

    if (!fs::exists(root)) {
        std::cerr << "Ошибка: путь " << root << " не существует.\n";
        return result;
    }

    if (!fs::is_directory(root)) {
        std::cerr << "Ошибка: путь " << root << " не является директорией.\n";
        return result;
    }

    try {
        for (const auto& entry : fs::recursive_directory_iterator(root)) {
            if (entry.is_directory() && entry.path().filename() == "build_scripts") {
                result.push_back(entry.path());
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка при обходе директории: " << e.what() << std::endl;
    }

    return result;
}

// 2. В каждой найденной "Scripts" ищем .dll/.so рекурсивно
void ScanScriptsInFolder(const fs::path& folder) {
    for (const auto& entry : fs::recursive_directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            const auto& path = entry.path();
#ifdef _WIN32
            if (path.extension() == ".dll")
#else
            if (path.extension() == ".so")
#endif
            {
                std::string name = path.stem().string(); // имя файла без расширения
                availableScripts[name] = path.string();
                std::cout << "Found script: " << name << " -> " << path.string() << "\n";
            }
        }
    }
}


// main


int main() {
    std::cout << "Start!\n";
    fs::path rootPath = fs::current_path();
    if (rootPath.empty()) {
        std::cerr << "Ошибка: путь root пуст.\n";
        return 1;
    }
    std::vector<fs::path> scriptFolders = FindScriptsFolders(rootPath);
    for (const auto& folder : scriptFolders) {
        ScanScriptsInFolder(folder);
    }
    auto it = availableScripts.find("Main");
    if (it != availableScripts.end()) {
        ScriptModule mod;
        if (mod.Load(it->second.c_str())) {
            mod.Start();
        }
    } else {
        std::cerr << "Script not found: " << "Main" << "\n";
    }
    char ch;
    std::cin >> ch;
    return 0;
}

