#ifndef _H_IRQHANDLE
#define _H_IRQHANDLE

#include <stdint.h>

typedef void(*IRQFunc)(void);

class IRQHandle {
public:
	IRQHandle();
	IRQHandle(uint8_t id);
	IRQHandle(uint8_t id, IRQFunc& func_cp);
	~IRQHandle();

	void registerCallback(IRQFunc& func_cb);
	void callback();

protected:
	
	uint8_t ID;

	// The callback function pointer
	IRQFunc p_IRQFunc;
};

#endif