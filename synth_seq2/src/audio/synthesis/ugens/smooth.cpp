#include "smooth.hpp"

double Smooth::get(double in)
{
    runningSum -= history[writeHead];
    runningSum += in;
    history[writeHead] = in;
    writeHead = (writeHead + 1) % history.size();
    return (runningSum / history.size());
}
