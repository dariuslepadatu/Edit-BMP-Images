#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./bmp_header.h"
#define MAX 3000000
#define OMIE 1000
#define ZECE 10

void ecuatia_dreptei(int y1, int x1, int y2, int x2,
int *coord_x, int *coord_y, int *lungime) {
    int  dx = 0, dy = 0, max = 0, min = 0;
    int coord = 0, i = 0;
    if (y2 > y1) {
        dy = y2 - y1;
    } else {
        dy = y1 - y2;
    }
    if (x2 > x1) {
        dx = x2 - x1;
    } else {
        dx = x1 - x2;
    }
    if (dy >= dx) {
        if (y2 > y1) {
            max = y2;
            min = y1;
            coord = 0;
        } else if (y2 < y1) {
            max = y1;
            min = y2;
            coord = 0;
        }
    } else {
        if (x2 > x1) {
            max = x2;
            min = x1;
            coord = 1;
        } else if (x2 < x1) {
            max = x1;
            min = x2;
            coord = 1;
        }
    }
    if (coord == 0) {
        for (i = min; i <= max; i++) {
            coord_y[*lungime] = i;
            (*lungime)++;
        }
        for (i = 0; i < *lungime; i++) {
            if (x2 != x1) {
                coord_x[i] =  (coord_y[i]*(x2 - x1) + x1*y2 - y1*x2)/(y2 - y1);
            } else if (x2 == x1) {
                coord_x[i] = x1;
            }
        }
    } else if (coord == 1) {
        for (i = min; i <= max; i++) {
            coord_x[*lungime] = i;
            (*lungime)++;
        }
        for (i = 0; i < *lungime; i++) {
            if (y2 != y1) {
                coord_y[i] = (-x1*y2 + y1*x2 + coord_x[i]*(y2 - y1))/(x2 - x1);
            } else {
                coord_y[i] = y1;
            }
        }
    }
}

void colorare_poza(int *coord_x, int *coord_y, char *pixeli1,
int lungime, int marime_creion, int h1, int w1,
int red, int green, int blue) {
    int k = 0, i = 0, j = 0, l = 0, r = 0, c = 0;
    while (k < lungime) {
        i = coord_x[k];
        j = coord_y[l];
        r = marime_creion / 2;
        c = -marime_creion / 2;
        while (r >=  -marime_creion / 2 && (i + r) < h1 && (j + c) >= 0 && (j + c) < w1) {
                pixeli1[3* w1 * (i + r) + 3 * (j + c)] = (char)blue;
                pixeli1[3* w1 * (i + r) + 3 * (j + c) + 1] = (char)green;
                pixeli1[3* w1 * (i + r) + 3 * (j + c) + 2] = (char)red;
                c++;
            if (c > marime_creion / 2) {
                c = -marime_creion / 2;
                r--;
            }
        }
        l++;
        k++;
    }
}

int conversie(char *p) {
    int i = 0, num = 0, a = 1, nr = 0;
    for (i = (int)strlen(p) - 1; i >= 0; i--) {
        num = p[i] - '0';
        nr = nr + a*num;
        a = a*ZECE;
    }
    return nr;
}

void prelucrare(char *s) {
    int i = 0;
    while (scanf("%c", &s[i]) != EOF) {
        if (s[i] == '\n') {
            s[i] = ' ';
        }
        i++;
    }
    s[i] = '\0';
}

void umplere(int x, int y, int h1, int w1, char *pixeli1,
int b_vechi, int g_vechi, int r_vechi,
int blue, int green, int red, int nr_umpleri) {
    int i = 0, cont_x = 0, cont_y = 0;
    int xnou = 0, ynou = 0, j = 0;
    if (nr_umpleri == 1) {
        while (i <= h1) {
            while (j <= 3 * w1) {
                if (pixeli1[3* w1 * i + 3 * j] == b_vechi
                && pixeli1[3* w1 * i + 3 * j + 1] == g_vechi
                && pixeli1[3* w1 * i + 3 * j + 2] == r_vechi) {
                        pixeli1[3* w1 * i + 3 * j] = (char)blue;
                        pixeli1[3* w1 * i + 3 * j + 1] = (char)green;
                        pixeli1[3* w1 * i + 3 * j + 2] = (char)red;
                }
                j++;
            }
            j = 0;
            i++;
        }
    } else  {
        for (i = 0; i < 4; i++) {
            if (i == 0) {
                cont_x = 1;
                cont_y = 0;
            }
            if (i == 1) {
                cont_x = 0;
                cont_y = 1;
            }
            if (i == 2) {
                cont_x = -1;
                cont_y = 0;
            }
            if (i == 3) {
                cont_x = 0;
                cont_y = -1;
            }
            xnou = x + cont_x;
            ynou = y + cont_y;
            if (pixeli1[3 * w1 * xnou + 3 * ynou] == (char)b_vechi
            && pixeli1[3 * w1 * xnou + 3 * ynou+ 1] == (char)g_vechi
            && pixeli1[3 * w1 * xnou + 3 * ynou+ 2] == (char)r_vechi
            && xnou >= 1 && xnou <= h1 - 1
            && ynou >= 1 && ynou <= 3 * w1 - 3) {
                pixeli1[3 * w1 * xnou + 3 * ynou] = (char)blue;
                pixeli1[3 * w1 * xnou + 3 * ynou+1] = (char)green;
                pixeli1[3 * w1 * xnou + 3 * ynou+2] = (char)red;
                umplere(xnou, ynou, h1, w1, pixeli1, b_vechi,
                g_vechi, r_vechi, blue, green, red, nr_umpleri);
            }
        }
    }
}


int main() {
    int quit = 0, red = 0, green = 0, blue  = 0, i = 0, j = 0;
    int w1 = 0, h1 = 0, w2 = 0, h2 = 0, marime1 = 0, marime2 = 0;
    int cont = 0, marime_creion = 0, y1 = 0, x1 = 0, y = 0, x = 0;
    int y2 = 0, x2 = 0, lungime = 0, wd = 0, hd = 0, nr_umpleri = 0;
    int yp = 0, xp = 0,   y3 = 0, x3 = 0, y4 = 0, x4 = 0;
    int *coord_x = NULL, *coord_y = NULL;
    char *comanda = NULL, *cuvant = NULL, *pixeli1 = NULL, *pixeli2 = NULL;
    char b_vechi = 0, g_vechi = 0, r_vechi = 0, *copie =  NULL, *fill = NULL;
    comanda = (char*)malloc(MAX*sizeof(char));
    cuvant = (char*)malloc(MAX*sizeof(char));
    pixeli1 = (char*)malloc(MAX*sizeof(char));
    pixeli2 = (char*)malloc(MAX*sizeof(char));
    copie = (char*)malloc(MAX*sizeof(char));
    coord_x = (int*)malloc(OMIE*sizeof(int));
    coord_y = (int*)malloc(OMIE*sizeof(int));
    FILE *fin = NULL, *fout = NULL, *fadd = NULL;
    bmp_fileheader file1header, file2header;
    bmp_infoheader info1header, info2header;
    prelucrare(comanda);
    strncpy(copie, comanda, MAX);
    fill = strtok(copie, " ");
    while (fill != NULL) {
        if (strcmp(fill, "fill") == 0) {
            nr_umpleri++;
        }
        fill = strtok(NULL, " ");
    }
    cuvant = strtok(comanda, " ");
    while (cuvant != NULL && quit == 0) {
        if (strcmp(cuvant, "edit") == 0) {
            cuvant = strtok(NULL, " ");
            fin = fopen(cuvant, "rb");
            fread(&file1header, sizeof(bmp_fileheader), 1, fin);
            fread(&info1header, sizeof(bmp_infoheader), 1, fin);
            h1 = info1header.height;
            w1 = info1header.width;
            if (info1header.biSizeImage != 0) {
                marime1 =  (int)info1header.biSizeImage;
            } else {
                marime1 =  h1 * w1 * 3;
            }
            fread(pixeli1, marime1, 1, fin);
            rewind(fin);
        }
        if (strcmp(cuvant, "insert") == 0) {
            cuvant = strtok(NULL, " ");
            fadd = fopen(cuvant, "rb");
            fread(&file2header, sizeof(bmp_fileheader), 1, fadd);
            fread(&info2header, sizeof(bmp_infoheader), 1, fadd);
            h2 = info2header.height;
            w2 = info2header.width;
            if (info2header.biSizeImage != 0) {
                marime2 =  (int)info2header.biSizeImage;
            } else {
                marime2 =  h2 * w2 * 3;
            }
            fread(pixeli2, marime2, 1, fadd);
            rewind(fadd);
            cuvant = strtok(NULL, " ");
            yp = conversie(cuvant);
            cuvant = strtok(NULL, " ");
            xp = conversie(cuvant);
            cont = 0;
            i = xp;
            j = yp * 3;
            while (i <= h1 && cont < marime2) {
                if (j >= 3 * w1) {
                    cont++;
                } else {
                    pixeli1[3 * w1 * i + j] = pixeli2[cont];
                    cont++;
                }
                j++;
                if ((int)(j - yp * 3) == (int)3 * w2) {
                    j = yp * 3;
                    i++;
                }
            }
        }
        if (strcmp(cuvant, "set") == 0) {
            cuvant = strtok(NULL, " ");
            if (strcmp(cuvant, "draw_color") == 0) {
                cuvant = strtok(NULL, " ");
                red = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                green = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                blue = conversie(cuvant);
            }
            if (strcmp(cuvant, "line_width") == 0) {
                cuvant = strtok(NULL, " ");
                marime_creion = conversie(cuvant);
            }
        }
        if (strcmp(cuvant, "draw") == 0) {
            cuvant = strtok(NULL, " ");
            if (strcmp(cuvant, "line") == 0) {
                lungime = 0;
                cuvant = strtok(NULL, " ");
                y1 = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                x1 = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                y2 = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                x2 = conversie(cuvant);
                ecuatia_dreptei(y1, x1, y2, x2,  coord_x,  coord_y,  &lungime);
                colorare_poza(coord_x, coord_y, pixeli1,
                lungime, marime_creion, h1, w1,
                red, green, blue);
            }
            if (strcmp(cuvant, "triangle") == 0) {
                lungime = 0;
                cuvant = strtok(NULL, " ");
                y1 = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                x1 = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                y2 = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                x2 = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                y3 = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                x3 = conversie(cuvant);
                ecuatia_dreptei(y1, x1, y2, x2,  coord_x,  coord_y,  &lungime);
                colorare_poza(coord_x, coord_y, pixeli1,
                lungime, marime_creion, h1, w1,
                red, green, blue);
                lungime = 0;
                ecuatia_dreptei(y2, x2, y3, x3,  coord_x,  coord_y,  &lungime);
                colorare_poza(coord_x, coord_y, pixeli1,
                lungime, marime_creion, h1, w1,
                red, green, blue);
                lungime = 0;
                ecuatia_dreptei(y1, x1, y3, x3,  coord_x,  coord_y,  &lungime);
                colorare_poza(coord_x, coord_y, pixeli1,
                lungime, marime_creion, h1, w1,
                red, green, blue);
            }
            if (strcmp(cuvant, "rectangle") == 0) {
                cuvant = strtok(NULL, " ");
                y1 = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                x1 = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                wd = conversie(cuvant);
                cuvant = strtok(NULL, " ");
                hd = conversie(cuvant);
                y2 = y1;
                x2 = hd + x1;
                y3 = y1 + wd;
                x3 = hd + x1;
                y4 = y1 + wd;
                x4 = x1;
                lungime = 0;
                ecuatia_dreptei(y1, x1, y2, x2,  coord_x,  coord_y,  &lungime);
                colorare_poza(coord_x, coord_y, pixeli1,
                lungime, marime_creion, h1, w1,
                red, green, blue);
                lungime = 0;
                ecuatia_dreptei(y2, x2, y3, x3,  coord_x,  coord_y,  &lungime);
                colorare_poza(coord_x, coord_y, pixeli1,
                lungime, marime_creion, h1, w1,
                red, green, blue);
                lungime = 0;
                ecuatia_dreptei(y3, x3, y4, x4,  coord_x,  coord_y,  &lungime);
                colorare_poza(coord_x, coord_y, pixeli1,
                lungime, marime_creion, h1, w1,
                red, green, blue);
                lungime = 0;
                ecuatia_dreptei(y4, x4, y1, x1,  coord_x,  coord_y,  &lungime);
                colorare_poza(coord_x, coord_y, pixeli1,
                lungime, marime_creion, h1, w1,
                red, green, blue);
            }
        }
        if (strcmp(cuvant, "fill") == 0) {
            cuvant = strtok(NULL, " ");
            y = conversie(cuvant);
            cuvant = strtok(NULL, " ");
            x = conversie(cuvant);
            b_vechi =  pixeli1[3 * w1 * x + 3 * y];
            g_vechi =  pixeli1[3 * w1 * x + 3 * y + 1];
            r_vechi =  pixeli1[3 * w1 * x + 3 * y + 2];
            i = 0;
            j = 0;
            umplere(x, y, h1, w1, pixeli1, b_vechi,
            g_vechi, r_vechi, blue, green, red, nr_umpleri);
        }
        if (strcmp(cuvant, "save") == 0) {
            cuvant = strtok(NULL, " ");
            fout = fopen(cuvant, "wb");
            fwrite(&file1header, sizeof(bmp_fileheader), 1, fout);
            fwrite(&info1header, sizeof(bmp_infoheader), 1, fout);
            fwrite(pixeli1, marime1, 1, fout);
        }
        if (strcmp(cuvant, "quit") == 0) {
            quit = 1;
        }
        cuvant = strtok(NULL, " ");
    }
    if (quit == 1) {
        free(comanda);
        free(cuvant);
        free(pixeli1);
        free(pixeli2);
        free(coord_x);
        free(coord_y);
        free(fill);
        free(copie);
    }
}
