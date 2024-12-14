#include "../config.h"

#include <QApplication>
#include "window.h"

#include <iostream>

int main(int argc, char *argv[])
{
	if (argc < 1) {
		// report version
		std::cout << argv[0] << " Version " << WordChecker_VERSION_MAJOR << "." << WordChecker_VERSION_MINOR << "." << WordChecker_VERSION_PATCH << std::endl;
		std::cout << "Usage: " << argv[0] << " number" << std::endl;
		return 1;
	}
	QApplication app (argc, argv);

	Window window;
	window.show();

	return app.exec();
}
