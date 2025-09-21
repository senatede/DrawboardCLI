# Assignment 1

## Git repository:

[https://github.com/VY-Assignments/oopd-assignment1-2025-bohdan-hupalo](https://github.com/VY-Assignments/oopd-assignment1-2025-bohdan-hupalo)

## Original design in mind
![desin](https://i.postimg.cc/h4QKgzDp/design.jpg)

The initial design had six classes: **Board**, **Shape** and 4 shapes subclasses. Idea of storing shapes in vector ordered by the layer worked perfectly. Shape class has necessary fields: id, type, fill, color, x, y. Subclasses have parameters for specific shapes(height for triangle, width and height for box, radius for circle and  dx, dy for line). Shape contains virtual methods draw(), info().

For the interface logic I added **CLI** class that handled command input and output. For file logic I chose to store board data in json format.

For the additional task I had to rethink color logic, I created new class **Color(name, r, g,b).** I replaced previous `std::string color` field with `std::shared_ptr<Color>`, also grid was no longer `std::vector<std::vector<char> >` but instead `std::vector<std::vector<std::shared_ptr<Color>> >`, where `nullptr` means empty pixel. I also had to add new command for adding color and file logic to store added colors

All the available commands are:

- help
- exit
- create <width> <height> - Create blackboard.
- draw - Draw blackboard to the console.
- color <name> <r> <g> <b> - add color.
- colors - list all available colors.
- list - Print all added shapes with their IDs and parameters.
- shape - Print a list of all available shapes and parameters for add call.
- add <parameters> - Add shape with specified colour and fill mode to the blackboard.
- select <id|x y> - Select a shape with an ID Or foreground shape by the selected coordinates.
- remove - Remove selected from blackboard the shape.
- edit <parameters> - Allows to modify the parameters of the selected figure.
- paint <color> - Change the colour the selected of figure.
- move <coordinates> - Move the selected shape to the coordinates.
- clear - Remove all shapes from blackboard.
- save <file-path> - Save the blackboard to the file.
- load <file-path> - Load the blackboard from the file.
