#include <array>
#include <iostream>

#include "Fractal.hpp"

class MandelbrotFractal : public Fractal
{
public:

    MandelbrotFractal(
            int width,
            int height,
            int max) noexcept
        : _width(width)
        , _height(height)
        , _max(max)
    {
    }

    void calculate(
            int* mat) noexcept
    {
        for (int row = 0; row < _height; row++)
        {
            for (int col = 0; col < _width; col++)
            {
                mat[row * _width + col] = calculate_point(row, col);
            }
        }
    }

private:

    int calculate_point(
            int row,
            int col) noexcept
    {
        double c_re = (col - _width / 2) * 4.0 / _width;
        double c_im = (row - _height / 2) * 4.0 / _width;
        double x = 0, y = 0;
        double r2;
        int iteration = 0;
        while (x * x + y * y < 4 && iteration < _max)
        {
            double x_new = x * x - y * y + c_re;
            y = 2 * x * y + c_im;
            x = x_new;
            iteration++;
        }
        return iteration;
    }

    int _width, _height, _max;
};