#include "WindowApp.h"
#include "Graphics.h"

// Define some settings
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

int main() {
	WindowApp app;
	if (app.InitializeWindow(SCREEN_WIDTH, SCREEN_HEIGHT)) {
		while (app.IsRunning()) {
			app.Cycle();
		}
	}
	return 0;
}