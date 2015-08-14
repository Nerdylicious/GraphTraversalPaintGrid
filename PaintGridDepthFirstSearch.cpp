//Purpose: Paint a boolean grid using depth first search
//The drawback of using a recursive approach is that the
//(implicit) stack will overflow quickly (since there are
//4 recursive calls each). If we paint 10 pixels away, this
//will lead to 4^10 or approximately 1 million entries
//in the call stack. A better alternative is doing a 
//breadth first search
#include <iostream>
using namespace std;

#define DIM_X 4
#define DIM_Y 4

enum color{
    white = 0,
    black = 1,
};

void print_grid(color grid[][DIM_X]){
    for(int r = 0; r < DIM_Y; r ++){
        for(int c = 0; c < DIM_X; c ++){
            cout << grid[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void paint_grid_dfs(color grid[][DIM_X], int x, int y, color orig_color, color new_color){

    if(orig_color != new_color){
        if((x >= 0) &&
            (x < DIM_X) &&
            (y >= 0) &&
            (y < DIM_Y)){

            if(grid[y][x] == orig_color){

                grid[y][x] = new_color;

                //visit all neighbors with the original color and is within the grid
                paint_grid_dfs(grid, x - 1, y, orig_color, new_color); //visit left neighbor
                paint_grid_dfs(grid, x + 1, y, orig_color, new_color); //visit right neighbor
                paint_grid_dfs(grid, x, y - 1, orig_color, new_color); //visit top neighbor
                paint_grid_dfs(grid, x, y + 1, orig_color, new_color); //visit bottom neighbor
            }
        }
    }
}

int main(){
    color grid[DIM_Y][DIM_X] = {
        { black, black, white, black },
        { black, white, white, black },
        { black, black, white, black },
        { black, white, white, black },
    };
    print_grid(grid);
    paint_grid_dfs(grid, 3, 3, grid[3][3], white);
    print_grid(grid);
    return 0;
}
