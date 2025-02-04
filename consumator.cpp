#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>

const char* PIPE_NAME = "buffer_pipe";

void consumer() {
    while (true) {
        std::ifstream pipe(PIPE_NAME);
        if (!pipe) {
            std::cerr << "Eroare la deschidere pipe pentru citire.\n";
            return;
        }

        int item;
        if (pipe >> item) {
            std::cout << "Consumatorul a consumat item-ul " << item << std::endl;
        }

        pipe.close();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 + rand() % 500));
    }
}

int main() {
    std::srand(std::time(nullptr));
    consumer();
    return 0;
}