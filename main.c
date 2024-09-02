#include <stdio.h>
#include <stdlib.h>

// Trouver l'indice de la colonne entrante
int baseIn(double matrice[3][5]) {
    int indice = 0;
    double smal = matrice[0][0]; // Initialiser avec le premier élément de la ligne des coûts

    // Cherche le plus petit coefficient dans la première ligne (ligne des coûts)
    for (int i = 1; i < 5; i++) {
        if (matrice[0][i] < smal) {
            smal = matrice[0][i];
            indice = i;
        }
    }
    return indice;
}

// Trouver l'indice de la ligne sortante
int baseOut(double matrice[3][5], int inIndice) {
    int inBase = 1;
    double minRatio = matrice[1][4] / matrice[1][inIndice];

    // Cherche la ligne avec le plus petit ratio (valeur de la dernière colonne / pivot)
    for (int i = 2; i < 3; i++) {
        double ratio = matrice[i][4] / matrice[i][inIndice];
        if (ratio < minRatio && ratio > 0) {
            minRatio = ratio;
            inBase = i;
        }
    }
    return inBase;
}

// Affichage de la matrice
void AffichageMatrice(double matrice[3][5]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%0.2f\t", matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void main() {
    double matrice[3][5] = {
        {-2, -4, 0, 0, 0},  // Ligne des coûts
        {3, 4, 1, 0, 1700}, // Contraintes
        {2, 5, 0, 1, 1600}  // Contraintes
    };

    // Affichage initial
    printf("Matrice initiale:\n");
    AffichageMatrice(matrice);

    // Boucle du Simplexe
    while (1) {
        // Détermination de la colonne entrante
        int col = baseIn(matrice);

        // Si tous les coefficients sont positifs ou nuls, on a atteint l'optimum
        if (matrice[0][col] >= 0) {
            break;
        }

        // Détermination de la ligne sortante
        int ligne = baseOut(matrice, col);

        // Pivotement : normalisation de la ligne pivot
        double pivot = matrice[ligne][col];
        for (int i = 0; i < 5; i++) {
            matrice[ligne][i] /= pivot;
        }

        // Mise à jour des autres lignes
        for (int i = 0; i < 3; i++) {
            if (i != ligne) {
                double facteur = matrice[i][col];
                for (int j = 0; j < 5; j++) {
                    matrice[i][j] -= facteur * matrice[ligne][j];
                }
            }
        }

        // Afficher la matrice après chaque itération
        printf("Matrice après une itération:\n");
        AffichageMatrice(matrice);
    }

    printf("Solution optimale trouvée:\n");
    AffichageMatrice(matrice);
}
