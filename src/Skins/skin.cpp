#include "skin.h"

float* Skin::getFreq()
{
    return &freq;
}

float* Skin::getLacunarity()
{
    return &lacunarity;
}

float* Skin::getGain()
{
    return &gain;
}

int* Skin::getOctaves()
{
    return &octaves;
}

float* Skin::getStrength()
{
    return &weightedStrength;
}

void Skin::setNoise(FastNoiseLite& noise)
{
    noise.SetFrequency(freq);
    noise.SetFractalOctaves(octaves);
    noise.SetFractalLacunarity(lacunarity);
    noise.SetFractalGain(gain);
    noise.SetFractalWeightedStrength(weightedStrength);
}
