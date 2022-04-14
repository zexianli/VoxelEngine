#include "block.h"

Block::Block(BlockID ID, glm::vec3 position, bool isSolid) {
	this->ID = ID;
	this->position = position;
	this->isSolid = isSolid;
}

Block ::~Block() {
}
