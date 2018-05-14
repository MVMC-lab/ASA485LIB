#include "ASA485.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	
	ASA485 asa_comm("COM12");

	asa_comm.setBaudrate(38400);
	asa_comm.setTimeout(1000);

	if (asa_comm.connect()) {
		std::cout
			<< "Connect "
			<< asa_comm.getPort()
			<< "successful!"
			<< std::endl;
	}
	else {
		std::cout
			<< "Connect "
			<< asa_comm.getPort()
			<< "Failed!"
			<< std::endl;

		return -1;
	}
	
	try {
		asa_comm.sendWrapByte('T');
	}
	catch (serial::SerialException e) {
		std::cerr<< e.what() << std::endl;
		return -1;
	}

	std::cout << "Read :" << asa_comm.readByte() << std::endl;
	std::cout << "Read :" << asa_comm.readByte() << std::endl;
	
	bool isrState(false);
	try {
		isrState = asa_comm.getISR();
	}
	catch (serial::SerialException e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

	std::cout << "ISR state : ";
	if (isrState) {
		std::cout << "Have ISR";
	}
	else {
		std::cout << "Without ISR";
	}
	std::cout << std::endl;


	//system("pause");

	return 0;
}