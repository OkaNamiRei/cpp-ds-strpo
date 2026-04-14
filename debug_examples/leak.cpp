#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>

int main() {
#ifdef _DEBUG
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

    _CrtMemState start_state{};
    _CrtMemState end_state{};
    _CrtMemState diff_state{};
    _CrtMemCheckpoint(&start_state);
#endif

    std::cout << "Allocating memory and intentionally not freeing it..." << std::endl;

    int* data = new int[128];
    data[0] = 42;

    std::cout << "data[0] = " << data[0] << std::endl;

    // delete[] data; // специально пропущено

#ifdef _DEBUG
    _CrtMemCheckpoint(&end_state);

    if (_CrtMemDifference(&diff_state, &start_state, &end_state)) {
        std::cout << "Memory difference detected." << std::endl;
        _CrtMemDumpStatistics(&diff_state);
        _CrtDumpMemoryLeaks();
    }
    else {
        std::cout << "No leaks detected." << std::endl;
    }
#endif

    return 0;
}