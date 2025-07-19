#!/usr/bin/python3
import sys
import copy

#Find the current location, but really only applies for the starting location
def findCurrentLocation(arr):
    col_id = 0
    for row_id in range(len(arr)):
        if('v' in arr[row_id]):
            col_id = arr[row_id].index('v')
        elif('>' in arr[row_id]):
            col_id = arr[row_id].index('>')
        elif('<' in arr[row_id]):
            col_id = arr[row_id].index('<')
        elif('^' in arr[row_id]):
            col_id = arr[row_id].index('^')
        if(col_id != 0):
            return (row_id, col_id)

#If function returns true, then the grid was able to be successfully traversed.
def traverseGrid(copied_arr, starting_row, starting_col, total_rows, total_cols):
    cur_row = starting_row
    cur_col = starting_col
    cur_movement_type = copied_arr[cur_row][cur_col]
    arr_count = [[0 for _ in range(total_cols)] for _ in range(total_rows)]
    copied_arr[cur_row][cur_col] = 'X'
    arr_count[cur_row][cur_col] = 1
    movement_order = '>v<^'
    while(True):
        prop_row = 0
        prop_col = 0
        if(cur_movement_type == '<'):
            prop_row = cur_row
            prop_col = cur_col-1
        elif(cur_movement_type == '>'):
            prop_row = cur_row
            prop_col = cur_col+1
        elif(cur_movement_type == '^'):
            prop_row = cur_row-1
            prop_col = cur_col
        elif(cur_movement_type == 'v'):
            prop_row = cur_row+1
            prop_col = cur_col
        #Check if we're now exiting the grid
        if(prop_row < 0 or prop_col < 0 or prop_row == total_rows or prop_col == total_cols):
            return True
        #When we encounted an obstacle, turn 90 degrees to the right and keep moving
        if(copied_arr[prop_row][prop_col] == '#'):
            #print(cur_movement_type)
            cur_movement_type = movement_order[(movement_order.index(cur_movement_type)+1) % 4]
            continue
        copied_arr[prop_row][prop_col] = 'X'
        arr_count[prop_row][prop_col] += 1
        cur_row = prop_row
        cur_col = prop_col
        if(arr_count[prop_row][prop_col] > 30):
            return False
        

def countMarkedSpots(arr):
    spots_marked = 0
    for row in arr:
        for spot in row:
            if(spot == 'X'):
                spots_marked+=1
    return spots_marked

def printGrid(arr):
    for row in arr:
        for spot in row:
            print(spot, end='')
        print()

def main():
    arr = []

    if(len(sys.argv) < 2):
        print("Must provide file as input to program")
        sys.exit()

    #Get all of the input into the 2d array
    with open(sys.argv[1], 'r') as fd:
        for line in fd.readlines():
            arr.append(list(line.strip()))

    num_rows = len(arr)
    # print(f"Number of rows in input: {num_rows}")
    num_cols = len(arr[1])
    # print(f"Number of cols in input: {num_cols}")

    starting_row, starting_col = findCurrentLocation(arr)
    # print(f"Starting point coords: {starting_row},{starting_col}")

    copied_arr = copy.deepcopy(arr)
    traverseGrid(copied_arr, starting_row, starting_col, num_rows, num_cols)
    p1_spots_marked = countMarkedSpots(copied_arr)

    # printGrid(copied_arr)

    print(f"p1 spots marked: {p1_spots_marked}")

    #Place an obstacle in a location on the grid, try to traverse it, then see if it fails or not
    well_placed_obstacles = 0
    for cur_obs_row in range(num_rows):
        for cur_obs_col in range(num_cols):
            if(cur_obs_col == starting_col and cur_obs_row == starting_row):
                continue
            copied_arr = copy.deepcopy(arr)
            copied_arr[cur_obs_row][cur_obs_col] = '#'
            if(traverseGrid(copied_arr, starting_row, starting_col, num_rows, num_cols) == False):
                print(f"Found a well placed obstacle at row {cur_obs_row} and column {cur_obs_col}")
                well_placed_obstacles += 1
    print(f"p2 well placed obstacles: {well_placed_obstacles}")

if(__name__ == "__main__"):
    main()