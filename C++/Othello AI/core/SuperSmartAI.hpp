//SUPERSMARTAI_HPP
#ifndef SUPERSMARTAI_HPP
#define SUPERSMARTAI_HPP

#include "OthelloAI.hpp"

namespace tsalako
{
	class SuperSmartAI : public OthelloAI
	{

	public:
		virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
	};
}
#endif
//SUPERSMARTAI_HPP