#include "terrain.hpp"

namespace simciv
{

Terrain::Terrain()
{
	ground.create(16,16);
	ground.fill(G_ROCK);
}

Terrain::~Terrain()
{

}



} // namespace simciv

