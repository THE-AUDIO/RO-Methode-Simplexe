#include <stdio.h>

// Fonction pour trouver la colonne pivot (colonne d'entrée)
int trouver_colonne_entree(double tableau[3][4]) {
    int col = 1; // Colonne 1 par défaut
    for (int j = 1; j < 3; j++) {
        if (tableau[2][j] < tableau[2][col]) {
            col = j;
        }
    }
    return col;
}

// Fonction pour trouver la ligne pivot (ligne de sortie)
int trouver_ligne_sortie(double tableau[3][4], int col_entree) {
    int ligne = 0;
    double min_ratio = 1e9;
    for (int i = 0; i < 2; i++) {
        if (tableau[i][col_entree] > 0) {
            double ratio = tableau[i][3] / tableau[i][col_entree];
            if (ratio < min_ratio) {
                min_ratio = ratio;
                ligne = i;
            }
        }
    }
    return ligne;
}

// Fonction de pivotage
void pivot(double tableau[3][4], int ligne, int col) {
    double pivot = tableau[ligne][col];

    // Divise la ligne pivot par l'élément pivot
    for (int j = 0; j < 4; j++) {
        tableau[ligne][j] /= pivot;
    }

    // Réduit les autres lignes
    for (int i = 0; i < 3; i++) {
        if (i != ligne) {
            double facteur = tableau[i][col];
            for (int j = 0; j < 4; j++) {
                tableau[i][j] -= facteur * tableau[ligne][j];
            }
        }
    }
}

int main() {
    // Tableau du simplexe : 2 contraintes + 1 fonction objective
    double tableau[3][4] = {
        {2, 1, 1, 14},  // Contrainte 1 : 2x + y + s1 = 14
        {4, 2, 3, 28},  // Contrainte 2 : 4x + 2y + 3s2 = 28
        {-3, -2, 0, 0}  // Fonction objective : Max Z = 3x + 2y
    };

    while (1) {
        int col_entree = trouver_colonne_entree(tableau);
        if (tableau[2][col_entree] >= 0) {
            break;  // Arrêt si tous les coefficients sont positifs (solution optimale trouvée)
        }

        int ligne_sortie = trouver_ligne_sortie(tableau, col_entree);
        pivot(tableau, ligne_sortie, col_entree);
    }

    printf("Solution Optimale :\n");
    printf("x = %.2f\n", tableau[0][3]);
    printf("y = %.2f\n", tableau[1][3]);
    printf("Valeur Maximale de Z = %.2f\n", tableau[2][3]);

    return 0;
}
