#include <iostream>
#include <cmath>

using namespace std;

int sta[2] = {0, 0};

int **create_dim_matrix(int nlines, int ncol) {
    int **matrix = new int *[nlines];

    for (int i = 0; i < nlines; i++) {
        matrix[i] = new int[ncol];
    }

    return matrix;
}

void delete_dim_matrix(int **matrix, int nlines) {
    for(int i = 0; i < nlines; i++) {
        delete [] matrix[i];
    }
}

int **matrix_sum(bool type, int *m1, int *m2, int **matrix_1, int **matrix_2) {
    int size = m1[2] - m1[0] + 1;

    if (size != m2[2] - m2[0] + 1) {
        cout << "\nError in sum\n";
        return nullptr;
    }

    int **new_matrix = create_dim_matrix(size, size);
    int x, y, i, j, k, p;

    if(type) {
        for (x = 0, i = m1[0], j = m2[0]; i <= m1[2] && j <= m2[2]; x++, i++, j++) {
            for (y = 0, k = m1[1], p = m2[1]; k <= m1[3] && p <= m2[3]; y++, k++, p++) {
                new_matrix[x][y] = matrix_1[i][k] + matrix_2[j][p];
            }
        }
    }
    else {
        for (x = 0, i = m1[0], j = m2[0]; i <= m1[2] && j <= m2[2]; x++, i++, j++) {
            for (y = 0, k = m1[1], p = m2[1]; k <= m1[3] && p <= m2[3]; y++, k++, p++) {
                new_matrix[x][y] = matrix_1[i][k] - matrix_2[j][p];
            }
        }
    }


    return new_matrix;
}

int reajust(int nline, int ncol) {
    if (nline > ncol) {
        while (ncol != nline) {
            ncol += 1;
        }
    } else {
        while (nline != ncol) {
            nline += 1;
        }
    }

    while (true) {
        if (nline % 2 == 0) {
            if (fmod(log2(nline), 1) == 0) {
                break;
            }
        } else {
            nline++;
            ncol++;
        }
    }

    return nline;
}


int **strassen(int **matrix_0, int **matrix_1, int *sizes_0, int *sizes_1) {
    if(sizes_0[2] - sizes_0[0] == 0) {
        int **m = new int*;
        m[0] = new int (matrix_0[sizes_0[0]][sizes_0[1]] * matrix_1[sizes_1[0]][sizes_1[1]]);
        return m;
    }

    cout << "dasdas\n";
    int i_2 = (sizes_0[0] + sizes_0[2]) / 2, j_2 = (sizes_0[1] + sizes_0[3]) / 2;
    int *a11 = new int[4] {sizes_0[0], sizes_0[1], i_2, j_2};
    int *a12 = new int[4] {sizes_0[0], j_2 + 1, i_2, sizes_0[3]};
    int *a21 = new int[4] {i_2 + 1, sizes_0[1], sizes_0[2], j_2};
    int *a22 = new int[4] {i_2 + 1, j_2 + 1, sizes_0[2], sizes_0[3]};

    i_2 = (sizes_1[0] + sizes_1[2]) / 2, j_2 = (sizes_1[1] + sizes_1[3]) / 2;
    int *b11 = new int[4] {sizes_1[0], sizes_1[1], i_2, j_2};
    int *b12 = new int[4] {sizes_1[0], j_2 + 1, i_2, sizes_1[3]};
    int *b21 = new int[4] {i_2 + 1, sizes_1[1], sizes_1[2], j_2};
    int *b22 = new int[4] {i_2 + 1, j_2 + 1, sizes_1[2], sizes_1[3]};

    int *base_size = new int[4] {0, 0, a11[2] - a11[0], a11[3] - a11[1]};
    int divid_size = a11[2] - a11[0] + 1;

    int **aux_m_0 = matrix_sum(true, a11, a22, matrix_0, matrix_0);
    int **aux_m_1 = matrix_sum(true, b11, b22, matrix_1, matrix_1);
    int **m1 = strassen(aux_m_0, aux_m_1, base_size, base_size);
    delete_dim_matrix(aux_m_0, divid_size);
    delete_dim_matrix(aux_m_1, divid_size);

    aux_m_0 = matrix_sum(true, a21, a22, matrix_0, matrix_0);
    int **m2 = strassen(aux_m_0, matrix_1, base_size, b11);
    delete_dim_matrix(aux_m_0, divid_size);

    aux_m_0 = matrix_sum(false, b12, b22, matrix_1, matrix_1);
    int **m3 = strassen(matrix_0, aux_m_0, a11, base_size);
    delete_dim_matrix(aux_m_0, divid_size);

    aux_m_0 = matrix_sum(false, b21, b11, matrix_1, matrix_1);
    int **m4 = strassen(matrix_0, aux_m_0, a22, base_size);
    delete_dim_matrix(aux_m_0, divid_size);

    aux_m_0 = matrix_sum(true, a11, a12, matrix_0, matrix_0);
    int **m5 = strassen(aux_m_0, matrix_1, base_size, b22);
    delete_dim_matrix(aux_m_0, divid_size);

    aux_m_0 = matrix_sum(false, a21, a11, matrix_0, matrix_0);
    aux_m_1 = matrix_sum(true, b11, b12, matrix_1, matrix_1);
    int **m6 = strassen(aux_m_0, aux_m_1, base_size, base_size);
    delete_dim_matrix(aux_m_0, divid_size);
    delete_dim_matrix(aux_m_1, divid_size);

    aux_m_0 = matrix_sum(false, a12, a22, matrix_0, matrix_0);
    aux_m_1 = matrix_sum(true, b21, b22, matrix_1, matrix_1);
    int **m7 = strassen(aux_m_0, aux_m_1, base_size, base_size);
    delete_dim_matrix(aux_m_0, divid_size);
    delete_dim_matrix(aux_m_1, divid_size);

    int i, j, k = 0, l = 0;
    int act_size = sizes_0[2] - sizes_0[0] + 1;
    int **result = create_dim_matrix(act_size, act_size);

    aux_m_0 = matrix_sum(true, base_size, base_size, m1, m4);
    aux_m_1 = matrix_sum(true, base_size, base_size, aux_m_0, m7);
    delete_dim_matrix(aux_m_0, divid_size);

    int **c = matrix_sum(false, base_size, base_size, aux_m_1, m5);
    for(i = 0, k = 0; i < divid_size; i ++, k ++) {
        for(j = 0, l = 0; j < divid_size; j ++, l ++) {
            result[k][l] = c[i][j];
        }
    }
    delete_dim_matrix(c, divid_size);

    c = matrix_sum(true, base_size, base_size, m3, m5);
    for(i = 0 , k = 0; i < divid_size; i ++, k ++) {
        for(j = 0, l = divid_size; j < divid_size; j ++, l ++) {
            result[k][l] = c[i][j];
        }
    }
    delete_dim_matrix(c, divid_size);

    c = matrix_sum(true, base_size, base_size, m2, m4);
    for(i = 0, k = divid_size; i < divid_size; i ++, k ++) {
        for(j = 0, l = 0; j < divid_size; j ++, l ++) {
            result[k][l] = c[i][j];
        }
    }
    delete_dim_matrix(c, divid_size);

    aux_m_0 = matrix_sum(true, base_size, base_size, m1, m3);
    aux_m_1 = matrix_sum(true, base_size, base_size, aux_m_0, m6);
    delete_dim_matrix(aux_m_0, divid_size);
    c = matrix_sum(false, base_size, base_size, aux_m_1, m2);
    for(i = 0, k = divid_size; i < divid_size; i ++, k ++) {
        for(j = 0, l = divid_size; j < divid_size; j ++, l ++) {
            result[k][l] = c[i][j];
        }
    }
    delete_dim_matrix(c, divid_size);


    int ***pointers_m = new int**[7] {m1, m2, m3, m4, m5, m6, m7};
    for(i = 0; i < 7; i++) {
        delete_dim_matrix(pointers_m[i], divid_size);
    }
    delete [] pointers_m;

    int **pointers = new int*[9] {a11, a12, a21, a22, b11, b12, b21, b22, base_size};
    for(i = 0; i < 9; i++) {
        delete [] pointers[i];
    }
    delete[] pointers;


    return result;
}

int **matrix_mult_strassen(int *sizes, int *nlines, int *ncol, int **matrix_1, int **matrix_2) {
    if (ncol[0] == nlines[1] || ncol[1] == nlines[0]) {
        if (ncol[1] == nlines[0] && ncol[0] != nlines[1]) {
            swap(matrix_1, matrix_2);
            swap(nlines[0], nlines[1]);
            swap(ncol[0], ncol[1]);
        }

        sizes[0] = nlines[0];
        sizes[1] = ncol[1];

        if ((nlines[0] != nlines[1] || ncol[0] != ncol[1]) || fmod(log2(nlines[0]), 1) != 0) {
            int new_size, aux;
            new_size = reajust(nlines[0], ncol[0]);
            aux = reajust(nlines[1], ncol[1]);

            if (aux > new_size) {
                new_size = aux;
            }

            int i, j;
            int **new_matrix_1 = create_dim_matrix(new_size, new_size);
            int **new_matrix_2 = create_dim_matrix(new_size, new_size);

            for (i = 0; i < new_size; i++) {
                for (j = 0; j < new_size; j++) {
                    if (i < nlines[0] && j < ncol[0]) {
                        new_matrix_1[i][j] = matrix_1[i][j];
                    } else {
                        new_matrix_1[i][j] = 0;
                    }

                    if (i < nlines[1] && j < ncol[1]) {
                        new_matrix_2[i][j] = matrix_2[i][j];
                    } else {
                        new_matrix_2[i][j] = 0;
                    }
                }
            }

            new_size--;
            int size_0[4] = {0, 0, new_size, new_size};
            int size_1[4] = {0, 0, new_size, new_size};

            int **result = strassen(new_matrix_1, new_matrix_2, size_0, size_1);
            delete_dim_matrix(new_matrix_1, new_size);
            delete_dim_matrix(new_matrix_2, new_size);

            return result;
        }
        else {
            int size_0[4] = {0, 0, nlines[0] - 1, nlines[0] - 1};
            int size_1[4] = {0, 0, nlines[1] - 1, nlines[1] - 1};

            return strassen(matrix_1, matrix_2, size_0, size_1);
        }
    } else {
        cout << "Não foi possível multiplicar estas matrizes\n";
        sizes[0] = -1;
        sizes[1] = -1;
        return nullptr;
    }
}

int main() {
    int nlines[2], ncol[2], i, j;

//    cout << "Digite o tamanho da primeira matriz\n\tLinhas: ";
//    cin >> nlines[0];
//    cout << "\tColunas: ";
//    cin >> ncol[0];
//    int **matrix_1 = create_pre_matrix(nlines[0], ncol[0]);
//
//    cout << "Digite o tamanho da segunda matriz\n\tLinhas: ";
//    cin >> nlines[1];
//    cout << "\tColunas: ";
//    cin >> ncol[1];
//    int **matrix_2 = create_pre_matrix(nlines[1], ncol[1]);
//
//    int sizes[2];
//    int **new_matrix = matrix_mult_strassen(sizes, nlines, ncol, matrix_1, matrix_2);
//
//    cout << "\n\nSua matriz : \n\t";
//    if(new_matrix != nullptr) {
//        for(i = 0; i < sizes[0]; i++) {
//            for(j = 0; j < sizes[1]; j++) {
//                cout << new_matrix[i][j] << "  ";
//            }
//
//            cout << "\n\t";
//        }
//    }

    cin >> nlines[0];
    cin >> ncol[0];
    nlines[1] = ncol[0];
    cin >> ncol[1];


    int **matrix_a = create_dim_matrix(nlines[0], ncol[0]);
    int **matrix_b = create_dim_matrix(nlines[1], ncol[1]);

    for(i = 0; i < nlines[0]; i ++) {
        for(j = 0; j < ncol[0]; j ++) {
            cin >> matrix_a[i][j];
        }
    }

    for(i = 0; i < nlines[1]; i ++) {
        for(j = 0; j < ncol[1]; j ++) {
            cin >> matrix_b[i][j];
        }
    }

    int sizes[2];
    int **result = matrix_mult_strassen(sizes, nlines, ncol, matrix_a, matrix_b);

    int aux = sizes[1] - 1;
    if(result != nullptr) {
        for(i = 0; i < sizes[0]; i++) {
            for(j = 0; j < sizes[1]; j++) {

                cout << result[i][j];

                if(j != aux) {
                    cout << " ";
                }
            }

            cout << "\n";
        }
    }

    return 0;
}