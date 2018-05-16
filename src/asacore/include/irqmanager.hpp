#ifndef _H_ISRMANAGER
#define _H_ISRMANAGER

#include <vector>

#include "irqhandle.hpp"
#include "asa485.hpp"


using namespace std;

class IRQManager {
public:
	IRQManager(ASA485& asa_comm);
	~IRQManager();
	
	void spinOnce();

	IRQHandle& findIRQHandle(int id);
	size_t getCount();

	void registerIRQHandle(IRQHandle& irqhandle);
	vector<IRQHandle> getIRQHandleList();

private:

	vector<IRQHandle> m_IRQHandles;

	ASA485* p_asacomm;
};


#endif // _H_ISRMANAGER