#include <iostream>
#include "serial/serial.h"

using namespace std;

int main(int argc, char const *argv[]) {

    if(argc < 2) {
        cout << "Usage: --find-devices --help --version\n";
    }
    vector<serial::PortInfo> devices_found = serial::list_ports();
    for( serial::PortInfo device : devices_found) {
        cout << device.port << ", " << device.description << ", " << device.hardware_id << endl;
    }

	vector<serial::PortInfo>::iterator iter = devices_found.begin();

	while( iter != devices_found.end() )
	{
		serial::PortInfo device = *iter++;

		printf( "(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(),
     device.hardware_id.c_str() );
	}

	serial::Serial my_serial("COM12", 38400, serial::Timeout::simpleTimeout(10000));
	cout << "Is the serial port open?";
	if (my_serial.isOpen())
		cout << " Yes." << endl;
	else
		cout << " No." << endl;

	string buffer;
	my_serial.readline(buffer);
	cout << buffer;

	system("pause");

    return 0;
}
