#include <iostream> 

size_t plus_grand_bloc_allouable() {
    // phase 1 : on cherche une taille qui echoue en doublant
    size_t moins = 0;      // derniere taille qui a reussi
    size_t plus = 1;       // premiere taille qui va echouer

    // on essaye d'allouer jusqu'a ce que ca plante
    while (true) {
        try {
            char *p = new char[plus];
            // reussi, on met a jour "moins" et on double "plus" pour aller plus loin
            moins = plus;
            plus *= 2;

            delete[] p; // liberer le bloc alloue
        } catch (const std::bad_alloc &) {
            // l'allocation de "plus" a rate, on arrete la boucle
            break;
        }
    }

    // pour le moment on retourne uniquement la valeur "moins" ;
    // plus tard on fera la recherche dichotomique entre moins et plus.
    return moins;
}
