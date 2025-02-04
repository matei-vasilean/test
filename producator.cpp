#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>

const char* PIPE_NAME = "buffer_pipe";

void producer() {
    int item = 1;
    while (true) {
        std::ofstream pipe(PIPE_NAME);
        if (!pipe) {
            std::cerr << "Eroare la deschidere pipe pentru scriere.\n";
            return;
        }

        pipe << item << std::endl;
        std::cout << "Producatorul a produs item-ul " << item << std::endl;
        item++;

        pipe.close();

        std::this_thread::sleep_for(std::chrono::milliseconds(800 + rand() % 400));
    }
}

int main() {
    std::srand(std::time(nullptr));
    producer();
    return 0;
}