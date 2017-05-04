#include "Runner.h"
#include <string>

int main(int argc, char** argv) {

    if (argc == 2) {
        Runner runner("127.0.0.1", "4242", "", argv[1]);
        runner.run();
    } else if (argc == 5) {
        Runner runner(argv[1], argv[2], argv[3], argv[4]);
        runner.run();
    } else {
        assert(false);
    }

    return 0;
}