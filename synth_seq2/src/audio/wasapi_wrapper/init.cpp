#include "init.hpp"

#include <Avrt.h>
#include <string>

REFERENCE_TIME REFTIMES_PER_SEC = 10000000;

REFERENCE_TIME REFTIMES_PER_MS = 10000;

void getEnumerator(WasapiWrapper& wasapiWrapper)
{
    CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
    IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);

    IMMDeviceEnumerator* enumerator = NULL;

    HRESULT hr = CoCreateInstance(
        CLSID_MMDeviceEnumerator,
        NULL,
        CLSCTX_ALL,
        IID_IMMDeviceEnumerator,
        (void**)&enumerator
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + toHex(hr) + ": getEnumerator");
    }
    else {
        std::cout << "SUCCESS: getEnumerator" << std::endl;
    }

    wasapiWrapper.enumerator = enumerator;
}

void getDevice(WasapiWrapper& wasapiWrapper)
{
    IMMDevice* device = NULL;

    HRESULT hr = wasapiWrapper.enumerator->GetDefaultAudioEndpoint(
        eRender,
        eConsole,
        &device
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + toHex(hr) + ": getDevice");
    }
    else {
        std::cout << "SUCCESS: getDevice" << std::endl;
    }

    wasapiWrapper.device = device;
}

void getAudioClient(WasapiWrapper& wasapiWrapper)
{
    IAudioClient* client = NULL;
    IID IID_IAudioClient = __uuidof(IAudioClient);

    HRESULT hr = wasapiWrapper.device->Activate(
        IID_IAudioClient,
        CLSCTX_ALL,
        NULL,
        (void**)&client
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + toHex(hr) + ": getAudioClient");
    }
    else {
        std::cout << "SUCCESS: getAudioClient" << std::endl;
    }

    wasapiWrapper.audioClient = client;
}

void getDevicePeriod(WasapiWrapper& wasapiWrapper, REFERENCE_TIME& devicePeriod)
{
    REFERENCE_TIME defaultDevicePeriod = 0;
    REFERENCE_TIME minimumDevicePeriod = 0;

    HRESULT hr = wasapiWrapper.audioClient->GetDevicePeriod(&defaultDevicePeriod, &minimumDevicePeriod);

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + toHex(hr) + ": getDevicePeriod");
    }
    else {
        std::cout << "SUCCESS: getDevicePeriod" << std::endl;
    }

    devicePeriod = minimumDevicePeriod;
}

WAVEFORMATEXTENSIBLE getWaveFormat()
{
    WAVEFORMATEXTENSIBLE w = {};

    w.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
    w.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
    w.Format.cbSize = 22;
    w.Format.nChannels = 2;
    w.Format.nSamplesPerSec = 44100;
    w.Format.wBitsPerSample = 32;
    w.Samples.wValidBitsPerSample = 24;
    w.Format.nBlockAlign = (w.Format.nChannels * w.Format.wBitsPerSample) / 8;
    w.Format.nAvgBytesPerSec = w.Format.nSamplesPerSec * w.Format.nBlockAlign;

    return w;
}

void checkFormatSupport(WasapiWrapper& wasapiWrapper)
{
    WAVEFORMATEX match = {0};
    WAVEFORMATEX* p_match = &match;

    HRESULT hr = wasapiWrapper.audioClient->IsFormatSupported(
        AUDCLNT_SHAREMODE_SHARED,
        &wasapiWrapper.waveFormat.Format,
        &p_match
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + toHex(hr) + ": checkFormatSupport");
    }
    else {
        std::cout << "SUCCESS: checkFormatSupport" << std::endl;
    }
}

void initAudioClient(WasapiWrapper& wasapiWrapper, REFERENCE_TIME minimumDevicePeriod)
{
    std::cout << "minimumDevicePeriod: " << minimumDevicePeriod << std::endl;

    // 100 ms buffer time
    REFERENCE_TIME period = REFTIMES_PER_MS * 100;

    HRESULT hr = wasapiWrapper.audioClient->Initialize(
        AUDCLNT_SHAREMODE_SHARED,
        AUDCLNT_STREAMFLAGS_EVENTCALLBACK,
        minimumDevicePeriod,
        // period,
        0,
        &wasapiWrapper.waveFormat.Format,
        NULL
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + toHex(hr) + ": initAudioClient");
    }
    else {
        std::cout << "SUCCESS: initAudioClient" << std::endl;
    }
}

void getRenderClient(WasapiWrapper& wasapiWrapper)
{
    IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);
    IAudioRenderClient *renderClient = NULL;

    HRESULT hr = wasapiWrapper.audioClient->GetService(
        IID_IAudioRenderClient,
        (void**)&renderClient
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + toHex(hr) + ": getRenderClient");
    }
    else {
        std::cout << "SUCCESS: getRenderClient" << std::endl;
    }

    wasapiWrapper.renderClient = renderClient;
}

void initEvent(WasapiWrapper& wasapiWrapper)
{
    HANDLE hEvent = CreateEvent(nullptr, false, false, nullptr);

    if (hEvent == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("ERROR: CreateEvent");
    }

    HRESULT hr = wasapiWrapper.audioClient->SetEventHandle(hEvent);

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + toHex(hr) + ": initEvent");
    }
    else {
        std::cout << "SUCCESS: initEvent" << std::endl;
    }

    wasapiWrapper.hEvent = hEvent;
}

void initTask(WasapiWrapper& wasapiWrapper)
{
    // increase thread priority
    unsigned long taskIndex = 0;
    wasapiWrapper.hTask = AvSetMmThreadCharacteristics(TEXT("Pro Audio"), &taskIndex);

    if (wasapiWrapper.hTask == NULL) {
        throw std::runtime_error("ERROR: initTask");
    }
    else {
        std::cout << "SUCCESS: initTask" << std::endl;
    }
}

void init(WasapiWrapper& wasapiWrapper)
{
    getEnumerator(wasapiWrapper);

    getDevice(wasapiWrapper);

    getAudioClient(wasapiWrapper);

    wasapiWrapper.waveFormat = getWaveFormat();

    checkFormatSupport(wasapiWrapper);

    REFERENCE_TIME minimumDevicePeriod = 0;

    getDevicePeriod(wasapiWrapper, minimumDevicePeriod);

    initAudioClient(wasapiWrapper, minimumDevicePeriod);

    getRenderClient(wasapiWrapper);

    initEvent(wasapiWrapper);

    initTask(wasapiWrapper);
}

void cleanUp(WasapiWrapper& wasapiWrapper)
{
    if (wasapiWrapper.enumerator != NULL) {
        wasapiWrapper.enumerator->Release();
    }

    if (wasapiWrapper.device != NULL) {
        wasapiWrapper.device->Release();
    }

    if (wasapiWrapper.audioClient != NULL) {
        wasapiWrapper.audioClient->Release();
    }

    if (wasapiWrapper.renderClient != NULL) {
        wasapiWrapper.renderClient->Release();
    }

    if (wasapiWrapper.hEvent != NULL) {
        CloseHandle(wasapiWrapper.hEvent);
    }

    if (wasapiWrapper.hTask != NULL) {
        AvRevertMmThreadCharacteristics(wasapiWrapper.hTask);
    }
}
