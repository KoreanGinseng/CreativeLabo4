#pragma once
#include "Framework/Common/Singleton.h"
#include <random>

class RandomUtilities : public Sample::Singleton<RandomUtilities> {
    friend Sample::Singleton<RandomUtilities>;
private:

    std::random_device device_;
    std::mt19937       engine_;

public:

    RandomUtilities() : device_(), engine_(device_()) {}
    ~RandomUtilities() {}

    uint32_t Random() {
        return engine_();
    }

    uint32_t Random(uint32_t h) {
        return Random() % h;
    }

    uint32_t Random(uint32_t l, uint32_t h) {
        auto r = Random(h);
        if (r < l) {
            r += l;
        }
        return r;
    }
};