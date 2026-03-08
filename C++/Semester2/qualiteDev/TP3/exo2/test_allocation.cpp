#include <iostream>
#include <new>      // pour std::bad_alloc

int main() {
    std::cout << "Debut du test d'allocation.\n";

    // On va essayer des tailles croissantes
    size_t taille = 1;
    for (int i = 0; i < 5; ++i) {
        try {
            // allocation d'un tableau de char de 'taille' octets
            char *bloc = new char[taille];
            std::cout << "Allocation de " << taille << " octets : reussie\n";
            delete[] bloc; // se souvenir de liberer
        } catch (const std::bad_alloc &e) {
            std::cout << "Allocation de " << taille << " octets : echouee (" << e.what() << ")\n";
        }
        taille *= 1024; // on multiplie par 1024 pour augmenter rapidement
    }

    std::cout << "Fin du test.\n";
    return 0;
}
