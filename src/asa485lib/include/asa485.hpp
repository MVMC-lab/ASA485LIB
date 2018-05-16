#ifndef _H_ASA485
#define _H_ASA485

#include"asacomm.hpp"

// Header for uint8_t definition
#include"stdint.h"

#include<vector>

#define PREFIX_DATA_TYPE		('D')
#define PREFIX_TRIGGLE_TYPE		('I')
#define PREFIX_GET_STATE_TYPE	('S')

class ASA485 : public ASAComm {
public:
	
	ASA485();
	ASA485(std::string port);

	~ASA485();

	/* [Wrap] read and write data method */
	size_t sendWrapMultiBytes(std::vector<uint8_t> data);
	bool sendWrapByte(uint8_t data);

	/* [Wrap] send Trigger signal(interrupt) to slaves*/
	bool sendTrigger();

	/* [Wrap] send Trigger signal(interrupt) to slaves*/
	bool getISR();

private:
	
	// Data buffer
	std::vector<uint8_t> _data_buffer;




};

#endif // _H_ASA485