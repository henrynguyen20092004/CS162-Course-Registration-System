#include "Command.h"

#include <stdlib.h>

void processCommand(Command command) {
    if (command == STOP) {
        exit(0);
    }
}
