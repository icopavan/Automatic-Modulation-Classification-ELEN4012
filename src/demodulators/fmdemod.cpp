#include "fmdemod.h"

FmDemod::FmDemod(double modIndex, double fc):
    _demod(freqdem_create((float)modIndex)),
    _scale_fc(fc / modIndex)
{

}

FmDemod::~FmDemod()
{
    freqdem_destroy(_demod);
}

double FmDemod::demod(const std::complex<double> &sampleData)
{
    float res = 0.0f;

    freqdem_demodulate(_demod, {(float)sampleData.real(), (float)sampleData.imag()}, &res);

    return (double) res - _scale_fc;
}

void FmDemod::reset()
{
    freqdem_reset(_demod);
}

AMC::ModType FmDemod::modType()
{
    return AMC::ModType::FM;
}
