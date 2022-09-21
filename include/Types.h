//
// Created by mkd on 9/21/22.
//

#ifndef GANYMEDE_TYPES_H
#define GANYMEDE_TYPES_H


enum class POSITIONAL_FLAG : unsigned {
	NONE = 1 << 0,
	VERTICAL = 1 << 1,
	HORIZONTAL = 1 << 2,
	UP = 1 << 3,
	DOWN = 1 << 4,
	LEFT = 1 << 5,
	RIGHT =  1 << 6
};


#endif //GANYMEDE_TYPES_H
