#include <iostream>
#include <string>

// Cette fonction transforme n'importe quel mot en un nombre unique (Hash)
// Elle ne contient JAMAIS le mot de passe secret.
unsigned long calculer_hash(std::string mot) {
    unsigned long hash = 5381;
    for (char c : mot) {
        hash = ((hash << 5) + hash) + c; // Algorithme djb2 (très connu)
    }
    return hash;
}

int main() {
    // Le hash de  calculé à l'avance est : 3591632766323
    // On ne stocke QUE ce nombre.
    const unsigned long HASH_SECRET = 8245147252682851653; 
    std::string saisie;

    std::cout << "--- MERKUR SECURE SYSTEM ---" << std::endl;
    std::cout << "Entrez la clef : ";
    std::cin >> saisie;

    // On hache ce que l'utilisateur tape et on compare les nombres
    if (calculer_hash(saisie) == HASH_SECRET) {
        std::cout << "[OK] Acces autorise." << std::endl;
    } else {
        std::cout << "[ALERTE] Clef invalide !" << std::endl;
    }

    return 0;
}
