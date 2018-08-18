#include "Randomizer.h"

std::random_device CRandomizer::ourRandomDevice;
std::default_random_engine CRandomizer::ourRandomEngine;

void CRandomizer::Init()
{
	ourRandomEngine = std::default_random_engine(ourRandomDevice());
}
