#include "irqhandle.hpp"
#include "irqexception.hpp"

#define DEFAULT_ID (-1)

IRQHandle::IRQHandle() : ID(DEFAULT_ID) {
	// setup default function
	p_IRQFunc = [](ASA485*) {; };
}

IRQHandle::IRQHandle(int id) : 
	ID(id) {
	// setup default function
	p_IRQFunc = [](ASA485*) {; };
}

IRQHandle::IRQHandle(int id, IRQFunc func_cp) : 
	ID(id) {
	// setup callback function
	p_IRQFunc = func_cp;
}

IRQHandle::~IRQHandle() {

}

void IRQHandle::registerCallback(IRQFunc func_cb) {
	p_IRQFunc = func_cb;
}

void IRQHandle::callback(ASA485* p_asa485) {
	if (p_IRQFunc == nullptr) {
		throw IRQFuncNotExistException();
	}
	// Call the IRQ function
	p_IRQFunc(p_asa485);
}

int IRQHandle::getID() {
	return ID;
}
void IRQHandle::setID(int id) {
	ID = id;
}
