#ifndef _H_IRQHANDLE
#define _H_IRQHANDLE

#include <stdint.h>
#include "asa485.hpp"

typedef void(*IRQFunc)(ASA485* p_asacomm);

class IRQHandle {
public:
	IRQHandle();
	IRQHandle(int id);
	IRQHandle(int id, IRQFunc func_cp);
	~IRQHandle();

	void registerCallback(IRQFunc func_cb);
	void callback(ASA485* p_asa485);

	int getID();
	void setID(int id);

protected:
	
	int ID;

	// The callback function pointer
	IRQFunc p_IRQFunc;
};

#endif