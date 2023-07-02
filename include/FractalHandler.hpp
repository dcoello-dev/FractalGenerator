#include <memory>

#include "MandelbrotFractal.hpp"

struct Fractal_Handler
{
    static std::unique_ptr<Fractal> get_instance(
            int w,
            int h,
            int m) noexcept

    {
        return std::make_unique<MandelbrotFractal>(w, h, m);
    }

};