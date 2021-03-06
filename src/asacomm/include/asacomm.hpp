#ifndef _H_ASACOMM
#define _H_ASACOMM

#include "serial/serial.h"
#include <vector>

class ASAComm {
public:
	ASAComm();
	~ASAComm();

	/* Control method */
	bool connect();
	bool isConnect();
	
	/* read and write method */
	size_t writeMultiBytes(std::vector<uint8_t> &data);
	bool writeByte(uint8_t data);

	std::vector<uint8_t> readMultiBytes(size_t count);
	uint8_t readByte();

	/* Configure method */
	std::string getPort();
	bool setPort(std::string port);

	bool setBaudrate(unsigned int baudrate);
	unsigned int getBaudrate();

	bool setTimeout(unsigned int timeout_ms);
	unsigned int getTimeout();

	std::vector<std::string> getDeviceList();

protected:
	serial::Serial m_serial;

private:
	
	unsigned int m_baudrate;
	std::string m_port;
	unsigned int m_timeout;

	// IO buffer
	std::vector<uint8_t> _buffer;

};

#endif // !_H_ASACOMM