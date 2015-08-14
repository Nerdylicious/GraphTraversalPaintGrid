//Purpose: Paint a boolean graph using breadth first search
#include <iostream>
using namespace std;

#define DIM_X 4
#define DIM_Y 4

#define NUM_OFFSETS 4

enum color{
    white = 0,
    black = 1,
};

class Coord{
    public:
        int x;
        int y;
        Coord(int, int);
};

Coord::Coord(int x, int y){
    this->x = x;
    this->y = y;
}

class Node{
    public:
        Coord *coord;
        Node *next;
        Node(Coord *);
};

Node::Node(Coord *coord){
    this->coord = coord;
    this->next = NULL;
}

class Queue{
    public:
        Node *first;
        Node *last;
        Queue();
        ~Queue();
        void enqueue(Coord *);
        Coord *dequeue();
        bool empty();
};

Queue::Queue(){
    this->first = NULL;
    this->last = NULL;
}

Queue::~Queue(){
    //to do
}

bool Queue::empty(){
    bool result = false;
    if(this->first == NULL){
        result = true;
    }
    return result;
}

void Queue::enqueue(Coord *coord){
    Node *new_node = new Node(coord);
    if(this->first == NULL && this->last == NULL){
        this->first = new_node;
        this->last = new_node;
    }
    else{
        this->last->next = new_node;
        this->last = new_node;
    }
}

Coord *Queue::dequeue(){
    Coord *coord = NULL;
    if(!empty()){
        if(this->first == this->last){
            Node *temp = this->first;
            coord = temp->coord;
            delete temp;
            this->first = NULL;
            this->last = NULL;
        }
        else{
            Node *temp = this->first;
            coord = temp->coord;
            this->first = this->first->next;
            delete temp;
        }
    }
    return coord;
}

void print_grid(color grid[][DIM_X]){
    for(int r = 0; r < DIM_Y; r ++){
        for(int c = 0; c < DIM_X; c ++){
            cout << grid[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void paint_grid_bfs(color grid[][DIM_X], Coord *coord, color orig_color, color new_color){

    if(orig_color != new_color){
        int neighbor_offsets[NUM_OFFSETS][2] = {
            { -1, 0 },
            { 1, 0 },
            { 0, -1 },
            { 0, 1 },
        };
        Queue *queue = new Queue();
        queue->enqueue(coord);
        grid[coord->y][coord->x] = new_color;

        while(!queue->empty()){
            Coord *curr_coord = queue->dequeue();
            //iterate through all incident edges
            for(int r = 0; r < NUM_OFFSETS; r ++){

                int neighbor_x = curr_coord->x + neighbor_offsets[r][0];
                int neighbor_y = curr_coord->y + neighbor_offsets[r][1];

                //check if the neighbor coord is within the grid
                if((neighbor_x >= 0) &&
                    (neighbor_x < DIM_X) &&
                    (neighbor_y >= 0) &&
                    (neighbor_y < DIM_Y)){

                    if(grid[neighbor_y][neighbor_x] == orig_color){
                        grid[neighbor_y][neighbor_x] = new_color;
                        Coord *neighbor_coord = new Coord(neighbor_x, neighbor_y);
                        queue->enqueue(neighbor_coord);
                    }
                }
            }
            delete curr_coord;
        }
        delete queue;
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
    paint_grid_bfs(grid, new Coord(1, 1), white, black);
    print_grid(grid);
    return 0;
}
