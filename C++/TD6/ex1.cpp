#include <iostream>
#include <vector>
#include <string>

std::vector<int> lireEntiers() {
    std::vector<int> entiers;
    std::string ligne;
    while (true) {
        std::getline(std::cin, ligne);
        if (ligne.empty()) {
            break;
        }
        try {
            int entier = std::stoi(ligne);
            entiers.push_back(entier);
        } catch (const std::invalid_argument&) {
            std::cout << "Veuillez entrer un entier valide ou une ligne vide pour terminer." << std::endl;
        }
    }
    return entiers;
}
