#pragma once
#ifndef MOTHERSHIP_H
#define MOTHERHSHIP_H

namespace rmas {
	class Mothership : public Object {
	private:
		Shape shape = Shape::COMPOUND;
	};
}

#endif