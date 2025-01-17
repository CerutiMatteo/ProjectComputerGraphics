INTRO
  - the game consists of searching for chests on the map, as soon as you find one another will appear in another spawn and the size of the chest will decrease making it more difficult to find

RULES:
  - in front of the home screen the user will be able to choose from the keyboard the number of chests to search for, if the user is playing with the joystick the chests to search for will always be 5
  - to collect the chests the user must be close to them
  - the user can switch between freecam mode and normal game mode at any time
  - the color of the direct light and the sky depends on the time the program is run. The user can also change manually by clicking C on the keyboard or TRIANGLE on the joystick
  - at the end of the mission a final screen will appear and the user will be able to continue exploring the map by clicking ENTER on the keyboard or X on the joystick
  - at the bottom left you can see a txt where the game phases and more are described

COMMAND (Keyboard - joystick):
  - enter - X            (to collect the chests and go beyond the overlays)
  - Tab   - O            (to hide or show the txt at the bottom left)
  - M     - R1           (to switch from freecam mode to game mode and vice versa)
  - C     - Triangolo    (to change the color of the sky and direct light)
  - R,F   - L2,L1        (to go up and down in freecam mode)
  - ESC                  (to quit)
  - To move use W, W+A, W+D, S or the left joystick
  - To move the view use the → ← ↓ ↑ or the right joystick

NOTES FOR PROGRAMMER:
  - for the current next spawn selection algorithm numOfHiddenchest must be less than (<) numOfSpawns
  - the text array that is passed to txt is currently made to have at most 9 chests to search
  - if you need to add more than 9 chests to search you need to pay attention to the scaling factor (currently it starts with a factor of 0.0027 and is decreased by 0.0003 each time it is found)
  - Projection Matrix (Mp): perspective projection technique
  - View Matrix (Mv): Freecam mode -> look-in technique, Game mode -> look-at technique
  - Lights: a direct light, an ambient light, a point light only at night for each street lamp
  - example command to compile shaders from .vert or .frag to .spv:
    C:\Users\Utente\Documents\VisualStudio\projects\ProjectComputerGraphics\ProjectComputerGraphics\shaders>glslc ToonShader.frag -o ToonFrag.spv
