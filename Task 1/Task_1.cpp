#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define N 4

using namespace std;

//Function to find the missing square
int* findMissing(int** arr, int size, int firstX, int firstY){
    int* missing = new int[2];
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(arr[firstX+i][firstY+j] == -1){
                missing[0] = firstX+i;
                missing[1] = firstY+j;
                return missing;
            }
        }
    }
    missing[0] = -1;
    missing[1] = -1;
    return missing;
}
int* findEdge(int** arr, int size, int firstX, int firstY, bool wide=false) {
    /*
        This function will return the edge color and location(to know the missing quadrant)
        The wide parameter is a flag to look in a wider range
    */
   if (size > 2 && !wide)
        return findEdge(arr, size/2, firstX+size/4, firstY+size/4);
    else if (size > 4){
        return findEdge(arr, size/2, firstX+size/4, firstY+size/4, true);
    }
    int* edge = new int[3];
    edge[0] = -1;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(arr[firstX+i][firstY+j] != 0 && arr[firstX+i][firstY+j] != -1){
                int edgeColor = arr[firstX+i][firstY+j];
                edge[0] = edgeColor;
                edge[1] = firstX + i;
                edge[2] = firstY + j;
                return edge;
            }
        }
    }
    return edge;
}
int* findOrentation(int** arr, int size){
    int* edge = new int[3];
    edge[0] = -1;
    for(int i = size/2 - 1; i < size/2 + 1; i++){
        for(int j = size/2-1; j < size/2 + 1; j++){
            if(arr[i][j] == 100){
                int edgeColor = arr[i][j];
                edge[0] = edgeColor;
                edge[1] = i;
                edge[2] = j;
                return edge;
            }
        }
    }
    return edge;
}

int** rotate90Clockwise(int** arr, int n){
    int** rotated = new int*[n];
    for (int i = 0; i < n; i++) {
        rotated[i] = new int[n];
    }

    // Fill the new array with the rotated values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rotated[j][n - i - 1] = arr[i][j];
        }
    }

    // Return the new array
    return rotated;
}
void rotateAndPlace(int** arr, int size, int firstX, int firstY, int* edge, int** savedDP, int* dpEdge){
    //We need to copy in the savedDP array
    int** temp = new int*[size];
    for(int i = 0; i < size; i++){
        temp[i] = new int[size];
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            temp[i][j] = savedDP[i][j];
        }
    }
    // This function will rotate the tormino and place it in the correct orentation
    while(!(dpEdge[1] == edge[1]-firstX && dpEdge[2] == edge[2]-firstY)){
        temp = rotate90Clockwise(temp, size);
        dpEdge = findOrentation(temp, size);
    }
    // Place the tormino
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(arr[firstX+i][firstY+j] == 0){
                arr[firstX+i][firstY+j] = temp[i][j];
            }
        }
    }
    // printFullGrid(arr);
}
void placeTormino(int** arr, int size, int firstX, int firstY, int* originEdge, int**** dp, bool lastTormino = false, int color=-1){
    // lastTormino is a flag to indicate that this is the last tormino to be placed and is used only in the 2x2 case
    //We need to find the edge color
    int* edge = findEdge(arr, size, firstX, firstY);
    // According to the edge color we will look for an answer in the dp memory or we will find one
    if(dp[int(log2(size))-1][edge[0]-1] != nullptr && size>2){
        // Place the saved tormino
        //We need to check if it is in the right orentation
        int** savedDP = dp[int(log2(size))-1][edge[0]-1];
        // printFullGrid(arr);
        int* dpEdge = findOrentation(savedDP, size);
        if (dpEdge[1] == edge[1]-firstX && dpEdge[2] == edge[2]-firstY){
            // Correct orentation
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    if(arr[firstX+i][firstY+j] == 0){
                        arr[firstX+i][firstY+j] = savedDP[i][j];
                    }
                }
            }
        }
        else{
            // We need to rotate and place tormino into correct orentaion
            rotateAndPlace(arr, size, firstX, firstY, edge, savedDP, dpEdge);
        }
    }
    else {
        if(size == 2){
            //If edge is black try to find in a wider range
            if (edge[0] == -1)
                edge = findEdge(arr, size, firstX, firstY, true);
            int newColor = color;
            //If it is a last tormino place the same color as the original edge
            if (lastTormino)
                newColor = originEdge[0];
            // If the size is 2 we will place the tormino
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    if(arr[firstX+i][firstY+j] == 0){
                        arr[firstX+i][firstY+j] = newColor;
                    }
                }
            }
            if(lastTormino){
                return;
            }
            //Store the answer
            int** dpNew = new int*[size];
            for(int i = 0; i < size; i++){
                dpNew[i] = new int[size];
            }
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    if(arr[firstX+i][firstY+j] == newColor){
                        dpNew[i][j] = arr[firstX+i][firstY+j];
                    } else{
                        dpNew[i][j] = 100;
                    }
                }
            }
            dp[int(log2(size))-1][edge[0]-1] = dpNew;
            return;
        }
        // Find tormino
        // A large tormino can be made up of 4 smaller torminos
        // We will start to put the tormino that is in the middle
        int colour1, colour2;

        if (edge[0]==1){
            colour1 = 3;
            colour2 = 2; 
        }
        else if (edge[0]==2){
            colour1 = 3;
            colour2 = 1;
        }
        else if(edge[0]==3){
            colour1 = 1;
            colour2 = 2;
        }
        placeTormino(arr, size/2, firstX+size/4, firstY+size/4, edge, dp, false,colour1);
        if(edge[1] >= size/2+firstX){
            if(edge[2] >= size/2+firstY){
                placeTormino(arr, size/2, firstX, firstY+size/2, edge, dp, false,color=colour2);
                placeTormino(arr, size/2, firstX+size/2, firstY, edge, dp, false,color=colour2);
                placeTormino(arr, size/2, firstX, firstY, edge, dp, true);
            } else {
                placeTormino(arr, size/2, firstX, firstY, edge, dp, false,color=colour2);
                placeTormino(arr, size/2, firstX+size/2, firstY+size/2, edge, dp, false,color=colour2);
                placeTormino(arr, size/2, firstX, firstY+size/2, edge, dp, true);
            }
        } else {
            if(edge[2] >= size/2+firstY){
                placeTormino(arr, size/2, firstX, firstY, edge, dp, false,color=colour2);
                placeTormino(arr, size/2, firstX+size/2, firstY+size/2, edge, dp, false,color=colour2);
                placeTormino(arr, size/2, firstX+size/2, firstY, edge, dp, true);
            } else {
                placeTormino(arr, size/2, firstX+size/2, firstY, edge, dp, false, color=colour2);
                placeTormino(arr, size/2, firstX, firstY+size/2, edge, dp, false, color=colour2);
                placeTormino(arr, size/2, firstX+size/2, firstY+size/2, edge, dp, true);
            }
        }
        
    }

}

void tile(int** arr, int size, int firstX, int firstY, int****dp){

    if(size == 1){
        return;
    }
    // We need to find the missing square
    int* missing = findMissing(arr, size, firstX, firstY);

    // If there is no missing square
    if(missing[0] > -1){
    //The grid can be broken down into a tormino and a square with the missing square
        if(missing[0]-firstX < size/2){
            if(missing[1]-firstY < size/2){
                tile(arr, size/2, firstX, firstY, dp);
            } else {
                tile(arr, size/2, firstX, firstY+size/2, dp);
            }
        } else {
            if(missing[1]-firstY < size/2){
                tile(arr, size/2, firstX+size/2, firstY, dp);
            } else {
                tile(arr, size/2, firstX+size/2, firstY+size/2, dp);
            }
        }
    }
    //tile the tormino
    // We need to find the edgeColor
    int* edge = findEdge(arr, size, firstX, firstY);
    int edgeColor = edge[0];
    //If the edge color is -1 which means this is the missing square and in this case we will put an answer
    if(size == 2){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(arr[firstX+i][firstY+j] == 0){
                    //We will put the tormino next to the missing square to be blue
                    arr[firstX+i][firstY+j] = 2;
                }
            }
        }
        return;
    }
   placeTormino(arr, size, firstX, firstY, edge, dp);     
}

int main(){
    srand(time(nullptr));
    int x = pow(2, N);
    int y = pow(2, N);

    int randX = rand() % x;
    int randY = rand() % y;

    int** arr = new int*[x];
    for(int i = 0; i < x; i++){
        arr[i] = new int[x];
    }

    //Initalize the array with zeros
    for(int i = 0; i < x; i++){
        for(int j = 0; j < x; j++){
            arr[i][j] = 0;
        }
    }
    arr[randX][randY] = -1;
    // We will create a dynamic programming memory to store the torminos solution
    int**** dp = new int***[N];
    for(int i = 0; i < N; i++){
        // In each size we will store 3 possible solutions for each color
        dp[i] = new int**[3];
    }

    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < 3; j++){
            // We will initialize the dp memory with -1 to indicate that we have not found a solution yet
            dp[i][j] = nullptr;
        }
    }

    tile(arr, x, 0, 0, dp);
    // for(int i = 0; i < x; i++){
    //     for(int j = 0; j < x; j++){
    //         cout << arr[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // return 0;
}                                                            