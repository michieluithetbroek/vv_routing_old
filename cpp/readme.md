#  Project overview

- Give every node at least _n_ outgoing arcs. This may avoid that dead ends street cannot be used

## Programming

### To do
- Separete init class for reading data
- Print tile data
- Correct tile input data
- Allow to set initial solution
- Reduces number of nodes on tiles
- Link CVRPSEP
- Implement user callback
- Use CVRPSEP in lazy callback

### Performance ideas for later
- Read more variables in callback at once instead of one by one
- Allocate vector for x values once in the Callback class instead of in lazy callback function
- Only create variables for non-zero arcs. Maybe we can use a vector of all existing arcs in the model class.
- auto const start1 = chrono::high_resolution_clock::now();

## Logbook
- 2022-04-19: implement lazy call back for SEC.
