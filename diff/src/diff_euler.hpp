#pragma once

#include <optional>

template<typename T, typename H, typename Func>
H diffEuler1(T t0, H f0, Func F, T t, T dt, int max_iter_count) {
    std::optional<H> predF = F(t0, f0);
    if (!predF.has_value()) return f0;
    if (dt * (t - t0) < 0)
        dt = -dt;
    for (int i = 1; i < max_iter_count; i++) {
        bool isLastStep = (t - t0) * (t - t0 - dt) < 0;
        if (isLastStep) {
            dt = t - t0;
        }
        t0 += dt;
        f0 += dt * predF.value();
        predF = F(t0, f0);
        if (!predF.has_value()) return f0;
        if (isLastStep) break;
    }
    return f0;
}
