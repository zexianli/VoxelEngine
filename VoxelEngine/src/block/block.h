#ifndef BLOCK_H
#define BLOCK_H
#include <glm/glm.hpp>
#include "blockID.h"

class Block {
private:
	BlockID ID;
	glm::vec3 position;
	bool isSolid;

public:
	Block(BlockID ID, glm::vec3 position, bool isSolid);
	~Block();



};

#endif