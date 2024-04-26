// HDRStatusGet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <dxgi1_6.h>

#pragma comment(lib, "DXGI.lib")

int main()
{
    IDXGIFactory* pFactory = nullptr;
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
    if (FAILED(hr)) {
        std::cerr << "Failed to create DXGI factory: " << hr << std::endl;
        return hr;
    }

    // Step 2: Enumerate Adapters
    IDXGIAdapter* pAdapter = nullptr;
    hr = pFactory->EnumAdapters(0, &pAdapter);
    if (FAILED(hr)) {
        std::cerr << "Failed to enumerate adapters: " << hr << std::endl;
        pFactory->Release();
        return hr;
    }

    // Step 3: Enumerate Outputs
    IDXGIOutput* pOutput = nullptr;
    hr = pAdapter->EnumOutputs(0, &pOutput);
    if (FAILED(hr)) {
        std::cerr << "Failed to enumerate outputs: " << hr << std::endl;
        pAdapter->Release();
        pFactory->Release();
        return hr;
    }

    IDXGIOutput6* pOutput6;
    hr = pOutput->QueryInterface(__uuidof(IDXGIOutput6), (void**)&pOutput6);
    if (SUCCEEDED(hr)) {
        // Use output6...
        DXGI_OUTPUT_DESC1 desc1;
        pOutput6->GetDesc1(&desc1);
        if (desc1.ColorSpace == DXGI_COLOR_SPACE_TYPE::DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            std::cout << "HDR Enabled" << std::endl;
        }
        else {
            std::cout << "HDR Disabled" << std::endl;
        }
    }
    else {
        pAdapter->Release();
        pFactory->Release();
        pOutput->Release();
        return hr;
    }

    pAdapter->Release();
    pFactory->Release();
    pOutput->Release();
    pOutput6->Release();

    return 0;
}
