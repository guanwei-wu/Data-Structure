#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

/* functions */
void heap_refresh(vector<int>& ol_i, vector<int>& ol_j, vector<int>& ol_val){

    int index = ol_val.size()-1;
    while(index>0){
        if(ol_val[(index-1)/2] > ol_val[index]){
            int temp = ol_val[(index-1)/2];
            ol_val[(index-1)/2] = ol_val[index];
            ol_val[index] = temp;
            temp = ol_i[(index-1)/2];
            ol_i[(index-1)/2] = ol_i[index];
            ol_i[index] = temp;
            temp = ol_j[(index-1)/2];
            ol_j[(index-1)/2] = ol_j[index];
            ol_j[index] = temp;
        }
        else{
            break;
        }
    }
    return ;
}

void min_heapify(vector<int>& ol_i, vector<int>& ol_j, vector<int>& ol_val, int key){

    if(ol_val.size()==0) return ;

    int l = 2*key+1, r = 2*key+2, smallest = 0;

    if(l<=ol_val.size()-1 && ol_val[l]<ol_val[key]) smallest = l;
    else smallest = key;

    if(r<=ol_val.size()-1 && ol_val[r]<ol_val[smallest]) smallest = r;

    if(smallest != key){
        int temp = ol_val[key];
        ol_val[key] = ol_val[smallest];
        ol_val[smallest] = temp;
        temp = ol_i[key];
        ol_i[key] = ol_i[smallest];
        ol_i[smallest] = temp;
        temp = ol_j[key];
        ol_j[key] = ol_j[smallest];
        ol_j[smallest] = temp;

        min_heapify(ol_i, ol_j, ol_val, smallest);
    }
    return ;
}

int MOVE_MIN_AT_LAST(vector<int>& ol_i, vector<int>& ol_j, vector<int>& ol_val){

    int temp = ol_val[ol_val.size()-1];
    ol_val[ol_val.size()-1] = ol_val[0];
    ol_val[0] = temp;
    temp = ol_i[ol_i.size()-1];
    ol_i[ol_i.size()-1] = ol_i[0];
    ol_i[0] = temp;
    temp = ol_j[ol_j.size()-1];
    ol_j[ol_j.size()-1] = ol_j[0];
    ol_j[0] = temp;

    temp = ol_val[ol_val.size()-1];
    ol_val.pop_back();

    min_heapify(ol_i, ol_j, ol_val, 0);

    return temp;
}

int main(){

    /* TODO: input */

    fstream fin;
    fstream fout;
    fin.open("PA_test/input5", ios::in);
    fout.open("PA_test/output5", ios::out);
    int INPUT_N = 0;
    fin >> INPUT_N;

    vector<vector<int>> INPUT_GRID = {};
    int weight = 0;
    int f_i, f_j = 0;
    INPUT_GRID.push_back({});
    for(int i=0;i<INPUT_N;i++){
        INPUT_GRID.push_back({});
        for(int j=0;j<INPUT_N;j++){
            fin >> weight;
            INPUT_GRID[i].push_back(weight);
        }
    }

    /* test input input0 */
//    int INPUT_N = 10;
//    vector<vector<int>> INPUT_GRID = {
//    {56, 29, 53, 7, 47, 12, 43, 28, 12, 34},
//    {33, 18, 36, 49, 49, 41, 3, 33, 49, 53},
//    {4, 57, 34, 59, 30, 26, 42, 31, 1, 12},
//    {5, 60, 34, 62, 55, 20, 19, 7, 5, 41},
//    {22, 50, 36, 42, 51, 58, 50, 18, 8, 18},
//    {36, 14, 33, 40, 0, 30, 8, 43, 12, 61},
//    {30, 11, 6, 4, 43, 0, 21, 12, 51, 13},
//    {0, 19, 10, 6, 30, 33, 40, 16, 13, 42},
//    {0, 40, 39, 55, 14, 38, 50, 1, 48, 3},
//    {23, 29, 54, 26, 22, 31, 60, 43, 55, 56}
//    };


    /* parameter */
    vector<vector<int>> record = {};
    vector<vector<char>> pred = {};
    vector<int> ol_i, ol_j, ol_val = {}; // ol = openlist, used as stack.
    int temp_i, temp_j, temp_val = 0;

    /* initialization */
    for(int i=0;i<INPUT_N;i++){
        record.push_back({});
        pred.push_back({});
        for(int j=0;j<INPUT_N;j++){
            record[i].push_back(INT_MAX);
            pred[i].push_back('N');
        }
    }
    record[0][0] = INPUT_GRID[0][0];
    ol_i.push_back(0);
    ol_j.push_back(0);
    ol_val.push_back(record[ol_i[0]][ol_j[0]]);

    /* Dijkstra's Algorithm */
    while(ol_val.size()>0){

        temp_val = MOVE_MIN_AT_LAST(ol_i, ol_j, ol_val);
        temp_i = ol_i[ol_i.size()-1];
        ol_i.pop_back();
        temp_j = ol_j[ol_j.size()-1];
        ol_j.pop_back();

        if(temp_i==INPUT_N-1 && temp_j==INPUT_N-1) break;

        /* up */
        if(temp_i>=1 && temp_val + INPUT_GRID[temp_i-1][temp_j] < record[temp_i-1][temp_j]){
            ol_val.push_back(temp_val + INPUT_GRID[temp_i-1][temp_j]);
            ol_i.push_back(temp_i-1);
            ol_j.push_back(temp_j);
            heap_refresh(ol_i, ol_j, ol_val);
            record[temp_i-1][temp_j] = temp_val + INPUT_GRID[temp_i-1][temp_j];
            pred[temp_i-1][temp_j] = 'U';
        }
        /* down */
        if(temp_i<=INPUT_N-2 && temp_val + INPUT_GRID[temp_i+1][temp_j] < record[temp_i+1][temp_j]){
            ol_val.push_back(temp_val + INPUT_GRID[temp_i+1][temp_j]);
            ol_i.push_back(temp_i+1);
            ol_j.push_back(temp_j);
            heap_refresh(ol_i, ol_j, ol_val);
            record[temp_i+1][temp_j] = temp_val + INPUT_GRID[temp_i+1][temp_j];
            pred[temp_i+1][temp_j] = 'D';
        }
        /* left */
        if(temp_j>=1 && temp_val + INPUT_GRID[temp_i][temp_j-1] < record[temp_i][temp_j-1]){
            ol_val.push_back(temp_val + INPUT_GRID[temp_i][temp_j-1]);
            ol_i.push_back(temp_i);
            ol_j.push_back(temp_j-1);
            heap_refresh(ol_i, ol_j, ol_val);
            record[temp_i][temp_j-1] = temp_val + INPUT_GRID[temp_i][temp_j-1];
            pred[temp_i][temp_j-1] = 'L';
        }
        /* right */
        if(temp_j<=INPUT_N-2 && temp_val + INPUT_GRID[temp_i][temp_j+1] < record[temp_i][temp_j+1]){
            ol_val.push_back(temp_val + INPUT_GRID[temp_i][temp_j+1]);
            ol_i.push_back(temp_i);
            ol_j.push_back(temp_j+1);
            heap_refresh(ol_i, ol_j, ol_val);
            record[temp_i][temp_j+1] = temp_val + INPUT_GRID[temp_i][temp_j+1];
            pred[temp_i][temp_j+1] = 'R';
        }
    }

    /* output */
    int length = record[INPUT_N-1][INPUT_N-1], step = 1;
    string str = "";
    int back_i = INPUT_N-1, back_j = INPUT_N-1;
    while(! (back_i==0 && back_j==0) ){
        step++;
        if(pred[back_i][back_j]=='U'){
            back_i += 1;
            str = 'U' + str;
        }
        else if(pred[back_i][back_j]=='D'){
            back_i -= 1;
            str = 'D' + str;
        }
        else if(pred[back_i][back_j]=='L'){
            back_j += 1;
            str = 'L' + str;
        }
//        else if(pred[back_i][back_j]=='R'){
//            back_j -= 1;
//            str = 'R' + str;
//        }
        else{
            back_j -= 1;
            str = 'R' + str;
        }
    }
    fout<<length<<" "<<step<<endl<<str;
    fin.close();
    fout.close();

    return 0;
}
