#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
void printmat(short* mat, short m, short n) {
    printf("\n");
    for(int a = 0; a < m * n; a++) {
        for(int i = 0; i < m * n; i++) {
            printf("%hi, ", mat[a * m*n + i]);
        }
        printf("\n");
    }
    printf("\n");

}
short* _createGrid(char* inputfile, short* rows, short* columns) {
    
    //open file
    FILE* file = fopen(inputfile, "rb");

    //read in dimensions
    short m;
    fread(&m, sizeof(short), 1, file);
    short n;
    fread(&n, sizeof(short), 1, file);
    *rows = m;
    *columns = n;
    printf("M = %d N = %d", m, n);
    
    short* grid = malloc(sizeof(short) * (m) * (n));

    for(int i = 0; i < m * n; i++) {
        fread(&(grid[i]), sizeof(short), 1, file);
    }
    //fill in grid by reading form file
    /*
    for(int i = 0; i < m; i++) {
        for(int a = 0; a < n; a++) {
            //fread(&(grid[i * a + i]), sizeof(short), 1, file);
            printf("%hi, ", grid[i * a + i]);
        }
    }
    */
    fclose(file);
    return grid;
}
short* createMatrix(short* grid, short m, short n){
    /*
    m = 2;
    n = 3;
    short* mat = calloc(2 * 3 * 2 * 3, sizeof(short));
    grid[0] = 1;
    grid[1] = 2;
    grid[2] = 3;
    grid[3] = 4;
    grid[4] = 5;
    grid[5] = 6;
    */
   /*
    printf("\n\n");
    for(int i = 0; i < m * n; i++) {
        printf("%hd", grid[i]);
    }
    printf("\n\n");
    */

    int length = m * (n+1) * m * (n+1);
    short* mat = calloc(length, sizeof(short));
    printf("\n");
    for(int i = 0; i < m * n; i++) {
        //printmat(mat, m, n);
            //node itself
            //I IS COLUMN NUMBER
            mat[i * n * m + i] = grid[i] + 1;     

            //adjacent nodes at i + 1, i + n TOP LEFT CORNER CASE (i = 0)
            if(i == 0){
                //mat[1] = grid[1];
                //mat[n * m] = grid[0]; //check

                // right connection:
                mat[(i * n * m) + i + 1] = grid[i + 1] + 1;
                //mat[((i + 1) * n * m) + i] = grid[i];


                //bottom connection(updated):   
                mat[n*m * i + i + n] = grid[i + n] + 1;
                //mat[n * m * (i + n) + i] = grid[i];
            }
            //adjacent nodes at i - 1, i + n TOP RIGHT CORNER CASE (i = n - 1)
            else if(i == n - 1) {
                //left connection
                //mat[(n-2) * (n*m) +(n-1)] = grid[n-1];
                //mat[(n-1) * (n*m) + (n-2)] = grid[n-2];
                //bottom connection: TODO
                //mat[((2 * n - 1) * (n*m) + (n - 1))] = grid[n-1];
                //mat[(n - 1) * (n * m) + (2 * n - 1)] = grid[2 * n - 1];
                
                //bottom connection (updated):
                mat[n*m * i + i + n] = grid[i + n] + 1;
                //mat[n * m * (i + n) + i] = grid[i];
                //left connection(updated):
                mat[i * n*m + i - 1] = grid[i - 1] + 1;
                //mat[(i - 1) * n * m + i] = grid[i];
            }
            //adjacent nodes at i - n, i + 1 BOTTOM LEFT CASE (i = m * (n - 1))
            else if(i == (n * (m - 1))){
                //right connection
                //mat[((n * (m - 1)) * m*n + i + 1)] = grid[i+1];
                //mat[((n * (m - 1) + 1) * m*n) + n * (m-1)] = grid[n * (m - 1)]; 
                
                //top connection:
                //mat[((n * m - 1 - m) * m*n + i)] = grid[i];
                //mat[(i) * m * n + (n * m - 1 - n)] = grid[n * m - 1 - m];

                //top connection (updated):
                //mat[(n*m) * (i - n) + i] = grid[i];
                mat[i * n * m + i - n] = grid[i - n] + 1;
               // right connection (updated):
                mat[(i * n * m) + i + 1] = grid[i + 1] + 1;
                //mat[((i + 1) * n * m) + i] = grid[i];
            } 
            //adjacent nodes at i - 1, i - n, BOTTOM RIGHT CASE (i = (m * n) - 1)
            else if(i == (m * n) - 1) {
                //left connection
                //mat[(n * m - 1) * (n * m) + n * m - 2] = grid[n * m - 2];
                //mat[(n * m - 2) * (n * m) + (n * m -1)] = grid[n * m - 1];
                
                //left connection (updated): 
                mat[i * n*m + i - 1] = grid[i - 1] + 1;
                //mat[(i - 1) * n * m + i] = grid[i];


                //top connection:
                //mat[(n*m-1) * (n*m) + m] = grid[m]; // may need to be fixed
                //mat[m * n * m + (n * m - 1)] = grid[n * m - 1];
                
                //top connection (updated):
                //mat[(n*m) * (i - n) + i] = grid[i];
                mat[i * n * m + i - n] = grid[i - n] + 1;
            }
            //adjacent nodes at i - n, i + n, i + 1, LEFT CASE ((i % n) = 0)
            else if((i%n) == 0) {
                //top connection:
                //mat[(n*m) * (i - n) + i] = grid[i];
                mat[i * n * m + i - n] = grid[i - n] + 1;

                //bottom connection:
                mat[n*m * i + i + n] = grid[i + n] + 1;
                //mat[n * m * (i + n) + i] = grid[i];
                
               // right connection:
                mat[(i * n * m) + i + 1] = grid[i + 1] + 1;
                //mat[((i + 1) * n * m) + i] = grid[i];
            }
            //adjacent nodes at i - n, i + n, i - 1, RIGHT CASE ((i + 1) % n = 0)
            else if(((i + 1) % n) == 0) {
                //top connection:
                //mat[(n*m) * (i - n) + i] = grid[i];
                mat[i * n * m + i - n] = grid[i - n] + 1;

                //bottom connection:
                mat[n*m * i + i + n] = grid[i + n] + 1;
                //mat[n * m * (i + n) + i] = grid[i];

                //left connection: 
                mat[i * n*m + i - 1] = grid[i - 1] + 1;
                //mat[(i - 1) * n * m + i] = grid[i];
            }
            //bottom case
            else if(i > (n-1) * m ) {
                //top connection:
                //mat[(n*m) * (i - n) + i] = grid[i];
                mat[i * n * m + i - n] = grid[i - n] + 1;
                //left connection: 
                mat[i * n*m + i - 1] = grid[i - 1] + 1;
                //mat[(i - 1) * n * m + i] = grid[i];
               // right connection:
                mat[(i * n * m) + i + 1] = grid[i + 1] + 1;
                //mat[((i + 1) * n * m) + i] = grid[i];
            }
            //top case
            else if(i < n) {
                //bottom connection:
                mat[n*m * i + i + n] = grid[i + n] + 1;
                //mat[n * m * (i + n) + i] = grid[i];
                //left connection: 
                mat[i * n*m + i - 1] = grid[i - 1] + 1;
                //mat[(i - 1) * n * m + i] = grid[i];
               // right connection:
                mat[(i * n * m) + i + 1] = grid[i + 1] + 1;
                //mat[((i + 1) * n * m) + i] = grid[i];
            }
            //adjacent nodes at i + 1, i - 1, i - n, i + n: GENERAL CASE
            else {
                //top connection:
                //mat[(n*m) * (i - n) + i] = grid[i];
                mat[i * n * m + i - n] = grid[i - n] + 1;

                //bottom connection:
                mat[n*m * i + i + n] = grid[i + n] + 1;
                //mat[n * m * (i + n) + i] = grid[i];

                //left connection: 
                mat[i * n*m + i - 1] = grid[i - 1] + 1;
                //mat[(i - 1) * n * m + i] = grid[i];

               // right connection:
                mat[(i * n * m) + i + 1] = grid[i + 1] + 1;
                //mat[((i + 1) * n * m) + i] = grid[i];
            }
        }
        //printmat(mat, m, n);    
    
    /*
    for(int i = 0; i < m*n*m*n; i++) {
        printf("index:%d, value:%hd \n", i, mat[i]);
    }
    */
    //short* mat = malloc(sizeof(short) * m * n * m * n);

    for(int i = 0; i < m * n * m * n; i++) {
        mat[i] = mat[i] - 1;
    }
    


    //close file
    /*
    FILE* ofile = fopen(outputfile, "w");
    fprintf(ofile, "%hd %hd\n", m, n);
    for(int i = 0; i < m; i++) {
        for(int i = 0; i < n - 1; i++) {
            fprintf(ofile, "%hd ", grid[i]);
        }
        fprintf(ofile, "%hd\n", grid[i]);
    }
    
    */
    return mat;
}

int getMin(int* distances, bool* shortestPaths, short m, short n) {
    int min = INT_MAX;
    int minindex = 0;
    for(int i = 0; i < m * n; i++) {
        if((shortestPaths[i] == false) && (distances[i] <= min)){
            minindex = i;
            min = distances[i];
        }
    }
    return minindex;
}
int* _dijkstras(short* matrix, int m, int n, int src) {
    int* distances = malloc(sizeof(int) * m * n);
    bool* shortestPaths = calloc(m * n, sizeof(bool));
    printf("\n");
    for(int i = 0; i < m * n; i++) {
        distances[i] = INT_MAX;
    }
    distances[src] = matrix[src*m*n + src]; //possibly incorrect
    /*
    if(distances[src] < 0) {
        distances[src] = 0;
    }
    */
    for(int a = 0; a < m * n; a++) {
        int minindex = getMin(distances, shortestPaths, m, n);
        //printf("min index: %d", minindex);
        //printf("Min Index:%d\n", minindex);
        shortestPaths[minindex] = true;
        for(int i = 0; i < m * n; i++){
            if((shortestPaths[i] == false) && (matrix[minindex * (m*n) + i] > -1) && (distances[minindex] < INT_MAX) && (distances[minindex] + matrix[minindex * (m*n) + i] < distances[i])) {
                distances[i] = distances[minindex] + matrix[minindex * (m*n) + i];
            }
            
        }

        /*
        for(int i = 0; i < m; i++){
            for(int x = 0; x < n; x++) {
                if((shortestPaths[i * n + x] == false) && (matrix[minindex * n + x] != 0) && (distances[minindex] != INT_MAX) && (distances[minindex] + matrix[minindex * n + x] < distances[i * n + x])) {
                    distances[i * n + x] = distances[minindex] + matrix[minindex * n + x];
                }
            }
        }
        */

    }
    /*
    printf("Shortest Paths\n");
    for(int i = 0; i < m * n; i++) {
    printf("%d, ", shortestPaths[i]);
    }
    */
   /*
    printf("\n");
    for(int i = 0; i < m * n; i++) {
        printf("%d    %d\n", i, distances[i]);
    }
    */
    
    free(shortestPaths);
    return distances;
}
int getMinDistances(int* distances, int m, int n) {
    int min = INT_MAX;
    for(int i = n * (m-1); i < m * n; i++) {
        if((distances[i] <= min)){
            min = distances[i];
        }
    }
    return min;
}
/*
void writetime(short* distances, char* timesfile, short m, short n) {
    FILE* file = fopen(timesfiles, "wb");
    fprintf(file,"%hd", n);
    
}
*/
int main(int argc, char* argv[]) {
    if(argc < 4) return EXIT_FAILURE;
    
    char* inputfile = argv[1];
    char* gridfileO = argv[2];
    char* fasttimefileO = argv[3];
    char* fastpathfileO = argv[4];

    //if input file cant be opened, return exit failure
    //if in process of finding fastest path, there is a failure in memory or writing, ,return exit failure


    //declare size variables in main function (necessary for writing to file later)
    short m;
    short n;
    short* grid = _createGrid(inputfile, &m, &n);
    
    FILE* ofile = fopen(gridfileO, "w");
    fprintf(ofile, "%hd %hd\n", m, n);
    for(int a = 0; a < m*n; a++) {
        if(((a+1) % n) == 0){
            fprintf(ofile, "%hd\n", grid[a]);
        }
        else {
            fprintf(ofile,"%hd ", grid[a]);
        }
    }
    fclose(ofile);
    //write grid
    
    /*FILE* ofile = fopen(gridfileO, "w");
    fprintf(ofile, "%hd %hd\n", m, n);
    
    for(int a = 0; a < m; a++) {
        for(int i = 0; i < n - 1; i++) {
            fprintf(ofile, "%hd ", grid[a*m + i]);
        }
        fprintf(ofile, "%hd\n", grid[a*m + n - 1]);
    }

    fclose(ofile);
    */

    short* matrix = createMatrix(grid, m, n);
    int* mindist = malloc(sizeof(int) * n);
    //write fastest times
    FILE* file = fopen(fasttimefileO, "wb");
    fwrite(&n, sizeof(short), 1, file);
    for(int i = 0; i < n; i++){
        int* distances = _dijkstras(matrix, m, n, i);
        mindist[i] = getMinDistances(distances, m, n); //check if we are storing min dist or min index
        printf("Mindist = %d", mindist[i]);
        fwrite(&mindist[i], sizeof(int), 1, file);
        free(distances);
    }
    free(mindist);
    free(matrix);
    fclose(file);
    free(grid);



    //writetime(distances, fasttimefileO, m, n);
    return EXIT_SUCCESS;
}
