#ifndef _H_ISRMANAGER
#define _H_ISRMANAGER

#include <vector>

#include "irqhandle.hpp"
#include "asa485.hpp"


using namespace std;

class IRQManager {
public:
	IRQManager();
	~IRQManager();
	
	void spinOnce();

	void registerIRQHandle(IRQHandle& irqhandle);
	vector<IRQHandle> getIRQHandleList();

private:

};


#endif // _H_ISRMANAGER