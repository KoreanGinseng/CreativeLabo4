#include "TextureManager.h"

CTextureManager::CTextureManager(void) {
}

CTextureManager::~CTextureManager(void) {
}

CTextureManager & CTextureManager::GetInstance(void) {
    static CTextureManager instance;
    return instance;
}

CTexturePtr& CTextureManager::Get(const std::string & key) {
    return m_Manager[key];
}

bool CTextureManager::Register(const std::string & key, const std::string & file) {
    auto& data = m_Manager[key];
    if (data != nullptr) {
        data->Release();
        data = nullptr;
    }
    data = std::make_shared<CTexture>();
    return data->Load(file.c_str());
}

bool CTextureManager::Release(const std::string & key) {
    if (key == "") {
        for (auto& it : m_Manager) {
            it.second->Release();
            it.second = nullptr;
        }
        return true;
    }
    else {
        auto& data = m_Manager[key];
        if (data == nullptr) {
            return false;
        }
        return data->Release();
    }
    return false;
}
