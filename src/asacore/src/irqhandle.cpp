#include "irqhandle.hpp"
#include "irqexception.hpp"

#define DEFAULT_ID (0)

IRQHandle::IRQHandle() : ID(DEFAULT_ID) {
	// setup default function
	p_IRQFunc = []() {; };
}

IRQHandle::IRQHandle(uint8_t id) : 
	ID(id) {
	// setup default function
	p_IRQFunc = []() {; };
}

IRQHandle::IRQHandle(uint8_t id, IRQFunc& func_cp) : 
	ID(id) {
	// setup callback function
	p_IRQFunc = func_cp;
}

IRQHandle::~IRQHandle() {

}

void IRQHandle::registerCallback(IRQFunc& func_cb) {
	p_IRQFunc();
}

void IRQHandle::callback() {
	if (p_IRQFunc == nullptr) {
		throw IRQFuncNotExistException();
	}
	// Call the IRQ function
	p_IRQFunc();
}
